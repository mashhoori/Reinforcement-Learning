#pragma once

template<class StateType, class ActionType>
class ValueIteration
{
private:
	float delta;
	float discountFactor;
	
public:
	ValueIteration(float delta, float discountFactor)
		: delta{ delta }, discountFactor{ discountFactor }
	{}

	void ComputeValue(const Environment<StateType, ActionType>& env, ValueStructure<StateType>& valueStr);
	void CreatePolicy(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const ValueStructure<StateType>& valueStr);

	void Run(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, ValueStructure<StateType>& valueStr);
};

template<class StateType, class ActionType>
void ValueIteration<StateType, ActionType>::ComputeValue(const Environment<StateType, ActionType>& env, ValueStructure<StateType>& valueStr)
{
	vector<StateType> allStates = env.GetAllStates();

	while (true)
	{
		bool converge = true;
		for (StateType& s : allStates)
		{	
			float preVal = valueStr.GetStateValue(s);
			float maxVal = preVal;

			for (auto act : env.GetPossibleActions(s))
			{
				float value = 0;
				for (auto ns : env.GetNextStateDistribution(s, act))
					value += ns.second * (env.GetReward(s, act, ns.first) + discountFactor * valueStr.GetStateValue(ns.first));
			
				if (value > maxVal)
					maxVal = value;
			}
			valueStr.SetStateValue(s, maxVal);
			if (abs(preVal - maxVal) > delta)
				converge = false;
		}

		if (converge)
			break;
	}

}

template<class StateType, class ActionType>
void ValueIteration<StateType, ActionType>::CreatePolicy(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const ValueStructure<StateType>& valueStr)
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
	}	
}

template<class StateType, class ActionType>
void ValueIteration<StateType, ActionType>::Run(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, ValueStructure<StateType>& valueStr)
{
	ComputeValue(env, valueStr);
	CreatePolicy(env, policy, valueStr);
}

