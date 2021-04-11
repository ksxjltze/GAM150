/******************************************************************************/
/*!
\title		Captain Stealth
\file		Grid.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for Grid.cpp
			Contains the grid and node class for pathfinding
			and spatial partitiioning

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <unordered_set>
#include "Color.h"

namespace StarBangBang
{
	
	class BoxCollider;

	//basic node
	class Node
	{
			
		public:
			AEVec2 nodePos = AEVec2{0,0};
			int index_x = 0; //the x index of the node inside the grid array
			int index_y = 0; //the y index of the node inside the grid array
			
	};
	//A* star node
	class A_Node : public Node 
	{
	public:
		bool occupied = false;
		A_Node* parent = nullptr;	 //used to trace back node path
		int hcost = 0;	 //estimate cost from current to end node 
		int gcost = 0;	 //cost to start node to end node
		constexpr int GetfCost()  const { return hcost + gcost; }
		
	};
	//partition cell
	class Cell
	{
	public:
		//all the colliders in this cell
		std::unordered_set<BoxCollider*> cell_colliders;
		//index of the cell in the paritition grid
		int cellIndex;
	
	};
	//partitioning grid
	class PartitionGrid
	{
	private:
		float cellSize;
		int buckets;
		
		
	public:
		Cell* grid = nullptr;


		/*!*************************************************************************
		****
			\brief
				The parition grid constructor
			\param cellSize
				The size of a partition cells
			\param buckets
				The maximum number of elements in the partition grid
			\return
				void

		****************************************************************************
		***/
		PartitionGrid(float cellSize = 100.0f, int buckets = 1024);


		void AllocateGrid();
		
		/*!*************************************************************************
		****
			\brief
				A simple hash function that returns the index to the grid
				based on a position in the world
			\param pos
				The position in the world
			\return
				The hash index base on the given param pos

		****************************************************************************
		***/
		int GetHashCellIndex(AEVec2 pos);

		/*!*************************************************************************
		****
			\brief
				Clears all the bucket cell in the grid
			\return
				void

		****************************************************************************
		***/
		void ClearAllBucketCell();

		/*!*************************************************************************
		****
			\brief
				Clears a bucket cell's colliders in the grid
			\param index
				The index to the bucket cell
			\return
				void

		****************************************************************************
		***/
		void ClearABucketCell(int index);

		/*!*************************************************************************
		****
			\brief
				Get the partition cell node size
			\param none
				
			\return
				void

		****************************************************************************
		***/
		inline float GetCellSize() const { return cellSize; }


		/*!*************************************************************************
		****
			\brief
				Get partition grid bucket size (grid array size)
			\param none

			\return
				Partition grid bucket size (grid array size)

		****************************************************************************
		***/
		inline int GetBucketSize() const { return buckets; }


		/*!*************************************************************************
		****
			\brief
				The parition grid destructor
			\return
				void

		****************************************************************************
		***/
		~PartitionGrid();
		
	};

	class Grid
	{
	private:
		//the 2d grid
		A_Node** grid = nullptr;
		//size of each node
		float nodeSize = 0.0f;
		// grid offset from center (ie to place it in other position)
		AEVec2 offset = AEVec2();	
		// number of nodes in a row
		int size_x = 0; 
		// number of nodes in a column
		int size_y = 0;
		bool visible{ true };

		//Debug function
		/*!*************************************************************************
		****
			\brief
				Set the world grid nodes to all occupied  (debug purpose)
			\param none

			\return
				void

		****************************************************************************
		***/
		void SetAllOccupied();

	public:
		//the half size of the grid
		constexpr AEVec2 GetGridExtend() const
		{ 
			return AEVec2{nodeSize * size_x * 0.5f, nodeSize * size_y * 0.5f};
		}
		//how much the grid is offset from the origin
		//it is basically the new grid position
		constexpr AEVec2 GetGridOffset() const { return offset; }
		//how many nodes in x 
		constexpr int GetGridSizeX() const { return size_x; }
		//how many nodes in y
		constexpr int GetGridSizeY() const { return size_y; }
		//get node size
		constexpr float GetNodeSize() const { return nodeSize; }

		/*!*************************************************************************
		****
			\brief
				Toggle the visibility of the world grid
			\param none

			\return
				void

		****************************************************************************
		***/
		void ToggleVisible();

		/*!*************************************************************************
		****
			\brief
				Get a random non-occupied node
			\param none

			\return
				A random node copy object

		****************************************************************************
		***/
		A_Node GetRandomFreeNode();

		/*!*************************************************************************
		****
			\brief
				Sets a node base on param x & y occupied flag to param occupied
			\param x
				The second index of the grid (Width)
			\param y
				The first index of the grid (Height)
			\return
				void

		****************************************************************************
		***/
		void SetOccupied(int x, int y, bool occupied = true);


		/*!*************************************************************************
		****
			\brief
				Draws the world grid
			\param color
				The outline color used to draw the grid
			\return
				void

		****************************************************************************
		***/
		void DrawGrid(Color color = Green);

		/*!*************************************************************************
		****
			\brief
				Free the allocated memory for the A* grid
			\return
				void

		****************************************************************************
		***/
		void FreeGrid(void);

		/*!*************************************************************************
		****
			\brief
				The function that creates a new grid 
				automatically called by the constructor
			\param _nodeSize
				The size of each node
			\param sizeX
				The number of nodes along x-axis
			\param sizeY
				The number of nodes along y-axis
			\param _offset
				The position to place the grid
			\return
				void

		****************************************************************************
		***/
		void CreateGrid(float _nodeSize, int sizeX, int sizeY, AEVec2 _offset);
	
		/*!*************************************************************************
		****
			\brief
				Get the 4 surrounding neighbours (up,down,left and right)
				of the param node
			\param node
				The center node
			\return
				A vector container of 4 surrounding neighbours

		****************************************************************************
		***/
		std::vector<A_Node*> Get8_NodeNeighbours(const A_Node* node);


		/*!*************************************************************************
		****
			\brief
				Get the 8 surrounding neighbours (up,down,left,right and the diagonals)
				of the param node
			\param node
				The center node
			\return
				A vector container of 8 surrounding neighbours

		****************************************************************************
		***/
		std::vector<A_Node*> Get4_NodeNeighbours(const A_Node* node);

		/*!*************************************************************************
		****
			\brief
				Gets a node object calculated base on the param pos
				The relevant node object
			\param pos
				The position of the world
			\return
				The node* calculated base on world position

		****************************************************************************
		***/
		A_Node* GetNodeFromPosition(AEVec2 pos) ;
	

		/*!*************************************************************************
		****
			\brief
				Gets a node object from the grid using param x & y
			\param x
				The second index of the grid (Width)
			\param y
				The first index of the grid (Height)
			\return
				The node* of grid[y]+x

		****************************************************************************
		***/
		A_Node* GetNode(int x, int y) const;


		Grid() = default;
		
		Grid(float _nodeSize, int sizeX, int sizeY, AEVec2 _offset = AEVec2{0.0f,0.0f});

		
	
	};
}