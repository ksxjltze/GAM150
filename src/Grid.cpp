/******************************************************************************/
/*!
\title		Captain Stealth
\file		Grid.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for Grid.h
			Contains the grid and node class for pathfinding
			and spatial partitiioning

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/



#include "Grid.h"
#include <cmath>
#include <iostream>
#include "BasicMeshShape.h"
#include "Collider.h"
#include "GraphicsManager.h"

using namespace StarBangBang;



#pragma region Partition Grid
	
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
	PartitionGrid::PartitionGrid(float cellSize, int buckets) 
	: cellSize{ cellSize }, buckets{ buckets },
	grid{ new Cell[buckets]} {}


	/*!*************************************************************************
	****
		\brief
			The parition grid destructor
		\return
			void

	****************************************************************************
	***/
	PartitionGrid::~PartitionGrid()
	{
		delete[] grid;
	}

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
	void PartitionGrid::ClearABucketCell(int index)
	{
		grid[index].cell_colliders.clear();
	}

	/*!*************************************************************************
	****
		\brief
			Clears all the bucket cell in the grid
		\return
			void

	****************************************************************************
	***/
	void PartitionGrid::ClearAllBucketCell()
	{
		for (int i = 0; i < buckets; i++)
		{
			grid[i].cell_colliders.clear();
		}
	}

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
	int PartitionGrid::GetHashCellIndex(AEVec2 pos)
	{
		//static int counter = 0;
		int x = static_cast<int>((pos.x / cellSize));
		int y = static_cast<int>((pos.y / cellSize));

		//++counter;
		const int multi_x = 0x8da6b343;
		const int multi_y = 0xd8163841;
		int hashIndex = (x * multi_x + y * multi_y) % buckets;


		if (hashIndex < 0)
			hashIndex += buckets;
		//PRINT("--------------------\n");
		//PRINT("hash:%d\n\n", hashIndex);
		//PRINT("%d------------------\n", counter);

		return hashIndex;
	}

	

#pragma endregion



