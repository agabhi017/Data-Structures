#include <bits/stdc++.h>

using namespace std;

struct Node{

    long long   m_key;
    int         m_index;
    Node*       m_rchild;
    Node*       m_lchild;
    Node(){
        m_rchild = m_lchild = nullptr;
    }
};

void in_order_traversal(Node* node, vector <long long>& arr, vector <int>& indices){
    if (node == nullptr){
        return;
    }
    in_order_traversal(node->m_lchild, arr, indices);
    arr.push_back(node->m_key);
    indices.push_back(node->m_index);
    in_order_traversal(node->m_rchild, arr, indices);
}

bool find_key(Node* node, long long key){
   if (node == nullptr){return false;}

   if (node->m_key == key)      {return true;}
   else if (node->m_key > key)  {return find_key(node->m_lchild, key);}
   else if (node->m_key < key)  {return find_key(node->m_rchild, key);}
   return false;
}

int main(){
    int n, left, right;
    long long key;
    cin >> n;

    vector <Node> tree_nodes(n);
    vector <long long> in_order_arr;
    vector <int> node_indices;
    in_order_arr.reserve(n);
    node_indices.reserve(n);

    for (int i = 0; i < n; i++){
        cin >> key >> left >> right;
        tree_nodes[i].m_key = key;
        tree_nodes[i].m_index = i;
        if (left != -1){
            tree_nodes[i].m_lchild = &tree_nodes[left];
        }
        if (right != -1){
            tree_nodes[i].m_rchild = &tree_nodes[right];
        }
    }

    in_order_traversal(&tree_nodes[0], in_order_arr, node_indices);
    bool incorrect = false;
    for (int i = 0; i < n - 1; i++){
        if (in_order_arr[i] > in_order_arr[i + 1]){
            incorrect = true;
            break;
        }
        else if (in_order_arr[i] == in_order_arr[i + 1]){
            bool bool_1 = find_key(tree_nodes[node_indices[i]].m_lchild, in_order_arr[i]);
            bool bool_2 = find_key(tree_nodes[node_indices[i + 1]].m_lchild, in_order_arr[i + 1]);
            if (bool_1 || bool_2){
                incorrect = true;
                break;
            }
        }
    }

    if (incorrect)  {cout << "INCORRECT";}
    else            {cout << "CORRECT";}
    return 0;
}
