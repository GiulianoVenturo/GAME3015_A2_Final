#pragma once

#include "Command.h"
#include "Input.h"
#include "map"

class CommandQueue;

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};

	Player();
	static const float		PlayerSpeed;
	void                    handleEvent(CommandQueue& commands, WPARAM btnState);
	void					handleRealtimeInput(CommandQueue& commands);
	void					assignKey(Action action, Input::Keys key);
	Input::Keys		        getAssignedKey(Action action) const;

private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);

private:
	std::map< Input::Keys, Action>		mKeyBinding;
	std::map<Action, Command>			mActionBinding;
};
#pragma endregion



