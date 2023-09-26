#include "OneginProcessing.h"
#include "OneginSorting.h"

//=============================================================================================================

int onegin_ctor(Onegin* onegin, const char* filename)
{
      if(file_open(onegin, filename))
      {
            return ERROR_MAINFILE_OPEN;
      }

      if(num_of_chars(onegin, filename))
      {
            return ERROR_STAT_SIZE;
      }

      switch(chars_buffer(onegin, onegin->mainfile))
      {
            case(0):
            {
                  break;
            }

            case(ERROR_BUFFER_NULLPTR):
            {
                  return ERROR_BUFFER_NULLPTR;
            }

            case(ERROR_FREAD_COUNT):
            {
                  return ERROR_FREAD_COUNT;
            }

            default:
            {
                  return -1;
            }
      }

      if(fill_structs_arr(onegin))
      {
            return ERROR_STRUCTS_ARRAY_NULLPTR;
      }

      return 0;
}

//=============================================================================================================

int file_open(Onegin* onegin, const char* filename)
{
      onegin->mainfile = fopen(filename, "r+");

      if (onegin->mainfile == nullptr)
      {
            onegin->error_code = ERROR_MAINFILE_OPEN;
            onegin_dtor(onegin);
            return ERROR_MAINFILE_OPEN;
      }
      return 0;
}

//=============================================================================================================

int num_of_chars(Onegin* onegin, const char* filename)
{
      struct stat buf{};
      
      stat(filename, &buf); 

      if(buf.st_size <= 0)
      {
            onegin->error_code = ERROR_STAT_SIZE;
            onegin_dtor(onegin);
            return ERROR_STAT_SIZE;
      }

      onegin->chars_num = buf.st_size + 1;
      
      return 0;
}

//=============================================================================================================

int chars_buffer(Onegin* onegin, FILE* filename)
{
      onegin->buffer_ptr = (char*)calloc(onegin->chars_num, sizeof(char));

      if (onegin->buffer_ptr == nullptr)
      {
            onegin->error_code = ERROR_BUFFER_NULLPTR;
            onegin_dtor(onegin);
            return ERROR_BUFFER_NULLPTR;
      }

      size_t fread_count = fread(onegin->buffer_ptr, sizeof(char), onegin->chars_num - 1, filename);

      num_of_strings(onegin);

      if(fread_count != (onegin->chars_num - onegin->strings_num))
      {
            onegin->error_code = ERROR_FREAD_COUNT;
            onegin_dtor(onegin);
            return ERROR_FREAD_COUNT;
      }

      onegin->buffer_ptr[onegin->chars_num - 1] = '\0';

      return 0;
}

//=============================================================================================================

void num_of_strings(Onegin* onegin)
{
      for(size_t i = 0; i <= onegin->chars_num; i++)
      {
            if(onegin->buffer_ptr[i] == '\n')
            {
                  onegin->buffer_ptr[i] = '\0';
                  onegin->strings_num++;
            }
            else if(onegin->buffer_ptr[i] == '\r')
            {
                  onegin->buffer_ptr[i] = '\0';
                  onegin->strings_num--;
            }
      }
      onegin->strings_num++;
}

//=============================================================================================================

int fill_structs_arr(Onegin* onegin)
{
      onegin->structs_arr = (String*)calloc(onegin->strings_num, sizeof(String));

      if(onegin->structs_arr == nullptr)
      {
            onegin->error_code = ERROR_STRUCTS_ARRAY_NULLPTR;
            onegin_dtor(onegin);
            return ERROR_STRUCTS_ARRAY_NULLPTR;
      }

      size_t counter = 0;

      for(size_t i = 0; i < onegin->strings_num; i++)
      {
            onegin->structs_arr[i].str_ptr = onegin->buffer_ptr + counter;
            onegin->structs_arr[i].str_len = strlen(onegin->buffer_ptr + counter);

            counter += onegin->structs_arr[i].str_len + 1;
      };
      return 0;
}

//=============================================================================================================

