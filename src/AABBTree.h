#pragma once
#include "Collider.h"

namespace StarBangBang
{
	const int NULL_AABB_NODE = -1;
	struct AABB_Node
	{
		//Actual collider it contains
		BoxCollider* userData;
		BoxCollider fatAABB;
		//node parent index in the nodes array in the tree
		int parent;
		//first child index in the nodes array in the tree
		int child1;
		//second child index in the nodes array in the tree
		int child2;
		//node index in the tree
		int treeIndex;
		AABB_Node(int treeIndex = 0) 
			: userData(nullptr), fatAABB(AEVec2{ 0,0 }), parent{ NULL_AABB_NODE },
			child1{ NULL_AABB_NODE }, child2{ NULL_AABB_NODE }, treeIndex{ treeIndex }
		{}

		inline bool IsLeaf() const
		{
			return child1 == NULL_AABB_NODE;
		}
		//set the node as a tree branch
		void SetAsBranch(AABB_Node&, AABB_Node&);
		void SetAsLeaf(BoxCollider*);
		void UpdateAABB(float margin);
		AABB_Node& GetSibling(void) const;
	};	

	class AABB_Tree
	{
	public:
		
		 void Add(BoxCollider* aabb);
		 void Remove(BoxCollider* aabb);
		 void UpdateTree(void);
		 inline AABB_Node& GetTreeNode(int index) 
		 {
			 return nodes[index];
		 }
		 inline size_t GetNodeCount() const
		 {
			 return nodes.size();
		 }
	private:
		//array of nodes
		std::vector<AABB_Node> nodes;
		int rootIndex = 0;
		//addition offset for fat aabb
		float margin_aabb;

		void InsertLeaf(int node_index , int parent_index);
		void RemoveLeaf(int node_index);
		void InsertNode(AABB_Node&, AABB_Node&);

	};

	
}
