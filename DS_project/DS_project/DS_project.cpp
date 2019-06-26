
#include "pch.h"
#include <iostream>
#include<vector>
#include<list>

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

};
int main()
{
	graph g(4);
	g.add_edge(3, 2, 4);
	g.add_edge(0, 1, 4);
	g.add_edge(1, 3, 4);
	g.add_edge(2, 1, 4);
	g.printList();
}
