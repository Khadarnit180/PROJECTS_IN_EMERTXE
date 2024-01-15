#ifndef view_H
#define view_Hi

#include"TYPES_H.h"
typedef struct tag
{
FILE *fp;
char fname[10];
char title[70];
char *content;
}tag_info;
status display(tag_info* mp3tag_info);

status view(tag_info* mp3tag_info,const char *tag);




#endif
