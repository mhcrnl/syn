#ifndef __SYN_H__
#define __SYN_H__

#include<stdio.h>
#include<uv.h>

#define u(x) ((void)(x))

#ifdef DEBUG
#define debug_n(fmt, ...); \
    fputs("DEBUG::> ", stderr); \
    fprintf(stderr, fmt, __VA_ARGS__); \
    fputc('\n', stderr);
#else
#define debug(fmt, ...)
#endif

#define pluralize(num) num != 1 ? "s" : ""

/* holds data for io transactions */
struct io {
    FILE *restrict input;
    FILE *restrict output;
};

struct location {
    int row;
    int col;
};

struct change_data {
    /* what data was added? */
    char *chars;
    /* where did this change occur? */
    struct location loc;
};

#endif
