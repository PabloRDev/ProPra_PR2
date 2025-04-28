#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "date.h"

// Copy a time from src to dst
void time_cpy(tTime *dst, tTime src)
{
	// Check output daa
	assert(dst != NULL);
	
	dst->hour = src.hour;
	dst->minutes = src.minutes;
}

// Parse a tTime from string information
void time_parse(tTime* time, const char* text){
    // Check output data
    assert(time != NULL);
    
    // Check input time
    assert(text != NULL);
    assert(strlen(text) == 5);  // Format expected: "HH:MM"

    // Parse the input time
    sscanf(text, "%d:%d", &(time->hour), &(time->minutes));
}

// Parse a tDate from string information
void date_parse(tDate* date, const char* text)
{
    // Check output data
    assert(date != NULL);
    
    // Check input date
    assert(text != NULL);
    assert(strlen(text) == DATE_LENGTH);
 
    // Parse the input date
    sscanf(text, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Copy a date from src to dst
void date_cpy(tDate *dst, tDate src) {
    // Check output data
    assert(dst != NULL);
    
    dst->day = src.day;
    dst->month = src.month;
    dst->year = src.year;
}

// Compare two dates
int date_cmp(tDate date1, tDate date2) {
    // Checkl year
    if (date1.year < date2.year) {
        return -1;
    }
    if (date1.year > date2.year) {
        return 1;
    }
    // Check month
    if (date1.month < date2.month) {
        return -1;
    }
    if (date1.month > date2.month) {
        return 1;
    }  
    // Check day
    if (date1.day < date2.day) {
        return -1;
    }
    if (date1.day > date2.day) {
        return 1;
    }
    
    return 0;
}

// Parse a tDateTime from string information
void dateTime_parse(tDateTime* dateTime, const char* date, const char* time) {
    // Check output data
    assert(dateTime != NULL);
    
    // Check input date
    assert(date != NULL);
    assert(strlen(date) == 10);
    
    // Check input time
    assert(time != NULL);
    assert(strlen(time) == 5);
    
    // Parse the input date
    sscanf(date, "%d/%d/%d", &(dateTime->date.day), &(dateTime->date.month), &(dateTime->date.year));
    
    // Parse the input time
    sscanf(time, "%d:%d", &(dateTime->time.hour), &(dateTime->time.minutes));
}

// Compare two tDateTime structures and return -1 if dateTime1<dateTime2, 0 if equals and 1 if dateTime1>dateTime2.
int dateTime_cmp(tDateTime dateTime1, tDateTime dateTime2) {    
    // Checkl year
    if (dateTime1.date.year < dateTime2.date.year) {
        return -1;
    }
    if (dateTime1.date.year > dateTime2.date.year) {
        return 1;
    }
    // Check month
    if (dateTime1.date.month < dateTime2.date.month) {
        return -1;
    }
    if (dateTime1.date.month > dateTime2.date.month) {
        return 1;
    }  
    // Check day
    if (dateTime1.date.day < dateTime2.date.day) {
        return -1;
    }
    if (dateTime1.date.day > dateTime2.date.day) {
        return 1;
    }
    // Check hour
    if (dateTime1.time.hour < dateTime2.time.hour) {
        return -1;
    }
    if (dateTime1.time.hour > dateTime2.time.hour) {
        return 1;
    }
    // Check minutes
    if (dateTime1.time.minutes < dateTime2.time.minutes) {
        return -1;
    }
    if (dateTime1.time.minutes > dateTime2.time.minutes) {
        return 1;
    }
    
    return 0;
}

// Compare two tDateTime structures and return true if they contain the same value or false otherwise.
bool dateTime_equals(tDateTime dateTime1, tDateTime dateTime2) {
    return dateTime_cmp(dateTime1, dateTime2) == 0;
}
