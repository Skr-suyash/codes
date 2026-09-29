#include <bits/stdc++.h>
using namespace std;

// coordinates
double x[] = {0,2,5,6,8,1,7,3};
double y[] = {0,6,2,7,3,4,6,1};

double dist(int a, int b) {
    return sqrt((x[a]-x[b])*(x[a]-x[b]) +
                (y[a]-y[b])*(y[a]-y[b]));
}

// W -> A -> B ... -> W
double cost(vector<int> r) {
    double ans = dist(0, r[0]);

    for(int i = 0; i < 6; i++)
        ans += dist(r[i], r[i+1]);

    ans += dist(r[6], 0);
    return ans;
}

void printRoute(vector<int> r) {
    cout << "W ";
    for(int i : r)
        cout << char('A' + i - 1) << " ";
    cout << "W";
}

int main() {
    // for seeding with the current time else same will be generated
    srand(time(0));

    vector<int> cur = {1,2,3,4,5,6,7};
    random_shuffle(cur.begin(), cur.end());

    int iteration = 0;

    cout << "Initial route: ";
    printRoute(cur);
    cout << "\nInitial cost: " << cost(cur) << "\n\n";

    while(true) {
        vector<int> best = cur;
        double bestCost = cost(cur);

        for(int i = 0; i < 7; i++) {
            for(int j = i+1; j < 7; j++) {
                vector<int> next = cur;
                swap(next[i], next[j]);

                if(cost(next) < bestCost) {
                    best = next;
                    bestCost = cost(next);
                }
            }
        }

        if(best == cur)
            break;

        cur = best;
        iteration++;

        cout << "Iteration " << iteration << ": ";
        printRoute(cur);
        cout << "  Cost = " << cost(cur) << "\n";
    }

    cout << "\nFinal route: ";
    printRoute(cur);
    cout << "\nFinal cost: " << cost(cur);
    cout << "\nIterations: " << iteration << "\n";
}