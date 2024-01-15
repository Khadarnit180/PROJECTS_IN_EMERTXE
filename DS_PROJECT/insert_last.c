///#include<stdlib.h>
#include "inverted_search.h"
// to use global variable that is intilized in other file extrn using
extern char *fname;
int insert_at_last(Wlist **head, data_t *data)
{

    //create node 

    Wlist *new = malloc(sizeof(Wlist));

    if(new == NULL)
    {
	return FAILURE;
    }

    //update 
    new->file_count = 1;
    strcpy(new->word, data);
    new->Tlink = NULL;
    new->link = NULL;
   // printf("word  ---%s\n ",new->word);
   //call fun to update link table 

   update_link_table(&new);

   //check list is empty or not Wlist
   if(*head == NULL)
   {
       *head = new;
       return SUCCESS;
   }
   // non-empty

   Wlist *temp = *head;
   //traverse through the list

   while(temp->link)
   {
       temp=temp->link;
   }
   temp->link=new;
   return SUCCESS;
}

int update_link_table(Wlist **head)
{
    //create new node 

    Ltable *new = malloc(sizeof(Ltable));

    //error check

    if(new == NULL)
    {
	return FAILURE;
    }

   //update 
    new->word_count = 1;
    strcpy(new->file_name,fname);
    new->table_link = NULL;
    
    (*head)->Tlink = new;
    return SUCCESS;
}
