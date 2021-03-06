// Day17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>

using namespace std;

int main()
{
    std::list<int>::iterator it;
    list<int> buffer;

    buffer.push_back(0);

    int step = 377;
    int position = 0;

    auto begin = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= 2017; ++i) {
        position = ((position + step) % buffer.size()) + 1;
        it = buffer.begin();
        std::advance(it, position);
        buffer.insert(it, i);
    }

    {
        auto it = std::find(buffer.begin(), buffer.end(), 2017);
        it++;
        std::cout << "Part one: " << *it << endl;
    }

    position = 0;
    auto size = 1;
    buffer.clear();
    buffer.push_back(0);

    it = buffer.begin();
    it++;

    for (int i = 1; i <= 50000000; ++i) {
        position = ((position + step) % size) + 1;
        if (position == 1) {
            buffer.insert(it, i);
            --it;
        }
        size++;
    }
    const auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Part two: " << *it << endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms for both parts" << std::endl;

    std::cin.ignore();

    return 0;
}