#include "AdjMatrix.h"
#include <iostream> //cout
#include <iomanip> //setw

AdjMatrix::AdjMatrix() :
    width(0),
    height(0)
{
}

AdjMatrix::AdjMatrix(int width,
    int height) :
    width(width),
    height(height)
{
    int size = width*height;
    //initialize all values of the adj matrix and set them to -1.
    for(int i = 0; i < size; i++)
    {
        std::vector<int> nums;
        for(int j = 0; j < size; j++)
        {
            nums.push_back(-1);

        }

        data.push_back(nums);

    }

    //make basic grid connections
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Point p(j, i);

            Point up(p.x, p.y-1);
            Point down(p.x, p.y+1);
            Point left(p.x-1, p.y);
            Point right(p.x+1, p.y);

            //checks if the new point is valid then sets the connection to 1
            set(p, up, 1);
            set(p, down, 1);
            set(p, left, 1);
            set(p, right, 1);

        }

    }

}

int AdjMatrix::getSize()
{
    return width*height;

}

int AdjMatrix::indexOf(Point p)
{
    //flattens a point to an index
    return p.y*width + p.x;

}

Point AdjMatrix::pointFrom(int index)
{
    //unflattens an index into a point in the grid
    return Point(index%width, index/width);

}

bool AdjMatrix::set(Point from,
    Point to,
    int w)
{
    if(from.x >= 0 && from.x < width
        && from.y >= 0 && from.y < height
        && to.x >= 0 && to.x < width
        && to.y >= 0 && to.y < height)
    {
        int fromIndex = indexOf(from);
        int toIndex = indexOf(to);

        if(w == 0) //don't bother setting it we don't want 0
        {
            return true;

        }

        data[fromIndex][toIndex] = w;
        return true;

    }

    return false;

}

void AdjMatrix::exclude(Point p)
{
    Point up(p.x, p.y-1);
    Point down(p.x, p.y+1);
    Point left(p.x-1, p.y);
    Point right(p.x+1, p.y);

    set(up, p, -1);
    set(down, p, -1);
    set(left, p, -1);
    set(right, p, -1);

}

void AdjMatrix::print()
{
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++)
        {
            if(data[i][j] < 0)
            {
                std::cout << std::setw(3) << ".";

            }
            else
            {
                std::cout << std::setw(3) << data[i][j];

            }

        }

        std::cout << "\n";

    }

}
