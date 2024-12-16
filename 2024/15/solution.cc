#include "../holiday/holiday.h"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

std::tuple<int, int, std::vector<std::string>, int, int, std::vector<std::string>, std::vector<std::string>> readFile(std::ifstream&);

void moveRobot(int&, int&, std::vector<std::string>&, std::vector<std::string>&);
void moveRobotUp(int&, int&, std::vector<std::string>&);
void moveRobotRight(int&, int&, std::vector<std::string>&);
void moveRobotDown(int&, int&, std::vector<std::string>&);
void moveRobotLeft(int&, int&, std::vector<std::string>&);

void moveWarehouseRobot(int&, int&, std::vector<std::string>&, std::vector<std::string>&);
void moveWarehouseRobotUp(int&, int&, std::vector<std::string>&);
void moveWarehouseRobotRight(int&, int&, std::vector<std::string>&);
void moveWarehouseRobotDown(int&, int&, std::vector<std::string>&);
void moveWarehouseRobotLeft(int&, int&, std::vector<std::string>&);

void helpMoveWareHouseRobot(int, int, int, std::vector<std::string>&);
long long calcGPSSum(std::vector<std::string>&);

bool checkIfMoveImpossible(int, int, int, std::vector<std::string>&);

int main()
{
    //std::ifstream in("test_small.txt");
    //std::ifstream in("test_large.txt");
    std::ifstream in("input.txt");
    auto [y, x, map, wy, wx, warehouseMap, commands] = readFile(in);
    in.close();

    moveRobot(y, x, map, commands);
    moveWarehouseRobot(wy, wx, warehouseMap, commands);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(15, out);
    out << "Part 1: " << calcGPSSum(map) << std::endl;
    out << "Part 2: " << calcGPSSum(warehouseMap) << std::endl;
    out.close();
}

long long calcGPSSum(std::vector<std::string>& map)
{
    long long gpsSum = 0;
    for (int y = 1; y < map.size()-1; y++)
        for (int x = 0; x < map[0].size()-1; x++)
            if (map[y][x] == 'O' || map[y][x] == '[')
                gpsSum += 100 * y + x;
    return gpsSum;
}

long long calcWarehouseGPSSum(std::vector<std::string>& map)
{
    int yt = map.size(),
        xt = map[0].size();

    long long gpsSum = 0;
    for (int y = 1; y < map.size()-1; y++)
        for (int x = 0; x < map[0].size()-1; x++)
            if (map[y][x] == 'O' || map[y][x] == '[')
                gpsSum += 100 * std::min(y, yt-y) + std::min(x, xt-x);
    return gpsSum;
}

void moveWarehouseRobot(int& y, int& x, std::vector<std::string>& map, std::vector<std::string>& commands)
{
    for (auto& line : commands)
    {
        for (char& ch : line)
        {
            switch (ch)
            {
                case '^':
                    moveWarehouseRobotUp(y, x, map);
                    break;
                case '>':
                    moveWarehouseRobotRight(y, x, map);
                    break;
                case 'v':
                    moveWarehouseRobotDown(y, x, map);
                    break;
                case '<':
                    moveWarehouseRobotLeft(y, x, map);
                    break;
            }
        }
    }
}

void moveWarehouseRobotUp(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y-1][x] == '#') return;
    if (map[y-1][x] == '.')
    {
        std::swap(map[y][x], map[y-1][x]);
        y--;
        return;
    }

    if (map[y-1][x] == '[' && checkIfMoveImpossible(y-1, x, -1, map)) return;
    else if (map[y-1][x-1] == '[' && checkIfMoveImpossible(y-1, x-1, -1, map)) return;

    if (map[y-1][x] == '[')
        helpMoveWareHouseRobot(y-1, x, -1, map);
    else
        helpMoveWareHouseRobot(y-1, x-1, -1, map);

    std::swap(map[y][x], map[y-1][x]);
    y--;
}

void moveWarehouseRobotDown(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y+1][x] == '#') return;
    if (map[y+1][x] == '.')
    {
        std::swap(map[y][x], map[y+1][x]);
        y++;
        return;
    }

    if (map[y+1][x] == '[' && checkIfMoveImpossible(y+1, x, 1, map)) return;
    else if (map[y+1][x-1] == '[' && checkIfMoveImpossible(y+1, x-1, 1, map)) return;

    if (map[y+1][x] == '[')
        helpMoveWareHouseRobot(y+1, x, 1, map);
    else
        helpMoveWareHouseRobot(y+1, x-1, 1, map);

    std::swap(map[y][x], map[y+1][x]);
    y++;
}

bool checkIfMoveImpossible(int y, int x, int dir, std::vector<std::string>& map)
{
    if (map[y+dir][x] == '#' || map[y+dir][x+1] == '#') return 1;
    if (map[y+dir][x] == '.' && map[y+dir][x+1] == '.') return 0;

    if (map[y+dir][x] == '[') return checkIfMoveImpossible(y+dir, x, dir, map);

    if (map[y+dir][x] == ']' && map[y+dir][x+1] == '[') return checkIfMoveImpossible(y+dir, x-1, dir, map) || checkIfMoveImpossible(y+dir, x+1, dir, map);
    if (map[y+dir][x] == ']') return checkIfMoveImpossible(y+dir, x-1, dir, map);
    if (map[y+dir][x+1] == '[') return checkIfMoveImpossible(y+dir, x+1, dir, map);

    return 0;
}

