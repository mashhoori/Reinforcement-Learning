#pragma once
#include "State.h"

class GridCell : public State
{
private:
	int rowIndex;
	int colIndex;
	

public:
	static int gridColCount;

	GridCell(int rIndex, int cIndex);

	int GetHashCode() const;
	int GetRowIndex() const;
	int GetColIndex() const;
};

