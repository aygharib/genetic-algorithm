#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void safe_fscanf(FILE* fp, char* temporaryWord) {
    if (fscanf(fp, "%s", temporaryWord) != 1) {
        printf("Read error");
    }
}

PPM_IMAGE* read_ppm(const char* file_name) {
    FILE* fp = fopen(file_name, "r");

    PPM_IMAGE* image = (PPM_IMAGE*)calloc(1, sizeof(PPM_IMAGE));

    char temporaryWord[100];

    safe_fscanf(fp, temporaryWord);

    if (strcmp(temporaryWord, "P3") != 0) {
        printf("Error, file is not of type P3");
        return NULL;
    }

    safe_fscanf(fp, temporaryWord);
    image->width = atoi(temporaryWord);

    safe_fscanf(fp, temporaryWord);
    image->height = atoi(temporaryWord);

    safe_fscanf(fp, temporaryWord);
    image->max_color = atoi(temporaryWord);

    PIXEL* data = (PIXEL*)calloc(image->width * image->height, sizeof(PIXEL));

    for (int i = 0; i < image->width * image->height; i++) {
        safe_fscanf(fp, temporaryWord);
        data[i].r = atoi(temporaryWord);
        safe_fscanf(fp, temporaryWord);
        data[i].g = atoi(temporaryWord);
        safe_fscanf(fp, temporaryWord);
        data[i].b = atoi(temporaryWord);
    }

    image->data = data;

    fclose(fp);

    return image;
}

void write_ppm(const char* file_name, const PPM_IMAGE* image) {
    FILE* fp = fopen(file_name, "w");

    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", image->width, image->height);
    fprintf(fp, "%d\n", image->max_color);

    for (int i = 0; i < image->width * image->height; i++) {
        fprintf(fp, "%d %d %d ", image->data[i].r, image->data[i].g, image->data[i].b);
    }

    fclose(fp);
}