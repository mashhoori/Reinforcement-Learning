#pragma once
#include "ActionValueStructure.h"
#include "Global.h"

template<class StateType, class ActionType>
class MonteCarlo_ES
{
private:
	float discountFactor;
	//float delta;	
	float eps;
	
	pair<StateType, ActionType> GenerateRandomStateAction(const Environment<StateType, ActionType>& env);
	vector<tuple<StateType, ActionType, float>> GenerateEpisode(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const pair<StateType, ActionType>& init);

public:
	MonteCarlo_ES()
		:eps{ 0.02f }, discountFactor{ 0.8f }
	{}

	void ImporvePolicy(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const ActionValueStructure<StateType, ActionType>& valueStr, const vector<StateType>& stateList);
	void Run(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, ActionValueStructure<StateType, ActionType>& valueStr);

};



template<class StateType, class ActionType>
vector<tuple<StateType, ActionType, float>> MonteCarlo_ES<StateType, ActionType>::GenerateEpisode(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const pair<StateType, ActionType>& init)
{
	StateType state = init.first;
	ActionType action = init.second;

	vector<tuple<StateType, ActionType, float>> list;

	while (true)
	{
		StateType newS = Global::SelectFromDistribution<StateType>(env.GetNextStateDistribution(state, action));

		float reward = env.GetReward(state, action, newS);
		auto t = make_tuple(state, action, reward);
		list.push_back(t);

		state = newS;

		if (!env.IsStateFinal(state))
			action = Global::SelectFromDistribution<ActionType>(policy.GetActionDistribution(state));
		else
			break;		
	}
	
	return list;
}


template<class StateType, class ActionType>
pair<StateType, ActionType> MonteCarlo_ES<StateType, ActionType>::GenerateRandomStateAction(const Environment<StateType, ActionType>& env)
{
	vector<StateType> allStates = env.GetAllStates();
	uniform_int_distribution<int> distribution1(0, allStates.size() - 1);
	int index = distribution1(Global::generator);
	StateType state = allStates[index];

	while (env.IsStateFinal(state))
	{
		index = distribution1(Global::generator);
		state = allStates[index];
	}

	vector<ActionType> allActions = env.GetPossibleActions(state);
	uniform_int_distribution<int> distribution2(0, allActions.size() - 1);
	index = distribution2(Global::generator);

	ActionType action = allActions[index];

	return make_pair(state, action);
}


template<class StateType, class ActionType>
void MonteCarlo_ES<StateType, ActionType>::ImporvePolicy(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, const ActionValueStructure<StateType, ActionType>& valueStr, const vector<StateType>& stateList)
{	
	for (StateType s : stateList)
	{
		vector<ActionType> bestActions;
		float maxVal = -10000;

		auto posibleActions = env.GetPossibleActions(s);
		for (auto act : posibleActions)
		{
			float value = valueStr.GetStateActionValue( make_pair(s, act) );
		
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

		for (auto act : posibleActions)		
			newMap[act] = eps;		

		for (ActionType act : bestActions)
			newMap[act] += (1.0 - posibleActions.size() * eps) / bestActions.size();

		auto oldMap = policy.GetActionDistribution(s);
		policy.SetActionDistribution(s, newMap);		
	}
}




template<class StateType, class ActionType>
void MonteCarlo_ES<StateType, ActionType>::Run(const Environment<StateType, ActionType>& env, Policy<StateType, ActionType>& policy, ActionValueStructure<StateType, ActionType>& valueStr)
{
	map<pair<StateType, ActionType>, int> count;
	map<pair<StateType, ActionType>, int> returnValues;

	int iter = 0;

	while (iter ++ < 10000)
	{
		returnValues.clear();
		

		pair<StateType, ActionType> stateAction = GenerateRandomStateAction(env);
		StateType state = stateAction.first;

		vector<tuple<StateType, ActionType, float>> episode = GenerateEpisode(env, policy, stateAction);
		float returnValue = 0;
		for (auto sar = episode.rbegin(); sar != episode.rend(); ++sar)
		{
			float reward = get<2>(*sar);
			returnValue = returnValue * discountFactor + reward;

			returnValues[make_pair(get<0>(*sar), get<1>(*sar))] = returnValue;
		}	

		vector<StateType> stateList;
		for (auto item : returnValues)
		{
			float oldVal = valueStr.GetStateActionValue(item.first);
			float newVal = ((oldVal * count[item.first]) + returnValues[item.first]) / (count[item.first] + 1);			

			valueStr.SetStateActionValue(item.first, newVal);
			count[item.first] += 1;

			stateList.push_back(item.first.first);			
		}

		ImporvePolicy(env, policy, valueStr, stateList);
	}
}
