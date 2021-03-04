#include "Grid.h"

using namespace StarBangBang;


Heap::Heap(int minCap)
{
	items.reserve(minCap);
	currentItemCount = 0;
}

void Heap::Add(A_Node* item)
{
	item->SetHeapIndex(currentItemCount);
	items.push_back(item);
	SortUp(item);
	currentItemCount++;
}

A_Node* Heap::RemoveFirst()
{
	A_Node* firstItem = items.front();
	currentItemCount--;
	items[0] = items[currentItemCount];
	items[0]->SetHeapIndex(0);

	SortDown(items[0]);
	return firstItem;
}

void Heap::UpdateItem(A_Node* item)
{
	SortUp(item);
}

bool Heap::Contains(A_Node* item)
{
	if (item->GetHeapIndex() > currentItemCount)
		return false;

	return (items[item->GetHeapIndex()] == item);
	/*for (int i = 0; i < currentItemCount; i++)
	{
		if (items[i]->GetHeapIndex() == item->GetHeapIndex())
			return true;
	}
	return false;*/
}
int Heap::CompareTo(const A_Node* lhs, const A_Node* rhs)
{	
	if (lhs->GetfCost() > rhs->GetfCost())
		return 1;
	if (lhs->GetfCost() < rhs->GetfCost())
		return -1;
	if (lhs->hcost > rhs->hcost)
		return 1;
	if (lhs->hcost < rhs->hcost)
		return -1;
	else
		return 0;
}

void Heap::SortDown(A_Node* item)
{
	while (true)
	{
		int childIndexLeft = item->GetHeapIndex() * 2 + 1;
		int childIndexRight = item->GetHeapIndex() * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < currentItemCount)
		{
			swapIndex = childIndexLeft;
			//inserted right
			if (childIndexRight < currentItemCount)
			{
				if (CompareTo(items[childIndexLeft], items[childIndexRight]) < 0)
				{
					swapIndex = childIndexRight;
				}
			}

			if (CompareTo(items[item->GetHeapIndex()], items[swapIndex]) < 0)
			{
				Swap(item, items[swapIndex]);
			}

			break;

		}

		break;

	}
}

void Heap::SortUp(A_Node* item)
{
	int parentIndex = (item->GetHeapIndex() - 1) / 2;

	while (true)
	{
		A_Node* parentItem = items[parentIndex];
		if (CompareTo(item, parentItem) > 0)
		{
			Swap(item, parentItem);
		}
		break;

		parentIndex = (item->GetHeapIndex() - 1) / 2;
	}
}

void Heap::Swap(A_Node* itemA, A_Node* itemB)
{
	items[itemA->GetHeapIndex()] = itemB;
	items[itemB->GetHeapIndex()] = itemA;
	int itemAIndex = itemA->GetHeapIndex();
	itemA->SetHeapIndex(itemB->GetHeapIndex());
	itemB->SetHeapIndex(itemAIndex);
}