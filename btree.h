#ifndef BTREE_H
#define BTREE_H

#include "node.h"
#include <stack>

//enum procedureState = { };

template <typename T>
class BTree {
    private:
        typedef pair<int, T> keyData;
        typedef vector<pair<int, T>> keyVector;
        typedef typename keyVector::iterator vectorIt;

        Node<T>* root;
        unsigned int degree;

        bool find_element(int k, Node<T> *&it, vectorIt &vit) {
            it = root;
            
            while (it) {
                if (it->searchKey(k, vit)) return 1;
                if (it->isLeaf()) return 0;

                it = it->getNextDir(k);
            }
            return 0;
        }

    public:
        BTree(unsigned int degree) : degree(degree), root(nullptr) {};

        T search(int k) { 
            // TODO
            Node<T> *it;
            vectorIt vit;
            if (!find_element(k, it, vit)) return 0;
            return (*vit).second;
        }

        bool insert(int k, T data) {
            // TODO
            if (!root) root = new Leaf<T>(degree);
            
            stack<Node<T>*> path;

            Node<T> *ptr(root), *temp;
            
            while (!ptr->isLeaf()) {
                path.push(ptr);
                
                ptr = ptr->getNextDir(k);
            }

            while(path.size() >= 0) {
                if (ptr->safeAddKey(k, data)) {
                    if (path.size() == 0) {
                        temp = new Internal<T>(degree);
                        temp->split(root);
                        root = temp;
                        return 1;
                    }

                    if (path.top()->split(ptr)) {
                        ptr = path.top();
                        path.pop();
                    }

                } else break;
            }
            return 1;        
        }

        bool remove(int k) {
            // TODO
        }

        void print() {
            // TODO
            root->print();
            cout << endl;
        }

        ~BTree() {
            root->deleteRecursive();
        }
};

#endif