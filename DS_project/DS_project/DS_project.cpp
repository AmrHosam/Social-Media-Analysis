#include "pch.h"
#include <iostream>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include <iomanip>
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
	void dijkstra(int src, vector<int> &dist)
	{
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > PQ;
		for(int i = 0; i < dist.size(); i++)
		{
			dist[i] = INT32_MAX;//infinty intial lel src
			if(i != src)//law m4 el src 7ot el periorty queue b infity brdo 
				PQ.push(make_pair(INT32_MAX,i));
		}
		dist[src] = 0; //dis from root to root 
		PQ.push(make_pair(0,src));//7atna brdo el src fel pq 
		while(!PQ.empty())
		{
			pair<int,int> mini;
			mini = PQ.top();//3a4n awl elment f el pq byb2a as8r wa7d f awl mra hyb2a el src
			int mini_n = mini.second;//n hna e5tsar l number
			int mini_w = mini.first;//w e5tsar l weight
			PQ.pop();//4elha b3d ma 3mltlha discover
			if(mini_w > dist[mini_n])
				continue;
			list<edge>::iterator it;
			for(it = nodes[mini_n].node_list.begin(); it != nodes[mini_n].node_list.end(); it++)//discover ely gwa el linked list
			{
				int w = it->getWeight();
				int n = it->getDestination();
				if(dist[n] > dist[mini_n] + w)
				{
					dist[n] = dist[mini_n] + w;
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
			cout<<nodes[i].edg_count<<"\n";
		}
	}
	float Closeness_centrality_oneNode(int root,int node_number) {
		
		int sum_shortest_dis=0;
		
		vector<int> distance(node_number);
		dijkstra(root, distance);
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
	void improve_dijkstra(int src, vector<int> &dist, vector<int> &parent,vector<vector<int>> &multiparent)
	{
		vector<int> path_no(parent.size(),0);
		int flagcount = 0;
		for (int i = 0; i < multiparent.size(); i++)
		{
			multiparent[i].push_back(-1);
		}
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > PQ;
		for (int i = 0; i < dist.size(); i++)
		{
			dist[i] = INT32_MAX;//infinty intial lel src
			parent[i] = -1;//how to know the root has parent -1
			if (i != src)//law m4 el src 7ot el periorty queue b infity brdo 
				PQ.push(make_pair(INT32_MAX, i));
		}
		dist[src] = 0; //dis from root to root 
		path_no[src] = 1;
		PQ.push(make_pair(0, src));//7atna brdo el src fel pq 
		while (!PQ.empty())
		{
			pair<int, int> mini;
			mini = PQ.top();//3a4n awl elment f el pq byb2a as8r wa7d f awl mra hyb2a el src
			int mini_n = mini.second;//n hna e5tsar l number
			int mini_w = mini.first;//w e5tsar l weight
			PQ.pop();//4elha b3d ma 3mltlha discover
			if (mini_w > dist[mini_n])
				continue;
			list<edge>::iterator it;
			for (it = nodes[mini_n].node_list.begin(); it != nodes[mini_n].node_list.end(); it++)//discover ely gwa el linked list
			{
				int w = it->getWeight();
				int n = it->getDestination();
				if (dist[n] > dist[mini_n] + w)
				{
					path_no[n] = path_no[mini_n];
					dist[n] = dist[mini_n] + w;
					parent[n] = mini_n;
					PQ.push(make_pair(dist[n], n));
				}
				else if (dist[n] == dist[mini_n] + w)
				{
					path_no[n] = path_no[mini_n]+1;
					if (multiparent[n].front() == -1)
					{
						multiparent[n].front() = mini_n;
					}
					else { multiparent[n].push_back(mini_n); }
					flagcount++;
				}
			
			}
		}
		for (int i = 0; i < multiparent.size(); i++)
		{
			if (multiparent[i][0] == -1)
			{
				multiparent[i][0] = parent[i];
			}
			else
				multiparent[i].push_back(parent[i]);
			
		}
		if (flagcount == 0) { cout << "it just one shortest path"; }
		else
		{


			for (int i = 0; i < parent.size(); i++)
			{
				for (int j = 0; j < multiparent[i].size(); j++)
				{
					if (multiparent[i].size() >1) {
						cout << "\t" << multiparent[i][j] << "  or  ";
					}
					else
					cout << endl  << "\t" << multiparent[i][0] << endl;
				}
				
			}
		}
	}
	void closeness_centrality(vector<double> &centrality)
	{
		int vertices_no = nodes.size();
		vector<int> distance(vertices_no);
		int sum = 0;
		for(int i=0 ; i < vertices_no; i++)
		{
			dijkstra(i,distance);
			for(int j=0; j < vertices_no; j++)
				sum += distance[j];
			centrality[i] = (vertices_no-1) / (double)sum;
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
				modified_DFS(src,mini_n,parent,paths_no,centrallity);
			list<edge>::iterator it;
			for(it = nodes[mini_n].node_list.begin(); it != nodes[mini_n].node_list.end(); it++)
			{
				int w = it->getWeight();
				int n = it->getDestination();
				if(dist[n] > dist[mini_n] + w)
				{
					if(parent[n].size() != 1)
						parent[n].resize(1);
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
	}
};
int main()
{
	int V=5 ,n;
	int x,y,z;
	cin>>V>>n;
	graph g(V);
	for(int i=0 ; i < n;i++)
	{
		cin>>x>>y>>z;
		g.add_edge(x, y, z);
	}


	//digree centrality
	//g.Degree_Centrality_all();



	//Closeness Centrality
	// vector<double> centrallity(V,0);
	// g.closeness_centrality(centrallity);
	// for(int i=0; i < centrallity.size(); i++)
	// 	cout<<setprecision(12)<<centrallity[i]<<"\n";



	// vector<double> centrallity(V,0);
	// vector<int> distance(V);
	// vector< vector<int> > prev(V,vector<int> (1));
	// for(int i = 0 ; i < V; i++)
	// 	g.modified_dijkstra(i,distance,prev,centrallity);
	// for(int i = 0; i < V; i++)
	// 	cout<<setprecision(12)<<centrallity[i]<<"\n";
}
