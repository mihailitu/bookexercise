#include "gtest.h"

/*
1.Question 1

*3-SUM in quadratic time.*
Design an algorithm for the 3-SUM problem that takes time proportional to n^2 in the worst case.
You may assume that you can sort the nnn integers in time proportional to n^2 or better.

/Hint:
    given an integer x and a sorted array a[] of n distinct integers, design a linear-time algorithm to determine
    if there exists two distinct indices i and j such that a[i]+a[j]==x.
*/

/*
2.Question 2

*Search in a bitonic array.*
An array is /bitonic/ if it is comprised of an increasing sequence of integers followed immediately by a decreasing
sequence of integers. Write a program that, given a bitonic array of n distinct integer values, determines whether a given integer is in the array.

  * Standard version: Use ∼3lg⁡n compares in the worst case.
  * Signing bonus: Use ∼2lg⁡n compares in the worst case (and prove that
    no algorithm can guarantee to perform fewer than ∼2lg⁡n compares in
    the worst case).

/Hints/: Standard version. First, find the maximum integer using ∼1lg⁡n compares—this divides the array into the increasing and decreasing pieces.

Signing bonus. Do it without finding the maximum integer.
*/

/*
3.Question 3

*Egg drop.*
Suppose that you have an nnn-story building (with floors 1 through n) and plenty of eggs. An egg breaks if it is dropped from
floor T or higher and does not break otherwise. Your goal is to devise a strategy to determine the value of T given the following limitations
on the number of eggs and tosses:

  * Version 0: 1 egg, ≤T\le T≤T tosses.
  * Version 1: ∼1lg⁡n eggs and ∼1lg⁡n tosses.
  * Version 2: ∼lg⁡T eggs and ∼2lg⁡T tosses.
  * Version 3: 222 eggs and ∼2n tosses.
  * Version 4: 222 eggs and ≤cT\le c \sqrt T≤cT

    ​tosses for some fixed constant ccc.

/Hints: /

  * Version 0: sequential search.
  * Version 1: binary search.
  * Version 2: find an interval containing TTT of size ≤2T\le 2T≤2T, then do binary search.
  * Version 3: find an interval of size n\sqrt nn

    ​, then do sequential search. Note: can be improved to ∼2n tosses.
  * Version 4:  1+2+3+…+t∼12t2. Aim for c=22c = 2 \sqrt{2}c=22

*/
