#include "inverted_search.h"

void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i=1 , empty;
	
    while(argv[i] != NULL)
    {
	empty = isFileEmpty(argv[i]);
	if(empty == FILE_NOTAVAILABLE)
	{
	    printf("File : %s is not available\n" , argv[i]);
	    printf("Hence we are not adding that file into file linked list\n");
	    i++;
	    continue;
	}
	else if(empty == FILE_EMPTY)
	{
	    printf("File : %s is empty\n" , argv[i]);
	    printf("Hence we are not adding that file into file linked list\n");
	    i++;
	    continue;
	}
	else
	{

	    int ret_val = to_create_list_of_files(f_head , argv[i]);

	    if(ret_val == SUCCESS)
	    {
		printf("Successfull : Inserting the file : %s into the file linked list\n" , argv[i]);
	    }
	    else if(ret_val == REPEATATION)
	    {
		printf("This file : %s is repeated. Do not add that file into file linked list\n" , argv[i]);
	    }
	    else
	    {
		printf("Failure\n");
	    }
		i++;
	}
    }
}



//fun is used to check whether file is available or not 
//check for file contents

int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename , "r");
    if(fptr == NULL)
    {
	if(errno == ENOENT)
	{
	    return FILE_NOTAVAILABLE;
	}
    }

    fseek(fptr , 0 , SEEK_END);
    if(ftell(fptr) == 0)
    {
	return FILE_EMPTY;
    }

}

// Function Definition
int to_create_list_of_files ( Flist **f_head, char *name )
{
    // Create the node 
	Flist *new = malloc ( sizeof ( Flist ) );

	// Check if node is created or not
	if ( !new )
		return FAILURE;

	// Update data and link 
	strcpy ( new -> file_name, name );
	new -> link = NULL;

	// Check if list is empty or not
	if ( *f_head == NULL )
	{
		*f_head = new;
		return SUCCESS;
	}

	// Traverse the list till last node 
	Flist *temp = *f_head, *prev;
	while ( temp )
	{
		prev = temp;
		if ( strcmp ( temp -> file_name, name ) )
			temp = temp -> link;
		else
			return REPEATATION; // On files being passed repeatedly
	}

	prev -> link = new;
	return SUCCESS;
}



