#pragma once
class Global
{
public:

	static default_random_engine generator;
	static uniform_real_distribution<float> realDist;

	template<class T>
	static T SelectFromDistribution(map<T, float> dist);

};


template<class T>
T Global::SelectFromDistribution(map<T, float> dist)
{
	float rand = realDist(generator);

	float sum = 0;
	for (auto item : dist)
	{
		sum += item.second;
		if (sum >= rand)
			return item.first;
	}
}
