#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

size_t  ft_strlen(const char *str);
int ft_slasher(const char *s, int c);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_cut(char  *temp)
char    *ft_recut(char  *temp);
char    *ft_read(int fd, char *temp);
char *get_next_line(int fd);

#endif
