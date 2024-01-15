#include "inverted_search.h"

// Function Definition
void save_database ( Wlist *head[] )
{
    // Declare required variables
    char file_name[FNAME_SIZE];

    // Prompt the user to enter the file name
    printf ("Enter the file name to save in database: ");
    scanf ("%s", file_name);

    // Open the file
    FILE *fptr = fopen ( file_name, "w" );

    // To access all the indices
    for ( int i = 0; i < 27; i++ )
    {
        if ( head[i] != NULL )
        {
            // Call write database file function
            write_databasefile ( head[i], fptr );
        }
    }
    printf ("Database saved\n");

}

void write_databasefile ( Wlist *head, FILE* databasefile )
{
    while ( head )
    {
        int index = ( tolower ( head -> word[0]) % 97 );
        if ( !( index >= 0 && index <= 25 ) )
            index = 26;
        
        fprintf ( databasefile, "# : [%2d]  word is  [%-7s]: file count  %d :file/s:", index, head -> word, head -> file_count); 
       
        //Create local reference pointer
        Ltable *Thead = head -> Tlink;

        //Traverse through the link table
        while ( Thead )
        {
            
            fprintf ( databasefile, "   file is %s:  word count is %d", Thead -> file_name, Thead -> word_count); 
            Thead = Thead -> table_link; // Update Thead         
        }

         fprintf(databasefile,"\n");
        head = head -> link; // Update head 
    }
}
