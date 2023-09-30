#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool binary_search(int* table, int length, int x) {
    int low = 0;
    int high = length - 1;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (x < table[middle]) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    return (high > -1) && (x == table[high]);
}

int main() {
    int length;
    printf("Type in the length of the array...\n");
    scanf("%d", &length);

    int* table = (int*)malloc(length * sizeof(int));

    printf("Type in the table numbers (number >= 0)...\n");
    for (int i = 0; i < length; i++) {
        scanf("%d", &table[i]);
    }

    while (true) {
        int target = -1;
        printf("\nType in the target number... (Type in number < 0 to exit)\n");
        scanf("%d", &target);
        if (target < 0) {
            break;
        }

        long start_clock = clock();
        bool found = binary_search(table, length, target);
        long end_clock = clock();

        printf("CPU execution time: %.8lf s.\n", (double)(end_clock - start_clock) / CLOCKS_PER_SEC);
        printf("Is target in the table: %s\n", found ? "Yes" : "No");
    }

    free(table);

    return 0;
}

// 実行結果
// Type in the length of the array...
// 5
// Type in the table numbers (number >= 0)...
// 1
// 3
// 3
// 5
// 9
//
// Type in the target number... (Type in number < 0 to exit)
// 3
// CPU execution time: 0.00000200 s.
// Is target in the table: Yes
//
// Type in the target number... (Type in number < 0 to exit)
// 5
// CPU execution time: 0.00000100 s.
// Is target in the table: Yes
//
// Type in the target number... (Type in number < 0 to exit)
// 8
// CPU execution time: 0.00000100 s.
// Is target in the table: No
//
// Type in the target number... (Type in number < 0 to exit)
// -1
