#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent, size; // 按大小合并树
    int cc_cnt; // cc for connection component

    DSU(int n): cc_cnt(n), parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }

    bool unite(int a, int b) {
        int root_a = find(a), root_b = find(b);
        if (root_a == root_b) 
            return false;
        if (size[root_a] < size[root_b]) 
            swap(root_a, root_b);
        parent[root_b] = root_a;
        size[root_a] += size[root_b];
        cc_cnt--;
        return true;
    }
    
    inline bool connected(int a, int b) { return find(a) == find(b); }

    inline int get_cc_cnt() { return cc_cnt; }
};

bool hasCycle(vector<vector<int>> edges, int n) {
    DSU dsu(n);
    for (auto e : edges) {
        int u = e[0], v = e[1];
        if (!dsu.unite(u, v)) 
            return true;
    }
    return false;
}

int main() {
    int edgecnt, nodecnt;
    cin >> edgecnt >> nodecnt;
    vector<vector<int>> edges;
    for (int i = 0; i < edgecnt; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    bool judge = hasCycle(edges, nodecnt);
    cout << boolalpha << judge << endl;
    return 0;
}