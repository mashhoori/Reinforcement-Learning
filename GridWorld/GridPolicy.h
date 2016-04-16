#pragma once
class GridPolicy : public Policy<GridCell, Move>
{
	private:
		Grid grid;
		map<GridCell, map<Move, float>> statePolicyMap;

	public:
		GridPolicy(const Grid& grid);		
		~GridPolicy();
		
		void InitRandomPolicy();
		void SetActionDistribution(const GridCell& a, const map<Move, float>& actDist);
		map<Move, float> GetActionDistribution(const GridCell& state) const;

		void Print() const;
};

