#ifndef __PERSON_H__
#define __PERSON_H__
#include "csv.h"
#include "date.h"
#include "error.h"

#define NUM_FIELDS_PERSON 8

typedef struct _tPerson {
    char* document;
    char* name;
    char* surname;
    char* phone;
    char* email;
    char* address;
    char* cp;
    tDate birthday;
} tPerson;

typedef struct _tPeople {
    tPerson* elems;
    int count;
} tPeople;

//////////////////////////////////
// Available methods
//////////////////////////////////

// Parse input from CSVEntry
void person_parse(tPerson* data, tCSVEntry entry);

// Copy the data from the source to destination
void person_cpy(tPerson* destination, tPerson source);

// Remove the data from a person
void person_free(tPerson* data);

// Initialize the people data
tApiError people_init(tPeople* data);

// Return the number of people
int people_count(tPeople data);

// Add a new person
tApiError people_add(tPeople* data, tPerson person);

// Remove a person
tApiError people_del(tPeople* data, const char *document);

// Return the position of a person with provided document. -1 if it does not exist
int people_find(tPeople data, const char* document);

// Print the person data
void people_print(tPeople data);

// Remove the data from all persons
tApiError people_free(tPeople* data);

////////////////////////////////////////////

#endif
