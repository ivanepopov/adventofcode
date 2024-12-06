#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../holiday/holiday.h"

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
};

int numDistinctPositions(std::unordered_map<int, std::unordered_set<int>>& distinct)
{
    int res = 1;
    for (auto& [y, set] : distinct)
        for (const int& x : set)
            res++;
    return res;
}

std::unordered_map<int, std::unordered_set<int>> getDistinctPositions(int y, int x, int dir, std::vector<std::vector<char>>& map)
{
    int infloop = 0;
    std::unordered_map<int, std::unordered_set<int>> distinct;
    std::unordered_map<int, std::unordered_set<int>> infinite; infinite[0] = {0};

    while (x < 130 && y < 130 && x > -1 && y > -1)
    {
        if (infloop > 7500) { return infinite; }

        if (distinct[y].find(x) != distinct[y].end());
        else if (map[y][x] == '#')
        {
            switch (dir)
            {
                case NORTH: { y++; break; }
                case EAST:  { x--; break; }
                case SOUTH: { y--; break; }
                case WEST:  { x++; break; }
            }
            dir++;
        }
        else if (map[y][x] == '.')
        {
            map[y][x] = 'X';
            distinct[y].insert(x);
        }

        dir %= 4;
        switch (dir)
        {
            case NORTH: { y--; break; }
            case EAST:  { x++; break; }
            case SOUTH: { y++; break; }
            case WEST:  { x--; break; }
        }
        infloop++;
    }
    return distinct;
}

int numObstructionPositions(int startY, int startX, std::vector<std::vector<char>>& map, std::unordered_map<int, std::unordered_set<int>>& distinct)
{
    int res = 0;
    for (auto& [y, set] : distinct)
    {
        for (const int& x : set)
        {
            map[y][x] = '#';
            if (getDistinctPositions(startY, startX, NORTH, map).size() == 1) res++;
            map[y][x] = 'X';
        }
    }
    return res;
}

int main()
{
    std::ifstream in("input.txt");

    std::vector<std::vector<char>> map(130, std::vector<char>(130, '.'));
    std::unordered_map<int, std::unordered_set<int>> distinct;
    std::string line;

    int row = 0;
    int startX, startY;
    while (getline(in, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '#') map[row][i] = '#';
            else if (line[i] == '^')
            {
                map[row][i] = 'X';
                startX = i; startY = row;
            }
        }
        row++;
    }
    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(6, out);
    distinct = getDistinctPositions(startY, startX, NORTH, map);
    out << "Part 1: " << numDistinctPositions(distinct) << std::endl;
    out << "Part 2: " << numObstructionPositions(startY, startX, map, distinct) << std::endl;
    out.close();
}
