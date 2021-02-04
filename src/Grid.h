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
			int hcost = 0;
			int gcost = 0;
			int index_x = 0; //the x index of the node inside the grid array
			int index_y = 0; //the y index of the node inside the grid array
			constexpr int GetfCost(){return hcost + gcost;}

			Node() {}
			Node(AEVec2 _nodePos,int _index_x ,int _index_y,bool _occupied = false)
			{
				nodePos = _nodePos;
				occupied = _occupied;
				index_x = _index_x;
				index_y = _index_y;
			}
		
	};
	
	class Grid
	{
	private:
		Node** grid = nullptr;
		float nodeSize;
		AEVec2 offset;	// grid offset from center (ie to place it in other position)
		int size_x = 0; // number of nodes in a row
		int size_y = 0; // number of nodes in a column
	public:
		constexpr AEVec2 GetGridExtend()
		{ 
			return AEVec2{nodeSize * size_x * 0.5f, nodeSize * size_y * 0.5f};
		}
		constexpr AEVec2 GetGridOffset() { return offset; };

		void DrawGrid(void);

		//create grid object
		void CreateGrid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });
		void CreateGrid(float _nodeSize, int width, int height);

		std::vector<Node*> GetNodeNeighbours(Node* node);

		Node* GetNodeFromPosition(AEVec2 pos);
		float GetNodeSize() { return nodeSize; }
		
		Grid();

		Grid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });

	
	};
}