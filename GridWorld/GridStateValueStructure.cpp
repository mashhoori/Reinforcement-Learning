#include "stdafx.h"
#include "GridCell.h"
#include "StateValueStructure.h"
#include "Grid.h"
#include "GridStateValueStructure.h"



GridStateValueStructure::GridStateValueStructure(const Grid & grid)
	:grid{ grid }, valueMap{}
{
}

GridStateValueStructure::~GridStateValueStructure()
{
}

float GridStateValueStructure::GetStateValue(const GridCell & state) const
{	
	return valueMap.at(state);
}

void GridStateValueStructure::SetStateValue(const GridCell & state, float value)
{
	valueMap[state] = value;	
}

void GridStateValueStructure::InitValues()
{
	for (auto gc : grid.GetAllStates())
		valueMap[gc] = 0;
}

void GridStateValueStructure::Print() const
{	
	vector<vector<float>> valMatrix(grid.GetNumRow(), vector<float>(grid.GetNumCol(), 0));
	for (auto cell : valueMap)
		valMatrix[cell.first.GetRowIndex()][cell.first.GetColIndex()] = cell.second;

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
