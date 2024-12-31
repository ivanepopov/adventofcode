#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Network {
    private:
        std::set<std::set<std::string>> c2x;
        std::set<std::set<std::string>> c3x;
        std::set<std::string> pw;
        std::unordered_map<std::string, std::unordered_set<std::string>> mp;

        void find3XConnections();
        void findMaxConnection();

        int tryFindHistorian();
        std::string findPassword();
    public:
        Network(std::string);
        void print();
};

int main()
{
    Network network("input.txt");
    network.print();
}

void Network::print()
{
    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(23, out);
    out << "Part 1: " << tryFindHistorian() << std::endl;
    out << "Part 2: " << findPassword() << std::endl;
    out.close();
}

std::string Network::findPassword()
{
    std::string password;
    for (auto& c : pw) password += (c + ',');
    password.erase(password.length()-1);
    return password;
}

void Network::find3XConnections()
{
    for (auto& c2 : c2x)
    {
        auto pc1 = c2.begin();
        auto pc2 = pc1++;

        for (auto& pc3 : mp[*pc1])
        {
            if (mp[*pc2].find(pc3) != mp[*pc2].end())
                c3x.insert({*pc1, *pc2, pc3});
        }
    }
}

void Network::findMaxConnection()
{
    std::set<std::set<std::string>> maxConnection = c3x, curr;
    bool fail;

    while (true)
    {
        curr.clear();
        for (const auto & conn : maxConnection)
        {
            for (const auto& [pc, pcs] : mp)
            {
                if (pcs.size() < conn.size()) continue;
                fail = false;

                for (const auto c_pc : conn)
                    if (mp[pc].find(c_pc) == mp[pc].end()) { fail = true; break; }

                if (!fail)
                {
                    auto newconn = conn;
                    newconn.insert(pc);
                    curr.insert(newconn);
                }
            }
        }
        if (curr.empty()) break;
        maxConnection = curr;
    }
    pw = *maxConnection.begin();
}

int Network::tryFindHistorian()
{
    int count = 0;
    for (auto& c3 : c3x) for (auto& c : c3) if (c[0] == 't') { count++; break; }
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

        mp[c1].insert(c2);
        mp[c2].insert(c1);
        c2x.insert({c1, c2});
    }

    find3XConnections();
    findMaxConnection();

    in.close();
}
