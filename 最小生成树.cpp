struct Edge {
    int a, b, w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    }
}e[M];
int p[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    int sum = 0;
    for (int i = 0; i < m; i ++ ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        e[i] = {a, b, c};
        sum += c;
    }

    sort(e, e + m);

    int res = 0;
    for (int i = 0; i < m; i ++ ) {
        int a = e[i].a, b = e[i].b, w = e[i].w;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            p[pa] = pb;
            res += w;
        }
    }
}