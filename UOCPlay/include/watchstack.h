#ifndef __WATCHSTACK_H__
#define __WATCHSTACK_H__

#include "film.h"
#include "error.h"
#include <stdbool.h>

// Node structure for the stack
typedef struct _tFilmstackNode {
    tFilm elem;
    struct _tFilmstackNode *next;
} tFilmstackNode;

// Stack structure
typedef struct _tFilmstack {
    tFilmstackNode *top;
    int count;
} tFilmstack;

/////////////////////////////////
// Function declarations
/////////////////////////////////

// Initializes the stack
tApiError filmstack_init(tFilmstack* stack);

// Returns true if the stack is empty
bool filmstack_isEmpty(tFilmstack stack);

// Adds a new film to the top of the stack
tApiError filmstack_push(tFilmstack* stack, tFilm film);

// Returns the top film without removing it
tFilm* filmstack_top(tFilmstack stack);

// Removes the top film from the stack
tApiError filmstack_pop(tFilmstack* stack);

// Frees all memory used by the stack
void filmstack_free(tFilmstack* stack);

#endif // __WATCHSTACK_H__