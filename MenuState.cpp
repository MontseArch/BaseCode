#include "MenuState.h"
//#include <string>
#include "MenuButton.h"
#include "TextureManager.h"
#include "game.h"
#include "PlayState.h"
#include "StateParser.h"

typedef void(*Callback)();
const std::string MenuState::s_menuID = "MENU";

MenuState::MenuState() {
}

MenuState::~MenuState() {
}

void MenuState::update()
{
	for (int i = 0; i < m_gameObjectsMenuState.size(); i++)
	{
		m_gameObjectsMenuState[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjectsMenuState.size(); i++)
	{
		m_gameObjectsMenuState[i]->draw();
	}
}

bool MenuState::onEnter()
{
	// parse the state
	StateParser stateParser;
	stateParser.parseState("assets/images.xml", s_menuID, &m_gameObjectsMenuState, &m_textureIDList);
	m_callbacksMenu.push_back(0); //pushback 0 callbackID start from 1
	m_callbacksMenu.push_back(s_menuToPlay);
	m_callbacksMenu.push_back(s_exitFromMenu);
	// set the callbacks for menu items
	setCallbacks(m_callbacksMenu);

	/*
	if (!TextureManager::Instance()->load("button_play.png","playbutton", Game::Instance()->getRender()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("button_exit.png","exitbutton", Game::Instance()->getRender()))
	{
		return false;
	}

	MenuButton* button1 = new MenuButton(new LoaderParams(160, 100, 322, 150, "playbutton"), s_menuToPlay);
	MenuButton* button2 = new MenuButton(new LoaderParams(160, 250, 322, 150, "exitbutton"), s_exitFromMenu);
	m_gameObjectsMenuState.push_back(button1);
	m_gameObjectsMenuState.push_back(button2);
	*/
	return true;
}

bool MenuState::onExit()
{
	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
			TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	/*
	for (int i = 0; i < m_gameObjectsMenuState.size(); i++)
	{
		m_gameObjectsMenuState[i]->clean();
	}
	m_gameObjectsMenuState.clear();
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	*/
	// reset the mouse button states to false
	InputHandler::Instance()->reset();
	return true;
}

void MenuState::s_menuToPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	Game::Instance()->running = false;
	Game::Instance()->clean();
}

void MenuState::setCallbacks(const std::vector<Callback>&callbacks){
	// go through the game objects
	for (int i = 0; i < m_gameObjectsMenuState.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(m_gameObjectsMenuState[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjectsMenuState[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
	}
}