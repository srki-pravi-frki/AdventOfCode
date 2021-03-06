// Day16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <map>
#include <fstream>
#include <streambuf>

using namespace std;

int main()
{
    string programs = "abcdefghijklmnop";

    map<string, int> prev;

    ifstream is("Input.txt");

    std::string sequence((std::istreambuf_iterator<char>(is)),
        std::istreambuf_iterator<char>());
    
    int i = 0;
    while (1)
    {
        ++i;

        istringstream s(sequence);

        std::string line;
        
        while (getline(s, line, ','))
        {
            string str2;

            switch (line.at(0))
            {
                case 's':
                {
                    auto length = stoi(line.substr(1, line.size() - 1));
                    std::rotate(std::begin(programs), std::end(programs) - length, std::end(programs));
                    break;
                }
                case 'x':
                {

                    int del = line.find('/');
                    int pos1 = stoi(line.substr(1, del));
                    int pos2 = stoi(line.substr(del + 1, line.size()));

                    swap(programs[pos1], programs[pos2]);

                    break;
                }
                case 'p':
                {
                    auto str1 = line.at(1);
                    auto str2 = line.at(3);
                    std::iter_swap(std::find(std::begin(programs), std::end(programs), str1),
                        std::find(std::begin(programs), std::end(programs), str2));

                    break;
                }
            }

        }

        if (prev.count(programs)) {
            if ((1000000000 - i) % (i - prev[programs]) == 0) {
                cout << "Iteration nr " << i << " Cycle length " << i - prev[programs] << endl;
                break;
            }
        }

        prev[programs] = i;
    }


    cout << "end string " << programs << endl;

    cin.ignore();
    return 0;
}

