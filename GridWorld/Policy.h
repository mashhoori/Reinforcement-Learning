#pragma once
#include "State.h"
#include "Action.h"

template<class StateType, class ActionType>
class Policy
{
public:	
	virtual void SetActionDistribution(const StateType& a, const map<ActionType, float>& actDist) = 0;
	virtual map<ActionType, float> GetActionDistribution(const StateType& state) const = 0;		
};

