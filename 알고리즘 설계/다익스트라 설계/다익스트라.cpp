#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef pair<int, int> P;

int node_num;		//������ ��
int edge_num;		//������ ��
int q_num;		//���� ����
int id;			//���� id
string name;		//���� �̸�
int code;		//���� ħ������

int id1;		//edge_list�Է½� �ʿ��� ������ id1
int id2;		//edge_list�Է½� �ʿ��� ������ id2
int length;		//edge_list�Է½� �ʿ��� ������ ����
char q;			//������ type
int tree_num;		//Ž���������� �����Ǵ� tree set�� �� 

vector<int> node_id;
vector<vector<pair<int, int>>> edge_list;		    //(�Ÿ�, ��������id) ->�ε����� ���� (�Ÿ�, ��������id)insert	    
vector<int> find_node(1000000);			    //(id, �ε���) -> id������ �ش� ����� idxã��
vector<string>find_name(1000000);			    //(�ε���, �̸�) -> �ε����� ���� �����̸� ã��
vector<int> find_code(1000000);			    //(�ε���, �ڵ�) -> �ε����� ���� ���� �ڵ� ã��
vector<int> len(1000000);				    //(�ش���id, start��忡�� �ش�������Ÿ�)
vector<int> parent(1000000);					    //(�ش���id, parent��� id)

struct cmp						    //�켱����ť�� ���� ����
{							    //�Ÿ��� ª������ �������� �����ϵ�,
    bool operator()(P p1, P p2)				    //�Ÿ��� �������� �ִٸ� id�� �������� ���� �����Ѵ�
    {
	if (p1.first == p2.first)
	{
	    return p1.second > p2.second;
	}
	return p1.first > p2.first;
    }
};

priority_queue<P, vector<P>, cmp> pq;	    //�켱����ť (�ش��� �Ÿ�, �ش���id)�� �Է��Ѵ�

void short_distance(int start_id, int end_id)	//����Ÿ���� A�ϰ�� ȣ���ϴ� �ּҰŸ��� ���ϴ� �Լ�
{
    int start_idx = find_node[start_id];	//�Է¹��� ���۸����� �ε���
    int end_idx = find_node[end_id];		//�Է¹��� ������ ������ �ε���

    len[start_id] = 0;				//���۸����� ���۸����κ����� �Ÿ��� 0�� �Է����ش�.
    pq.push(make_pair(0, start_id));		//�켱����ť�� ��ó�� ���۸����� ������ �Է��Ѵ�

    while (!pq.empty())				//�켱����ť�� ����°� �ɶ����� �ݺ��Ѵ�.
    {
	P new_t = pq.top();
	pq.pop();

	int new_t_idx = find_node[new_t.second];	//�湮�� ������ �ε���
	int new_tree_id = new_t.second;			//�湮�� ������ id
	int now_len = len[new_tree_id];			//������ ����Ǿ��� �湮�� ������ ���۸����κ����� �Ÿ�
	
	if (now_len < new_t.first)			//������ �湮�Ǿ��ٸ� �����ϰ� �ٸ� ������ �湮�Ѵ�
	{
	    continue;
	}
	tree_num++;

	if (end_id == new_tree_id)			//�������� ã�Ҵٸ� �Լ��� ������
	{
	    return;
	}

	for (int i = 0; i < edge_list[new_t_idx].size(); i++)		//�湮�� ������ ���������� ���� Ȯ���ϴ� ����
	{
	    int check_id = edge_list[new_t_idx][i].second;		//Ȯ������ ���������� id 
	    int check_d = edge_list[new_t_idx][i].first;		//Ȯ������ ������������ �Ÿ�
	    int check_idx = find_node[check_id];			//Ȯ������ ���������� �ε���

	    if (len[check_id] > now_len + check_d && find_code[check_idx] == 0)	//Ȯ������ ������ �ִܰ�θ� ������ ������� Ȯ��
	    {
		len[check_id] = now_len + check_d;				//�ִܰŸ��� �������ش�
		pq.push(make_pair(len[check_id], check_id));			//�׸��� �켱����ť�� �־��ش�
	    }
	}
    }
}

