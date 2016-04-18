#include "stdafx.h"
#include "GridCell.h"
#include "Move.h"
#include "Grid.h"
#include "ActionValueStructure.h"
#include "GridActionValueStructure.h"

GridActionValueStructure::GridActionValueStructure(const Grid & grid)
	:grid{ grid }, valueMap{}
{
}

GridActionValueStructure::~GridActionValueStructure()
{
}

float GridActionValueStructure::GetStateActionValue(const pair<GridCell, Move>& stateAction) const
{
	return valueMap.at(stateAction);
}

void GridActionValueStructure::SetStateActionValue(const pair<GridCell, Move>& stateAction, float value)
{
	valueMap[stateAction] = value;
}

void GridActionValueStructure::InitValues()
{
	for (auto gc : grid.GetAllStates())
		for(auto mv: grid.GetPossibleActions(gc))
			valueMap[ make_pair(gc, mv)] = 0;
}

void GridActionValueStructure::Print() const
{
	vector<vector<float>> valMatrix(grid.GetNumRow(), vector<float>(grid.GetNumCol(), -1000));
	
	for (auto& item : valueMap)
	{
		const GridCell& cell = item.first.first;
		const Move& move = item.first.second;
		if (item.second > valMatrix[cell.GetRowIndex()][cell.GetColIndex()])
			valMatrix[cell.GetRowIndex()][cell.GetColIndex()] = item.second;
	}

	for (size_t i = 0; i < grid.GetNumRow(); i++)
	{
		for (size_t j = 0; j < grid.GetNumCol(); j++)
		{
			if (grid.GetCellStatus(i, j) == GridCellStatus::Ordinary)
				printf("%+9.2f  ", valMatrix[i][j]);

			else if (grid.GetCellStatus(i, j) == GridCellStatus::Final)
				printf("%9s  ", "*Goal*");
			else
				printf("%+9s  ", "|%|");
		}
		printf("\n");
	}

	printf("===============================\n\n\n");
}
