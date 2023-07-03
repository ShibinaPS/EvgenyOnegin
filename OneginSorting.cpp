#include "OneginSorting.h"
#include "OneginProcessing.h"

//=============================================================================================================

int left_comp(const void* first_struct, const void* second_struct)
{
      char* first_string = ((String*)first_struct)->str_ptr;
      char* second_string = ((String*)second_struct)->str_ptr;

      size_t i = 0;
      size_t j = 0;

      if (first_string[i] == '\0' || second_string[j] == '\0')
      {
            return (tolower(first_string[i]) - tolower(second_string[j]));
      }

      while(!(isalpha(first_string[i])))
      {
            i++;
      }

      while(!(isalpha(second_string[j])))
      {
            j++;
      }

      if (tolower(first_string[i]) == tolower(second_string[j]))
      {
            if(first_string[i + 1] == '\0' || second_string[j + 1] == '\0')
            {
                  return (tolower(first_string[i + 1]) - tolower(second_string[j + 1]));
            }

            i++;
            j++;
      }

      else
      {
            return(tolower(first_string[i]) - tolower(second_string[j]));
      }

      return 0;
}

//=============================================================================================================

int right_comp(const void* first_struct, const void* second_struct)
{
      char* first_string = ((String*)first_struct)->str_ptr;
      char* second_string = ((String*)second_struct)->str_ptr;

      size_t i = ((String*)first_struct)->str_len - 1;
      size_t j = ((String*)second_struct)->str_len - 1;

      if (first_string[i] == '\0' || second_string[j] == '\0')
      {
            return (tolower(first_string[i]) - tolower(second_string[j]));
      }

      while(!(isalpha(first_string[i])))
      {
            i--;
      }

      while(!(isalpha(second_string[j])))
      {
            j--;
      }

      if (tolower(first_string[i]) == tolower(second_string[j]))
      {
            if(first_string[i - 1] == '\0' || second_string[j - 1] == '\0')
            {
                  return (tolower(first_string[i - 1]) - tolower(second_string[j - 1]));
            }

            i--;
            j--;
      }

      else
      {
            return (tolower(first_string[i]) - tolower(second_string[j]));
      }

      return 0;

}

//=============================================================================================================

int left_sorting(Onegin* onegin)
{
      qsort(onegin->structs_arr, onegin->strings_num, sizeof(String), left_comp);

      if(left_sort_output(onegin))
      {
            return ERROR_LEFT_COMP_NULLPTR;
      }

      return 0;
}

//=============================================================================================================

int right_sorting(Onegin* onegin)
{
      qsort(onegin->structs_arr, onegin->strings_num, sizeof(String), right_comp);

      if(right_sort_output(onegin))
      {
            return ERROR_RIGHT_COMP_NULLPTR;
      }

      return 0;
}

//=============================================================================================================

void source_text_output(Onegin* onegin, FILE* filename)
{
      fputs("\t--------------Source text--------------\n", filename);

      size_t buff_len = 0;

      while(buff_len < onegin->chars_num)
      {
            size_t cur_str_len = strlen(onegin->buffer_ptr + buff_len);
            fputs(onegin->buffer_ptr + buff_len, filename);
            fputc('\n', filename);
            buff_len += cur_str_len + 1;
      }
}

//=============================================================================================================

int left_sort_output(Onegin* onegin)
{
      onegin->left_comp = fopen("Sorted text from left to right.txt", "w");

      if(onegin->left_comp == nullptr)
      {
            return ERROR_LEFT_COMP_NULLPTR;
      }

      fputs("------------------ Sorted from left to right text ------------------\n", onegin->left_comp);

      for(size_t i = 0; i < onegin->strings_num; i++)
      {
            fputs(onegin->structs_arr[i].str_ptr, onegin->left_comp);
            fputc('\n', onegin->left_comp);
      }

      source_text_output(onegin, onegin->left_comp);

      return 0;
}

//=============================================================================================================

int right_sort_output(Onegin* onegin)
{
      onegin->right_comp = fopen("Sorted text from right to left.txt", "w");

      if(onegin->right_comp == nullptr)
      {
            return ERROR_RIGHT_COMP_NULLPTR;
      }

      fputs("\t------------------ Sorted from right to left text ------------------\n", onegin->right_comp);

      for(size_t i = 0; i < onegin->strings_num; i++)
      {
            fputs(onegin->structs_arr[i].str_ptr, onegin->right_comp);
            fputc('\n', onegin->right_comp);
      }

      source_text_output(onegin, onegin->right_comp);

      return 0;
}

//=============================================================================================================

int sorting_choice(Onegin* onegin)
{
      int type_of_sorting = 0;

      printf("Please, choose a sorting type:\n"
            "* enter 1 if you want from left to right sorting\n"
            "* enter -1 if you want from right to left sorting\n"
            "* enter 0 if you want both type of sorting\n"
            "Your choice is:\n");

      scanf("%d", &type_of_sorting);

      switch(type_of_sorting)
      {
            case(-1):
            {
                  if (right_sorting(onegin))
                  {
                        onegin->error_code = ERROR_RIGHT_COMP_NULLPTR;
                        onegin_dtor(onegin);
                        return ERROR_RIGHT_COMP_NULLPTR;
                  }
                  break;
            }

            case(0):
            {
                  if (left_sorting(onegin))
                  {
                        onegin->error_code = ERROR_LEFT_COMP_NULLPTR;
                        onegin_dtor(onegin);
                        return ERROR_LEFT_COMP_NULLPTR;
                  }

                  else if (right_sorting(onegin))
                  {
                        onegin->error_code = ERROR_RIGHT_COMP_NULLPTR;
                        onegin_dtor(onegin);
                        return ERROR_RIGHT_COMP_NULLPTR;
                  }
                  break;
            }

            case(1):
            {
                  if(left_sorting(onegin))
                  {
                        onegin->error_code = ERROR_LEFT_COMP_NULLPTR;
                        onegin_dtor(onegin);
                        return ERROR_LEFT_COMP_NULLPTR;
                  }
                  break;
            }

            default:
            {
                  onegin->error_code = ERROR_SORTING_CHOICE;
                  onegin_dtor(onegin);
                  return ERROR_SORTING_CHOICE;
            }
      }
      return 0;            
}