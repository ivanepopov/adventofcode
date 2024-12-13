#include "../holiday/holiday.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

struct machine
{
    ll ax;
    ll ay;
    ll bx;
    ll by;
    ll px;
    ll py;
};

std::vector<machine> readFile();
ll minTokensDP(machine, ll);
ll minTokensWithMath(machine, ll);

int main()
{
    std::vector<machine> m = readFile();

    ll part1 = 0, part2 = 0;
    for (int i = 0; i < m.size(); i++)
    {
        part1 += minTokensWithMath(m[i], 0);
        part2 += minTokensWithMath(m[i], 10000000000000);
    }

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(13, out);
    out << "Part 1: " << part1 << std::endl;
    out << "Part 2: " << part2 << std::endl;
    out.close();
}

ll minTokensDP(machine m, ll OFFSET)
{
    m.px += OFFSET; m.py += OFFSET;
    std::vector<std::vector<ll>> dp(m.px + 1, std::vector<ll>(m.py + 1, LONG_MAX));
    dp[0][0] = 0;

    int a_press = 0, b_press = 0;
    for(ll ax = m.ax, ay = m.ay;
        ax <= m.px && ay <= m.py && a_press <= 100;
        ax += m.ax, ay += m.ay, a_press++
    )
    {
        dp[ax][ay] = std::min(dp[ax][ay], 3 + dp[ax - m.ax][ay - m.ay]);

        b_press = 0;
        for (ll bx = ax + m.bx, by = ay + m.by;
                bx <= m.px && by <= m.py && b_press <= 100;
                bx += m.bx, by += m.by, b_press++
        )
            dp[bx][by] = std::min(dp[bx][by], 1 + dp[bx - m.bx][by - m.by]);
    }

    return dp[m.px][m.py] == LONG_MAX ? 0 : dp[m.px][m.py];
}

ll minTokensWithMath(machine m, ll OFFSET)
{
    ll a = m.ax, b = m.bx, c = m.px + OFFSET,
       d = m.ay, e = m.by, f = m.py + OFFSET;

    // (Xa * Yb - Xb * Ya)
    ll den = a * e - b * d;
    if (den == 0) return 0;

    ll x = (c * e - b * f) / den,
       y = (a * f - c * d) / den;

    if (x >= 0 && y >= 0 &&
        a * x + b * y == c &&
        d * x + e * y == f
    )
        return 3 * x + y;

    return 0;
}

std::vector<machine> readFile()
{
    std::ifstream in("input.txt");

    std::vector<machine> m;
    std::string line, ax, ay, bx, by, px, py;
    while (getline(in, line))
    {
        //button a
        ax = line.substr(line.find('+')+1); ax = ax.substr(0, ax.find(','));
        ay = line.substr(line.find_last_of('+')+1);

        //button b
        getline(in, line);
        bx = line.substr(line.find('+')+1); bx = bx.substr(0, bx.find(','));
        by = line.substr(line.find_last_of('+')+1);

        //prize
        getline(in, line);
        px = line.substr(line.find('=')+1); px = px.substr(0, px.find(','));
        py = line.substr(line.find_last_of('=')+1);

        m.push_back({
            std::stoll(ax), std::stoll(ay),
            std::stoll(bx), std::stoll(by),
            std::stoll(px), std::stoll(py)
        });

        //empty line
        getline(in, line);
    }

    return m;
}