void helpMoveWareHouseRobot(int y, int x, int dir, std::vector<std::string>& map)
{
    if (map[y+dir][x] == '[') helpMoveWareHouseRobot(y+dir, x, dir, map);

    if (map[y+dir][x] == ']') helpMoveWareHouseRobot(y+dir, x-1, dir, map);
    if (map[y+dir][x+1] == '[') helpMoveWareHouseRobot(y+dir, x+1, dir, map);

    std::swap(map[y][x], map[y+dir][x]);
    std::swap(map[y][x+1], map[y+dir][x+1]);
}

void moveWarehouseRobotRight(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y][x+1] == '#') return;
    if (map[y][x+1] == '.')
    {
        std::swap(map[y][x], map[y][x+1]);
        x++;
        return;
    }

    int x2 = x+1;
    while (map[y][x2] == '[' || map[y][x2] == ']') x2++;
    if (map[y][x2] == '#') return;

    int i = 0, j = x2-x;
    for (; i < j; i++)
    {
        std::swap(map[y][x+i], map[y][x2]);
    }

    x++;
}

void moveWarehouseRobotLeft(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y][x-1] == '#') return;
    if (map[y][x-1] == '.')
    {
        std::swap(map[y][x], map[y][x-1]);
        x--;
        return;
    }

    int x2 = x-1;
    while (map[y][x2] == '[' || map[y][x2] == ']') x2--;
    if (map[y][x2] == '#') return;

    int i = 0, j = x-x2;
    for (; i < j; i++)
    {
        std::swap(map[y][x-i], map[y][x2]);
    }

    x--;
}

void moveRobot(int& y, int& x, std::vector<std::string>& map, std::vector<std::string>& commands)
{
    for (auto& line : commands)
    {
        for (char& ch : line)
        {
            switch (ch)
            {
                case '^':
                    moveRobotUp(y, x, map);
                    break;
                case '>':
                    moveRobotRight(y, x, map);
                    break;
                case 'v':
                    moveRobotDown(y, x, map);
                    break;
                case '<':
                    moveRobotLeft(y, x, map);
                    break;
            }
        }
    }
}

void moveRobotUp(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y-1][x] == '#') return;
    if (map[y-1][x] == '.')
    {
        std::swap(map[y][x], map[y-1][x]);
        y--;
        return;
    }

    int y2 = y-1;
    while (map[y2][x] == 'O') y2--;
    if (map[y2][x] == '#') return;

    int i = 0, j = y-y2;
    for (; i < j; i++)
    {
        std::swap(map[y-i][x], map[y2][x]);
    }

    y--;
}

void moveRobotRight(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y][x+1] == '#') return;
    if (map[y][x+1] == '.')
    {
        std::swap(map[y][x], map[y][x+1]);
        x++;
        return;
    }

    int x2 = x+1;
    while (map[y][x2] == 'O') x2++;
    if (map[y][x2] == '#') return;

    int i = 0, j = x2-x;
    for (; i < j; i++)
    {
        std::swap(map[y][x+i], map[y][x2]);
    }

    x++;
}

void moveRobotDown(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y+1][x] == '#') return;
    if (map[y+1][x] == '.')
    {
        std::swap(map[y][x], map[y+1][x]);
        y++;
        return;
    }

    int y2 = y+1;
    while (map[y2][x] == 'O') y2++;
    if (map[y2][x] == '#') return;

    int i = 0, j = y2-y;
    for (; i < j; i++)
    {
        std::swap(map[y+i][x], map[y2][x]);
    }

    y++;
}

void moveRobotLeft(int& y, int& x, std::vector<std::string>& map)
{
    if (map[y][x-1] == '#') return;
    if (map[y][x-1] == '.')
    {
        std::swap(map[y][x], map[y][x-1]);
        x--;
        return;
    }

    int x2 = x-1;
    while (map[y][x2] == 'O') x2--;
    if (map[y][x2] == '#') return;

    int i = 0, j = x-x2;
    for (; i < j; i++)
    {
        std::swap(map[y][x-i], map[y][x2]);
    }

    x--;
}

std::tuple<int, int, std::vector<std::string>, int, int, std::vector<std::string>, std::vector<std::string>> readFile(std::ifstream& in)
{
    std::vector<std::string> map, warehouseMap, commands;
    int y = -1, x,
        wy = -1, wx;

    std::string line;
    getline(in, line);
    while (line.length() != 0)
    {
        if (y == -1)
        {
            size_t found = line.find('@');
            if (found != std::string::npos)
            {
                x = found, y = map.size();
            }
        }

        map.push_back(line);
        getline(in, line);
    }

    while (getline(in, line))
    {
        commands.push_back(line);
    }

    for (std::string& row : map)
    {
        line = "";
        for (char& ch : row)
        {
            switch (ch)
            {
                case '#':
                    line += "##";
                    break;
                case '.':
                    line += "..";
                    break;
                case 'O':
                    line += "[]";
                    break;
                case '@':
                    line += "@.";
                    break;
            }
        }

        if (wy == -1)
        {
            size_t found = line.find('@');
            if (found != std::string::npos)
            {
                wx = found, wy = warehouseMap.size();
            }
        }

        warehouseMap.push_back(line);
    }

    return {y, x, map, wy, wx, warehouseMap, commands};
}
