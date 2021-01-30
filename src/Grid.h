#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
namespace StarBangBang
{
	class Node
	{
		public:
			AEVec2 nodePos = AEVec2{0,0};
			bool occupied = false;
			Node() {};
			Node(AEVec2 _nodePos,bool _occupied = false)
			{
				nodePos = _nodePos;
				occupied = _occupied;
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

		Node* GetNodeFromPosition(AEVec2 pos);
		
		//Grid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset = AEVec2{ 0,0 });

	
	};
}