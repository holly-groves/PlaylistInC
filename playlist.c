/*
	Name: Holly Groves
	Matric: 180007261
	Module: AC21008
	Playlist Assignment
		Doubly Linked List with Iterator
*/

#include "playlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
	create a new playlist (a new doubly linked list)
	parameters:
		listPtr - receives a pointer to the new doubly linked list
*/
int createPlaylist(Playlist **listPtr){
	//check that the memory address was provided
	if (listPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the list has not been created already
	if (*listPtr != NULL)
		return INVALID_INPUT_PARAMETER;

	//allocate memory for the new list and store in the pointer
	(*listPtr) = (Playlist*)myMalloc(sizeof(Playlist));

	//check that memory allocation was successful
	if ((*listPtr) == NULL)
		return MEMORY_ALLOCATION_ERROR;

	//initialise fields in the list (playlist)
	(*listPtr)->head = NULL;
	(*listPtr)->tail = NULL;
	(*listPtr)->curr = NULL;

	return SUCCESS;
}

/*
	insert a new track before the current track (insert a new node before the current node in the list)
	parameters:
		listPtr - a pointer to the playlist
		trackName - name of the track to add
		trackLength - the length of the track to add
*/
int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength) {
	//input validation
	if (trackName == NULL)
		return INVALID_INPUT_PARAMETER;
	int strLength; 
	strLength = strlen(trackName); //get the length of the track name
	if (strLength > 50) //validate name
		return INVALID_INPUT_PARAMETER;
		
	if (trackLength == 0) //validate track length
		return INVALID_INPUT_PARAMETER;

	//check the pointer given is valid
	if (listPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//create a new track to go into the playlist
	MP3Track *newTrack = (MP3Track*)myMalloc(sizeof(MP3Track));
	//check memory allocation was successful
	if (newTrack == NULL)
		return MEMORY_ALLOCATION_ERROR;

	//initialise fields in new node
	strcpy(newTrack->trackName, trackName);
	newTrack->trackLength = trackLength;
	newTrack->prev = NULL;
	newTrack->next = NULL;

	
	if (listPtr->curr == NULL) //if the playlist is empty
	{
		listPtr->head == newTrack;
		listPtr->tail == newTrack;
		listPtr->curr == newTrack;
	}
	else if (listPtr->curr == listPtr->head) //if the current track is at the head of the list
	{
		newTrack->next = listPtr->curr;
		listPtr->curr->prev = newTrack;
		listPtr->head = newTrack;
	}
	else //if the current track is not the head of the list
	// if (listPtr->curr->prev != NULL) 
	{
		newTrack->next = listPtr->curr;
		newTrack->prev = listPtr->curr->prev;
		listPtr->curr->prev->next = newTrack;
		listPtr->curr->prev = newTrack;
		// //move curr one position back in the list
		// listPtr->curr = listPtr->curr->prev;
	}

	return SUCCESS;
}

/*
	insert a new track after the current track (insert a new node after the current node)
	parameters:
		listPtr - a pointer to the playlist
		trackName - name of the track to be added
		trackLength - length of the track to be added
*/
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength){
	//input validation
	if (trackName == NULL)
		return INVALID_INPUT_PARAMETER;
	int strLength; 
	strLength = strlen(trackName); //get the length of the track name
	if (strLength > 50) //validate name
		return INVALID_INPUT_PARAMETER;
	if (trackLength <= 0) //validate track length
		return INVALID_INPUT_PARAMETER;

	//check the pointer given is valid
	if (listPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//create a new track to go into the playlist
	MP3Track *newTrack = (MP3Track*)myMalloc(sizeof(MP3Track));
	//check memory allocation was successful
	if (newTrack == NULL)
		return MEMORY_ALLOCATION_ERROR;

	//initialise fields in new node
	strcpy(newTrack->trackName, trackName);
	newTrack->trackLength = trackLength;
	newTrack->prev = NULL;
	newTrack->next = NULL;

	if (listPtr->curr == NULL) //if the list is empty
	{
  		listPtr->head = newTrack;
	  	listPtr->tail = newTrack;
  		listPtr->curr = newTrack;
	}	
	else //if the list isn't empty
	{
		if (listPtr->curr == listPtr->tail) //if the current track is at the tail of the list
		{
			newTrack->prev = listPtr->curr;
  			listPtr->curr->next = newTrack;
  			listPtr->tail = newTrack;
		}
		else //if the current track is in the middle of the list
		{
     		newTrack->prev = listPtr->curr;
     		newTrack->next = listPtr->curr->next;
  		  	listPtr->curr->next->prev = newTrack;
  			listPtr->curr->next = newTrack;
		}
	}

	return SUCCESS;
}

/*
	go to the next track in the playlist (make the next node after the current node the new current node)
	paramters:
		listPtr - a pointer to the playlist
*/
int skipNext(Playlist* listPtr){
	//validation
	if (listPtr == NULL) //if list is not initialised
		return INVALID_INPUT_PARAMETER;
	if (listPtr->curr == NULL || listPtr->curr->next == NULL) //if list is empty or current track is at the tail
		return INVALID_LIST_OPERATION;
	
	listPtr->curr = listPtr->curr->next;

	return SUCCESS;
}

/*
	go to the previous track in the playlist (make the node before the current node the new current node)
	parameters:
		listPtr - a pointer to the playlist
*/
int skipPrev(Playlist* listPtr){
	//validation
	if (listPtr == NULL) //if list is not initialised
		return INVALID_INPUT_PARAMETER;
	if (listPtr->curr == NULL  || listPtr->curr->prev == NULL) //if list is empty or current track is at the head
		return INVALID_LIST_OPERATION;
	
	listPtr->curr = listPtr->curr->prev;

	return SUCCESS;
}

/*
	get the information for the current track in the playlist
	parameters:
		listPtr - a pointer to the playlist
		pTrack - a pointer which will recieve the current track
*/
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack){
	//validation
	if (listPtr == NULL) //check that it is a valid list
		return INVALID_INPUT_PARAMETER;
	if (listPtr->curr == NULL) //check that the list isn't empty
		return INVALID_LIST_OPERATION;

	//get the data from the current track
	strcpy(pTrack->trackName, listPtr->curr->trackName);
	pTrack->trackLength = listPtr->curr->trackLength;
	pTrack->next = listPtr->curr->next;
	pTrack->prev = listPtr->curr->prev;

	return SUCCESS;
}

