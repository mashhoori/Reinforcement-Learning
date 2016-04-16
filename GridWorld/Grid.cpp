#include "stdafx.h"
#include "Environment.h"
#include "GridCell.h"
#include "Move.h"
#include "GridCell.h"
#include "Grid.h"


Grid::Grid(int nRow, int nCol)
:numRow{ nRow }, numCol{ nCol }, rewardMat{ nRow, vector<float>(nCol, -1) }, cellStatusMat{ nRow, vector<GridCellStatus>(nCol, GridCellStatus::Ordinary) }
{
	GridCell::gridColCount = numCol;	
}

Grid::~Grid()
{
}

void Grid::CreateStates()
{
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)		
			if (cellStatusMat[i][j] != GridCellStatus::Wall)
			{
				GridCell gc(i, j);
				states.push_back(gc);
			}		
}

float Grid::GetReward(const GridCell& preState, const Move& a, const GridCell & newState) const
{
	return rewardMat[newState.GetRowIndex()][newState.GetColIndex()];
}

map<GridCell, float> Grid::GetNextStateDistribution(const GridCell& state, const Move& a) const
{
	int row = state.GetRowIndex();
	int col = state.GetColIndex();

	map<GridCell, float> nextSD{};

	switch (a.GetDirection())
	{
		case Up:
			if (row != 0 && cellStatusMat[row - 1][col] != GridCellStatus::Wall)
				nextSD[GridCell(row - 1, col)] = 1;			
			else
				nextSD[GridCell(row, col)] = 1;
			break;

		case Down:
			if (row != numRow - 1 && cellStatusMat[row + 1][col] != GridCellStatus::Wall)
				nextSD[GridCell(row + 1, col)] = 1;
			else
				nextSD[GridCell(row, col)] = 1;
			break;

		case Right:
			if (col != numCol - 1 && cellStatusMat[row][col+1] != GridCellStatus::Wall)
				nextSD[GridCell(row, col+1)] = 1;
			else
				nextSD[GridCell(row, col)] = 1;
			break;

		case Left:
			if (col != 0 && cellStatusMat[row][col-1] != GridCellStatus::Wall)
				nextSD[GridCell(row, col - 1)] = 1;
			else
				nextSD[GridCell(row, col)] = 1;
			break;

		default:
			break;
	}

	return nextSD;
}

vector<GridCell> Grid::GetAllStates() const
{
	return states;
}

vector<Move> Grid::GetPossibleActions(const GridCell& state) const
{
	vector<Move> list;	

	Move up(Up);
	Move down(Down);
	Move left(Left);
	Move right(Right);
	

	if (cellStatusMat[state.GetRowIndex()][state.GetColIndex()] != GridCellStatus::Final)
	{
		list.push_back(up);
		list.push_back(down);
		list.push_back(left);
		list.push_back(right);
	}
	return list;
}

void Grid::SetReward(int i, int j, float reward)
{	
	rewardMat[i][j] = reward;
}

void Grid::SetCellStatus(int i, int j, GridCellStatus status)
{
	cellStatusMat[i][j] = status;
}

GridCellStatus Grid::GetCellStatus(int i, int j) const
{
	return cellStatusMat[i][j];
}

int Grid::GetNumRow() const
{
	return numRow;
}

int Grid::GetNumCol() const
{
	return numCol;
}
