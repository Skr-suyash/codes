#include <bits/stdc++.h>
using namespace std;

double x[] = {0,2,5,6,8,1,7,3};
double y[] = {0,6,2,7,3,4,6,1};

double dist(int a, int b) {
    return sqrt((x[a]-x[b])*(x[a]-x[b]) +
                (y[a]-y[b])*(y[a]-y[b]));
}

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
    srand(time(0));

    vector<int> cur = {1,2,3,4,5,6,7};
    random_shuffle(cur.begin(), cur.end());

    vector<int> best = cur;

    double T = 100;
    double alpha = 0.95;
    int iteration = 0;

    cout << "Initial route: ";
    printRoute(cur);
    cout << "\nInitial cost: " << cost(cur) << "\n\n";

    while(T >= 0.1) {
        vector<int> next = cur;

        int i = rand() % 7;
        int j = rand() % 7;

        while(i == j)
            j = rand() % 7;

        swap(next[i], next[j]);

        double currentCost = cost(cur);
        double newCost = cost(next);

        double delta = newCost - currentCost;

        bool accepted = false;

        if(delta < 0) {
            accepted = true;
        }
        else {
            double p = exp(-delta / T);
            double r = (double)rand() / RAND_MAX; // no between 0 and 1

            if(r < p)
                accepted = true;
        }

        if(accepted) {
            cur = next;

            if(cost(cur) < cost(best))
                best = cur;
        }

        iteration++;

        cout << "Iteration " << iteration
             << "  T = " << T
             << "  Current Cost = " << cost(cur)
             << "  ";

        if(accepted)
            cout << "Accepted\n";
        else
            cout << "Rejected\n";

        T = T * alpha;
    }

    cout << "\nBest route: ";
    printRoute(best);

    cout << "\nBest cost: " << cost(best);
    cout << "\nIterations: " << iteration << "\n";
}