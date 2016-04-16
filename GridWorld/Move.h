#pragma once
#include "Action.h"

enum MoveDirection {Up, Down, Left, Right};

class Move : public Action
{
private:
	MoveDirection direction;

public:
	Move(MoveDirection dir);
	MoveDirection GetDirection() const;	
	int GetHashCode() const;
};

