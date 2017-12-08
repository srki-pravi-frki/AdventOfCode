#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <iterator>
#include <functional>
#include <algorithm>
#include <regex>
#include <map>
using namespace std;
using std::regex;

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream myfile("Input.txt");

	string line;
    map<string, int> registers;

    int maxValue = INT_MIN;
    
    const auto begin = std::chrono::high_resolution_clock::now();

	if (myfile.is_open()) {

		const regex base_regex("^(\\w+) (dec|inc) (-?\\d+) if (\\w+) ([><=!]=?) (-?\\d+)$");

		smatch pieces_match;

		while (getline(myfile, line))
		{
			if (!line.empty())
			{
				if (regex_match(line, pieces_match, base_regex)) {

                    // If the registers are not in the map, add them and set the value to 0
                    if (registers.find(pieces_match[1]) == registers.end()) {
                        registers[pieces_match[1]] = 0;
                    }

                    if (registers.find(pieces_match[4]) == registers.end()) {
                        registers[pieces_match[4]] = 0;
                    }

                    // Now check the condition
                    string condition = pieces_match[5];
                    bool condResult = false;

                    if (condition == "<") {
                        if (registers[pieces_match[4]] < stoi(pieces_match[6]))
                            condResult = true;
                    }
                    else if (condition == ">") {
                        if (registers[pieces_match[4]] > stoi(pieces_match[6]))
                            condResult = true;
                    }
                    else if (condition == ">=") {
                        if (registers[pieces_match[4]] >= stoi(pieces_match[6]))
                            condResult = true;
                    }
                    else if (condition == "==") {
                        if (registers[pieces_match[4]] == stoi(pieces_match[6]))
                            condResult = true;
                    }
                    else if (condition == "<=") {
                        if (registers[pieces_match[4]] <= stoi(pieces_match[6]))
                            condResult = true;
                    }
                    else if (condition == "!=") {
                        if (registers[pieces_match[4]] != stoi(pieces_match[6]))
                            condResult = true;
                    }

                    if (condResult) {
                        // Contition is true. Do the operation
                        string operation = pieces_match[2];

                        if (operation == "inc") {
                            registers[pieces_match[1]] += stoi(pieces_match[3]);
                        }
                        else if (operation == "dec") {
                            registers[pieces_match[1]] -= stoi(pieces_match[3]);
                        }
                    }

                    // Find the maximum temporary element
                    auto x = std::max_element(registers.begin(), registers.end(),
                        [](const pair<string, int>& p1, const pair<string, int>& p2) {
                        return p1.second < p2.second; });

                    if (x->second > maxValue) maxValue = x->second;
				}
			}
		}
	}
	else {
		cout << "cannot open file " << endl;
		return 0;
	}

    auto x = std::max_element(registers.begin(), registers.end(),
        [](const pair<string, int>& p1, const pair<string, int>& p2) {
        return p1.second < p2.second; });

    cout << x->first << " : " << x->second << endl;
    cout << "Maximum value in register " << maxValue << endl;

	const auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for part one" << std::endl;

	cout << endl;
	cin.ignore();

	return 0;
}