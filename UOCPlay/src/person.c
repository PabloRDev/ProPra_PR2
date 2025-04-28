#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "person.h"

// Parse input from CSVEntry
void person_parse(tPerson* data, tCSVEntry entry) {
    // Check input data
    assert(data != NULL);
    
    // Check entry fields
    assert(csv_numFields(entry) == NUM_FIELDS_PERSON);
      
    // Copy identity document data
    data->document = (char*) malloc((strlen(entry.fields[0]) + 1) * sizeof(char));
    assert(data->document != NULL);
    memset(data->document, 0, (strlen(entry.fields[0]) + 1) * sizeof(char));
    csv_getAsString(entry, 0, data->document, strlen(entry.fields[0]) + 1);
    
    // Copy name data
    data->name = (char*) malloc((strlen(entry.fields[1]) + 1) * sizeof(char));
    assert(data->name != NULL);
    memset(data->name, 0, (strlen(entry.fields[1]) + 1) * sizeof(char));
    csv_getAsString(entry, 1, data->name, strlen(entry.fields[1]) + 1);
    
    // Copy surname data
    data->surname = (char*) malloc((strlen(entry.fields[2]) + 1) * sizeof(char));
    assert(data->surname != NULL);
    memset(data->surname, 0, (strlen(entry.fields[2]) + 1) * sizeof(char));
    csv_getAsString(entry, 2, data->surname, strlen(entry.fields[2]) + 1);
    
    // Copy phone data
    data->phone = (char*) malloc((strlen(entry.fields[3]) + 1) * sizeof(char));
    assert(data->phone != NULL);
    memset(data->phone, 0, (strlen(entry.fields[3]) + 1) * sizeof(char));
    csv_getAsString(entry, 3, data->phone, strlen(entry.fields[3]) + 1);

    // Copy email data
    data->email = (char*) malloc((strlen(entry.fields[4]) + 1) * sizeof(char));
    assert(data->email != NULL);
    memset(data->email, 0, (strlen(entry.fields[4]) + 1) * sizeof(char));
    csv_getAsString(entry, 4, data->email, strlen(entry.fields[4]) + 1);
    
    // Copy address data
    data->address = (char*) malloc((strlen(entry.fields[5]) + 1) * sizeof(char));
    assert(data->address != NULL);
    memset(data->address, 0, (strlen(entry.fields[5]) + 1) * sizeof(char));
    csv_getAsString(entry, 5, data->address, strlen(entry.fields[5]) + 1);
    
    // Copy cp data
    data->cp = (char*) malloc((strlen(entry.fields[6]) + 1) * sizeof(char));
    assert(data->cp != NULL);
    memset(data->cp, 0, (strlen(entry.fields[6]) + 1) * sizeof(char));
    csv_getAsString(entry, 6, data->cp, strlen(entry.fields[6]) + 1);
    
    // Check birthday lenght
    assert(strlen(entry.fields[7]) == 10);
    // Parse the birthday date
    sscanf(entry.fields[7], "%d/%d/%d", &(data->birthday.day), &(data->birthday.month), &(data->birthday.year));
}

// Copy the data from the source to destination
void person_cpy(tPerson* destination, tPerson source) {
    // Copy identity document data
    destination->document = (char*) malloc((strlen(source.document) + 1) * sizeof(char));
    assert(destination->document != NULL);
    strcpy(destination->document, source.document);
    
    // Copy name data
    destination->name = (char*) malloc((strlen(source.name) + 1) * sizeof(char));
    assert(destination->name != NULL);
    strcpy(destination->name, source.name);
    
    // Copy surname data
    destination->surname = (char*) malloc((strlen(source.surname) + 1) * sizeof(char));
    assert(destination->surname != NULL);
    strcpy(destination->surname, source.surname);
    
    // Copy phone data
    destination->phone = (char*) malloc((strlen(source.phone) + 1) * sizeof(char));
    assert(destination->phone != NULL);
    strcpy(destination->phone, source.phone);

    // Copy email data
    destination->email = (char*) malloc((strlen(source.email) + 1) * sizeof(char));
    assert(destination->email != NULL);
    strcpy(destination->email, source.email);
    
    // Copy address data
    destination->address = (char*) malloc((strlen(source.address) + 1) * sizeof(char));
    assert(destination->address != NULL);
    strcpy(destination->address, source.address);
    
    // Copy cp data
    destination->cp = (char*) malloc((strlen(source.cp) + 1) * sizeof(char));
    assert(destination->cp != NULL);
    strcpy(destination->cp, source.cp);
    
    // Copy the birthday date
    destination->birthday = source.birthday;
}

