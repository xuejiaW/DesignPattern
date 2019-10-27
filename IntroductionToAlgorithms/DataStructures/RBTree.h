#include <iostream>

using namespace std;

enum NodeColor
{
	RED,
	BLACK
};


class RBTreeNode
{
public:
	RBTreeNode()
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	}
	~RBTreeNode() {}

	int value;
	RBTreeNode* right;
	RBTreeNode* left;
	RBTreeNode* parent;
	NodeColor color;
};


class RBTree
{
private:
	void DestroyTree(RBTreeNode* node);
	bool LeftRotate(RBTreeNode* node);
	bool RightRotate(RBTreeNode* node);
	void InsertFixUp(RBTreeNode* node);
	bool CheckRB(RBTreeNode* root, int blackNodesNum, int k);
	void DoubleBlackFixUp(RBTreeNode* node);
public:
	RBTreeNode* doubleBlackNode;//Used for delete function
	RBTreeNode* rootNode;
	RBTreeNode* nullNode;
	RBTree();

	RBTreeNode* Search(int value);
	bool Insert(int value);
	bool Delete(int value);
	bool CheckRB();
	RBTreeNode* GetMinimum(RBTreeNode* node);
	void InorderTreeWalk(RBTreeNode* node);

	~RBTree()
	{
		DestroyTree(rootNode);
		delete nullNode;
		delete doubleBlackNode;
	}
};

bool RBTree::CheckRB()
{
	//rule 1 no need to check since every RBTreeNode has color variables
	//rule 3 no need to check since every RBTreeNode has nullNode which color is black as both children

	if (rootNode == nullNode)
		return true;
	if (rootNode->color == RED) //Break rule 2
		return false;

	int blackNodesNum_Left = 0;//left path black NodesNum from root
	int blackNodesNum_Right = 0;//left path black NodesNum from root

	RBTreeNode* node = rootNode;
	while (node != nullNode)
	{
		if (node->color == BLACK)
			blackNodesNum_Left++;

		node = node->left;
	}

	node = rootNode;
	while (node != nullNode)
	{
		if (node->color == BLACK)
			blackNodesNum_Right++;

		node = node->right;
	}

	if (blackNodesNum_Left != blackNodesNum_Right)
		return false;


	//Check every node in the tree
	return CheckRB(rootNode, blackNodesNum_Left, 0);
}

bool RBTree::CheckRB(RBTreeNode* node, int rootBlackNodesNum, int currentBlackNodesNum)
{
	if (node == nullNode)
		return true;
	if (node->color == BLACK)
		currentBlackNodesNum++;

	RBTreeNode* parent = node->parent;

	if (parent != nullNode && parent->color == RED && node->color == RED)
		return false; //break rule 4

	if (node == nullNode && currentBlackNodesNum != rootBlackNodesNum)
		return false; //break rule 5


	return CheckRB(node->left, rootBlackNodesNum, currentBlackNodesNum)
		&& CheckRB(node->right, rootBlackNodesNum, currentBlackNodesNum);

}

RBTree::RBTree()       //���캯��
{
	this->nullNode = new RBTreeNode();
	this->rootNode = nullNode;

	this->nullNode->right = this->rootNode;
	this->nullNode->left = this->rootNode;
	this->nullNode->parent = this->rootNode;
	this->nullNode->color = BLACK;

	this->doubleBlackNode = new RBTreeNode();
	this->doubleBlackNode->color = BLACK;
	this->doubleBlackNode->left = nullNode;
	this->doubleBlackNode->right = nullNode;
};


RBTreeNode* RBTree::Search(int value)
{
	RBTreeNode* node = rootNode;

	while (node != nullNode && node->value != value)
	{
		node = value < node->value ? node->left : node->right;
	}

	return node;
}


bool RBTree::LeftRotate(RBTreeNode* node)
{
	if (node == nullNode || node->right == nullNode)
	{
		cout << "Invalid operation: LeftRotate";
		return false;
	}

	//lowerRight's left subtree become node's right subtree
	RBTreeNode* lowerRight = node->right;
	node->right = lowerRight->left;
	if (lowerRight->left != nullNode)
	{
		lowerRight->left->parent = node;
	}

	//lowerRight replace node's place
	lowerRight->parent = node->parent;
	if (node->parent == nullNode)
	{
		rootNode = lowerRight;
		nullNode->right = rootNode;
		nullNode->left = rootNode;
		nullNode->parent = rootNode;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = lowerRight;
	}
	else
	{
		node->parent->right = lowerRight;
	}

	//node as lowerRight's left subtree
	node->parent = lowerRight;
	lowerRight->left = node;
}

