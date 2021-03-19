#include <bits/stdc++.h>

using namespace std;

struct Node{

    int     m_key;
    Node*   m_rchild;
    Node*   m_lchild;
    Node(){
        m_rchild = nullptr;
        m_lchild = nullptr;
    }
};

void in_order_traversal(Node* node){
    if (node == nullptr){
        return;
    }
    in_order_traversal(node->m_lchild);
    cout << node->m_key << " ";
    in_order_traversal(node->m_rchild);
}

void pre_order_traversal(Node* node){
    if (node == nullptr){
        return;
    }
    cout << node->m_key << " ";
    pre_order_traversal(node->m_lchild);
    pre_order_traversal(node->m_rchild);
}

void post_order_traversal(Node* node){
    if (node == nullptr){
        return;
    }
    post_order_traversal(node->m_lchild);
    post_order_traversal(node->m_rchild);
    cout << node->m_key << " ";
}

int main(){
    int n, key, left, right;
    cin >> n;
    vector <Node> tree_nodes(n);
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
    in_order_traversal(&tree_nodes[0]);
    cout << endl;
    pre_order_traversal(&tree_nodes[0]);
    cout << endl;
    post_order_traversal(&tree_nodes[0]);
    return 0;
}
