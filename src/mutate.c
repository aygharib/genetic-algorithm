#include "a4.h"
#include <stdlib.h>

void mutate(Individual* individual, double rate) {
    int size = individual[0].image.width * individual[0].image.height;
    int numPixelsToMutate = (int) (rate * size / 100);
    
    for (int i = 0; i < numPixelsToMutate; i++) {
        int index = rand() % size;

        individual->image.data[index].r = rand() % (individual->image.max_color + 1);
        individual->image.data[index].g = rand() % (individual->image.max_color + 1);
        individual->image.data[index].b = rand() % (individual->image.max_color + 1);
    }
}

void mutate_population(Individual* individual, int population_size, double rate) {
    for (int i = population_size / 4; i < population_size; i++) {
        mutate(&individual[i], rate);
    }
}