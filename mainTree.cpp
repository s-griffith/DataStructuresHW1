#include "Movie.h"
#include "GenericNode.h"
#include "Node.h"
#include "AVLMultiVariable.h"
#include "AVLTree.h"
#include "ComplexNode.h"
#include <iostream>
#include "wet1util.h"

int main() {
    Tree<GenericNode<int*>, int*> t1;
    for(int i = 1; i<10; i++) {
        t1.insert(&i, i);
    }
    t1.print_tree();
    MultiTree<Movie*> t2;
    Movie m1(1, Genre::NONE, 2, false);
    Movie m2(2, Genre::NONE, 2, false);
    Movie m3(3, Genre::NONE, 3, false);
    Movie m4(4, Genre::NONE, 4, false);

    t2.insert(&m1, 1, 2, 3);
    t2.insert(&m2, 2, 2, 3);
    t2.insert(&m3, 3, 4, 1);
    t2.insert(&m4, 4, 2, 4);
    t2.print_tree();
}