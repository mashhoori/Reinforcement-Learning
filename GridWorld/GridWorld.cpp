// GridWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Policy.h"
#include "State.h"
#include "Action.h"
#include "Environment.h"
#include "ValueStructure.h"
#include "Grid.h"
#include "GridPolicy.h"
#include "GridValueStructure.h"
#include "PolicyIteration.h"
#include "ValueIteration.h"



int main()
{
	int gDim = 7;
	Grid g(gDim, gDim);
	g.SetReward(3, 1, 1000);
	g.SetCellStatus(3, 1, GridCellStatus::Final);
	g.SetReward(6, 3, -250);

	g.SetCellStatus(1, 2, GridCellStatus::Wall);
	g.SetCellStatus(2, 2, GridCellStatus::Wall);	
	g.SetCellStatus(4, 2, GridCellStatus::Wall);
	g.SetCellStatus(5, 2, GridCellStatus::Wall);	

	g.SetCellStatus(0, 5, GridCellStatus::Wall);	
	g.SetCellStatus(2, 5, GridCellStatus::Wall);
	g.SetCellStatus(3, 5, GridCellStatus::Wall);
	g.SetCellStatus(4, 5, GridCellStatus::Wall);	

	g.CreateStates();	

	GridPolicy gPolicy{g};
	gPolicy.InitRandomPolicy();	

	GridValueStructure gValStr{g};
	gValStr.InitValues();

	
	PolicyIteration<GridCell, Move> policyIteration{ 0.001f, 0.8f };
	policyIteration.Run(g, gPolicy, gValStr);

	// Uncomment  for Value iteration
	// ValueIteration<GridCell, Move> valueIteration{ 0.001f, 0.8f };
	// valueIteration.Run(g, gPolicy, gValStr);


	gValStr.Print();
	gPolicy.Print();


	getchar();
    return 0;
}

