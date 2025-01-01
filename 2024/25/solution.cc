#include "../holiday/holiday.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Office
{
    private:
        std::vector<std::vector<int>> locks;
        std::vector<std::vector<int>> keys;

        int getUniqueFitCount();
    public:
        Office(std::string);
        void print();
};

int main()
{
    Office office("input.txt");
    office.print();
}

void Office::print()
{
    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(25, out);
    out << "Part 1: " << getUniqueFitCount() << std::endl;
    out.close();
}

int Office::getUniqueFitCount()
{
    int i, uniqueFits = 0;
    for (auto& lock : locks)
    {
        for (auto& key : keys)
        {
            i = 0;
            for (; i < 5; i++)
                if (lock[i] + key[i] > 5) break;
            if (i > 4) uniqueFits++;
        }
    }
    return uniqueFits;
}

Office::Office(std::string file)
{
    std::ifstream in(file);

    std::string line;
    bool lock = false;
    while (in >> line)
    {
        if (line[0] == '#') lock = true;
        else lock = false;

        std::vector<int> item(5, 0);

        for (int i = 0; i < 5; i++)
        {
            in >> line;
            for (int j = 0; j < 5; j++)
                if (line[j] == '#') item[j]++;
        }

        if (lock) locks.push_back(item);
        else keys.push_back(item);

        in >> line;
    }

    in.close();
}
