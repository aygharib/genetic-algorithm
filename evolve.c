#include "a4.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

static int compareIndividualFitness(const void* a, const void* b) {
    Individual* individual1 = (Individual*) a;
    Individual* individual2 = (Individual*) b;

    if (individual1->fitness < individual2->fitness) {
        return -1;
    } else if (individual1->fitness > individual2->fitness) {
        return 1;
    } else {
        return 0;
    }
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate) {
    srand(time(NULL));

    Individual* population = generate_population(population_size, image->width, image->height, image->max_color);

    comp_fitness_population(image->data, population, population_size);
    qsort(&population[0], population_size, sizeof(Individual), compareIndividualFitness);

    for (int i = 0; i < num_generations; i++) {
        crossover(population, population_size);
        mutate_population(population, population_size, rate);
        comp_fitness_population(image->data, population, population_size);
        qsort(&population[0], population_size, sizeof(Individual), compareIndividualFitness);

        printf("Generation number: %d   Fitness: %lf \n", i, population[0].fitness);
    }

    PPM_IMAGE* final = (PPM_IMAGE*)calloc(1, sizeof(PPM_IMAGE));
    final->width = population[0].image.width;
    final->height = population[0].image.height;
    final->max_color = population[0].image.max_color;
    final->data = (PIXEL*)calloc(final->width * final->height, sizeof(PIXEL));
    memcpy(final->data, population[0].image.data, final->width * final->height * sizeof(PIXEL));

    for (int i = 0; i < population_size; i++) {
        free(population[i].image.data);
    }

    free(population);

    return final;
}

void free_image(PPM_IMAGE *p) {
    free(p->data);
    free(p);
}