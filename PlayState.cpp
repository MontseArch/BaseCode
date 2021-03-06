#include "PlayState.h"
#include "Dog.h"
#include "Player.h"
#include "game.h"
#include "MenuState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "SoundManager.h"

const std::string PlayState::s_playID = "PLAY";
void PlayState::update()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		s_playToPause();
		//Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	/*
	for (int i = 0; i < m_gameObjectsPlay.size(); i++)
	{
		m_gameObjectsPlay[i]->update();
	}*/
	ppLevel->update();
}
void PlayState::render()
{
	
	//for (int i = 0; i < m_gameObjectsPlay.size(); i++)
	//{
		//m_gameObjectsPlay[i]->draw();
	//}
	ppLevel->render();
}
bool PlayState::onEnter()
{
	// parse the state
	//StateParser stateParser;
	//stateParser.parseState("assets/images.xml", s_playID, &m_gameObjectsPlay, &m_textureIDList);
	SDL_Renderer* render;
	render = Game::Instance()->getRender();
	SDL_SetRenderDrawColor(render, 133, 224, 255, 255);
	Game::Instance()->setRender(render);
	SoundManager::Instance()->playMusic("SongPlay", -1);
	LevelParser levelParser;
	ppLevel = levelParser.parseLevel("assets/mapaBueno.tmx");



	return true;
}
bool PlayState::onExit()
{
	SoundManager::Instance()->stopMusic();
	InputHandler::Instance()->clean();
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	m_textureIDList.clear();
	//Game::Instance()->getStateMachine()->popState();
	m_textureIDList.clear();

	m_gameObjectsPlay.clear();
	
	return true;
}

void PlayState::s_playToPause()
{
	SoundManager::Instance()->stopMusic();
	Game::Instance()->getStateMachine()->pushState(new PauseState());
	//Game::Instance()->getStateMachine()->changeState(new PauseState());
}