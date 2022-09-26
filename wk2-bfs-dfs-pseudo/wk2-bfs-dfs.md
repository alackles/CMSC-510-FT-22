# Pseudocode for BFS/DFS

## BFS Pseudocode

```
BFS(G, s)

    for each vertex u in G.V - {s}:
        u.color = WHITE
        u.d = inf 
        u.pi = NIL
    s.color = GREY
    s.d = 0
    s.pi = NIL
    Q = []
    ENQUEUE(Q,s)
    
    while Q not empty:
        u = DEQUEUE(Q)
        for each vertex v in G.Adj[u]:
            if v.color == WHITE: 
                v.color = GREY
                v.d = u.d + 1
                v.pi = u 
                ENQUEUE(Q, v)
        u.color = BLACK
```

## DFS Pseudocode 

```
DFS(G):
    for each vertex u in G.V
        u.color = WHITE
        u.pi = NIL
    time = 0 
    for each vertex u in G.V
        if u.color == WHITE
            DFS-VISIT(G,u)

DFS-VISIT(G, u)
    time = time + 1
    u.d = time
    u.color = GREY
    for each vertex v in G.Adj[u]
        if v.color == WHITE
            v.pi = u
            DFS-VISIT(G, v)
    time = time + 1
    u.f = time 
    u.color = BLACK
```
