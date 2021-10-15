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


// 最長増加部分列(LIS)
ll LIS(const vector<ll> &A) {
    ll N = (ll)A.size();
    // dp[i] := 増加部分列の長さがiのときの、数列の最終要素の最小値
    vector<ll> dp(N, INF);
    for(ll i=0; i<N; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), A[i]);
        *it = A[i];
    }

    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    cout << LIS(A) << endl;
}


int main() {
    solve();
    return 0;
}