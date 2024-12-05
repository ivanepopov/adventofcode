#include "../holiday/holiday.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main()
{
    std::ifstream in("input.txt");

    std::string line;
    int key, correctUpdates = 0, fixedUpdates = 0;
    std::unordered_map<int, std::unordered_set<int>> mp;

    while (getline(in, line))
    {
        if (line.length() == 0) break;

        std::stringstream ss(line);
        getline(ss, line, '|');
        key = std::stoi(line);

        getline(ss, line, '|');
        mp[key].insert(std::stoi(line));
    }

    std::vector<int> v; bool fail;
    while (getline(in, line))
    {
        std::stringstream ss(line);
        while (getline(ss, line, ',')) v.push_back(std::stoi(line));

        fail = false;
        for (int i = 1; i < v.size(); i++)
        {
            for (int j = i-1; j >= 0; j--)
            {
                if (mp[v[i]].find(v[j]) != mp[v[i]].end())
                {
                    std::rotate(v.begin()+j, v.begin()+i, v.begin()+i+1);
                    i = j;
                    fail = true;
                }
            }
        }

        if (!fail) correctUpdates += v[v.size()/2];
        else fixedUpdates += v[v.size()/2];

        v.clear();
    }
    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(5, out);
    out << "Part 1: " << correctUpdates << std::endl;
    out << "Part 2: " << fixedUpdates << std::endl;
    out.close();
}
