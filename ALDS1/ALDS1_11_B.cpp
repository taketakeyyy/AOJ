#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

void dfs(ll u, ll &t, vector<ll> &d, vector<ll> &f, vector<vector<ll>> const &G) {
    // 発見時刻を書き込む
    if (d[u] == -1) d[u] = t++;

    // 探索
    for(ll v: G[u]) {
        if (d[v] != -1) continue;
        dfs(v, t, d, f, G);
    }

    // 終了時刻を書き込む
    if (f[u] == -1) f[u] = t++;
}

void solve() {
    ll N; cin >> N;
    vector<vector<ll>> G(N+1);
    for(ll i=1; i<=N; i++) {
        ll u, K; cin >> u >> K;
        for(ll k=0; k<K; k++) {
            ll v; cin >> v;
            G[u].push_back(v);
        }
    }

    // DFS探索
    vector<ll> d(N+1, -1);  // 発見時刻
    vector<ll> f(N+1, -1);  // 完了時刻
    ll t = 1;
    for(ll i=1; i<=N; i++) {
        dfs(i, t, d, f, G);
    }

    // 出力
    for(ll i=1; i<=N; i++) {
        cout << i << " " << d[i] << " " << f[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}