#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int checkAround(
        int i, int j, char val,
        std::vector<std::vector<char>>& map,
        std::vector<std::vector<int>>& dp,
        std::unordered_map<int, std::unordered_set<int>>& us
        )
{
    if (i < 0 || i >= map.size() || j < 0 || j >= map[0].size()) return 0;
    if (map[i][j] != (val + 1)) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (map[i][j] == '9')
    {
        if (us[i].find(j) != us[i].end()) return 0;
        us[i].insert(j);
        return 1;
    }

    return
        checkAround(i-1, j, map[i][j], map, dp, us)
        + checkAround(i, j-1, map[i][j], map, dp, us)
        + checkAround(i, j+1, map[i][j], map, dp, us)
        + checkAround(i+1, j, map[i][j], map, dp, us);
}


int checkDistinctAround(
        int i, int j, char val,
        std::vector<std::vector<char>>& map,
        std::vector<std::vector<int>>& dp
        )
{
    if (i < 0 || i >= map.size() || j < 0 || j >= map[0].size()) return 0;
    if (map[i][j] != (val + 1)) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (map[i][j] == '9') return 1;

    return
        checkDistinctAround(i-1, j, map[i][j], map,dp)
        + checkDistinctAround(i, j-1, map[i][j], map, dp)
        + checkDistinctAround(i, j+1, map[i][j], map, dp)
        + checkDistinctAround(i+1, j, map[i][j], map, dp);
}

int trailheadScoreCount(std::vector<std::vector<char>>& map)
{
    int res = 0;
    size_t n = map.size(), m = map[0].size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (map[i][j] != '0') continue;
            std::unordered_map<int, std::unordered_set<int>> us;
            dp[i][j] = checkAround(i, j, map[i][j]-1, map, dp, us);
            res += dp[i][j];
        }
    }

    return res;
}

int trailheadDistinctScoreCount(std::vector<std::vector<char>>& map)
{
    int res = 0;
    size_t n = map.size(), m = map[0].size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            dp[i][j] = checkDistinctAround(i, j, map[i][j]-1, map, dp);
            if (map[i][j] == '0') res += dp[i][j];
        }
    }

    return res;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::vector<char>> map;
    std::vector<char> maprow;
    while (getline(in, line))
    {
        for (char& c : line) maprow.push_back(c);
        map.push_back(maprow);
        maprow.clear();
    }
    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(10, out);
    out << "Part 1: " << trailheadScoreCount(map) << std::endl;
    out << "Part 2: " << trailheadDistinctScoreCount(map) << std::endl;
    out.close();
}
