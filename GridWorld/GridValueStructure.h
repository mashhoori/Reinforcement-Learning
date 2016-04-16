#pragma once
class GridValueStructure : public ValueStructure<GridCell>
{
private:
	Grid grid;
	map<GridCell, float> valueMap;

public:
	GridValueStructure(const Grid &grid);
	~GridValueStructure();

	float GetStateValue(const GridCell& state) const;
	void SetStateValue(const GridCell& state, float value);
	
	void InitValues();
	void Print() const;
};

