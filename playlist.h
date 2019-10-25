#include <stddef.h>

// error codes
#define SUCCESS                  100   // Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER  101   // Value to be returned if you detect that one of the input parameters 
                                       // into your function is invalid, e.g. it is NULL or an unexpected value
#define MEMORY_ALLOCATION_ERROR  102   // Value to be returned if a memory allocation error occurs during your function
#define INVALID_LIST_OPERATION   103   // Value to be returned if your function detects an operation that is being
                                       // attempted on your list data structure isn't valid or your list
                                       // isn't in a ready state to receive. For example, an attempt is made to remove
                                       // an item from an empty list
#define NOT_IMPLEMENTED          104   // Value to be returned if you haven't implemented this function yet
#define FILE_IO_ERROR			 105   // Value specifically related to the 'savePlaylist()' function which can be used
                                       // if a file input/output error is detected


/* typedef for a data structure to hold details of an MP3 track */
typedef struct MP3Track {
	char trackName[50];		// the name of the track
	int trackLength;		// the running time in seconds
	struct MP3Track* prev;	// points to the previous track in the playlist before this one
	struct MP3Track* next;	// points to the next track in the playlist after this one
} MP3Track;


/* typedef for the playlist */
typedef struct Playlist {
	MP3Track* head;	// points to the MP3 track at the start / head of the playlist
	MP3Track* tail;	// points to the MP3 track at the end / tail of the playlist
	MP3Track* curr;	// points to the 'current' track, i.e. the one that is currently being played
} Playlist;


/* Create a new, empty playlist, storing a pointer to it in the variable 
   provided (e.g. listPtr) */
int createPlaylist(Playlist **listPtr);

/* Add a new MP3 track into the playlist immediately
   BEFORE the current position in the list */
int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength);

/* Add a new MP3 track into the playlist immediately
   AFTER the current position in the list */
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength);

/* Skip to the next track in the playlist, i.e. shift 'curr' one
   position forward in the list */
int skipNext(Playlist* listPtr);

/* Skip to the previous track in the playlist, i.e. shift 'curr' one
   position back in the list */
int skipPrev(Playlist* listPtr);

/* Get the data for the current track in the playlist */
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack);

/* Remove the MP3 track from the current position in the list. The track data should be copied into 
   the variable provided (*pTrack) for confirmation. The variable ‘moveForward’ is used to suggest 
   what happens to the ‘curr’ pointer in the list after the track is removed. If ‘moveForward’ is set 
   to 1 then the ‘curr’ pointer should be set to point to the next track in the list, immediately 
   after the one which has just been removed. Otherwise, ‘curr’ should be set to point to the previous 
   track in the list, immediately prior to the one which has just been removed. */
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward);

/* Empty the entire contents of the playlist, freeing up any memory that it currently uses */
int clearPlaylist(Playlist* listPtr);

/* save details of all of the tracks in the playlist into the given file */
int savePlaylist(Playlist *listPtr, char filename[]);

/* This function is similar to 'createPlaylist'. It should create a new, empty playlist BUT
   then also load the details of a playlist from the given file (a list of track names and 
   track lengths); insert these as new MP3 tracks into your playlist, and store a pointer to 
   the newly created playlist into the variable provided (e.g. listPtr)  */
int loadPlaylist(Playlist **listPtr, char filename[]);

/* We define this function in 'list_tester.c'.
   Always use this function to request memory.
   Use it, but don't define it. */
void* myMalloc(size_t size);