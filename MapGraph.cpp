#include "include/MapGraph.h"
#include <exception>
#include <queue>
#include <iostream>

size_t find_nth(const std::string &haystack, size_t pos, const std::string &needle, size_t nth)
{
    size_t foundPos = haystack.find(needle, pos);
    if (0 == nth || std::string::npos == foundPos)
        return foundPos;
    return find_nth(haystack, foundPos + 1, needle, nth - 1);
}

std::pair<std::string, int> MapGraph::makeNeighbourPair(std::string pair)
{
    std::string first = pair.substr(0, pair.find(' '));
    map[first].clear();
    pair.erase(0, pair.find(' ') + 1);
    // neighs[neighsIndex++].second = std::stoi(currPair);
    int second = std::stoi(pair);

    return std::make_pair(first, second);
}

void MapGraph::fromLine(std::string &line, std::string &root, std::vector<std::pair<std::string, int>> &neighs)
{
    root = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);

    while (find_nth(line, 0, " ", 1) != std::string::npos)
    {
        int secondWhiteSpacePos = find_nth(line, 0, " ", 1);

        std::string currPair = line.substr(0, secondWhiteSpacePos);
        neighs.push_back(std::move(makeNeighbourPair(currPair)));
        line.erase(0, secondWhiteSpacePos + 1);
    }
    neighs.push_back(std::move(makeNeighbourPair(line)));
}

void MapGraph::deserializeFromFile(std::ifstream &is)
{
    std::string line;
    std::string root;
    std::vector<std::pair<std::string, int>> neighs;
    while (std::getline(is, line))
    {
        neighs.clear();
        fromLine(line, root, neighs);
        map[root] = neighs;
    }
}

void MapGraph::fillConectedCompsHelper(const int &currCompInx, const std::string &start, std::unordered_map<std::string, bool> &visited)
{
    std::queue<std::string> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty())
    {
        std::string curr = q.front();
        q.pop();

        connectedComps[currCompInx].push_back(curr);

        for (auto &&i : map.at(curr))
        {
            if (!visited[i.first])
            {
                q.push(i.first);
                visited[i.first] = true;
            }
        }
    }
}

void MapGraph::fillConectedComps()
{
    std::unordered_map<std::string, bool> visited;
    int currCompIndx = 0;
    for (auto &&i : map)
    {
        if (!visited[i.first])
        {
            fillConectedCompsHelper(currCompIndx, i.first,visited);
            currCompIndx++;
        }
    }
}

MapGraph::MapGraph(const std::string &fileName)
{
    std::ifstream is;
    is.open(fileName);
    if (!is)
    {
        throw std::logic_error("Invalid file, couldn't open it");
    }
    deserializeFromFile(is);
    fillConectedComps();
}