#ifndef MY_ONEGIN_SORTING_H
#define MY_ONEGIN_SORTING_H

//=============================================================================================================

#include "OneginProcessing.h"

//=============================================================================================================

/**
 * @brief The left sorting comparator based on qsort function.
 * 
 * @param first_struct  the pointer to the first structure containing the pointer to the buffer 
 *                      and the lenth of the string
 * @param second_struct the pointer to the second structure containing the pointer to the buffer 
 *                      and the lenth of the string
 * @return int 
 */

int left_comp(const void* first_struct, const void* second_struct);

//=============================================================================================================

/**
 * @brief The right sorting comparator based on qsort function.
 * 
 * @param first_struct  the pointer to the first structure containing the pointer to the buffer 
 *                      and the lenth of the string
 * @param second_struct the pointer to the second structure containing the pointer to the buffer 
 *                      and the lenth of the string
 * @return int 
 */

int right_comp(const void* first_struct, const void* second_struct);

//=============================================================================================================

/**
 * @brief Calls the function qsort.
 * 
 * @param onegin The pointer to the structure
 * @return int 
 */

int left_sorting(Onegin* onegin);

//=============================================================================================================

/**
 * @brief Calls the function qsort.
 * 
 * @param onegin The pointer to the structure
 * @return int 
 */

int right_sorting(Onegin* onegin);

//=============================================================================================================

/**
 * @brief Prints the source text.
 * 
 * @param onegin   The pointer to the structure
 * @param filename the name of the file
 */

void source_text_output(Onegin* onegin, FILE* filename);

//=============================================================================================================

/**
 * @brief Prints the text sorting from left to right to the file "Sorted from left to right.txt".
 * 
 * @param onegin The pointer to the structure
 * @return int 
 */

int left_sort_output(Onegin* onegin);

//=============================================================================================================

/**
 * @brief Prints the text sorting from left to right to the file "Sorted from right to left.txt".
 * 
 * @param onegin The pointer to the structure
 * @return int 
 */

int right_sort_output(Onegin* onegin);

//=============================================================================================================

/**
 * @brief Gives user an opportunity to choose the type of sorting.
 * 
 * @param onegin The pointer to the structure
 * @return int 
 */

int sorting_choice(Onegin* onegin);

//=============================================================================================================

#endif //MY_ONEGIN_SORTING_H