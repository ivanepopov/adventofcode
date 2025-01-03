#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../holiday/holiday.h"

int main()
{
    std::ifstream in("input.txt");
    std::string line;

    std::vector<int> leftValues;
    std::vector<int> rightValues;

    while(std::getline(in, line))
    {
        std::stringstream ss(line);
        ss >> line;
        leftValues.push_back(std::stoi(line));
        ss >> line;
        rightValues.push_back(std::stoi(line));
    }

    in.close();

    std::sort(leftValues.begin(), leftValues.end());
    std::sort(rightValues.begin(), rightValues.end());

    int distance = 0;
    for (int i = 0; i < leftValues.size(); i++)
    {
        distance += abs(leftValues[i] - rightValues[i]);
    }

    int similarity = 0;
    int maxSize = std::max(leftValues[leftValues.size()-1], rightValues[rightValues.size()-1]);
    std::vector<int> mp(maxSize, 0);
    for (int& val : rightValues) mp[val]++;
    for (int& val : leftValues) similarity += (val * mp[val]);

    Holiday holiday;
    std::ofstream out("output.txt");
    holiday.happyHolidays(1, out);
    out << "Part 1: " << distance << "\n";
    out << "Part 2: " << similarity << "\n";
    out.close();

    return 0;
}
