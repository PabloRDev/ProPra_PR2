#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "film.h"
#include "watchstack.h"

// 2c - Initializes the stack
tApiError filmstack_init(tFilmstack *stack) {
    assert(stack != NULL);

    stack->top = NULL;
    stack->count = 0;

    return E_SUCCESS;
}

// 2d - Returns true if the stack is empty
bool filmstack_isEmpty(tFilmstack stack) {
    return stack.top == NULL;
}


// 2e - Adds a new film to the stack, unless it already exists
tApiError filmstack_push(tFilmstack *stack, tFilm film) {
    assert(stack != NULL);

    // Check film already exists
    tFilmstackNode *current = stack->top;
    while (current != NULL) {
        if (strcmp(current->elem.name, film.name) == 0) {
            return E_FILM_ALREADY_EXISTS;
        }
        current = current->next;
    }

    // Film NOT exists, create
    tFilmstackNode *newFilmstackNode = malloc(sizeof(tFilmstackNode));
    if (newFilmstackNode == NULL) {
        return E_MEMORY_ERROR;
    }
    film_cpy(&(newFilmstackNode->elem), film);

    // New node to top
    newFilmstackNode->next = stack->top;
    stack->top = newFilmstackNode;
    stack->count++;

    return E_SUCCESS;
}

// 2f - Returns the top film (without removing it)
tFilm *filmstack_top(tFilmstack stack) {
    return &stack.top->elem;
}

// 2g - Removes the top film from the stack
tApiError filmstack_pop(tFilmstack *stack) {
    assert(stack != NULL);
    // Empty top
    if (stack->top == NULL) {
        return E_STRUCTURE_EMPTY;
    }

    tFilmstackNode *nodeToPop = stack->top;
    stack->top = stack->top->next;
    if (nodeToPop != NULL) {
        free(nodeToPop);
    }
    stack->count--;

    return E_SUCCESS;
}

// 2h - Frees the whole stack
void filmstack_free(tFilmstack *stack) {
    if (stack != NULL) {
        // Free each node
        tFilmstackNode *current = stack->top;
        while (current != NULL) {
            tFilmstackNode *nextNode = current->next;
            free(current);

            current = nextNode;
        }

        stack->top = NULL;
        stack->count = 0;
    }
}
