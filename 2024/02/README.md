Day 2: Red-Nosed Reports  
=================================  
https://adventofcode.com/2024/day/2

* 7 6 4 2 1
* 1 2 7 8 9
* 9 7 6 2 1
* 1 3 2 4 5
* 8 6 4 4 1
* 1 3 6 7 9

## Part One

The engineers are trying to figure out which reports are safe. The Red-Nosed reactor safety systems can only tolerate levels that are either gradually increasing or gradually decreasing. So, a report only counts as safe if both of the following are true:
* The levels are either all increasing or all decreasing.
* Any two adjacent levels differ by at least one and at most three.  

So, in this example, 2 reports are safe.

## Part Two
The engineers are surprised by the low number of safe reports until they realize they forgot to tell you about the Problem Dampener.
The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.

Thanks to the Problem Dampener, 4 reports are actually safe!
