#ifndef NODE_H
#define NODE_H

#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Node {
    typedef pair<int, T> keyData;
    typedef vector<Node<T>*> childVector;
    typedef vector<pair<int, T>> keyVector;
    typedef typename keyVector::iterator keyIt;
    typedef typename childVector::iterator childIt;

    unsigned int size;
    keyVector keys;
    childVector childs;
    
    public: 
        Node(unsigned int size) : size(size) {
            //keys.resize(size - 1);
            //childs.resize(size);
        }

        bool searchKey(int k, keyIt &it) {
            if (keys.size() == 0) return 0;

            it = find_if(keys.begin(), keys.end(), 
            [&](keyData temp) { return temp.first == k; });
            
            return it != keys.end();
        }

        bool inKeyVector(int k) {
            keyIt it;
            return searchKey(k, it);
        }

        bool safeAddKey(int k, T data) {
            keyIt it;

            if (searchKey(k, it)) {
                (*it).second = data;
                return 0;
            }
            
            keyData temp = make_pair(k, data);

            keys.push_back(temp);
            sort(keys.begin(), keys.end());
            
            return keys.size() == size;
        }

        keyData getMedian() {
            return keys[size/2];
        }

        void addChild(Node<T> *node) {
            childs.push_back(node);
        }

        bool split(Node<T> *node);

        Node<T>* getNextDir(int k) {
            for (int i = 0; i < keys.size(); ++i) {
                if (keys[i].first > k) return childs[i];
            }   return childs[size - 1];
        }

        void print() {
            keyIt kit;
            childIt cit;

            kit = keys.begin();
            cit = childs.begin();

            while (kit != keys.end() || cit != childs.end()) {
                if (cit != childs.end()) {
                    (*cit)->print();
                    cit++;
                }

                if (kit != keys.end()) {
                    cout << (*kit).first << " ";
                    kit++;
                }
            }
        }

        ~Node() {
            keys.clear();
            childs.clear();
        }

        void deleteRecursive() {
            if (!isLeaf()) {
                for (Node<T>* node : childVector)
                    node->deleteRecursive();
            } delete this;
        }

        virtual bool isLeaf() = 0;

};

template <typename T>
class Internal : public Node<T> {
    public:
        Internal(unsigned int size) : Node<T>(size) { }
        
        bool isLeaf() { return 0; }
};

template <typename T>
class Leaf : public Node<T> {
    public: 
        Leaf(unsigned int size) : Node<T>(size) { }
        
        bool isLeaf() { return 1; }

};


template <typename T>
bool Node<T>::split(Node<T> *node) {            
            keys.push_back(node->getMedian());
            
            Node<T> *ptr;
            childIt cit;

            
            if (node->isLeaf())
                childs.push_back(new Leaf<T>(size));
            else {
                cit = node->childs.begin();
                childs.push_back(new Internal<T>(size));
            }
            
            ptr = childs[childs.size() - 1];
            
            for (keyData val : node->keys) {
                if (val == node->getMedian()) {
                    if (node->isLeaf())
                        childs.push_back(new Leaf<T>(size));
                    else {
                        ptr->addChild(*cit);
                        cit++;
                        childs.push_back(new Internal<T>(size));
                    }
                    ptr = childs[childs.size() - 1];
                    continue;
                }   

                ptr->safeAddKey(val.first, val.second);

                if (!node->isLeaf()) {
                    ptr->addChild(*cit);
                    cit++;       
                }
            }
            
            if (!node->isLeaf())
                ptr->addChild(*cit);
            
            delete node;

            return keys.size() == size;
        }

#endif