#include "Movie.h"
#include "GenericNode.h"
#include "Node.h"
#include "AVLMultiVariable.h"
#include "AVLTree.h"
#include "ComplexNode.h"
#include <iostream>
#include "wet1util.h"
#include "StreamingDBa1.h"

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
    streaming_database* ab = new streaming_database();
    ab->add_movie(5, Genre::FANTASY, 500, false);
    ab->add_movie(55, Genre::FANTASY, 500, false);
    ab->add_movie(6, Genre::FANTASY, 500, false);
    ab->add_movie(7, Genre::FANTASY, 500, false);
    ab->add_movie(78, Genre::FANTASY, 500, false);
    ab->add_movie(79, Genre::DRAMA, 500, false);
    ab->add_movie(787, Genre::DRAMA, 500, false);
    ab->add_movie(786, Genre::COMEDY, 500, true);
    ab->add_movie(783, Genre::COMEDY, 500, false);
    ab->add_movie(781, Genre::COMEDY, 500, false);
    ab->add_user(6, true);
    ab->rate_movie(6 ,55, 6);
    ab->remove_movie(7);
    output_t<int> out1 = ab->get_all_movies_count(Genre::NONE);
    output_t<int> out2 = ab->get_all_movies_count(Genre::FANTASY);
    output_t<int> out3 = ab->get_all_movies_count(Genre::COMEDY);
    ab->add_user(5, 1);
    ab->add_user(5, 1);
    ab->add_group(5);
    ab->add_user_to_group(5, 5);

    int b=5;
}