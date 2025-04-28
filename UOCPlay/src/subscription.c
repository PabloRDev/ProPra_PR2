#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "subscription.h"

// Parse input from CSVEntry
void subscription_parse(tSubscription* data, tCSVEntry entry) {
    // Check input data
    assert(data != NULL);

    // Check entry fields
    assert(csv_numFields(entry) == NUM_FIELDS_SUBSCRIPTION);

    int pos = 0; // Allow to easy incremental position of the income data

    // Copy subscription's id data
    data->id = csv_getAsInteger(entry, pos);

    // Copy identity document data
    assert(strlen(entry.fields[++pos]) == MAX_DOCUMENT);
    csv_getAsString(entry, pos, data->document, MAX_DOCUMENT + 1);

    // Parse start date
    assert(strlen(entry.fields[++pos]) == DATE_LENGTH);
    date_parse(&(data->start_date), entry.fields[pos]);

    // Parse end date
    assert(strlen(entry.fields[++pos]) == DATE_LENGTH);
    date_parse(&(data->end_date), entry.fields[pos]);

    // Copy plan data
    csv_getAsString(entry, ++pos, data->plan, MAX_PLAN + 1);

    // Copy price data
    data->price = csv_getAsReal(entry, ++pos);

    // Copy number of devices data
    data->numDevices = csv_getAsInteger(entry, ++pos);

    // Check preconditions that needs the readed values
    assert(data->price >= 0);
    assert(data->numDevices >= 1);
}

// Copy the data from the source to destination (individual data)
void subscription_cpy(tSubscription* destination, tSubscription source) {
    // Copy subscription's id data
    destination->id = source.id;

    // Copy identity document data
    strncpy(destination->document, source.document, MAX_DOCUMENT + 1);

    // Copy start date
    date_cpy(&(destination->start_date), source.start_date);

    // Copy end date
    date_cpy(&(destination->end_date), source.end_date);

    // Copy plan data
    strncpy(destination->plan, source.plan, MAX_PLAN + 1);

    // Copy price data
    destination->price = source.price;

    // Copy number of devices data
    destination->numDevices = source.numDevices;
}

// Get subscription data using a string
void subscription_get(tSubscription data, char* buffer) {
    // Print all data at same time
    sprintf(buffer,"%d;%s;%02d/%02d/%04d;%02d/%02d/%04d;%s;%g;%d",
        data.id,
        data.document,
        data.start_date.day, data.start_date.month, data.start_date.year,
        data.end_date.day, data.end_date.month, data.end_date.year,
        data.plan,
        data.price,
        data.numDevices);
}

// Initialize subscriptions data
tApiError subscriptions_init(tSubscriptions* data) {
    // Check input data
    assert(data != NULL);
    data->elems = NULL;
    data->count = 0; 
	
	return E_SUCCESS;
}

// Return the number of subscriptions
int subscriptions_len(tSubscriptions data) {
	return data.count;
}

// Add a new subscription
tApiError subscriptions_add(tSubscriptions* data, tPeople people, tSubscription subscription) {

    // Check input data
    assert(data != NULL);

	// If subscription already exists, return an error
	if (subscriptions_find(*data, subscription.id) >= 0)
		return E_SUBSCRIPTION_DUPLICATED;

	// If the person does not exist, return an error
	if (people_find(people, subscription.document) < 0)
		return E_PERSON_NOT_FOUND;

    // Copy the data to the new position
	if (data->elems == NULL) {
		data->elems = (tSubscription*) malloc(sizeof(tSubscription));
	} else {
		data->elems = (tSubscription*) realloc(data->elems, (data->count + 1) * sizeof(tSubscription));
	}
	assert(data->elems != NULL);
	subscription_cpy(&(data->elems[data->count]), subscription);
    

    /////////////////////////////////
    // PR2_2a
    /////////////////////////////////
    
    
    
    /////////////////////////////////
	// Increase the number of elements
	data->count++;
	
	return E_SUCCESS;
}

// Remove a subscription
tApiError subscriptions_del(tSubscriptions* data, int id) {
    int idx;
    int i;
    
    // Check if an entry with this data already exists
    idx = subscriptions_find(*data, id);
	
	// If the subscription does not exist, return an error
	if (idx < 0)
		return E_SUBSCRIPTION_NOT_FOUND;
    
    // Shift elements to remove selected
	for(i = idx; i < data->count-1; i++) {
			// Copy element on position i+1 to position i
			subscription_cpy(&(data->elems[i]), data->elems[i+1]);
	}
	// Update the number of elements
	data->count--;  

	if (data->count > 0) {
		data->elems = (tSubscription*) realloc(data->elems, data->count * sizeof(tSubscription));
		assert(data->elems != NULL);
	} else {
		subscriptions_free(data);
	}
	
	return E_SUCCESS;
}

// Get subscription data of position index using a string
void subscriptions_get(tSubscriptions data, int index, char* buffer)
{
    assert(index >= 0 && index < data.count);
    subscription_get(data.elems[index], buffer);
}

// Returns the position of a subscription looking for id's subscription. -1 if it does not exist
int subscriptions_find(tSubscriptions data, int id) {
    int i = 0;
    while (i < data.count) {
        if (data.elems[i].id == id) {
            return i;
        }
        i++;
    }

    return -1;
}

// Print subscriptions data
void subscriptions_print(tSubscriptions data) {
    char buffer[1024];
    int i;
    for (i = 0; i < data.count; i++) {
        subscriptions_get(data, i, buffer);
        printf("%s\n", buffer);
    }
}

// Remove all elements 
tApiError subscriptions_free(tSubscriptions* data) {    
    if (data->elems != NULL) {
    /////////////////////////////////
    // PR2_2b
    /////////////////////////////////
        
        
    /////////////////////////////////
        free(data->elems);
    }
    subscriptions_init(data);
	
	return E_SUCCESS;
  
}