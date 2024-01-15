/*
Name: Sd .abdul khadar

/*


#include<stdio.h>
#include<string.h>
#include "view.h"
#include "edit.h"
#include "TYPES_H.h"

int main(int argc, char *argv[])
{
if(!strcmp(argv[1],"-v"))
{
	printf("<-------view option selected------------->-\n");
tag_info mp3tag_info;


if(argv[2]!=NULL)
strcpy(mp3tag_info.fname,argv[2]);

mp3tag_info.fp=fopen(mp3tag_info.fname,"r");
if(mp3tag_info.fp==NULL)
{
	printf("error file");

}
char id[3];
fread(id,3,1,mp3tag_info.fp);
int v;
fread(&v,2,1,mp3tag_info.fp);
//printf("%d",v);
if(!strcmp(id,"ID3") )//&& v==0x0300)
{
int ret=display(&mp3tag_info);
if(ret!=0)
{
printf("failure ");
}

}
}
else if(!strcmp(argv[1],"-e"))

printf("<--------edit option selcted--------> \n");
mp3_edit edit_tag_info;
strcpy(edit_tag_info.fname,argv[4]);


edit_tag_info.fp=fopen(edit_tag_info.fname,"r+");
if(edit_tag_info.fp==NULL)
{
	printf("error file");
}



char id[3];
fread(id,3,1,edit_tag_info.fp);
if(!strcmp(id,"ID3") )//&& v==0x0300)
{

if(argc>1 && argc==5)
{
//printf("editing%s%s",argv[2],argv[3]);

int ret=edit(&edit_tag_info,argv);
if(ret!=0)
{
printf("failure ");
}

}
else
{
	printf("enter valid no of args ");
}
}



	return 0;
}
