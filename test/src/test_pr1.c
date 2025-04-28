#include "test_pr1.h"
#include "api.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Run all tests for PR1
bool run_pr1(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR1", "Tests for PR1 exercices");

    section = testSuite_getSection(test_suite, "PR1");
    assert(section != NULL);

    ok = run_pr1_ex1(section, input);
    ok = run_pr1_ex2(section, input) && ok;
    ok = run_pr1_ex3(section, input) && ok;
    ok = run_pr1_ex4(section, input) && ok;

    return ok;
}

// Run all tests for Exercice 1 of PR1
bool run_pr1_ex1(tTestSection *test_section, const char *input) {
	bool passed = true, failed = false;
	const char *version;

	/////////////////////////////
	/////  PR1 EX1 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX1_1", "Read version information.");
	// Get the version
	version = api_version();
	if (strcmp(version, "UOC PP 20242") != 0) {
		failed = true;
		passed = false;
	}
	end_test(test_section, "PR1_EX1_1", !failed);

	return passed;
}

// Run all tests for Exercice 2 of PR1
bool run_pr1_ex2(tTestSection *test_section, const char *input) {
	tApiError error;
	tTime duration;
	tDate release;
	tFilm film1, film2, film3, film4;
	tFilmCatalog catalog;
	
	bool passed = true;
	bool failed = false;
	bool fail_all = false;
	
	// film1
	duration.hour = 2;
	duration.minutes = 49;
	release.day = 7;
	release.month = 11;
	release.year = 2014;
	film_init(&film1, "Interstellar", duration, 4, release, 4.8f, false);

	// film2
	duration.hour = 2;
	duration.minutes = 0;
	release.day = 15;
	release.month = 5;
	release.year = 2015;
	film_init(&film2, "Mad Max: Fury Road", duration, 0, release, 4.5f, false);

	// film3
	duration.hour = 3;
	duration.minutes = 9;
	release.day = 10;
	release.month = 12;
	release.year = 1999;
	film_init(&film3, "The Green Mile", duration, 2, release, 4.8f, true);

	// film4
	duration.hour = 1;
	duration.minutes = 57;
	release.day = 15;
	release.month = 12;
	release.year = 2006;
	film_init(&film4, "The Pursuit of Happyness", duration, 2, release, 4.4f, true);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_1", "Initialize the catalog data structure");
	// Initialize the catalog
	error = film_catalog_init(&catalog);
	if (error != E_SUCCESS) {
		failed = true;
		passed = false;
		fail_all = true;
	} else {
		if (catalog.filmList.first != NULL || catalog.filmList.last != NULL || catalog.filmList.count != 0 
		 || catalog.freeFilmList.first != NULL || catalog.freeFilmList.last != NULL || catalog.freeFilmList.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR1_EX2_1", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_2", "Add a film to an empty catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Add a film to an empty catalog
		error = film_catalog_add(&catalog, film1);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (catalog.filmList.first == NULL || catalog.filmList.last == NULL || catalog.filmList.count != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first != NULL || catalog.freeFilmList.last != NULL || catalog.freeFilmList.count != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next != NULL || strcmp(catalog.filmList.first->elem.name, film1.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX2_2", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_3", "Add a free film to a non-empty catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Add a free film to a non-empty catalog
		error = film_catalog_add(&catalog, film3);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (catalog.filmList.first == NULL || catalog.filmList.last == NULL || catalog.filmList.count != 2) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first == NULL || catalog.freeFilmList.last == NULL || catalog.freeFilmList.count != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next == NULL || strcmp(catalog.filmList.first->elem.name, film1.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next->next != NULL || strcmp(catalog.filmList.first->next->elem.name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first->next != NULL || strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (&(catalog.filmList.first->next->elem) != catalog.freeFilmList.first->elem) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX2_3", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_4", "Add a duplicated film to the catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Add a duplicated film to the catalog
		error = film_catalog_add(&catalog, film1);
		if (error != E_FILM_DUPLICATED) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (catalog.filmList.first == NULL || catalog.filmList.last == NULL || catalog.filmList.count != 2) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first == NULL || catalog.freeFilmList.last == NULL || catalog.freeFilmList.count != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next == NULL || strcmp(catalog.filmList.first->elem.name, film1.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next->next != NULL || strcmp(catalog.filmList.first->next->elem.name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first->next != NULL || strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (&(catalog.filmList.first->next->elem) != catalog.freeFilmList.first->elem) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX2_4", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 5  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_5", "Remove a non-existing film from the catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Remove a non-existing film from the catalog
		error = film_catalog_del(&catalog, film2.name);
		if (error != E_FILM_NOT_FOUND) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (catalog.filmList.first == NULL || catalog.filmList.last == NULL || catalog.filmList.count != 2) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first == NULL || catalog.freeFilmList.last == NULL || catalog.freeFilmList.count != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next == NULL || strcmp(catalog.filmList.first->elem.name, film1.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next->next != NULL || strcmp(catalog.filmList.first->next->elem.name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first->next != NULL || strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (&(catalog.filmList.first->next->elem) != catalog.freeFilmList.first->elem) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX2_5", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 6  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_6", "Remove a film from the catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Remove a film from the catalog
		error = film_catalog_del(&catalog, film1.name);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (catalog.filmList.first == NULL || catalog.filmList.last == NULL || catalog.filmList.count != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first == NULL || catalog.freeFilmList.last == NULL || catalog.freeFilmList.count != 1) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.filmList.first->next != NULL || strcmp(catalog.filmList.first->elem.name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first->next != NULL || strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (&(catalog.filmList.first->elem) != catalog.freeFilmList.first->elem) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX2_6", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 7  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_7", "Remove a free film from the catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Remove a free film from the catalog
		error = film_catalog_del(&catalog, film3.name);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			if (catalog.filmList.first != NULL || catalog.filmList.last != NULL || catalog.filmList.count != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			} else if (catalog.freeFilmList.first != NULL || catalog.freeFilmList.last != NULL || catalog.freeFilmList.count != 0) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX2_7", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 8  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_8", "Get the number of films");
	if (fail_all) {
		failed = true;
	} else {
		// Add films into the catalog
		film_catalog_add(&catalog, film1);
		film_catalog_add(&catalog, film2);
		film_catalog_add(&catalog, film3);
		film_catalog_add(&catalog, film4);
		
		if (catalog.filmList.first == NULL || catalog.filmList.last == NULL || catalog.filmList.count != 4) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (catalog.freeFilmList.first == NULL || catalog.freeFilmList.last == NULL || catalog.freeFilmList.count != 2) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (film_catalog_len(catalog) != 4 || film_catalog_freeLen(catalog) != 2) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR1_EX2_8", !failed);
	
	/////////////////////////////
	/////  PR1 EX2 TEST 8  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_9", "Remove all films from the catalog");
	if (fail_all) {
		failed = true;
	} else {
		// Remove all the data from the catalog
		error = film_catalog_free(&catalog);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (catalog.filmList.first != NULL || catalog.filmList.last != NULL || catalog.filmList.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		} else if (catalog.freeFilmList.first != NULL || catalog.freeFilmList.last != NULL || catalog.freeFilmList.count != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR1_EX2_9", !failed);
	
	// Release all data
	film_catalog_free(&catalog);
	film_free(&film1);
	film_free(&film2);
	film_free(&film3);
	film_free(&film4);
	
	return passed;
}

// Run all tests for Exercice 3 of PR1
bool run_pr1_ex3(tTestSection *test_section, const char *input) {
	tApiData data;
	tApiError error;
	tCSVEntry entry;
	int nPeople;
	int nSubscriptions;
	int nFilms;
	int nFreeFilms;

	bool passed = true;
	bool failed = false;
	bool fail_all = false;

	/////////////////////////////
	/////  PR1 EX3 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_1", "Initialize the API data structure");
	// Initialize the data
	error = api_initData(&data);
	if (error != E_SUCCESS) {
		failed = true;
		passed = false;
		fail_all = true;
	}
	end_test(test_section, "PR1_EX3_1", !failed);

	/////////////////////////////
	/////  PR1 EX3 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_2", "Add an invalid person");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954", "PERSONA");
		
		// Add an invalid person type
		error = api_addPerson(&data, entry);
		if (error != E_INVALID_ENTRY_TYPE) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954;oops", "PERSON");
		
		// Add an invalid person format
		error = api_addPerson(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;27/08/1954", "PERSON");
		
		// Add an invalid person format
		error = api_addPerson(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_2", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_3", "Add a duplicated person");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954", "PERSON");
		
		// Add a valid person
		error = api_addPerson(&data, entry);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		if (!failed) {
			// Add a duplicated person
			error = api_addPerson(&data, entry);
			
			if (error != E_PERSON_DUPLICATED) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_3", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_4", "Add an invalid subscription");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;98765432J;01/01/2025;31/12/2025;Free;0;1", "SUBSCRIPTIO");
		
		// Add an invalid subscription type
		error = api_addSubscription(&data, entry);
		if (error != E_INVALID_ENTRY_TYPE) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;98765432J;01/01/2025;31/12/2025;Free;0;1;oops", "SUBSCRIPTION");
		
		// Add an invalid subscription format
		error = api_addSubscription(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;98765432J;01/01/2025;31/12/2025;Free;1", "SUBSCRIPTION");
		
		// Add an invalid subscription format
		error = api_addSubscription(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_4", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 5  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_5", "Add a duplicated subscription");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "1;98765432J;01/01/2025;31/12/2025;Free;0;1", "SUBSCRIPTION");
		
		// Add a valid subscription
		error = api_addSubscription(&data, entry);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		if (!failed) {
			// Add a duplicated subscription
			error = api_addSubscription(&data, entry);
			
			if (error != E_SUBSCRIPTION_DUPLICATED) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_5", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 6  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_6", "Add a subscription with non-existing person");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "2;00000000T;01/01/2025;31/12/2025;Free;0;1", "SUBSCRIPTION");
		
		// Add a valid subscription with non-exist person
		error = api_addSubscription(&data, entry);
		if (error != E_PERSON_NOT_FOUND) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_6", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 7  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_7", "Add an invalid film");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "Interstellar;02:49;4;07/11/2014;4.8;0", "FILMO");
		
		// Add an invalid film type
		error = api_addFilm(&data, entry);
		if (error != E_INVALID_ENTRY_TYPE) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "Interstellar;02:49;4;07/11/2014;4.8;0;oops", "FILM");
		
		// Add an invalid film format
		error = api_addFilm(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
		
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "Interstellar;4;07/11/2014;4.8;0", "FILM");
		
		// Add an invalid film format
		error = api_addFilm(&data, entry);
		if (error != E_INVALID_ENTRY_FORMAT) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_7", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 8  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_8", "Add a duplicated film");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_parseEntry(&entry, "Interstellar;02:49;4;07/11/2014;4.8;0", "FILM");
		
		// Add a valid film
		error = api_addFilm(&data, entry);
		if (error != E_SUCCESS) {
			failed = true;
			passed = false;
			fail_all = true;
		}
		
		if (!failed) {
			// Add a duplicated film
			error = api_addFilm(&data, entry);
			
			if (error != E_FILM_DUPLICATED) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
		
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX3_8", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 9  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_9", "Check the number of persons");
	if (fail_all) {
		failed = true;
	} else {
		nPeople = api_peopleCount(data);
		if (nPeople != 1) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			// Valid person
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867", "PERSON");
			api_addPerson(&data, entry);
			csv_freeEntry(&entry);
			
			// Valid person
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972", "PERSON");
			api_addPerson(&data, entry);
			csv_freeEntry(&entry);
			
			// Duplicated person
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972", "PERSON");
			api_addPerson(&data, entry);
			csv_freeEntry(&entry);
			
			// Invalid person
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972", "PERSON");
			api_addPerson(&data, entry);
			csv_freeEntry(&entry);
			
			// Invalid person
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972", "PERSONA");
			api_addPerson(&data, entry);
			csv_freeEntry(&entry);
			
			nPeople = api_peopleCount(data);
			if (nPeople != 3) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX3_9", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 10  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_10", "Check the number of subscriptions");
	if (fail_all) {
		failed = true;
	} else {
		nSubscriptions = api_subscriptionsCount(data);
		if (nSubscriptions != 1) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			// Valid subscription
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3", "SUBSCRIPTION");
			api_addSubscription(&data, entry);
			csv_freeEntry(&entry);
			
			// Duplicated subscription
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3", "SUBSCRIPTION");
			api_addSubscription(&data, entry);
			csv_freeEntry(&entry);
			
			// Invalid subscription
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "3;33365111X;01/05/2025;30/04/2026;Standard;29.95;3", "SUBSCRIPTIONA");
			api_addSubscription(&data, entry);
			csv_freeEntry(&entry);
			
			// Invalid subscription
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "3;33365111X;01/05/2025;30/04/2026;Standard;29.95", "SUBSCRIPTION");
			api_addSubscription(&data, entry);
			csv_freeEntry(&entry);
			
			// Non-existing person
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "3;00000000T;01/05/2025;30/04/2026;Standard;29.95;3", "SUBSCRIPTION");
			api_addSubscription(&data, entry);
			csv_freeEntry(&entry);
			
			nSubscriptions = api_subscriptionsCount(data);
			if (nSubscriptions != 2) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX3_10", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 11 //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX3_11", "Check the number of films");
	if (fail_all) {
		failed = true;
	} else {
		nFilms = api_filmsCount(data);
		nFreeFilms = api_freeFilmsCount(data);
		if (nFilms != 1 || nFreeFilms != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		} else {
			// Valid film
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "Blade Runner 2049;02:44;4;06/10/2017;4.6;1", "FILM");
			api_addFilm(&data, entry);
			csv_freeEntry(&entry);
			
			// Valid film
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "The Matrix;02:16;4;31/03/1999;4.9;1", "FILM");
			api_addFilm(&data, entry);
			csv_freeEntry(&entry);
			
			// Duplicated film
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "The Matrix;02:16;4;31/03/1999;4.9;1", "FILM");
			api_addFilm(&data, entry);
			csv_freeEntry(&entry);
			
			// Invalid film
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "Inception;02:28;0;16/07/2010;4.7;1;oops", "FILM");
			api_addFilm(&data, entry);
			csv_freeEntry(&entry);
			
			// Invalid film
			csv_initEntry(&entry);
			csv_parseEntry(&entry, "Inception;02:28;0;16/07/2010;4.7;1", "FILMO");
			api_addFilm(&data, entry);
			csv_freeEntry(&entry);
			
			nFilms = api_filmsCount(data);
			nFreeFilms = api_freeFilmsCount(data);
			if (nFilms != 3 || nFreeFilms != 2) {
				failed = true;
				passed = false;
				fail_all = true;
			}
		}
	}
	end_test(test_section, "PR1_EX3_11", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 12 //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_12", "Free API data");
	if (fail_all) {
		failed = true;
	} else {
		error = api_freeData(&data);
		nPeople = api_peopleCount(data);
		nSubscriptions = api_subscriptionsCount(data);
		nFilms = api_filmsCount(data);
		nFreeFilms = api_freeFilmsCount(data);
		if (error != E_SUCCESS || nPeople != 0 || nSubscriptions != 0 || nFilms != 0 || nFreeFilms != 0) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR1_EX2_12", !failed);
	
	/////////////////////////////
	/////  PR1 EX3 TEST 13 //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX2_13", "Load data from file");
	if (fail_all) {
		failed = true;
	} else {
		error = api_loadData(&data, input, true);
		nPeople = api_peopleCount(data);
		nSubscriptions = api_subscriptionsCount(data);
		nFilms = api_filmsCount(data);
		nFreeFilms = api_freeFilmsCount(data);
		if (error != E_SUCCESS || nPeople != 5 || nSubscriptions != 5 || nFilms != 15 || nFreeFilms != 11) {
			failed = true;
			passed = false;
			fail_all = true;
		}
	}
	end_test(test_section, "PR1_EX2_13", !failed);
	
	// Release all data
	api_freeData(&data);

	return passed;
}

// Run all tests for Exercice 4 of PR1
bool run_pr1_ex4(tTestSection *test_section, const char *input) {
	tApiData data;
	tApiError error;
	tCSVEntry entry;
	tCSVEntry refEntry;
	tCSVData report;
	tCSVData refReport;
	int nPeople;
	int nSubscriptions;
	int nFilms;
	int nFreeFilms;
	bool passed = true;
	bool failed = false;
	bool fail_all = false;

	// Initialize the data
	error = api_initData(&data);
	if (error != E_SUCCESS) {
		passed = false;
		fail_all = true;
	}

	if (!fail_all) {
		error = api_loadData(&data, input, true);
		nPeople = api_peopleCount(data);
		nSubscriptions = api_subscriptionsCount(data);
		nFilms = api_filmsCount(data);
		nFreeFilms = api_freeFilmsCount(data);
		if (error != E_SUCCESS || nPeople != 5 || nSubscriptions != 5 || nFilms != 15 || nFreeFilms != 11) {
			passed = false;
			fail_all = true;
		}
	}

	/////////////////////////////
	/////  PR1 EX4 TEST 1  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX4_1", "Request a missing subscription");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		error = api_getSubscription(data, 999, &entry);
		if (error != E_SUBSCRIPTION_NOT_FOUND) {
			failed = true;
			passed = false;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX4_1", !failed);

	/////////////////////////////
	/////  PR1 EX4 TEST 2  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX4_2", "Request a valid subscription");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_initEntry(&refEntry);
		csv_parseEntry(&refEntry, "5;47051307Z;01/01/2023;31/12/2028;Premium;29.95;3", "SUBSCRIPTION");
		error = api_getSubscription(data, 5, &entry);
		if (error != E_SUCCESS || !csv_equalsEntry(entry, refEntry)) {
			failed = true;
			passed = false;
		}
		csv_freeEntry(&entry);
		csv_freeEntry(&refEntry);
	}
	end_test(test_section, "PR1_EX4_2", !failed);
 
	/////////////////////////////
	/////  PR1 EX4 TEST 3  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX4_3", "Request a missing film");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		error = api_getFilm(data, "Unknown", &entry);
		if (error != E_FILM_NOT_FOUND) {
			failed = true;
			passed = false;
		}
		csv_freeEntry(&entry);
	}
	end_test(test_section, "PR1_EX4_3", !failed);

	/////////////////////////////
	/////  PR1 EX4 TEST 4  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX4_4", "Request a valid film");
	if (fail_all) {
		failed = true;
	} else {
		csv_initEntry(&entry);
		csv_initEntry(&refEntry);
		csv_parseEntry(&refEntry, "The Pursuit of Happyness;01:57;2;15/12/2006;4.4;1", "FILM");
		error = api_getFilm(data, "The Pursuit of Happyness", &entry);
		if (error != E_SUCCESS || !csv_equalsEntry(entry, refEntry)) {
			failed = true;
			passed = false;
		}
		csv_freeEntry(&entry);
		csv_freeEntry(&refEntry);
	}
	end_test(test_section, "PR1_EX4_4", !failed);

	/////////////////////////////
	/////  PR1 EX4 TEST 5  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX4_5", "Get free films");
	if (fail_all) {
		failed = true;
	} else {
		csv_init(&report);
		csv_init(&refReport);

		csv_addStrEntry(&refReport, "Blade Runner 2049;02:44;4;06/10/2017;4.6;1", "FILM");	
		csv_addStrEntry(&refReport, "The Matrix;02:16;4;31/03/1999;4.9;1", "FILM");
		csv_addStrEntry(&refReport, "Inception;02:28;0;16/07/2010;4.7;1", "FILM");
		csv_addStrEntry(&refReport, "Die Hard;02:12;0;15/07/1988;4.3;1", "FILM");
		csv_addStrEntry(&refReport, "Superbad;01:53;1;17/08/2007;4.0;1", "FILM");
		csv_addStrEntry(&refReport, "Monty Python and the Holy Grail;01:31;1;03/04/1975;4.8;1", "FILM");
		csv_addStrEntry(&refReport, "The Green Mile;03:09;2;10/12/1999;4.8;1", "FILM");
		csv_addStrEntry(&refReport, "The Pursuit of Happyness;01:57;2;15/12/2006;4.4;1", "FILM");
		csv_addStrEntry(&refReport, "The Shining;02:26;3;23/05/1980;4.5;1", "FILM");
		csv_addStrEntry(&refReport, "A Nightmare on Elm Street;01:31;3;09/11/1984;4.1;1", "FILM");
		csv_addStrEntry(&refReport, "Get Out;01:44;3;24/02/2017;4.3;1", "FILM");

		error = api_getFreeFilms(data, &report);
		if (error != E_SUCCESS || !csv_equals(report, refReport)) {
			failed = true;
			passed = false;
		}
		csv_free(&report);
		csv_free(&refReport);
	}
	end_test(test_section, "PR1_EX4_5", !failed);

	/////////////////////////////
	/////  PR1 EX4 TEST 6  //////
	/////////////////////////////
	failed = false;
	start_test(test_section, "PR1_EX4_6", "Get films by genre");
	if (fail_all) {
		failed = true;
	} else {
		csv_init(&report);
		csv_init(&refReport);		

		csv_addStrEntry(&refReport, "Interstellar;02:49;4;07/11/2014;4.8;0" ,"FILM");
		csv_addStrEntry(&refReport, "Blade Runner 2049;02:44;4;06/10/2017;4.6;1" ,"FILM");
		csv_addStrEntry(&refReport, "The Matrix;02:16;4;31/03/1999;4.9;1" ,"FILM");

		error = api_getFilmsByGenre(data, &report, GENRE_SCIENCE_FICTION);
		if (error != E_SUCCESS || !csv_equals(report, refReport)) {
			failed = true;
			passed = false;
		}
		csv_free(&report);
		csv_free(&refReport);
		
		if (!failed) {
			csv_init(&report);
			csv_init(&refReport);		

			csv_addStrEntry(&refReport, "The Shining;02:26;3;23/05/1980;4.5;1" ,"FILM");
			csv_addStrEntry(&refReport, "A Nightmare on Elm Street;01:31;3;09/11/1984;4.1;1" ,"FILM");
			csv_addStrEntry(&refReport, "Get Out;01:44;3;24/02/2017;4.3;1" ,"FILM");

			error = api_getFilmsByGenre(data, &report, GENRE_HORROR);
			if (error != E_SUCCESS || !csv_equals(report, refReport)) {
				failed = true;
				passed = false;
			}
			csv_free(&report);
			csv_free(&refReport);
		}
	}
	end_test(test_section, "PR1_EX4_6", !failed);

	// Release all data
	api_freeData(&data);

	return passed;
}
