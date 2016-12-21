#include "Point.h"

Point::Point() :
    x(0),
    y(0)
{
}

Point::Point(int x,
    int y) :
    x(x),
    y(y)
{
}

bool Point::operator==(const Point& o)
{
    return x == o.x && y == o.y;

}

bool Point::operator!=(const Point& o)
{
    return x != o.x || y != o.y;

}

