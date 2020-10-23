/*hash.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}


//
// Hash
// 
// Hashes the given date "mm-dd-year" and returns an array index.
// If the date falls within the range "01/01/2000" .. "12/31/2099", 
// inclusive, a valid array index is returned in the range 0..N-1.
// If the date falls outside this range, or the date is not formatted
// mm/dd/yyyy, then -1 is returned.  If N >= 37200 then the function 
// is a perfect hash function; if N < 37200 then collisions will occur.
// 
// NOTE: the actual date is not validated, e.g. the function does not
// validate that 02/29/2020 is a leap year.  Validation is limited to 
// checking that the format is mm/dd/yyyy, where 1<=mm<=12, 1<=dd<=31,
// and 2000<=yy<=2099.
// 
// NOTE: the total # of combinations is 365.25 days per year * 100 total
// years.  That's 36,525 possible permutations.  We don't need to be that
// precise.  To simplify things, we'll assume 12 months per year, 31 days
// per month, across 100 years.  That's 12 * 31 * 100 = 37,200 possible
// permutations.  If N >= 37,200, the hash function is perfect and will
// return a value in the range -1 .. 37199, inclusive.
//
int Hash(string theDate, int N)
{
	//
	// is the date formatted properly?  A valid date has the format
	// mm/dd/yyyy, or in terms of a regular expression DD/DD/DDDD.
	// We'll still have to check the bounds of the month, day, year,
	// but at least we'll know the format is correct.
	// 
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [1-9] means match any digit 1-9, and
	// | means "or".  The () is a grouping mechanism that means match 
	// the sub-expression within.  The {n} means match the preceding
	// sub-expression n times.
	// 
	regex pattern("[[:d:]][[:d:]]/[[:d:]][[:d:]]/[[:d:]]{4}",
		regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (!regex_match(theDate, matchResults, pattern))
		return -1;
	
	//
	// Basic formatting is okay, though we still need
	// to make sure the month, day and year fall within
	// the proper numeric bounds (e.g. 1<=month<=12):
	// 
	// NOTE: challenge exercise is to write a better regular expression
	// that eliminates the need for the if statements below.  Start by 
	// just trying to validate the month, that's the easiest one.  Then
	// try the day and year.
	//
	string month = theDate.substr(0, 2);  // mm/...
	string day   = theDate.substr(3, 2);  // mm/dd/...
	string year  = theDate.substr(6, 4);  // mm/dd/yyyy
	
	int M = stoi(month);
	int D = stoi(day);
	int Y = stoi(year);
	
	if (M < 1 || M > 12)
		return -1;
	if (D < 1 || D > 31)
		return -1;
	if (Y < 2000 || Y > 2099)
		return -1;
	
	//
	// it's valid, map to array index and return:
	// 
	// NOTE: each year is a bin of size 372, which is one
	// year worth of data (12*31).  Then we sub-divide
	// into 12 bins, one per month.  Day is the offset.
	//
	int index = ((Y-2000) * 372) + ((M-1) * 31) + (D-1);

	return index % N;
}


//
// Hash
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int Hash(string theDate)
{
  return Hash(theDate, 37200);
}
