#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


/** 全方位木DP
 * @note
 *   問題ごとに以下を書き換える
 *   - 型DPと単位元
 *   - 型DPに対する二項演算 merge
 *   - まとめたDPを用いて新たな部分木のDPを計算する add_root
 *   計算量: O(N)
 *
 * @ref https://algo-logic.info/tree-dp/
 *
 * @example
 * // 全方位木DP作成
 * ReRooting reroot(N);
 * for (int i=0; i<N-1; i++) {
 *     int s, t, w; cin >> s >> t >> w;
 *     reroot.add_edge(s, t, w);
 *     reroot.add_edge(t, s, w);
 * }
 * reroot.build();
 *
 * // 各頂点uを根としたときの答え
 * for (ll u=0; u<N; u++) {
 *     cout << "Vertex" << u+1 << ": " << reroot.ans[u].val << endl;
 * }
 *
*/
struct ReRooting {
    /* start 問題ごとに書き換え */
    struct DP {  // DP の型
        ll val;
        DP(ll val_) : val(val_) {}
    };
    const DP identity = DP(0LL);  // 単位元(末端の値は add_root(identity) になるので注意)
    function<DP(DP, DP)> merge = [](DP a, DP b) -> DP {
        return DP(max(a.val, b.val));
    };
    function<DP(DP, ll)> add_root = [](DP a, ll w) -> DP {
        return DP(a.val + w);
    };
    /* end 問題ごとに書き換え */

    // グラフの定義
    struct Edge {
        ll to; // 行き先の頂点番号
        ll w; // 辺の重み
    };
    using Graph = vector<vector<Edge>>;

    vector<vector<DP>> dp;  // dp[v][i]: vから出るi番目の有向辺に対応する部分木のDP
    vector<DP> ans;         // ans[v]: 頂点vを根とする木の答え
    Graph G;

    ReRooting(ll N) : G(N) {
        dp.resize(N);
        ans.assign(N, identity);
    }

    void add_edge(ll a, ll b, ll w) {
        G[a].push_back({b,w});
    }
    void build() {
        dfs(0);            // 普通に木DP
        bfs(0, identity);  // 残りの部分木に対応するDPを計算
    }

    DP dfs(ll u, ll parent=-1, ll w=0) {  // 頂点u, 親parent
        DP dp_cum = identity;
        ll deg = G[u].size();
        dp[u] = vector<DP>(deg, identity);
        for (ll i=0; i<deg; i++) {
            ll v = G[u][i].to;
            if (v == parent) continue;
            dp[u][i] = dfs(v, u, G[u][i].w);
            dp_cum = merge(dp_cum, dp[u][i]);
        }
        return add_root(dp_cum, w);
    }
    void bfs(ll u, const DP& dp_p, ll parent=-1) {  // bfs だが、実装が楽なので中身は dfs になっている
        ll deg = G[u].size();
        for (ll i=0; i<deg; i++) {  // 前のbfsで計算した有向辺に対応する部分木のDPを保存
            if (G[u][i].to == parent) dp[u][i] = dp_p;
        }
        vector<DP> dp_left(deg+1, identity), dp_right(deg+1, identity);  // 累積merge
        for (ll i=0; i<deg; i++) {
            dp_left[i+1] = merge(dp_left[i], dp[u][i]);
        }
        for (ll i=deg-1; i>=0; i--) {
            dp_right[i] = merge(dp_right[i+1], dp[u][i]);
        }

        ans[u] = add_root(dp_left[deg], 0);  // 頂点uの答え

        for (int i=0; i<deg; i++) {  // 一つ隣の頂点に対しても同様に計算
            int v = G[u][i].to;
            if (v == parent) continue;
            bfs(v, add_root(merge(dp_left[i], dp_right[i+1]), G[u][i].w), u);
        }
    }
};

int main() {
    ll N; cin >> N;

    // 全方位木DP作成
    ReRooting reroot(N);
    for (int i=0; i<N-1; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        reroot.add_edge(u, v, 1);
        reroot.add_edge(v, u, 1);
    }
    reroot.build();

    // 各頂点uを根としたときの最長距離
    for (ll u=0; u<N; u++) {
        ll res = reroot.ans[u].val;
        ll ans = (N-1)*2 - res;
        cout << ans << endl;
    }
}