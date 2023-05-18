int primes[N], cnt;
bool st[N];
int p[N], c;

void getprimes(int n) {
	for (int i = 2; i <= n; i ++ ) {
		if (!st[i]) primes[cnt ++ ] = i;
		for (int j = 0; primes[j] <= n / i; j ++ ) {
			st[i * primes[j]] = true;
			if (i % primes[j] == 0) break;
		}
	}
}

void getfactor(int n) {
	c = 0;
	for (int i = 0; primes[i] <= n / primes[i]; i ++ ) {
		if (n % primes[i] == 0) {
			while (n % primes[i] == 0) {
				n /= primes[i];
			}
			p[c ++ ] = primes[i];
		}
	}
	
	if (n > 1) p[c ++ ] = n;
}