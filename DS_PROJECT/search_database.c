#include "inverted_search.h"

// Function Definition
void search ( Wlist *head, char *word )
{
    // If linked list is not created for the word
    if ( head == NULL )
    {
        printf ("Search word is not available in the list\n");
        return;
    }

    // Traverse through the list to find the node
    while ( head )
    {
        // If word is present
        if ( !strcmp ( head -> word, word ) )
        {
            printf ("Word %s is present in %d file/s\n", word, head -> file_count);

            //Create a local reference pointer
            Ltable *Thead = head -> Tlink;

            // Traverse through the link table
            while ( Thead )
            {
                printf ("In file: %s %d time/s\n", Thead -> file_name, Thead -> word_count);

                // Advance to the next node in link table
                Thead = Thead -> table_link;
            }

            printf ("\n");
            return;
        }
        head = head -> link;
    }
    printf ("Search word is not available in the list\n");
}
