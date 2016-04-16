#include "stdafx.h"
#include "State.h"
#include "GridCell.h"


int GridCell::gridColCount = 0;


GridCell::GridCell(int rIndex, int cIndex)
	:rowIndex{ rIndex }, colIndex{ cIndex }
{}

int GridCell::GetHashCode() const
{
	return rowIndex * gridColCount + colIndex;
}

int GridCell::GetRowIndex() const 
{ return rowIndex; }

int GridCell::GetColIndex() const 
{ return colIndex; }