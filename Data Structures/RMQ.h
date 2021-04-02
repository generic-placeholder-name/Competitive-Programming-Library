//O(n log n), O(1) RMQ

#pragma once

template<typename T, typename Comparator>
struct rmq {
    static const Comparator comparator;
    int n;
    vector<vector<T>> tb;

    __attribute__((always_inline)) T op(const T& a, const T& b) const {
        return comparator(a, b) ? a : b;
    }

    rmq(const vector<T>& v) {
        n = v.size(); int dep = __lg(n) + 1;
        tb.resize(dep);
        tb[0] = v;
        for(int j = 1; j < dep; j++) {
            tb[j].resize(n - (1 << j) + 1);
            for(int i = 0; i + (1 << j) <= n; i++) {
                tb[j][i] = op(tb[j - 1][i], tb[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) const {
        assert(l <= r);
        int dep = __lg(r - l + 1);
        auto x = op(tb[dep][l], tb[dep][r - (1 << dep) + 1]);
        return x;
    }
};

template<typename T>
using min_rmq = rmq<T, less<T>>;

template<typename T>
using max_rmq = rmq<T, greater<T>>;
