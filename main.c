#include <stdio.h>
#include<stdlib.h>

struct Pipes{
    int x1, x2, y1, y2, water, input;
};
struct Pipes *pip;
struct Pipes *pipOrder;

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
    }
    //
    // Ordering the pipes
    //
    // The order is stored in an int array.



    //
    // Calculate water.
    //
    for (int j = 0; j < numberOfPipes; ++j) {
        int key = 0;
        for (int i = 0; i < numberOfPipes; ++i) { // j is beneath i
            int candidateKey = 0;
            if(pip[j].y1 < pip[i].y1 || pip[j].y2 < pip[i].y2 || pip[j].y2 < pip[i].y1 || pip[j].y1 <pip[i].y2){ // If true, then pipe j could be covered by pipe i
                //puts("Candidate");
                if(pip[i].x1 < pip[j].x1 && pip[i].x2 > pip[j].x1 ||
                        pip[i].x2 > pip[j].x2 && pip[i].x1 < pip[j].x2 ||
                        pip[i].x1 > pip[j].x1 && pip[i].x2 < pip[j].x2){ // If true, then pipe i covers pipe j.
                    //puts("Some water gets modified");
                    /* Fully covered */
                    if(pip[j].x1 < pip[i].x1 && pip[j].x2 > pip[i].x2){
                        candidateKey = 0;
                        //puts("Fully covered");
                    }
                    /* Partly covered */
                    else if(pip[j].x1 > pip[i].x1 && pip[j].x2 < pip[i].x2){
                        candidateKey = pip[i].water - (pip[j].x1 + pip[j].x2);
                        //puts("Partly covered");
                    }
                    /* Half covered - To the left */
                    else if(pip[j].x1 > pip[i].x1){
                        candidateKey = pip[j].x2 - pip[i].x2;
                        //puts("Half covered 1");
                    }
                    /* Half covered - To the right */
                    else if(pip[j].x2 < pip[i].x2){
                        candidateKey = pip[i].x1 - pip[j].x1;
                        //puts("Half covered 1");
                    }
                    /* Decides if to update key */
                    if(candidateKey > key){
                        key = candidateKey;
                    }
                }
            }
        }
        printf("The key is %d\n", key);
        pip[j].water = pip[j].water - key;
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