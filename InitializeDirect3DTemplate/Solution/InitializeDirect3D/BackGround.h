#pragma once
#include"Entity.hpp"

class BackGround :
	public Entity
{
public:
	enum BackGroundType
	{
		TitleScreen,
		MainMenu,
		PauseScreen
	};
public:
	BackGround(BackGroundType Type, Game* game);
public:
	virtual void drawCurrent() const;
	virtual void buildCurrent();
private:
	BackGroundType    mType;
	std::string       mSprite;
};

