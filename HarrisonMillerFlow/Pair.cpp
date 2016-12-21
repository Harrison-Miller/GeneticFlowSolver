#include "Pair.h"
#include <iostream>

Pair::Pair()
{
}

Pair::Pair(char name,
    Point a,
    Point b) :
    name(name),
    a(a),
    b(b)
{
}

bool Pair::isConnected()
{
    return path.size() > 1;

}

int Pair::getFilled()
{
    if(isConnected())
    {
        return path.size();

    }

    return 2; //the start and end nodes take up space no matter what

}

void Pair::print()
{
    std::cout << name << " -";
    for(int i = 0; i < path.size(); i++)
    {
        Point& p = path[i];
        //y, x order as asked by the problem description
        std::cout << " (" << p.y << ", " << p.x << ")";

    }

    std::cout << "\n";

}

bool Pair::operator==(const Pair& o)
{
    return name == o.name;

}

bool Pair::operator!=(const Pair& o)
{
    return name != o.name;

}
