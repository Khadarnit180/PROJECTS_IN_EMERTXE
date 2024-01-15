#include "inverted_search.h"

// Function Definition
void update_database ( Wlist *head[], Flist **f_head )
{
    // Declare required variables
    int ret_val, empty,flag=0;

    // Declare an array to store the file name
    char file_name[FNAME_SIZE];

    // Prompt the user to enter the file
    printf ("Enter the file name to update database: ");
    scanf ("%s", file_name);

    // Validate the file

    // Check if the file passed is empty or not
    // Call isFileEmpty() function
    empty = isFileEmpty ( file_name );

    if ( empty == FILE_NOTAVAILABLE )
    {
        printf ("This file: %s is not available\nHence not updated to the file linked list\n", file_name);
        return;
    }

    if ( empty == FILE_EMPTY )
    {
        printf ("This file: %s is empty\nHence not updated to the file linked list\n", file_name);
        return;
    }

    // If file is valid, add the file to file linked list
    // Call to_create_list_of_files()
    ret_val = to_create_list_of_files ( f_head, file_name );


	if ( ret_val ==  SUCCESS )
    {
        printf ("Successful: inserting file %s into the file linked list\n", file_name);
    }
    else if ( ret_val == REPEATATION )
    {
		flag=1;
        printf ("This file %s is repeated. Do not insert into file linked list more than once\n", file_name);
    }
    else if ( ret_val ==  FAILURE )
	{
		flag=1;
        printf ("Failure: inserting file %s into the file linked list\n", file_name);
        return;
    }

   // After successful insertion of new file into file list, update database
    if(flag==0)
	{
		while((*f_head)->link!=NULL)
		{
			(*f_head)=(*f_head)->link;
		}
        create_database ( *f_head, head );
	}
	else
	{
		printf("Database update failed due to duplicate file\n");
	}
}
