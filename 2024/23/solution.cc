#include "../holiday/holiday.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct connection_2x {
    std::string c1;
    std::string c2;

    bool operator==(const connection_2x& c) const {
        return c1 == c.c1 && c2 == c.c2;
    }
};

struct connection_2x_hash {
    std::size_t operator()(const connection_2x& c) const {
        std::size_t h1 = std::hash<std::string>()(c.c1);
        std::size_t h2 = std::hash<std::string>()(c.c2);
        return h1 ^ (h2 << 1);
    }
};

struct connection_3x {
    std::string c1;
    std::string c2;
    std::string c3;

    bool operator==(const connection_3x& other) const {
        return c1 == other.c1 && c2 == other.c2 && c3 == other.c3;
    }
};

struct connection_3x_hash {
    std::size_t operator()(const connection_3x& c) const {
        std::size_t h1 = std::hash<std::string>()(c.c1);
        std::size_t h2 = std::hash<std::string>()(c.c2);
        std::size_t h3 = std::hash<std::string>()(c.c3);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class Network {
    private:
       std::unordered_set<connection_2x, connection_2x_hash> connections;

       std::unordered_set<connection_3x, connection_3x_hash> find3XConnections();
    public:
        Network(std::string);
        int tryFindHistorian();
};

int main()
{
    Network network("input.txt");

    std::cout << network.tryFindHistorian() << std::endl;
}

std::unordered_set<connection_3x, connection_3x_hash> Network::find3XConnections()
{
    std::unordered_set<connection_3x, connection_3x_hash> c3x;
    std::unordered_map<std::string, std::unordered_set<std::string>> mp;

    for (auto& c : connections)
    {
        for (auto& pair : mp[c.c1])
            if (mp[c.c2].find(pair) != mp[c.c2].end())
                c3x.insert({c.c1, c.c2, pair});

        mp[c.c1].insert(c.c2);
        mp[c.c2].insert(c.c1);
    }

    return c3x;
}

int Network::tryFindHistorian()
{
    std::unordered_set<connection_3x, connection_3x_hash> c3x = find3XConnections();

    int count = 0;
    for (auto& c : c3x) if (c.c1[0] == 't' || c.c2[0] == 't' || c.c3[0] == 't') count++;
    return count;
}

Network::Network(std::string file)
{
    std::ifstream in(file);

    std::string line, c1, c2;
    while (in >> line)
    {
        c1 = line.substr(0, 2);
        c2 = line.substr(3);
        connections.insert({c1, c2});
    }

    in.close();
}
