#include <bits/stdc++.h>

using namespace std;

struct Node{

    int     m_key;
    Node*   m_rchild;
    Node*   m_lchild;
    Node(){
        m_rchild = m_lchild = nullptr;
    }
};

void in_order_traversal(Node* node, vector <int>& arr){
    if (node == nullptr){
        return;
    }
    in_order_traversal(node->m_lchild, arr);
    arr.push_back(node->m_key);
    in_order_traversal(node->m_rchild, arr);
}

int main(){
    int n, key, left, right;
    cin >> n;

    vector <Node> tree_nodes(n);
    vector <int> in_order_arr;
    in_order_arr.reserve(n);

    for (int i = 0; i < n; i++){
        cin >> key >> left >> right;
        tree_nodes[i].m_key = key;
        if (left != -1){
            tree_nodes[i].m_lchild = &tree_nodes[left];
        }
        if (right != -1){
            tree_nodes[i].m_rchild = &tree_nodes[right];
        }
    }

    in_order_traversal(&tree_nodes[0], in_order_arr);
    bool incorrect = false;
    for (int i = 0; i < n - 1; i++){
        if (in_order_arr[i] > in_order_arr[i + 1]){
            incorrect = true;
            break;
        }
    }

    if (incorrect)  {cout << "INCORRECT";}
    else            {cout << "CORRECT";}
    return 0;
}
