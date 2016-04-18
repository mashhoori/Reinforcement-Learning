#pragma once
class GridStateValueStructure : public StateValueStructure<GridCell>
{
private:
	Grid grid;
	map<GridCell, float> valueMap;

public:
	GridStateValueStructure(const Grid &grid);
	~GridStateValueStructure();

	float GetStateValue(const GridCell& state) const;
	void SetStateValue(const GridCell& state, float value);
	
	void InitValues();
	void Print() const;
};

