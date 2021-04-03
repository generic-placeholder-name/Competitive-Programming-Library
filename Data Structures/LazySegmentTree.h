//basic lazy segment tree (+, max)
//can be easily changed to other queries

struct SegTree {
private:
    vll mx, lz;
    int n;

    void push(int v) {
        if(!lz[v]) return;
        lz[v*2]+=lz[v];
        lz[v*2+1]+=lz[v];
        mx[v*2]+=lz[v];
        mx[v*2+1]+=lz[v];
        lz[v]=0;
    }

    void upd(int ql, int qr, ll val, int v, int l, int r) {
        if(ql>r||qr<l) return;
        if(ql<=l&&qr>=r) {
            mx[v]+=val;
            lz[v]+=val;
        }
        else {
            push(v);
            int m=(l+r)/2;
            upd(ql, qr, val, v*2, l, m);
            upd(ql, qr, val, v*2+1, m+1, r);
            mx[v]=max(mx[v*2], mx[v*2+1]);
        }
    }

    ll get(int ql, int qr, int v, int l, int r) {
        if(ql>r||qr<l) return LLONG_MIN;
        if(ql<=l&&qr>=r) return mx[v];
        else {
            push(v);
            int m=(l+r)/2;
            return max(get(ql, qr, v*2, l, m), get(ql, qr, v*2+1, m+1, r));
        }
    }

public:
    SegTree(int n): n(n), mx(4*n+4, 0), lz(4*n+4, 0){}
    void upd(int ql, int qr, ll val) {upd(ql, qr, val, 1, 0, n-1);}
    ll get(int ql, int qr) {return get(ql, qr, 1, 0, n-1);}
};