void short_path(int start_id, int end_id)				//����Ÿ���� B�� ��� ȣ���ϴ� �ּҰ�� �Լ�
{
    int start_idx = find_node[start_id];				//���۸����� �ε���
    int end_idx = find_node[end_id];					//��ǥ������ �ε���

    len[start_id] = 0;							//���۸����� ���۸����κ����� �Ÿ��� 0���� ����
    parent[start_id] = -1;						//���۸����� ǥ�ø� ���� ���۸����� ���������� id�� -1�� ǥ���Ѵ�	    
    pq.push(make_pair(0, start_id));					//�켱����ť�� ���۸����� ���� �Է�

    while (!pq.empty())
    {
	P new_t = pq.top();
	pq.pop();

	int new_t_idx = find_node[new_t.second];			//�湮�� ������ �ε���
	int new_tree_id = new_t.second;					//�湮�� ������ id
	int now_len = len[new_tree_id];					//������ ����Ǿ��� �湮�� ������ ���۸����κ����� �Ÿ�
	
	if (now_len < new_t.first)					//������ �湮�ߴ� �����̶�� �����ϰ� ���� ���� Ž��
	{
	    continue;
	}
	tree_num++;

	if (end_id == new_tree_id)					//�湮������ ��������� �Լ�����
	{
	    return;
	}

	for (int i = 0; i < edge_list[new_t_idx].size(); i++)		//�湮�� ������ ���������� ���� Ȯ���ϴ� ����
	{
	    int check_id = edge_list[new_t_idx][i].second;		//Ȯ������ ��������� id 
	    int check_d = edge_list[new_t_idx][i].first;		//Ȯ������ ���������� �Ÿ�
	    int check_idx = find_node[check_id];			//Ȯ������ ��������� �ε���

	    if (len[check_id] > now_len + check_d && find_code[check_idx] == 0)		//Ȯ������ ������ �ִܰ�θ� ������ ������� Ȯ��
	    {
		parent[check_id] = new_tree_id;						//�ּҰ�θ� �����ϱ����� �׳���� ������θ� �缳��
		len[check_id] = now_len + check_d;					//���������κ����� �ּҰŸ��� ����
		pq.push(make_pair(len[check_id], check_id));				//�켱����ť�� ���� �Է�
	    }
	}
    }

}

void init()							    //���� 1���� ������ ��� ��庰 �Ÿ� 100������ �ʱ�ȭ
{
    for (int i = 0; i < node_id.size(); i++)		
    {
	len[node_id[i]] = 1000000;
    }
    return;
}

void Atype_print()						    //A type ������ ���� ��� ���
{
    if (len[id2] > 100000)					    //������� 100000�̻��̶�� None�� ����Ѵ�
    {
	printf("None");
    }
    else							    //�׷��� �ʴٸ� �ش� �������� ����Ѵ�
    {
	cout << tree_num << " " << len[id2] << " " << find_name[find_node[id1]] << " " << find_name[find_node[id2]] << " ";
    }
    return;
}

void Btype_print()						    //B type ������ ���� ��� ���
{
    if (len[id2] > 100000)					    //������� 100000�̻��̶�� None�� ����Ѵ�
    {
	printf("None");
    }
    else							    //�׷��� �ʴٸ� �ش� �������� ����Ѵ�
    {
	cout << tree_num << " ";
	vector<int> st;
	int tmp = id2;

	while (1)
	{
	    st.push_back(tmp);
	    tmp = parent[tmp];
	    if (tmp == -1)break;
	}

	for (int i = st.size() - 1; i >= 0; i--)
	{
	    cout << st[i] << " ";
	}
    }
    return;
}

void pq_clear()					//������ �ѹ� ��ĥ������ �켱����ť�� clear���ش�
{
    while (!pq.empty())
    {
	pq.pop();
    }
    return;
}

int main()
{
    cin >> node_num >> edge_num >> q_num;
    edge_list.resize(edge_num);

    for (int i = 0; i < node_num; i++)			    //�� ������� �Է¹ޱ�
    {
	cin >> id >> name >> code;			    
	find_node[id] = i;				    //�ش� ����� id�� index�� ����
	find_name[i] = name;				    //�ش� ����� index�� �̸��� ����
	find_code[i] = code;				    //�ش� ����� index�� ħ�����θ� ����
	node_id.push_back(id);				    //��� ����� id�� ����
    }

    for (int i = 0; i < edge_num; i++)			    //�� edge�� ������ �Է¹޴´�
    {
	cin >> id1 >> id2 >> length;

	int idx1 = find_node[id1];
	int idx2 = find_node[id2];

	edge_list[idx1].push_back(make_pair(length, id2));
	edge_list[idx2].push_back(make_pair(length, id1));
    }

    for (int i = 0; i < q_num; i++)			    //��� ������ ��ģ�� ������ �Է¹ް� �׿� ���� ����� ����Ѵ�
    {
	cin >> q >> id1 >> id2;
	int idx1 = find_node[id1];
	int idx2 = find_node[id2];
	tree_num = 0;

	init();						    //�� ������ �����ϱ��� �켱����ť�� �ʱ�ȭ�Ѵ�

	if (q == 'A')
	{
	    if (find_code[idx1] == 1 || find_code[idx2] == 1)cout << "None" << " ";
	    else
	    {
		short_distance(id1, id2);
		Atype_print();			//����type�� A�϶� �������ϴ� �Լ� ȣ��
	    }
	}
	else if (q == 'B')
	{
	    if (find_code[idx1] == 1 || find_code[idx2] == 1)cout << "None" << " ";
	    else
	    {
		short_path(id1, id2);
		Btype_print();			//����type�� B�϶� �������ϴ� �Լ� ȣ��
	    }
	}
	cout << endl;
	pq_clear();
    }

    return 0;
}