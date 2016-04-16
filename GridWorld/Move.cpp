#include "stdafx.h"
#include "Action.h"
#include "Move.h"



Move::Move(MoveDirection dir)
	:direction{ dir }
{}

MoveDirection Move::GetDirection() const
{
	return direction;
}

int Move::GetHashCode() const
{
	return direction;
}