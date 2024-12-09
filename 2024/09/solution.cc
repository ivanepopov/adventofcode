#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void populateDisk(std::vector<int>& disk, std::string& line)
{
    for (int i = 0; i < line.length(); i++)
        for (int j = 0; j < line[i]-'0'; j++)
            if (i % 2 == 1) disk.push_back(-1);
            else disk.push_back(i/2);
}

long long calcChecksum(std::vector<int>& disk)
{
    long long res = 0;
    for (int i = 0; i < disk.size(); i++)
        if (disk[i] == -1) continue;
        else res += i * disk[i];
    return res;
}

long long moveSingleFileBlocks(std::vector<int> disk)
{
    long long res = 0;
    int n = disk.size();
    for (int i = 0, j = n-1; i < j; i++, j--)
    {
        while (disk[i] != -1) i++;
        while (disk[j] == -1) j--;

        if (i > j) break;
        std::swap(disk[i], disk[j]);
    }

    return calcChecksum(disk);
}

long long moveFullFileBlocks(std::vector<int> disk, std::string line)
{
    long long res = 0;
    int a = line.size(), b = disk.size(),
        i, j,
        k = 0, l = b-1, m;

    a % 2 == 0 ? i = a - 2 : i = a - 1;
    for (; i >= 0; i -= 2)
    {
        j = 1;
        while (j < i && line[j] < line[i]) j += 2;
        if (j >= i) continue;

        k = 0;
        while (disk[k] != j/2) k++;
        while (disk[k] != -1) k++;

        while (disk[l] != i/2) l--;
        while (disk[l] == i/2) l--;
        l++;

        for (m = 0; m < line[i] - '0'; m++, k++, l++)
            std::swap(disk[k], disk[l]);

        line[j] = '0' + (line[j] - line[i]);
    }

    return calcChecksum(disk);
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line);
    in.close();

    std::vector<int> disk;
    populateDisk(disk, line);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(9, out);
    out << "Part 1: " << moveSingleFileBlocks(disk) << std::endl;
    out << "Part 2: " << moveFullFileBlocks(disk, line) << std::endl;
    out.close();
}

