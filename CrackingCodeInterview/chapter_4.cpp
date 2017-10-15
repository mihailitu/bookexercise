#include "chapter_4.h"

Graph::Graph(int vertices) : vNo(vertices) {
    adjacentList.resize(vertices);
    visited.resize(vertices, false);
}

void Graph::addEdge(int v, int w) {
    if (v >= vNo || w >= vNo)
        return;
    adjacentList[v].push_back(w);
}

void Graph::_dfs(int v) {
    visited[v] = true;
    std::cout << v << " ";
    for(auto i : adjacentList[v])
        if (!visited[i])
            _dfs(i);
}

void Graph::DFS(int v) {
    std::fill(visited.begin(), visited.end(), false);
    _dfs(v);
}

void Graph::BFS(int v) {
    std::fill(visited.begin(), visited.end(), false);
    std::list<int> vQueue;

    visited[v] = true;
    vQueue.push_back(v);

    while(!vQueue.empty()) {
        v = vQueue.front();
        std::cout << v << " ";
        vQueue.pop_front();
        for(auto i : adjacentList[v])
            if (!visited[i]) {
                visited[i] = true;
                vQueue.push_back(i);
            }
    }
}

void run_chapter_4()
{
    BinaryTree<int> bt;
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);

    bt.InOrder();
    bt.PostOrder();
    bt.PreOrder();

    BinaryTree<char> bct;
    bct.insert('M');
    bct.insert('B');
    bct.insert('Q');
    bct.insert('Z');
    bct.insert('A');
    bct.insert('C');
    bct.PreOrder();
    bct.InOrder();
    bct.PostOrder();

    Graph g(4);
    g.addEdge(0, 1); g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0); g.addEdge(2, 3);
    g.addEdge(3, 3);
    std::cout << "Graph DFS" << std::endl;
    g.DFS(2);
    std::cout << std::endl << "Graph BFS" << std::endl;
    g.BFS(2);
}
