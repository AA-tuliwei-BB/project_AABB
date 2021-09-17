#include <bits/stdc++.h>

using namespace std;

int gcd(int x, int y) {
	x = abs(x), y = abs(y);
	return !y ? x : gcd(y, x % y);
}

struct fs {
	int a, b;
	fs(int x = 0, int y = 1) {
		int G = gcd(x, y);
		a = x / G, b = y / G;
		if (b < 0) a = -a, b = -b;
	}

	void out() {
		if (b == 1 || a == 0) printf("%d", a);
		else if (b == -1) printf("-%d", a);
		else if (b != 1) printf("%d/%d", a, b);
	}
};

fs operator + (fs a, fs b) {
	int x, y;
	y = a.b * b.b;
	x = a.a * b.b + b.a * a.b;
	return fs(x, y);
}

fs operator - (fs a, fs b) {
	int x, y;
	y = a.b * b.b;
	x = a.a * b.b - b.a * a.b;
	return fs(x, y);
}

fs operator * (fs a, fs b) {
	return fs(a.a * b.a, a.b * b.b);
}

fs operator / (fs a, fs b) {
	swap(b.a, b.b);
	return a * b;
}

struct line {
	fs a[1005];
	int len;
} l[1005];

line operator + (line a, line b) {
	line res;
	res.len = a.len;
	for (int i = 1; i <= a.len; ++i)
		res.a[i] = a.a[i] + b.a[i];
	return res;
}

line operator * (line a, int _b) {
	fs b = fs(_b, 1);
	line res;
	for (int i = 1; i <= a.len; ++i)
		res.a[i] = a.a[i] * b;
	return res;
}

int n;

void print() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n + 1; ++j) {
			l[i].a[j].out();
			putchar(' ');
		}
		putchar('\n');
	}
	puts("");
}

void clear(int i, int j) {
	int p = 0;
	line &a = l[i], &b = l[j];
	for (int i = 1; i <= a.len; ++i)
		if (a.a[i].a) {
			p = i;
			break;
		}

	fs k = b.a[p] / a.a[p];
	if (!k.a) return void();
	for (int i = 1; i <= n + 1; ++i)
		b.a[i] = b.a[i] - a.a[i] * k;
	printf("r(%d) - r(%d) * ", j, i);
	k.out(), puts(":");
	print();
}

/*
void rclear(int i, int j) {
	int p = 0;
	line a = l[i], b = l[j];
	for (int i = a.len; i; --i)
		if (a.a[i].a) {
			p = i;
			break;
		}

	fs k = b.a[p] / a.a[p];
	for (int i = p; i; --i)
		b.a[i] = b.a[i] - a.a[i] * k;
	printf("r(%d) - r(%d) * ", j, i);
	k.out(), puts(":");
	print();
} */

void lineswap(int i, int j) {
	printf("r(%d) <-> r(%d) :\n", i, j);
	print();
	swap(l[i], l[j]);
}

void TurnTo1(int i) {
	int p = 0;
	for (int j = 1; j <= n; ++j)
		if (l[i].a[j].a) {
			p = j;
			break;
		}
	if (!p) return void();

	fs tmp = fs(1, 1) / l[i].a[p];
	for (int j = 1; j <= n + 1; ++j)
		l[i].a[j] = l[i].a[j] * tmp;
	tmp.out();
	printf("r(%d):\n", i);
	print();
}

bool check(int i, int p) {
	for (int j = p; j <= n; ++j)
		if (l[j].a[i].a) return true;
	return false;
}

int main() {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		l[i].len = n + 1;
		for (int j = 1; j <= n + 1; ++j) {
			int tmp; cin >> tmp;
			l[i].a[j] = fs(tmp, 1);
		}
	}

	for (int i = 1, p = 1; i <= n; ++i) { // i 是列，p是行
		if (!check(i, p)) continue;
		if (!l[p].a[i].a) {
			for (int j = p; j <= n; ++j)
				if (l[j].a[i].a) {
					lineswap(j, p);
					break;
				}
		}

		for (int j = p + 1; j <= n; ++j)
			if (l[j].a[i].a)
				clear(p, j);
		++p;
	}

	for (int i = n; i; --i) {
		bool flag = false;
		for (int j = 1; j <= n; ++j)
			if (l[i].a[j].a) flag = true;
		if (!flag) continue;
		else for (int j = i - 1; j; --j)
			clear(i, j);
	}

	for (int i = 1; i <= n; ++i)
		TurnTo1(i);
	return 0;
}
