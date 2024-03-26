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

