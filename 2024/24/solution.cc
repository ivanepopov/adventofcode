#include "../holiday/holiday.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

typedef long long ll;

struct op
{
    std::string x, y, res, op;
};

class Device {
private:
    std::vector<op> ops;
    std::unordered_map<std::string, std::vector<op>> opsMap;
    std::unordered_map<std::string, int> wires;
    std::vector<std::string> zIndex;

    void operate(int);
    bool checkZIndex();
    bool checkWire(std::string& w) { return w[0] == 'x' || w[0] == 'y'; }

    ll activateTheGates();
    std::string addTheGates();
public:
    Device(std::string);
    void print();
};

int main()
{
    Device dev("input.txt");
    dev.print();
}

void Device::print()
{
    std::ofstream out("output.txt");
    Holiday h; h.happyHolidays(24, out);
    out << "Part 1: " << activateTheGates() << std::endl;
    out << "Part 2: " << addTheGates() << std::endl;
    out.close();
}

std::string Device::addTheGates()
{
    for (auto& [w, ops] : opsMap) {
        std::sort(std::begin(ops), std::end(ops),
            [](const auto& op1, const auto& op2) { return op1.op < op2.op; }
        );
    }

    std::set<std::string> errors;
    for (auto& [x, y, res, op] : ops) {

        if (res == zIndex.front() || res == zIndex.back()) continue;
        bool inputWireX = checkWire(x), inputWireY = checkWire(y);

        if (inputWireX && !inputWireY)
        {
            errors.insert(res);
        }
        else if (op == "XOR")
        {
            if (inputWireX && res[0] == 'z')
                errors.insert(res);
            else if (!inputWireX && res[0] != 'z')
                errors.insert(res);
            else if (inputWireX && (opsMap[res][0].op != "AND" || opsMap[res][1].op != "XOR"))
                errors.insert(res);
        }
        else if (op == "AND" && (opsMap[res].size() < 1 || opsMap[res][0].op != "OR"))
        {
            errors.insert(res);
        }
        else if (op == "OR")
        {
            if (inputWireX || inputWireY)
                errors.insert(res);
            else if (opsMap.find(res) == opsMap.end() || (opsMap[res].size() != 2 || opsMap[res][0].op != "AND" || opsMap[res][1].op != "XOR"))
                errors.insert(res);
        }
    }

    for (const auto& op : ops)
        if (op.x == "x00" || op.y == "x00" || op.x == "y00" || op.y == "y00")
            errors.erase(op.res);

    std::string gates;
    for (const auto& err : errors) gates += (err + ',');
    gates.pop_back();
    return gates;
}

ll Device::activateTheGates()
{
    int n = ops.size();

    while (!checkZIndex())
    {
        for (int i = 0; i < n; i++)
        {
            if (!wires.count(ops[i].x)) continue;
            if (!wires.count(ops[i].y)) continue;
            if (wires.count(ops[i].res)) continue;

            operate(i);
        }
    }

    ll output = 0;
    for (int i = zIndex.size() - 1; i >= 0; i--, output <<= 1)
        if (wires[zIndex[i]] == 1) output++;
    output >>= 1;

    return output;
}

void Device::operate(int i)
{
    if      (ops[i].op == "XOR") wires[ops[i].res] = wires[ops[i].x] ^ wires[ops[i].y];
    else if (ops[i].op == "AND") wires[ops[i].res] = wires[ops[i].x] & wires[ops[i].y];
    else if (ops[i].op == "OR")  wires[ops[i].res] = wires[ops[i].x] | wires[ops[i].y];
}

bool Device::checkZIndex()
{
    for(auto& z : zIndex) if (!wires.count(z)) return false;
    return true;
}

Device::Device(std::string file)
{
    std::ifstream in(file);

    // input x00 - x??, y00 - y??
    std::string line, wire, val;
    while (getline(in, line))
    {
        if (line.length() == 0) break;

        std::stringstream ss(line);
        ss >> wire;  wire.pop_back();
        ss >> val;   wires[wire] = std::stoi(val);
    }

    // input operands and operators
    while (getline(in, line))
    {
        std::stringstream ss(line);
        op no;
        ss >> line;             no.x   = line;
        ss >> line;             no.op  = line;
        ss >> line;             no.y   = line;
        ss >> line; ss >> line; no.res = line;

        ops.push_back(no);

        opsMap[no.x].push_back(no);
        opsMap[no.y].push_back(no);
    }

    // z indexes
    for (auto& op : ops) if (op.res[0] == 'z') zIndex.push_back(op.res);
    std::sort(zIndex.begin(), zIndex.end());

    in.close();
}
