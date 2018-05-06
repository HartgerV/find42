#include <stdio.h>
#include <stdlib.h>
#define MAXDEPTH 1000000

int dls(int depth, int node, int limit, int goal, int cost) {
    printf("%d \n", node);
    if(node == goal) {
        printf("Goal Found!\n");
        printf("Path cost: %d \n", cost);

        return node;
    }
    if(depth < limit) {
        int result = dls(depth + 1, node + 1, limit, goal, cost + 1);
        if(result !=-1) {
            printf("%d (+1) <- %d, ", node+1, node);
            return result;
        };
        if(node > 0) {
            result = dls(depth + 1, node - 1, limit, goal, cost + 1);
            if (result != -1) {
                printf("%d (-1) <- %d, ", node - 1, node);
                return result;
            };
            result = dls(depth + 1, node * 2, limit, goal, cost + 2);
            if (result != -1) {
                printf("%d (*2) <- %d, ", node * 2, node);
                return result;
            };
            result = dls(depth + 1, node * 3, limit, goal, cost + 2);
            if (result != -1) {
                printf("%d (*3) <- %d, ", node * 3, node);
                return result;
            };
            result = dls(depth + 1, node / 2, limit, goal, cost + 3);
            if (result != -1) {
                printf("%d (/2) <- %d, ", node / 2, node);
                return result;
            };
            result = dls(depth + 1, node / 3, limit, goal, cost + 3);
            if (result != -1) {
                printf("%d (/3) <- %d, ", node / 3, node);
                return result;
            };
        }
    }
    return -1;
}

int ids(int start, int goal) {
    for(int i = 0; i < MAXDEPTH; i++) {
        printf("limit: %d \n", i);
        int found = dls(0, start, i, goal, 0);
        if(found != -1) {
            return found;
        }
    }
}

int main(int argc, char *argv[]) {

    if ((argc == 1) || (argc > 3)) {
        fprintf(stderr, "Usage: %s [start] [goal]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int start = 0;
    int goal = 42;
    if (argc == 2) {
        goal = atoi(argv[1]);
    } else if (argc == 3) {
        start = atoi(argv[1]);
        goal = atoi(argv[2]);
    }

    printf("Found: %d \n",ids(start, goal));
    return EXIT_SUCCESS;
}
