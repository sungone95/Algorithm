#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class node 
{
public:
    string color;			    //red-black-tree�� ����� ��(black or red)
    node* left;				    //red-black-tree�� ���� �ڽĳ��
    node* right;			    //red-black-tree�� ������ �ڽĳ��
    node* parent;			    //red-black-tree�� �θ���
    int depth;				    //red-black-tree���� ����� ��ġ�� ���� ����

    int value;				    //ȯ�ڹ�ȣ
    string name;			    //�̸�
    string phone_num;			    //����ó
    string home_x;			    //x��ǥ
    string home_y;			    //y��ǥ
    string last_type;			    //���������� �߰��� ����
    vector<pair<string, int>> sick_list;    //����� ����� ����Ʈ

    node(int value, string name, string phone_num, string home_x, string home_y, string sick_type, int money)	    //node class�� ������
    {
	this->value = value;
	this->name = name;
	this->phone_num = phone_num;
	this->home_x = home_x;
	this->home_y = home_y;
	this->last_type = sick_type;
	sick_list.push_back(make_pair(sick_type, money));		    //ȯ�� ������ �Է°��� node�� ������ �Է��Ѵ�. 

	this->color = "red";						    //�ʱ� node�� �����Ҷ��� ��Ģ�� ���� red�� ����
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
	this->depth = 0;
    }
};

class RBT
{
public:
    node* root;
    vector<node*> list;							    //red-black-tree�� node ����Ʈ�� ���ͷ� ����

    RBT() 
    {
	root = NULL;
    }

    void insert(int value, string name, string phone_num, string home_x, string home_y, string sick_type, int money)	    //node�� ���Կ���
    {
	node* Node = new node(value, name, phone_num, home_x, home_y, sick_type, money);	    //���ο� ��带 �����ϰ� ���ڸ� ���� �Է¹������� �����Ѵ�.
	int d = 0;										    //���̴� ����� ���� �Է��ؾ��ϹǷ� �ʱ�ȭ�� 0�����Ѵ�.

	if (root == NULL)   
	{
	    root = Node;									    //red-black-tree���� root�� ���ٸ� ���ο� ��带 root�� ���� 
	    Node->depth = d;
	}
	else
	{
	    node* cur = root;									    //����� ��ġŽ���� ���� ��������
	    node* next = root;

	    while (next != NULL)								    //����� ��ġ�� Ž���ϴ� ����
	    {
		cur = next;
		if (cur->value > Node->value)
		{
		    next = cur->left;
		}
		else next = cur->right;

		d++;										    //Ž���ϴ� �������� ���̴� 1�� �����Ѵ�
	    }
	    if (cur->value < Node->value)cur->right = Node;					    //cur���� Node����� ���񱳸� ���� left���� right���� Ȯ�� 
	    else cur->left = Node;

	    Node->parent = cur;
	    Node->depth = d;
	}
	list.push_back(Node);									    //��带 ��ü �����ϴ� ���Ϳ��� �Է�
	
	st_change(Node);									    //Ʈ���� ������ Ʈ���� ������ �����ϴ� �Լ� ȣ��
    }
    
    node* find(int data)									    //�Էµ� ȯ�ڹ�ȣ�� �������� �ش��带 ã�� �Լ�
    {
	node* cur = root;
	
	while (cur != NULL)									    //root�������� ���񱳸� ���� ��带 ã�°���
	{
	    if (cur->value > data)cur = cur->left;
	    else if (cur->value < data)cur = cur->right;
	    else if (cur->value == data)return cur;
	}
	return NULL;
    }

    int check(string sick_type)									    //���ິ ����Ƚ���� ��üŽ���ϴ� �Լ�
    {
	int count = 0;										    //Ƚ���� �����ϴ� ����(0���� �ʱ�ȭ)
	for (int i = 0; i < list.size(); i++)					
	{
	    if (list[i]->last_type == sick_type)count++;					    //��� ��带 �����ϴ� ���Ϳ��� ����Ž���� ���� count�� ����Ѵ�.
	}
	return count;
    }

