#include <cstdio>

const int N = 1e6 + 1;

int t, n, top, flag;
int a[N], p[N][2];
char st[N];

void dfs(int l1, int r1, int l2, int r2) {
	if (l1 + 1 >= l2 && r2 + 1 >= r1) {
		flag = 1;
		for (int i = 1; i < n; i++)
			putchar(st[i]);
		printf("L\n");
		return;
	}
	if (p[a[l1 + 1]][1] == l2 - 1 || p[a[l1 + 1]][1] == r2 + 1) {
		st[++top] = 'L';
		if (p[a[l1 + 1]][1] == l2 - 1)
			st[n - top + 1] = 'L', dfs(l1 + 1, r1, l2 - 1, r2);
		else
			st[n - top + 1] = 'R', dfs(l1 + 1, r1, l2, r2 + 1);
		top--;
	} else if (p[a[r1 - 1]][0] == l2 - 1 || p[a[r1 - 1]][0] == r2 + 1) {
		st[++top] = 'R';
		if (p[a[r1 - 1]][0] == l2 - 1)
			st[n - top + 1] = 'L', dfs(l1, r1 - 1, l2 - 1, r2);
		else
			st[n - top + 1] = 'R', dfs(l1, r1 - 1, l2, r2 + 1);
		top--;
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		top = flag = 0;
		scanf("%d", &n);
		n <<= 1;
		for (int i = 1; i <= n; i++)
			p[i][0] = p[i][1] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			if (!p[a[i]][0])
				p[a[i]][0] = i;
			else
				p[a[i]][1] = i;
		}
		st[++top] = 'L';
		dfs(1, n + 1, p[a[1]][1], p[a[1]][1]);
		if (flag)
			continue;
		top = 0;
		st[++top] = 'R';
		dfs(0, n, p[a[n]][0], p[a[n]][0]);
		if (flag)
			continue;
		printf("-1\n");
	}
}