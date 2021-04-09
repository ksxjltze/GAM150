/******************************************************************************/
/*!
\file		PathFinder.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for PathFinder.h
			Contains functions for pathfinding and grid object

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/



#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Grid.h"

namespace StarBangBang
{
	namespace PathFinder
	{
		
		/*!*************************************************************************
		****
			\brief
				Initialise the pathfinder grid to be used for the game world
			\param rows
				The number of rows of the matrix
			\param cols
				The number of columns of the matrix
			\return
				void
		
		****************************************************************************
		***/
		void PathFinderInit();

		/*!*************************************************************************
		****
			\brief
				Display the world grid
			\param visible
				Whether the grid should be drawn
			\return
				void

		****************************************************************************
		***/
		void ShowGrid(bool visible = true);



		/*!*************************************************************************
		****
			\brief
				Free the world grid
			\param visible
				Whether the grid should be drawn
			\return
				void
		****************************************************************************
		***/
		void Free();



		/*!*************************************************************************
		****
			\brief
				Search for a path given a start and end position
			\param start
				The starting positions
			\param target
				The target position to reach
			\param pathing
				
			\return
				void
		****************************************************************************
		***/
		void SearchForPath(AEVec2 start, AEVec2 target, std::vector<A_Node*>& pathing);
	
		
		void GridDraw();
		Grid& GetWorldGrid();

	}
	
}


