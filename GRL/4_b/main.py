# -*- coding:utf-8 -*-

def solve():
    from collections import deque

    """入力"""
    V, E = list(map(int, input().split()))
    G = [[] for _ in range(V)]  # グラフG[i] = [j1, j2, ...] は、頂点iからj1,j2,...に到達可能なことを示す
    in_degrees = [0 for _ in range(V)]  # 入次数
    for _ in range(E):
        s, t = list(map(int, input().split()))
        G[s].append(t)
        in_degrees[t] += 1

    """トポロジカルソートを作成する
    頂点番号がトポロジカル順序のリストDAGを作成する
    """
    DAG = []
    que = deque()  # 処理する頂点を順番にキューに追加する

    # まず、入次数0の頂点をキューに追加する
    for i, v in enumerate(in_degrees):
        if v == 0:
            que.append(i)

    # 「キューに入っている頂点を削除する」処理を繰り返す
    while len(que) != 0:
        i = que.popleft()

        # 頂点iを削除するので、頂点iに隣接している頂点の入次数を減らす
        for j in G[i]:
            in_degrees[j] -= 1
            if in_degrees[j] == 0:
                que.append(j)  # 入次数が0になった頂点は、キューに追加する

        DAG.append(i)

    """ 頂点をトポロジカル順序で出力する """
    for i in DAG:
        print(i)


if __name__ == "__main__":
    solve()