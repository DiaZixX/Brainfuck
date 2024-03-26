#include "brainfuck_helper.h"

bool valid_character(char c){
    switch (c) {
        case '>' :
        case '<' :
        case '+' :
        case '-' :
        case '.' :
        case ',' :
        case '[' :
        case ']' :
            return true;
        default :
            return false;
    }
}

char* get_input_prog(char* input_filename){
    FILE* file = fopen(input_filename, "r");
    if (file != NULL){
        int length = INITIAL_SIZE;
        char* input = (char *) malloc(length*sizeof(char));
        int read_c = fgetc(file);
        int i = 0;
        while (read_c != EOF){
            if (valid_character(read_c))       
                input[i++] = read_c;
            if (i >= length){
                length *= 2;
                input = (char *) realloc(input, length*sizeof(char));
            }
            read_c = fgetc(file);
        }
        input[i] = '\0';
        fclose(file);
        return input;
    }
    else {
        return NULL;
    }
}

void free_input_prog(char* input_prog){
    free(input_prog);
}

void* build_loops(char* input_prog){
    return NULL;
}

void free_loops(void* loops){
}

void execute_instruction(char** ipp, uint8_t** dpp, void* loops){
    switch (**ipp) {
        case '>':
            ++*dpp;
            break;
        case '<':
            --*dpp;
            break;
        case '+':
            ++(**dpp);
            break;
        case '-':
            --(**dpp);
            break;
        case '.':
            putchar(**dpp);
            break;
        case ',':
            **dpp = getchar();
            break;
        case '[':
            if (**dpp == 0) {
                int loop = 1;
                while (loop > 0) {
                    ++*ipp;
                    if (**ipp == '[') {
                        ++loop;
                    } else if (**ipp == ']') {
                        --loop;
                    }
                }
            }
            break;
        case ']':
            if (**dpp != 0) {
                int loop = 1;
                while (loop > 0) {
                    --*ipp;
                    if (**ipp == '[') {
                        --loop;
                    } else if (**ipp == ']') {
                        ++loop;
                    }
                }
            }
            break;
    }
    ++*ipp;
}

void compile_to_c(char* input_prog){
    FILE* file = fopen("Compiled/compiled_to_c.c", "w");
    fprintf(file, "#include <assert.h>\n#include <stdlib.h>\n#include <stdint.h>\n#include <stdio.h>\n#include <string.h>\n\n");
    fprintf(file, "#define DATA_ARRAY_SIZE 32000\n\n");
    fprintf(file, "int main(){\n");
    fprintf(file, "    uint8_t* data_array = calloc(DATA_ARRAY_SIZE, sizeof(uint8_t));\n    uint8_t* dp = data_array;\n");
    int i = 0;
    int loop = 1;
    int tab[DATA_ARRAY_SIZE] = {0};
    int j = 0;
    while (input_prog[i] != '\0'){
        switch (input_prog[i]){
            case '>':
                fprintf(file, "    ++dp;\n");
                break;
            case '<':
                fprintf(file, "    --dp;\n");
                break;
            case '+':
                fprintf(file, "    ++*dp;\n");
                break;
            case '-':
                fprintf(file, "    --*dp;\n");
                break;
            case '.':
                fprintf(file, "    putchar(*dp);\n");
                break;
            case ',':
                fprintf(file, "    *dp = getchar();\n");
                break;
            case '[':
                tab[j++] = loop; 
                fprintf(file, "loop%d:\n", loop);
                fprintf(file, "    if (*dp == 0)\n");
                fprintf(file, "        goto after_loop%d;\n", loop++);
                break;
            case ']':
                j--;
                fprintf(file, "    if(*dp != 0)\n");
                fprintf(file, "        goto loop%d;\n", tab[j]);
                fprintf(file, "after_loop%d:\n", tab[j]);
                break;
            }
        i++;
    }
    fprintf(file, "    return EXIT_SUCCESS;\n");
    fprintf(file, "}\n\n");
    fclose(file);
}
