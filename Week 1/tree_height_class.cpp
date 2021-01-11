#include <iostream>
#include <vector>

using namespace std;

class Node {
    public :
        int key;
        Node* parent;
        vector <Node*> children;
        Node() {
            this->parent = NULL;
        }
        void setParent(Node* parent_pointer){
            parent = parent_pointer;
            parent->children.push_back(this);
        }
};

int tree_height(Node* parent){
    if (parent->children.size() == 0){
        return 0;
    }
    int h = 0;
    int h2;
    for (Node* nd : parent->children){
        h2 = 1 + tree_height(nd);
        if (h < h2){h = h2;}
    }
    return h;
}

int main(){
    int n;
    cin >> n;
    vector <Node> tree_nodes;
    for (int i = 0; i < n; i++){
        Node new_node;
        new_node.key = i;
        tree_nodes.push_back(new_node);
    }
    int root_node;
    int max_height = 0;
    for (int i = 0; i < n; i++){
        int value;
        cin >> value;
        if (value != -1){
            tree_nodes[i].setParent(&tree_nodes[value]);
        }
        else {root_node = i;}
    }
    max_height = 1+ tree_height(&tree_nodes[root_node]);
    cout << max_height;
    return 0;
}
