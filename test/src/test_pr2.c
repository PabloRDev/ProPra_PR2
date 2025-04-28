#include "test_pr2.h"
#include "api.h"
#include <assert.h>
#include <string.h>

// Run all tests for PR2

bool run_pr2(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section, input);
    ok = run_pr2_ex2(section, input) && ok;
    ok = run_pr2_ex3(section, input) && ok;
    
    return ok;
}

bool run_pr2_ex1(tTestSection *test_section, const char* input) {
    bool passed = true;
    bool result = false;
    bool fail_all = false;

    tShowCatalog shows;
    tShow show;    
    tSeason season;
    tEpisode episode, episode_duplicated;
    tShow *realShow ;
    tShow* pShow ;
    tSeason *realSeason;
    tDate date, seasonDate, secondSeasonDate;
    tTime time, episodeDuration,secondEpisodeDuration, episode2_1Duration, episode2_2Duration;
    tTime totalDuration;
    tApiError error;
    float avgRating;


    /////////////////////////////////////////////////
    // PR2 EX1 TEST 1 - Initialize show list
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_1", "Initialize show list");
    error = showList_init(&shows);
    result = (error == E_SUCCESS && shows.count == 0);
    if (!result) fail_all = true;
    end_test(test_section, "PR2_EX1_1", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 2 - Add a new show
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_2", "Add a new show to list");
    if (fail_all) {
        result = false;
    } else {
        error = show_init(&show, "Stranger Things");
        if (error == E_SUCCESS){
            error = showList_add(&shows, show);            
            show_free(&show);
        }
        result = (error == E_SUCCESS && shows.count == 1);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_2", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 3 - Add a season to the show
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_3", "Add a season to the show");
    if (fail_all) {
        result = false;
    } else {
        
        pShow = showList_find(shows, "Stranger Things");
        date_parse(&seasonDate,"15/07/2016");         
        if (pShow == NULL) {
            result = false;
            fail_all = true;
        } else {
            error = season_init(&season, 1, seasonDate);
            if (error == E_SUCCESS)
                error = seasonList_add(&(pShow->seasons), season);
            result = (error == E_SUCCESS && pShow->seasons.count == 1);
            if (!result) fail_all = true;
        }
    }
    end_test(test_section, "PR2_EX1_3", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 4 - Add an episode to the season
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_4", "Add an episode to season 1");
    if (fail_all) {
        result = false;
    } else {
        time_parse(&episodeDuration,"00:47");        
        error = episode_init(&episode,1, "Chapter One: The Vanishing of Will Byers", episodeDuration,  4.5f);
        if (error == E_SUCCESS){
            error = show_addEpisode(&shows, "Stranger Things", 1, episode);
            episode_free(&episode);
            
        }

        realShow = showList_find(shows, "Stranger Things");
        realSeason = NULL;
        if (realShow != NULL) {
            realSeason = seasonList_find(realShow->seasons, 1);
        }
        result = (error == E_SUCCESS && realSeason != NULL && realSeason->episodes.count == 1);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_4", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 5 - Calculate total duration
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_5", "Calculate total duration of season");
    if (fail_all) {
        result = false;
    } else {
        totalDuration = show_seasonTotalDuration(shows, "Stranger Things", 1);
        result = (totalDuration.hour == 0 && totalDuration.minutes == 47);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_5", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 6 - Calculate average rating
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_6", "Calculate average rating of season");
    if (fail_all) {
        result = false;
    } else {
        avgRating = show_seasonAverageRating(shows, "Stranger Things", 1);
        result = (avgRating == 4.5f);
        if (!result) fail_all = true;
    }
    
    if (fail_all) {
        result = false;
    } else {
        avgRating = show_seasonAverageRating(shows, "Not existing show", 1);
        result = (avgRating == 0.0f);
        if (!result) fail_all = true;
    }
    
    end_test(test_section, "PR2_EX1_6", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 7 - Add second season
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_7", "Add a second season to the show");
    if (fail_all || pShow == NULL) {
        result = false;
    } else {
        date_parse(&secondSeasonDate,"27/10/2017"); 
       
        error = season_init(&season, 2, secondSeasonDate);
        if (error == E_SUCCESS)
            error = seasonList_add(&(pShow->seasons), season);
        result = (error == E_SUCCESS && pShow->seasons.count == 2);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_7", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 8 - Add more episodes
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_8", "Add more episodes to both seasons");
    if (fail_all) {
        result = false;
    } else {
        // Season 1
        time_parse(&secondEpisodeDuration,"00:55");
        error = episode_init(&episode, 2, "Chapter Two: The Weirdo on Maple Street", secondEpisodeDuration, 4.7f);
        if (error == E_SUCCESS){
            error = show_addEpisode(&shows, "Stranger Things", 1, episode);
            episode_free(&episode);
        }
        result = (error == E_SUCCESS);       
        
        // Season 2        
        time_parse(&episode2_1Duration,"00:48");
        error = episode_init(&episode, 1,"Chapter One: MADMAX", episode2_1Duration, 4.6f);
        if (error == E_SUCCESS){
            error = show_addEpisode(&shows, "Stranger Things", 2, episode);
            episode_free(&episode);
        }
        result &= (error == E_SUCCESS);      
        
        time_parse(&episode2_2Duration,"00:52");
        error = episode_init(&episode,2, "Chapter Two: Trick or Treat, Freak", episode2_2Duration, 4.8f);
        if (error == E_SUCCESS) {
            error = show_addEpisode(&shows, "Stranger Things", 2, episode);
            episode_free(&episode);
        }
        result &= (error == E_SUCCESS);
       

        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_8", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 9 - Duration of season 2
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_9", "Calculate total duration of other season");
    if (fail_all) {
        result = false;
    } else {
        tTime totalDuration = show_seasonTotalDuration(shows, "Stranger Things", 2);
        result = (totalDuration.hour == 1 && totalDuration.minutes == 40);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_9", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 10 - Rating of season 2
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_10", "Calculate average rating of other season");
    if (fail_all) {
        result = false;
    } else {
        avgRating = show_seasonAverageRating(shows, "Stranger Things", 2);
        result = (avgRating == (4.6f + 4.8f) / 2.0f);
        if (!result) fail_all = true;
        
        // not existing season
        avgRating = show_seasonAverageRating(shows, "Stranger Things", 4);
        result = (avgRating == 0.0f);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX1_10", result);
    passed &= result;


    /////////////////////////////////////////////////
    // PR2 EX1 TEST 11 - Check number of shows with showsList_len
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_11", "Check number of shows with showsList_len");
    if (fail_all) {
        result = false;
    } else {        
        result = (showsList_len(shows) == 1);
        if (!result) fail_all = true;
        
        error = show_init(&show, "One Piece");
        if (error == E_SUCCESS){
            error = showList_add(&shows, show); 
            show_free(&show);
        }       
        
        result = (showsList_len(shows) == 2);
        
        if (!result) fail_all = true;
      
    }
    end_test(test_section, "PR2_EX1_11", result);
    passed &= result;

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 12 - Add duplicated episode 
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_12", "Add duplicated episode");
    if (fail_all) {
        result = false;
    } else {
        showList_free(&shows);
        showList_init(&shows);

        // Step 1: Add show and season    
        date_parse(&date,"15/07/2016");       

        show_init(&show, "Stranger Things");
        season_init(&season, 1, date);
        seasonList_add(&show.seasons, season);  
        
        showList_add(&shows, show);       
        show_free(&show);
        // Step 2: Add first episode using show_addEpisode
        time_parse(&time,"00:47");     
        episode_init(&episode, 1,"Chapter One: The Vanishing of Will Byers", time, 4.5f);
        show_addEpisode(&shows, "Stranger Things", 1, episode);       
        episode_free(&episode);
        
        // Step 3: Try adding the same episode again       
        episode_init(&episode_duplicated,1, "Chapter One: The Vanishing of Will Byers", time, 4.5f);
        
        error = show_addEpisode(&shows, "Stranger Things", 1, episode_duplicated);
        episode_free(&episode_duplicated);
        
        showList_free(&shows);
              
        result = (error == E_EPISODE_DUPLICATED);
    }
    end_test(test_section, "PR2_EX1_12", result);

    /////////////////////////////////////////////////
    // PR2 EX1 TEST 13 - Free show list
    /////////////////////////////////////////////////
    start_test(test_section, "PR2_EX1_13", "Free show list");
    error = showList_free(&shows);
    result = (error == E_SUCCESS && shows.count == 0);
    if (!result) fail_all = true;
    end_test(test_section, "PR2_EX1_13", result);
    passed &= result;

    return passed;
}


bool run_pr2_ex2(tTestSection *test_section, const char* input) {
    bool passed = true;
    bool result = false;
    bool fail_all = false;

    tFilmstack stack;
    tFilm film1, film2, film3, film4;
    tTime duration;
    tDate release;
    bool dup1,dup2,dup3;
    tFilm* topFilm;
    tApiError error;

    duration.hour = 2; duration.minutes = 49;
    release.day = 7; release.month = 11; release.year = 2014;
    film_init(&film1, "Interstellar", duration, 4, release, 4.8f, false);

    duration.hour = 2; duration.minutes = 0;
    release.day = 15; release.month = 5; release.year = 2015;
    film_init(&film2, "Mad Max: Fury Road", duration, 0, release, 4.5f, false);

    duration.hour = 3; duration.minutes = 9;
    release.day = 10; release.month = 12; release.year = 1999;
    film_init(&film3, "The Green Mile", duration, 2, release, 4.8f, true);

    duration.hour = 1; duration.minutes = 57;
    release.day = 15; release.month = 12; release.year = 2006;
    film_init(&film4, "The Pursuit of Happyness", duration, 2, release, 4.4f, true);

    start_test(test_section, "PR2_EX2_1", "Initialize film stack");
    error = filmstack_init(&stack);
    result = (error == E_SUCCESS && filmstack_isEmpty(stack));
    if (!result) fail_all = true;
    end_test(test_section, "PR2_EX2_1", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_2", "Push films to stack");
    if (fail_all) {
        result = false;
    } else {
        filmstack_push(&stack, film1);
        filmstack_push(&stack, film2);
        filmstack_push(&stack, film3);
        filmstack_push(&stack, film4);
        result = (stack.count == 4);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_2", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_3", "Prevent duplicate films");
    if (fail_all) {
        result = false;
    } else {
        dup1 = (filmstack_push(&stack, film1) == E_FILM_ALREADY_EXISTS);
        dup2 = (filmstack_push(&stack, film3) == E_FILM_ALREADY_EXISTS);
        dup3 = (filmstack_push(&stack, film4) == E_FILM_ALREADY_EXISTS);
        result = (dup1 && dup2 && dup3 && stack.count == 4);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_3", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_4", "Top film is last pushed");
    if (fail_all) {
        result = false;
    } else {
        topFilm = filmstack_top(stack);
        result = (topFilm != NULL && strcmp(topFilm->name, "The Pursuit of Happyness") == 0);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_4", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_5", "Pop top film");
    if (fail_all) {
        result = false;
    } else {
        error = filmstack_pop(&stack);
        topFilm = filmstack_top(stack);
        result = (error == E_SUCCESS && topFilm != NULL && strcmp(topFilm->name, "The Green Mile") == 0);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_5", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_6", "Pop all films");
    if (fail_all) {
        result = false;
    } else {
        filmstack_pop(&stack);
        filmstack_pop(&stack);
        filmstack_pop(&stack);
        result = filmstack_isEmpty(stack);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_6", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_7", "Free stack and catalog");
    if (fail_all) {
        result = false;
    } else {
        filmstack_free(&stack);
        result = (stack.count == 0);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_7", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_8", "Pop from empty stack");
    if (fail_all) {
        result = false;
    } else {
        error = filmstack_pop(&stack);
        result = (error == E_STRUCTURE_EMPTY);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_8", result);
    passed &= result;

    start_test(test_section, "PR2_EX2_9", "Top from empty stack");
    if (fail_all) {
        result = false;
    } else {
        topFilm = filmstack_top(stack);
        result = (topFilm == NULL);
        if (!result) fail_all = true;
    }
    end_test(test_section, "PR2_EX2_9", result);
    passed &= result;
    
    film_free(&film1);
	film_free(&film2);
	film_free(&film3);
	film_free(&film4);

    return passed;
}

bool run_pr2_ex3(tTestSection *test_section, const char* input) {
    tApiData data;
    tApiError error;
    tCSVEntry entry;
    tFilmstack* stack;
    tFilm* topFilm;
    int nPeople, nSubscriptions, nFilms, nFreeFilms, nShows;
    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    // Inicialización de datos
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
        nShows = api_showsCount(data);      
       
        if (error != E_SUCCESS || nShows!=3  || nPeople != 5 || nSubscriptions != 5 || nFilms != 15 || nFreeFilms != 11) {
            passed = false;
            fail_all = true;
        }
    }
   
    
    //////////////////////////////////////
    /////  PR2 EX3 TEST 1: Add films  ////
    //////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_1", "Add films to watchlist from CSV");
    if (fail_all) {
        failed = true;
    } else {
        stack = &data.subscriptions.elems[subscriptions_find(data.subscriptions, 5)].watchlist;

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Interstellar;02:49;4;07/11/2014;4.8;0", "FILM");
        api_addToWatchlist(&data, 5, entry);
        csv_freeEntry(&entry);
        
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Mad Max: Fury Road;02:00;0;15/05/2015;4.5;0", "FILM");
        api_addToWatchlist(&data, 5, entry);
        csv_freeEntry(&entry);
        
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "The Green Mile;03:09;2;10/12/1999;4.8;1", "FILM");
        api_addToWatchlist(&data, 5, entry);
        csv_freeEntry(&entry);

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "The Pursuit of Happyness;01:57;2;15/12/2006;4.4;1", "FILM");
        api_addToWatchlist(&data, 5, entry);
        csv_freeEntry(&entry);
        
        if (stack->count != 4) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_1", !failed);

    //////////////////////////////////////////////
    /////  PR2 EX3 TEST 2: Duplicate insert  /////
    //////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_2", "Prevent duplicate film in watchlist");
    if (fail_all) {
        failed = true;
    } else {
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Interstellar;02:49;4;07/11/2014;4.8;0", "FILM");
        error = api_addToWatchlist(&data, 5, entry);
        if (error != E_FILM_ALREADY_EXISTS) {
            failed = true;
            passed = false;
        }
        csv_freeEntry(&entry);
    }
    end_test(test_section, "PR2_EX3_2", !failed);

    //////////////////////////////////////////////
    /////  PR2 EX3 TEST 3: Check top film    /////
    //////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_3", "Top film is the last pushed");
    if (fail_all) {
        failed = true;
    } else {
        topFilm = filmstack_top(*stack);
        if (topFilm == NULL || strcmp(topFilm->name, "The Pursuit of Happyness") != 0) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_3", !failed);

    //////////////////////////////////////////////
    /////  PR2 EX3 TEST 4: Pop top film      /////
    //////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_4", "Pop top film from watchlist");
    if (fail_all) {
        failed = true;
    } else {
        error = filmstack_pop(stack);
        topFilm = filmstack_top(*stack);
        if (error != E_SUCCESS || topFilm == NULL || strcmp(topFilm->name, "The Green Mile") != 0) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_4", !failed);

    //////////////////////////////////////////////
    /////  PR2 EX3 TEST 5: Empty the stack   /////
    //////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_5", "Pop all films and check stack is empty");
    if (fail_all) {
        failed = true;
    } else {
        filmstack_pop(stack);
        filmstack_pop(stack);
        filmstack_pop(stack);
        if (!filmstack_isEmpty(*stack)) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_5", !failed);

    /////////////////////////////////////////////////////
    /////  PR2 EX3 TEST 6: Pop from empty stack     /////
    /////////////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_6", "Pop from empty stack returns error");
    if (fail_all) {
        failed = true;
    } else {
        error = filmstack_pop(stack);
        if (error != E_STRUCTURE_EMPTY) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_6", !failed);

    /////////////////////////////////////////////////////
    /////  PR2 EX3 TEST 7: Top from empty stack     /////
    /////////////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_7", "Top from empty stack returns NULL");
    if (fail_all) {
        failed = true;
    } else {
        topFilm = filmstack_top(*stack);
        if (topFilm != NULL) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_7", !failed);
    
    ///////////////////////////////////////////////////////////////
    /////  PR2 EX3 TEST 8: Verify loaded shows from file    /////
    ///////////////////////////////////////////////////////////////
    
    
    failed = false;
    start_test(test_section, "PR2_EX3_8", "Verify shows and episodes loaded");
    if (fail_all) {
        failed = true;
    } else {
        // Verify Breaking Bad
        tShow* show = api_findShow(data, "Breaking Bad");
        if (show == NULL) {
            failed = true;
            passed = false;
        } else {
            tSeason* season = seasonList_find(show->seasons, 1);
            if (season == NULL || season->episodes.count != 2) {
                failed = true;
                passed = false;
            } else {
                tEpisodeNode* ep = season->episodes.first;
                if (ep == NULL || strcmp(ep->episode.title, "Pilot") != 0) {
                    failed = true;
                    passed = false;
                } else if (ep->next == NULL || strcmp(ep->next->episode.title, "Cat's in the Bag...") != 0) {
                    failed = true;
                    passed = false;
                }
            }
        }

        // Verify Stranger Things
        if (!failed) {
            show = api_findShow(data, "Stranger Things");
            if (show == NULL) {
                failed = true;
                passed = false;
            } else {
                tSeason* season = seasonList_find(show->seasons, 1);
                if (season == NULL || season->episodes.count != 2) {
                    failed = true;
                    passed = false;
                } else {
                    tEpisodeNode* ep = season->episodes.first;
                    if (ep == NULL || strcmp(ep->episode.title, "The Vanishing of Will Byers") != 0) {
                        failed = true;
                        passed = false;
                    } else if (ep->next == NULL || strcmp(ep->next->episode.title, "The Weirdo on Maple Street") != 0) {
                        failed = true;
                        passed = false;
                    }
                }
            }
        }
                     
        // Verify The Office
        if (!failed) {
            show = api_findShow(data, "The Office");
            if (show == NULL) {
                failed = true;
                passed = false;
            } else {
                tSeason* season = seasonList_find(show->seasons, 1);
                if (season == NULL || season->episodes.count != 2) {
                    failed = true;
                    passed = false;
                } else {
                    tEpisodeNode* ep = season->episodes.first;
                    if (ep == NULL || strcmp(ep->episode.title, "Pilot") != 0) {
                        failed = true;
                        passed = false;
                    } else if (ep->next == NULL || strcmp(ep->next->episode.title, "Diversity Day") != 0) {
                        failed = true;
                        passed = false;
                    }
                }
            }
        }
    }
    end_test(test_section, "PR2_EX3_8", !failed);


    
    ///////////////////////////////////////////////////////////////
    /////  PR2 EX3 TEST 9: Add episodes to existing shows     /////
    /////                 and check number of shows           /////
    ///////////////////////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_9", "Add episodes to new season");
    if (fail_all) {
        failed = true;
    } else {
        // Add episode to Breaking Bad, season 2
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Breaking Bad;2;08/03/2009;1;Seven Thirty-Seven;00:47;4.7", "SHOW");
        error = api_addDataEntry(&data, entry);
        csv_freeEntry(&entry);

        // Add episode to Stranger Things, season 2
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Stranger Things;2;27/10/2017;1;MADMAX;00:48;4.6", "SHOW");
        error = api_addDataEntry(&data, entry);
        csv_freeEntry(&entry);

        // Add episode to The Office, season 1
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "The Office;2;24/03/2005;1;The Dundies;00:23;4.1", "SHOW");
        error = api_addDataEntry(&data, entry);
        csv_freeEntry(&entry);

        // Check that number of shows remains the same (should be 3)
        if (api_showsCount(data) != 3) {
            failed = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX3_9", !failed);

    ///////////////////////////////////////////////////////////////
    /////  PR2 EX3 TEST 10: Verify manually added episodes    /////
    ///////////////////////////////////////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_10", "Verify manually added episodes");
    if (fail_all) {
        failed = true;
    } else {
        // Verify Breaking Bad - Season 2 - Seven Thirty-Seven
        tShow* show = api_findShow(data, "Breaking Bad");
        if (show == NULL) {
            failed = true;
            passed = false;
        } else {
            tSeason* season = seasonList_find(show->seasons, 2);
            if (season == NULL || season->episodes.count != 1) {
                failed = true;
                passed = false;
            } else {
                tEpisodeNode* ep = season->episodes.first;
                if (ep == NULL || strcmp(ep->episode.title, "Seven Thirty-Seven") != 0) {
                    failed = true;
                    passed = false;
                }
            }
        }

        // Verify Stranger Things - Season 2 - MADMAX
        if (!failed) {
            show = api_findShow(data, "Stranger Things");
            if (show == NULL) {
                failed = true;
                passed = false;
            } else {
                tSeason* season = seasonList_find(show->seasons, 2);
                if (season == NULL || season->episodes.count != 1) {
                    failed = true;
                    passed = false;
                } else {
                    tEpisodeNode* ep = season->episodes.first;
                    if (ep == NULL || strcmp(ep->episode.title, "MADMAX") != 0) {
                        failed = true;
                        passed = false;
                    }
                }
            }
        }

        // Verify The Office - Season 1 - Pilot
        if (!failed) {
            show = api_findShow(data, "The Office");
            if (show == NULL) {
                failed = true;
                passed = false;
            } else {
                tSeason* season = seasonList_find(show->seasons, 2);
                if (season == NULL || season->episodes.count != 1) {
                    failed = true;
                    passed = false;
                } else {
                    tEpisodeNode* ep = season->episodes.first;
                    if (ep == NULL || strcmp(ep->episode.title, "The Dundies") != 0) {
                        failed = true;
                        passed = false;
                    }
                }
            }
        }
    }
    end_test(test_section, "PR2_EX3_10", !failed);


  
    api_freeData(&data);

   

    return passed;
}

