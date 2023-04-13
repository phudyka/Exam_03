#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char *ft_strcpy(char *s1, char *s2)
{
	int i = 0;

	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return(s1);
}

char *ft_strncpy(char *s1, char *s2, int n)
{
    int i = 0;

    while (s2[i] && i < n)
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return(s1);
}

char *ft_strchr(char *s, int c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == (char)c)
			return(s + i);
		i++;
	}
	return(NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *joined;
	int i = -1;
	int j = -1;
	int len1 = 0;
	int len2 = 0;
    
    if (s1)
        len1 = ft_strlen(s1);
    if (s2)
        len2 = ft_strlen(s2);
    if(!(joined = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
        return (NULL);
    while (++i < len1)
        joined[i] = s1[i];
    while (++j < len2)
        joined[i + j] = s2[j];
    joined[i + j] = '\0';
    free(s1);
    return (joined);
}

char *ft_cut(char *temp)
{
    char *cut;
    int i = 0;
    while (temp[i] && temp[i] != '\n')
        i++;
    cut = (char *)malloc(i + 2);
    if (!cut)
        return NULL;
    ft_strncpy(cut, temp, i);
    cut[i] = '\n';
    cut[i + 1] = '\0';
    return cut;
}

char *ft_recut(char *temp)
{
    char *recut;
    char *pos = ft_strchr(temp, '\n');
    if (!pos)
    {
        free(temp);
        return NULL;
    }
    size_t len = ft_strlen(pos + 1);
    recut = (char *)malloc(len + 1);
    if (!recut)
        return NULL;
    ft_strcpy(recut, pos + 1);
    free(temp);
    return recut;
}

char *ft_read(int fd, char *temp)
{
    char buf[BUFFER_SIZE + 1];
    int byte = 1;
    while (!ft_strchr(temp, '\n') && byte > 0)
    {
        byte = read(fd, buf, BUFFER_SIZE);
        if (byte == -1)
            return (NULL);
        buf[byte] = '\0';
        temp = ft_strjoin(temp, buf);
    }
    return (temp);
}

char *get_next_line(int fd)
{
	char *line;
	static char *temp;

	if (!fd || BUFFER_SIZE <= 0 || read(fd, &temp, 0) < 0)
		return(NULL);
	temp = ft_read(fd, temp);
	if (!temp)
		return (NULL);
	line = ft_cut(temp);
	temp = ft_recut(temp);
	return(line);
}
