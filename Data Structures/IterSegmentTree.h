//iterative segment tree (set, max)
//does not have lazy

#pragma once

struct SegTree {
    typedef int T;
    static constexpr T id = INT_MIN;
    __attribute__((always_inline)) T op(const T& a, const T& b) const {return max(a, b);}
    //monoid definitions, can be easily changed

    vector<T> s; int n;
    SegTree(int n = 0, T def = 0): s(n << 1, def), n(n) {}

    void update(int pos, const T& val) {
        for(s[pos += n] = val; pos > 1; pos >>= 1) {
            s[pos >> 1] = op(s[pos & ~1], s[pos | 1]);
        }
    }

    T query(int l, int r) { //inclusive
        T ra = id, rb = id;
        for(int l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ra = op(ra, s[l++]);
            if(r & 1) rb = op(s[--r], rb);
        }
        return op(ra, rb);
    }
};
