#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <unordered_set>
#include "Heap.h"

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
	class A_Node : public Node , public Interface
	{
	public:
		bool occupied = false;
		A_Node* parent = nullptr;	 //used to trace back node path
		int hcost = 0;	 //cost from current to end node
		int gcost = 0;	 //cost to start node to end node
		constexpr int GetfCost()  const { return hcost + gcost; }

		virtual int GetHeapIndex() const;
		virtual void SetHeapIndex(int);
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
	
	class PartitionGrid
	{
	private:
		float cellSize;
		int buckets;
		Cell* grid = nullptr;
		
	public:
		PartitionGrid(float cellSize = 100.0f, int buckets = 1024);
		//create grid object
		int GetHashCellIndex(AEVec2 pos);
		inline float GetCellSize() const { return cellSize; }
		Cell& GetCell(int index);
		~PartitionGrid();
		
	};

	class Grid
	{
	private:
		A_Node** grid = nullptr;
		float nodeSize = 0.0f;
		AEVec2 offset = AEVec2();	// grid offset from center (ie to place it in other position)
		int size_x = 0; // number of nodes in a row
		int size_y = 0; // number of nodes in a column
		void CheckOccupiedGrid();
	public:
		constexpr AEVec2 GetGridExtend() const
		{ 
			return AEVec2{nodeSize * size_x * 0.5f, nodeSize * size_y * 0.5f};
		}
		constexpr AEVec2 GetGridOffset() const { return offset; }
		//how many nodes in x 
		constexpr int GetGridSizeX() const { return size_x; }
		//how many nodes in y
		constexpr int GetGridSizeY() const { return size_y; }
		constexpr float GetNodeSize() const { return nodeSize; }


		void DrawGrid();
		void FreeGrid(void);
		//create grid object
		void CreateGrid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });
		
		std::vector<A_Node*> GetNodeNeighbours(const A_Node* node);

		A_Node* GetNodeFromPosition(AEVec2 pos) ;
		float GetNodeSize() { return nodeSize; }
		A_Node* GetNode(int x, int y) const;
		Grid() = default;
		
		Grid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });

		

		~Grid();
	
	};
}