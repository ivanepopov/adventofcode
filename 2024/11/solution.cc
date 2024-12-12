#include "../holiday/holiday.h"
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

typedef unsigned long long ull;

struct stone
{
    ull value;
    int depth;
    bool operator==(const stone& s) const {
        return value == s.value && depth == s.depth;
    }
};

template<>
struct std::hash<stone>
{
    size_t operator() (const stone &k) const
    {
        auto h1 = hash<ull>{}(k.value);
        auto h2 = hash<int>{}(k.depth);
        return h1 ^ h2;
    }
};

int checkDigits(ull);
std::tuple<ull, ull> splitNumber(ull, int);
ull countStones(ull n, int depth, std::unordered_map<stone, ull>&);;

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line);
    std::stringstream ss(line);
    std::vector<ull> nums;
    std::unordered_map<stone, ull> mp1, mp2;
    while (ss >> line) nums.push_back(std::stoll(line));
    in.close();

    ull part1 = 0, part2 = 0;
    for (ull n : nums) part1 += countStones(n, 25, mp1);
    for (ull n : nums) part2 += countStones(n, 75, mp2);

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(11, out);
    out << "Part 1: " << part1 << std::endl;
    out << "Part 2: " << part2 << std::endl;
    out.close();
}

ull countStones(ull n, int depth, std::unordered_map<stone, ull>& mp)
{
    stone s = {n, depth};
    if (mp.count(s)) return mp[s];
    if (depth == 0) return 1;
    if (n == 0)
    {
        mp[s] = countStones(1, depth-1, mp);
        return mp[s];
    }

    int cd = checkDigits(n);
    if (cd == -1)
    {
        mp[s] = countStones(n*2024, depth-1, mp);
        return mp[s];
    }

    auto [a, b] = splitNumber(n, cd);
    mp[s] = countStones(a, depth-1, mp) + countStones(b, depth-1, mp);
    return mp[s];
}

int checkDigits(ull n)
{
     int l = lround(floor(log10(n)) + 1);
     return l % 2 == 0 ? l/2 : -1;
}

std::tuple<ull, ull> splitNumber(ull n, int cd)
{
    ull a = 0, b = 0;
    for (int i = 0; i < cd; i++)
    {
        b += ((n % 10) * pow(10, i));
        n /= 10;
    }

    for (int i = 0; i < cd; i++)
    {
        a += ((n % 10) * pow(10, i));
        n /= 10;
    }

    return {a, b};
}

