#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor
	};

public:
	Aircraft(Type type, Game* game);
	Aircraft::Type GetAircraftType() { return mType; }

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();

private:
	Type				mType;
	std::string			mSprite;
};
