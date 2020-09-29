//
// Created by Adam on 2020/9/29.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef WORD_ANALYSIS_WORD_ANALYSIS_H
#define WORD_ANALYSIS_WORD_ANALYSIS_H

#endif //WORD_ANALYSIS_WORD_ANALYSIS_H

extern void word_analysis(char *source_fn, char *target_fn) {
    FILE *source, *target;
    if (!(source = fopen(source_fn, "r"))) {
        printf("Error: can't open the file!");
        exit(-1);
    }

    fclose(source);
}