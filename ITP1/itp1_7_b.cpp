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


void solve() {
    while(1) {
        ll N, X; cin >> N >> X;
        if (N==0 && X==0) break;

        // i,jでループし、kを求める
        ll ans = 0;
        for(ll i=1; i<=N; i++) {
            for(ll j=i+1; j<=N; j++) {
                ll k = X-(i+j);
                if (1<=k && k<=N && j<k) ans++;
            }
        }

        // 出力
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}