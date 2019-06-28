#include "pch.h"
#include <iostream>
#include<vector>
#include<list>
#include<queue>

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
};
int main()
{
	int V = 4;
	graph g(V);
	vector<int> distance(V);
	vector<int> parent(V);
	g.add_edge(0, 1, 1);
	g.add_edge(0, 3, 5);
	g.add_edge(0, 2, 10);
	g.add_edge(1, 3, 1);
	g.add_edge(2, 3, 4);
	g.printList();
	g.dijkstra(0,distance,parent);
	for(int i=0; i < V; i++)
		cout<<distance[i]<<"\t"<<parent[i]<<endl;
	g.Degree_Centrality_all();
	g.Closeness_centrality_all(V);
}
