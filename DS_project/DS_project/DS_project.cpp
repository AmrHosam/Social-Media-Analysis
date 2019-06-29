#include "pch.h"
#include <iostream>
#include<vector>
#include<list>
#include<queue>
#include<stack>

using namespace std;

class edge
{
private:
	int weight;
	int dest;
public:
	edge(int d, int w) {
		weight = w;
		dest = d;
	}
	void setWeight(int w) {
		weight = w;
	}
	void setDestination(int d) {
		dest = d;
	}
	int getWeight() {
		return weight;
	}
	int getDestination() {
		return dest;
	}
};
struct node {
public:
	list<edge> node_list;
	int edg_count=0;

};
class graph {
	
	vector<node> nodes;
public:
	graph(int vertices_num) {
		nodes.resize(vertices_num);
		
	}
	void add_edge(int a, int b, int weight) {
		edge n1(b, weight);
		nodes[a].node_list.push_back(n1);
		nodes[a].edg_count++;
		edge n2(a, weight);
		nodes[b].node_list.push_back(n2);
		nodes[b].edg_count++;
	}
	void printList()
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			list<edge>::iterator it;
			cout << " node{" << i << "}" << "has " << nodes[i].edg_count << " edges" << endl;
			for (it = nodes[i].node_list.begin(); it != nodes[i].node_list.end(); ++it){
				cout << " node{" << i << "} -> " << it->getDestination() << " with " << it->getWeight() << ",";
		      
		    }
			cout << endl;
		}
		cout << endl;
	}
	void dijkstra(int src, vector<int> &dist, vector<int> &parent)
	{
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > PQ;
		for(int i = 0; i < dist.size(); i++)
		{
			dist[i] = INT32_MAX;
			parent[i] = -1;
			if(i != src)
				PQ.push(make_pair(INT32_MAX,i));
		}
		dist[src] = 0;
		PQ.push(make_pair(0,src));
		while(!PQ.empty())
		{
			pair<int,int> mini;
			mini = PQ.top();
			int mini_n = mini.second;
			int mini_w = mini.first;
			PQ.pop();
			if(mini_w > dist[mini_n])
				continue;
			list<edge>::iterator it;
			for(it = nodes[mini_n].node_list.begin(); it != nodes[mini_n].node_list.end(); it++)
			{
				int w = it->getWeight();
				int n = it->getDestination();
				if(dist[n] > dist[mini_n] + w)
				{
					dist[n] = dist[mini_n] + w;
					parent[n] = mini_n;
					PQ.push(make_pair(dist[n], n));
				}
			}
		}
	}
	int Degree_Centrality_oneNode(int node) {
		return nodes[node].edg_count;
	}
	void Degree_Centrality_all() {
		for (int i = 0; i < nodes.size(); i++)
		{
			cout << "node[" << i << "]" << "  ->  " << "Degree_Centrality= " << nodes[i].edg_count << endl;
		}
	}
	float Closeness_centrality_oneNode(int root,int node_number) {
		
		int sum_shortest_dis=0;
		
		vector<int> distance(node_number);
		vector<int> parent(node_number);
		dijkstra(root, distance, parent);
		for (int i = 0; i < node_number; i++)
		{
			sum_shortest_dis += distance[i];
		}
		//cout << "sum_shortest_dis= " << sum_shortest_dis<<endl;
		return (float)(node_number - 1) /sum_shortest_dis;
	}
	void Closeness_centrality_all(int node_number) {
		for(int i = 0; i < nodes.size(); i++) {
		 cout<< "node[" << i << "]" << "  ->  "<<" Closeness_centrality= " << Closeness_centrality_oneNode(i, node_number)<<endl;		
		}
	}
	void closeness_centrality(vector<float> &centrality)
	{
		int vertices_no = nodes.size();
		vector<int> distance(vertices_no);
		vector<int> parent(vertices_no);
		int sum = 0;
		for(int i=0 ; i < vertices_no; i++)
		{
			dijkstra(i,distance,parent);
			for(int j=0; j < vertices_no; j++)
				sum += distance[j];
			centrality[i] = (vertices_no-1) / (float)sum;
			sum = 0;
		}
	}
	void modified_DFS(int src, int dest, vector< vector<int> > &parent, vector<int> &paths_no, vector<double> &centrallity)
	{
		stack<int> to_bo_visited;
		for(int i = 0 ; i < parent[dest].size(); i++)
			to_bo_visited.push(parent[dest][i]);
			while(!to_bo_visited.empty())
			{
				int x = to_bo_visited.top();
				to_bo_visited.pop();
				if(x != src)
				{
					centrallity[x] += paths_no[x]/(double)paths_no[dest];
					for(int i = 0 ; i < parent[x].size(); i++)
						to_bo_visited.push(parent[x][i]);
				}
			}
	}
	void modified_dijkstra(int src, vector<int> &dist, vector< vector<int> > &parent, vector<double> &centrallity)
	{
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > PQ;
		vector<int> paths_no(dist.size(),0);
		for(int i = 0; i < dist.size(); i++)
		{
			dist[i] = INT32_MAX;
			if(parent[i].size() != 1)
				parent[i].resize(1);
			parent[i][0] = -1;
			if(i != src)
				PQ.push(make_pair(INT32_MAX,i));
		}
		dist[src] = 0;
		paths_no[src] = 1;
		PQ.push(make_pair(0,src));
		while(!PQ.empty())
		{
			pair<int,int> mini;
			mini = PQ.top();
			int mini_n = mini.second;
			int mini_w = mini.first;
			PQ.pop();
			if(mini_w > dist[mini_n])
				continue;
			if(mini_n > src)
			{
				// if(src == 1 && mini_n == 2)
				// {
				// 	for(int i = 0 ; i < parent.size(); i++)
				// 	{
				// 		for(int j = 0; j < parent[i].size(); j++)
				// 		{
				// 			cout<<parent[i][j]<<"\t";
				// 		}
				// 		cout<<"\n";
				// 	}
				// }
				// else
					modified_DFS(src,mini_n,parent,paths_no,centrallity);
				//cout<<mini_n<<"\n";
			}
			list<edge>::iterator it;
			for(it = nodes[mini_n].node_list.begin(); it != nodes[mini_n].node_list.end(); it++)
			{
				int w = it->getWeight();
				int n = it->getDestination();
				if(dist[n] > dist[mini_n] + w)
				{
					paths_no[n] = paths_no[mini_n];
					dist[n] = dist[mini_n] + w;
					parent[n][0] = mini_n;
					PQ.push(make_pair(dist[n], n));
				}
				else if(dist[n] == dist[mini_n] + w)
				{
					paths_no[n] += paths_no[mini_n];
					parent[n].push_back(mini_n);
				}
			}
		}
		// for(int i=0; i < paths_no.size(); i++)
		// 	cout<<paths_no[i]<<"\t";
		// cout<<"\n";
	}
};
int main()
{
	int V ,n;
	// int x,y,z;
	// cin>>V>>n;
	graph g(V);
	vector<double> centrallity(V,0);
	vector<int> distance(V);
	vector<int> parent(V);
	vector< vector<int> > prev(V,vector<int> (1));
	// for(int i=0 ; i < n;i++)
	// {
	// 	cin>>x>>y>>z;
	// 	g.add_edge(x, y, z);
	// }
	g.add_edge(0, 1, 1);
	g.add_edge(0, 2, 1);
	g.add_edge(1, 3, 1);
	g.add_edge(2, 3, 1);
	g.add_edge(2, 4, 3);
	g.add_edge(3, 4, 1);
	g.printList();
	g.dijkstra(0,distance,parent);
	for(int i=0; i < V; i++)
		cout<<distance[i]<<"\t"<<parent[i]<<endl;
	g.Degree_Centrality_all();
	g.Closeness_centrality_all(V);
	for(int i = 0 ; i < V; i++)
		g.modified_dijkstra(i,distance,prev,centrallity);
	for(int i = 0; i < V; i++)
		cout<<centrallity[i]<<"\n";
	for(int i = 0 ; i < prev.size(); i++)
	{
		for(int j = 0; j < prev[i].size(); j++)
		{
			cout<<prev[i][j]<<"\t";
		}
		cout<<"\n";
	}
	
}