void onegin_dtor(Onegin* onegin)
{
      switch(onegin->error_code)
      {
            case(0):
            {
                  onegin->chars_num       = 0;
                  onegin->strings_num     = 0;
                  onegin->error_code      = 0;

                  for(size_t i = 0; i <= onegin->strings_num; i++)
                  {
                        onegin->structs_arr[i].str_ptr = nullptr;
                        onegin->structs_arr[i].str_len = 0;
                  }

                  free(onegin->buffer_ptr);
                  onegin->buffer_ptr = nullptr;

                  free(onegin->structs_arr);
                  onegin->structs_arr = nullptr;

                  fclose(onegin->mainfile);
                  onegin->mainfile = nullptr;

                  if(onegin->left_comp != nullptr)
                  {
                        fclose(onegin->left_comp);
                        onegin->left_comp = nullptr;
                  }

                  if(onegin->right_comp != nullptr)
                  {
                        fclose(onegin->right_comp);
                        onegin->right_comp = nullptr;
                  }

                  break;
            }

            case(ERROR_MAINFILE_OPEN):
            {
                  onegin->error_code = 0;
                  break;
            }

            case(ERROR_STAT_SIZE):
            {
                  onegin->error_code = 0;

                  fclose(onegin->mainfile);
                  onegin->mainfile   = nullptr;

                  break;
            }

            case(ERROR_BUFFER_NULLPTR):
            {
                  onegin->error_code = 0;
                  onegin->chars_num  = 0;

                  fclose(onegin->mainfile);
                  onegin->mainfile   = nullptr;

                  break;
            }

            case(ERROR_FREAD_COUNT):
            {
                  onegin->error_code      = 0;
                  onegin->strings_num     = 0;
                  onegin->chars_num       = 0;
                  
                  fclose(onegin->mainfile);
                  onegin->mainfile   = nullptr;

                  free(onegin->buffer_ptr);
                  onegin->buffer_ptr = nullptr;

                  break;
            }

            case(ERROR_STRUCTS_ARRAY_NULLPTR):
            {
                  onegin->chars_num       = 0;
                  onegin->strings_num     = 0;
                  onegin->error_code      = 0;

                  for(size_t i = 0; i <= onegin->strings_num; i++)
                  {
                        onegin->structs_arr[i].str_ptr = nullptr;
                        onegin->structs_arr[i].str_len = 0;
                  }

                  free(onegin->buffer_ptr);
                  onegin->buffer_ptr = nullptr;

                  fclose(onegin->mainfile);
                  onegin->mainfile = nullptr;

                  break;
            }
            
            case(ERROR_LEFT_COMP_NULLPTR):
            {
                  onegin->chars_num   = 0;
                  onegin->strings_num = 0;
                  onegin->error_code  = 0;

                  for(size_t i = 0; i < onegin->strings_num; i++)
                  {
                        onegin->structs_arr[i].str_len = 0;
                        onegin->structs_arr[i].str_ptr = nullptr;
                  }

                  free(onegin->buffer_ptr);
                  onegin->buffer_ptr = nullptr;  

                  free(onegin->structs_arr);
                  onegin->structs_arr = nullptr;

                  fclose(onegin->mainfile);
                  onegin->mainfile = nullptr;

                  if(onegin->right_comp != nullptr)   
                  {
                        fclose(onegin->right_comp);
                        onegin->right_comp = nullptr;
                  } 

                  break;
            }

            case(ERROR_RIGHT_COMP_NULLPTR):
            {
                  onegin->chars_num   = 0;
                  onegin->strings_num = 0;
                  onegin->error_code  = 0;

                  for(size_t i = 0; i < onegin->strings_num; i++)
                  {
                        onegin->structs_arr[i].str_len = 0;
                        onegin->structs_arr[i].str_ptr = nullptr;
                  }

                  free(onegin->buffer_ptr);
                  onegin->buffer_ptr = nullptr;  

                  free(onegin->structs_arr);
                  onegin->structs_arr = nullptr;

                  fclose(onegin->mainfile);
                  onegin->mainfile = nullptr;

                  if(onegin->left_comp != nullptr)   
                  {
                        fclose(onegin->right_comp);
                        onegin->right_comp = nullptr;
                  } 

                  break;
            }

            case(ERROR_SORTING_CHOICE):
            {
                  onegin->chars_num   = 0;
                  onegin->strings_num = 0;
                  onegin->error_code  = 0;

                  for(size_t i = 0; i < onegin->strings_num; i++)
                  {
                        onegin->structs_arr[i].str_len = 0;
                        onegin->structs_arr[i].str_ptr = nullptr;
                  }

                  free(onegin->buffer_ptr);
                  onegin->buffer_ptr = nullptr;  

                  free(onegin->structs_arr);
                  onegin->structs_arr = nullptr;

                  fclose(onegin->mainfile);
                  onegin->mainfile = nullptr;

                  break;
            }

            default:
            {
                  printf("Undefined error!");
                  break;
            }
    }
}

//=============================================================================================================