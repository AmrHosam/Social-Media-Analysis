#include<iostream>
class edge
{
private:
    int weight;
    int dest;
public:
    void setWeight(int);
    void setDestination(int);
    int getWeight();
    int getDestination();
};