#ifndef NODE_HPP
#define NODE_HPP 

#include <utility> // std::pair


typedef std::pair<double, double> Point;


typedef struct Node_ {
    Point xy;
    struct Node_* next;
    struct Node_* prev;
    Node_ () {};
    Node_ (double x, double y): 
        xy(std::make_pair(x, y)) { }
} Node;



#endif /* NODE_HPP */
