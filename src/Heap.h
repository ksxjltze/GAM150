#pragma once
namespace StarBangBang
{
	class A_Node;

	class Interface 
	{
	public:
		virtual int GetHeapIndex() const = 0;
		virtual void SetHeapIndex(int index) = 0;
		Interface() :heapIndex{ 0 } {}
	protected:
		int heapIndex;
	};

	class Heap 
	{

	public:
		std::vector<A_Node*> items;
		int currentItemCount;
		Heap(int minCap);

		void Add(A_Node* item);

		A_Node* RemoveFirst();

		void UpdateItem(A_Node* item);

		constexpr int Count ()  const
		{
			return currentItemCount;
		}

		bool Contains(A_Node* item);

		int CompareTo(const A_Node* lhs, const A_Node* rhs);

		void SortDown(A_Node* item);

		void SortUp(A_Node* item);

		void Swap(A_Node* itemA, A_Node* itemB);
	};
}


