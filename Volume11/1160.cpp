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

ll W, H;
vector<ll> vh = { -1, 0, 1, 0, -1, -1, 1, 1 };
vector<ll> vw = { 0, 1, 0, -1, -1, 1, -1, 1 };

bool is_inside(ll h, ll w) {
    return (h>=0 && h<H && w>=0 && w<W);
}

// 島を探索して、探索済みにする
void dfs(ll h, ll w, vector<vector<ll>> &grid) {
    grid[h][w] = -1;  // 探索済みの陸

    for(ll i=0; i<(ll)vh.size(); i++) {
        ll nh = h + vh[i];
        ll nw = w + vw[i];
        if (!is_inside(nh,nw)) continue;
        if (grid[nh][nw] != 1) continue;
        dfs(nh, nw, grid);
    }
}

void solve() {
    while(true) {
        cin >> W >> H;
        if (W==0 && H==0) break;

        vector<vector<ll>> grid(H, vector<ll>(W, 0));
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                cin >> grid[h][w];
            }
        }

        // DFSで島を探索する
        ll ans = 0;
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (grid[h][w] == 1) {
                    ans++;
                    dfs(h, w, grid);
                }
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