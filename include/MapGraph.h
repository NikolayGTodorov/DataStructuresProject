#include <unordered_map>
#include <vector>
#include <map>
#include <fstream>

class MapGraph
{
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> map;

    std::pair<std::string, int> makeNeighbourPair(std::string pair);
    //friend std::ifstream &operator>>(std::ifstream &is, MapGraph& g);
    void fromLine(std::string& line, std::string& root, std::vector<std::pair<std::string,int>>& neighs);
    void deserializeFromFile(std::ifstream& is);
    void fillConectedCompsHelper(const int& currCompInx, const std::string &start, std::unordered_map<std::string, bool> &visited);
    void fillConectedComps();
public:
    std::map <int, std::vector<std::string>> connectedComps; 
    MapGraph(const std::string& fileName); //map <std::pair<string,string>, bool>
};

