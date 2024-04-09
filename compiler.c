#include <string.h>
#include "brainfuck_helper.h"

#define CMP_PATH "Compiled/"

/**
 * @brief Renvoie le meme nom de fichier brainfuck en .c
 * 
 * @param filename nom du fichier contenant le programme brainfuck
 * 
 * @return le nom en .c
*/
char* file_name_c(char* filename){
    int length = strlen(filename);
    char* new_name = (char *) malloc((length)*sizeof(char));
    for (int i = 0; i < length - 1; i++){
        new_name[i] = filename[i];
    }
    new_name[length-2] = 'c';
    new_name[length-1] = '\0';
    return new_name;
}

/**
 * @brief Renvoie le meme nom de fichier brainfuck en .py
 * 
 * @param filename nom du fichier contenant le programme brainfuck
 * 
 * @return le nom en .py
*/
char* file_name_py(char* filename){
    int length = strlen(filename);
    char* new_name = (char *) malloc((length+1)*sizeof(char));
    for (int i = 0; i < length ; i++){
        new_name[i] = filename[i];
    }
    new_name[length-2] = 'p';
    new_name[length-1] = 'y';
    new_name[length] = '\0';
    return new_name;
}

/**
 * @brief Compile en C le programme brainfuck
 * 
 * @param filename nom du programme brainfuck a compiler en C
*/
void compile_to_c(char* filename){
    char* input_prog = get_input_prog(filename);
    char* ip = input_prog;

    if (ip == NULL){
        printf("Le fichier Brainfuck passé en paramètre n'existe pas dans le répertoire courant\n");
        exit(0);
    }

    int length_path = strlen(CMP_PATH);
    char* path = (char *) malloc((length_path+1)*sizeof(char));
    strncpy(path, CMP_PATH, length_path);
    path[length_path] = '\0';
    char* temp = file_name_c(filename);
    strcat(path, temp);

    FILE* file = fopen(path, "w");
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
    free(path);
    free(temp);
    free_input_prog(input_prog);
    fclose(file);
}

/**
 * @brief Compile en Python le programme brainfuck
 * 
 * @param filename nom du programme brainfuck a compiler en Python
*/
void compile_to_py(char* filename){
    char* input_prog = get_input_prog(filename);
    char* ip = input_prog;

    if (ip == NULL){
        printf("Le fichier Brainfuck passé en paramètre n'existe pas dans le répertoire courant\n");
        exit(0);
    }

    int length_path = strlen(CMP_PATH);
    char* path = (char *) malloc((length_path+1)*sizeof(char));
    strncpy(path, CMP_PATH, length_path);
    path[length_path] = '\0';
    char* temp = file_name_py(filename);
    strcat(path, temp);

    FILE* file = fopen(path, "w");
    fprintf(file, "#!/usr/bin/env python3\n\n");
    fprintf(file, "DATA_ARRAY_SIZE = 32000\n\n");
    fprintf(file, "def main():\n");
    fprintf(file, "    data_array = [0 for _ in range(DATA_ARRAY_SIZE)]\n    i = 0\n");
    int i = 0;
    int indent = 1;
    while (input_prog[i] != '\0'){
        for (int a = 0; a < indent; a++)
            fprintf(file, "    ");
        switch (input_prog[i]){
            case '>':
                fprintf(file, "i += 1\n");
                break;
            case '<':
                fprintf(file, "i -= 1\n");
                break;
            case '+':
                fprintf(file, "data_array[i] = (data_array[i] + 1) %% 256\n");
                break;
            case '-':
                fprintf(file, "data_array[i] = (data_array[i] - 1) %% 256\n");
                break;
            case '.':
                fprintf(file, "print(chr(data_array[i]), end=\"\")\n");
                break;
            case ',':
                fprintf(file, "data_array[i] = int(ord(input('').split(\" \")[0])) %% 256\n");
                break;
            case '[': 
                fprintf(file, "while data_array[i] != 0 :\n");
                indent++;
                break;
            case ']':
                fprintf(file, "\n");
                indent--;
                break;
            }
        i++;
    }
    fprintf(file, "\nif __name__ == '__main__' :\n    main()\n\n");
    free(path);
    free(temp);
    free_input_prog(input_prog);
    fclose(file);
}

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Veuillez entrer le nom du fichier contenant le programme brainfuck\n");
        printf("La commande correcte est ./compiler <language> <nom du fichier>.bf\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "python") == 0){
        compile_to_py(argv[2]);
    }
    else if (strcmp(argv[1], "c") == 0){
        compile_to_c(argv[2]);
    }
    else {
        printf("Arguments invalides !\n");
        printf("La commande correcte est ./compiler <language> <nom du fichier>.bf\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
