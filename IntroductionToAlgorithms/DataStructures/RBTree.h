#include <iostream>

using namespace std;

enum NodeColor
{
	RED,
	BLACK
};


class RB_Node   //�����
{
public:
	RB_Node()   //�ڵ��๹��
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	}
	NodeColor color; //��ɫ
	RB_Node* right;  //������
	RB_Node* left;   //������
	RB_Node* parent; //�����
	int value;    //��
};


class RB_Tree
{
private:
	RB_Tree(const RB_Tree& input) {}
	const RB_Tree& operator=(const RB_Tree& input) {}
	void InOrderTraverse(RB_Node* node); //�������
	void clear(RB_Node* node);   //���RB��
	RB_Node* doubleBlackNode;
public:
	RB_Node* root;
	RB_Node* nullNode;
	RB_Tree();  //���캯��
	bool Empty();   //�Ƿ�Ϊ����
	RB_Node* find(int key);  //���Ҽ�key��ֵ
	bool Insert(int key);    //����
	void InsertFixUp(RB_Node* node); //������޸�
	bool RotateLeft(RB_Node* node);      //����
	bool RotateRight(RB_Node* node); //����
	bool Delete(int key);   //ɾ��
	void DoubleBlackFixUp(RB_Node* node);    //˫���޸�
	RB_Node* FindMin(RB_Node* node);
	void InOrderTraverse()  //��������ⲿ�ӿ�
	{
		InOrderTraverse(root);
	}
	~RB_Tree()
	{
		clear(root);
		delete nullNode;
	}
};

RB_Tree::RB_Tree()       //���캯��
{
	this->nullNode = new RB_Node();
	this->root = nullNode;
	this->nullNode->right = this->root;
	this->nullNode->left = this->root;
	this->nullNode->parent = this->root;
	this->nullNode->color = BLACK;

	this->doubleBlackNode = new RB_Node();
	this->doubleBlackNode->color = BLACK;
	this->doubleBlackNode->left = nullNode;
	this->doubleBlackNode->right = nullNode;
};


bool RB_Tree::Empty()
{
	if (this->root == this->nullNode)
	{
		return true;
	}
	else
	{
		return false;
	}
}


RB_Node* RB_Tree::find(int key)   //���ң��˴��ɵݹ飬�ο���һƪ���������
{
	RB_Node* index = root;
	while (index != nullNode)
	{
		if (key < index->value)
		{
			index = index->left;
		}
		else if (key > index->value)
		{
			index = index->right;
		}
		else
		{
			break;
		}
	}
	return index;
}

/*
	����������һ��ָ��lower_rightָ����ת����Һ��ӡ�
	lower_right�ĸ����Ϊ��ת��ĸ����,��ת����Һ���Ϊlower_right�����ӣ�������Ӳ�Ϊ�գ���Ҫ�������ӵĸ���Ϊ��ת�㣩��
	�ж���ת���Ƿ�Ϊ���ڵ㡣�ǵĻ�����m_root��ֵ�����������ת��ĸ�������� or �Һ��ӵ�ָ��
	������ת�㸸���Ϊlower_right��lower_right������Ϊ��ת��
*/
bool RB_Tree::RotateLeft(RB_Node* node)
{
	if (node == nullNode || node->right == nullNode)
	{
		return false;   //������ת
	}
	RB_Node* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != nullNode)
	{
		lower_right->left->parent = node;
	}
	if (node->parent == nullNode)
	{
		root = lower_right;
		nullNode->right = root;
		nullNode->left = root;
		nullNode->parent = root;
	}
	else
	{
		if (node == node->parent->left)
		{
			node->parent->left = lower_right;
		}
		else
		{
			node->parent->right = lower_right;
		}
	}
	node->parent = lower_right;
	lower_right->left = node;
}

bool RB_Tree::RotateRight(RB_Node* node)  //������ԭ��ͬ����,left��right�����Ϳ���
{
	if (node == nullNode || node->left == nullNode)
	{
		return false;//can't rotate    
	}
	RB_Node* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != nullNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == nullNode) //node is root    
	{
		root = lower_left;
		nullNode->left = root;
		nullNode->right = root;
		nullNode->parent = root;    
	}
	else
	{
		if (node == node->parent->right)
		{
			node->parent->right = lower_left;
		}
		else
		{
			node->parent->left = lower_left;
		}
	}
	node->parent = lower_left;
	lower_left->right = node;
}

