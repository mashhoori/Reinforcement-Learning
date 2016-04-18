#include "stdafx.h"
#include "Policy.h"
#include "Move.h"
#include "GridCell.h"
#include "Grid.h"
#include "GridPolicy.h"


GridPolicy::GridPolicy(const Grid& grid)
	:grid(grid)
{
}

GridPolicy::~GridPolicy()
{
}

void GridPolicy::InitRandomPolicy()
{
	vector<GridCell> allStates = grid.GetAllStates();
	for (auto gc : allStates)
	{
		vector<Move> actions = grid.GetPossibleActions(gc);
		map<Move, float> actMap{};

		for (Move m : actions)
			actMap[m] = 1.0 / actions.size();

		statePolicyMap[gc] = actMap;
	}
}

void GridPolicy::SetActionDistribution(const GridCell & a, const map<Move, float>& actDist)
{
	statePolicyMap[a] = actDist;
}

map<Move, float> GridPolicy::GetActionDistribution(const GridCell &state) const 
{
	return statePolicyMap.at(state);
}

void GridPolicy::Print() const
{
	std::string dir[] = {"Up", "Down", "Left", "Right"};	

	vector<vector<int>> polMatrix(grid.GetNumRow(), vector<int>(grid.GetNumCol(), 0));
	for (auto cell : statePolicyMap)
		if (cell.second.size() > 0)
		{
			float max = -1000;
			int maxDirection = 0;
			for (auto move : cell.second)			
				if (move.second > max)
				{
					max = move.second;
					maxDirection = move.first.GetDirection();
				}			
			polMatrix[cell.first.GetRowIndex()][cell.first.GetColIndex()] = maxDirection;
		}

	for (size_t i = 0; i < grid.GetNumRow(); i++)
	{
		for (size_t j = 0; j < grid.GetNumCol(); j++)
		{
			if (grid.GetCellStatus(i, j) == GridCellStatus::Ordinary)			
				printf("%9s  ", dir[polMatrix[i][j]].c_str());			
			else if (grid.GetCellStatus(i, j) == GridCellStatus::Final)
				printf("%9s  ", "*Goal*");
			else
				printf("%9s  ", "|%|");
		}
		printf("\n");
	}
	
	printf("===============================\n\n\n");
}