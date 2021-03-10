#include "Grid.h"
#include <cmath>
#include <iostream>
#include "BasicMeshShape.h"
#include "Collider.h"

using namespace StarBangBang;



#pragma region Partition Grid

	PartitionGrid::PartitionGrid(float cellSize, int buckets) 
	: cellSize{ cellSize }, buckets{ buckets },
	grid{ new Cell[buckets]} {}

	PartitionGrid::~PartitionGrid()
	{
		delete[] grid;
	}

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

		//PRINT("hash:%d\n", hashIndex);
		//PRINT("%d------------------\n", counter);

		return hashIndex;
	}

	

#pragma endregion


	int A_Node::GetHeapIndex() const
	{
		return heapIndex;
	}
	void A_Node::SetHeapIndex(int index)
	{
		heapIndex = index;
	}



#pragma region A* grid
	
	//Change to destructor some time
	void Grid::FreeGrid()
	{
		for (int i = 0; i < size_y; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
	}

	Grid::~Grid()
	{
		Grid::FreeGrid();
	}


	
	Grid::Grid(float _nodeSize, int sizeX, int sizeY, AEVec2 _offset)
	{
		this->nodeSize = _nodeSize;
		this->offset = _offset;
		CreateGrid(_nodeSize, sizeX , sizeY, AEVec2{ 0,0 });
	}

	void Grid::CheckOccupiedGrid()
	{

	}

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
		}
		std::cout << "X:" << size_x << std::endl;
		std::cout << "Y:" << size_y << std::endl;
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
				//check if occupied

			}

		}
	}
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

	void Grid::DrawGrid(Color color)
	{

		for (size_t y = 0; y < size_y; y++)
		{
			for (size_t x = 0; x < size_x; x++)
			{
				if (grid[y][x].occupied)
				{
					StarBangBang::DrawBox(AEVec2{ nodeSize,nodeSize }, grid[y][x].nodePos, Red());
				}
				else
					StarBangBang::DrawBoxWired(AEVec2{ nodeSize,nodeSize }, grid[y][x].nodePos, color);
			}
		}
	}

#pragma endregion

