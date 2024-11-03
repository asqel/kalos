#ifndef KALOLS_COMMON_H
#define KALOS_COMMON_H


/// @brief open a file and return its content and its size
/// @param path a path to the file
/// @param file_size a pointer where the size of the file will be stored
/// @return the content of the file, NULL if there was an error
char *kalos_read_file(char *path, int *file_size);

#define kalos_min(a, b) (a < b ? a : b)

#define kalos_max(a, b) (a > b ? a : b)

#endif