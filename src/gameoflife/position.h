//  GameOfLife position class
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

#include <boost/range/any_range.hpp>

class GOLAbstractPosition {
public:
    typedef boost::any_range<std::pair<int, int>, 
                             boost::forward_traversal_tag,
                             std::pair<int, int>,
                             std::ptrdiff_t> range;
    
    virtual void setPosition(range r) = 0;
    virtual int size() const = 0;
    virtual bool isAlive(int i, int j) const = 0;
    virtual void nextTurn() = 0;
};

class GOLPosition : public GOLAbstractPosition {
private:
    int field_size;
    std::set<std::pair<int, int> > alive;

public:
    GOLPosition(int _size);

    virtual void setPosition(range r);
    
    int size() const;
    bool isAlive(int i, int j) const;
    void nextTurn();
};
