#pragma once 

template<typename T>
struct FenwickTree {
    int n;
    vector<T> s;
    
    FenwickTree(int n): n(n), s(n) {}
    void update(int pos, const T& df) {
        for(; pos < n; pos |= pos + 1) s[pos] += df;
    }
    
    T query(int pos) const { //inclusive 
        T res = T();
        for(++pos; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }
    
    T query(int l, int r) const { //inclusive	
        if(l > r) return T();
        return query(r) - query(l - 1);
    }
    
    int lower_bound(T sum) const {
        int pos = 0;
        for(int p = 1 << __lg(n); p; p >>= 1) {
            if (pos + p <= n && s[pos + p - 1] < sum) {
                pos += p;
                sum -= s[pos - 1];
            }
        }
        return pos;
    }
};