bool RBTree::RightRotate(RBTreeNode* node)
{
	//As the symmetry of LeftRotate
	if (node == nullNode || node->left == nullNode)
	{
		return false;
	}

	RBTreeNode* lowerLeft = node->left;
	node->left = lowerLeft->right;
	if (lowerLeft->right != nullNode)
	{
		lowerLeft->right->parent = node;
	}

	lowerLeft->parent = node->parent;
	if (node->parent == nullNode)
	{
		rootNode = lowerLeft;
		nullNode->left = rootNode;
		nullNode->right = rootNode;
		nullNode->parent = rootNode;
	}
	else if (node == node->parent->right)
	{
		node->parent->right = lowerLeft;
	}
	else
	{
		node->parent->left = lowerLeft;
	}

	node->parent = lowerLeft;
	lowerLeft->right = node;
}

bool RBTree::Insert(int value)
{
	RBTreeNode* targetNode = rootNode;
	RBTreeNode* targetNodeParent = nullNode;

	while (targetNode != nullNode)
	{
		targetNodeParent = targetNode;
		if (value < targetNode->value)
		{
			targetNode = targetNode->left;
		}
		else if (value > targetNode->value)
		{
			targetNode = targetNode->right;
		}
		else
		{
			return false;
		}
	}

	RBTreeNode* toInsert = new RBTreeNode();
	toInsert->value = value;
	toInsert->color = RED;
	toInsert->right = nullNode;
	toInsert->left = nullNode;

	if (targetNodeParent == nullNode)//Tree is empty
	{
		rootNode = toInsert;
		rootNode->parent = nullNode;
		nullNode->left = rootNode;
		nullNode->right = rootNode;
		nullNode->parent = rootNode;
	}
	else
	{
		if (value < targetNodeParent->value)
		{
			targetNodeParent->left = toInsert;
		}
		else
		{
			targetNodeParent->right = toInsert;
		}
		toInsert->parent = targetNodeParent;
	}

	InsertFixUp(toInsert);
	return true;
}


void RBTree::InsertFixUp(RBTreeNode* node)
{
	while (node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)//The first three cases
		{
			RBTreeNode* uncle = node->parent->parent->right;

			if (uncle->color == RED) //Case 1
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right) //Case 2
				{
					node = node->parent;
					LeftRotate(node);
				}

				//Case3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			//The remainging three cases, as the symmetry of the first three

			RBTreeNode* uncle = node->parent->parent->left;
			if (uncle->color == RED)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RightRotate(node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				LeftRotate(node->parent->parent);
			}
		}
	}
	rootNode->color = BLACK;
}

/*
	ɾ��һ����㣺

*/
bool RBTree::Delete(int key)
{

	RBTreeNode* delete_point = Search(key);   //�ҵ�Ҫɾ���ĵ�
	if (delete_point == nullNode)
	{
		return false;
	}
	if (delete_point->left != nullNode && delete_point->right != nullNode) //�������ӽ��
	{
		RBTreeNode* replace_node = GetMinimum(delete_point->right);
		//ɾ������滻���ֵ�����������ɫ����
		int tmpkey = delete_point->value;
		delete_point->value = replace_node->value;
		replace_node->value = tmpkey;
		delete_point = replace_node;
	}
	RBTreeNode* delete_point_child;
	if (delete_point->color == RED)  //���ýڵ�Ϊ��ɫ
	{
		if (delete_point == delete_point->parent->left)   //���������
		{
			delete_point->parent->left = nullNode;
		}
		else   //������Һ���
		{
			delete_point->parent->right = nullNode;
		}
		delete delete_point;
	}

	else if (delete_point->right != nullNode) //����ҽ�㲻Ϊ��,��ʱҪɾ���Ľ��϶�Ϊ��ɫ�����ҽ��϶�Ϊ��ɫ
	{
		if (delete_point == delete_point->parent->left)  //Ҫɾ���ĵ�������
		{
			delete_point->parent->left = delete_point->right;
			delete_point->right->parent = delete_point->parent;
		}
		else
		{
			delete_point->parent->right = delete_point->right;
			delete_point->right->parent = delete_point->parent;
		}
		delete_point->right->color = BLACK;    //�ҽ����ɫ��Ϊ��ɫ
		delete delete_point;
	}
	else if (delete_point->left != nullNode)  //������㲻Ϊ�գ�δ�����滻�������ҽڵ㲻Ϊ�ղ���һ��
	{
		if (delete_point == delete_point->parent->left)   //Ҫɾ���ĵ�������
		{
			delete_point->parent->left = delete_point->left;
			delete_point->left->parent = delete_point->parent;
		}
		else
		{
			delete_point->parent->right = delete_point->left;
			delete_point->left->parent = delete_point->parent;
		}
		delete_point->left->color = BLACK; //�ҽ����ɫ��Ϊ��ɫ
		delete delete_point;
	}
	else    //���ӽڵ�����
	{
		//��ʱΨһʣ�����Ϊ��Ҫɾ�����Ϊ��ɫ�����ӽ��
		if (delete_point->parent == nullNode)  //���Ҫɾ�����Ǹ��ڵ�
		{
			rootNode = nullNode;
			nullNode->parent = rootNode;
			nullNode->left = rootNode;
			nullNode->left = rootNode;
			delete delete_point;
		}
		else
		{


			RBTreeNode* tmp = delete_point->parent;
			if (delete_point == delete_point->parent->left)   //���Ҫɾ�����Ϊ��ڵ�
			{

				delete delete_point;
				tmp->left = doubleBlackNode;
				doubleBlackNode->parent = tmp;
				DoubleBlackFixUp(doubleBlackNode);
				tmp->left = nullNode;
			}
			else    //���Ҫɾ�����Ϊ�ҽڵ�
			{

				delete delete_point;
				tmp->right = doubleBlackNode;
				doubleBlackNode->parent = tmp;
				DoubleBlackFixUp(doubleBlackNode);
				tmp->right = nullNode;
			}
		}
	}
}

