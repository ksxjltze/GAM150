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
		PartitionGrid(float cellSize = 100.0f, int buckets = 1024);
		//create grid object
		int GetHashCellIndex(AEVec2 pos);
		void ClearAllBucketCell();
		void ClearABucketCell(int index);

		inline float GetCellSize() const { return cellSize; }
		//Cell& GetCell(int index);
		inline int GetBucketSize() const { return buckets; }
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
		//set all nodes to occupied
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

		void ToggleVisible();

		A_Node GetRandomFreeNode();
		void SetOccupied(int x, int y, bool occupied = true);
		void DrawGrid(Color color = Green);
		void FreeGrid(void);
		//create grid object
		void CreateGrid(float _nodeSize, int sizeX, int sizeY, AEVec2 _offset);
		
		std::vector<A_Node*> Get8_NodeNeighbours(const A_Node* node);
		std::vector<A_Node*> Get4_NodeNeighbours(const A_Node* node);


		A_Node* GetNodeFromPosition(AEVec2 pos) ;
		float GetNodeSize() { return nodeSize; }
		A_Node* GetNode(int x, int y) const;
		Grid() = default;
		
		Grid(float _nodeSize, int sizeX, int sizeY, AEVec2 _offset = AEVec2{0.0f,0.0f});

		
	
	};
}