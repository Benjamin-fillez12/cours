#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* make_array(int size) {
    int* array = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = i;
        // printf("array[%d]=%d\n", array[i], i);
    };
    return array;
};

const int getMiddleValue(int* array, int start_index, int end_index) {
    int middle_index = start_index + (end_index - start_index) / 2;
    const int value_at_middle = array[middle_index];
    return value_at_middle;
};

const int getValueAtIndex(int* array, int index, const int size) {
    if (index >= size) {
        printf("%d can't be greater than or equal to the array size.\n", index);
        const int const_error_ptr_number = -1;
        return const_error_ptr_number;
    };
    int* value_ptr = &array[index];
    if (value_ptr == NULL) {
        printf("Getting index \"%d\" from array failed.", index);
        const int const_error_ptr_number = -1;
        return const_error_ptr_number;
    };
    const int registered_value_ptr = *value_ptr;
    return registered_value_ptr;
}

int main(int argc, char** argv) {
    int* arrayData = make_array(atoi(argv[1]));
    const int indexValue = getValueAtIndex(arrayData, 15, atoi(argv[1]));
    const int middleIndexValue = getMiddleValue(arrayData, 0, atoi(argv[1]));
    printf("%d\n", indexValue);
    return 0;
}
