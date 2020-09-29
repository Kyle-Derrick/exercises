#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: not found file parameter!");
        return 1;
    }
    char *fname = argv[1];

    FILE *fp;
    if (!(fp = fopen(fname, "r"))) {
        printf("Error: can't open the file!");
        return 1;
    }

    return 0;
}
