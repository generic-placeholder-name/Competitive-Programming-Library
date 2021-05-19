//SCC code
constexpr int N = 100000;
vi adj[N];
int disc[N], low[N];
stack<int> st[N];
bool in[N];
int comp[N];
int comps;

void dfs(int u) {
    static int t = 0;
    disc[u] = low[u] = ++t;
    st.push(u);
    in[u] = 1;
    for(int v: adj[u]) {
        if(!disc[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(in[v]) low[u] = min(low[u], disc[v]);
    }
    if(low[u] == disc[u]) {
        ++comps;
        while(st.top() != u) {
            int v = st.top();
            comp[v] = comps;
            in[v] = 0;
            st.pop();
        }
        int v = st.top();
        comp[v] = comps;
        in[v] = 0;
        st.pop();
    }
}
