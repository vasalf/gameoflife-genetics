//  GameOfLifePosition class
//  Copyright (C) 2016  Alferov Vasiliy
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <string>
#include <vector>

#include <gameoflife/position.h>

using namespace std;

int main() {
    string trash;
    GOLPosition pos;
    
    vector<pair<int, int> > glider = {
        make_pair(1, 2),
        make_pair(2, 1),
        make_pair(2, 0),
        make_pair(1, 0),
        make_pair(0, 0)};

    pos.setPosition(GOLAbstractPosition::range(glider.begin(), glider.end()));

    while (true) {
        for (int i = 9; i > -9; i--) {
            for (int j = -9; j < 10; j++) {
                if (pos.isAlive(i, j))
                    cout << "#";
                else
                    cout << ".";
            }
            cout << endl;
        }
        cout << endl;
        cout.flush();
        getline(cin, trash);

        pos.nextTurn();
    }

    return 0;
}
