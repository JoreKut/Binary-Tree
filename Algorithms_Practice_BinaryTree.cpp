#include <iostream>
#include <deque>
#include <cmath>

using namespace std;

void printIndent(int indent) {
    for (int i = 0; i < indent; i++)
        cout << " ";
}
        
class Node
{
public:
    static int max_level;

    string who; // type of node (L/R)

    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    int value;
    int level;
    int indent;
        
    Node(int value, int level){
        indent = 1;
        this->value = value;
        this->level = level;
    }

    void add(Node* child) {
        child->parent = this;

        if (child->value > value) {
            // go right
            if (right != nullptr) {
                child->level++;
                if (child->level > Node::max_level)
                    Node::max_level = child->level;

                right->add(child);
            }
            else
            {
                child->who = "R";
                right = child;

            }
        }
        else
        {
            //go left
            if (left != nullptr) {
                child->level++;
                if (child->level > Node::max_level)
                    Node::max_level = child->level;

                left->add(child);
            }
            else
            {
                child->who = "L";
                left = child;
            }
        }
    }

};

int Node::max_level = 1;

class BinaryTree {
public:

    Node* root;

    BinaryTree(int rootValue) {
        this->root = new Node(rootValue, 1);
    }

    void add(int value) {
        root->add(new Node(value, 2));
    }

    void print() {
        
        int max_lvl = Node::max_level;

        int value_size = 2; // number length

        deque<Node*> nodes;
        
        root->indent = (pow(2, max_lvl - 1) * value_size + pow(2, max_lvl - 1) - 1) / 2;

        nodes.push_back(root);

        while (nodes.size() != 0) {

            int size = nodes.size();
            
            for (int i = 0; i < size; i++) {

                Node* buff = nodes.front();

                printIndent(buff->indent);            
                cout << buff->value;
                
                int indent_addition = pow(2, max_lvl - buff->level - 1) + value_size / 2;
                
                if (buff->left != nullptr) {
                    buff->left->indent = buff->indent - indent_addition;
                    nodes.push_back(buff->left);
                }
                if (buff->right != nullptr) {
                    
                    buff->right->indent = buff->indent + indent_addition - value_size ;
                    nodes.push_back(buff->right);
                }

                nodes.pop_front();

                if (nodes.size() > 0 && buff->level == nodes.front()->level) {
                    if(nodes.front()->indent > buff->indent)
                        nodes.front()->indent -= buff->indent;
                }

            }
            cout << "\n\n\n";

        }

        cout << "The deepest number is " << Node::max_level << endl;

    }

};


int main()
{
    BinaryTree tree = BinaryTree(43);

    tree.add(25);
    tree.add(15);
    tree.add(51);
    tree.add(26);
    tree.add(11);
    tree.add(6);
    tree.add(20);
    tree.add(45);
    tree.add(5);
    tree.add(16);
    tree.add(24);
    tree.add(70);
    tree.add(12);

    // Binary tree: 43, 25, 15, 51, 26, 11, 6, 20, 45, 5, 15, 24, 70, 12;

    cout << "\n\n\n";
    tree.print();
    cout << Node::max_level;

}

