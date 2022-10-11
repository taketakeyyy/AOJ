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

bool is_inside(ll x, ll y) {
    return (x>=0 && x<8 && y>=0 && y<8);
}

bool is_puttable(ll r, ll c, vector<vector<char>> &grid) {
    // 縦と横
    for(ll i=0; i<8; i++) {
        if (i!=c) {
            if (grid[r][i]=='Q') return false;
        }
        if (i!=r) {
            if (grid[i][c]=='Q') return false;
        }
    }
    {// 左上
        ll x=r, y=c;
        while(1) {
            x--; y--;
            if (!is_inside(x,y)) break;
            if (grid[x][y]=='Q') return false;
        }
    }
    {// 右上
        ll x=r, y=c;
        while(1) {
            x++; y--;
            if (!is_inside(x,y)) break;
            if (grid[x][y]=='Q') return false;
        }
    }
    {// 左下
        ll x=r, y=c;
        while(1) {
            x--; y++;
            if (!is_inside(x,y)) break;
            if (grid[x][y]=='Q') return false;
        }
    }
    {// 右下
        ll x=r, y=c;
        while(1) {
            x++; y++;
            if (!is_inside(x,y)) break;
            if (grid[x][y]=='Q') return false;
        }
    }
    return true;
}

// クイーンは各行、各列に1個ずつしか置けない
// 各行に1個置くとして、どの列に置くかは順列全列挙で試して判定する
void solve() {
    ll K; cin >> K;
    vector<pair<ll,ll>> queens;
    vector init_grid(8, vector<char>(8, '.'));
    for(ll k=0; k<K; k++) {
        ll r, c; cin >> r >> c;
        queens.push_back({r,c});
        init_grid[r][c] = 'Q';
    }

    vector<ll> A(8);
    for(ll i=0; i<8; i++) A[i] = i;
    sort(A.begin(), A.end());

    // どの列にクイーンを置くかは順列全列挙
    do {
        vector grid = init_grid;
        for(ll i=0; i<8; i++) {
            ll c = A[i];
            grid[i][c] = 'Q';
        }

        // どのクイーンも襲撃できないかチェック
        bool is_ok = true;
        for(ll r=0; r<8; r++) {
            for(ll c=0; c<8; c++) {
                if (grid[r][c] == 'Q') {
                    if (!is_puttable(r,c,grid)) is_ok = false;
                    break;
                }
            }
            if (!is_ok) break;
        }

        if (is_ok) {
            // 出力
            for(ll r=0; r<8; r++) {
                for(ll c=0; c<8; c++) {
                    cout << grid[r][c];
                }
                cout << endl;
            }
        }
    }while (next_permutation(A.begin(), A.end()));
}


// 各クイーンが正しく置けているかチェック
bool check_queens(set<pair<ll,ll>> queens) {
    if ((ll)queens.size() > 8) return false;

    // 各クイーンのななめ方向の判定（行の差 - 列の差が一致したら駄目）
    auto it1 = queens.begin();
    while (it1 != queens.end()) {
        auto it2 = it1; it2++;
        while(it2 != queens.end()) {
            auto [r1, c1] = *it1;
            auto [r2, c2] = *it2;
            if (abs(r1-r2) == abs(c1-c2)) return false;
            it2++;
        }
        it1++;
    }
    return true;
}

// クイーンは各行、各列に1個ずつしか置けない
// 各行に1個置くとして、どの列に置くかは順列全列挙で試して判定する
void solve2() {
    ll K; cin >> K;
    set<pair<ll,ll>> init_queens;
    for(ll k=0; k<K; k++) {
        ll r, c; cin >> r >> c;
        init_queens.insert({r,c});
    }

    vector<ll> A(8);
    for(ll i=0; i<8; i++) A[i] = i;
    sort(A.begin(), A.end());

    // どの列にクイーンを置くかは順列全列挙
    do {
        // クイーンを配置
        set queens = init_queens;
        for(ll i=0; i<8; i++) {
            queens.insert({i,A[i]});
        }

        // どのクイーンも襲撃できないかチェック
        if (check_queens(queens)) {
            // 出力
            for(ll r=0; r<8; r++) {
                for(ll c=0; c<8; c++) {
                    if (queens.count({r,c})) cout << 'Q';
                    else cout << '.';
                }
                cout << endl;
            }
        }
    }while (next_permutation(A.begin(), A.end()));
}

int main() {
    // solve();
    solve2();
    return 0;
}