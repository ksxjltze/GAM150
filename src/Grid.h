#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <vector>
namespace StarBangBang
{
	class Node
	{
			
		public:
			AEVec2 nodePos = AEVec2{0,0};
			bool occupied = false;	
			int index_x = 0; //the x index of the node inside the grid array
			int index_y = 0; //the y index of the node inside the grid array
			Node* parent = nullptr;	 //used to trace back node path
			int hcost = 0;	 //cost from current to end node
			int gcost = 0;	 //cost to start node to end node
			constexpr int GetfCost()  const  {return hcost + gcost;}

			
	};
	
	class Grid
	{
	private:
		Node** grid = nullptr;
		float nodeSize;
		AEVec2 offset;	// grid offset from center (ie to place it in other position)
		int size_x = 0; // number of nodes in a row
		int size_y = 0; // number of nodes in a column
		void CheckOccupiedGrid();
	public:
		constexpr AEVec2 GetGridExtend() const
		{ 
			return AEVec2{nodeSize * size_x * 0.5f, nodeSize * size_y * 0.5f};
		}
		constexpr AEVec2 GetGridOffset() const { return offset; }

		constexpr int GetGridSizeX() const { return size_x; }
		constexpr int GetGridSizeY() const { return size_y; }

		void DrawGrid();
		void FreeGrid(void);
		//create grid object
		void CreateGrid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });
		void CreateGrid(float _nodeSize, int width, int height);

		std::vector<Node*> GetNodeNeighbours(const Node* node);

		Node* GetNodeFromPosition(AEVec2 pos) ;
		float GetNodeSize() { return nodeSize; }
		Node* GetNode(int x, int y) const;
		
		Grid();
		
		Grid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });

		

		~Grid();
	
	};
}