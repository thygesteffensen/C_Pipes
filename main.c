#include <stdio.h>
#include<stdlib.h>

struct Pipes{
    int x1, x2, y1, y2, water, isUpdated, input;
};
struct Pipes *pip;
struct Pipes *pipOrder;
void fullyCovered(int j);

int main() {
    //
    // Define pipes
    //
    int numberOfPipes;
    puts("Enter the number of pipes: ");
    scanf("%d", &numberOfPipes);

    pip = (struct Pipes*) malloc(numberOfPipes * sizeof(struct Pipes));
    pipOrder = (struct Pipes*) malloc(numberOfPipes * sizeof(struct Pipes));

    puts("Enter x1 y1 x2 y2 coordinate for every pipe: \n");
    for (int i = 0; i < numberOfPipes; ++i) {
        int tmpx1 = 0, tmpx2 = 0, tmpy1 = 0, tmpy2 = 0;
        scanf("%d %d %d %d", &tmpx1, &tmpy1, &tmpx2, &tmpy2);
        if(tmpx1 < tmpx2){
            pip[i].x1 = tmpx1;
            pip[i].x2 = tmpx2;
            pip[i].y1 = tmpy1;
            pip[i].y2 = tmpy2;
        }
        else{
            pip[i].x1 = tmpx2;
            pip[i].x2 = tmpx1;
            pip[i].y1 = tmpy2;
            pip[i].y2 = tmpy1;
        }
        pip[i].input = i;
        pip[i].water = pip[i].x2 - pip[i].x1;
        printf("%d\n", pip[i].water);
        pip[i].isUpdated = 0;
    }
    //
    // Ordering the pipes
    //
    // The order is stored in an int array.

    int ix1, ix2 , iy1, iy2, jx1, jx2, jy1, jy2;

    //
    // Calculate water.
    //
    for (int j = 0; j < numberOfPipes; ++j) {
        int key = 0;
        int rightX = pip[j+1].x2; // FROM THE RIGHT
        int leftX = 0; // FROM THE LEFT
        int partlyRight = pip[j].x2;
        int partlyLeft = pip[j].x1;
        for (int i = j + 1; i < numberOfPipes; ++i) { // j is beneath i
            ix1 = pip[i].x1, ix2 = pip[i].x2, iy1 = pip[i].y1, iy2 =pip[i].y2,
                    jx1 = pip[j].x1, jx2 = pip[j].x2, jy1 = pip[j].y1, jy2 =pip[j].y2;
            /* Find the smallest and highest point on every pipe */
            int smallest;
            if(pip[j].y1 <= pip[j].y2){
                smallest = pip[j].y1;
            }
            else{
                smallest = pip[j].y2;
            }
            int highest;
            if(pip[i].y1 >= pip[i].y2){
                highest = pip[i].y1;
            }
            else{
                highest = pip[i].y2;
            }
            if(highest >= smallest){
            //if(pip[j].y1 < pip[i].y1 || pip[j].y2 < pip[i].y2 || pip[j].y2 < pip[i].y1 || pip[j].y1 <pip[i].y2){ // If true, then pipe j could be covered by pipe i

                puts("Candidate");
                /* Fully covered */
                if(pip[i].x1 < pip[j].x1 && pip[i].x2 > pip[j].x2){
                    fullyCovered(j);
                }
                /* Is it at all covered? */
                if(pip[i].x2 > pip[j].x1 || pip[i].x1 < pip[j].x2) {
                    /* Is it covered to the right or to the left?
                     * Finds the x value, which covers the pipe
                     * the most, from each side...*/
                    /* To the left */
                    if (pip[i].x1 > pip[j].x1) {
                        if (pip[i].x2 > leftX) {
                            leftX = pip[i].x1;
                        }
                    }
                    /* To the right */
                    else if (pip[i].x2 < pip[j].x2) {
                        if (pip[i].x2 < rightX) {
                            rightX = pip[i].x2;
                        }
                    }

                }
                /* Partly covered */ // = are added recent... could be removed
                if(pip[i].x1 >= pip[j].x1 && pip[i].x2 <= pip[j].x2){
                    if(partlyLeft > pip[i].x1){
                        partlyLeft = pip[i].x1;
                    }
                    if(partlyRight < pip[i].x2){
                        partlyRight = pip[i].x2;
                    }
                }
            }
        }
        puts("Breek");
        /* Now I update the water for pipe j
         * I went through every pipe above j
         * and stored the value, that covers
         * the pipe the most
         */
        if(pip[j].isUpdated == 1){
            break;
        }
        if(partlyLeft == pip[j].x1 && partlyRight == pip[j].x2){
            fullyCovered(j);
            // If one or more partly i pipes, covers pipe j fully
        }
        else if(leftX == pip[j].x2 && rightX == pip[j].x1){
            fullyCovered(j);
            // If one or more right/left partly i pipes, covers
            // pipe j fully.
        }
        else if((leftX == pip[j].x2 && partlyLeft == pip[j].x1) ||
                (rightX == pip[j].x1 && partlyRight == pip[j].x2)){
            fullyCovered(j);
            // Rest of fully covered possibilities.
        }
        else if(leftX == rightX && leftX != 0){
            fullyCovered(j);
            // if to covers the whole pipe from both sides
        }
        else if(partlyLeft == 0 && partlyRight == 0){
            // There is no partly covering pipes.
            if(leftX == 0 && rightX != 0){
//                int water = pip[j].water - (pip[j].x2 - rightX);
//                int diff = pip[j].x2 - rightX;
//                pip[j].water = water;
//                printf("Water: %d\nDiff: %d\nrX: %d\npX: %d\n", water, diff, rightX, pip[j].x2);
                pip[j].water = pip[j].water - (pip[j].x2 - rightX);
            }
            else if(rightX == 0 && leftX != 0){
                pip[j].water = pip[j].water - (leftX - pip[j].x1);
            }
            else if(rightX != 0 && leftX != 0){
                pip[j].water = pip[j].water - (leftX - pip[j].x1) + (pip[j].x2 - rightX);
            }
            pip[j].isUpdated = 1;
        }
        else if(leftX == 0 && rightX == 0){
            // if their is no covering from the sides
            pip[j].water = pip[j].water - (partlyRight - partlyLeft);
            pip[j].isUpdated = 1;
        }




    }
    //
    // Calculate water flow.
    //
    for (int k = 0; k < numberOfPipes; ++k) {
        for (int i = 0; i < numberOfPipes; ++i) {
            if(pip[k].y1 > pip[i].y1 && pip[k].y1 < pip[k].y2){ // Is it possible to get water from pipe k to i?
                if(pip[k].x1 >= pip[i].x1 && pip[k].x1 <= pip[i].x2){ // Is pipe i beneath pipe k?
                    pip[i].water = pip[i].water + pip[k].water;
                    break;
                }
            }
            if(pip[k].y2 > pip[i].y2 && pip[k].y1 > pip[k].y2){
                if(pip[k].x2 >= pip[i].x1 && pip[k].x2 <= pip[i].x2){ // Is pipe i beneath pipe k?
                    pip[i].water = pip[i].water + pip[k].water;
                    break;
                }
            }
        }
    }

    for (int j = 0; j < numberOfPipes; ++j) {
    printf("%d \n", pip[j].water);
    }
}

void fullyCovered(int j){
    pip[j].water = 0;
    pip[j].isUpdated = 1;
    puts("Fully covered");
}