// Remove the data from a person
void person_free(tPerson* data) {
    // Check input data
    assert(data != NULL);
    
    // Release document data
    if(data->document != NULL) free(data->document);
    data->document = NULL;
    
    // Release name data
    if(data->name != NULL) free(data->name);
    data->name = NULL;
    
    // Release surname data
    if(data->surname != NULL) free(data->surname);
    data->surname = NULL;
    
    // Release phone data
    if(data->phone != NULL) free(data->phone);
    data->phone = NULL;
    
    // Release email data
    if(data->email != NULL) free(data->email);
    data->email = NULL;
    
    // Release address data
    if(data->address != NULL) free(data->address);
    data->address = NULL;
    
    // Release cp data
    if(data->cp != NULL) free(data->cp);
    data->cp = NULL;
}

// Initialize the people data
tApiError people_init(tPeople* data) {
    // Check input/output data
    assert(data != NULL);
    
    data->elems = NULL;
    data->count = 0;
	
	return E_SUCCESS;
}

// Return the number of people
int people_count(tPeople data) {
	return data.count;
}

// Add a new person
tApiError people_add(tPeople* data, tPerson person) {
    // Check input data
    assert(data != NULL);
    
	// If person already exist, return an error
	if (people_find(data[0], person.document) >= 0)
		return E_PERSON_DUPLICATED;
	
    // Allocate memory for new element
	if (data->count == 0) {
		// Request new memory space
		data->elems = (tPerson*) malloc(sizeof(tPerson));            
	} else {
		// Modify currently allocated memory
		data->elems = (tPerson*) realloc(data->elems, (data->count + 1) * sizeof(tPerson));            
	}
	assert(data->elems != NULL);
			
	// Copy the data to the new position
	person_cpy(&(data->elems[data->count]), person);
	
	// Increase the number of elements
	data->count ++;
	
	return E_SUCCESS;
}

// Remove a person
tApiError people_del(tPeople* data, const char *document) {
    int i;
    int pos;
    
    // Check input data
    assert(data != NULL);
    
    // Find if it exists
    pos = people_find(data[0], document);
    
	// If person does not exist, return an error
	if (pos < 0)
		return E_PERSON_NOT_FOUND;
	
	// Remove current position memory
	person_free(&(data->elems[pos]));
	// Shift elements 
	for(i = pos; i < data->count-1; i++) {
		// Copy address of element on position i+1 to position i
		data->elems[i] = data->elems[i+1];
	}
	// Update the number of elements
	data->count--;
	// Resize the used memory
	if (data->count == 0) {
		// No element remaining
		free(data->elems);
		data->elems = NULL;
	} else {
		// Still some elements are remaining
		data->elems = (tPerson*)realloc(data->elems, data->count * sizeof(tPerson));
	}
	
	return E_SUCCESS;
}

// Return the position of a person with provided document. -1 if it does not exist
int people_find(tPeople data, const char* document) {
    int i;
    
    for(i = 0; i < data.count; i++) {
        if(strcmp(data.elems[i].document, document) == 0 ) {
            return i;
        }
    }
    
    return -1;
}

// Print the person data
void people_print(tPeople data) {
    int i;
    
    for(i = 0; i < data.count; i++) {
        // Print position and document
        printf("%d;%s;", i, data.elems[i].document);
        // Print name and surname
        printf("%s;%s;", data.elems[i].name, data.elems[i].surname);        
        // Print phone
        printf("%s;", data.elems[i].phone);
        // Print email
        printf("%s;", data.elems[i].email);
        // Print address and CP
        printf("%s;%s;", data.elems[i].address, data.elems[i].cp);
        // Print birthday date
        printf("%02d/%02d/%04d\n", data.elems[i].birthday.day, data.elems[i].birthday.month, data.elems[i].birthday.year);
    }
}

// Remove the data from all persons
tApiError people_free(tPeople* data) {
    int i;
    
    // Check input data
    assert(data != NULL);
    
    // Remove contents
    for(i = 0; i < data->count; i++) {
        person_free(&(data->elems[i]));
    }    
    
    // Release memory
    if (data->count > 0) {
        free(data->elems);
        data->elems = NULL;
        data->count = 0;
    }
	
	return E_SUCCESS;
}