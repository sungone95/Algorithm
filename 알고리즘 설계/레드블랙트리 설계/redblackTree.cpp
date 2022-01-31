#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class node 
{
public:
    string color;			    //red-black-tree의 노드의 색(black or red)
    node* left;				    //red-black-tree의 왼쪽 자식노드
    node* right;			    //red-black-tree의 오른쪽 자식노드
    node* parent;			    //red-black-tree의 부모노드
    int depth;				    //red-black-tree에서 노드의 위치에 따른 깊이

    int value;				    //환자번호
    string name;			    //이름
    string phone_num;			    //연락처
    string home_x;			    //x좌표
    string home_y;			    //y좌표
    string last_type;			    //마지막으로 추가된 병명
    vector<pair<string, int>> sick_list;    //병명과 진료비 리스트

    node(int value, string name, string phone_num, string home_x, string home_y, string sick_type, int money)	    //node class의 생성자
    {
	this->value = value;
	this->name = name;
	this->phone_num = phone_num;
	this->home_x = home_x;
	this->home_y = home_y;
	this->last_type = sick_type;
	sick_list.push_back(make_pair(sick_type, money));		    //환자 정보의 입력값을 node의 변수에 입력한다. 

	this->color = "red";						    //초기 node를 생성할때는 규칙에 따라 red로 생성
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
    vector<node*> list;							    //red-black-tree의 node 리스트를 벡터로 저장

    RBT() 
    {
	root = NULL;
    }

    void insert(int value, string name, string phone_num, string home_x, string home_y, string sick_type, int money)	    //node의 삽입연산
    {
	node* Node = new node(value, name, phone_num, home_x, home_y, sick_type, money);	    //새로운 노드를 생성하고 인자를 통해 입력받은수를 대입한다.
	int d = 0;										    //깊이는 계산을 통해 입력해야하므로 초기화는 0으로한다.

	if (root == NULL)   
	{
	    root = Node;									    //red-black-tree에서 root가 없다면 새로운 노드를 root로 저장 
	    Node->depth = d;
	}
	else
	{
	    node* cur = root;									    //노드의 위치탐색을 위한 변수선언
	    node* next = root;

	    while (next != NULL)								    //노드의 위치를 탐색하는 과정
	    {
		cur = next;
		if (cur->value > Node->value)
		{
		    next = cur->left;
		}
		else next = cur->right;

		d++;										    //탐색하는 과정에서 깊이는 1씩 증가한다
	    }
	    if (cur->value < Node->value)cur->right = Node;					    //cur노드와 Node노드의 값비교를 통해 left인지 right인지 확인 
	    else cur->left = Node;

	    Node->parent = cur;
	    Node->depth = d;
	}
	list.push_back(Node);									    //노드를 전체 저장하는 벡터에도 입력
	
	st_change(Node);									    //트리에 삽입후 트리의 구조를 조정하는 함수 호출
    }
    
    node* find(int data)									    //입력된 환자번호를 기준으로 해당노드를 찾는 함수
    {
	node* cur = root;
	
	while (cur != NULL)									    //root에서부터 값비교를 통해 노드를 찾는과정
	{
	    if (cur->value > data)cur = cur->left;
	    else if (cur->value < data)cur = cur->right;
	    else if (cur->value == data)return cur;
	}
	return NULL;
    }

    int check(string sick_type)									    //유행병 조사횟수를 전체탐색하는 함수
    {
	int count = 0;										    //횟수를 저장하는 변수(0으로 초기화)
	for (int i = 0; i < list.size(); i++)					
	{
	    if (list[i]->last_type == sick_type)count++;					    //모든 노드를 저장하는 벡터에서 순차탐색을 통해 count를 계산한다.
	}
	return count;
    }

    void d_reset(node* tmp, int d)						//트리의 구조가 바뀔때 위치가 조정된 노드의 깊이를 조정해주는 함수
    {
	if (tmp == NULL)return;
	tmp->depth = d+1;									

	d_reset(tmp->left, d + 1);
	d_reset(tmp->right, d + 1);						//위치가 조정된 sub트리의 root에서부터 재귀적으로 모든노드의 위치를 조정해준다
    }

    void st_change(node* Node)									//구조 재배치 및 노드색 변경(각 case에 대한 설명은 보고서에 기입)
    {
	if (Node == root)
	{
	    Node->color = "black";								//root면 검은색으로 바꾸고 끝.
	    return;
	}
	else if (Node->parent->color == "black")return;						//부모노드가 검은색이면 그대로 놔둠.
	else if (Node->parent->color == "red")							//부모노드가 빨간색이면 구조 재배치.
	{
	    node* g_p = Node->parent->parent;							//g_p는 Node의 부모노드의 부모노드(grand parent의 약자)
	    node* p = Node->parent;	    
	    node* gg_p = g_p->parent;								//g_p가 루트이면 놔두고 아니면 gg_p(g_p의 parent노드)도 선언 				

	    if ((g_p->left == NULL || g_p->left->color == "black") && g_p->value < Node->value && Node->value < p->value)	//1번 케이스
	    {
		Node->parent = NULL;								    //기존의 관계들 정리, 끊기
		p->left = NULL;									    //트리의 구조가 조정되면 각 노드의 관계도 변하므로
		p->parent = NULL;								    //오류를 방지하기위해 미리 관계를 끊어준다.
		g_p->right = NULL;
		g_p->parent = NULL;

		if (g_p == root)root = Node;			    				    
		else										    //아니면 new의 부모를 gg_p로 
		{
		    if (gg_p->value > g_p->value)gg_p->left = Node;
		    else gg_p->right = Node;

		    Node->parent = gg_p;
		}
		Node->depth -= 2;								    //재배치에 따른 해당노드 깊이 조절

		g_p->right = Node->left;
		if(Node->left!=NULL)Node->left->parent = g_p;							

		p->left = Node->right;
		if(Node->right!=NULL)Node->right->parent = p;					    //끊었던 노드관계들 위치조정후 관계정리

		Node->left = g_p; g_p->parent = Node;						    //new의 자식노드로 g_p, p를 연결
		Node->right = p; p->parent = Node;
		Node->color = "black"; g_p->color = "red";

		d_reset(Node->left, Node->depth);						    //Node가 sub_tree의 root가 되므로 Node의 left,right의 depth를 재조정
		d_reset(Node->right, Node->depth);
	    }
	    else if ((g_p->right == NULL || g_p->right->color == "black") && p->value < Node->value && Node->value < g_p->value)   //2번케이스
	    {
		Node->parent = NULL;
		p->right = NULL;
		p->parent = NULL;
		g_p->left = NULL;
		g_p->parent = NULL;								    //기존의 관계들 정리, 끊기

		if (g_p == root)root = Node;
		else
		{
		    if (gg_p->value > g_p->value)gg_p->left = Node;
		    else gg_p->right = Node;

		    Node->parent = gg_p;
		}

		Node->depth -= 2;								    //재배치에 따른 노드별 깊이 조절

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
	    else if ((g_p->right == NULL || g_p->right->color == "black") && Node->value < p->value && p->value < g_p->value)	//3번케이스
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
	    else if ((g_p->left == NULL || g_p->left->color == "black") && g_p->value < p->value && p->value < Node->value)	//4번케이스
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
	    else if (g_p->left!=NULL && g_p->left->color == "red" && g_p->right!=NULL && g_p->right->color == "red") // 5번케이스(uncle노드가 red일때)
	    {
		g_p->color = "red";
		g_p->left->color = "black";
		g_p->right->color = "black";
		st_change(g_p);						    //g_p노드의 색, gg_p노드의 색모두 red일수 있으므로 재귀실행
	    }
	}
    }
};


int main()
{
    RBT rbt;
    
    int input;
    char q_type;

    int value;			    //환자번호
    string name;		    //이름
    string phone_num;		    //연락처
    string home_x;
    string home_y;
    string sick_type;
    int money;

    cin >> input;
    
    for (int i = 0; i < input; i++)
    {
	cin >> q_type;		    //질문 종류 입력

	if (q_type == 'I')	    //환자 정보 확인후 없으면 새로운 정보 입력
	{
	    cin >> value >> name >> phone_num >> home_x >> home_y >> sick_type >> money;    //환자 정보 입력
	    node* tmp = rbt.find(value);						    //node형 포인터변수를 선언후 해당 노드가 있는지 확인
	    if (tmp == NULL)								    //찾아보고 없으면 입력받은값으로 노드생성
	    {
		rbt.insert(value, name, phone_num, home_x, home_y, sick_type, money);
		cout << rbt.find(value)->depth << " " << 1 << endl;
	    }
	    else									    //값이 있을때
	    {
		cout << tmp->depth << " " << 0 << endl;
	    }
	}
	else if (q_type == 'F')		    //환자 정보 찾기
	{
	    cin >> value;
	    node* tmp = rbt.find(value);    // 해당 환자의 노드를 찾는다
	    
	    if (tmp == NULL)cout << "Not found" << endl;    //해당 환자가 없을때
	    else					    //있을때는 관련 정보를 출력한다
	    {
		cout << tmp->depth << " " << tmp->name << " " << tmp->phone_num << " " << tmp->home_x << " " << tmp->home_y << endl;
	    }
	}
	else if (q_type == 'A')		 //환자 병명, 진료비 추가
	{
	    cin >> value >> sick_type >> money;
	    node* tmp = rbt.find(value);
	    
	    if (tmp == NULL)cout << "Not found" << endl;    //해당 환자가 없을때
	    else					    //해당 환자가 있으면 (추가적인병명,진료비)를 입력한다.
	    {
		tmp->sick_list.push_back(make_pair(sick_type,money));
		tmp->last_type = sick_type;
		cout << tmp->depth << endl;
	    }
	}
	else if (q_type == 'E')		    //유행병 카운트 출력
	{
	    cin >> sick_type;
	    cout << rbt.check(sick_type) << endl;
	}
    }

    return 0;
}