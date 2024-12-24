#include "../holiday/holiday.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::tuple<std::vector<int>, std::vector<int>> readFile(std::ifstream&);
std::string runProgram(std::vector<int>, std::vector<int>&);

void adv(std::vector<int>&, int);
void bxl(std::vector<int>&, int, int&);
void bst(std::vector<int>&, int);
void jnz(std::vector<int>&, int, int&);
void bxc(std::vector<int>&, int);
void out(std::vector<int>&, int, std::string&);
void bdv(std::vector<int>&, int);
void cdv(std::vector<int>&, int);

int main()
{
    std::ifstream in("input.txt");
    auto [registers, commands] = readFile(in);
    in.close();

    std::cout << runProgram(registers, commands) << std::endl;
}

std::string runProgram(std::vector<int> registers, std::vector<int>& commands)
{
    std::string s;

    int i = 0, n = commands.size();
    while (i < n)
    {
        switch (commands[i])
        {
            case 0:
                adv(registers, commands[i+1]);
                break;
            case 1:
                bxl(registers, commands[i+1], i);
                break;
            case 2:
                bst(registers, commands[i+1]);
                break;
            case 3:
                jnz(registers, commands[i+1], i);
                break;
            case 4:
                bxc(registers, commands[i+1]);
                break;
            case 5:
                out(registers, commands[i+1], s);
                break;
            case 6:
                bdv(registers, commands[i+1]);
                break;
            case 7:
                cdv(registers, commands[i+1]);
                break;
        }
        i += 2;
    }

    return s;
}

void adv(std::vector<int>& r, int c)
{
    if (c > 6) return;
    if (c > 3) c = r[c % 4];
    r[0] /= pow(2, c);
}
void bxl(std::vector<int>& r, int l, int& i)
{
    r[1] ^= l;
}
void bst(std::vector<int>& r, int c)
{
    if (c > 6) return;
    if (c > 3) c = r[c % 4];
    r[1] = c % 8;
}
void jnz(std::vector<int>& r, int l, int& i)
{
    if (r[0] == 0) return;
    i = l;
    i -= 2;
}
void bxc(std::vector<int>& r, int c)
{
    if (c > 6) return;
    r[1] ^= r[2];
}
void out(std::vector<int>& r, int c, std::string& s)
{
    if (c > 6) return;
    if (c > 3) c = r[c % 4];
    if (s.length() != 0) s += ',';
    s += std::to_string(c % 8);
}
void bdv(std::vector<int>& r, int c)
{
    if (c > 6) return;
    if (c > 3) c = r[c % 4];
    r[1] = r[0];
    r[1] /= pow(2, c);
}
void cdv(std::vector<int>& r, int c)
{
    if (c > 6) return;
    if (c > 3) c = r[c % 4];
    r[2] = r[0];
    r[2] /= pow(2, c);
}

std::tuple<std::vector<int>, std::vector<int>> readFile(std::ifstream& in)
{
    std::string line;
    std::vector<int> registers, commands;

    while (getline(in, line))
    {
        if (line.length() == 0) break;
        line.erase(0, 12);

        registers.push_back(std::stoi(line));
    }

    getline(in, line);
    line.erase(0, 9);

    std::stringstream ss(line);
    while (getline(ss, line, ','))
    {
        commands.push_back(std::stoi(line));
    }

    return {registers, commands};
}
