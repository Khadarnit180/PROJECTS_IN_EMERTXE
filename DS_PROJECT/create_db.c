#include "inverted_search.h"

// Declare global pointer
char *fname;

// Function Definition
void create_database ( Flist *f_head, Wlist *head[] )
{
    // Traverse through the file linked list
    while ( f_head )
    {
        // Call read_datafile function
        read_datafile ( f_head, head, f_head -> file_name );
	printf ("Successful: Creation of Database for file: %s\n", f_head -> file_name);
        // To advance to next file to read its contents
        f_head = f_head -> link;
    }
}

void read_datafile ( Flist *file, Wlist *head[], char *filename )
{
    // Declare required variables
    FILE *fptr;
    int index, flag = 1;

    // Declare array to store the word
    char word[WORD_SIZE];

    // Store the file name
    fname = filename;    

    // Open the file
    fptr = fopen ( filename, "r" );
    
    // Read the contents of the file till end of file
    while ( fscanf ( fptr, "%s", word ) != EOF )
    {
        // To get the index for different alphabets
        index = ( tolower ( word[0] ) ) % 97;
        // To get index for special characters
        if ( ! ( index >= 0 && index <= 25 ) )
                index = 26;
        
        if ( head[index] != NULL )
        {
            // Traverse through linked list to find words are present or not
            Wlist *temp = head[index];

            while ( temp )
            {
                if ( !strcmp ( temp -> word, word ) )
                {
                    // If words are repeated
                    // Call update_word_count()
                    update_word_count ( &temp, filename );
                    flag = 0;
                    break;
                }
                temp = temp -> link;
            }
        }

        // If the words are not repeated
        if ( flag == 1 )
        {
            // Call insert_at_last() to store the word in linked list
            insert_at_last ( &head[index], word );
        }
    } 
}

int update_word_count ( Wlist **head, char *file_name )
{
    /* Check whether the f

file names are same or not
    If filenames are same, increment word_count
    If filenames are different, increment file_count and create link table */

    Ltable *temp = ( *head ) -> Tlink;

    while ( temp )
    {
        if ( !strcmp ( temp -> file_name, file_name ) )
        {
            ( temp -> word_count ) = ( temp ->word_count ) + 1;
            return SUCCESS;
        }
        temp = temp -> table_link;
    }

    // Increment file_count
    ( ( *head ) -> file_count )++;

    // Create link table
    Ltable *new = malloc ( sizeof ( Ltable ) );

    // Check if node is created or not
    if ( new == NULL )
        return FAILURE; 

    // Update link table
    new -> word_count = 1;
    new -> table_link = NULL;
    strcpy ( new -> file_name, file_name );
    temp = ( *head ) -> Tlink;

    while ( temp -> table_link )
    {
        temp = temp -> table_link;
    }
    temp -> table_link = new;

    return SUCCESS;
}
