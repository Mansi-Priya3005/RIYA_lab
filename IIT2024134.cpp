#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct V {
    int t;
    string l;
};

vector<string> s = {"A", "B", "C"};
vector<vector<V>> d(3);
V a[3];
bool used[3] = {false, false, false};

bool related(int x, int y) {
    return (x == 0 && y == 1) || (x == 1 && y == 0) ||
           (x == 1 && y == 2) || (x == 2 && y == 1);
}

bool valid(int x, V v) {

    if (x == 0 && v.l != "L1")
        return false;

    if (x == 2 && v.l == "L1")
        return false;

    if (x == 1 && v.t == 4 && v.l != "L2")
        return false;

    for (int i = 0; i < 3; i++) {

        if (!used[i])
            continue;

        if (related(x, i) && v.t == a[i].t)
            return false;

        if (v.t == a[i].t && v.l == a[i].l)
            return false;

        if ((x == 0 && i == 2) || (x == 2 && i == 0)) {
            if (abs(v.t - a[i].t) == 1)
                return false;
        }
    }

    return true;
}

int degree(int x) {
    if (x == 1)
        return 2;
    return 2;
}

int selectVar() {

    int b = -1;

    for (int i = 0; i < 3; i++) {

        if (used[i])
            continue;

        if (b == -1 ||
            d[i].size() < d[b].size() ||
            (d[i].size() == d[b].size() &&
             degree(i) > degree(b))) {
            b = i;
        }
    }

    return b;
}

void show() {

    for (int i = 0; i < 3; i++) {

        if (used[i])
            continue;

        cout << s[i] << ": ";

        if (d[i].empty()) {
            cout << "{}";
        } else {
            for (auto v : d[i])
                cout << "(" << v.t << "," << v.l << ") ";
        }

        cout << endl;
    }
}

bool solve(int cnt) {

    if (cnt == 3)
        return true;

    int x = selectVar();

    cout << "\nSelected: " << s[x] << endl;

    vector<vector<V>> old = d;

    for (V v : old[x]) {

        if (!valid(x, v))
            continue;

        cout << "Assign " << s[x] << " = ("
             << v.t << "," << v.l << ")" << endl;

        a[x] = v;
        used[x] = true;

        for (int i = 0; i < 3; i++) {

            if (used[i])
                continue;

            vector<V> nd;

            for (V u : d[i]) {

                bool ok = true;

                if (v.t == u.t && v.l == u.l)
                    ok = false;

                if (related(x, i) && v.t == u.t)
                    ok = false;

                if ((x == 0 && i == 2) ||
                    (x == 2 && i == 0)) {

                    if (abs(v.t - u.t) == 1)
                        ok = false;
                }

                if (i == 1 && u.t == 4 && u.l != "L2")
                    ok = false;

                if (ok)
                    nd.push_back(u);
            }

            d[i] = nd;
        }

        cout << "Updated domains:\n";
        show();

        bool fail = false;

        for (int i = 0; i < 3; i++) {
            if (!used[i] && d[i].empty()) {
                cout << "Domain of " << s[i] << " is empty\n";
                fail = true;
            }
        }

        if (!fail && solve(cnt + 1))
            return true;

        cout << "Backtracking from "
             << s[x] << " = ("
             << v.t << "," << v.l << ")\n";

        used[x] = false;
        d = old;
    }

    return false;
}

int main() {

    d[0] = {
        {1,"L1"},
        {2,"L1"}
    };

    d[1] = {
        {2,"L1"},
        {2,"L2"},
        {3,"L1"},
        {3,"L2"},
        {4,"L2"}
    };

    d[2] = {
        {1,"L2"},
        {3,"L2"},
        {4,"L2"}
    };

    cout << "--- CSP Backtracking Search ---\n";

    cout << "\nInitial domains:\n";
    show();

    if (solve(0)) {

        cout << "\nFinal Schedule:\n";
        cout << "Section  Time Slot  Lab\n";

        for (int i = 0; i < 3; i++) {
            cout << s[i] << "        "
                 << a[i].t << "          "
                 << a[i].l << endl;
        }

    } else {
        cout << "\nNo valid schedule exists\n";
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Question 2///////////////////////

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
