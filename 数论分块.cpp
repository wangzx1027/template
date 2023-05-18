ll block(ll x) {
    ll l = 1, r = 0, res = 0;
    while (l <= n) {
        r = n / (n / l);
        res += (r - l + 1) * (n / l);
        l = r + 1;
    }
    return res;
}