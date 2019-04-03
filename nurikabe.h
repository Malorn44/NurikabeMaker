// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// Nurikabe Solver by Stephan T. Lavavej
// https://en.wikipedia.org/wiki/Nurikabe_(puzzle)

// cl /EHsc /nologo /W4 /std:c++17 /MT /O2 /GL nurikabe.cpp && nurikabe && wikipedia_hard.html

#ifndef _NURIKABE_H_
#define _NURIKABE_H_

#include <stddef.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using namespace std::chrono;

class Grid {
public:
    Grid(int width, int height, const string& s);

    enum SitRep {
        CONTRADICTION_FOUND,
        SOLUTION_FOUND,
        KEEP_GOING,
        CANNOT_PROCEED
    };

    SitRep solve(bool verbose = true, bool guessing = true);

    int known() const;

    void write(ostream& os, steady_clock::time_point start, steady_clock::time_point finish) const;

private:
    // The states that a cell can be in. Numbered cells are positive,
    // which is why this has an explicitly specified underlying type.
    enum State : int {
        UNKNOWN = -3,
        WHITE = -2,
        BLACK = -1
    };

    // Each region is black, white, or numbered. This allows us to
    // remember when white cells are connected to numbered cells,
    // as the whole region is marked as numbered.
    // Each region keeps track of the coordinates that it occupies.
    // Each region also keeps track of the unknown cells that it's surrounded by.
    class Region {
    public:
        Region(const State state, const int x, const int y, const set<pair<int, int>>& unknowns)
            : m_state(state), m_coords(), m_unknowns(unknowns) {

            if (state == UNKNOWN) {
                throw logic_error("LOGIC ERROR: Grid::Region::Region() - state must be known!");
            }

            m_coords.insert(make_pair(x, y));
        }


        bool white() const {
            return m_state == WHITE;
        }

        bool black() const {
            return m_state == BLACK;
        }

        bool numbered() const {
            return m_state > 0;
        }

        int number() const {
            if (!numbered()) {
                throw logic_error(
                    "LOGIC ERROR: Grid::Region::number() - This region is not numbered!");
            }

            return m_state;
        }


        set<pair<int, int>>::const_iterator begin() const {
            return m_coords.begin();
        }

        set<pair<int, int>>::const_iterator end() const {
            return m_coords.end();
        }

        int size() const {
            return static_cast<int>(m_coords.size());
        }

        bool contains(const int x, const int y) const {
            return m_coords.find(make_pair(x, y)) != m_coords.end();
        }

        template <typename InIt> void insert(InIt first, InIt last) {
            m_coords.insert(first, last);
        }


        set<pair<int, int>>::const_iterator unk_begin() const {
            return m_unknowns.begin();
        }

        set<pair<int, int>>::const_iterator unk_end() const {
            return m_unknowns.end();
        }

        int unk_size() const {
            return static_cast<int>(m_unknowns.size());
        }

        template <typename InIt> void unk_insert(InIt first, InIt last) {
            m_unknowns.insert(first, last);
        }

        void unk_erase(const int x, const int y) {
            m_unknowns.erase(make_pair(x, y));
        }

    private:
        State m_state;
        set<pair<int, int>> m_coords;
        set<pair<int, int>> m_unknowns;
    };

    typedef map<shared_ptr<Region>, set<pair<int, int>>> cache_map_t;

    bool analyze_complete_islands(bool verbose);
    bool analyze_single_liberties(bool verbose);
    bool analyze_dual_liberties(bool verbose);
    bool analyze_unreachable_cells(bool verbose);
    bool analyze_potential_pools(bool verbose);
    bool analyze_confinement(bool verbose, cache_map_t& cache);
    vector<pair<int, int>> guessing_order();
    bool analyze_hypotheticals(bool verbose);

    // We use an upper-left origin.
    // This is convenient during construction and printing.
    // It's irrelevant during analysis.

    bool valid(int x, int y) const;

    State& cell(int x, int y);
    const State& cell(int x, int y) const;

    shared_ptr<Region>& region(int x, int y);
    const shared_ptr<Region>& region(int x, int y) const;

    void print(const string& s, const set<pair<int, int>>& updated = {},
        int failed_guesses = 0, const set<pair<int, int>>& failed_coords = {});
    bool process(bool verbose, const set<pair<int, int>>& mark_as_black,
        const set<pair<int, int>>& mark_as_white, const string& s,
        int failed_guesses = 0, const set<pair<int, int>>& failed_coords = {});

    template <typename F> void for_valid_neighbors(int x, int y, F f) const;
    void insert_valid_neighbors(set<pair<int, int>>& s, int x, int y) const;
    void insert_valid_unknown_neighbors(set<pair<int, int>>& s, int x, int y) const;

    void add_region(int x, int y);
    void mark(State s, int x, int y);
    void fuse_regions(shared_ptr<Region> r1, shared_ptr<Region> r2);

    bool impossibly_big_white_region(int n) const;

    bool unreachable(int x_root, int y_root,
        set<pair<int, int>> discovered = {}) const;

    bool confined(const shared_ptr<Region>& r, cache_map_t& cache,
        const set<pair<int, int>>& verboten = {}) const;

    bool detect_contradictions(bool verbose, cache_map_t& cache);


    int m_width; // x is valid within [0, m_width).
    int m_height; // y is valid within [0, m_height).
    int m_total_black; // The total number of black cells that will be in the solution.

    // m_cells[x][y].first is the state of a cell.
    // m_cells[x][y].second is the region of a cell.
    // (If the state is unknown, the region is empty.)
    vector<vector<pair<State, shared_ptr<Region>>>> m_cells;

    // The set of all regions can be traversed in linear time.
    set<shared_ptr<Region>> m_regions;

    // This is initially KEEP_GOING.
    // If an attempt is made to fuse two numbered regions, or to mark an already known cell,
    // this is set to CONTRADICTION_FOUND.
    SitRep m_sitrep;

    // This stores the output that is generated during solving, to be converted into HTML later.
    vector<tuple<string, vector<vector<State>>, set<pair<int, int>>, steady_clock::time_point,
        int, set<pair<int, int>>>> m_output;

    // This is used to guess cells in a deterministic but pseudorandomized order.
    mt19937 m_prng;

    Grid(const Grid& other);
    Grid& operator=(const Grid&) = delete;
};

string format_time(const steady_clock::time_point start, const steady_clock::time_point finish); 

#endif
