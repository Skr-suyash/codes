#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

vector<string> getNext(string s) {
    vector<string> v;
    int p = s.find('0');

    int r = p / 3, c = p % 3;

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

void BFS(string start) {
    queue<string> q;
    map<string, string> parent;
    set<string> vis;

    q.push(start);
    vis.insert(start);
    parent[start] = "";

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        if (cur == goal) {
            vector<string> path;

            while (cur != "") {
                path.push_back(cur);
                cur = parent[cur];
            }

            reverse(path.begin(), path.end());

            for (auto x : path)
                print(x);

            return;
        }

        for (string nxt : getNext(cur)) {
            if (!vis.count(nxt)) {
                vis.insert(nxt);
                parent[nxt] = cur;
                q.push(nxt);
            }
        }
    }
}

int main() {
    string start = "123046758";

    BFS(start);

    return 0;
}