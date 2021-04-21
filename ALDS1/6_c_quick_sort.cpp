#include <stdio.h>
#include <iostream>
#include <tuple>
#include <vector>
#include <deque>
#include <map>

using namespace std;


int partition(vector<pair<char,int>>& A, int l, int r) {
    // 配列A[l..r]を、pivot以下の配列A[l..q]と、pivotより大きい配列A[q+1..r]に分割する
    // pivotのインデックスを返す
    int pivot = A[r].second;
    int i = l;
    for(int j=l; j<=r; j++) {
        if (A[j].second <= pivot) {
            swap(A[i], A[j]);
            i++;
        }
    }
    return i-1;
}

void quick_sort(vector<pair<char, int>>& A, int l, int r) {
    if (l < r) {
        int q = partition(A, l, r);
        quick_sort(A, l, q-1);
        quick_sort(A, q+1, r);
    }
}

void solve() {
    int N; cin >> N;
    vector<pair<char, int>> cards(N);
    map<int, deque<char> > stable_map;  // 安定ソートだったかの確認用
    for(int i=0; i<N; i++) {
        int a; char c;
        cin >> c >> a;
        cards[i] = make_pair(c,a);
        stable_map[a].push_back(c);
    }

    quick_sort(cards, 0, N-1);

    // 安定ソートだったか確認する
    bool is_stable = true;
    for(int i=0; i<N; i++) {
        char c = cards[i].first;
        int a = cards[i].second;
        char c2 = stable_map[a].front(); stable_map[a].pop_front();
        if (c!=c2) {
            is_stable = false;
            break;
        }
    }

    // 出力
    if (is_stable) {
        cout << "Stable" << endl;
    }
    else {
        cout << "Not stable" << endl;
    }
    for(int i=0; i<N; i++) {
        cout << cards[i].first << " " << cards[i].second << endl;
    }
}


int main() {
    solve();
    return 0;
}