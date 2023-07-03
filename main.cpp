#include "OneginProcessing.h"
#include "OneginSorting.h"

//=============================================================================================================

int main()
{
      Onegin onegin{};

      switch(onegin_ctor(&onegin, "input.txt"))
      {
            case(0):
            {
                  switch(sorting_choice(&onegin))
                  {
                        case(0):
				{
					onegin_dtor(&onegin);
					return 0;
				}

				case(ERROR_LEFT_COMP_NULLPTR):
				{
					printf("Error: %d\n", ERROR_LEFT_COMP_NULLPTR);
					return 0;
				}

				case(ERROR_RIGHT_COMP_NULLPTR):
				{
					printf("Error: %d\n", ERROR_RIGHT_COMP_NULLPTR);
					return 0;
				}

				case(ERROR_SORTING_CHOICE):
				{
					printf("Error: %d\n", ERROR_SORTING_CHOICE);
					return 0;
				}

				default:
				{
					printf("Undefined error!\n");
					return 0;
				}
			}
		}
		
            case(ERROR_MAINFILE_OPEN):
		{
			printf("Error: %d\n", ERROR_MAINFILE_OPEN);
			return 0;
		}

		case (ERROR_STAT_SIZE):
		{
			printf("Error: %d\n", ERROR_STAT_SIZE);
			return 0;
		}

		case(ERROR_BUFFER_NULLPTR):
		{
			printf("Error: %d\n", ERROR_BUFFER_NULLPTR);
			return 0;
		}

		case(ERROR_FREAD_COUNT):
		{
			printf("Error: %d\n", ERROR_FREAD_COUNT);
			return 0;
		}

		case(ERROR_STRUCTS_ARRAY_NULLPTR):
		{
			printf("Error: %d\n", ERROR_STRUCTS_ARRAY_NULLPTR);
			return 0;
		}

		default:
		{
			printf("Undefined error!\n");
			return 0;
		}
	}
}
