#include "StateStack.h" 

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}

void StateStack::update(const GameTimer& gt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(gt))
			break;
	}
	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::Ptr& state : mStack)
		state->draw();
}
void StateStack::buildScene()
{
	applyPendingChanges();
	for (State::Ptr& state : mStack)
		state->buildScene();
}

void StateStack::buildScene(States::ID ID)
{
	applyPendingChanges();

	for (State::Ptr& state : mStack)
		state->buildScene();
}

void StateStack::handleEvent(WPARAM btnStat)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		if (!(*itr)->handleEvent(btnStat))
			break;

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
	applyPendingChanges();
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

void StateStack::RemoveState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Remove, stateID));
}

void StateStack::changeStateCondition(States::ID stateID, bool OnlyScene)/// test for states
{
	State::Ptr stateFound = createState(stateID);

	for (State::Ptr& state : mStack)
	{
		if (typeid(*state) == typeid(*stateFound))
		{
			if (OnlyScene)
				state->SetScene();
			else
			{
				state->SetIsActive(!state->GetIsActive());
				if (state->GetIsActive())
					state->SetScene();
				else
					state->HideScene();

			}

		}
	}
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

CommandQueue& StateStack::getCommandQueue()
{
	return mCommandQueue;
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
		case Remove:

			for (State::Ptr& state : mStack)
			{
				if (typeid(*state) == typeid(createState(change.stateID)))
				{
					auto itr = std::remove(mStack.begin(), mStack.end(), state);
					mStack.erase(itr, mStack.end());
				}
			}
			break;
		}
	}
	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{
}

#pragma endregion