#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 500010, maxm = 1000100;

struct edge
{
	int id, g, nxt; 

	edge() { }
	edge(int _id, int _g, int _nxt): id(_id), g(_g), nxt(_nxt) { }
};

int en;
int st[maxn + 5];
edge e[(maxm << 1) + 5];

inline void add_edge(int x, int y, int z)
{
	e[en] = edge(y, z, st[x]), st[x] = en++;
}

int n, m;

int S, T;

bool bad[maxn + 5];

int buffer[maxn + 5];

int dfn_cnt = 0;
int dfn[maxn + 5], low[maxn + 5];

bool has_T[maxn + 5];

void get_bad_vertices(int x)
{
	if (x == T) has_T[x] = 1;
	dfn[x] = low[x] = dfn_cnt++;
	int cnt = 0;
	for (int i = st[x]; ~i; i = e[i].nxt)
	{
		int y = e[i].id;
		if (!~dfn[y]) 
		{
			get_bad_vertices(y);
			if (has_T[y]) has_T[x] = 1;
			if (has_T[y] || low[y] < dfn[x])
			{
				cnt += buffer[x];
				chkmin(low[x], low[y]);
			}
			buffer[x] = 0;
		}
		else if (dfn[y] < dfn[x]) 
		{
			++cnt;
			++buffer[y];
			chkmin(low[x], dfn[y]);
		}
	}
	if (cnt <= 2 && x != S && x != T) 
	{
		bad[x] = 1;
	}
}

LL dis[maxn + 5];

bool on_path[maxm + 5];

int pathn;
int path[maxn + 5];
int id[maxn + 5];

inline void get_path()
{
	static bool vis[maxn + 5];
	static int pre[maxn + 5];
	priority_queue<pair<LL, int>, vector<pair<LL, int> >, greater<pair<LL, int> > > q;
	memset(dis, oo, sizeof(dis[0]) * n);
	memset(vis, 0, sizeof(vis[0]) * n);
	q.push(mp(0, S));
	dis[S] = 0;
	while (!q.empty())
	{
		int x = q.top().y; q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = st[x]; ~i; i = e[i].nxt)
		{
			int y = e[i].id;
			if (!bad[y] && chkmin(dis[y], dis[x] + e[i].g))
			{
				pre[y] = i ^ 1;
				q.push(mp(dis[y], y));
			}
		}
	}

	memset(on_path, 0, sizeof(on_path[0]) * m);
	pathn = 0;
	int cur = T;
	while (cur != S)
	{
		path[pathn++] = cur;
		on_path[pre[cur] >> 1] = 1;
		cur = e[pre[cur]].id;
	}
	path[pathn++] = cur;
	reverse(path, path + pathn);

	memset(id, -1, sizeof(id[0]) * n);
	REP(i, 0, pathn) id[path[i]] = i;
}

int bad_pair[(maxm << 1) + 5];

vector<int> down[maxn + 5];

inline void set_bad_pair(const vector<int> &v)
{
	if (SZ(v) != 2) return;
	bad_pair[v[0]] = v[1];
	bad_pair[v[1]] = v[0];
}

void get_bad_pairs(int x)
{
	dfn[x] = low[x] = dfn_cnt++;
	vector<int> up;
	for (int i = st[x]; ~i; i = e[i].nxt) if (!on_path[i >> 1])
	{
		int y = e[i].id;
		if (~dfn[y] && dfn[y] < dfn[x]) 
		{
			if (SZ(down[y]) <= 2) down[y].pb(i ^ 1);
			chkmin(low[x], dfn[y]);
			if (SZ(up) <= 2) up.pb(i);
		}
		else
		{
			if (!~dfn[y]) 
			{
				get_bad_pairs(y);
				if (low[y] < dfn[x]) 
				{
					up.insert(up.end(), ALL(down[x]));
					chkmin(low[x], low[y]);
				}
				else
				{
					if (!~id[x]) 
					{
						set_bad_pair(down[x]);
					}
				}
				down[x].clear();
			}
		}
	}
	if (!~id[x]) 
	{
		set_bad_pair(up);
	}
}

int fa[maxn + 5];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

int lim[maxn + 5];

