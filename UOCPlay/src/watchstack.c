#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "film.h"
#include "watchstack.h"

// Initializes the stack
tApiError filmstack_init(tFilmstack* stack) {
    /////////////////////////////////
    // PR2_2c
    /////////////////////////////////

   
    return E_NOT_IMPLEMENTED;
}

// Returns true if the stack is empty
bool filmstack_isEmpty(tFilmstack stack) {
    /////////////////////////////////
    // PR2_2d
    /////////////////////////////////

    return false;
}


// Adds a new film to the stack, unless it already exists
tApiError filmstack_push(tFilmstack* stack, tFilm film) {
    /////////////////////////////////
    // PR2_2e
    /////////////////////////////////


    return E_NOT_IMPLEMENTED;
}

// Returns the top film (without removing it)
tFilm* filmstack_top(tFilmstack stack) {
    /////////////////////////////////
    // PR2_2f
    /////////////////////////////////

   
    return NULL;
}

// Removes the top film from the stack
tApiError filmstack_pop(tFilmstack* stack) {
    /////////////////////////////////
    // PR2_2g
    /////////////////////////////////


    return E_NOT_IMPLEMENTED;
}

// Frees the whole stack
void filmstack_free(tFilmstack* stack) {
    /////////////////////////////////
    // PR2_2f
    /////////////////////////////////

    
}