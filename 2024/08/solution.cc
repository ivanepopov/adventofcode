#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

void calcTFreqAntinodes(int i, int j, std::vector<std::vector<char>>& map, std::vector<std::vector<char>>& a_map)
{
    int freqi = i, freqj = j-1;
    int n = map.size(), m = map[0].size();

    for (; i < n; i++)
    {
        for (; j < m; j++)
        {
            if (map[i][j] == map[freqi][freqj])
            {
                if (map[freqi][freqj] == '#');
                else a_map[freqi][freqj] = '#';

                if (map[i][j] == '#');
                else a_map[i][j] = '#';

                int di = i - freqi, dj = j - freqj;
                int ddi = di, ddj = dj;
                while (i + ddi < n && i + ddi > -1 && j + ddj < m && j + ddj > -1)
                {
                    a_map[i+ddi][j+ddj] = '#';
                    ddi += di; ddj += dj;
                }

                di *= -1;  dj *= -1;
                ddi = di, ddj = dj;
                while (freqi + ddi < n && freqi + ddi > -1 && freqj + ddj < m && freqj + ddj > -1)
                {
                    a_map[freqi+ddi][freqj+ddj] = '#';
                    ddi += di; ddj += dj;
                }
            }
        }
        j = 0;
    }
}

void calcAntinodes(int i, int j, std::vector<std::vector<char>>& map, std::vector<std::vector<char>>& a_map)
{
    int freqi = i, freqj = j-1;
    int n = map.size(), m = map[0].size();

    for (; i < n; i++)
    {
        for (; j < m; j++)
        {
            if (map[i][j] == map[freqi][freqj])
            {
                int di = i - freqi, dj = j - freqj;
                if (i + di < n && i + di > -1 && j + dj < m && j + dj > -1)
                    a_map[i+di][j+dj] = '#';

                di *= -1;  dj *= -1;
                if (freqi + di < n && freqi + di > -1 && freqj + dj < m && freqj + dj > -1)
                    a_map[freqi+di][freqj+dj] = '#';
            }
        }
        j = 0;
    }
}

int calcTotalAntinodes(std::vector<std::vector<char>>& map)
{
    int res = 0;
    std::vector<std::vector<char>> a_map(map.size(), std::vector<char>(map[0].size(), '.'));

    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[0].size(); j++)
            if (map[i][j] != '.') calcAntinodes(i, j+1, map, a_map);

    for (int i = 0; i < a_map.size(); i++)
        for (int j = 0; j < a_map[0].size(); j++)
            if (a_map[i][j] == '#') res++;

    return res;
}

int calcTotalTFreqAntinodes(std::vector<std::vector<char>>& map)
{
    int res = 0;
    std::vector<std::vector<char>> a_map(map.size(), std::vector<char>(map[0].size(), '.'));

    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[0].size(); j++)
            if (map[i][j] != '.') calcTFreqAntinodes(i, j+1, map, a_map);

    for (int i = 0; i < a_map.size(); i++)
        for (int j = 0; j < a_map[0].size(); j++)
            if (a_map[i][j] == '#') res++;

    return res;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::vector<char>> map;
    std::vector<char> row;
    while (getline(in, line))
    {
        row.clear();
        for (char& ch : line) row.push_back(ch);
        map.push_back(row);
    }
    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(8, out);
    out << "Part 1: " << calcTotalAntinodes(map) << std::endl;
    out << "Part 2: " << calcTotalTFreqAntinodes(map) << std::endl;
    out.close();
}
