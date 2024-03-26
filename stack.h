#ifndef STACK_H

#define STACK_H

#include "stdlib.h"
#include "stdbool.h"
#include "assert.h"

typedef int type_t;

typedef struct elem{
    type_t val;
    struct elem* next;
} elem;

typedef struct stack{
    elem* first;
} stack;

/**
 * @brief Initialise une pile
 * @return retourne une pile vide 
*/
stack* init_stack();

/**
 * @brief Verifie si la pile est vide
 * @param s La pile
 * @return Vrai si la pile est vide, faux sinon
*/
bool is_empty(stack *s);

/**
 * @brief Ajoute un nouveau maillon a la pile 
 * @param s La pile
 * @param val La valeur du nouveau maillon
*/
void push(stack* s, type_t val);

/**
 * @brief Enleve le maillon en haut de la pile en renvoyant sa valeur
 * @param s La pile
 * @return La valeur contenant dans le maillon enleve
*/
type_t pop(stack* s);

/**
 * @brief Donne la valeur en haut de la pile sans enlever le maillon
 * @param s La pile
 * @return La valeur du maillon en haut de la pile
*/
type_t peek(stack* s);

/**
 * @brief Supprime la pile et libere la memoire
 * @param s La pile
*/
void free_stack(stack* s);

#endif
