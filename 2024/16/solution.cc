#include "../holiday/holiday.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <vector>

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct dir {
    int dy, dx;
} dirs[4] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

struct coor {
    int y, x;
};

struct pos {
    int y, x, cost, d;
    std::list<struct coor> path;
};

std::vector<std::string> readFile(std::ifstream&);
std::tuple<int, int> runReindeerRun(std::vector<std::string>&);

int main()
{
    std::ifstream in("input.txt");

    std::vector<std::string> map = readFile(in);
    auto [minCost, tileCount] = runReindeerRun(map);

    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(16, out);
    out << "Part 1: " << minCost << std::endl;
    out << "Part 2: " << tileCount << std::endl;
    out.close();
}

std::tuple<int, int> runReindeerRun(std::vector<std::string>& map)
{
    int y = map.size()-2,
        x = 1;

    std::vector<std::vector<int>> v(map.size(), std::vector<int>(map[0].size(), INT32_MAX));
    v[y][x] = 0;

    int minCost = INT32_MAX;

    std::list<struct pos> newpos;
    std::list<struct pos> pos;
    std::list<struct pos> reached_end;
    struct pos start = { y, x, 0, EAST, {} };

    start.path.push_back({y,x});
    pos.push_back(start);

    while (!pos.empty())
    {
        for (auto p : pos)
        {
            if (v[p.y][p.x] < p.cost - 1000) continue;
            v[p.y][p.x] = p.cost;

            if (map[p.y][p.x] == 'E')
            {
                if (p.cost < minCost) minCost = p.cost;
                reached_end.push_back(p);
                continue;
            }

            int ny, nx, nd;

            p.path.push_back({0,0});

            nd = p.d;
            ny = p.y + dirs[nd].dy;
            nx = p.x + dirs[nd].dx;
            if (map[ny][nx] != '#') {
                p.path.pop_back();
                p.path.push_back({ny,nx});
                newpos.push_back({ny,nx,p.cost+1,nd,p.path});
            }

            nd = (p.d-1)&3;
            ny = p.y + dirs[nd].dy;
            nx = p.x + dirs[nd].dx;
            if (map[ny][nx] != '#') {
                p.path.pop_back();
                p.path.push_back({ny,nx});
                newpos.push_back({ny,nx,p.cost+1001,nd,p.path});
            }

            nd = (p.d+1)&3;
            ny = p.y + dirs[nd].dy;
            nx = p.x + dirs[nd].dx;
            if (map[ny][nx] != '#') {
                p.path.pop_back();
                p.path.push_back({ny,nx});
                newpos.push_back({ny,nx,p.cost+1001,nd,p.path});
            }
        }
        pos.clear();
        pos.swap(newpos);
    }

    int tileCount = 0;
    for (auto p : reached_end)
    {
        if (p.cost != minCost) continue;
        for (auto c : p.path)
        {
            if (map[c.y][c.x] != 'O') tileCount++;
            map[c.y][c.x] = 'O';
        }
    }


    return {minCost, tileCount};
}

std::vector<std::string> readFile(std::ifstream& in)
{
    std::vector<std::string> map;
    std::string line;
    while (getline(in, line)) map.push_back(line);
    return map;
}
