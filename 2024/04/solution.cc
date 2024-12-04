#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../holiday/holiday.h"

bool checkAdjacent(char c, std::vector<std::vector<char>>& xmas, int i, int j)
{
    if (i < 0 || j < 0 || i > 139 || j > 140) return false;
    return xmas[i][j] == c;
}

int findXmas(std::vector<std::vector<char>>& xmas)
{
    int xmasCount = 0;
    for (int i = 0; i < 140; i++)
    {
        for (int j = 0; j < 141; j++)
        {
            if (xmas[i][j] == 'X')
            {
                if (checkAdjacent('M', xmas, i-1, j-1))
                    if (checkAdjacent('A', xmas, i-2, j-2))
                        if (checkAdjacent('S', xmas, i-3, j-3))
                            xmasCount++;

                if (checkAdjacent('M', xmas, i-1, j))
                    if (checkAdjacent('A', xmas, i-2, j))
                        if (checkAdjacent('S', xmas, i-3, j))
                            xmasCount++;

                if (checkAdjacent('M', xmas, i-1, j+1))
                    if (checkAdjacent('A', xmas, i-2, j+2))
                        if (checkAdjacent('S', xmas, i-3, j+3))
                            xmasCount++;


                if (checkAdjacent('M', xmas, i, j-1))
                    if (checkAdjacent('A', xmas, i, j-2))
                        if (checkAdjacent('S', xmas, i, j-3))
                            xmasCount++;

                if (checkAdjacent('M', xmas, i, j+1))
                    if (checkAdjacent('A', xmas, i, j+2))
                        if (checkAdjacent('S', xmas, i, j+3))
                            xmasCount++;


                if (checkAdjacent('M', xmas, i+1, j-1))
                    if (checkAdjacent('A', xmas, i+2, j-2))
                        if (checkAdjacent('S', xmas, i+3, j-3))
                            xmasCount++;

                if (checkAdjacent('M', xmas, i+1, j))
                    if (checkAdjacent('A', xmas, i+2, j))
                        if (checkAdjacent('S', xmas, i+3, j))
                            xmasCount++;

                if (checkAdjacent('M', xmas, i+1, j+1))
                    if (checkAdjacent('A', xmas, i+2, j+2))
                        if (checkAdjacent('S', xmas, i+3, j+3))
                            xmasCount++;
            }
        }
    }
    return xmasCount;
}

int findXmasShape(std::vector<std::vector<char>>& xmas)
{
    int xmasShapeCount = 0;

    for (int i = 0; i < 140; i++)
    {
        for (int j = 0; j < 141; j++)
        {
            if (xmas[i][j] == 'A')
            {
                if (checkAdjacent('M', xmas, i-1, j-1) && checkAdjacent('M', xmas, i-1, j+1))
                    if (checkAdjacent('S', xmas, i+1, j-1) && checkAdjacent('S', xmas, i+1, j+1))
                        xmasShapeCount++;

                if (checkAdjacent('M', xmas, i-1, j+1) && checkAdjacent('M', xmas, i+1, j+1))
                    if (checkAdjacent('S', xmas, i-1, j-1) && checkAdjacent('S', xmas, i+1, j-1))
                        xmasShapeCount++;

                if (checkAdjacent('M', xmas, i+1, j-1) && checkAdjacent('M', xmas, i+1, j+1))
                    if (checkAdjacent('S', xmas, i-1, j-1) && checkAdjacent('S', xmas, i-1, j+1))
                        xmasShapeCount++;

                if (checkAdjacent('M', xmas, i-1, j-1) && checkAdjacent('M', xmas, i+1, j-1))
                    if (checkAdjacent('S', xmas, i-1, j+1) && checkAdjacent('S', xmas, i+1, j+1))
                        xmasShapeCount++;
            }
        }
    }
    return xmasShapeCount;
}

int main()
{
    std::vector<std::vector<char>> xmas(140, std::vector<char>(141, 0));
    std::ifstream in("input.txt");

    std::string line;
    int i = 0, j;
    while (getline(in, line))
    {
        for (j = 0; j < 141; j++) xmas[i][j] = line[j];
        i++;
    }
    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(4, out);
    out << "Part 1: " << findXmas(xmas) << std::endl;
    out << "Part 2: " << findXmasShape(xmas) << std::endl;
    out.close();
}
