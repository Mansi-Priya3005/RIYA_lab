#include <iostream>
#include <vector>
#include <set>
using namespace std;

int n = 15;
int lim = 225;

set<pair<int,int>> obs = {
    {1,1},{1,2},{1,13},{2,3},{2,11},
    {3,5},{3,6},{3,11},{4,7},{4,11},
    {5,11},{10,4},{10,5},{11,8},{11,9},{11,10}
};

set<pair<int,int>> tr = {
    {1,3},{2,12},{8,1},{14,2},{14,11}
};

set<pair<int,int>> vis;
set<pair<int,int>> got;

int dr[] = {-1,0,1,0};
int dc[] = {0,1,0,-1};

int steps = 0;
int first = -1;
int repeat = 0;

bool dfs(int r, int c, int d) {

    if (d > lim)
        return false;

    vis.insert({r,c});

    if (tr.count({r,c}) && !got.count({r,c})) {
        got.insert({r,c});
        cout << "Grab item at (" << r << "," << c << ")\n";

        if (first == -1)
            first = steps;
    }

    if (got.size() == tr.size())
        return true;

    for (int i = 0; i < 4; i++) {

        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr < 1 || nr > n || nc < 1 || nc > n ||
            obs.count({nr,nc})) {

            cout << "Change the path at (" << r << "," << c << ")\n";
            continue;
        }

        if (vis.count({nr,nc})) {
            repeat++;
            steps++;
            steps--;
            continue;
        }

        cout << "Move ahead: (" << r << "," << c << ") -> ("
             << nr << "," << nc << ")\n";

        steps++;

        if (dfs(nr,nc,d + 1))
            return true;

        steps++;
        cout << "Change the path at (" << nr << "," << nc << ")\n";
    }

    return false;
}

int main() {

    dfs(8,8,0);

    cout << "\nFirst treasure steps: " << first << endl;
    cout << "Steps to find all treasures: " << steps << endl;
    cout << "Cells revisited: " << repeat << endl;

    return 0;
}
