#pragma once
#include "stdafx.h"
#include "State.h"
#include "Action.h"
#include "Environment.h"

template<class StateType, class ActionType>
class Environment
{
public:

	virtual float GetReward(const StateType& preState, const ActionType& a, const StateType& newState) const = 0;
	virtual map<StateType, float> GetNextStateDistribution(const StateType& state, const ActionType& a) const = 0;
	virtual vector<StateType> GetAllStates() const = 0;
	virtual vector<ActionType>  GetPossibleActions(const StateType& state) const= 0;
	
};




