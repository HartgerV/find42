#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"
#include "fringe.h"

#define RANGE 1000000

Fringe insertValidSucc(Fringe fringe, int value, int history [1000], int depth) {
  State s;
  if ((value < 0) || (value > RANGE)) {
    /* ignore states that are out of bounds */
    return fringe;
  }
  s.value = value;
  memcpy(s.history, history, sizeof history[0] * 1000);
  s.history[depth] = value;
  s.depth = depth;
  return insertFringe(fringe, s);
}

void search(int mode, int start, int goal) {
  Fringe fringe;
  State state;
  int isVisited [RANGE] = {0}; // zero array, to track if numbers have been visited (set to 1 for visited)
  int goalReached = 0;
  int visited = 0;
  int value;
  int depth;

  fringe = makeFringe(mode);
  state.value = start;
  state.actionIndex = 0; //actionIndex 0 == start
  state.depth = 0;
  state.history[0] = start;
  fringe = insertFringe(fringe, state);
  while (!isEmptyFringe(fringe)) {
    /* get a state from the fringe */
    fringe = removeFringe(fringe, &state);
    visited++;

    value = state.value;
    depth = state. depth;
    if (isVisited[value] == 0) { //check if value has been visited before
      printf(" visiting (%d) \n", value);
      isVisited[value] = 1; // mark current value as visited
      /* is state the goal? */
      if (value == goal) {
        goalReached = 1;
        break;
      }
      /* insert neighbouring states */
      fringe = insertValidSucc(fringe, value + 1, state.history, depth + 1); /* rule n->n + 1      */
      if (value != 0) { // ignore neighbouring states that would lead to an infinite chain of 0
        fringe = insertValidSucc(fringe, 2 * value, state.history, depth + 1); /* rule n->2*n        */
        fringe = insertValidSucc(fringe, 3 * value, state.history, depth + 1); /* rule n->3*n        */
        fringe = insertValidSucc(fringe, value - 1, state.history, depth + 1); /* rule n->n - 1      */
        fringe = insertValidSucc(fringe, value / 2, state.history, depth + 1); /* rule n->floor(n/2) */
        fringe = insertValidSucc(fringe, value / 3, state.history, depth + 1); /* rule n->floor(n/3) */
      }
    }
  }
  if (goalReached == 0) {
    printf("goal not reachable ");
  } else {
    printf("goal reached ");
    printf("(%d pathLength )\n", state.depth);
    for(int i = 0; i < depth; i++)
      printf("%d ", state.history[i]);
  }
  printf("(%d nodes visited)\n", visited);
  showStats(fringe);
  deallocFringe(fringe);  
}

void solutionPath(State s) {
    switch (s.actionIndex) {
        case 0:

          break;
        case 1:
          break;
    }
}

int main(int argc, char *argv[]) {
  int start, goal, fringetype;
  if ((argc == 1) || (argc > 4)) {
    fprintf(stderr, "Usage: %s <STACK|FIFO|HEAP> [start] [goal]\n", argv[0]);
    return EXIT_FAILURE;
  }
  fringetype = 0;
  
  if ((strcmp(argv[1], "STACK") == 0) || (strcmp(argv[1], "LIFO") == 0)) {
    fringetype = STACK;
  } else if (strcmp(argv[1], "FIFO") == 0) {
    fringetype = FIFO;
  } else if ((strcmp(argv[1], "HEAP") == 0) || (strcmp(argv[1], "PRIO") == 0)) {
    fringetype = HEAP;
  }
  if (fringetype == 0) {
    fprintf(stderr, "Usage: %s <STACK|FIFO|HEAP> [start] [goal]\n", argv[0]);
    return EXIT_FAILURE;
  }

  start = 0;
  goal = 42;
  if (argc == 3) {
    goal = atoi(argv[2]);
  } else if (argc == 4) {
    start = atoi(argv[2]);
    goal = atoi(argv[3]);
  }

  printf("Problem: route from %d to %d\n", start, goal);
  search(fringetype, start, goal); 
  return EXIT_SUCCESS;
}
