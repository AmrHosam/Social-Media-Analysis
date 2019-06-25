#include"edge.h"
void edge::setWeight(int w)
{
    weight = w;
}
void edge::setDestination(int n)
{
    dest = n;
}
int edge::getWeight()
{
    return weight;
}
int edge::getDestination()
{
    return dest;
}