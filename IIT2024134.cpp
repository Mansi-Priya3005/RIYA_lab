
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Val {
    int t;
    string l;
};

vector<string> sec = {"A", "B", "C"};
vector<vector<Val>> dom(3);
vector<Val> ans(3);
bool used[3] = {false, false, false};

bool con(int a, int b) {
    return (a == 0 && b == 1) || (a == 1 && b == 0) ||
           (a == 1 && b == 2) || (a == 2 && b == 1) ||
           (a == 0 && b == 2) || (a == 2 && b == 0);
}

bool safe(int x, Val v) {
    for (int i = 0; i < 3; i++) {
        if (!used[i] || i == x)
            continue;

        if (i == 0 || i == 1 || i == 2) {
            if (v.t == ans[i].t && con(x, i))
                return false;

            if (v.t == ans[i].t && v.l == ans[i].l)
                return false;

            if ((x == 0 && i == 2) || (x == 2 && i == 0)) {
                if (abs(v.t - ans[i].t) == 1)
                    return false;
            }
        }
    }

    return true;
}

int degree(int x) {
    if (x == 1)
        return 2;
    return 2;
}

int pick() {
    int b = -1;

    for (int i = 0; i < 3; i++) {
        if (used[i])
            continue;

        if (b == -1 ||
            dom[i].size() < dom[b].size() ||
            (dom[i].size() == dom[b].size() &&
             degree(i) > degree(b))) {
            b = i;
        }
    }

    return b;
}

void showDom() {
    cout << "Domains:\n";

    for (int i = 0; i < 3; i++) {
        if (used[i])
            continue;

        cout << sec[i] << ": ";

        if (dom[i].empty()) {
            cout << "{}";
        } else {
            for (auto v : dom[i])
                cout << "(" << v.t << "," << v.l << ") ";
        }

        cout << "\n";
    }
}

bool solve(int cnt) {
    if (cnt == 3)
        return true;

    int x = pick();

    cout << "\nMRV selects " << sec[x] << "\n";

    vector<vector<Val>> old = dom;

    for (auto v : old[x]) {

        if (!safe(x, v))
            continue;

        cout << "Assign " << sec[x] << " = ("
             << v.t << "," << v.l << ")\n";

        ans[x] = v;
        used[x] = true;

        for (int i = 0; i < 3; i++) {
            if (used[i])
                continue;

            vector<Val> nd;

            for (auto u : dom[i]) {
                bool ok = true;

                if (v.t == u.t) {
                    if (v.l == u.l)
                        ok = false;

                    if (con(x, i))
                        ok = false;
                }

                if ((x == 0 && i == 2) || (x == 2 && i == 0)) {
                    if (abs(v.t - u.t) == 1)
                        ok = false;
                }

                if (ok)
                    nd.push_back(u);
            }

            dom[i] = nd;
        }

        showDom();

        bool empty = false;

        for (int i = 0; i < 3; i++) {
            if (!used[i] && dom[i].empty()) {
                cout << "Domain of " << sec[i] << " becomes empty\n";
                empty = true;
            }
        }

        if (!empty && solve(cnt + 1))
            return true;

        cout << "Backtracking from "
             << sec[x] << " = (" << v.t << "," << v.l << ")\n";

        used[x] = false;
        dom = old;
    }

    return false;
}

int main() {

    dom[0] = {
        {1,"L1"},
        {2,"L1"},
        {3,"L1"}
    };

    dom[1] = {
        {2,"L1"},
        {2,"L2"},
        {3,"L1"},
        {3,"L2"},
        {4,"L2"}
    };

    dom[2] = {
        {1,"L2"},
        {3,"L2"},
        {4,"L2"}
    };

    cout << "--- CSP Backtracking Search ---\n";

    cout << "\nInitial Domains:\n";
    showDom();

    if (solve(0)) {

        cout << "\nFinal Schedule:\n";
        cout << "Section  Time Slot  Lab\n";

        for (int i = 0; i < 3; i++) {
            cout << sec[i] << "        "
                 << ans[i].t << "          "
                 << ans[i].l << "\n";
        }

    } else {
        cout << "\nNo valid schedule exists\n";
    }

    return 0;
}
