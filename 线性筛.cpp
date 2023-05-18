int primes[N], cnt;
bool st[N];

void getprimes(int n) {
	for (int i = 2; i <= n; i ++ ) {
		if (!st[i]) primes[cnt ++ ] = i;
		for (int j = 0; primes[j] <= n / i; j ++ ) {
			st[i * primes[j]] = true;
			if (i % primes[j] == 0) break;
		}
	}
}