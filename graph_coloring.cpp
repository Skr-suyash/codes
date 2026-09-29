#include <bits/stdc++.h>
using namespace std;

// 5 vertices 3 colors

vector<int> adj[5];
int color[5];
int n = 5;

bool safe(int v, int c) {
    for(int u : adj[v])
        if(color[u] == c)
            return false;
    return true;
}

int selectMRV() {
    int best = -1;
    int minValues = 4;

    for(int v = 0; v < n; v++) {
        if(color[v] != -1)
            continue;

        int cnt = 0;

        for(int c = 0; c < 3; c++)
            if(safe(v, c))
                cnt++;

        if(cnt < minValues) {
            minValues = cnt;
            best = v;
        }
    }

    return best;
}

bool solve(int assigned) {
    if(assigned == n)
        return true;

    int v = selectMRV();

    for(int c = 0; c < 3; c++) {
        if(safe(v, c)) {
            color[v] = c;

            cout << char('A' + v) << " = "
                 << char('R' + c) << endl;

            if(solve(assigned + 1))
                return true;

            color[v] = -1;
        }
    }

    return false;
}

int main() {
    for(int i = 0; i < n; i++)
        color[i] = -1;

    adj[0] = {1, 2};          // A
    adj[1] = {0, 2, 3, 4};    // B
    adj[2] = {0, 1, 4};       // C
    adj[3] = {1, 4};          // D
    adj[4] = {1, 2, 3};       // E

    solve(0);

    cout << "\nFinal coloring:\n";

    for(int i = 0; i < n; i++) {
        cout << char('A' + i) << " = "
             << char('R' + color[i]) << endl;
    }
}