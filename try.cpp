#include <bits/stdc++.h>
using namespace std;

// 5 vertices 3 colors

int time[5];

bool safe(int c, int t) {
    if (c == 0 && t == 4) return false;
    if (c == )
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

bool solve(int c) {
    if (c > 4) {
        return true;
    }
    for (int i = 1; i <= 4; i++) {
        if (safe(c, i)) {
            time[c] = i;
            if (solve(c+1)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    for(int i = 0; i < n; i++)
        time[i] = -1;

    
}