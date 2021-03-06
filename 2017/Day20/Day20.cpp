// Day20.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <regex>
#include <unordered_map>

using namespace std;
using std::regex;

struct coordinate {
    int pos;
    int speed;
    int accel;
};

struct particle {
    coordinate X;
    coordinate Y;
    coordinate Z;
    bool dead = false;
};

int main()
{
    ifstream myfile("Input.txt");

    vector<particle> particles;

    if (myfile.is_open()) {
        const regex base_regex("p=<([\\d-]*),([\\d-]*),([\\d-]*)>, v=<([\\d-]*),([\\d-]*),([\\d-]*)>, a=<([\\d-]*),([\\d-]*),([\\d-]*)>");
        smatch pieces_match;
        string line;
        while (getline(myfile, line)) {
            if (!line.empty()) {
                if (regex_match(line, pieces_match, base_regex)) {
                    particle onePart;
                    onePart.X.pos = stoi(pieces_match[1]);
                    onePart.X.speed = stoi(pieces_match[4]);
                    onePart.X.accel = stoi(pieces_match[7]);

                    onePart.Y.pos = stoi(pieces_match[2]);
                    onePart.Y.speed = stoi(pieces_match[5]);
                    onePart.Y.accel = stoi(pieces_match[8]);

                    onePart.Z.pos = stoi(pieces_match[3]);
                    onePart.Z.speed = stoi(pieces_match[6]);
                    onePart.Z.accel = stoi(pieces_match[9]);
                    particles.push_back(onePart);
                }
            }
        }
    }
    else {
        cout << "cannot open file " << endl;
        return 0;
    }

    auto minAccel = INT_MAX;
    auto i = 0;

    for (auto part : particles) {
        auto manh_accel = abs(part.X.accel) + abs(part.Y.accel) + abs(part.Z.accel);
        if (manh_accel <= minAccel) {
            cout << i << " " << manh_accel << endl;
            minAccel = manh_accel;
        }
        i++;
    }

    // Simlation steps
    for (auto z = 0; z < 100; z++) {
        // Move all particles
        for (int i = 0; i < particles.size(); i++) {
            particle* part;
            part = &particles[i];

            if (part->dead)
                continue;

            part->X.speed += part->X.accel;
            part->X.pos += part->X.speed;
            part->Y.speed += part->Y.accel;
            part->Y.pos += part->Y.speed;
            part->Z.speed += part->Z.accel;
            part->Z.pos += part->Z.speed;
        }

        // Find colisions
        for (int i = 0; i != particles.size(); ++i) {
            if (particles[i].dead)
                continue;

            auto q = i;
            ++q;
            for (; q != particles.size(); ++q) {
                if ((particles[i].X.pos == particles[q].X.pos) && (particles[i].Y.pos == particles[q].Y.pos) && (particles[i].Z.pos == particles[q].Z.pos)) {
                    particles[i].dead = true;
                    particles[q].dead = true;
                }
            }
        }
    }

    int nrDead = 0;
    for (auto part : particles) {
        if (part.dead)
            nrDead++;
    }

    cout << "Nr live particles " << particles.size() - nrDead << endl;

    return 0;
}
