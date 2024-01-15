#include<stdio.h>
#include"view.h"
#include"TYPES_H.h"
#include<string.h>
#include<stdlib.h>
status view(tag_info* mp3tag_info,const char *tag_name)
{




char tag1[5];
fread(tag1,4,1,mp3tag_info->fp); //after 10 bytes of tag header  this si 4byte                                  s of frame id(11-14))
tag1[4]='\0';
printf("%s :",tag1);
char buf[4];
int size=0;
for(int i =0;i<4;i++)
{
fread(buf+i,1,1,mp3tag_info->fp);       //4bytesreading size of content 15 -18
size =(size<<(i*8))|buf[i];

}
//printf("%ld\n",ftell(mp3tag_info->fp));
if(!strcmp(tag1,tag_name))
{
//printf("size is %d\n",size);
fseek(mp3tag_info->fp,3,SEEK_CUR);// skipping 3byte of flag after size till 21 
	mp3tag_info->content=malloc(size);

	fread(mp3tag_info->content,size-1,1,mp3tag_info->fp); //from 21 to 21 +size                                                          content  wil be read
	mp3tag_info->content[size]='\0';
}
	return p_success;
}

status display(tag_info* mp3tag_info)
{

fseek(mp3tag_info->fp,10,SEEK_SET);
//printf("%ld",ftell(mp3tag_info->fp));//	
printf("\n-------	MP3 TAG READAER AND EDITOR FOR ID3V2.3----------\n");

int ret=view(mp3tag_info,"TIT2");
if(ret==0) 
printf("TITLE       : %s\n",mp3tag_info->content);

 ret=view(mp3tag_info,"TPE1");
if(ret==0)
printf("ARTIST      : %s\n",mp3tag_info->content);
 
ret=view(mp3tag_info,"TALB");
if(ret==0)
printf("ALBUM      : %s\n",mp3tag_info->content);
 
ret=view(mp3tag_info,"TYER");
if(ret==0)
printf("YEAR       : %s\n",mp3tag_info->content);
 
ret=view(mp3tag_info,"TCON");
if(ret==0)
printf("MUSIC       :%s\n",mp3tag_info->content);

ret=view(mp3tag_info,"COMM");
if(ret==0)
printf("COMMENT     :%s\n",mp3tag_info->content);
printf("\n-------	tags displayed successfully----------");




return p_success;
}


