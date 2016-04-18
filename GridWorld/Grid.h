#pragma once
#include "Move.h"
#include "GridCell.h"
#include "Environment.h"

enum GridCellStatus{Ordinary, Wall, Final};


class Grid : public Environment<GridCell, Move>
{

private:
	int numRow;
	int numCol;

	vector<GridCell> states;
	vector<vector<float>> rewardMat;
	vector<vector<GridCellStatus>> cellStatusMat;

public:
	Grid(int nRow, int nCol);	

	~Grid();

	void CreateStates();

	float GetReward(const GridCell& preState, const Move& a, const GridCell& newState) const;
	map<GridCell, float> GetNextStateDistribution(const GridCell& state, const Move& a) const;
	vector<GridCell> GetAllStates() const;
	vector<Move> GetPossibleActions(const GridCell& state) const;	
	bool IsStateFinal(const GridCell& state) const;

	void SetReward(int i, int j, float reward);
	void SetCellStatus(int i, int j, GridCellStatus status);
	GridCellStatus GetCellStatus(int i, int j) const;

	int GetNumRow() const;
	int GetNumCol() const;
};

