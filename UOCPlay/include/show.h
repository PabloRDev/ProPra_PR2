#ifndef __SHOW_H__
#define __SHOW_H__

#include <stdbool.h>
#include "csv.h"
#include "date.h"
#include "error.h"

#define NUM_FIELDS_SHOW 7

///////////////////////////////////////////////// 
// Data structures
/////////////////////////////////////////////////

// Episode data structure
typedef struct _tEpisode {
    char* title;
    int number;
    tTime duration;
    float rating;
} tEpisode;

// Node for the episode queue
typedef struct _tEpisodeNode {
    tEpisode episode;
    struct _tEpisodeNode* next;
} tEpisodeNode;

// Episode queue
typedef struct _tEpisodeQueue {
    tEpisodeNode* first;
    tEpisodeNode* last;
    int count;
} tEpisodeQueue;

// Season data structure
typedef struct _tSeason {
    int number;
    tDate releaseDate;
    int numEpisodes;
    tEpisodeQueue episodes;
} tSeason;

// Node for the singly linked list of seasons
typedef struct _tSeasonNode {
    tSeason season;
    struct _tSeasonNode* next;
} tSeasonNode;

// List of seasons
typedef struct _tSeasonList {
    tSeasonNode* first;
    int count;
} tSeasonList;

// Show data structure
typedef struct _tShow {
    char* name;
    tSeasonList seasons;
} tShow;

// Node for the doubly linked list of shows
typedef struct _tShowNode {
    tShow show;
    struct _tShowNode* next;
    struct _tShowNode* prev;
} tShowNode;

// Doubly linked list of shows
typedef struct _tShowCatalog {
    tShowNode* first;
    tShowNode* last;
    int count;
} tShowCatalog;

/////////////////////////////////////////////////
// Main methods for managing data structures
/////////////////////////////////////////////////

// Parse a CSV entry into a show structure
void show_parse(tShow* show, tCSVEntry entry);

// Print a single show, including its seasons and episodes
void show_print(const tShow* show);

// Return the number of total shows
int showsList_len(tShowCatalog shows);

// Initialize a show with name and empty season list
tApiError show_init(tShow* data, const char* name);

// Initialize an episode with title, number, duration and rating
tApiError episode_init(tEpisode* ep, int episodeNumber, const char* title, tTime duration, float rating);

// Initialize a season with number and release date
tApiError season_init(tSeason* season, int number, tDate releaseDate);

// Initialize a show list
tApiError showList_init(tShowCatalog* list);

// Initialize a season list
tApiError seasonList_init(tSeasonList* list);

// Initialize an episode queue
tApiError episodeQueue_init(tEpisodeQueue* queue);

// Add a show to the show list
tApiError showList_add(tShowCatalog* list, tShow show);

// Add a season to the season list
tApiError seasonList_add(tSeasonList* list, tSeason season);

// Enqueue an episode in the episode queue
tApiError episodeQueue_enqueue(tEpisodeQueue* queue, tEpisode episode);

// Find a show in the show list by name
tShow* showList_find(tShowCatalog list, const char* name);

// Find a season in the season list by number
tSeason* seasonList_find(tSeasonList list, int number);

// Delete a show from the show list
tApiError showList_del(tShowCatalog* list, const char* name);

// Delete a season from the season list
tApiError seasonList_del(tSeasonList* list, int number);

// Dequeue an episode from the episode queue
tApiError episodeQueue_dequeue(tEpisodeQueue* queue, tEpisode* episode);

// Copy a show from src to dst
tApiError show_cpy(tShow* dst, const tShow* src);

// Copy a season from src to dst
tApiError season_cpy(tSeason* dst, const tSeason* src);

// Copy an episode from src to dst
tApiError episode_cpy(tEpisode* dst, const tEpisode* src);

// Print all shows in the show list
void showList_print(tShowCatalog list);

// Free memory allocated for a single episode
tApiError episode_free(tEpisode* episode);

// Free memory allocated for a single show
tApiError show_free(tShow* show);

// Free all memory from the show list
tApiError showList_free(tShowCatalog* list);

// Free all memory from the season list
tApiError seasonList_free(tSeasonList* list);

// Free memory allocated for a single season
tApiError season_free(tSeason* season);

// Free all memory from the episode queue
tApiError episodeQueue_free(tEpisodeQueue* queue);

// Add an episode to a specific season of a show
tApiError show_addEpisode(tShowCatalog* shows, const char* showName, int seasonNumber, tEpisode episode);

// Calculate the total duration of a season of a show
tTime show_seasonTotalDuration(tShowCatalog shows, const char* showName, int seasonNumber);

// Calculate the average rating of a season
float show_seasonAverageRating(tShowCatalog shows, const char* showName, int seasonNumber);

// Print all episode titles of a season
void season_printEpisodes(tSeason season);

// Return the season with the best average rating from a show
tSeason* show_bestRatedSeason(tShowCatalog shows, const char* showName);

// Return the show with the highest number of seasons
tShow* show_mostSeasons(tShowCatalog shows);



#endif // __SHOW_H__
