#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<char>> readFile();
int partOneFencing(std::vector<std::vector<char>>&);
int partTwoFencing(std::vector<std::vector<char>>&);
int createRegion(int, int, bool, std::vector<std::vector<char>>&, std::vector<std::vector<bool>>&);
int checkAllAdjacent(char, int, int, int&, std::vector<std::vector<char>>&, std::vector<std::vector<bool>>&);
void checkAllAdjacentForCorners(char, int, int, int&, int&, std::vector<std::vector<char>>&, std::vector<std::vector<bool>>&);
int checkAdjacent(char, int, int, int&, std::vector<std::vector<char>>&, std::vector<std::vector<bool>>&);
int checkAdjacentForCorner(char, int, int, int&, int&, std::vector<std::vector<char>>&, std::vector<std::vector<bool>>&);

int main()
{
    std::vector<std::vector<char>> map = readFile();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(12, out);
    out << "Part 1: " << partOneFencing(map) << std::endl;
    out << "Part 2: " << partTwoFencing(map) << std::endl;
    out.close();
}

int partOneFencing(std::vector<std::vector<char>>& map)
{
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), 0));
    int fencingPrice = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (visited[i][j]) continue;
            fencingPrice += createRegion(i, j, 0, map, visited);
        }
    }
    return fencingPrice;
}

int partTwoFencing(std::vector<std::vector<char>>& map)
{
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), 0));
    int fencingPrice = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (visited[i][j]) continue;
            fencingPrice += createRegion(i, j, 1, map, visited);
        }
    }
    return fencingPrice;
}

int createRegion(int i, int j, bool bulk, std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited)
{
    visited[i][j] = 1;

    int area = 1;
    int perimeter = 0;
    if (bulk)
        checkAllAdjacentForCorners(map[i][j], i, j, area, perimeter, map, visited);
    else
        perimeter = checkAllAdjacent(map[i][j], i, j, area, map, visited);

    return area * perimeter;
}

int checkAllAdjacent(char c, int i, int j, int& area, std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited)
{
    return checkAdjacent (map[i][j], i-1, j, area, map, visited)
    + checkAdjacent(map[i][j], i+1, j, area, map, visited)
    + checkAdjacent(map[i][j], i, j-1, area, map, visited)
    + checkAdjacent(map[i][j], i, j+1, area, map, visited);
}

void checkAllAdjacentForCorners(char c, int i, int j, int& area, int& corners, std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited)
{
    int N = checkAdjacentForCorner(map[i][j], i-1, j, area, corners, map, visited);
    int S = checkAdjacentForCorner(map[i][j], i+1, j, area, corners, map, visited);
    int W = checkAdjacentForCorner(map[i][j], i, j-1, area, corners, map, visited);
    int E = checkAdjacentForCorner(map[i][j], i, j+1, area, corners, map, visited);

    if (N == 1 && W == 1) corners++;
    if (N == 0 && W == 0 && map[i-1][j-1] != c) corners++;
    if (N == 1 && E == 1) corners++;
    if (N == 0 && E == 0 && map[i-1][j+1] != c) corners++;
    if (S == 1 && W == 1) corners++;
    if (S == 0 && W == 0 && map[i+1][j-1] != c) corners++;
    if (S == 1 && E == 1) corners++;
    if (S == 0 && E == 0 && map[i+1][j+1] != c) corners++;
}

int checkAdjacent(char c, int i, int j, int& area, std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited)
{
    if (i < 0 || i > map.size() - 1 || j < 0 || j > map[0].size() - 1) return 1;
    if (map[i][j] == c && visited[i][j]) return 0;
    if (map[i][j] != c) return 1;

    area++;
    visited[i][j] = 1;
    return checkAllAdjacent(map[i][j], i, j, area, map, visited);
}

int checkAdjacentForCorner(char c, int i, int j, int& area, int& corners, std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited)
{
    if (i < 0 || i > map.size() - 1 || j < 0 || j > map[0].size() - 1) return 1;
    if (map[i][j] == c && visited[i][j]) return 0;
    if (map[i][j] != c) return 1;

    area++;
    visited[i][j] = 1;
    checkAllAdjacentForCorners(map[i][j], i, j, area, corners, map, visited);
    return 0;
}

std::vector<std::vector<char>> readFile()
{
    std::vector<std::vector<char>> map;

    std::ifstream in("input.txt");

    std::string line;
    std::vector<char> mapRow;
    while (getline(in, line))
    {
        for (char& ch : line) mapRow.push_back(ch);
        map.push_back(mapRow);
        mapRow.clear();
    }

    in.close();

    return map;
}
