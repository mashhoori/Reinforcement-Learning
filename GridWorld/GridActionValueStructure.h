#pragma once
#include "ActionValueStructure.h"
class GridActionValueStructure : public ActionValueStructure<GridCell, Move>
{
private:
	Grid grid;
	map<pair<GridCell, Move>, float> valueMap;

public:
	GridActionValueStructure(const Grid &grid);
	~GridActionValueStructure();

	float GetStateActionValue(const pair<GridCell, Move>& stateAction) const;
	void SetStateActionValue(const pair<GridCell, Move>& stateAction, float value);

	void InitValues();
	void Print() const;
};
