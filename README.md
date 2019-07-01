# Social-Media-Analysis
The project aims at applying algorithms based on graph theory to compute the centrality property for each node in the graph.
Definition of ‘central’ varies by context/purpose. However, the main aim is to give a score to each node. This score is used to determine the most important nodes in the graph. These techniques are used in social media analysis to determine the set of influencers out of a graph containing millions of users and connections.
Centrality has many definitions. Each definition gives scores to nodes in different ways.
You are asked to implement three centrality metrics on undirected connected graphs.

## Centrality in graphs

#### Degree Centrality
Degree centrality is the simplest centrality measure to compute. Recall that a node's degree is simply a count of how many social connections (i.e., edges) it has. The degree centrality for a node is simply its degree. A node with 10 social connections would have a degree centrality of 10. A node with 1 edge would have a degree centrality of 1.

#### Closeness Centrality
Closeness centrality indicates how close a node is to all other nodes in the network. It is calculated as the average of the shortest path length from the node to every other node in the network.
For a node x and a graph of N connected nodes, The centrality C(x) is defined as:

<a href="https://imgbb.com/"><img src="https://i.ibb.co/KVShvsH/Screenshot-from-2019-07-01-22-36-15.png" alt="Closeness-Formula" border="0"></a><br />
where d(y,x) is the shortest distance between node x and all other nodes y that are connected to it.

#### Betweenness Centrality
Betweenness centrality measures the number of times a node lies on the shortest path between other nodes.
According to wikipedia:

<a href="https://imgbb.com/"><img src="https://i.ibb.co/71VBgn0/Betweenness-Formula.png" alt="Betweenness-Formula" border="0"></a>
<br><br>
<hr>

### Team Members:

Code          | Name	     | Section
------------- | -------------| -------------
1500913  | Omar Fathy | 2
1500948  | Amr Hossam | 2
