#include "../holiday/holiday.h"
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

typedef long long ll;

class MonkeyMarket
{
    private:
        int SG_COUNT = 2000;
        std::vector<int> secrets;
        std::map<std::deque<int>, std::pair<ll, int>> mp;

        ll genSecretNumber(int);
    public:
        MonkeyMarket(std::string);
        ll calcSecretNumbers();
        ll calcMaxBananas();
};

int main()
{
    MonkeyMarket mm("input.txt");

    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(22, out);
    out << "Part 1: " << mm.calcSecretNumbers() << std::endl;
    out << "Part 2: " << mm.calcMaxBananas() << std::endl;
    out.close();
}

ll MonkeyMarket::calcMaxBananas()
{
    ll mx = 0;
    for (auto& m : mp)
        mx = std::max(mx, m.second.first);
    return mx;
}

ll MonkeyMarket::calcSecretNumbers()
{
    ll total = 0;
    for (int n = 0; n < secrets.size(); n++) total += genSecretNumber(n);
    return total;
}

ll MonkeyMarket::genSecretNumber(int n)
{
    ll s = secrets[n];
    std::deque<int> p_diff;
    int p_curr = s % 10,
        p_new;

    for (int i = 0; i < SG_COUNT; i++)
    {
        // * 64 & Mix
        s ^= s * 64;
        // Prune
        s %= 16777216;
        // / 32 & Mix
        s ^= s / 32;
        // Prune
        s %= 16777216;
        // * 2048 & Mix
        s ^= s * 2048;
        // Prune
        s %= 16777216;

        p_new = s % 10;
        p_diff.push_back(p_new - p_curr);
        p_curr = p_new;

        if (p_diff.size() > 3)
        {
            if (!mp.count(p_diff))
            {
                mp[p_diff] = {p_curr, n};
            }
            if (mp[p_diff].second < n)
            {
                mp[p_diff].first += p_curr;
                mp[p_diff].second = n;
            }
            if (i == 0 && n == 0)
            {
                mp[p_diff].first = std::max(mp[p_diff].first, (ll)p_curr);
            }
            p_diff.pop_front();
        }
    }
    return s;
}

MonkeyMarket::MonkeyMarket(std::string file)
{
    std::ifstream in(file);

    std::string line;
    while (in >> line) secrets.push_back(std::stoi(line));

    in.close();
}
