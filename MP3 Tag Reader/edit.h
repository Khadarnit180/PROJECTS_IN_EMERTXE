#ifndef view_H
#define view_H

#include"TYPES_H.h"
typedef struct edit
{
FILE *fp;
char fname[10];
char title[70];
char *content;
}mp3_edit;
status edit_view(mp3_edit* mp3tag_info,const char *,char *argv[]);

status edit(mp3_edit* mp3tag_info, char **argv);




#endif
