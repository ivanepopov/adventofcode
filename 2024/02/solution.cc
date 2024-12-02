#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../holiday/holiday.h"

int calculateSafeReports(std::vector<std::vector<int>>& reports, std::vector<int>& safeReports, bool dampener)
{
    bool fail = false;
    int index = 0, i, j, sz = 0;

    for (auto& rep : reports)
    {
        if (dampener) sz = rep.size();
        for (int skip = -1; skip < sz; skip++)
        {
            if (safeReports[index]) continue;

            i = 0; if (skip == i) i++;
            j = i+1; if (skip == j) j++;

            if (rep[i] == rep[j]) continue;

            fail = false;
            if (rep[i] > rep[j] && rep[i] - rep[j] < 4)
            {
                while (j < rep.size())
                {
                    if (rep[i] <= rep[j] || rep[i] - rep[j] > 3) { fail = true; break; }

                    i++; if (skip == i) i++;
                    j++; if (skip == j) j++;
                }
                if (!fail) { safeReports[index] = 1; break; }
            }
            else if (rep[j] > rep[i] && rep[j] - rep[i] < 4)
            {
                while (j < rep.size())
                {
                    if (rep[j] <= rep[i] || rep[j] - rep[i] > 3) { fail = true; break; }

                    i++; if (skip == i) i++;
                    j++; if (skip == j) j++;
                }
                if (!fail) { safeReports[index] = 1; break; }
            }
        }
        index++;
    }

    int safe = 0;
    for (auto& rep : safeReports) if (rep) safe++;
    return safe;
}

int main()
{
    std::ifstream in("input.txt");

    std::string line;
    std::vector<std::vector<int>> reports(1000);

    int i = 0;
    while (std::getline(in, line))
    {
        std::stringstream ss(line);
        while (ss >> line) reports[i].push_back(std::stoi(line));
        i++;
    }

    std::vector<int> safeReports(1000, 0);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(2, out);
    out << "Part 1: " << calculateSafeReports(reports, safeReports, false) << "\n";
    out << "Part 2: " << calculateSafeReports(reports, safeReports, true) << "\n";
}
