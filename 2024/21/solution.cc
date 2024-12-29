#include "../holiday/holiday.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <deque>
#include <fstream>
#include <climits>

typedef unsigned long long ll;

struct keypad
{
    int y, x;

    bool operator==(const keypad& k) const {
        return y == k.y && x == k.x;
    }
};

struct visited
{
    keypad k;
    std::string p;
};

class Door
{
    private:
        std::unordered_map<char, keypad>
        numeric_keypad =
        {
            {'0', {3, 1}}, //+---+---+---+
            {'1', {2, 0}}, //| 7 | 8 | 9 |
            {'2', {2, 1}}, //+---+---+---+
            {'3', {2, 2}}, //| 4 | 5 | 6 |
            {'4', {1, 0}}, //+---+---+---+
            {'5', {1, 1}}, //| 1 | 2 | 3 |
            {'6', {1, 2}}, //+---+---+---+
            {'7', {0, 0}}, //  X | 0 | A |
            {'8', {0, 1}}, //    +---+---+
            {'9', {0, 2}},
            {'A', {3, 2}},
            {'X', {3, 0}}
        },
        dir_keypad =
        {
            {'^', {0, 1}}, //    +---+---+
            {'<', {1, 0}}, //  X | ^ | A |
            {'v', {1, 1}}, //+---+---+---+
            {'>', {1, 2}}, //| < | v | > |
            {'A', {0, 2}}, //+---+---+---+
            {'X', {0, 0}}
        };

        int ROBOTS;
        std::vector<std::string> codes;
        std::map<ll, ll> memo;

        ll robotNumpad(keypad&, keypad&);
        ll robotDirpad(keypad&, keypad&, int);
        ll minRobot(const std::string&, int);
        ll hash(keypad& c, keypad& d, int n) { return (((c.y * 4 + c.x) * 4 + d.y) * 4 + d.x) * 30 + n; }

    public:
        Door(std::string);
        ll calculateComplexities(int);
};

int main()
{
    Door door("input.txt");

    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(21, out);
    out << "Part 1: " << door.calculateComplexities(4) << std::endl;
    out << "Part 2: " << door.calculateComplexities(27) << std::endl;
    out.close();
}

ll Door::robotDirpad(keypad& c, keypad& d, int n)
{
    ll h = hash(c, d, n);
    auto it = memo.find(h);
    if (it != memo.end()) return it->second;

    ll res = LLONG_MAX;

    std::deque<visited> q;
    q.push_back({ c, "" });
    while (!q.empty())
    {
        auto [c, p] = q.front();
        q.pop_front();

        if (c == d)
        {
            res = std::min(res, minRobot(p + "A", n-1));
            continue;
        }
        if (c == dir_keypad['X']) continue;
        else
        {
            if      (c.y < d.y) q.push_back({ c.y + 1, c.x, p + "v" });
            else if (c.y > d.y) q.push_back({ c.y - 1, c.x, p + "^" });

            if      (c.x < d.x) q.push_back({ c.y, c.x + 1, p + ">" });
            else if (c.x > d.x) q.push_back({ c.y, c.x - 1, p + "<" });
        }
    }

    memo[h] = res;
    return memo[h];
}

ll Door::minRobot(const std::string& p, int n)
{
    if (n == 1) return p.length();

    ll res = 0;
    keypad c = dir_keypad['A'], d;

    for (auto& ch : p)
    {
        d = dir_keypad[ch];
        res += robotDirpad(c, d, n);
        c = d;
    }

    return res;
}

ll Door::robotNumpad(keypad& c, keypad& d)
{
    ll res = LLONG_MAX;

    std::deque<visited> q;
    q.push_back({ c, "" });
    while (!q.empty())
    {
        auto [c, p] = q.front();
        q.pop_front();

        if (c == d)
        {
            res = std::min(res, minRobot(p + "A", ROBOTS));
            continue;
        }
        if (c == numeric_keypad['X']) continue;
        else
        {
            if      (c.y < d.y) q.push_back({ c.y + 1, c.x, p + "v" });
            else if (c.y > d.y) q.push_back({ c.y - 1, c.x, p + "^" });

            if      (c.x < d.x) q.push_back({ c.y, c.x + 1, p + ">" });
            else if (c.x > d.x) q.push_back({ c.y, c.x - 1, p + "<" });
        }
    }

    return res;
}

ll Door::calculateComplexities(int n)
{
    memo.clear();
    ROBOTS = n-1;

    ll cc = 0;
    for (auto& code : codes)
    {
        ll res = 0;
        keypad c = numeric_keypad['A'], d;

        for (auto& ch : code)
        {
            d = numeric_keypad[ch];
            res += robotNumpad(c, d);
            c = d;
        }

        cc += res * stoi(code);
    }

    return cc;
}

Door::Door(std::string file)
{
    std::ifstream in(file);

    std::string line;
    while (in >> line) codes.push_back(line);

    in.close();
}
