#include "get_next_line.h"

size_t  ft_strlen(const char *str)
{
    size_t  i = 0;

    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int ft_slasher(const char *s, int c)
{
    int	i = 0;

    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == (char)c)
            return (1);
        i++;
    }
    return (0);
}

char    *ft_strjoin(char *s1, char *s2)
{
    size_t  i;
    size_t  j;
    char    *join;

    if (!s1)
    {
        s1 = (char *)malloc(sizeof(char) * 1);
        *s1 = '\0';
    }
    if (!s1 || !s2)
        return (NULL);
    if (!(join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
        return (NULL);
    i = -1;
    while (s1[++i])
        join[i] = s1[i];
    j = -1;
    while (s2[++j])
        join[i + j] = s2[j];
    join[i + j] = '\0';
    free (s1);
    return (join);
}

char    *ft_cut(char *temp)
{
    size_t  i = 0;
    size_t  j = 0;
    char    *cut;

    if (!*temp)
        return (NULL);
    while (temp[i] && temp[i] != '\n')
        i++;
    cut = (char *)malloc(sizeof(char) * (i + 2));
    if (!cut)
        return (NULL);
    while (temp[j] && j <= i)
    {
        cut[j] = temp[j];
        j++;
    }
    cut[j] = '\0';
    return (cut);
}

char    *ft_recut(char  *temp)
{
    size_t  i;
    size_t  j;
    char    *recut;

    i = 0;
    while (temp[i] && temp[i] != '\n')
        i++;
    if (!temp[i])
    {
        free (temp);
        return (NULL);
    }
    recut = (char *)malloc(sizeof(char) * (ft_strlen(temp) -i + 1))
        return (NULL);
    j = 0;
    while (temp[i++])
        recut[j++] = (temp[i]);
    recut[j] = '\0';
    free(temp);
    return (recut);
}

char    *ft_read(int fd, char *temp)
{
    int     byte = 1;
    char    mini[BUFFER_SIZE + 1];

    while (!ft_slasher(temp, '\n') && byte)
    {
        byte = read(fd, mini, BUFFER_SIZE);
        if (byte == -1)
        {
            free (mini);
            return (NULL);
        }
        mini[byte] = '\0';
        temp = ft_strjoin(temp, mini);
    }
    return (temp);
}

char    *get_next_line(int fd)
{
    char        *line;
    static char *maxi;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &maxi, 0) < 0)
        return (NULL);
    maxi = ft_read(fd, maxi);
    if (!maxi)
        return (NULL);
    line = ft_cut(maxi);
    maxi = ft_recut(maxi);
    return (line);
}

/*
int main(void)
{
    char    *str;
    int fd = open("test.txt", O_RDONLY);

    int i = 100;
    while (i--)
    {
        str = get_next_line(fd);
        if (!str)
            break;
        printf("STR :%s", str);
        free (str);
    }
    system ("leaks a.out");
}*/
