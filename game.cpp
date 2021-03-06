#include "game.h"
#include "GameObject.h"
#include <stdlib.h>
#include "SDL_image.h"
#include <vector>
#include "Player.h"
#include "Dog.h"
#include "GameStateMachine.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "ImageSimple.h"


std::vector<GameObject*> m_gameObjects;
TextureManager* TextureManager::s_pInstance = 0;
GameObject* player;
GameObject* dog;
GameObject* menu;
std::vector<LoaderParams*> loader;
LoaderParams* l1;
LoaderParams* l2;
Game* Game::s_pInstanceG = 0;
GameStateMachine* m_pGameStateMachine;

	Game::Game(){
	}

	Game::~Game(){
	}

	Game* Game::Instance()
	{
		if (s_pInstanceG == 0)
		{
			s_pInstanceG = new Game();
		}
		return s_pInstanceG;
	}

	SDL_Renderer* Game::getRender() {
		return g_lRenderer;
	}

	bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
		//Cargamos todos los sonidos
		SoundManager::Instance()->load("./sound/SongPlay.wav", "SongPlay", SOUND_MUSIC);
		SoundManager::Instance()->load("./sound/SongMenu.wav", "SongMenu", SOUND_MUSIC);
		SoundManager::Instance()->load("./sound/SongPause.wav", "SongPause", SOUND_MUSIC);
		SoundManager::Instance()->load("./sound/SongGameOver.wav", "SongGameOver", SOUND_MUSIC);
		SoundManager::Instance()->load("./sound/Jump.wav", "Jump", SOUND_SFX);
		// initialize SDL
		m_gameWidth = width;
		m_gameHeight = height;
		
		if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		{
			// if succeeded create our window
			g_lWindow = SDL_CreateWindow(title,xpos, ypos,width, height,fullscreen);
			// if the window creation succeeded create our renderer
			if (g_lWindow != 0)
			{
				g_lRenderer = SDL_CreateRenderer(g_lWindow, -1, 0);
			}
		}
		else
		{
			return false; // sdl could not initialize
		}

		//Registrem els objectes
		GameObjectFactory::Instance()->Register("MenuButton", MenuButton::Create);
		GameObjectFactory::Instance()->Register("Player", &Player::Create);
		GameObjectFactory::Instance()->Register("Dog", Dog::Create);
		GameObjectFactory::Instance()->Register("ImageSimple", ImageSimple::Create);

		//Creem la maquina d'estats
		m_pGameStateMachine = new GameStateMachine();
		//I fem un changeState per inciar en el estat de MenuState
		m_pGameStateMachine->changeState(new MenuState());
		//Posem el running a true per indicar que el programa esta en execuci�
		running = true;
		return true;
	}

	void Game::render()
	{
		//SDL_SetRenderDrawColor(g_lRenderer, 255, 229, 204, 255);
		SDL_RenderClear(g_lRenderer);
		m_pGameStateMachine->render();
		SDL_RenderPresent(g_lRenderer);
	}

	void Game::update()
	{
		m_pGameStateMachine->update();
	}

	void Game::handleEvents() {
		InputHandler::Instance()->update();
	}
	void Game::clean() {
		
		for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->clean();
		}
		
		SDL_DestroyWindow(g_lWindow);
		SDL_DestroyRenderer(g_lRenderer);
		SDL_Quit();
	}
	bool Game::isRunning() {
		return running;
	}

	void Game::setRender(SDL_Renderer* render) {
		g_lRenderer = render;
	}
	
	GameStateMachine* Game::getStateMachine() {
		return m_pGameStateMachine;
	}

	int Game::getGameWidth()
	{
		return m_gameWidth;
	}

	int Game::getGameHeight()
	{
		return m_gameHeight;
	}
	