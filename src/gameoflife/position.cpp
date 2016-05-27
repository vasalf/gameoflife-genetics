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

#include <set>
#include <utility>

#include <boost/foreach.hpp>

#include <gameoflife/position.h>

using std::set;
using std::pair;
using std::make_pair;

GOLPosition::GOLPosition(int _size) {
    field_size = _size;
}

void GOLPosition::setPosition(GOLPosition::range r) {
    alive.clear();

    BOOST_FOREACH(auto p, r) {
        alive.insert(p);
    }
}

int GOLPosition::size() const {
    return field_size;
}

bool GOLPosition::isAlive(int i, int j) const {
    return alive.count(make_pair(i, j));
}

static const int dx[] = { 1,  1,  1,  0,  0, -1, -1, -1,  0};
static const int dy[] = { 1,  0, -1,  1, -1,  1,  0, -1,  0};

#define MATHMOD(A, M) ((((A) % (M)) + (M)) % (M))

static inline int countNeighbours(const GOLAbstractPosition& pos, int i, int j) {
    int cnt = 0;
    for (int d = 0; d < 8; d++)
        cnt += pos.isAlive(MATHMOD(i + dx[d], pos.size()), MATHMOD(j + dy[d], pos.size()));
    return cnt;
}

void GOLPosition::nextTurn() {
    set<pair<int, int> > next;
    set<pair<int, int> > viewed;
    for (auto pt : alive) {
        for (int d = 0; d < 9; d++) {
            pair<int, int> p(MATHMOD(pt.first + dx[d], field_size), MATHMOD(pt.second + dy[d], field_size));
            if (!viewed.count(p)) {
                int cnt = countNeighbours(*this, p.first, p.second);
                if (alive.count(p)) {
                    if (2 <= cnt && cnt <= 3)
                        next.insert(p);
                } else {
                    if (cnt == 3)
                        next.insert(p);
                }
                viewed.insert(p);
            }
        }
    }
    alive = next;
}
