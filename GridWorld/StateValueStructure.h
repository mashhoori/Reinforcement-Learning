#pragma once
template <class StateType>
class StateValueStructure
{
public:
	virtual float GetStateValue(const StateType& state) const = 0;
	virtual void SetStateValue(const StateType& state, float value) = 0;
};

