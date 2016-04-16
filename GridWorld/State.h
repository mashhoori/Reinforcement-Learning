#pragma once
class State
{	
public:
	virtual int GetHashCode() const = 0;
	bool operator<(const State& state) const{
		return GetHashCode() < state.GetHashCode();
	}
};

