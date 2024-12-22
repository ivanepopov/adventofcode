#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

typedef long long ll;

std::tuple<std::unordered_set<std::string>, std::unordered_set<std::string>> readFile(std::string);
std::tuple<ll, ll> checkTowels(std::unordered_set<std::string>&, std::unordered_set<std::string>&);

int main()
{
    auto [patterns, towels] = readFile("input.txt");
    auto [valid, total] = checkTowels(patterns, towels);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(19, out);
    out << "Part 1: " << valid << std::endl;
    out << "Part 2: " << total << std::endl;
    out.close();
}

std::tuple<ll, ll> checkTowels(std::unordered_set<std::string>& patterns, std::unordered_set<std::string>& towels)
{
    ll validTowels = 0, totalTowels = 0, tl, n;
    std::vector<long long> dp;

    for (auto& towel : towels)
    {
        n = towel.size();
        dp.assign(n+1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (auto& pattern : patterns)
            {
                tl = pattern.size();
                if (i >= tl && towel.substr(i - tl, tl) == pattern)
                    dp[i] += dp[i - tl];
            }
        }

        if (dp[n] > 0) validTowels += 1;
        totalTowels += dp[n];
    }

    return {validTowels, totalTowels};
}

std::tuple<std::unordered_set<std::string>, std::unordered_set<std::string>> readFile(std::string file)
{
    std::unordered_set<std::string> patterns, towels;

    std::ifstream in(file);

    std::string line;
    getline(in, line);
    std::stringstream ss(line);
    while (getline(ss, line, ','))
    {
        if (line[0] == ' ') line.erase(0, 1);
        patterns.insert(line);
    }

    getline(in, line);
    while (getline(in, line))
        towels.insert(line);

    in.close();

    return {patterns, towels};
}
