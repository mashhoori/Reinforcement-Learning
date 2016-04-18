#pragma once

template<class StateType, class ActionType>
class PolicyIteration
{
private:
	float delta;
	float discountFactor;
	bool MapsAreEqual(const map<ActionType, float>& oldMap, const map<ActionType, float>& newMap) const;

public:
	PolicyIteration(float delta, float discountFactor)
		: delta{ delta }, discountFactor{ discountFactor }
	{}
	
	void EvaluatePolicy(const Environment<StateType, ActionType>& env, const Policy<StateType, ActionType>& policy, StateValueStructure<StateType>& valueStr);
	bool ImporvePolicy(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const StateValueStructure<StateType>& valueStr);

	void Run(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, StateValueStructure<StateType>& valueStr);
};

template<class StateType, class ActionType>
bool PolicyIteration<StateType, ActionType>::MapsAreEqual(const map<ActionType, float>& oldMap, const map<ActionType, float>& newMap) const 
{
	if (oldMap.size() != newMap.size())
		return true;
	for (auto item : oldMap)
		if (newMap.count(item.first) == 0 || newMap.at(item.first) != item.second)
			return true;

	return false;
}

template<class StateType, class ActionType>
void PolicyIteration<StateType, ActionType>::EvaluatePolicy(const Environment<StateType, ActionType>& env, const Policy<StateType, ActionType>& policy, StateValueStructure<StateType>& valueStr)  
{
	vector<StateType> allStates = env.GetAllStates();

	while (true)
	{
		bool converge = true;
		for (StateType& s : allStates)
		{
			float value = 0;
			float preVal = valueStr.GetStateValue(s);

			for (auto act : policy.GetActionDistribution(s))
				for (auto ns : env.GetNextStateDistribution(s, act.first))
					value += act.second * ns.second * (env.GetReward(s, act.first, ns.first) + discountFactor * valueStr.GetStateValue(ns.first));

			valueStr.SetStateValue(s, value);
			if (abs(preVal - value) > delta)
				converge = false;
		}

		if (converge)
			break;
	}

}

template<class StateType, class ActionType>
bool PolicyIteration<StateType, ActionType>::ImporvePolicy(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const StateValueStructure<StateType>& valueStr)
{
	bool anyChange = false;	

	vector<StateType> allStates = env.GetAllStates();
	for (StateType s : allStates)
	{
		vector<ActionType> bestActions;
		float maxVal = -10000;

		for (auto act : env.GetPossibleActions(s))
		{
			float value = 0;
			for (auto ns : env.GetNextStateDistribution(s, act))
				value += ns.second * (env.GetReward(s, act, ns.first) + discountFactor * valueStr.GetStateValue(ns.first));

			if (value > maxVal)
			{
				bestActions.clear();
				bestActions.push_back(act);
				maxVal = value;
			}
			else if (value == maxVal)
				bestActions.push_back(act);
		}

		map<ActionType, float> newMap;
		for (ActionType act : bestActions)
			newMap[act] = 1.0 / bestActions.size();
		
		auto oldMap = policy.GetActionDistribution(s);
		policy.SetActionDistribution(s, newMap);

		if(MapsAreEqual(oldMap, newMap))
			anyChange = true;
	}

	return anyChange;
}

template<class StateType, class ActionType>
void PolicyIteration<StateType, ActionType>::Run(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, StateValueStructure<StateType>& valueStr)
{
	bool policyChanged = true;
	int i = 0;
	do
	{
		EvaluatePolicy(env, policy, valueStr);
		policyChanged = ImporvePolicy(env, policy, valueStr);
	} while (policyChanged);
}

