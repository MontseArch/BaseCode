#pragma once
//#include "GameObject.h"
#include "LoaderParams.h"
#include "SDL.h"
#include "Vector2D.h"
#include "CollisionObject.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public CollisionObject
{
public:
	Player();
	~Player();
	void load(const LoaderParams* ppParams);
	void draw();
	void update();
	void clean();
	void Player::handleInput();
	static GameObject * Create() { return new Player(); }
protected:
	const LoaderParams *pParams;
};
#endif PLAYER_H
