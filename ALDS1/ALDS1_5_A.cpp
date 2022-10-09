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


// 2**20 = 1048576
// bit全探索で、作れる整数を前計算しておく。
// その後、各クエリについて応答する
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    ll Q; cin >> Q;

    // bit全探索
    set<ll> ints;  // 作ることのできる整数
    for(ll bit=0; bit<(1<<N); bit++) {
        ll total = 0;
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) {
                total += A[d];
            }
        }
        ints.insert(total);
    }

    // 各クエリについて応答する
    for(ll q=0; q<Q; q++) {
        ll M; cin >> M;
        if (ints.count(M)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}


int main() {
    solve();
    return 0;
}