#pragma region A* grid
	
	/*!*************************************************************************
	****
		\brief
			Frees the A* grid
		\return
			void

	****************************************************************************
	***/
	void Grid::FreeGrid()
	{
		if (!grid)
			return;

		for (int i = 0; i < size_y; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
		
		grid = nullptr;
	}
	
	/*!*************************************************************************
	****
		\brief
			Grid object constructor
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
	Grid::Grid(float _nodeSize, int sizeX, int sizeY, AEVec2 _offset)
	{
		this->nodeSize = _nodeSize;
		this->offset = _offset;
		CreateGrid(_nodeSize, sizeX , sizeY, AEVec2{ 0,0 });
	}


	/*!*************************************************************************
	****
		\brief
			The function that creates a new grid
			called by the constructor
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
	void Grid::CreateGrid(float _nodeSize, int sizeX , int sizeY, AEVec2 _offset)
	{

		nodeSize = _nodeSize;
		offset = _offset;

		if (sizeX <= 0 || sizeY <= 0)
			std::cout << "Error : Grid size cannot be 0 \n";
		//size_x = static_cast<int>(ceil(gridSize.x / nodeSize));
		//size_y = static_cast<int>(ceil(gridSize.y / nodeSize));
		size_x = sizeX;
		size_y = sizeY;
		try
		{
			grid = new A_Node * [size_y];

			for (int i = 0; i < size_y; i++)
			{
				grid[i] = new A_Node[size_x];

			}
		}
		catch (const std::bad_alloc& exp)
		{
			std::cout << "Allocation failed for grid object:" << exp.what() << std::endl;
			
			GRAPHICS::ToggleFullscreen();
			MessageBox(AESysGetWindowHandle(), "Fail to allocate memory on your machine! Please close some program!", "Error!", MB_OK);
			//quit
		}
	
	
	/*	std::cout << "X:" << size_x << std::endl;
		std::cout << "Y:" << size_y << std::endl;*/
		AEVec2 extend = GetGridExtend();
		float half_node = nodeSize * 0.5f;

		AEVec2 btmNode = AEVec2{ offset.x - extend.x + half_node  , offset.y - extend.y - half_node };
		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				//calculate position
				grid[y][x].index_x = x;
				grid[y][x].index_y = y;
				grid[y][x].nodePos = AEVec2{ btmNode.x + x * nodeSize , btmNode.y + nodeSize * y };
				
			}

		}
	}


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
	std::vector<A_Node*> Grid::Get4_NodeNeighbours(const A_Node* node)
	{
		std::vector<A_Node*> n;
		n.reserve(4);
		int top_x = node->index_x ;
		int top_y = node->index_y + 1;

		int right_x = node->index_x + 1;
		int right_y = node->index_y ;

		int left_x = node->index_x - 1;
		int left_y = node->index_y ;

		int btm_x = node->index_x;
		int btm_y = node->index_y -1;
	
		if (top_x >= 0 && top_x < size_x && top_y >= 0 && top_y < size_y)
		{
			n.push_back(grid[top_y] + top_x);
		}
		if (right_x >= 0 && right_x < size_x && right_y >= 0 && right_y < size_y)
		{
			n.push_back(grid[right_y] + right_x);
		}
		if (left_x >= 0 && left_x < size_x && left_y >= 0 && left_y < size_y)
		{
			n.push_back(grid[left_y] + left_x);
		}
		if (btm_x >= 0 && btm_x < size_x && btm_y >= 0 && btm_y < size_y)
		{
			n.push_back(grid[btm_y] + btm_x);
		}
		
		
		return n;
	}

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
	std::vector<A_Node*> Grid::Get8_NodeNeighbours(const A_Node* node)
	{
		std::vector<A_Node*> n;
		n.reserve(8);
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				//it is the node we passed in so skip it
				if (x == 0 && y == 0)
					continue;
				int index_x = node->index_x + x;
				int index_y = node->index_y + y;

				if (index_x >= 0 && index_x < size_x && index_y >= 0 && index_y < size_y)
					n.push_back(grid[index_y] + index_x);
			}
		}

		return n;
	}


	/*!*************************************************************************
	****
		\brief
			Gets a node object calculated base on the param pos
			The relevant node object 
		\param pos
			The position of the world
		\return
			A 

	****************************************************************************
	***/
	A_Node* Grid::GetNodeFromPosition(AEVec2 pos)
	{
		AEVec2 result;
		AEVec2Sub(&result, &pos, &offset);

		AEVec2 gridExtend = GetGridExtend();
		result.x += gridExtend.x;
		result.y += gridExtend.y;
		float half_node = nodeSize * 0.5f;

		int  x = static_cast<int>(round((result.x - half_node)/ nodeSize));
		int  y = static_cast<int>(round((result.y + half_node) / nodeSize));

		if (x >= 0 && x < size_x && y >= 0 && y < size_y)
		{
			return grid[y] + x;
		}
		else
			return nullptr;
	}

	A_Node* StarBangBang::Grid::GetNode(int x, int y) const
	{
		if (x >= 0 && x < size_x && y >= 0 && y < size_y)
			return grid[y] + x;
		else
			return nullptr;
	}

	void StarBangBang::Grid::SetAllOccupied()
	{
		for (size_t y = 0; y < size_y; y++)
		{
			for (size_t x = 0; x < size_x; x++)
			{
				grid[y][x].occupied = true;
			}
		}
	}

	void StarBangBang::Grid::ToggleVisible()
	{
		visible = !visible;
	}

	A_Node StarBangBang::Grid::GetRandomFreeNode()
	{
		int rand_x = static_cast<int>(AERandFloat() * size_x), rand_y = static_cast<int>(AERandFloat()* size_y);
		A_Node n = grid[rand_y][rand_x];

		while (n.occupied)
		{
			rand_x = static_cast<int>(AERandFloat() * size_x), rand_y = static_cast<int>(AERandFloat() * size_y);
			n = grid[rand_y][rand_x];
		}

		return n;
	}

	void StarBangBang::Grid::SetOccupied(int x, int y, bool occupied)
	{
		if (x < size_x && y < size_y)
			grid[y][x].occupied = occupied;
	}

	void Grid::DrawGrid(Color color)
	{
		if (!visible)
			return;

		for (size_t y = 0; y < size_y; y++)
		{
			for (size_t x = 0; x < size_x; x++)
			{
				if (grid[y][x].occupied)
				{
					//Disable for now
					/*StarBangBang::DrawBox(AEVec2{ nodeSize,nodeSize }, grid[y][x].nodePos, Red);*/
				}
				else
					StarBangBang::DrawBoxWired(AEVec2{ nodeSize,nodeSize }, grid[y][x].nodePos, color);
			}
		}
	}

#pragma endregion

