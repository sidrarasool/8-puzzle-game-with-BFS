#include<iostream>
#include <queue>

using namespace std;

void printNode(int A[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            cout <<  A[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}
int CalculateHeuristic(int source[][3], int goal[][3])
{
    int counter = 0, i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (source[i][j] != goal[i][j])  counter++;

    return counter;
}

class node {
public: 
    int puzz[3][3];
    int heuristic;

    node(int arr[][3], int h) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                puzz[i][j] = arr[i][j];
            }
        }
        heuristic = h;
    }
    node() { heuristic = NULL; };
  

};

void leftChild(node n, priority_queue<node>& queue, int i,int j, int gState[][3]) {
    if (j > 0) {
        node l(n.puzz, n.heuristic);
        l.puzz[i][j] = l.puzz[i][j - 1];
        l.puzz[i][j - 1] = 0;
        l.heuristic = CalculateHeuristic(l.puzz, gState);
        queue.push(l);
    }
   
}

void rightChild(node n, priority_queue<node>& queue, int i, int j, int gState[][3]) {
    if (j < 2) {
        node r(n.puzz, n.heuristic);
        r.puzz[i][j] = r.puzz[i][j + 1];
        r.puzz[i][j + 1] = 0;
        r.heuristic = CalculateHeuristic(r.puzz, gState);
        queue.push(r);
    }
}
void upChild(node n, priority_queue<node>& queue, int i, int j, int gState[][3]) {
    if (i > 0) {
        node u(n.puzz, n.heuristic);
        u.puzz[i][j] = u.puzz[i - 1][j];
        u.puzz[i - 1][j] = 0;
        u.heuristic = CalculateHeuristic(u.puzz, gState);
        queue.push(u);
    }
}

void downChild(node n, priority_queue<node>& queue, int i, int j, int gState[][3]) {
    if (i < 2) {
        node d(n.puzz, n.heuristic);
        d.puzz[i][j] = d.puzz[i + 1][j];
        d.puzz[i + 1][j] = 0;
        d.heuristic = CalculateHeuristic(d.puzz, gState);
        queue.push(d);
    }
}

bool operator<(const node& p1, const node& p2)
{

    return p1.heuristic > p2.heuristic;
}

void findZeroIndex(int& i, int& j, int arr[][3]) {
    for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++)
        {
            if (arr[k][l] == 0) {
                i = k;
                j = l;
                break;
            }
        }
    }

}
int main() {
    int A[3][3] = { {2,8,3}, {1,6,4}, {7,0,5} };  // the initial array
    int B[3][3] = { {1,2,3}, {8,0,4}, {7,6,5} };    //goal Array

    int heu = CalculateHeuristic(A, B);
    node init(A, heu);

    priority_queue<node> queue;

    queue.push(init);
    int i, j;
    //node onTop;
    node onTop = queue.top();
    while (onTop.heuristic != 0) {
        queue.pop();
        printNode(onTop.puzz);
        findZeroIndex(i, j, onTop.puzz);
        
        leftChild(onTop, queue, i, j, B);
        rightChild(onTop, queue, i, j, B);
        upChild(onTop, queue, i, j, B);
        downChild(onTop, queue, i, j, B);
        onTop= queue.top();
    }
    printNode(onTop.puzz);
    return 0;


}