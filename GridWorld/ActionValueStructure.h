#pragma once

template <class StateType, class ActionType>
class ActionValueStructure
{
public:
	virtual float GetStateActionValue(const pair<StateType, ActionType>& stateAction) const = 0;
	virtual void SetStateActionValue(const pair<StateType, ActionType>& stateAction, float value) = 0;
};