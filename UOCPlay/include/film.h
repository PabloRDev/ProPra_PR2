#ifndef __FILM_H__
#define __FILM_H__
#include <stdbool.h>
#include "csv.h"
#include "date.h"
#include "error.h"

#define RATING_MIN 0.0
#define RATING_MAX 5.0

#define NUM_FIELDS_FILM 6

typedef enum {
	GENRE_FIRST = 0,
	
	GENRE_ACTION = GENRE_FIRST,	// 0
	GENRE_COMEDY,				// 1
	GENRE_DRAMA,				// 2
	GENRE_HORROR,				// 3
	GENRE_SCIENCE_FICTION,		// 4
	
	GENRE_END					// Max number of genres, used to check maximum values or iterate through them
} tFilmGenre;

typedef struct _tFilm {
	char* name;
	tTime duration;
	tFilmGenre genre;
	tDate release;
	float rating;
	bool isFree;
} tFilm;

typedef struct _tFilmListNode {
	tFilm elem;
	struct _tFilmListNode *next;
} tFilmListNode;

typedef struct _tFilmList {
	tFilmListNode *first;
	tFilmListNode *last;
	int count;
} tFilmList;

typedef struct _tFreeFilmListNode {
	tFilm *elem;
	struct _tFreeFilmListNode *next;
} tFreeFilmListNode;

typedef struct _tFreeFilmList {
	tFreeFilmListNode *first;
	tFreeFilmListNode *last;
	int count;
} tFreeFilmList;

typedef struct _tFilmCatalog {
	tFilmList filmList;
	tFreeFilmList freeFilmList;
} tFilmCatalog;

//////////////////////////////////
// Available methods
//////////////////////////////////

// Parse input from CSVEntry
void film_parse(tFilm* data, tCSVEntry entry);

// Initialize a film
void film_init(tFilm* data, const char* name, tTime duration, tFilmGenre genre, tDate release, float rating, bool isFree);

// Copy a film from src to dst
void film_cpy(tFilm* dst, tFilm src);

// Get film data using a string
void film_get(tFilm data, char* buffer);

// Remove the data from a film
void film_free(tFilm* data);

// Returns true if two films are considered equal (same name)
bool film_equals(tFilm a, tFilm b);

// Initialize the films list
tApiError filmList_init(tFilmList* list);

// Add a new film to the list
tApiError filmList_add(tFilmList* list, tFilm film);

// Remove a film from the list
tApiError filmList_del(tFilmList* list, const char* name);

// Return a pointer to the film
tFilm* filmList_find(tFilmList list, const char* name);

// Remove the films from the list
tApiError filmList_free(tFilmList* list);

// Initialize the free films list
tApiError freeFilmList_init(tFreeFilmList* list);

// Add a new free film to the list
tApiError freeFilmList_add(tFreeFilmList* list, tFilm* film);

// Remove a free film from the list
tApiError freeFilmList_del(tFreeFilmList* list, const char* name);

// Return a pointer to the free film
tFilm* freeFilmList_find(tFreeFilmList list, const char* name);

// Remove the free films from the list
tApiError freeFilmsList_free(tFreeFilmList* list);

// Initialize the films catalog
tApiError film_catalog_init(tFilmCatalog* catalog);

// Add a new film to the catalog
tApiError film_catalog_add(tFilmCatalog* catalog, tFilm film);

// Remove a film from the catalog
tApiError film_catalog_del(tFilmCatalog* catalog, const char* name);

// Return the number of total films
int film_catalog_len(tFilmCatalog catalog);

// Return the number of free films
int film_catalog_freeLen(tFilmCatalog catalog);

// Remove the films from the catalog
tApiError film_catalog_free(tFilmCatalog* catalog);

////////////////////////////////////////////

#endif
