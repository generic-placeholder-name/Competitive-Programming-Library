//offline 2D fenwick tree
//must first call fakeUpdate() on all coordinates before updating
//if online is neccessary then use fenwick of order statistics trees instead

#pragma once

#include "FenwickTree.h"

template<typename T>
struct FenwickTree2D {
    vector<vector<int>> ys;
    vector<FenwickTree<T>> ft;

    FenwickTree2D(int limx): ys(limx) {}

    void fakeUpdate(int x, int y) {
        for(; x < ys.size(); x |= x + 1) ys[x].push_back(y);
    }

    void init() {
        for(auto& v: ys) {
            sort(v.begin(), v.end());
            ft.emplace_back(v.size());
        }
    }

    __attribute__((always_inline)) int idx(int x, int y) const {
        return lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin();
    }

    void update(int x, int y, const T& df) {
        for(; x < ys.size(); x |= x + 1) {
            ft[x].update(idx(x, y), df);
        }
    }

    T query(int x, int y) const { //inclusive
        T sum = 0;
        for(++x, ++y; x; x &= x - 1) {
            sum += ft[x - 1].query(idx(x - 1, y) - 1);
        }
    }

    T query(int x1, int y1, int x2, int y2) const {
        assert(x1 <= y1 && x2 <= y2);
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};
