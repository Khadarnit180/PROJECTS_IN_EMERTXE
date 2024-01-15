#include "inverted_search.h"

// Function Definition
void display_database ( Wlist *head[] )
{ 
    printf ("[index] [word]               file_count      file/s: File: File_name       word_count\n");

    // To go to that paticular index of linked list
    for ( int i = 0; i < 27; i++ )
    {
        if ( head[i] != NULL )
        {
            // Call print word count function
            print_word_count ( head[i] );
        }
    }
}

int print_word_count ( Wlist *head )
{
    while ( head != NULL )
    {
	int index = ( tolower ( head -> word[0] ) ) % 97;
        if ( !( index >= 0 && index <= 25 ) )
            index = 26;
        
        printf ("[%-2d]     [%-15s]       %d           file/s: ", index, head -> word,  head -> file_count);

        // Declare a pointer pointing to link table
        Ltable *Thead = head -> Tlink;

        // Traverse through the link table
        while ( Thead != NULL )
        {
            printf ("File: %s             %d     ", Thead -> file_name, Thead -> word_count);

            // Advance to next node of link table
            Thead = Thead -> table_link;
        }
        printf("\n");
        head = head -> link;
    }
}
