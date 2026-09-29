#include <bits/stdc++.h>
using namespace std;

string START = "123046758";
string GOAL  = "123456780";

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
string mvName[] = {"Up", "Down", "Left", "Right"};

vector<pair<string,string>> getNext(const string &s) {
    vector<pair<string,string>> v;
    int p = s.find('0');
    int r = p / 3, c = p % 3;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
            string t = s;
            swap(t[p], t[nr * 3 + nc]);
            v.push_back({t, mvName[i]});
        }
    }
    return v;
}

vector<pair<string,string>> getNextDFS(const string &s) {
    int order[] = {3, 1, 0, 2};
    vector<pair<string,string>> v;
    int p = s.find('0');
    int r = p / 3, c = p % 3;
    for (int k = 0; k < 4; k++) {
        int i = order[k];
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
            string t = s;
            swap(t[p], t[nr * 3 + nc]);
            v.push_back({t, mvName[i]});
        }
    }
    return v;
}

int heuristic(const string &s) {
    int cnt = 0;
    for (int i = 0; i < 9; i++)
        if (s[i] != '0' && s[i] != GOAL[i]) cnt++;
    return cnt;
}

void printBoard(const string &s) {
    for (int i = 0; i < 9; i++) {
        if (s[i] == '0') cout << "# ";
        else cout << s[i] << " ";
        if (i % 3 == 2) cout << "\n";
    }
    cout << "\n";
}

void printPath(const vector<string> &path, const map<string,string> &move) {
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << "Move " << i << ": blank " << move.at(path[i]) << "\n";
        printBoard(path[i]);
    }
    cout << "Depth (moves): " << path.size() - 1 << "\n";
}

vector<string> buildPath(string cur, map<string,string> &parent) {
    vector<string> path;
    while (cur != "") { path.push_back(cur); cur = parent[cur]; }
    reverse(path.begin(), path.end());
    return path;
}

void BFS() {
    cout << "===== BFS =====\n";
    queue<string> q;
    map<string,string> parent, move;
    set<string> vis;
    q.push(START); vis.insert(START); parent[START] = "";
    int expanded = 0;
    string found = "";
    while (!q.empty()) {
        string cur = q.front(); q.pop();
        expanded++;
        if (cur == GOAL) { found = cur; break; }
        for (auto [nxt, m] : getNext(cur)) {
            if (!vis.count(nxt)) {
                vis.insert(nxt);
                parent[nxt] = cur;
                move[nxt] = m;
                q.push(nxt);
            }
        }
    }
    cout << "expanded=" << expanded << " generated=" << vis.size() << "\n";
    if (found != "") printPath(buildPath(found, parent), move);
    else cout << "No solution\n";
}

void DFS() {
    cout << "===== DFS (stack, graph-search) =====\n";
    vector<string> st;
    map<string,string> parent, move;
    set<string> vis;
    st.push_back(START); vis.insert(START); parent[START] = "";
    int expanded = 0;
    string found = "";
    while (!st.empty()) {
        string cur = st.back(); st.pop_back();
        expanded++;
        if (cur == GOAL) { found = cur; break; }
        auto nbrs = getNextDFS(cur);
        reverse(nbrs.begin(), nbrs.end());
        for (auto [nxt, m] : nbrs) {
            if (!vis.count(nxt)) {
                vis.insert(nxt);
                parent[nxt] = cur;
                move[nxt] = m;
                st.push_back(nxt);
            }
        }
    }
    cout << "expanded=" << expanded << " generated=" << vis.size() << "\n";
    if (found != "") printPath(buildPath(found, parent), move);
    else cout << "No solution\n";
}

struct Node {
    string state;
    int g, h;
    bool operator<(const Node& o) const { return g + h > o.g + o.h; }
};

void AStar() {
    cout << "===== A* (g=depth, h=mismatched) =====\n";
    priority_queue<Node> pq;
    map<string,string> parent, move;
    map<string,int> dist;
    pq.push({START, 0, heuristic(START)});
    parent[START] = ""; dist[START] = 0;
    set<string> closed;
    int expanded = 0;
    string found = "";
    int fg = 0;
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        string s = cur.state;
        if (closed.count(s)) continue;
        closed.insert(s);
        expanded++;
        if (s == GOAL) { found = s; fg = cur.g; break; }
        for (auto [nxt, m] : getNext(s)) {
            int ng = cur.g + 1;
            if (!dist.count(nxt) || ng < dist[nxt]) {
                dist[nxt] = ng;
                parent[nxt] = s;
                move[nxt] = m;
                pq.push({nxt, ng, heuristic(nxt)});
            }
        }
    }
    cout << "expanded=" << expanded << " generated=" << dist.size() << "\n";
    if (found != "") {
        vector<string> path = buildPath(found, parent);
        for (size_t i = 0; i < path.size(); i++) {
            int g = dist[path[i]], h = heuristic(path[i]);
            if (i > 0) cout << "Move " << i << ": blank " << move[path[i]];
            cout << " [g=" << g << " h=" << h << " f=" << g + h << "]\n";
            printBoard(path[i]);
        }
        cout << "Depth (moves): " << fg << "\n";
    } else cout << "No solution\n";
}

int main() {
    cout << "Start:\n"; printBoard(START);
    cout << "Goal:\n"; printBoard(GOAL);
    BFS();
    DFS();
    AStar();
    return 0;
}
