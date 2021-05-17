//using hilbert order to reduce Mo's algorithm from O((q + n) sqrt n) to O(n sqrt q)

#pragma once

ll hilbertOrder(int x, int y){
    static constexpr int S = 20;
    ll d = 0;
    for (int s = 1 << (S - 1); s; s >>= 1){
        bool rx = x & s, ry = y & s;
        d = d << 2 | rx * 3 ^ static_cast<int>(ry);
        if (!ry) {
            if (rx){
                x = (1 << S) - x;
                y = (1 << S) - y;
            }
            swap(x, y);
        }
    }
    return d;
}

struct Query {
    int l, r, idx;
    ll ord;
    
    Query(int l, int r, int idx): l(l), r(r), idx(idx) {
        ord = hilbertOrder(l, r);
    }
    
    bool operator < (const Query &it) const {
        return ord < it.ord;
    }
};
