# -*- coding:utf-8 -*-
# 問題：http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0189

class WarshallFloyd():
    """ワーシャルフロイド法
    計算量:
        O(V**3)
    """
    def __init__(self, v):
        """
        Args:
            V: 頂点数
        """
        self._dist = [[float("inf") for _ in range(v)] for __ in range(v)]  # 隣接行列dist[i][j] := iからjへ行くまでのコスト
        for i in range(v):
            self._dist[i][i] = 0
        self.V = v

    @property
    def dist(self):
        return self._dist

    def update(self, a, b, cost):
        """隣接行列のコストを更新する"""
        self._dist[a][b] = cost

    def shortest_path(self):
        """最短経路を計算する"""
        for k in range(self.V):
            for i in range(self.V):
                for j in range(self.V):
                    self._dist[i][j] = min(self._dist[i][j], self._dist[i][k]+self._dist[k][j])


def solve():
    n = int(input())
    As, Bs, Cs = [], [], []

    V = 0  # 頂点数
    for i in range(n):
        a, b, c = list(map(int, input().split()))
        As.append(a)
        Bs.append(b)
        Cs.append(c)
        V = max(V, a+1, b+1)

    wf = WarshallFloyd(V)

    for i in range(n):
        a, b, c = As[i], Bs[i], Cs[i]
        wf.update(a, b, c)
        wf.update(b, a, c)

    wf.shortest_path()

    ans_id, ans_cost = float("inf"), float("inf")
    for i in range(V):
        total_cost = 0
        for j in range(V):
            total_cost += wf.dist[i][j]
        if total_cost < ans_cost:
            ans_id, ans_cost = i, total_cost
        elif total_cost == ans_cost:
            ans_id = min(ans_id, i)

    print(ans_id, ans_cost)


if __name__ == "__main__":
    solve()
