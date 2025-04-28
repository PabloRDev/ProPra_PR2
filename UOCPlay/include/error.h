#ifndef __UOCHEALTHCENTER_ERROR__H
#define __UOCHEALTHCENTER_ERROR__H

// Define error codes
enum _tApiError
{
    E_SUCCESS = 0, // No error
    E_NOT_IMPLEMENTED = -1, // Called method is not implemented
    E_FILE_NOT_FOUND = -2, // File not found
    E_INVALID_ENTRY_TYPE = -3, // Invalid entry type
    E_INVALID_ENTRY_FORMAT = -4, // Invalid entry format
    E_MEMORY_ERROR = -5, // Memory error 
	E_FILM_DUPLICATED = -6, // Film duplicated
	E_FILM_NOT_FOUND = -7, // Film not found
	E_PERSON_DUPLICATED = -8, // Person duplicated
	E_PERSON_NOT_FOUND = -9, // Person not found
	E_SUBSCRIPTION_DUPLICATED = -10, // Subscription duplicated
	E_SUBSCRIPTION_NOT_FOUND = -11, // Subscription not found
    E_STRUCTURE_EMPTY = -12, // try to get element from an empty estructure
    E_FILM_ALREADY_EXISTS = -13, // avoid duplicated films
    E_EPISODE_DUPLICATED = -14, // Episode duplicated
};


// Define an error type
typedef enum _tApiError tApiError;

#endif // __UOCHEALTHCENTER_ERRORS__H