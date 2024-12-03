Day 3: Mull It Over
=================================  
https://adventofcode.com/2024/day/3

x<b><i>mul(2,4)</i></b>%&mul[3,7]!@^do_not_<b><i>mul(5,5)</i></b>+mul(32,64]then(<b><i>mul(11,8)</i></b><b><i>mul(8,5)</i></b>)

## Part One

Only the four highlighted sections are real mul instructions. Adding up the result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).
Scan the corrupted memory for uncorrupted mul instructions. What do you get if you add up all of the results of the multiplications?

## Part Two
As you scan through the corrupted memory, you notice that some of the conditional statements are also still intact.
If you handle some of the uncorrupted conditional statements in the program, you might be able to get an even more accurate result.

There are two new instructions you'll need to handle:
* The do() instruction enables future mul instructions.
* The don't() instruction disables future mul instructions.

Only the most recent do() or don't() instruction applies. At the beginning of the program, mul instructions are enabled.
