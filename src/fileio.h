#ifndef __FILEIO_H__
#define __FILEIO_H_

#include"syn.h"

/* open a file handle */
int syn_open_file(syn_file_t *res, char *name);
/* read a line from a file handle */
int syn_read_file(syn_file_t *file, char *buf, size_t size);
/* close a file handle */
int syn_close_file(syn_file_t *file);

#endif
