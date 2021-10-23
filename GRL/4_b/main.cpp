#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


/**トポロジカルソート（DAG）
 * 閉路のない有向グラフ
 * 「どの頂点iについても、行き先の頂点番号が、頂点iよりも大きくなる」という性質を持つ
 *
 * Args:
 *  N(T): 頂点数（整数）
 **/
template<typename T>
class DAG {
    private:
        vector<T> in_degrees;  // in_degrees[i] := ノードiの入次数
        vector<vector<T>> G;  // G[i] := ノードiに隣接しているノードの集合（配列）
    public:
        T V;  // 頂点数
        T E = 0;  // 辺の数
        vector<T> dag;  // トポロジカル順序で並んだ要素の配列

        DAG(T N) {
            this->V = N;
            this->in_degrees.assign(N, 0);
            this->G.resize(N);
        }

        /*** 頂点uから頂点vへの辺を追加する
         ***/
        void add_edge(T u, T v) {
            this->G[u].emplace_back(v);
            this->in_degrees[v]++;
        }

        /*** DAGを構築する
         ***/
        void build() {
            deque<T> deq;

            // まず、入次数0の頂点をキューに追加する
            for(T i=0; i<this->V; i++) {
                if (in_degrees[i]==0) deq.push_back(i);
            }

            // 「キューに入っている頂点を削除する」処理を繰り返す
            while(!deq.empty()) {
                T u = deq.front(); deq.pop_front();

                // 頂点uを削除するので、頂点uに隣接している頂点の入次数を減らす
                for(auto v: G[u]) {
                    this->in_degrees[v]--;
                    if (this->in_degrees[v] == 0) deq.push_back(v);  // 入次数が0になった頂点は、キューに追加する
                }

                this->dag.emplace_back(u);
            }
        }
};

void solve(){
    ll V, E; cin >> V >> E;

    // DAGの宣言
    DAG dag = DAG(V);

    // DAGの辺の追加
    for(ll i=0; i<E; i++) {
        ll u, v; cin >> u >> v;
        dag.add_edge(u, v);
    }

    // DAGの構築
    dag.build();

    // 出力
    for(ll i=0; i<V; i++) {
        cout << dag.dag[i] << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}