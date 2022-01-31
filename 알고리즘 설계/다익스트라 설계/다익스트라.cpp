#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef pair<int, int> P;

int node_num;		//마을의 수
int edge_num;		//도로의 수
int q_num;		//질의 갯수
int id;			//마을 id
string name;		//마을 이름
int code;		//마을 침수여부

int id1;		//edge_list입력시 필요한 정점의 id1
int id2;		//edge_list입력시 필요한 정점의 id2
int length;		//edge_list입력시 필요한 간선의 길이
char q;			//질문의 type
int tree_num;		//탐색과정에서 증가되는 tree set의 수 

vector<int> node_id;
vector<vector<pair<int, int>>> edge_list;		    //(거리, 인접정점id) ->인덱스를 통해 (거리, 인접정점id)insert	    
vector<int> find_node(1000000);			    //(id, 인덱스) -> id를통해 해당 노드의 idx찾기
vector<string>find_name(1000000);			    //(인덱스, 이름) -> 인덱스를 통해 마을이름 찾기
vector<int> find_code(1000000);			    //(인덱스, 코드) -> 인덱스를 통해 마을 코드 찾기
vector<int> len(1000000);				    //(해당노드id, start노드에서 해당노드까지거리)
vector<int> parent(1000000);					    //(해당노드id, parent노드 id)

struct cmp						    //우선순위큐의 정렬 기준
{							    //거리가 짧은것을 기준으로 정렬하되,
    bool operator()(P p1, P p2)				    //거리가 같은것이 있다면 id가 작은것을 먼저 선정한다
    {
	if (p1.first == p2.first)
	{
	    return p1.second > p2.second;
	}
	return p1.first > p2.first;
    }
};

priority_queue<P, vector<P>, cmp> pq;	    //우선순위큐 (해당노드 거리, 해당노드id)를 입력한다

void short_distance(int start_id, int end_id)	//질문타입이 A일경우 호출하는 최소거리를 구하는 함수
{
    int start_idx = find_node[start_id];	//입력받은 시작마을의 인덱스
    int end_idx = find_node[end_id];		//입력받은 목적지 마을의 인덱스

    len[start_id] = 0;				//시작마을의 시작마을로부터의 거리는 0을 입력해준다.
    pq.push(make_pair(0, start_id));		//우선순위큐에 맨처음 시작마을의 정보를 입력한다

    while (!pq.empty())				//우선순위큐가 빈상태가 될때까지 반복한다.
    {
	P new_t = pq.top();
	pq.pop();

	int new_t_idx = find_node[new_t.second];	//방문한 마을의 인덱스
	int new_tree_id = new_t.second;			//방문한 마을의 id
	int now_len = len[new_tree_id];			//이전에 저장되었던 방문한 마을의 시작마을로부터의 거리
	
	if (now_len < new_t.first)			//이전에 방문되었다면 무시하고 다른 마을을 방문한다
	{
	    continue;
	}
	tree_num++;

	if (end_id == new_tree_id)			//목적지를 찾았다면 함수를 끝낸다
	{
	    return;
	}

	for (int i = 0; i < edge_list[new_t_idx].size(); i++)		//방문한 마을의 인접마을에 대해 확인하는 과정
	{
	    int check_id = edge_list[new_t_idx][i].second;		//확인중인 인접마을의 id 
	    int check_d = edge_list[new_t_idx][i].first;		//확인중인 인접마을과의 거리
	    int check_idx = find_node[check_id];			//확인중인 인접마을의 인덱스

	    if (len[check_id] > now_len + check_d && find_code[check_idx] == 0)	//확인중인 마을이 최단경로를 갱신할 대상인지 확인
	    {
		len[check_id] = now_len + check_d;				//최단거리를 갱신해준다
		pq.push(make_pair(len[check_id], check_id));			//그리고 우선순위큐에 넣어준다
	    }
	}
    }
}

