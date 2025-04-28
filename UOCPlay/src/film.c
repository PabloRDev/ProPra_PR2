#include "film.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Parse input from CSVEntry
void film_parse(tFilm* data, tCSVEntry entry) {
	// Check input data
	assert(data != NULL);
	assert(csv_numFields(entry) == NUM_FIELDS_FILM);

	int pos = 0;

	// Name
	const char* name = entry.fields[pos++];
	assert(name != NULL);

	// Duration
	assert(strlen(entry.fields[pos]) == TIME_LENGTH);
	tTime duration;
	int itemsRead = sscanf(entry.fields[pos++], "%d:%d", &duration.hour, &duration.minutes);
	assert(itemsRead == 2);

	// Genre
	int genreValue = csv_getAsInteger(entry, pos++);
	assert(genreValue >= GENRE_FIRST && genreValue < GENRE_END);
	tFilmGenre genre = (tFilmGenre)genreValue;

	// Release date
	assert(strlen(entry.fields[pos]) == DATE_LENGTH);
	tDate release;
	itemsRead = sscanf(entry.fields[pos++], "%d/%d/%d", &release.day, &release.month, &release.year);
	assert(itemsRead == 3);

	// Rating
	float rating = csv_getAsReal(entry, pos++);
	assert(rating >= RATING_MIN && rating <= RATING_MAX);

	// isFree
	int isFree = csv_getAsInteger(entry, pos++);
	assert(isFree == 0 || isFree == 1);

	// Call film_init with the parsed data
	film_init(data, name, duration, genre, release, rating, (bool)isFree);
}

// Initialize a film
void film_init(tFilm* data, const char* name, tTime duration, tFilmGenre genre, tDate release, float rating, bool isFree) {
	// Check preconditions
	assert(data != NULL);
	assert(name != NULL);
	
	// Name
	data->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
	assert(data->name != NULL);
	strcpy(data->name, name);
	
	// Duration
	time_cpy(&data->duration, duration);
	
	// Genre
	data->genre = genre;
	
	// Release
	date_cpy(&data->release, release);
	
	// Rating
	data->rating = rating;
	
	// isFree
	data->isFree = isFree;
}

// Copy a film from src to dst
void film_cpy(tFilm* dst, tFilm src) {
	// Check preconditions
	assert(dst != NULL);
	
	film_init(dst, src.name, src.duration, src.genre, src.release, src.rating, src.isFree);
}

// Get film data using a string
void film_get(tFilm data, char* buffer) {
	// Print all data at same time
    sprintf(buffer,"%s;%02d:%02d;%d;%02d/%02d/%04d;%.1f;%d",
        data.name,
		data.duration.hour, data.duration.minutes,
		data.genre,
		data.release.day, data.release.month, data.release.year,
		data.rating,
		data.isFree);
}

// Remove the data from a film
void film_free(tFilm* data) {
	// Check preconditions
	assert(data != NULL);
	
	if (data->name != NULL)
	{
		free(data->name);
		data->name = NULL;
	}
}

// Returns true if two films are considered equal (same name)
bool film_equals(tFilm a, tFilm b) {
    if (a.name == NULL || b.name == NULL) {
        return false;
    }
    return strcmp(a.name, b.name) == 0;
}

// Initialize the films list
tApiError filmList_init(tFilmList* list) {
	// Check preconditions
	assert(list != NULL);
	
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
	
	return E_SUCCESS;
}

// Add a new film to the list
tApiError filmList_add(tFilmList* list, tFilm film) {
	// Check preconditions
	assert(list != NULL);
	
	tFilmListNode *node;
	
	// Check if the film is already in the list
	if (filmList_find(*list, film.name) != NULL)
		return E_FILM_DUPLICATED;
	
	// Create the node
	node = (tFilmListNode*)malloc(sizeof(tFilmListNode));
	assert(node != NULL);
	
	// Assign the properties of the nodes
	film_cpy(&node->elem, film);
	node->next = NULL;
	
	// Link the new node to the end of the list
	if (list->first == NULL)
		list->first = node;
	else
		list->last->next = node;
	
	list->last = node;
	list->count++;
	
	return E_SUCCESS;
}

// Remove a film from the list
tApiError filmList_del(tFilmList* list, const char* name) {
	// Check preconditions
	assert(list != NULL);
	assert(name != NULL);
	
	tFilmListNode *node, *prev;
	
	// Iterate until the node and remove it
	node = list->first;
	prev = NULL;
	
	while (node != NULL)
	{
		if (strcmp(node->elem.name, name) == 0)
			break;
		
		prev = node;
		node = node->next;
	}
	
	// If node does not exist, return an error
	if (node == NULL)
		return E_FILM_NOT_FOUND;
	
	// Link the list without the node to remove
	if (prev == NULL)
		list->first = node->next;
	else
		prev->next = node->next;
	
	if (list->last == node)
		list->last = prev;
	
	list->count--;
	
	film_free(&(node->elem));
	free(node);
	
	return E_SUCCESS;
}

// Return a pointer to the film
tFilm* filmList_find(tFilmList list, const char* name) {
	// Check preconditions
	assert(name != NULL);
	
	tFilmListNode *node;
	node = list.first;
	
	while (node != NULL)
	{
		if (strcmp(node->elem.name, name) == 0)
			return &(node->elem);
		
		node = node->next;
	}
	
	return NULL;
}

