#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template <typename T>
class Node {
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T>*> childs;

    public: 
        Node(unsigned int size) : size(size) {
            keys.resize(size - 1);
            childs.resize(size);
        }

        /**
         * An alternative is to create two different nodes (Internal and Leaf) that inherite from Node 
         * an implement this function
         */
        //virtual bool isLeaf() = 0;

    friend class BTree; 
};

template <typename T>
class Internal : public Node {
    public: 
        Internal(unsigned int size) : Node::size(size) {
        }
        
        bool isLeaf() { return 0; }

    friend class BTree; 
};

template <typename T>
class Leaf : public Node {
    public: 
        Internal(unsigned int size) : Node::size(size) {
        }
        
        bool isLeaf() { return 1; }

    friend class BTree; 
};

#endif