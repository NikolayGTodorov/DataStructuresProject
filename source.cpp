#include <iostream>
#include "MapGraph.cpp"

int main(){
    std::ifstream is;
    is.open("test.txt");
    MapGraph m("test.txt");
    
    for (int i = 0; i < m.connectedComps.size(); i++)
    {
        for (auto &&u : m.connectedComps.at(i))
        {
            std::cout << u << ' ';
        }
        std::cout << '\n';
    }
    
    
    return 0;
}