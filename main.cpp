#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> b(4);
    b.insert(1, 2);
    b.insert(2, 2);
    b.insert(5, 2);
    b.insert(7, 2);
    b.insert(8, 9);
    

    b.print();

    system("pause");
    return EXIT_SUCCESS;
}