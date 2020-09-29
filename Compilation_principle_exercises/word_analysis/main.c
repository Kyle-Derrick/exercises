#include <stdio.h>
#include "word_analysis.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: not found file parameter!");
        return -1;
    }

    char *target_fn;
    if (argc > 2) {
        target_fn = argv[2];
    } else {
        
    }

    word_analysis(argv[1], argv[1]);

    return 0;
}
