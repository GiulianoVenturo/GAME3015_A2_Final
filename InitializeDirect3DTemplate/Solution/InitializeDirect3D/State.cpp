#include "State.h"
#include "StateStack.h"


State::Context::Context(Game* game, Player& player)
	:mPlayer(&player), mGame(game)
{
}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}


State::~State()
{
}

bool State::handleEvent(WPARAM wparam)
{
	return false;
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}
void State::requestStateRemoval(States::ID stateID)
{
	mStack->RemoveState(stateID);
}

void State::ChangeScene(States::ID stateID)
{
	requestStackPop();
	requestStackPush(stateID);
}


bool State::GetIsActive()
{
	return mIsActive;
}

void State::SetIsActive(bool isActive)
{
	mIsActive = isActive;
}


void State::SetScene()
{

}
void State::HideScene()
{

}

void State::requestChangeState(States::ID stateID, bool isOnlyScene)
{
	mStack->changeStateCondition(stateID, isOnlyScene);
}
State::Context State::getContext() const
{
	return mContext;
}

#pragma endregion