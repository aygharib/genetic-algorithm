#include "a4.h"
#include <stdlib.h>

PIXEL* generate_random_image(int width, int height, int max_color) {
    PIXEL* A = (PIXEL*)calloc(width * height, sizeof(PIXEL));

    for (int i = 0; i < width * height; i++) {
        A[i].r = rand() % (max_color + 1);
        A[i].g = rand() % (max_color + 1);
        A[i].b = rand() % (max_color + 1);
    }

    return A;
}

Individual* generate_population(int population_size, int width, int height, int max_color) {
    Individual* A = (Individual*)calloc(population_size, sizeof(Individual));

    for (int i = 0; i < population_size; i++) {
        A[i].image.width = width;
        A[i].image.height = height;
        A[i].image.max_color = max_color;
        A[i].image.data = generate_random_image(width, height, max_color);
    }

    return A;
}