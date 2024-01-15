/*
Name          : syed abdul khadar
Date          : 31-08-2023
Title         : Inverted Search
Description   : The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query. 
                Without an index, the search engine would scan every document in the corpus, which would require considerable time and 
                computing power.
Pre-requisite : Hashing and Single linked list
 */

#include "inverted_search.h"

int main( int argc, char *argv[] )
{
    // Declare required variables
    Flist *f_head = NULL;
    int choice,f=0;
	char option, word[WORD_SIZE];
    Wlist *head[27] = {NULL};


    // Validate the CLA's
    if ( argc == 1 )
    {
        printf ("Enter the valid number of arguments\n");
        printf ( "./Slist.exe f1.txt f2.txt ......\n");
        return 1;
    }

    // Call the file validation function
    file_validation_n_file_list ( &f_head, argv);

    // If file is not valid
    if ( f_head == NULL )
    {
        printf ("No file is available in the file linked list\nHence the process is terminated\n");
        return 1;
    }

    do
	{
		// Display the menu and read the choice from the user
		printf ("Select your choice from following options: \n1.Create Database\n2.Display Database\n3.Update Database\n4.Search Database\n5.Save Database\nEnter your choice: ");
		scanf ("%d", &choice);

		/* Switch case */
		switch ( choice )
		{
			/*1 . Create Database */
			case 1:
				if(f==0)
				{
				create_database ( f_head, head );
				f++;
				}
				else 
					printf("Already  database created \n");

				break;

			/*2. Display Database */
			case 2:
				if(f!=0)
				{
				display_database ( head );
				}
				else
				{
					printf("Database not created,create database first\n");
				}
				break;

            /*3. Update Database */
			case 3:
			    if(f!=0)
				{
					update_database ( head, &f_head );	
				}
				else
				{
					
					printf("Database not created so create database first\n");
				}

		
				break;

			/*4. Search database */
			case 4:
				if(f!=0)
				{
				printf ("Enter the word to be searched in the database : ");
				scanf ("%s", word);
                // To determine the index
				int index = tolower ( word[0] ) % 97;
				if ( index > 25 )
					index = 26;
				search ( head[index], word );
				}
				else
				{
                    printf("Database not created so create database first\n");
				}
				break;

			/*5. Save database */
			case 5:
				if(f!=0)
                                {
                               
				save_database ( head );
                                 }
				else
					printf("Database not created so create database first\n");

				break;
		         default:
				printf("Invalid choice\n");
			    break;
		}

        // Implement the continue option
		printf ("Do you want to continue ? \nEnter y/Y to continue else n/N not to continue: ");
		scanf ("\n%c", &option);
	}while ( option == 'y' || option == 'Y' );
    
    return 0;

}
