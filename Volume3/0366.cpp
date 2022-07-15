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

/** 強連結成分分解（SCC）
 * @brief
 * 有向グラフに対して「お互いに行き来できる頂点を同じグループにする」ことを強連結分解（SCC）という。
 *
 * サイクルをグループ分けするイメージ。
 *
 * @tparam T int, long long
 *
 * @param N 頂点数
 * @param G グラフG。G[i] := 頂点iに隣接している頂点集合
 * @example
 * Usage
 *   long long N = 4;
 *   long long M = 7;  // 辺数（使ってない）
 *   vector<set<long long>> graph(N);
 *   graph[0].insert(1);
 *   graph[1].insert(0);
 *   graph[1].insert(2);
 *   graph[3].insert(2);
 *   graph[3].insert(0);
 *   graph[0].insert(3);
 *   graph[1].insert(2);
 *
 *   // SCC実行
 *   SCC scc = SCC<long long>(N, graph);
 *   set<set<long long>> scc_groups = scc.scc_groups();
 *
 *   // SCCを見る
 *   scc.print_scc_groups(scc_groups);
 *   // group0 (size: 3): 0 1 3
 *   // group1 (size: 1): 2
 */
template<typename T>
class SCC {
    private:
        T N;  // 頂点数
        vector<set<T>> graph;  // graph[u] := 頂点uに隣接している頂点vの集合（uからvへの有向辺）
        vector<set<T>> rev_graph;  // graphの有向辺を反転させたグラフrev_graph
        vector<T> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
        vector<T> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）

        /**
         * @brief
         * graphの有向辺を反転させたグラフrev_graphを確定させる。
         * O(頂点数+辺数)。
         */
        void fix_rev_graph() {
            this->rev_graph.assign(this->N, set<T>());
            for(T u=0; u<this->N; u++) {
                for(auto v: graph[u]) {
                    this->rev_graph[v].insert(u);
                }
            }
        }

        void dfs_step1(T u, T &sccid, set<T> &visited) {
            if (visited.count(u)) return;
            if (id2sccid[u]!=-1) return;
            visited.insert(u);

            for(auto v: this->graph[u]) {
                dfs_step1(v, sccid, visited);
            }

            id2sccid[u] = sccid;
            sccid2id[sccid] = u;
            sccid++;
        }

        void dfs_step2(T u, set<T> &visited, vector<bool> &step2_done) {
            if (visited.count(u)) return;
            if (step2_done[id2sccid[u]]) return;
            visited.insert(u);
            step2_done[id2sccid[u]] = true;

            for(auto v: this->rev_graph[u]) {
                dfs_step2(v, visited, step2_done);
            }
        }


    public:
        SCC(T N, vector<set<T>> graph) {
            this->N = N;
            this->graph = graph;
            this->id2sccid.assign(N, -1);
            this->sccid2id.assign(N, -1);
        }

        /**
         * @brief SCCを実行。
         * 計算量O(頂点数+辺数)。
         * @return set<set<T>> 強連結成分のグループ
         */
        set<set<T>> scc_groups() {
            // [ステップ1]
            // DFSの帰りがけ順に番号を振る
            T sccid = 0; // SCCでつける番号
            for(int u=0; u<N; u++) {
                set<T> visited;
                this->dfs_step1(u, sccid, visited);
            }

            // [ステップ2]
            // 辺の向きをすべて反転させ、番号の大きい順からDFSする
            // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
            this->fix_rev_graph();
            vector<bool> step2_done(this->N, false);  // ステップ2で終了したSCCIDを記録する
            set<set<T>> scc_groups;  // 強連結成分のグループ
            for(int i=N-1; i>=0; i--) {
                if (step2_done[i]) continue;
                set<T> visited;
                dfs_step2(sccid2id[i], visited, step2_done);
                scc_groups.insert(visited);
            }

            return scc_groups;
        }

        /**
         * @brief scc_groupsの中身を見る。
         * @param scc_groups
         * @param idx_plus 頂点番号に足す数。デフォルト0。
         */
        void print_scc_groups(set<set<T>> &scc_groups, T idx_plus=0) {
            auto itr = scc_groups.begin();
            for(size_t i=0; i<scc_groups.size(); i++) {
                cout << "group" << i << " (size: " << (*itr).size() << "): ";
                for(auto u: *itr) {
                    cout << u+idx_plus << " ";
                }
                cout << endl;
                itr++;
            }
        }
};


void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    vector<set<ll>> invG(N);  // 反転グラフ
    for(ll i=0; i<M; i++) {
        ll s, t; cin >> s >> t;
        G[s].insert(t);
        invG[t].insert(s);
    }

    // 「強連結成分分解（SCC)して、同じグループのものは1つの頂点とみなすと、DAGになる」性質を使う
    // 同じグループのものは1つの頂点とみなした新しいグラフ（DAG）において、
    // 入次数が0の頂点を根と呼び、出次数が0の頂点を葉と呼ぶことにする。
    // 葉から根に有向辺を張れば、大きなループができてたくさんの道を通れるようになる。
    // 任意の頂点から全ての道を通れるために追加する道の数は、max(根の数, 葉の数)
    // ただし、グループ数が1のときは、道を追加する必要はないので答えは0
    SCC<ll> scc(N, G);
    auto scc_groups = scc.scc_groups();
    if (scc_groups.size() == 1) { cout << 0 << endl; return; }

    // SCC後のDAGの根の判定は、グループ外からグループ内に有向辺が存在しないなら根
    ll root_num = 0;  // 根の数
    for(auto group: scc_groups) {
        bool is_root = true;
        for(ll u: group) {
            for(ll v: invG[u]) {
                if (!group.count(v)) { is_root = false; break; }
            }
            if (!is_root) { break; }
        }
        if (is_root) { root_num++; }
    }

    // SCC後のDAGの葉の判定は、グループ内からグループ外に有向辺が存在しないなら葉
    ll leaf_num = 0;  // 葉の数
    for(auto group: scc_groups) {
        bool is_leaf = true;
        for(ll u: group) {
            for(ll v: G[u]) {
                if (!group.count(v)) { is_leaf = false; break; }
            }
            if (!is_leaf) { break; }
        }
        if (is_leaf) { leaf_num++; }
    }

    cout << (ll)max(root_num, leaf_num) << endl;
}


int main() {
    solve();
    return 0;
}