struct Segtree {
    struct Node {
        int l, r;
        ll add, sum;
    }tr[N << 2];

    /* define ls (u * 2)
       define rs (u * 2 + 1) */

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
            tr[u] = {l, r, 0, a[l]};
            return;
        }
        tr[u] = {l, r, 0, 0};
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(u);
    }
 
    void update(int u, int l, int r,int v) {
        if (tr[u].l >= l && tr[u].r <= r) {
            //tr[u].add;
            tr[u].sum += v;
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) update(ls, l, r, v);
        if (r > mid) update(rs, l, r, v);
        pushup(u);
    }
 
    ll query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        ll res = 0;
        if (l <= mid) res = query(ls, l, r);
        if (r > mid) res += query(rs, l, r);
        return res; 
    }
    
    //权值线段树，找第k大
    // int kth(int u, int k) {
    //     if (tr[u].l == tr[u].r) return tr[u].l;
    //     int mid = tr[u].l + tr[u].r >> 1;
    //     if (tr[ls].sum >= k) return kth(ls, k);
    //     else return kth(rs, k - tr[ls].sum);
    // }
 
    void build() {build(1, 1, n);}
    void update(int l, int r, int v) {update(1, l, r, v);}
    ll query(int l, int r) {return query(1, l, r);}
    //int kth(int k) {return kth(1, k);}
 
}name;