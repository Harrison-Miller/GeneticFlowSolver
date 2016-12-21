#ifndef POINT_H_
#define POINT_H_

/*
Simple 2d integer point class.
*/
class Point
{
public:
    Point();

    Point(int x,
        int y);

    bool operator==(const Point& o);

    bool operator!=(const Point& o);

    int x;
    int y;

};

#endif /*POINT*/
