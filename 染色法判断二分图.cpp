vector<int> e[N];
int vis[N];

void dfs(int u, int col, int fa) {
    if (vis[u]) return;
    vis[u] = col;
    for (int v : e[u]) {
        if (v == fa) continue;
        dfs(v, 3 - col, u);
    }
}