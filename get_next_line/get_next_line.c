#include "get_next_line.h"

char *get_next_line(int fd)
{
static char *buffer = NULL;
char *line = NULL;
static size_t line_size = 0;
int ret;

arduino
Copy code
if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;

while (1)
{
    if (!buffer || *buffer == '\0')
    {
        free(buffer);
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret <= 0)
            break;
        buffer[ret] = '\0';
    }
    size_t i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
    {
        if (i + 1 >= line_size)
        {
            size_t new_size = line_size + BUFFER_SIZE + 1;
            char *new_line = malloc(new_size);
            if (!new_line)
            {
                free(line);
                free(buffer);
                return NULL;
            }
            if (line)
            {
                size_t j = 0;
                while (line[j] != '\0')
                {
                    new_line[j] = line[j];
                    j++;
                }
                free(line);
            }
            line = new_line;
            line_size = new_size;
        }
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
    {
        buffer += i + 1;
        break;
    }
    if (ret == 0 && i == 0)
        break;
    buffer = NULL;
}
if (line)
    line[i] = '\0';
return line;
}
