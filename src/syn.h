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
    /* input for io */
    const FILE *restrict in;
    /* output for io */
    const FILE *restrict out;
};

struct location {
    /* row in editor */
    int row;
    /* col in editor */
    int col;
};

struct change_data {
    /* what data was added? */
    const char *chars;
    /* where did this change occur? */
    const struct location loc;
};

#endif
