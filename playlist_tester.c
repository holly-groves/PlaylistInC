#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"
#include <string.h>

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

int main()
{
	// store the result of calling functions
	int result;

	// a variable to store an MP3 track popped from the list
	MP3Track track;

	// a pointer to our doubly-linked list
	Playlist *listPtr = NULL;

	// initialise the list - passing the address of our
	// list pointer as an input so it can be modified 
	// to point to the memory allocated for the list
	result = createPlaylist(&listPtr);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to initialise the list\n");
	}
	else
	{
		printf("List initialised successfully\n");
	}
	printf("\n");

	// try getting data at the current position
	// this should fail because the list is empty
	result = getCurrentTrack(listPtr, &track);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to get data from an empty list\n");
	}
	else
	{
		printf("Correctly identified attempt to get data from an empty list\n");
	}

	// try getting removing data at the current position
	// this should fail because the list is empty
	result = removeAtCurr(listPtr, &track, 1);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to remove data from an empty list\n");
	}
	else
	{
		printf("Correctly identified attempt to remove data from an empty list\n");
	}

	// try  moving 'curr' to the next node in the list
	// this should fail because the list is empty
	result = skipNext(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to skip next list is empty\n");
	}
	else
	{
		printf("Correctly identified attempt to skip next when list is empty\n");
	}

	// try  moving 'curr' to the previous node in the list
	// this should fail because the list is empty
	result = skipPrev(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to skip prev when list is empty\n");
	}
	else
	{
		printf("Correctly identified attempt to skip prev when list is empty\n");
	}
	printf("\n");

	// add a new item to the list
	char trackName[] = "White Christmas";
	int length = 233;
	result = insertAfterCurr(listPtr, trackName, length);
	if (result != SUCCESS)
	{
		printf("Error: failed to add new node to list\n");
	}
	else
	{
		printf("Inserting a new node into list successful\n");
	}
	printf("\n");

	// try  moving 'curr' to the next node in the list
	// this should fail because 'curr' is at the tail of the list, nothing after it
	result = skipNext(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to move 'curr' next when it is already at the tail of the list\n");
	}
	else
	{
		printf("Correctly identified attempt to move 'curr' next when it is already at the tail of the list\n");
	}

	// try  moving 'curr' to the previous node in the list
	// this should fail because 'curr' is at the head of the list, nothing before it
	result = skipPrev(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to move 'curr' previous when it is already at the head of the list\n");
	}
	else
	{
		printf("Correctly identified attempt to move 'curr' previous when it is already at the head of the list\n");
	}	

	// add another item to the list BUT this time with an erroneous / NULL track name
	result = insertAfterCurr(listPtr, NULL, 12);
	if (result != INVALID_INPUT_PARAMETER)
	{
		printf("Error: should have detected attempt to add another item to the list when the track name provided is 'NULL'\n");
	}
	else
	{
		printf("Correctly identified attempt to add another item to the list when the track name provided is 'NULL'\n");
	}
	printf("\n");

	// add another item to the list
	char trackName2[] = "Macarena";
	int length2 = 145;
	result = insertAfterCurr(listPtr, trackName2, length2);
	if (result != SUCCESS)
	{
		printf("Error: failed to add node 2 to list\n");
	}
	else
	{
		printf("Inserting node 2 into list successful\n");
	}
	printf("\n");
	
	// try getting data at the current position
	// We should get the first track in the list, where 'curr' is currently positioned
	result = getCurrentTrack(listPtr, &track);
	if (result != SUCCESS)
	{
		printf("Error: failed to getCurrentTrack() data for the newly added item in the playlist\n");
	}
	else
	{
		printf("Successfully managed to getCurrentTrack() data for the newly added item in the playlist\n");

		// check data retreived is correct
		if (strncmp(track.trackName, trackName, 49) != 0)
		{
			// tracks don't match
			printf("Error: track names don't match in the data obtained for the newly added item in the list\n");
		}
		else
		{
			if (track.trackLength != length)
			{				
				// track lengths don't match
				printf("Error: track lengths don't match in the data obtained for the newly added item in the list\n");
			}
			else
			{
				// all good
				printf("Track names and track lengths match correctly in the data obtained for the newly added item in the list\n");
			}
		}
	}
	printf("\n");

	// try  moving 'curr' to the next node in the list
	result = skipNext(listPtr);
	if (result != SUCCESS)
	{
		printf("Error: failed to move 'curr' to next node in list\n");
	}
	else
	{
		printf("Successfully managed to move 'curr' to next node in list\n");
	}
	printf("\n");

	// get the data for the new current item in the list and check it's validity
	result = getCurrentTrack(listPtr, &track);
	if (result != SUCCESS)
	{
		printf("Error: failed to getCurrentTrack() data for the next item in the list\n");
	}
	else
	{
		printf("Successfully managed to getCurrentTrack() data for the next item in the list\n");

		// check data retreived is correct
		if (strncmp(track.trackName, trackName2, 49) != 0)
		{
			// tracks don't match
			printf("Error: track names don't match in the data obtained for the next item in the list\n");
		}
		else
		{
			if (track.trackLength != length2)
			{				
				// track lengths don't match
				printf("Error: track lengths don't match in the data obtained for the next item in the list\n");
			}
			else
			{
				// all good
				printf("Track names and track lengths match correctly in the data obtained for the next item in list\n");
			}
		}
	}
	printf("\n");


	// try saving the list to a file
	result = savePlaylist(listPtr, "out.txt");
	if (result != SUCCESS)
	{
		printf("Error: failed to write playlist to file.\n");
	}
	else
	{
		printf("Successfully managed to write playlist to file\n");
	}
	printf("\n");

	// try removing a node
	result = removeAtCurr(listPtr, &track, 1);
	if (result != SUCCESS)		
	{
		printf("Error: failed to remove the node from the current position in the list\n");
	}
	else
	{
		printf("Successfully managed to remove the node from the current position in the list\n");

		// check data retreived is correct
		if (strncmp(track.trackName, trackName2, 49) != 0)
		{
			// tracks don't match
			printf("Error: track names don't match in data obtained from node removed\n");
		}
		else
		{
			if (track.trackLength != length2)
			{				
				// track lengths don't match
				printf("Error: track lengths don't match in data obtained from node removed\n");
			}
			else
			{
				// all good
				printf("Track name and track length are correct in the data obtained from the removed node\n");
			}
		}
	}
	printf("\n");

	// try emptying the list
	result = clearPlaylist(listPtr);
	if (result != SUCCESS)
	{
		printf("Error: failed to clear the playist\n");
	}
	else
	{
		printf("Successfully free-d the playlist\n");
	}
	printf("\n");

	// a pointer to a another doubly-linked list - this time to load from a file
	Playlist *listPtr2 = NULL;

	// attempt to load a playlist from a file
	result = loadPlaylist(&listPtr2, "test_playlist.txt");
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to load playlist from a file\n");
	}
	else
	{
		printf("Playlist loaded from file successfully\n");

		// display the contents of the list
		MP3Track *pTrack = listPtr2->head;
		while (pTrack!=NULL)
		{
			printf("Next track name is %s and track length %d\n", pTrack->trackName, pTrack->trackLength);
			pTrack = pTrack->next;
		}

		// free the memory for the playlist
		result = clearPlaylist(listPtr2);
		if (result != SUCCESS)
		{
			printf("Error: failed to free playlist loaded from file\n");
		}
		else
		{
			printf("Successfully free-d the playlist loaded from file\n");
		}
	}

	return 0;
}