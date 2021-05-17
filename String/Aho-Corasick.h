//this is slow b/c I coded it 
//but it does fine in most cases
//this version lists all collisions 
//for counts modify suffix links

#pragma once

const int K=26; //max size
int conv(char& x) {return x-'A';} //char to int converter
 
template<int K, int op(char&)> //templating
struct Vertex {
    int next[K]; //children
    bool leaf=false; //leaf node
    int p=-1; char ch; //parent; current vertex char
    int link=-1, slink=-1; /*link, suffix link*/ int go[K]; //suffix with next character
    vi idx; //end node indexes
    Vertex(int p=-1, char ch='#'): p(p), ch(ch) { //fill shit
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};
 
template<int K, int op(char&)>
struct Trie { //wrapper for trie
    vector<Vertex<K, op>> trie; int n=0;
    void add(const string& s, int id) { //just adding
        int v=0;
        for(char ch: s) {
            int c=op(ch);
            if(trie[v].next[c]==-1) { //if not present then add
                trie[v].next[c]=trie.size();
                trie.emplace_back(v, ch);
            }
            v=trie[v].next[c];
        }
        trie[v].leaf=true;
        trie[v].idx.pb(id); //push index
    }
    Trie() {trie=vector<Vertex<K, op>>(1);}
    Trie(vector<string>& s) {trie=vector<Vertex<K, op>>(1); for(string& it: s) add(it, n++);}
    int go(int v, char ch);
    int get_link(int v) { //get closest suffix
        if(trie[v].link==-1) { //memoize
            if(v==0||trie[v].p==0) trie[v].link=0; //case 0
            else trie[v].link=go(get_link(trie[v].p), trie[v].ch); //goto link of parent which also contains this character
        }
        return trie[v].link;
    }
    int get_suff_link(int v) { //get closest leaf suffix
        if(trie[v].slink==-1) { //similar to above
            if(get_link(v)==0||trie[get_link(v)].leaf) trie[v].slink=get_link(v);
            else trie[v].slink=get_suff_link(get_link(v)); //basic dp
        }
        return trie[v].slink;
    }
};
 
template<int K, int op(char&)>
int Trie<K, op>::go(int v, char ch) {
    int c=op(ch);
    if(trie[v].go[c]==-1) {
        if(trie[v].next[c]!=-1) trie[v].go[c]=trie[v].next[c]; //if has next then goto next
        else trie[v].go[c]=v==0?0:go(get_link(v), ch); //if v=0 then abort; else just goto link until satisfied
    }
    return trie[v].go[c];
}
 
template<int K, int op(char&)>
struct Aho_Corasick { //perfunctory
    Trie<K, op> t;
    Aho_Corasick(Trie<K, op> t): t(t) {}
    Aho_Corasick(vector<string>& vt): t(Trie<K, op>(vt)) {}
    const vector<pii> get(string s) { //return a vector of pairs; 1st element is index at end of collision, 2nd is index of colliding string
        vector<pii> res;
        int v=0;
        rep(i, s.length()) {
            v=t.go(v, s[i]);
            int _v=v;
            while(_v!=0) {
                if(t.trie[_v].leaf) for(int id: t.trie[_v].idx) res.pb({i, id});
                _v=t.get_suff_link(_v);
            }
        }
        return res;
    }
};
