#ifndef UTILS_H
#define UTILS_H

char **split_c(const char *str, char separator);
void destroy_split_array(char **arr);
int is_int(const char *str);
int is_float(const char *str);

#endif