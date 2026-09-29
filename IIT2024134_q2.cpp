//Question2

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int main() {
    int n = 20, p = 10;

    vector<int> base(n);
    for (int i = 0; i < n; i++)
        base[i] = i + 1;

    random_device rd;
    mt19937 gen(rd());

    vector<vector<int>> pop;

    for (int i = 0; i < p; i++) {
        vector<int> tour = base;
        shuffle(tour.begin(), tour.end(), gen);
        pop.push_back(tour);
    }

    cout << "Initial Population:\n\n";

    for (int i = 0; i < p; i++) {
        cout << "Tour " << i + 1 << ": ";

        for (int x : pop[i])
            cout << x << " ";

        cout << "\n";
    }

    return 0;
}
