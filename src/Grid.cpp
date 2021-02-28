#include "Grid.h"
#include <cmath>
#include <iostream>
#include "BasicMeshShape.h"
#include "Collider.h"

using namespace StarBangBang;



	#pragma region Partition Grid

	PartitionGrid::PartitionGrid()
	{
		PRINT("HELP\n");
		nodeSize = 60;
		offset = AEVec2{ 10,10 };
		CreateGrid(nodeSize, AEVec2{ 1000.0f, 1000.0f }, offset);
		
	}
	//Change to destructor some time
	void PartitionGrid::FreeGrid()
	{
		for (int i = 0; i < size_y; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
	}
	PartitionGrid::~PartitionGrid()
	{
		PartitionGrid::FreeGrid();
	}

	PartitionGrid::PartitionGrid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset)
	{
		this->nodeSize = _nodeSize;
		this->offset = _offset;
		CreateGrid(_nodeSize, gridSize, AEVec2{ 0,0 });
	}

	void PartitionGrid::CreateGrid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset)
	{

		nodeSize = _nodeSize;
		offset = _offset;

		if (gridSize.x == 0 || gridSize.y == 0)
			std::cout << "Error : Grid size cannot be 0 \n";
		size_x = static_cast<int>(ceil(gridSize.x / nodeSize));
		size_y = static_cast<int>(ceil(gridSize.y / nodeSize));

		try
		{
			grid = new Cell * [size_y];

			for (int i = 0; i < size_y; i++)
			{
				grid[i] = new Cell[size_x];

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

		//top right node
		AEVec2 startNode = AEVec2{ offset.x - extend.x - half_node  , offset.y + extend.y - half_node };
		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				//calculate position
				grid[y][x].index_x = x;
				grid[y][x].index_y = y;
				grid[y][x].nodePos = AEVec2{ startNode.x + x * nodeSize , startNode.y + nodeSize * y };

			}

		}

	}

	void PartitionGrid::CreateGrid(float _nodeSize, int width, int height)
	{
		AEVec2 size = { width * _nodeSize, height * _nodeSize };
		CreateGrid(_nodeSize, size, { _nodeSize / 2, _nodeSize / 2 - size.y });
	}

	std::vector<Cell*> PartitionGrid::GetNodeNeighbours(const Cell* node)
	{
		std::vector<Cell*> n;
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
	Cell* PartitionGrid::GetNodeFromPosition(AEVec2 pos)
	{
		AEVec2 result;
		AEVec2Sub(&result, &pos, &offset);

		AEVec2 gridExtend = GetGridExtend();
		result.x += gridExtend.x;
		result.y -= gridExtend.y;

		float half_size = nodeSize * 0.5f;
		int  x = static_cast<int>(ceil((result.x - half_size) / nodeSize));
		int  y = static_cast<int>(ceil((result.y + half_size) / nodeSize));

		if (x >= 0 && x < size_x && y >= 0 && y < size_y)
		{
			return grid[y] + x;
		}
		else
			return nullptr;
	}

	Cell* PartitionGrid::GetNode(int x, int y) const
	{
		if (x >= 0 && x < size_x && y >= 0 && y < size_y)
			return grid[y] + x;
		else
			return nullptr;
	}

	void PartitionGrid::DrawGrid()
	{

		for (size_t y = 0; y < size_y; y++)
		{
			for (size_t x = 0; x < size_x; x++)
			{
				StarBangBang::DrawBoxWired(AEVec2{ nodeSize,nodeSize }, grid[y][x].nodePos, White());
			}
		}
	}

#pragma endregion




	#pragma region A* grid
	Grid::Grid()
	{
		nodeSize = 30.0f;
		offset = AEVec2{ 0,0 };
		CreateGrid(nodeSize, AEVec2{ 1000.0f, 1000.0f });
	}
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



	Grid::Grid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset)
	{
		std::cout << "Init \n";
		this->nodeSize = _nodeSize;
		this->offset = _offset;
		CreateGrid(_nodeSize, gridSize, AEVec2{ 0,0 });
	}

	void Grid::CheckOccupiedGrid()
	{

	}

	void Grid::CreateGrid(float _nodeSize, AEVec2 gridSize, AEVec2 _offset)
	{

		nodeSize = _nodeSize;
		offset = _offset;

		if (gridSize.x == 0 || gridSize.y == 0)
			std::cout << "Error : Grid size cannot be 0 \n";
		size_x = static_cast<int>(round(gridSize.x / nodeSize));
		size_y = static_cast<int>(round(gridSize.y / nodeSize));

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

		//top right node
		AEVec2 startNode = AEVec2{ offset.x - extend.x - half_node  , offset.y + extend.y - half_node };
		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				//calculate position
				grid[y][x].index_x = x;
				grid[y][x].index_y = y;
				grid[y][x].nodePos = AEVec2{ startNode.x + x * nodeSize , startNode.y + nodeSize * y };
				//check if occupied

			}

		}
		
	}

	void StarBangBang::Grid::CreateGrid(float _nodeSize, int width, int height)
	{
		AEVec2 size = { width * _nodeSize, height * _nodeSize };
		CreateGrid(_nodeSize, size, { _nodeSize / 2, _nodeSize / 2 - size.y });
	}

	std::vector<A_Node*> Grid::GetNodeNeighbours(const A_Node* node)
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
		result.y -= gridExtend.y;

		int  x = static_cast<int>(ceil(result.x / nodeSize));
		int  y = static_cast<int>(ceil(result.y / nodeSize));

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

	void Grid::DrawGrid()
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
					StarBangBang::DrawBoxWired(AEVec2{ nodeSize,nodeSize }, grid[y][x].nodePos, Green());
			}
		}
	}

	#pragma endregion

