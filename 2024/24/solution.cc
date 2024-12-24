#include "../holiday/holiday.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

typedef long long ll;

class Device {
private:
    std::vector<std::string> x, y, op, res;
    std::unordered_map<std::string, int> wires;

    void operate(int);
    std::vector<std::string> findZIndex();
    bool checkZIndex(std::vector<std::string>&);
    ll calculateOutput(std::vector<std::string>&);
public:
    Device(std::string);
    ll activateTheGates();
};

int main()
{
    Device dev_test("test.txt");
    Device dev_test_small("test_small.txt");
    Device dev("input.txt");

    std::cout << dev_test.activateTheGates() << std::endl;
    std::cout << dev_test_small.activateTheGates() << std::endl;
    std::cout << dev.activateTheGates() << std::endl;
}

ll Device::activateTheGates()
{
    std::vector zIndex = findZIndex();
    int n = res.size();

    while(!checkZIndex(zIndex))
    {
        for (int i = 0; i < n; i++)
        {
            if (!wires.count(x[i])) continue;
            if (!wires.count(y[i])) continue;
            if (wires.count(res[i])) continue;

            operate(i);
        }
    }
    return calculateOutput(zIndex);
}

void Device::operate(int i)
{
    if (op[i] == "XOR")
        wires[res[i]] = wires[x[i]] ^ wires[y[i]];
    else if (op[i] == "AND")
        wires[res[i]] = wires[x[i]] & wires[y[i]];
    else if (op[i] == "OR")
        wires[res[i]] = wires[x[i]] | wires[y[i]];
}

bool Device::checkZIndex(std::vector<std::string>& zIndex)
{
    for(auto& z : zIndex)
        if (!wires.count(z)) return false;
    return true;
}

std::vector<std::string> Device::findZIndex()
{
    std::vector<std::string> zIndex;
    for (auto& out : res)
    {
        if (out[0] != 'z') continue;
        zIndex.push_back(out);
    }

    std::sort(zIndex.begin(), zIndex.end());
    return zIndex;
}

ll Device::calculateOutput(std::vector<std::string>& zIndex)
{
    ll output = 0;
    for (int i = zIndex.size() - 1; i >= 0; i--, output <<= 1)
        if (wires[zIndex[i]] == 1) output++;

    output >>= 1;
    return output;
}

Device::Device(std::string file)
{
    std::ifstream in(file);

    std::string line;
    while (getline(in, line))
    {
        if (line.length() == 0) break;

        std::stringstream ss(line);
        std::string wire, val;
        ss >> wire;
        wire.pop_back();
        ss >> val;

        wires[wire] = std::stoi(val);
    }

    while (getline(in, line))
    {
        std::stringstream ss(line);
        ss >> line;
        x.push_back(line);
        ss >> line;
        op.push_back(line);
        ss >> line;
        y.push_back(line);

        ss >> line;
        ss >> line;
        res.push_back(line);
    }

    in.close();
}