/*
		���룬whileѭ����insert_pointָ��Ҫ����ĵ�
		���������Ѿ����ڣ�����false������������һ�ſ�����ֱ�Ӹ�ֵ�����ڵ㡣�����ڲ���㸳ֵ
*/
bool RB_Tree::Insert(int key)
{
	RB_Node* targetNode = root;
	RB_Node* targetNodeParent = nullNode;

	while (targetNode != nullNode)
	{
		targetNodeParent = targetNode;
		if (key < targetNode->value)
		{
			targetNode = targetNode->left;
		}
		else if (key > targetNode->value)
		{
			targetNode = targetNode->right;
		}
		else
		{
			return false;
		}
	}   //��ʱinsert_pointָ��Ҫ����ĵ�
	RB_Node* insert_node = new RB_Node(); //�������Ľ��
	insert_node->value = key;
	insert_node->color = RED;
	insert_node->right = nullNode;
	insert_node->left = nullNode;
	if (targetNodeParent == nullNode)        //�����һ�ſ���
	{
		root = insert_node;
		root->parent = nullNode;
		nullNode->left = root;
		nullNode->right = root;
		nullNode->parent = root;
	}
	else
	{
		if (key < targetNodeParent->value)
		{
			targetNodeParent->left = insert_node;
		}
		else
		{
			targetNodeParent->right = insert_node;
		}
		insert_node->parent = targetNodeParent;
	}
	InsertFixUp(insert_node);   //����InsertFixUp�޸����������
}

/*
A   ���׽ڵ�Ϊ��ɫʱ���޸�
	�����޸�����Ϊ�����ĸ�������游�������ӻ����Һ���
B   ���ӵĻ���
 C      ����һ��uncle���ָ������ڵ㣨�������ֵܣ���
 D      1�����������Ϊ��ɫ���������������ڣ��游�ڵ�������Ϊ��ǰ���
 E      2������ڵ�Ϊ��ɫ���������ڵ��Ǹ��ڵ���Һ��ӣ��������Ϊ��ǰ�ڵ�Ȼ��������ת��Ϊ�������������
 F      3������ڵ�Ϊ��ɫ������ڵ�Ϊ���ӣ�������ڣ��游��죬�游���Ϊ֧������
G   �Һ��ӵĻ���
*/
void RB_Tree::InsertFixUp(RB_Node* node)
{
	while (node->parent->color == RED)        //A
	{
		if (node->parent == node->parent->parent->left)    //B
		{
			RB_Node* uncle = node->parent->parent->right;   //C
			if (uncle->color == RED) //D
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else if (uncle->color == BLACK)
			{
				if (node == node->parent->right) //E
				{
					node = node->parent;
					RotateLeft(node);
				}
				//F
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RotateRight(node->parent->parent);
			}
		}
		else    //G
		{
			RB_Node* uncle = node->parent->parent->left;
			if (uncle->color == RED)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				uncle->parent->color = RED;
				node = node->parent->parent;
			}
			else if (uncle->color == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RotateLeft(node->parent->parent);
			}
		}
	}
	root->color = BLACK;    //�޸����ڵ���ɫ����ֹ����Ϊ��ɫ
}

/*
	ɾ��һ����㣺

*/
bool RB_Tree::Delete(int key)
{

	RB_Node* delete_point = find(key);   //�ҵ�Ҫɾ���ĵ�
	if (delete_point == nullNode)
	{
		return false;
	}
	if (delete_point->left != nullNode && delete_point->right != nullNode) //�������ӽ��
	{
		RB_Node* replace_node = FindMin(delete_point->right);
		//ɾ������滻���ֵ�����������ɫ����
		int tmpkey = delete_point->value;
		delete_point->value = replace_node->value;
		replace_node->value = tmpkey;
		delete_point = replace_node;
	}
	RB_Node* delete_point_child;
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
			root = nullNode;
			nullNode->parent = root;
			nullNode->left = root;
			nullNode->left = root;
			delete delete_point;
		}
		else
		{


			RB_Node* tmp = delete_point->parent;
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
void RB_Tree::DoubleBlackFixUp(RB_Node* node) //�������Ĳ�������˫�ڽ��
{

	if (node == node->parent->left)  //����˽��������
	{

		RB_Node* brother = node->parent->right;
		//���3
		if (brother->color == RED)
		{
			node->parent->color = RED;
			brother->color = BLACK;
			RotateLeft(node->parent);
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
				RotateLeft(node->parent);
			}
			else   //B
			{
				RotateRight(brother);
				node->parent->right->color = node->parent->color;
				node->parent->color = BLACK;
				RotateLeft(node->parent);
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
		RB_Node* brother = node->parent->left;
		//���3
		if (brother->color == RED)
		{
			node->parent->color = RED;
			brother->color = BLACK;
			RotateRight(node->parent);
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
				RotateRight(node->parent);
			}
			else   //B
			{
				RotateLeft(brother);
				node->parent->left->color = node->parent->color;
				node->parent->color = BLACK;
				RotateRight(node->parent);
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

RB_Node* RB_Tree::FindMin(RB_Node* node)
{
	if (node->left == nullNode)
		return node;
	return FindMin(node->left);
}

  //�������
void RB_Tree::InOrderTraverse(RB_Node* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		InOrderTraverse(node->left);
		cout << node->value << endl;
		InOrderTraverse(node->right);
	}
}

void RB_Tree::clear(RB_Node* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
};

