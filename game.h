#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#ifndef GAME_H
#define GAME_H
class Game
{
private:
	Game();
public:
	~Game();
	bool init(const char* title, int xpos, int
		ypos, int width, int height, bool fullscreen);
	SDL_Renderer* getRender();
	void setRender(SDL_Renderer* render);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	static Game* Instance();
	GameStateMachine* getStateMachine();
	bool running = false;
	int getGameWidth();
	int getGameHeight();
private:
	SDL_Window* g_lWindow = 0;
	SDL_Renderer* g_lRenderer = 0;
	static Game* s_pInstanceG;
	int m_gameWidth;
	int m_gameHeight;
};
#endif GAME_H