    void d_reset(node* tmp, int d)						//Ʈ���� ������ �ٲ� ��ġ�� ������ ����� ���̸� �������ִ� �Լ�
    {
	if (tmp == NULL)return;
	tmp->depth = d+1;									

	d_reset(tmp->left, d + 1);
	d_reset(tmp->right, d + 1);						//��ġ�� ������ subƮ���� root�������� ��������� ������� ��ġ�� �������ش�
    }

    void st_change(node* Node)									//���� ���ġ �� ���� ����(�� case�� ���� ������ ������ ����)
    {
	if (Node == root)
	{
	    Node->color = "black";								//root�� ���������� �ٲٰ� ��.
	    return;
	}
	else if (Node->parent->color == "black")return;						//�θ��尡 �������̸� �״�� ����.
	else if (Node->parent->color == "red")							//�θ��尡 �������̸� ���� ���ġ.
	{
	    node* g_p = Node->parent->parent;							//g_p�� Node�� �θ����� �θ���(grand parent�� ����)
	    node* p = Node->parent;	    
	    node* gg_p = g_p->parent;								//g_p�� ��Ʈ�̸� ���ΰ� �ƴϸ� gg_p(g_p�� parent���)�� ���� 				

	    if ((g_p->left == NULL || g_p->left->color == "black") && g_p->value < Node->value && Node->value < p->value)	//1�� ���̽�
	    {
		Node->parent = NULL;								    //������ ����� ����, ����
		p->left = NULL;									    //Ʈ���� ������ �����Ǹ� �� ����� ���赵 ���ϹǷ�
		p->parent = NULL;								    //������ �����ϱ����� �̸� ���踦 �����ش�.
		g_p->right = NULL;
		g_p->parent = NULL;

		if (g_p == root)root = Node;			    				    
		else										    //�ƴϸ� new�� �θ� gg_p�� 
		{
		    if (gg_p->value > g_p->value)gg_p->left = Node;
		    else gg_p->right = Node;

		    Node->parent = gg_p;
		}
		Node->depth -= 2;								    //���ġ�� ���� �ش��� ���� ����

		g_p->right = Node->left;
		if(Node->left!=NULL)Node->left->parent = g_p;							

		p->left = Node->right;
		if(Node->right!=NULL)Node->right->parent = p;					    //������ ������� ��ġ������ ��������

		Node->left = g_p; g_p->parent = Node;						    //new�� �ڽĳ��� g_p, p�� ����
		Node->right = p; p->parent = Node;
		Node->color = "black"; g_p->color = "red";

		d_reset(Node->left, Node->depth);						    //Node�� sub_tree�� root�� �ǹǷ� Node�� left,right�� depth�� ������
		d_reset(Node->right, Node->depth);
	    }
	    else if ((g_p->right == NULL || g_p->right->color == "black") && p->value < Node->value && Node->value < g_p->value)   //2�����̽�
	    {
		Node->parent = NULL;
		p->right = NULL;
		p->parent = NULL;
		g_p->left = NULL;
		g_p->parent = NULL;								    //������ ����� ����, ����

		if (g_p == root)root = Node;
		else
		{
		    if (gg_p->value > g_p->value)gg_p->left = Node;
		    else gg_p->right = Node;

		    Node->parent = gg_p;
		}

		Node->depth -= 2;								    //���ġ�� ���� ��庰 ���� ����

		p->right = Node->left;
		if(Node->left!=NULL)Node->left->parent = p;
		g_p->left = Node->right;
		if(Node->right!=NULL)Node->right->parent = g_p;

		Node->left = p; p->parent = Node;
		Node->right = g_p; g_p->parent = Node;
		Node->color = "black"; g_p->color = "red";

		d_reset(Node->left, Node->depth);
		d_reset(Node->right, Node->depth);
	    }
	    else if ((g_p->right == NULL || g_p->right->color == "black") && Node->value < p->value && p->value < g_p->value)	//3�����̽�
	    {
		p->parent = NULL;
		g_p->left = NULL;
		g_p->parent = NULL;

		if (g_p == root)root = p;
		else
		{
		    if (gg_p->value > g_p->value)gg_p->left = p;
		    else gg_p->right = p;

		    p->parent = gg_p;
		}
		p->depth--;

		g_p->left = p->right;
		if(p->right!=NULL)p->right->parent = g_p;

		p->right = g_p; g_p->parent = p;
		p->color = "black"; g_p->color = "red";

		d_reset(p->left, p->depth);
		d_reset(p->right, p->depth);
	    }
	    else if ((g_p->left == NULL || g_p->left->color == "black") && g_p->value < p->value && p->value < Node->value)	//4�����̽�
	    {
		p->parent = NULL;
		g_p->right = NULL;
		g_p->parent = NULL;

		if (g_p == root)root = p;
		else
		{
		    if (gg_p->value > g_p->value)gg_p->left = p;
		    else gg_p->right = p;

		    p->parent = gg_p;
		}
		p->depth--;

		g_p->right = p->left;
		if(p->left!=NULL)p->left->parent = g_p;

		p->left = g_p; g_p->parent = p;
		p->color = "black"; g_p->color = "red";

		d_reset(p->left, p->depth);
		d_reset(p->right, p->depth);
	    }
	    else if (g_p->left!=NULL && g_p->left->color == "red" && g_p->right!=NULL && g_p->right->color == "red") // 5�����̽�(uncle��尡 red�϶�)
	    {
		g_p->color = "red";
		g_p->left->color = "black";
		g_p->right->color = "black";
		st_change(g_p);						    //g_p����� ��, gg_p����� ����� red�ϼ� �����Ƿ� ��ͽ���
	    }
	}
    }
};


