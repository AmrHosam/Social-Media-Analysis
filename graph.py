import networkx as nx
import matplotlib.pyplot as plt
G=nx.Graph()
f = open("output.txt", "r")
c=[]
i = 0
for x in f:
    c.append([i,float(x[0:len(x)-1])])
    i = i + 1
f.close()
c = sorted(c,key=lambda c:c[1], reverse=True)
r = 0
g = 51
b = 102
colors = []
prev = -1
for x in c:
    if(prev != x[1] and prev != -1):
        r = int(r + 255/len(c))
        g = int(g + 204/len(c))
        b = int(b + 153/len(c))
    colors.append(str('#%02x%02x%02x' % (r, g, b)))
    prev = x[1]
    G.add_node(x[0])
#print(colors)
f = open("input.txt", "r")
f.readline()
for x in f:
    edge = x.split(" ")
    G.add_edge(int(edge[0]),int(edge[1]),weight=edge[2])
f.close()
a = list(G.nodes)
# print(a)
# print(G.nodes.data())
pos=nx.spring_layout(G)
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
#nx.draw_networkx_nodes(G,pos)
nx.draw(G,pos,node_color=colors, node_size=300, cmap=plt.cm.Blues, with_labels=True, font_weight='bold', font_color = 'red')
#nx.draw(G, with_labels=True, font_weight='bold')
#plt.savefig("path_graph1.png")
plt.show()