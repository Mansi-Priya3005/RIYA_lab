#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    int c, r, x, y;
    bool operator>(const Node& o) const {
        return c > o.c;
    }
};

int cost(char ch) {
    if (ch == 'S') return 0;
    if (ch == 'M') return 3;
    if (ch == 'T') return 5;
    return 1;
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<string> g(n);
    for (int i = 0; i < n; i++)
        cin >> g[i];

    pair<int,int> s, t;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'S')
                s = {i, j};

            if (g[i][j] == 'G')
                t = {i, j};
        }
    }

    const int inf = 1e9;

    vector<vector<int>> d(n, vector<int>(m, inf));
    vector<vector<pair<int,int>>> par(
        n, vector<pair<int,int>>(m, {-1, -1})
    );

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    d[s.first][s.second] = 0;
    pq.push({0, s.first, s.second});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    vector<pair<int,int>> ex;

    while (!pq.empty()) {

        Node cur = pq.top();
        pq.pop();

        int c = cur.c;
        int r = cur.r;
        int x = cur.x;
        int y = cur.y;

        if (c != d[x][y])
            continue;

        ex.push_back({x, y});

        if (x == t.first && y == t.second)
            break;

        for (int k = 0; k < 4; k++) {

            int nx = x + dr[k];
            int ny = y + dc[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            if (g[nx][ny] == 'X')
                continue;

            int nc = c + cost(g[nx][ny]);

            if (nc < d[nx][ny]) {
                d[nx][ny] = nc;
                par[nx][ny] = {x, y};
                pq.push({nc, nx, ny});
            }
        }
    }

    cout << "--- Uniform Cost Search ---\n";

    cout << "Start: (" << s.first << "," << s.second << ")\n";
    cout << "Goal: (" << t.first << "," << t.second << ")\n";

    if (d[t.first][t.second] == inf) {
        cout << "No path exists\n";
        return 0;
    }

    cout << "\nExpanded nodes:\n";

    for (auto p : ex)
        cout << "(" << p.first << "," << p.second << ") ";

    vector<pair<int,int>> path;

    pair<int,int> cur = t;

    while (cur != make_pair(-1, -1)) {
        path.push_back(cur);

        if (cur == s)
            break;

        cur = par[cur.first][cur.second];
    }

    reverse(path.begin(), path.end());

    cout << "\n\nMinimum-cost route:\n";

    for (int i = 0; i < path.size(); i++) {

        cout << "(" << path[i].first << "," << path[i].second << ")";

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\n\nTotal movements: " << path.size() - 1;
    cout << "\nTotal path cost: " << d[t.first][t.second] << endl;

    return 0;
}
