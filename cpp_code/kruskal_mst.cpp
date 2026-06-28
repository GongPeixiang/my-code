#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dst;
    int w;
    Edge(int s, int d, int w) : src(s), dst(d), w(w) {}
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent, size; // 按大小合并树
    int cc_cnt; // cc for connection component

    DSU(int n): cc_cnt(n), parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {// 递归路径压缩更彻底
        if (x != parent[x]) 
            parent[x] = find(parent[x]);
        return parent[x];
    }

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
};

class Kruskal {
private:
    int V;
    vector<Edge> edges;
    
public:
    Kruskal(int v) : V(v) {}
    
    void add_edge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }
    
    pair<vector<Edge>, int> find_mst() {
        vector<Edge> result;  // 存储最小生成树的边
        int total_cost = 0;   // 总权重

        sort(edges.begin(), edges.end());
        DSU dsu(V);
        
        for (const Edge &edge : edges) {
            int src_root = dsu.find(edge.src), 
                dst_root = dsu.find(edge.dst);
            if (src_root != dst_root) {
                result.push_back(edge);
                total_cost += edge.w;
                dsu.unite(src_root, dst_root);
            }
            if (result.size() == V - 1) 
                break;
        }
        
        return {result, total_cost};
    }
};

int main() {
    int V = 4;
    // 创建一个有4个顶点的图
    Kruskal kruskal(V);
    
    kruskal.add_edge(0, 1, 1);
    kruskal.add_edge(1, 2, 3);
    kruskal.add_edge(2, 3, 2);
    kruskal.add_edge(0, 2, 4);
    kruskal.add_edge(1, 3, 5);
    
    auto [mst_edges, totalWeight] = kruskal.find_mst();
    
    if (mst_edges.size() != V - 1) {
        cout << "图不连通，无法生成最小生成树" << '\n';
        return 0;
    }

    cout << "最小生成树的边：" << '\n';
    for (const Edge &edge : mst_edges) 
        cout << edge.src << " -- " << edge.dst << " 权重: " 
            << edge.w << '\n';
    cout << "总权重: " << totalWeight << '\n';
}