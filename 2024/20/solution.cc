#include "../holiday/holiday.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

typedef long long ll;

struct pos
{
    int y, x;

    bool operator==(const pos& p) const {
       return y == p.y && x == p.x;
    }
};

template<>
struct std::hash<pos>
{
    size_t operator() (const pos &p) const
    {
        return hash<int>{}(p.y) ^ hash<int>{}(p.x);
    }
};

class Racetrack
{
    private:
        std::vector<std::string> track;
        pos start, end;
        int CHEATS;
        pos dirs[4] =
        {
            {-1, 0},
            {0, 1},
            {1, 0},
            {0, -1},
        };

        bool isValid(pos&);
        ll timeSaved(std::vector<std::vector<ll>>&);
    public:
        Racetrack(std::string);
        ll race(int);
};

int main()
{
    Racetrack track("input.txt");

    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(20, out);
    out << "Part 1: " << track.race(2) << std::endl;
    out << "Part 2: " << track.race(20) << std::endl;
    out.close();
}

ll Racetrack::timeSaved(std::vector<std::vector<ll>>& dp)
{
    std::map<int, int> mp;
    for (int y = 0; y < dp.size(); y++)
    {
        for (int x = 0; x < dp[0].size(); x++)
        {
            if (dp[y][x] == LLONG_MAX) continue;
            if (y == end.y && x == end.x) continue;

            std::list<std::pair<pos, int>> p;
            for (int i = 2; i <= CHEATS; i++)
            {
                for (int j = 0, k; j < i; j++)
                {
                    k = i - j;
                    p.push_back({{y + k, x + j}, i});
                    p.push_back({{y - j, x + k}, i});
                    p.push_back({{y - k, x - j}, i});
                    p.push_back({{y + j, x - k}, i});
                }
            }

            for (auto& v : p)
            {
                auto [dest, cheats] = v;
                if (!isValid(dest) || dp[dest.y][dest.x] == LLONG_MAX) continue;
                mp[dp[dest.y][dest.x] - dp[y][x] - cheats]++;
            }
        }
    }

    ll ts = 0;
    for (auto& m : mp) if (m.first >= 100) ts += m.second;
    return ts;
}

ll Racetrack::race(int cheats)
{
    CHEATS = cheats;

    std::vector<std::vector<ll>> dp(track.size()+1, std::vector<ll>(track[0].size()+1, LLONG_MAX));
    std::unordered_map<pos, bool> visited;
    std::queue<pos> q;

    q.push(start);
    visited[start] = 1;
    dp[start.y][start.x] = 0;

    while (!q.empty())
    {
        auto curr = q.front();
        q.pop();

        for (auto& dir : dirs)
        {
            pos dest = {curr.y + dir.y, curr.x + dir.x};

            if (!isValid(dest) || visited[dest] || track[dest.y][dest.x] == '#') continue;

            dp[dest.y][dest.x] = std::min(dp[dest.y][dest.x], dp[curr.y][curr.x] + 1);
            q.push(dest);
            visited[dest] = 1;
        }
    }

    return timeSaved(dp);
}

bool Racetrack::isValid(pos& p)
{
    return (p.y >= 0 && p.x >= 0 && p.y <= track.size() && p.x <= track[0].size());
}

Racetrack::Racetrack(std::string file)
{
    std::ifstream in(file);
    std::string line;

    bool foundS = 0, foundE = 0;
    while (in >> line)
    {
        if (!foundS)
        {
            auto it = line.find("S");
            if (it != std::string::npos)
            {
                start.x = it;
                start.y = track.size();
                foundS = 1;
            }
        }

        if (!foundE)
        {
            auto it = line.find("E");
            if (it != std::string::npos)
            {
                end.x = it;
                end.y = track.size();
                foundE = 1;
            }
        }

        track.push_back(line);
    }
    in.close();
}
