#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

struct Node {
    string state;
    int g, h;

    bool operator<(const Node& other) const {
        return g + h > other.g + other.h;
    }
};

int heuristic(string s) {
    int cnt = 0;

    for (int i = 0; i < 9; i++) {
        if (s[i] != '0' && s[i] != goal[i])
            cnt++;
    }

    return cnt;
}

vector<string> getNext(string s) {
    vector<string> v;

    int p = s.find('0');

    int r = p / 3;
    int c = p % 3;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
            string t = s;
            swap(t[p], t[nr * 3 + nc]);
            v.push_back(t);
        }
    }

    return v;
}

void print(string s) {
    for (int i = 0; i < 9; i++) {
        if (s[i] == '0') cout << "# ";
        else cout << s[i] << " ";

        if (i % 3 == 2) cout << '\n';
    }
    cout << '\n';
}

void AStar(string start) {
    priority_queue<Node> pq;

    map<string, string> parent;
    map<string, int> dist;

    pq.push({start, 0, heuristic(start)});
    parent[start] = "";
    dist[start] = 0;

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        string s = cur.state;

        if (s == goal) {
            vector<string> path;

            while (s != "") {
                path.push_back(s);
                s = parent[s];
            }

            reverse(path.begin(), path.end());

            for (auto x : path)
                print(x);

            return;
        }

        for (string nxt : getNext(s)) {
            int newG = cur.g + 1;

            if (!dist.count(nxt) || newG < dist[nxt]) {
                dist[nxt] = newG;
                parent[nxt] = s;

                pq.push({nxt, newG, heuristic(nxt)});
            }
        }
    }
}

int main() {
    string start = "123046758";

    AStar(start);

    return 0;
}