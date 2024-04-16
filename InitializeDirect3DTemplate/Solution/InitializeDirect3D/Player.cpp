
#include "Player.h"
#include "SceneNode.hpp"
#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.hpp"
#include "Game.h"

const float Player::PlayerSpeed = 40.0f;

std::ofstream myfile;
Input::Keys myKeys;

struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz)
		: velocity(vx, vy, vz)
	{
	}

	void operator() (SceneNode& node, const float dt) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity);
	}

	XMFLOAT3 velocity;
};

Player::Player()
{
	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	if (GetAsyncKeyState(Input::A) & 0x8000  )
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-PlayerSpeed, 0.f, 0.f));
		commands.push(moveLeft);

	}

	if (GetAsyncKeyState(Input::D) & 0x8000 )
	{
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(AircraftMover(PlayerSpeed , 0.f, 0.f));
		commands.push(moveRight);
	}

	if (GetAsyncKeyState(Input::W) & 0x8000  )
	{
		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(AircraftMover(0.f, 0.f, PlayerSpeed ));
		commands.push(moveUp);
	}
	
	if (GetAsyncKeyState(Input::S) & 0x8000 )
	{
		Command moveDown;
		moveDown.category = Category::PlayerAircraft;
		moveDown.action = derivedAction<Aircraft>(AircraftMover(0.f, 0.f, -PlayerSpeed ));
		commands.push(moveDown);
	}

	if (GetAsyncKeyState(Input::Q) & 0x8000)
	{
		Command goUpwards;
		goUpwards.category = Category::PlayerAircraft;
		goUpwards.action = derivedAction<Aircraft>(AircraftMover(0.f, PlayerSpeed, 0.f));
		commands.push(goUpwards);
	}

	if (GetAsyncKeyState(Input::E) & 0x8000)
	{
		Command goDownwards;
		goDownwards.category = Category::PlayerAircraft;
		goDownwards.action = derivedAction<Aircraft>(AircraftMover(0.f, -PlayerSpeed, 0.f));
		commands.push(goDownwards);
	}

}
void Player::initializeActions()
{
}

void Player::handleEvent(CommandQueue& commands, WPARAM btnState)
{
	Input::Keys tempKeys;

	tempKeys = (Input::Keys)btnState;

	auto found = mKeyBinding.find(tempKeys);
	if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		commands.push(mActionBinding[found->second]);
}


bool Player::isRealtimeAction(Action action)
{
	return false;
}

void Player::assignKey(Action action, Input::Keys key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}
	// Insert new binding
	mKeyBinding[key] = action;
}

Input::Keys Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return Input::Keys::Unknown;
}

#pragma endregion