inline bool get_lim()
{
	static bool leftmost[maxn + 5], rightmost[maxn + 5];
	static bool vis[maxn + 5];
	memset(leftmost, 0, sizeof(leftmost[0]) * pathn);
	memset(rightmost, 0, sizeof(rightmost[0]) * pathn);
	memset(vis, 0, sizeof(vis[0]) * n);
	REP(i, 0, pathn)
	{
		if (!vis[get(path[i])]) 
		{
			leftmost[i] = 1;
			vis[get(path[i])] = 1;
		}
	}
	memset(vis, 0, sizeof(vis[0]) * n);
	for (int i = pathn - 1; i >= 0; --i)
	{
		if (!vis[get(path[i])]) 
		{
			rightmost[i] = 1;
			vis[get(path[i])] = 1;
		}
	}
	if (leftmost[pathn - 1] || rightmost[0]) return 0;
	REP(i, 0, pathn + 1) lim[i] = pathn;
	int lst = -1;
	REP(i, 0, pathn)
	{
		if (leftmost[i]) lst = i;
		if (rightmost[i])
		{
			if (lst > 0 && i + 1 < pathn)
			{
				lim[lst - 1] = i + 1;
			}
		}
	}
	for (int i = pathn - 1; i >= 0; --i)
	{
		chkmin(lim[i], lim[i + 1]);
	}
	return 1;
}

inline LL work()
{
	static int vis[maxn + 5];
	static int info[maxn + 5];
	priority_queue<pair<LL, pair<int, int> >, vector<pair<LL, pair<int, int> > >, greater<pair<LL, pair<int, int> > > > q;
	memset(vis, 0, sizeof(vis[0]) * n);
	q.push(mp(0, mp(S, 0)));
	while (!q.empty())
	{
		LL d = q.top().x;
		int x = q.top().y.x, lst = q.top().y.y; q.pop();
		if (x == T) return d;
		if (!vis[x])
		{
			info[x] = lst;
		}
		else if (vis[x] == 1)
		{
			if (~id[x])
			{
				if (lim[lst] <= lim[info[x]]) continue;
			}
			else
			{
				if (lst >= info[x]) continue;
			}
		}
		else if (vis[x] > 1) continue;
		++vis[x];
		for (int i = st[x % n]; ~i; i = e[i].nxt)
		{
			int y = e[i].id;
			if (bad[y]) continue;
			if (~id[y])
			{
				if (~bad_pair[i] && path[lst] == e[bad_pair[i]].id) continue;
				if (id[y] == lst) continue;
				if (!on_path[i >> 1])
				{
					q.push(mp(d + e[i].g, mp(y, id[y])));
				}
				else if (id[y] < lim[lst])
				{
					q.push(mp(d + e[i].g, mp(y, lst)));
				}
			}
			else 
			{
				if (~id[x]) q.push(mp(d + e[i].g, mp(y, id[x])));
				else q.push(mp(d + e[i].g, mp(y, lst)));
			}
		}
	}
	return -1;
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	scanf("%d%d", &n, &m);
	memset(st, -1, sizeof(st[0]) * n), en = 0;
	REP(i, 0, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z), --x, --y;
		add_edge(x, y, z);
		add_edge(y, x, z);
	}
	scanf("%d%d", &S, &T), --S, --T;
	memset(buffer, 0, sizeof(buffer[0]) * n);
	memset(dfn, -1, sizeof(dfn[0]) * n);
	memset(bad, 0, sizeof(bad[0]) * n);
	memset(has_T, 0, sizeof(has_T[0]) * n);
	dfn_cnt = 0;
	get_bad_vertices(S);

	get_path();

	REP(i, 0, n) fa[i] = i;
	REP(i, 0, n)
		for (int j = st[i]; ~j; j = e[j].nxt)
			if (!on_path[j >> 1]) fa[get(i)] = get(e[j].id);

	bool not_connected = 0;
	REP(i, 0, n) if (get(i) != get(0)) { not_connected = 1; break; }

	REP(i, 0, n) down[i].clear();
	memset(dfn, -1, sizeof(dfn[0]) * n);
	memset(bad_pair, -1, sizeof(bad_pair[0]) * en);
	dfn_cnt = 0;
	REP(i, 0, pathn) if (!~dfn[path[i]]) get_bad_pairs(path[i]);

	if (not_connected)
	{
		get_lim();
		printf("%lld\n", work());
	}
	else printf("%lld\n", dis[T]);
	return 0;
}