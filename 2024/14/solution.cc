#include "../holiday/holiday.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct robot
{
    int px;
    int py;
    int vx;
    int vy;
};

std::vector<robot> readFile(std::ifstream&);
int moveRobots(int, int, std::vector<std::vector<int>>, std::vector<robot>);
int calcQuadrants(int, int, std::vector<std::vector<int>>&);
int findChristmasTree(int, int, std::vector<std::vector<int>>, std::vector<robot>);
bool checkForEasterEgg(int, int, std::vector<std::vector<int>>&);

int main()
{
    std::ifstream in("input.txt");
    std::vector<robot> r = readFile(in);
    in.close();

    int m_h = 103,
        m_w = 101;

    std::vector<std::vector<int>> map(m_h, std::vector<int>(m_w, 0));

    int safetyFactor = moveRobots(m_h, m_w, map, r);
    int treeFound = findChristmasTree(m_h, m_w, map, r);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(14, out);
    out << "Part 1: " << safetyFactor<< std::endl;
    out << "Part 2: " << treeFound << std::endl;
    out.close();
}

int calcQuadrants(int m_h, int m_w, std::vector<std::vector<int>>& map)
{
    int quad1 = 0,
        quad2 = 0,
        quad3 = 0,
        quad4 = 0;

    for (int i = 0; i < m_h; i++)
    {
        if (i == m_h/2) continue;
        for (int j = 0; j < m_w; j++)
        {
            if (j == m_w/2) continue;

            if      (j < m_w/2 && i < m_h/2) quad1 += map[i][j];
            else if (j > m_w/2 && i < m_h/2) quad2 += map[i][j];
            else if (j > m_w/2 && i > m_h/2) quad3 += map[i][j];
            else if (j < m_w/2 && i > m_h/2) quad4 += map[i][j];
        }
    }

    return quad1 * quad2 * quad3 * quad4;
}

int findChristmasTree(int m_h, int m_w, std::vector<std::vector<int>> map, std::vector<robot> r)
{
    int treeFound = -1;

    for (auto& [px, py, vx, vy] : r)
        map[py][px]++;

    if (checkForEasterEgg(m_h, m_w, map))
        treeFound = 0;

    int i = 1;
    while (i < INT32_MAX && treeFound == -1)
    {
        for (auto& [px, py, vx, vy] : r)
        {
            map[py][px]--;

            px += vx;
            if (px >= m_w) px %= m_w;
            if (px < 0) px = m_w - abs(px);

            py += vy;
            if (py >= m_h) py %= m_h;
            if (py < 0) py = m_h - abs(py);

            map[py][px]++;
        }
        if (checkForEasterEgg(m_h, m_w, map))
            treeFound = i;
        i++;
    }

    return treeFound;
}

int moveRobots(int m_h, int m_w, std::vector<std::vector<int>> map, std::vector<robot> r)
{
    for (auto& [px, py, vx, vy] : r)
        map[py][px]++;

    for (int i = 1; i < 101; i++)
    {
        for (auto& [px, py, vx, vy] : r)
        {
            map[py][px]--;

            px += vx;
            if (px >= m_w) px %= m_w;
            if (px < 0) px = m_w - abs(px);

            py += vy;
            if (py >= m_h) py %= m_h;
            if (py < 0) py = m_h - abs(py);

            map[py][px]++;
        }
    }

    return calcQuadrants(m_h, m_w, map);
}

bool checkForEasterEgg(int m_h, int m_w, std::vector<std::vector<int>>& map)
{
    for (int i = 0; i < m_h; i++)
        for (int j = 0; j < m_w; j++)
            if (map[i][j] > 1) return false;

    return true;
}

std::vector<robot> readFile(std::ifstream& in)
{
    std::vector<robot> r;

    std::string line, px, py, vx, vy;
    while (getline(in, line))
    {
        px = line.substr(line.find('=')+1); px = px.substr(0, px.find(','));
        py = line.substr(line.find(',')+1); py = py.substr(0, py.find('v')-1);

        vx = line.substr(line.find_last_of('=')+1); vx = vx.substr(0, vx.find(','));
        vy = line.substr(line.find_last_of(',')+1);

        r.push_back({
            std::stoi(px), std::stoi(py),
            std::stoi(vx), std::stoi(vy)
        });
    }

    return r;
}
