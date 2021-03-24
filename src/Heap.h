
#pragma once
#include <vector>
template<typename T, typename Compare = std::greater<T> >
class Heap 
{

public:
	int max_size;
	int curr_size;

	Heap(int max_size) : max_size(max_size), curr_size{ 0 } {container.reserve(max_size); }

	int GetLeftChild(int pIndex) const
	{
		return pIndex * 2 + 1;
	}
	int GetRightChild(int pIndex) const
	{
		return pIndex * 2 + 2;
	}
	//sort from btm up
	void SortUp(const T& val)
	{
		int parentIndex = (val.HeapIndex - 1) / 2;

		while (parentIndex > 0)
		{
			//int compare = Compare();
		
			T parentItem = container[parentIndex];
			
			parentIndex = (val.HeapIndex - 1) / 2;
		}
	}
	//sort from top to btm
	void SortDown()
	{

	}
	void Insert(const T& val)
	{
		
		//no sorting
		if (curr_size == 0)
		{
			++curr_size;
			container[0] = val;
			return;
		}
		
		container[curr_size] = val;
		val.SetHeapIndex(curr_size);
		++curr_size;
		SortUp(val);

	}
	//remove the first elememt
	T pop()
	{
		if (curr_size <= 0)
			return;
		

		T first = container[0];


		return first;
	}

private:
	std::vector<T> container;

};