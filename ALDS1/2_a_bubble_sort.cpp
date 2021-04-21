#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
#define ll long long

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    ll cnt = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N-i-1; j++) {
            if (A[j]>A[j+1]) {
                swap(A[j], A[j+1]);
                cnt++;
            }
        }
    }

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i];
        if (i!=N-1) {
            cout << " ";
        }
    }
    cout << endl;
    cout << cnt << endl;
}


int main() {
    solve();
    return 0;
}