void short_path(int start_id, int end_id)				//질문타입이 B일 경우 호출하는 최소경로 함수
{
    int start_idx = find_node[start_id];				//시작마을의 인덱스
    int end_idx = find_node[end_id];					//목표마을의 인덱스

    len[start_id] = 0;							//시작마을의 시작마을로부터의 거리는 0으로 설정
    parent[start_id] = -1;						//시작마을의 표시를 위해 시작마을의 이전마을의 id는 -1로 표시한다	    
    pq.push(make_pair(0, start_id));					//우선순위큐에 시작마을의 정보 입력

    while (!pq.empty())
    {
	P new_t = pq.top();
	pq.pop();

	int new_t_idx = find_node[new_t.second];			//방문한 마을의 인덱스
	int new_tree_id = new_t.second;					//방문한 마을의 id
	int now_len = len[new_tree_id];					//이전에 저장되었던 방문한 마을의 시작마을로부터의 거리
	
	if (now_len < new_t.first)					//이전에 방문했던 마을이라면 무시하고 다음 마을 탐색
	{
	    continue;
	}
	tree_num++;

	if (end_id == new_tree_id)					//방문마을이 목적지라면 함수종료
	{
	    return;
	}

	for (int i = 0; i < edge_list[new_t_idx].size(); i++)		//방문한 마을의 인접마을에 대해 확인하는 과정
	{
	    int check_id = edge_list[new_t_idx][i].second;		//확인중인 인접노드의 id 
	    int check_d = edge_list[new_t_idx][i].first;		//확인중인 인접노드와의 거리
	    int check_idx = find_node[check_id];			//확인중인 인접노드의 인덱스

	    if (len[check_id] > now_len + check_d && find_code[check_idx] == 0)		//확인중인 마을이 최단경로를 갱신할 대상인지 확인
	    {
		parent[check_id] = new_tree_id;						//최소경로를 갱신하기위해 그노드의 이전경로를 재설정
		len[check_id] = now_len + check_d;					//시작점으로부터의 최소거리를 갱신
		pq.push(make_pair(len[check_id], check_id));				//우선순위큐에 정보 입력
	    }
	}
    }

}

void init()							    //질문 1번이 끝난후 모든 노드별 거리 100만으로 초기화
{
    for (int i = 0; i < node_id.size(); i++)		
    {
	len[node_id[i]] = 1000000;
    }
    return;
}

void Atype_print()						    //A type 질문에 대한 결과 출력
{
    if (len[id2] > 100000)					    //결과값이 100000이상이라면 None을 출력한다
    {
	printf("None");
    }
    else							    //그렇지 않다면 해당 정보들을 출력한다
    {
	cout << tree_num << " " << len[id2] << " " << find_name[find_node[id1]] << " " << find_name[find_node[id2]] << " ";
    }
    return;
}

void Btype_print()						    //B type 질문에 대한 결과 출력
{
    if (len[id2] > 100000)					    //결과값이 100000이상이라면 None을 출력한다
    {
	printf("None");
    }
    else							    //그렇지 않다면 해당 정보들을 출력한다
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

void pq_clear()					//질문을 한번 마칠때마다 우선순위큐를 clear해준다
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

    for (int i = 0; i < node_num; i++)			    //각 노드정보 입력받기
    {
	cin >> id >> name >> code;			    
	find_node[id] = i;				    //해당 노드의 id와 index를 맵핑
	find_name[i] = name;				    //해당 노드의 index와 이름을 맵핑
	find_code[i] = code;				    //해당 노드의 index와 침수여부를 맵핑
	node_id.push_back(id);				    //모든 노드의 id를 저장
    }

    for (int i = 0; i < edge_num; i++)			    //각 edge의 정보를 입력받는다
    {
	cin >> id1 >> id2 >> length;

	int idx1 = find_node[id1];
	int idx2 = find_node[id2];

	edge_list[idx1].push_back(make_pair(length, id2));
	edge_list[idx2].push_back(make_pair(length, id1));
    }

    for (int i = 0; i < q_num; i++)			    //모든 세팅을 마친후 질문을 입력받고 그에 따른 결과를 출력한다
    {
	cin >> q >> id1 >> id2;
	int idx1 = find_node[id1];
	int idx2 = find_node[id2];
	tree_num = 0;

	init();						    //각 질문을 실행하기전 우선순위큐를 초기화한다

	if (q == 'A')
	{
	    if (find_code[idx1] == 1 || find_code[idx2] == 1)cout << "None" << " ";
	    else
	    {
		short_distance(id1, id2);
		Atype_print();			//질문type이 A일때 결과출력하는 함수 호출
	    }
	}
	else if (q == 'B')
	{
	    if (find_code[idx1] == 1 || find_code[idx2] == 1)cout << "None" << " ";
	    else
	    {
		short_path(id1, id2);
		Btype_print();			//질문type이 B일때 결과출력하는 함수 호출
	    }
	}
	cout << endl;
	pq_clear();
    }

    return 0;
}