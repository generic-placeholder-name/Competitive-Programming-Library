//note: this is NOT fast and is only performant up to 1e9 or so

constexpr int UB=2e6+1;
struct accesser {
    ll a[UB+1];
    gp_hash_table<ll, ll> large; //roughly uniform anyway
    accesser() {memset(a, 0, sizeof(a)); large.clear();}
    inline ll get(const ll& n) {if(n<=UB) return a[n]; else return large[n];}
    inline void set(const ll& n, const ll x) {if(n<=UB) a[n]=x; else large[n]=x;}
    inline void add(const ll& n, const ll& x) {
        if(n<=UB) a[n]=a[n]+x;
        else large[n]=large[n]+x;
    }
};
 
constexpr int MAXR=1.5e8+1;
bitset<MAXR+1> isprime;
int Sum[MAXR+1];
void init() {
    for(int i=2; i<=MAXR; i++) isprime[i]=1;
    isprime[0]=isprime[1]=0;
    for(int p=2; p*p<=MAXR; p++) if(isprime[p]) {
        for(int i=p*p; i<=MAXR; i+=p) isprime[i]=0;
    }
    for(int i=1; i<=MAXR; i++) Sum[i]=Sum[i-1]+isprime[i];
}
 
accesser S;
ll cnt(ll n) {
    if(n<=MAXR) return Sum[n];
    int r=sqrt(n);
    vector<ll> V; V.reserve(2*r);
    rep1(i, r) V.pb(n/i);
    for(int i=V.back()-1; i>0; i--) V.push_back(i);
    rep(i, V.size())  {
        S.set(V[i], V[i]-1);
    }
    for(int p=2; p<=r; p++) {
        if (isprime[p]) {
            rep(i, V.size()) {
                const ll v=V[i];
                if(v<1ll*p*p) break;
                S.add(v, S.get(p-1)-S.get(v/p));
            }
        }
    }
    return S.get(n);
}
