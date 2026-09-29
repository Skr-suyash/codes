#include <bits/stdc++.h>
using namespace std;

string name[4] = {"AI","DBMS","OS","CN"};

vector<int> dom[4] = {
    {1,2,3},
    {1,2,4},
    {2,3,4},
    {1,3,4}
};

int color[4] = {-1,-1,-1,-1};

bool conflict(int a, int b) {
    if((a==0 && (b==1 || b==2)) ||
       (b==0 && (a==1 || a==2)))
        return true;

    if((a==1 && b==3) || (a==3 && b==1))
        return true;

    if((a==2 && b==3) || (a==3 && b==2))
        return true;

    return false;
}

bool safe(int v, int t) {
    for(int i=0;i<4;i++)
        if(color[i] == t && conflict(v,i))
            return false;

    return true;
}

int MRV() {
    int best = -1;
    int mn = 100;

    for(int i=0;i<4;i++) {
        if(color[i] != -1)
            continue;

        int cnt = 0;

        for(int t : dom[i])
            if(safe(i,t))
                cnt++;

        if(cnt < mn) {
            mn = cnt;
            best = i;
        }
    }

    return best;
}

bool solve(int done) {

    if(done == 4)
        return true;

    int v = MRV();

    cout << "\nSelected: " << name[v] << endl;

    for(int t : dom[v]) {

        if(!safe(v,t))
            continue;

        color[v] = t;

        cout << "Assign " << name[v]
             << " = " << t << endl;

        if(solve(done+1))
            return true;

        color[v] = -1;

        cout << "Backtracking..." << endl;
    }

    return false;
}

int main() {

    solve(0);

    cout << "\nFinal Solution:\n";

    for(int i=0;i<4;i++)
        cout << name[i] << " -> "
             << color[i] << endl;
}

// int func(int z,)