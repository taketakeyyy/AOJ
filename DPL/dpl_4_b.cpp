#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
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


// dp[i][k][s] := i枚目まで見て、今までk枚のコインを選んでいて、値段の合計がsのときの場合の数
// 上記はO(N*K*R)なのでTLEする
//
// P1[k] := 前半k枚のコインを選んだときに作れる値段のリスト（ソート済み）
// P2[k] := 後半k枚のコインを選んだときに作れる値段のリスト（ソート済み）
// P1からx枚選ぶことを固定すると、P2からはK-x枚選ぶ。
// P1[x]の値段がp1円のとき、P2[K-x]からは[L-p1, R-p1]の範囲の個数を数えたい。これは二分探索で求められる
void solve() {
    ll N, K, L, R; cin >> N >> K >> L >> R;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // Aから[l,r)の範囲を切り取ってPを作る
    auto genP = [&](ll l, ll r) -> vector<vector<ll>>{
        // Aから[l,r)の範囲を切り取ったものをBとする
        vector<ll> B;
        for(ll i=l; i<r; i++) B.push_back(A[i]);
        ll NB = B.size();

        // bit全探索でPを作る
        vector<vector<ll>> P(NB+1);
        for(ll state=0; state<(1<<NB); state++) {
            ll total = 0; // 値段の合計
            ll num = 0; // 枚数
            for(ll d=0; d<NB; d++) {
                if (state>>d&1) {
                    total += B[d];
                    num++;
                }
            }
            P[num].push_back(total);
        }
        for(ll num=0; num<NB+1; num++) sort(P[num].begin(), P[num].end());
        return P;
    };

    auto P1 = genP(0, N/2); // 前半部分
    auto P2 = genP(N/2, N); // 後半部分

    ll ans = 0;
    // P1からx枚選ぶことを固定する
    for(ll x=0; x<(ll)P1.size(); x++) { // 高々40回
        ll y = K-x; // P2から選ぶ枚数
        if (y>=(ll)P2.size() || y<0) continue;
        for(auto p1: P1[x]) { // 高々2^20回
            ll l = lower_bound(P2[y].begin(), P2[y].end(), L-p1) - P2[y].begin();
            ll r = upper_bound(P2[y].begin(), P2[y].end(), R-p1) - P2[y].begin();
            ans += r-l;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}