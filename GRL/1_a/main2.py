class BellmanFord():
    """ ベルマンフォード法
    重み付き有向グラフにおける単一始点最短路アルゴリズム
    
    * 使用条件
        - DAG（有向グラフで閉路を持たない）であること
        - 負のコストがあってもOK
    
    * 負の閉路がある場合、最短路は求まらないが、負の閉路の検出はできる
    
    * 計算量はO(V*E)
    """
    class Edge():
        """ 重み付き有向辺 """
        def __init__(self, _from, _to, _cost):
            self.from_ = _from
            self.to = _to
            self.cost = _cost
        
    def __init__(self):
        self.edges = []  # 辺
        self.v_set = set()  # 頂点の集合
    
    @property
    def E(self):
        """ 辺数 """
        return len(self.edges)
    
    @property
    def V(self):
        """ 頂点数 """
        return len(self.v_set)
    
    def add(self, _from, _to, _cost):
        """ 2頂点と、辺のコストを追加する """
        self.edges.append(self.Edge(_from, _to, _cost))
        self.v_set.add(_from)
        self.v_set.add(_to)
    
    def shortest_path(self, s):
        """ 始点sから頂点iまでの最短路を格納したリストを返す 
        Args:
            s(int): 始点s
        Returns:
            d(list): d[i] := 始点sから頂点iまでの最短路
        """
        d = [float("inf")] * self.V
        d[s] = 0
    
        while True:
            do_update = False
            for i in range(self.E):
                e = self.edges[i]
                if d[e.from_] != float("inf") and d[e.to] > d[e.from_]+e.cost:
                    d[e.to] = d[e.from_] + e.cost
                    do_update = True
            
            if not do_update: break
        
        return d
    
    def exist_negative_loop(self):
        """ 負の閉路が存在するか否か
        Returns:
            (bool): 負の閉路が存在する(True)/しない(False)
        """
        d = [0] * self.V
        for i in range(self.V):
            for j in range(self.E):
                e = self.edges[j]
                if d[e.to] > d[e.from_] + e.cost:
                    d[e.to] = d[e.from_] + e.cost
                    # n回目にも更新があるなら負の閉路が存在する
                    if i == self.V-1: return True
        return False
    
if __name__ == "__main__":
    V, E, s = list(map(int, input().split()))
    bf = BellmanFord()
    if V == 1:
        print(0)
        exit()
        
    if E == 0:
        for i in range(V-1):
            bf.add(i, i+1, float("INF"))
    else:
        for i in range(E):
            _from, to, cost = list(map(int, input().split()))
            bf.add(_from, to, cost)
        
        for i in range(V):
            # 入力に存在しない頂点があるとき、適当にINFの辺を作成する
            if not i in bf.v_set:
                bf.add(i, 0, float("inf"))

    d = bf.shortest_path(s)
    
    for i in range(V):
        if i >= len(d):
            print("INF")
            continue

        cost = d[i]
        if cost == float("inf"):
            print("INF")
        else:
            print(cost)
