#include "../holiday/holiday.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int addPos1(long long curr, int j, long long target, std::vector<long long>& nums);
int multPos1(long long curr, int j, long long target, std::vector<long long>& nums);

int addPos2(long long curr, int j, long long target, std::vector<long long>& nums);
int multPos2(long long curr, int j, long long target, std::vector<long long>& nums);
int concatPos2(long long curr, int j, long long target, std::vector<long long>& nums);

int main()
{
    std::ifstream in("input.txt");

    std::string line;
    std::vector<long long> nums;

    int count1, count2;
    long long val, part1res = 0, part2res = 0;
    while (getline(in, line))
    {
        nums.clear();
        std::stringstream ss(line);
        ss >> line;
        val = std::stoll(line);
        while (ss >> line) nums.push_back(std::stoll(line));

        count1 = std::max(addPos1(nums[0], 1, val, nums), multPos1(nums[0], 1, val, nums));
        count2 = std::max({addPos2(nums[0], 1, val, nums), multPos2(nums[0], 1, val, nums), concatPos2(nums[0], 1, val, nums)});
        part1res += count1 * val;
        part2res += count2 * val;
    }

    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(7, out);
    out << "Part 1: " << part1res << std::endl;
    out << "Part 2: " << part2res << std::endl;
    out.close();
}

int addPos1(long long curr, int j, long long target, std::vector<long long>& nums)
{
    if (curr > target) return 0;
    if (curr == target) return 1;
    if (j >= nums.size()) return 0;

    curr += nums[j];
    return std::max(addPos1(curr, j+1, target, nums), multPos1(curr, j+1, target, nums));
}

int multPos1(long long curr, int j, long long target, std::vector<long long>& nums)
{
    if (curr > target) return 0;
    if (curr == target) return 1;
    if (j >= nums.size()) return 0;

    curr *= nums[j];
    return std::max(addPos1(curr, j+1, target, nums), multPos1(curr, j+1, target, nums));
}

int addPos2(long long curr, int j, long long target, std::vector<long long>& nums)
{
    if (curr > target) return 0;
    if (curr == target) return 1;
    if (j >= nums.size()) return 0;

    curr += nums[j];
    return std::max({addPos2(curr, j+1, target, nums), multPos2(curr, j+1, target, nums), concatPos2(curr, j+1, target, nums)});
}

int multPos2(long long curr, int j, long long target, std::vector<long long>& nums)
{
    if (curr > target) return 0;
    if (curr == target) return 1;
    if (j >= nums.size()) return 0;

    curr *= nums[j];
    return std::max({addPos2(curr, j+1, target, nums), multPos2(curr, j+1, target, nums), concatPos2(curr, j+1, target, nums)});
}

int concatPos2(long long curr, int j, long long target, std::vector<long long>& nums)
{
    if (curr > target) return 0;
    if (curr == target) return 1;
    if (j >= nums.size()) return 0;

    int ten = 1;
    while (nums[j] >= pow(10, ten)) ten++;
    curr *= (pow(10, ten));
    curr += nums[j];

    return std::max({addPos2(curr, j+1, target, nums), multPos2(curr, j+1, target, nums), concatPos2(curr, j+1, target, nums)});
}