/*
	remove the current track from the playlist
	parameters:
		listPtr - a pointer to the playlist
		pTrack - will store the track to be removed
		moveForward - used when the track to be removed is not at the head or the tail to determine where current should move to
*/
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward){
	if (listPtr == NULL) //check that the list is initalised
		return INVALID_INPUT_PARAMETER;
	if(listPtr->head == NULL) //check that the list isn't empty
		return INVALID_LIST_OPERATION;

	/* set the track to remove (pTrack) to the current node */
	strcpy(pTrack->trackName, listPtr->curr->trackName);
	pTrack->trackLength = listPtr->curr->trackLength;
	pTrack->next = listPtr->curr->next;
	pTrack->prev = listPtr->curr->prev;

	if (listPtr->head == listPtr->tail) //there is only one item in the list
	{
		listPtr->head = NULL;
		listPtr->tail = NULL;
		listPtr->curr = NULL;
		free(listPtr->curr);
	}
	else //more than one item in the list
	{
		if (listPtr->head == listPtr->curr) //if current track is at the head of the list
		{
			listPtr->head = pTrack->next;
			listPtr->head->prev = NULL;
			listPtr->curr = listPtr->head;
			free(listPtr->curr);
		}
		else if (listPtr->tail == listPtr->curr) //if the current track is at the tail of the list
		{
			listPtr->tail = pTrack->prev;
			listPtr->tail->next == NULL;
			listPtr->curr = listPtr->tail;
			free(listPtr->curr);
		}
		else //more than one track in the playlist, track to be removed is in the middle of the playlist
		{
			pTrack->prev->next = pTrack->next;
			pTrack->next->prev = pTrack->prev;
			listPtr->curr = pTrack->next;
			free(listPtr->curr);

			if (moveForward == 1) //move the curr to the next track
				listPtr->curr = pTrack->next;
			else //move the curr to the previous track
				listPtr->curr = pTrack->prev;
		}
	}

	return SUCCESS;
}

/*
	empty the contents of the playlist (empty the contents of the doubly linked list)
	parameters:
		listPtr - a pointer to the list to be freed
*/
int clearPlaylist(Playlist* listPtr){
	if (listPtr == NULL) //check the list is valid
		return INVALID_INPUT_PARAMETER;

	while (listPtr->head != NULL)
	{
		MP3Track *curr = listPtr->head;
		listPtr->head = listPtr->head->next;

		free(curr);
	}

	free(listPtr);

	return SUCCESS;
}

/*
	save the contents of a playlist to a file (save the information of the doubly linked list)
	parameters:
		listPtr - a pointer to the playlist to be saved
		filename - name of file that will have the playlist saved
*/
int savePlaylist(Playlist *listPtr, char filename[]){
	if (listPtr == NULL)
		INVALID_INPUT_PARAMETER;
	if (filename == NULL)
		INVALID_INPUT_PARAMETER;

	FILE *fp;
	fp = fopen(filename, "w");
	char hash = '#';
	char newLine = '\n';
	if (fp != NULL) //if the file opened successfully
	{
		MP3Track *temp = listPtr->head;
		while (temp)
		{
			char tempName[50];
			strcpy(tempName, temp->trackName);
			int tempLength = temp->trackLength;

			fputs(tempName, fp);
			fputc(hash, fp);
			fprintf(fp, "%d" ,tempLength);
			fputc(hash, fp);
			fputc(newLine, fp);

			temp = temp->next;
		}
		fclose(fp);
	}
	return SUCCESS;
}

/*
	creates a new playlist (a new list) and loads the contents from a file
	reuses the code from the create a playlist 
	reads from a file with the same layout used in the save a playlist method
	paramters:
		listPtr - a pointer to the new playlist being created
		filename - name of the file to load from
*/
int loadPlaylist(Playlist **listPtr, char filename[]){
	(void)listPtr;
	(void)filename;
	return NOT_IMPLEMENTED;
}