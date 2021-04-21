#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * partition(A, l, r)
 * 配列A[l..r]を、
 * * A[l..q-1]の各要素がA[q]以下で、
 * * A[q+1..r]の各要素がA[q]より大きい
 * A[l..q-1]とA[q+1..r]に分割し、
 * インデックスqを返す
 **/
int partition (vector<int>& A, int l, int r) {
    int x = A[r];  // partitionの基準（xより大きい配列と小さい配列に分割する）
    int i = l;
    for(int j=l; j<=r; j++) {
        if (A[j] <= x) {
            swap(A[i], A[j]);
            i++;
        }
    }
    return i-1;
}

void solve() {
    int N; cin >> N;
    vector<int> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    int p = partition(A, 0, N-1);

    // 出力
    for(int i=0; i<N; i++) {
        if (i==p) cout << "[";
        cout << A[i];
        if (i==p) cout << "]";
        if (i!=N-1) cout << " ";
    }
    cout << endl;
}

int main() {
    solve();
}