#pragma once
#include"Entity.hpp"
class UIHandler
	:
	public Entity
{
public:
	enum UIHandlerType
	{
		PressAnyKey,
		MainMenu
	};
public:
	UIHandler(UIHandlerType Type, Game* game);
public:
	virtual void drawCurrent() const;
	virtual void buildCurrent();
private:
	UIHandlerType   mType;
	std::string       mSprite;
};