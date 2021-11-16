#include <iostream>
#include <deque>
#include <cmath>
#include <string> 

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
private:
    string repeat(string s, int count) {
        string ss = "";
        for (int i = 0; i < count; i++)
            ss += s;
        
        return ss;
    }

public:

    Node* root;

    BinaryTree(int rootValue) {
        this->root = new Node(rootValue, 0);
    }

    void add(int value) {
        root->add(new Node(value, 1));
    }
    
    void common_solution() {

        /// <summary>
        ///     This is where the principle of outputting to the console for trees without empty branches is worked out
        ///     This solution is the basis for a solution where not all parts of the tree are filled.
        ///     This can help you understand how it works.
        /// </summary>

        int mx_lvl = Node::max_level;

        int rows = 2*mx_lvl+1;
        int val_width = 2;

        int cols = pow(2, mx_lvl - 1) * 3 - 1;

        int s_pos = 3 * pow(2, mx_lvl - 1)/2 - 1;

        string** m = new string * [rows];
        for (int i = 0; i < rows; i++) {
            m[i] = new string[cols];
            for (int j = 0; j < cols; j++) {
                m[i][j] = repeat(" ", val_width);
            }
        }

        int line = 0;
        for (int i = 0; i < mx_lvl-1; i++) {
            
            int item_number = pow(2, i);
            int s_pos = 3 * pow(2, mx_lvl - i - 2) - 1;
            
            int indent = s_pos * 2 + 1;
            
            int inner_indent = (s_pos - 1) / 2;

            for (int j = 0; j < item_number; j++) {
                m[line][s_pos] = to_string(rand() % 10 + 10);
                
                if (s_pos - 1 >= 0 && s_pos + 2 < cols && i != mx_lvl-2) {

                    for (int x = -inner_indent + 1; x < inner_indent; x++) {
                        if (x == 0) continue;
                        m[line + 1][s_pos + x] = repeat("-", val_width);
                    }
                    m[line + 1][s_pos - 1] = "/ ";
                    m[line + 1][s_pos + 1] = " \\";
                }

                s_pos += indent + 1;
            }

            line += 1;
            
        }
        cout << "\n";
        for (int i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++) {
                cout << m[i][j];
            }
            cout << "\n\n";
        }

    }

    void print() {
        int mx_lvl = Node::max_level;

        int val_width = 2;
        int output_indent = 10;

        int rows = 3 * mx_lvl + 1;
        int cols = pow(2, mx_lvl - 1) * 3 - 1 + output_indent;
        int s_pos = 3 * pow(2, mx_lvl - 2) - 1;

        string** m = new string * [rows];
        for (int i = 0; i < rows; i++) {
            m[i] = new string[cols];
            for (int j = 0; j < cols; j++) {
                m[i][j] = repeat(" ", val_width);
            }
        }

        deque<Node*> node_line;
        
        root->indent = 3 * pow(2, mx_lvl - 2) - 1;
        node_line.push_back(root);

        int line = 0;
        for (int i = 0; i <= mx_lvl; i++) {
            int item_number = pow(2, i);
            item_number = node_line.size();

            int s_pos = 3 * pow(2, mx_lvl - i - 2) - 1;

            int inner_indent = (s_pos - 1) / 2 + 2;

            for (int j = 0; j < item_number; j++) {

                Node* node = node_line.front();
                s_pos = node->indent + output_indent;

                string buff = to_string(node->value);
                while (buff.length() < val_width)
                    buff = buff + " ";

                m[line][s_pos] = buff;

                if (node->left != nullptr) {
                    node->left->indent = node->indent - inner_indent;
                    node_line.push_back(node->left);
                }
                if (node->right != nullptr) {
                    node->right->indent = node->indent + inner_indent;
                    node_line.push_back(node->right);
                }
                    
                if (s_pos - 1 >= 0 && s_pos + 1 < cols && node->left != nullptr) {

                    if (node->left != nullptr) {
                        for (int x = -inner_indent + 1; x < 0; x++) {
                            if(s_pos + x < cols)
                                m[line + 1][s_pos + x] = repeat("-", val_width);
                        }

                        m[line + 1][s_pos - 1] = "/" + repeat(" ", val_width - 1);
                    }
                    if (node->right != nullptr) {
                        for (int x = 1; x < inner_indent; x++) {
                            if (s_pos + x < cols)
                                m[line + 1][s_pos + x] = repeat("-", val_width);
                        }
                        m[line + 1][s_pos + 1] = repeat(" ", val_width - 1) + "\\";

                    }
                    
                }

                node_line.pop_front();
            }


            line += 2;

        }
        cout << "\n";
        for (int i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++) {
                cout << m[i][j];
            }
            cout << "\n";
        }

    }

};


int main()
{
    BinaryTree tree = BinaryTree(42);

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
    tree.add(44);
    tree.add(7);
    tree.add(4);
    tree.add(43);

    // Binary tree: 42, 25, 15, 51, 26, 11, 6, 20, 45, 5, 16, 24, 70, 12, 44, 7, 4, 43;

    cout << "\n\n\n";
    tree.print();
    cout << Node::max_level;

}

