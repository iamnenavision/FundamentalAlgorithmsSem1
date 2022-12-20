#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_LEN 20


int is_space(char c)
{
    return c == '\n' || c == ' ' || c == '\t';
}


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    if (argc == 1)
    {
        printf("There is no name of file!\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r+");

    if (file == NULL)
    {
        printf("File doesn't exists!\n");
        return 1;
    }

    char c, _c;
    
    int number_column = -1;
    char **columns = (char **) malloc(sizeof(char *) * 3);
    if (columns == NULL)
    {
        printf("Memory cannot be allocated!\n");
        return 2;
    }


    int it = 0;
    int cur_len = START_LEN;
    
    while ((c = fgetc(file)) != EOF)
    {
        if (number_column == -1)
        {
            if (columns[0])
            {
                fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 4), SEEK_CUR);
                fprintf(file, "%s %s %s\n", columns[2], columns[0], columns[1]);
                fseek(file, 1, SEEK_CUR);
            }

            else
            {
                int i;
                for (i = 0; i < 3; ++i)
                {
                    columns[i] = (char *) malloc(sizeof(char) * START_LEN);
                    if (columns[i] == NULL)
                    {
                        printf("Memory cannot be allocated!\n");
                        return 2;
                    }



                    columns[i][START_LEN - 1] = '\0';
                }
            }
            number_column = 0;
        }


        if (!is_space(c))
        {
            if (strlen(columns[number_column]) - 1 == cur_len)
            {
                cur_len *= 2;

                char* ptr = realloc(columns[number_column], sizeof(char) * cur_len);
                if (NULL == ptr)
                {
                    printf("Memory cannot be allocated!\n");
                    for (int i = 0; i < 3; ++i)
                    {
                        free(columns[i]);
                    }
                    free(columns);

                    return 2;
                }
                columns[number_column] = ptr;



                if (columns[number_column] == NULL)
                {
                    printf("Not enough memory!\n");
                    fclose(file);
                    int i;
                    for (i = 0; i < 3; ++i)
                    {
                        free(columns[i]);
                    }
                    free(columns);
                    return 1;
                }
            }

            *(*(columns + number_column )+ it++) = c;
        }
        else
        {
            columns[number_column][it++] = '\0';
            cur_len = START_LEN;
            it = 0;
            number_column = (number_column + 1) % 3;
            if (number_column == 0)
            {
                number_column = -1;
            }
        }
        _c = c;
    }
    if (_c != '\n')
    {
        columns[number_column][it++] = '\0';
        fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 3), SEEK_CUR);
        fprintf(file, "\n%s %s %s", columns[2], columns[0], columns[1]);
    }
    else
    {
        fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 4), SEEK_CUR);
        fprintf(file, "\n%s %s %s\n", columns[2], columns[0], columns[1]);
    }

    int i;
    for (i = 0; i < 3; ++i)
    {
        free(columns[i]);
    }
    free(columns);

    printf("Success\n");

    fclose(file);

    return 0;
}
