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


/**
 * @brief 二次元座標のKD木。二次元座標の領域内にある点を取得したりする。
 *
 * @tparam T int, long long
 */
template<typename T>
class KDTree {
    public:
        static const T NIL = -1;  // 意味のない値
        /**
         * @brief KDTreeの木構造用ノード
         */
        class Node{
            public:
                T location;  // 位置
                T p, l, r;  // 親, 左の子, 右の子
                Node(){}
        };
        /**
         * @brief 座標クラス
         */
        class Point{
            public:
                T id, x, y;  // 頂点番号, x座標, y座標
                Point(){}
                Point(T id, T x, T y): id(id),x(x),y(y){}
                bool operator<(const Point &p)const{
                    return id < p.id;
                }
        };
        // X座標でソートするための比較関数
        static bool compX(const Point &p1,const Point &p2){return p1.x<p2.x;}
        // Y座標でソートするための比較関数
        static bool compY(const Point &p1,const Point &p2){return p1.y<p2.y;}

    private:
        /**
         * @brief buildメソッドの実態(DFSで構築する)
         *
         * @param l 左の境界値
         * @param r 右の境界値
         * @param depth DFSの深さ
         * @param np ?
         */
        T _build(T l, T r, T depth, T &np) {
            if (!(l<r)) { return NIL; }
            T mid = (l+r)/2;
            T t = np++;
            if (depth%2 == 0) {
                sort(P.begin()+l, P.begin()+r, compX);  // X座標でソート
            }
            else {
                sort(P.begin()+l, P.begin()+r, compY);  // Y座標でソート
            }
            nodes[t].location = mid;
            nodes[t].l = _build(l, mid, depth+1, np);
            nodes[t].r = _build(mid+1, r, depth+1, np);
            return t;
        }

        /**
         * @brief findメソッドの実態
         *
         * @param v
         * @param scoord 領域の開始座標(sx, sy)
         * @param tcoord 領域の終了座標(tx, ty)
         * @param depth DFSの深さ
         * @param ans 領域に含まれる点を格納
         */
        void _find(T v, pair<T, T>scoord, pair<T, T> tcoord, T depth, vector<Point> &ans) {
            auto [sx, sy] = scoord;
            auto [tx, ty] = tcoord;
            T x = P[nodes[v].location].x;
            T y = P[nodes[v].location].y;
            if (sx<=x && x<=tx && sy<=y && y<=ty){
                ans.push_back(P[nodes[v].location]);
            }
            if (depth%2 == 0) {
                if (nodes[v].l != NIL) {
                    if(sx<=x) _find(nodes[v].l,{sx,sy},{tx,ty},depth+1,ans);
                }
                if (nodes[v].r != NIL) {
                    if(x<=tx) _find(nodes[v].r,{sx,sy},{tx,ty},depth+1,ans);
                }
            }
            else {
                if (nodes[v].l != NIL) {
                    if (sy<=y) _find(nodes[v].l,{sx,sy},{tx,ty},depth+1,ans);
                }
                if (nodes[v].r != NIL) {
                    if (y<=ty) _find(nodes[v].r,{sx,sy},{tx,ty},depth+1,ans);
                }
            }
        }

    public:
        T N;  // 頂点数
        vector<Point> P;  // 点を格納するリスト
        vector<Node> nodes;  // 木構造用のNodeを格納するリスト
        T root;  // 根

        KDTree(){}
        KDTree(T N){init(N);}

        void init(T N_){
            N = N_;
            P.assign(N, Point());
            nodes.assign(N, Node());
        }

        /**
         * @brief kdtreeを構築する。計算量は、ソートしてるので O(N (logN)^2)。
         */
        void build() {
            T np = 0;
            root = _build(0, N, 0, np);
        }

        /**
         * @brief 指定の領域内に含まれる座標（Point）のリストを返す
         *
         * @param scoord 領域の開始座標(sx, sy)
         * @param tcoord 領域の終了座標(tx, ty)
         *
         * @note
         * (sx, sy)●────┐
         *         │    │
         *         └────●(tx, ty)
         */
        vector<Point> find(pair<T, T>scoord, pair<T, T> tcoord) {
            vector<Point> ans;
            _find(root, scoord, tcoord, 0, ans);
            return ans;
        }

        /**
         * @brief 二次元座標に点を追加する
         *
         * @param id 頂点番号
         * @param x X座標
         * @param y Y座標
         */
        void add_point(T id, T x, T y) {
            P[id] = Point(id, x, y);
            nodes[id].l = nodes[id].r = nodes[id].p = NIL;
        }

        /**
         * @brief nodesを出力する。デバッグ用。
         */
        void print_nodes() {
            for(ll i=0; i<N; i++) {
                cout << "nodes[" << i << "]: ";
                cout << "location=" << nodes[i].location << " ";
                cout << "p=" << nodes[i].p << " ";
                cout << "l=" << nodes[i].l << " ";
                cout << "r=" << nodes[i].r << endl;
            }
        }

        /**
         * @brief Pを出力する。デバッグ用。
         */
        void print_points() {
            for(ll i=0; i<N; i++) {
                cout << "P[" << i << "]: ";
                cout << "id=" << P[i].id << " ";
                cout << "(x, y)=" << "(" << P[i].x << ", " << P[i].y << ")" << endl;
            }
        }
};


void solve() {
    ll N; cin >> N;

    // KDTreeを構築する
    KDTree kd(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        kd.add_point(i, x, y);
    }
    kd.build();
    // kd.print_nodes();
    // kd.print_points();

    // 各クエリに応える
    ll Q; cin >> Q;
    for(int q=0; q<Q; q++){
        ll sx, tx, sy, ty;
        cin >> sx >> tx >> sy >> ty;

        // 領域内に含まれる点のリストを得て、出力する
        vector<KDTree<ll>::Point> ans;
        ans = kd.find({sx,sy}, {tx,ty});
        sort(ans.begin(), ans.end());
        for(ll j=0; j<(ll)ans.size(); j++){
            cout << ans[j].id << endl;
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}