/*
	˫���޸�
*/
void RBTree::DoubleBlackFixUp(RBTreeNode* node) //�������Ĳ�������˫�ڽ��
{

	if (node == node->parent->left)  //����˽��������
	{

		RBTreeNode* brother = node->parent->right;
		//���3
		if (brother->color == RED)
		{
			node->parent->color = RED;
			brother->color = BLACK;
			LeftRotate(node->parent);
			//֮��ת�����1��2
		}
		//���1
		if (brother->color == BLACK && (brother->left->color == RED || brother->right->color == RED))
		{
			if (brother->right->color == RED) //A
			{
				brother->color = node->parent->color;
				brother->right->color == BLACK;
				node->parent->color = BLACK;
				LeftRotate(node->parent);
			}
			else   //B
			{
				RightRotate(brother);
				node->parent->right->color = node->parent->color;
				node->parent->color = BLACK;
				LeftRotate(node->parent);
			}
		}
		//���2
		else if (brother->color == BLACK && (brother->left->color == BLACK && brother->right->color == BLACK))
		{
			while (node->parent != nullNode)  //��node���Ǹ��ڵ��ʱ��
			{
				brother->color = RED;
				if (node->parent->color == RED)   //�����ԭ��Ϊ��ɫ
				{
					node->parent->color = BLACK;
					break;
				}
				else  //����㱾�����Ǻ�ɫ
				{
					node = node->parent;
				}
			}
		}

	}
	else    //����˽ڵ����ҽ�㣬��������� left��right�����Ϳ���
	{
		RBTreeNode* brother = node->parent->left;
		//���3
		if (brother->color == RED)
		{
			node->parent->color = RED;
			brother->color = BLACK;
			RightRotate(node->parent);
			//֮��ת�����1��2
		}
		//���1
		if (brother->color == BLACK && (brother->right->color == RED || brother->left->color == RED))
		{
			if (brother->left->color == RED)   //A,Զֶ��
			{
				brother->color = node->parent->color;
				brother->left->color = BLACK;
				node->parent->color = BLACK;
				RightRotate(node->parent);
			}
			else   //B
			{
				LeftRotate(brother);
				node->parent->left->color = node->parent->color;
				node->parent->color = BLACK;
				RightRotate(node->parent);
			}
		}
		//���2
		else if (brother->color == BLACK && (brother->right->color == BLACK && brother->left->color == BLACK))
		{
			while (node->parent != nullNode)   //��node���Ǹ��ڵ��ʱ��
			{
				brother->color = RED;
				if (node->parent->color == RED)    //�����ԭ��Ϊ��ɫ
				{
					node->parent->color = BLACK;
					break;
				}
				else  //����㱾�����Ǻ�ɫ
				{
					node = node->parent;
				}
			}
		}
	}
}

RBTreeNode* RBTree::GetMinimum(RBTreeNode* node)
{
	if (node->left == nullNode)
		return node;
	return GetMinimum(node->left);
}

void RBTree::InorderTreeWalk(RBTreeNode* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		InorderTreeWalk(node->left);
		cout << node->value << endl;
		InorderTreeWalk(node->right);
	}
}

void RBTree::DestroyTree(RBTreeNode* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		DestroyTree(node->left);
		DestroyTree(node->right);
		delete node;
	}
};

