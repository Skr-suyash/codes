#include <bits/stdc++.h>
using namespace std;

int main() {

    int n = 6;
    vector<tuple<int,int,int>> edges = {
        {0,1,5},
        {0,2,2},
        {0,3,3},
        {1,2,2},
        {1,5,3},
        {2,3,1},
        {2,4,2},
        {2,5,6},
        {3,4,4},
        {4,5,4}
    };
    string name = "abcdef";

    vector<vector<pair<int,int>>> adj(n);
    vector<int> dist(n, 1e9);
    vector<int> parent(n, -1);
    int start = 0, goal = 5;
    dist[start] = 0;

    for (auto [u, v, w] : edges) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> h = {6, 2, 5, 6, 4, 0};

    // {f, g, u}
    priority_queue
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > pq;
    pq.push({h[start], 0, start});

    while (!pq.empty()) {
        auto [f, g, u] = pq.top();
        pq.pop();

        if (g > dist[u]) continue;          // stale entry, a cheaper route was already found

        cout << "expand " << name[u] << "  g=" << g
             << " h=" << h[u] << " f=" << f << "\n";

        if (u == goal) break;               // goal popped, so this is the best path

        for (auto [v, w] : adj[u]) {
            int newG = g + w;
            int newF = newG + h[v];
            if (newG < dist[v]) {           // cheaper route to v than any known so far
                dist[v] = newG;
                parent[v] = u;
                pq.push({newF, newG, v});
            }
        }
    }

    // build path from goal back to start
    vector<int> path;
    for (int x = goal; x != -1; x = parent[x]) path.push_back(x);
    reverse(path.begin(), path.end());

    cout << "cost = " << dist[goal] << ", path = ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << name[path[i]];
        if (i + 1 < (int)path.size()) cout << " -> ";
    }
    cout << "\n";

    return 0;
}