int main()
{
    RBT rbt;
    
    int input;
    char q_type;

    int value;			    //ȯ�ڹ�ȣ
    string name;		    //�̸�
    string phone_num;		    //����ó
    string home_x;
    string home_y;
    string sick_type;
    int money;

    cin >> input;
    
    for (int i = 0; i < input; i++)
    {
	cin >> q_type;		    //���� ���� �Է�

	if (q_type == 'I')	    //ȯ�� ���� Ȯ���� ������ ���ο� ���� �Է�
	{
	    cin >> value >> name >> phone_num >> home_x >> home_y >> sick_type >> money;    //ȯ�� ���� �Է�
	    node* tmp = rbt.find(value);						    //node�� �����ͺ����� ������ �ش� ��尡 �ִ��� Ȯ��
	    if (tmp == NULL)								    //ã�ƺ��� ������ �Է¹��������� ������
	    {
		rbt.insert(value, name, phone_num, home_x, home_y, sick_type, money);
		cout << rbt.find(value)->depth << " " << 1 << endl;
	    }
	    else									    //���� ������
	    {
		cout << tmp->depth << " " << 0 << endl;
	    }
	}
	else if (q_type == 'F')		    //ȯ�� ���� ã��
	{
	    cin >> value;
	    node* tmp = rbt.find(value);    // �ش� ȯ���� ��带 ã�´�
	    
	    if (tmp == NULL)cout << "Not found" << endl;    //�ش� ȯ�ڰ� ������
	    else					    //�������� ���� ������ ����Ѵ�
	    {
		cout << tmp->depth << " " << tmp->name << " " << tmp->phone_num << " " << tmp->home_x << " " << tmp->home_y << endl;
	    }
	}
	else if (q_type == 'A')		 //ȯ�� ����, ����� �߰�
	{
	    cin >> value >> sick_type >> money;
	    node* tmp = rbt.find(value);
	    
	    if (tmp == NULL)cout << "Not found" << endl;    //�ش� ȯ�ڰ� ������
	    else					    //�ش� ȯ�ڰ� ������ (�߰����κ���,�����)�� �Է��Ѵ�.
	    {
		tmp->sick_list.push_back(make_pair(sick_type,money));
		tmp->last_type = sick_type;
		cout << tmp->depth << endl;
	    }
	}
	else if (q_type == 'E')		    //���ິ ī��Ʈ ���
	{
	    cin >> sick_type;
	    cout << rbt.check(sick_type) << endl;
	}
    }

    return 0;
}