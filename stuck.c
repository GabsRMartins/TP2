#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 1000

void init_vector(int *vector) {
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = 0;
    }
}

int find_element(int *vector, int size, int element) {
    for (int i = 0; i < size; i++) {
        if (vector[i] == element) {
            return i;
        }
    }
    return -1;
}

int add_or_get_distance(int *vector, int size, int element) {
    int index = find_element(vector, size, element);

    int distance = (index == -1) ? 0 : index + 1;

    if (index != -1) {
        for (int i = index; i > 0; i--) {
            vector[i] = vector[i - 1];
        }
    } else {
        for (int i = size - 1; i > 0; i--) {
            vector[i] = vector[i - 1];
        }
    }

    vector[0] = element;

    return distance;
}

void print_vector(int *vector, int size) {
    printf("Vector: ");
    for (int i = 0; i < size; i++) {
        if (vector[i] != 0) {
            printf("%d ", vector[i]);
        }
    }
    printf("\n");
}

int main() {
    int vector[VECTOR_SIZE];

    init_vector(vector);

    char line[1000];
    int offset = 0;

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        int val = strtol(line, NULL, 16);
        if (!offset) offset = val;
        int o = ((val - offset) / 4) + 1;
        printf("%d\n", add_or_get_distance(vector, VECTOR_SIZE, o));
    }

    return 0;
}
