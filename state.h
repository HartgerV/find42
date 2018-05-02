#ifndef STATE_H
#define STATE_H

/* The type State is a data type that represents a possible state 
 * of a search problem. It can be a complicated structure, but it 
 * can also be a simple type (like int, char, ..). 
 * Note: if State is a structure, make sure that the structure does not 
 *       contain pointers!
 */

typedef struct {
  int value; //value of node
  int depth; //depth of node
    /* history of actions applied to get from start to current node, stored as
     * index 0 == start
     * index 1 == +1
     * index 2 == *2
     * index 3 == *3
     * index 4 == -1
     * index 5 == /2
     * index 6 == /3
     * */
  int history[1000];
} State;

#endif

