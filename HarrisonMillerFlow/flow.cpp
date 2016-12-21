#include "Solver.h"
#include <iostream>
#include <vector>

int main(int argc,
    char** argv)
{
    std::vector<std::vector<char> > gridData;
    std::string line;
    int y = 0;

    bool debug = false;
    for(int i = 0; i < argc; i++)
    {
        std::string option = argv[i];
        if(option == "-d")
        {
            debug = true;

        }

    }

    while(std::getline(std::cin, line))
    {
        std::string chars("_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        if(line.find_first_of(chars) == std::string::npos)
        {
            break;

        }

        gridData.push_back(std::vector<char>());

        int x = 0;
        for(int i = 0; i < line.size(); i++)
        {
            if(chars.find(line[i]) == std::string::npos)
                continue;

            gridData[y].push_back(line[i]);

            x++;
        
        }

        y++;

    }

    if(!(gridData.size() > 0))
    {
        std::cout << "grid is to small\n";
        return 0;

    }

    int width = gridData.size();
    int height = gridData[0].size();
    //std::cout << width << " by " << height << "\n";

    std::vector<Pair> pairs;
    for(int i = 0; i < gridData.size(); i++)
    {
        for(int j = 0; j < gridData.size(); j++)
        {
            char name = gridData[i][j];
            if(name != '_')
            {
                bool found = false;
                for(int k = 0; k < pairs.size(); k++)
                {
                    if(pairs[k].name == name)
                    {
                        pairs[k].b = Point(j, i);
                        found = true;
                        break;

                    }

                }

                if(!found)
                {
                    Pair pair(name, Point(j, i), Point(0, 0));
                    pairs.push_back(pair);

                }

            }

        }

    }

    Solver solver(width, height, pairs);
    solver.debug = debug;
    solver.solve();
    solver.print();

    return 0;

}
