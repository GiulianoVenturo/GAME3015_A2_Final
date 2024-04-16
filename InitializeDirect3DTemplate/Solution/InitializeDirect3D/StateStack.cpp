#pragma region step 5
#include "StateStack.h" 

#include <cassert>


StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}



void StateStack::update(const GameTimer& gt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(gt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	for (State::Ptr& state : mStack)
		state->draw();
	
}
void StateStack::buildScene() // add it
{
	//  active buildscene in states from bottom to top
	applyPendingChanges(); // wtf

	for (State::Ptr& state : mStack)
		state->buildScene();
}

void StateStack::buildScene(States::ID ID) // add it
{
	//  active buildscene in states from bottom to top
	applyPendingChanges(); // wtf

	for (State::Ptr& state : mStack)
	{
		state->buildScene();

		if (state->getStateID() == ID)
		{
		}
	}
}

void StateStack::handleEvent(WPARAM btnStat)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(btnStat))
			break;
	}

	
	applyPendingChanges();

}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
	applyPendingChanges();
}

void StateStack::popState()
{
	//applyPendingChanges();
	mPendingList.push_back(PendingChange(Pop));
	//applyPendingChanges();

}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

void StateStack::RemoveState(States::ID stateID)
{

	mPendingList.push_back(PendingChange(Remove, stateID));
	//applyPendingChanges();
}

//void StateStack::changeStateCondition(States::ID stateID)/// test for states
//{
//	State::Ptr stateFound = createState(stateID);
//
//	for (State::Ptr& state : mStack)
//	{
//		if (typeid(*state) == typeid(*stateFound))
//		{
//			state->SetIsActive(!state->GetIsActive());
//			state->SetScene();
//
//			
//		}
//	}
//}

void StateStack::changeStateCondition(States::ID stateID, bool OnlyScene)/// test for states
{
	State::Ptr stateFound = createState(stateID);

	for (State::Ptr& state : mStack)
	{
		if (typeid(*state) == typeid(*stateFound))
		{
			if (OnlyScene)
			{
				state->SetScene();
			}
			else
			{
				state->SetIsActive(!state->GetIsActive());
				if (state->GetIsActive())
				{
					state->SetScene();

				}
				else
				{
					state->HideScene();
				}

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

			//auto itr = std::remove(mStack.begin(), mStack.end(), createState(change.stateID));
			//mStack.erase(itr, mStack.end());
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