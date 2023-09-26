#ifndef MY_ONEGIN_PROCESSING_H
#define MY_ONEGIN_PROCESSING_H

//=============================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <cctype>

//=============================================================================================================

typedef struct String
{
      char* str_ptr  = nullptr;
      size_t str_len = 0;
}str;

//=============================================================================================================

typedef struct Onegin
{
      FILE* mainfile   = nullptr;
      FILE* left_comp  = nullptr;
      FILE* right_comp = nullptr;

      char* buffer_ptr    = nullptr;
      String* structs_arr = nullptr;

      size_t chars_num   = 0;
      size_t strings_num = 0;

      int error_code = 0;
}onegin;

//=============================================================================================================

/**
 * @brief Contains error codes.
 * 
 */

enum OneginErrors
{
      ERROR_MAINFILE_OPEN           = 1,
      ERROR_STAT_SIZE               = 2,
      ERROR_BUFFER_NULLPTR          = 3,
      ERROR_FREAD_COUNT             = 4,
      ERROR_STRUCTS_ARRAY_NULLPTR   = 5,
      ERROR_LEFT_COMP_NULLPTR       = 6,
      ERROR_RIGHT_COMP_NULLPTR      = 7,
      ERROR_SORTING_CHOICE          = 8,
      ERROR_UNKNOWN_ERROR           = 9,
};

//=============================================================================================================

/**
 * @brief Creates and initializes Onegin.
 * 
 * @param onegin the pointer to the structure
 * @param filename the name of the file
 * @return int 
 */

int onegin_ctor(Onegin* onegin, const char* filename);

//=============================================================================================================

/**
 * @brief Opens the source file "input.txt".
 * 
 * @param onegin the pointer to the structure
 * @param filename the name of the file
 * @return int 
 */

int file_open(Onegin* onegin, const char* filename);

//=============================================================================================================

/**
 * @brief Counts the number of chars in the source text "input.txt".
 * 
 * @param onegin the pointer to the structure
 * @param filename the name of the file
 * @return int 
 */

int num_of_chars(Onegin* onegin, const char* filename);

//=============================================================================================================

/**
 * @brief Reads the text from the source file "input.txt" and fills the buffer with it.
 * 
 * @param onegin the pointer to the structure
 * @param filename the name of the file
 * @return int 
 */

int chars_buffer(Onegin* onegin, FILE* filename);

//=============================================================================================================

/**
 * @brief Counts the number of strings in the source file.
 * 
 * @param onegin the pointer to the structure
 */

void num_of_strings(Onegin* onegin);

//=============================================================================================================

/**
 * @brief Fills 2 fields in the structure of array: the pointer to the buffer and the lenth of each string.
 * 
 * @param onegin the pointer to the structure
 * @return int 
 */

int fill_structs_arr(Onegin* onegin);

//=============================================================================================================

/**
 * @brief Frees the buffer and resets the parameters.
 * 
 * @param onegin the pointer to the structure
 */

void onegin_dtor(Onegin* onegin);

//=============================================================================================================

#endif //MY_ONEGIN_PROCESSING_H