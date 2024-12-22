#include "../holiday/holiday.h"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

class RAM
{
private:
    int h, w, bytes;
    std::vector<std::vector<char>> memory;
    std::vector<std::pair<int, int>> excessBytes;
    std::vector<std::pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    bool isValid(int y, int x);
    void printRAM();
public:
    RAM(std::string, int, int, int);
    int shortestExitPath();
    std::string findByteThatPreventsExit();
};

int main()
{
    RAM r_input("input.txt", 70, 70, 1024);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(18, out);
    out << "Part 1: " << r_input.shortestExitPath() << std::endl;
    out << "Part 2: " << r_input.findByteThatPreventsExit() << std::endl;
    out.close();
}

std::string RAM::findByteThatPreventsExit()
{
    int i = 0;
    std::pair<int, int> b = excessBytes[i];
    memory[b.first][b.second] = '#';

    while (shortestExitPath() != INT32_MAX)
    {
        i++;
        b = excessBytes[i];
        memory[b.first][b.second] = '#';
    }

    return std::to_string(b.second) + ',' + std::to_string(b.first);
}

bool RAM::isValid(int y, int x)
{
    return (y >= 0 && x >= 0 && y <= h && x <= w && memory[y][x] != '#');
}

int RAM::shortestExitPath()
{
    std::vector<std::vector<int>> dp(h+1, std::vector<int>(w+1, INT32_MAX));
    std::vector<std::vector<bool>> visited(h+1, std::vector<bool>(w+1, 0));
    std::queue<std::pair<int, int>> q;

    q.push({0, 0});
    visited[0][0] = 1;
    dp[0][0] = 0;

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (auto& dir : directions)
        {
            int y2 = y + dir.first;
            int x2 = x + dir.second;

            if (isValid(y2, x2) && !visited[y2][x2])
            {
                dp[y2][x2] = std::min(dp[y2][x2], dp[y][x] + 1);
                q.push({y2, x2});
                visited[y2][x2] = 1;
            }
        }
    }

    return dp[h][w];
}

RAM::RAM(std::string s_map, int h, int w, int bytes)
    : h(h)
    , w(w)
    , bytes(bytes)
{
    std::vector<std::vector<char>> m_map(h+1, std::vector<char>(w+1, '.'));

    std::ifstream in(s_map);
    std::string line;
    int y , x, i = 0;
    while (getline(in, line))
    {
        x = std::stoi(line.substr(0, line.find(',')));
        y = std::stoi(line.substr(line.find(',') + 1));

        if (i < bytes)
            m_map[y][x] = '#';
        else
            excessBytes.push_back({y,x});

        i++;
    }

    memory = m_map;
    in.close();
}

void RAM::printRAM()
{
    for (auto& r : memory)
    {
        for (auto& c : r)
            std::cout << c << " ";
        std::cout << std::endl;
    }
}
