#include "stack.h"
#include "brainfuck_helper.h"

bool syntax_analysis(char* filename){
    char* input_prog = get_input_prog(filename);
    int i = 0;
    stack* lifo = init_stack();

    while (input_prog[i] != '\0'){
        switch (input_prog[i]) {
            case '>' :
            case '<' :
            case '+' :
            case '-' :
            case '.' :
            case ',' :
                break;
            case '[' :
                push(lifo, i);
                break;
            case ']' :
                if (is_empty(lifo)){
                    printf("Unexpected loop closure ']' at position : %d\n", input_prog[i], i);
                    free_stack(lifo);  
                    return false;
                }
                else {
                    pop(lifo);
                    break;
                }
            default :
                printf("Unexpected caracter %c at position : %d\n", input_prog[i], i);
                free_stack(lifo);
                return false;
        }
        i++;
    }
    if (!is_empty(lifo)){
        printf("Unclosed loop '[' at position : %d\n", pop(lifo));
        free_stack(lifo);
        return false;
    }
    else {
        free_stack(lifo);
        return true;
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Veuillez entrer le nom du fichier contenant le programme brainfuck\n");
        printf("La commande correcte est ./syntax <nom du fichier>.bf\n");
        return EXIT_FAILURE;
    }

    bool ret = syntax_analysis(argv[1]);

    if (!ret){
        printf("The code is syntactically correct\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}