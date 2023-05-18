typedef long long ll;
const int N = 100010, M = N * 2;

int n, m, w[N], nw[N], id[N], h[N], e[M], ne[M], idx, dep[N], sz[N], fa[N], top[N], son[N], tot;

struct Node {
    int l, r;
    ll add, sum;
}tr[N << 2];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void pushup(int u) {
    tr[u].sum = tr[ls].sum + tr[rs].sum;
}

void pushdown(int u) {
    if (tr[u].add) {
        tr[ls].add += tr[u].add;
        tr[ls].sum += tr[u].add * (tr[ls].r - tr[ls].l + 1);
        tr[rs].add += tr[u].add;
        tr[rs].sum += tr[u].add * (tr[rs].r - tr[rs].l + 1);
        tr[u].add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, 0, nw[l]};
        return;
    }
    tr[u] = {l, r, 0, 0};
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}

void update(int u, int ql, int qr, int k) {
    if (tr[u].l >= ql && tr[u].r <= qr) {
        tr[u].add += k;
        tr[u].sum += k * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (ql <= mid) update(ls, ql, qr, k);
    if (qr > mid) update(rs, ql, qr, k);
    pushup(u);
}

ll query(int u, int ql, int qr) {
    if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(ls, ql, qr);
    if (qr > mid) res += query(rs, ql, qr);
    return res;
}

void dfs1(int u, int father, int depth) {
    dep[u] = depth, sz[u] = 1, fa[u] = father;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}

void dfs2(int u, int t) {
    id[u] = ++ tot, nw[tot] = w[u], top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

void update_path(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}

ll query_path(int u, int v) {
    ll res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    return res + query(1, id[v], id[u]);
}

void update_tree(int u, int k) {
    update(1, id[u], id[u] + sz[u] - 1, k);
}

ll query_tree(int u) {
    return query(1, id[u], id[u] + sz[u] - 1);
}