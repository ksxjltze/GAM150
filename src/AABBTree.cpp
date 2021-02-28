#include "AABBTree.h"
using namespace StarBangBang;


namespace 
{
    AABB_Tree tree;
}

void AABB_Node::SetAsBranch( AABB_Node& n1,  AABB_Node& n2)
{
	n1.parent = treeIndex;
	n2.parent = treeIndex;

	child1 = n1.treeIndex;
	child2 = n2.treeIndex;

}

void AABB_Node::SetAsLeaf(BoxCollider* userData)
{
	this->userData = userData;
	//userData.
	
	child1 = NULL_AABB_NODE;
	child2 = NULL_AABB_NODE;
}
void AABB_Node::UpdateAABB(float margin)
{
    if (IsLeaf())
    {
        AEVec2 min{ userData->Min().x - margin , userData->Min().y - margin };
        AEVec2 max{ userData->Max().x + margin , userData->Max().y + margin };
        // make fat AABB
        fatAABB = BoxCollider(min,max);
    }
    else
        // make union of child AABBs of child nodes
        fatAABB = tree.GetTreeNode(child1).userData
        ->Union(*tree.GetTreeNode(child2).userData);
}

AABB_Node& AABB_Node::GetSibling() const
{
    return treeIndex == child1 
        ? tree.GetTreeNode(child2) : tree.GetTreeNode(child1);
   
}

void AABB_Tree::Add(BoxCollider* aabb)
{

}

void AABB_Tree::Remove(BoxCollider* aabb)
{

}

void AABB_Tree::UpdateTree(void)
{

}
