#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const double PM = 0.05;

int wt[] = {7,2,1,9};
int val[] = {500,400,700,200};

int fitness(string s) {
    int weight = 0, value = 0;

    for(int i = 0; i < 4; i++) {
        if(s[i] == '1') {
            weight += wt[i];
            value += val[i];
        }
    }

    if(weight > 15)
        return 0;

    return value;
}

string randomGene() {
    string s = "";

    for(int i = 0; i < 4; i++)
        s += char('0' + rand()%2);

    return s;
}

string select(vector<string> pop) {
    int total = 0;

    for(string s : pop)
        total += fitness(s);

    int r = rand() % total;
    int sum = 0;

    for(string s : pop) {
        sum += fitness(s);

        if(r < sum)
            return s;
    }

    return pop.back();
}

void mutate(string &s) {
    for(int i = 0; i < 4; i++) {
        double r = (double)rand()/RAND_MAX;

        if(r < PM)
            s[i] = (s[i] == '0' ? '1' : '0');
    }
}

int main() {
    srand(time(0));

    vector<string> pop;

    for(int i = 0; i < N; i++)
        pop.push_back(randomGene());

    for(int gen = 0; gen < 10; gen++) {

        cout << "\nGeneration " << gen+1 << "\n";

        int best = 0;

        for(int i = 0; i < N; i++) {
            cout << pop[i]
                 << "  Fitness = " << fitness(pop[i]) << "\n";

            if(fitness(pop[i]) > fitness(pop[best]))
                best = i;
        }

        cout << "Best = " << pop[best]
             << "  Fitness = " << fitness(pop[best]) << "\n";

        vector<string> newPop;

        while(newPop.size() < N) {

            string p1 = select(pop);
            string p2 = select(pop);

            int point = 1 + rand()%3;

            string c1 = p1.substr(0,point) + p2.substr(point);
            string c2 = p2.substr(0,point) + p1.substr(point);

            mutate(c1);
            mutate(c2);

            newPop.push_back(c1);

            if(newPop.size() < N)
                newPop.push_back(c2);
        }

        pop = newPop;
    }

    int best = 0;

    for(int i = 1; i < N; i++)
        if(fitness(pop[i]) > fitness(pop[best]))
            best = i;

    cout << "\nFinal Answer\n";
    cout << "Gene = " << pop[best] << "\n";
    cout << "Maximum Value = " << fitness(pop[best]) << "\n";
}