// Remove the films from the list
tApiError filmList_free(tFilmList* list) {
	// Check preconditions
	assert(list != NULL);
	
	tFilmListNode *node, *auxNode;
	
	node = list->first;
	auxNode = NULL;
	
	while (node != NULL)
	{
		auxNode = node->next;
		
		film_free(&(node->elem));
		free(node);
		
		node = auxNode;
	}
	
	filmList_init(list);
	
	return E_SUCCESS;
}

// Initialize the free films list
tApiError freeFilmList_init(tFreeFilmList* list) {
	// Check preconditions
	assert(list != NULL);
	
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
	
	return E_SUCCESS;
}

// Add a new free film to the list
tApiError freeFilmList_add(tFreeFilmList* list, tFilm* film) {
	// Check preconditions
	assert(list != NULL);
	assert(film != NULL);

	if (freeFilmList_find(*list, film->name) != NULL)
		return E_FILM_DUPLICATED;

	tFreeFilmListNode* node = (tFreeFilmListNode*)malloc(sizeof(tFreeFilmListNode));
	assert(node != NULL);

	node->elem = film; // Store the reference
	node->next = NULL;

	if (list->first == NULL)
		list->first = node;
	else
		list->last->next = node;

	list->last = node;
	list->count++;

	return E_SUCCESS;
}

// Remove a free film from the list
tApiError freeFilmList_del(tFreeFilmList* list, const char* name) {
	// Check preconditions
	assert(list != NULL);
	assert(name != NULL);

	tFreeFilmListNode *node = list->first, *prev = NULL;

	while (node != NULL)
	{
		if (strcmp(node->elem->name, name) == 0)
			break;
		prev = node;
		node = node->next;
	}

	if (node == NULL)
		return E_FILM_NOT_FOUND;

	if (prev == NULL)
		list->first = node->next;
	else
		prev->next = node->next;

	if (list->last == node)
		list->last = prev;

	free(node);
	list->count--;

	return E_SUCCESS;
}

// Return a pointer to the free film
tFilm* freeFilmList_find(tFreeFilmList list, const char* name) {
	// Check preconditions
	assert(name != NULL);
	
	tFreeFilmListNode *node;
	node = list.first;
	
	while (node != NULL)
	{
		if (strcmp(node->elem->name, name) == 0)
			return node->elem;
			
		node = node->next;
	}
	
	return NULL;
}

// Remove the free films from the list
tApiError freeFilmsList_free(tFreeFilmList* list) {
	// Check preconditions
	assert(list != NULL);
	
	tFreeFilmListNode *node, *auxNode;
	
	node = list->first;
	auxNode = NULL;
	
	while (node != NULL)
	{
		auxNode = node->next;
		free(node);
		node = auxNode;
	}
	
	freeFilmList_init(list);
	
	return E_SUCCESS;
}

// Initialize the films catalog
tApiError film_catalog_init(tFilmCatalog* catalog) {
	/////////////////////////////////
	// Ex1 PR1 2a
	/////////////////////////////////
	// Check preconditions
	assert(catalog != NULL);
	
	filmList_init(&(catalog->filmList));
	freeFilmList_init(&(catalog->freeFilmList));
	
	return E_SUCCESS;
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a new film to the catalog
tApiError film_catalog_add(tFilmCatalog* catalog, tFilm film) {
	/////////////////////////////////
	// Ex1 PR1 2b
	/////////////////////////////////
	tApiError error;
	tFilm *auxFilm;
	
	// Check preconditions
	assert(catalog != NULL);
	
	// Try to add the film to the catalog
	error = filmList_add(&(catalog->filmList), film);
	
	// Get the film from the list if exist and if it is free
	if (film.isFree && error == E_SUCCESS && (auxFilm = filmList_find(catalog->filmList, film.name)) != NULL)
	{
		error = freeFilmList_add(&(catalog->freeFilmList), auxFilm);
		
		// Revert if freeFilmList_add failed
		if (error != E_SUCCESS)
		{
			filmList_del(&(catalog->filmList), film.name);
		}
	}
	
	return error;
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Remove a film from the catalog
tApiError film_catalog_del(tFilmCatalog* catalog, const char* name) {
	/////////////////////////////////
	// Ex1 PR1 2c
	/////////////////////////////////
	// Check preconditions
	assert(catalog != NULL);
	assert(name != NULL);
	
	// Try to remove the film from the free film list
	freeFilmList_del(&(catalog->freeFilmList), name);
	
	// Then, remove the film from the list and return the result
	return filmList_del(&(catalog->filmList), name);
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Return the number of total films
int film_catalog_len(tFilmCatalog catalog) {
	/////////////////////////////////
	// Ex1 PR1 2d
	/////////////////////////////////
	return catalog.filmList.count;
	/////////////////////////////////
    // return -1;
}

// Return the number of free films
int film_catalog_freeLen(tFilmCatalog catalog) {
	/////////////////////////////////
	// Ex1 PR1 2d
	/////////////////////////////////
	return catalog.freeFilmList.count;
	/////////////////////////////////
    // return -1;
}

// Remove the films from the catalog
tApiError film_catalog_free(tFilmCatalog* catalog) {
	/////////////////////////////////
	// Ex1 PR1 2e
	/////////////////////////////////
	// Check preconditions
	assert(catalog != NULL);
	
	freeFilmsList_free(&(catalog->freeFilmList));
	filmList_free(&(catalog->filmList));
	
	return E_SUCCESS;
	/////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}
