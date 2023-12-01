#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int first_puzzle();
int second_puzzle();
int get_num(char*);

int main() {

    first_puzzle();

    second_puzzle();

    return 0;
}

int first_puzzle() {
    FILE *input_txt = fopen("input.txt", "r");
    
    if (input_txt == NULL) {
        printf("couldn't open file\n");
        return -1;
    }

    int first_num, last_num;

    char * line = NULL;
    size_t len = 0;
    size_t read;

    int sum = 0;

    while ((read = getline(&line, &len, input_txt)) != -1) {
        first_num = -1;

        for (int i = 0; i < read; i++) {
            if (isdigit(line[i])) {
                if (first_num == -1) {
                    first_num = line[i] - '0';
                }
                last_num = line[i] - '0';
            }
        }

        sum += first_num * 10 + last_num;
    }

    printf("sum => %d\n", sum);

    fclose(input_txt);
    
    if (line) {
        free(line);
    }

    return sum;
}

int second_puzzle() {
    FILE *input_txt = fopen("input.txt", "r");
    
    if (input_txt == NULL) {
        printf("couldn't open file\n");
        return -1;
    }

    int first_num, last_num;

    char * line = NULL;
    size_t len = 0;
    size_t read;

    int sum = 0;

    while ((read = getline(&line, &len, input_txt)) != -1) {
        
        first_num = -1;

        int str_num;

        for (int i = 0; i < read; i++) {

            char c = line[i];

            if (isdigit(line[i])) {
                if (first_num == -1) {
                    first_num = line[i] - '0';
                }
                last_num = line[i] - '0';
                continue;
            }

            for (int j = 1; j < 6; j++) {

                if ((i + j) >= read) {
                    break;
                }
                
                size_t arr_len = j;

                char * arr = (char *) malloc (arr_len * sizeof(char) + 1);
                arr[arr_len] = '\0';
                
                memset(arr, 0, arr_len * sizeof(char));

                memcpy(arr, line + i, arr_len * sizeof(char));

                str_num = get_num(arr);

                if (str_num != -1) {
                    break;
                }

                free(arr);
            }

            if (str_num == -1) {
                continue;
            }

            if (first_num == -1) {
                first_num = str_num;
            }

            last_num = str_num;

        }
        
        sum += first_num * 10 + last_num;
    }

    printf("sum => %d\n", sum);

    fclose(input_txt);
    
    if (line) {
        free(line);
    }

    return sum;
}

int get_num(char * str_num_array) {
    const char *nums[9];
    nums[0] = "one";
    nums[1] = "two";
    nums[2] = "three";
    nums[3] = "four";
    nums[4] = "five";
    nums[5] = "six";
    nums[6] = "seven";
    nums[7] = "eight";
    nums[8] = "nine";

    for (int i = 0; i < 9; i++) {
        if (strcmp(str_num_array, nums[i]) == 0) {
            return i + 1;
        }
    }
    return -1;
}