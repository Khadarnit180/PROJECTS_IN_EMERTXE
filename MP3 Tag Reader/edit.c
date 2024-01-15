#include<stdio.h>
#include"edit.h"
#include"TYPES_H.h"
#include<string.h>
#include<stdlib.h>



status edit_view(mp3_edit* edit_tag_info,const char *tag_name,char *argv[])
{
char tag1[5];
fread(tag1,4,1,edit_tag_info->fp); //after 10 bytes of tag header  this si 4byte                                  s of frame id(11-14))
tag1[4]='\0';
//printf("%s :",tag1);
char buf[4];
int size=0;
for(int i =0;i<4;i++)
{
fread(buf+i,1,1,edit_tag_info->fp);       //4bytesreading size of content 15 -18
size =(size<<(i*8))|buf[i];

}
fseek(edit_tag_info->fp,3,SEEK_CUR);// skipping 3byte of flag after size till 21 pr
//printf("%ld\n",ftell(edit_tag_info->fp));
if(!strcmp(tag1,tag_name))
{
	if(argv[3]!=NULL)
//printf("size is %s\n",argv[3]);

	edit_tag_info->content=malloc(size);
			strcpy(edit_tag_info->content,argv[3]);
		//	printf("%s",edit_tag_info->content);

fwrite(edit_tag_info->content,size-1,1,edit_tag_info->fp);
fseek(edit_tag_info->fp,-(size-1),SEEK_CUR);
char buf[size];
//fseek(edit_tag_info->fp,-(size-1),SEEK_CUR);
//printf("%ld\n",ftell(edit_tag_info->fp));
	fread(buf,size-1,1,edit_tag_info->fp); //from 21 to 21 +size                                  
	buf[size-1]='\0';            
	printf("%s",buf);
	return p_success;
	
}
else{
fseek(edit_tag_info->fp,(size-1),SEEK_CUR);

return p_failure;
}
}



status edit(mp3_edit* edit_tag_info, char *argv[])
{
fseek(edit_tag_info->fp,10,SEEK_SET);

printf("\n-------	MP3 TAG READAER AND EDITOR FOR ID3V2.3----------\n");
char buf[5];
int i=0;
 if ((strncmp (argv [2], "-t", 2) == 0))
        {
			printf("new - title : ");
            strncpy (buf, "TIT2", 5);
           i=1;
        }
        else if ((strncmp (argv [2], "-A", 2) == 0))
        {
            strncpy (buf, "TPE1", 5);
	
			printf("new - Artist : ");
i=2;
        }
        else if ((strncmp (argv [2], "-a", 2) == 0))
        {
            strncpy (buf, "TALB", 5);
i=3;
printf("new - album : ");	
        }
        else if ((strncmp (argv [2], "-y", 2) == 0))
        {
            strncpy (buf, "TYER", 5);
	printf("new - year : ");	
i=4;
        }
        else if ((strncmp (argv [2], "-C", 2) == 0))
        {
            strncpy (buf, "TCON", 5);
i=5;
printf("new-content:");
        }
        else if ((strncmp (argv [2], "-c", 2) == 0))
        {
	printf("new -comment : ");	

            strncpy (buf, "COMM", 5);
i=6;
        }
        else
        {
            printf ("ERROR: Unsupported Modifier.\n");
            printf ("INFO: Modifier Functions:\n");
            printf ("-t\tModify Title Tag\n-A\tModify Artist Tag\n-a\tModify Album Tag\n-y\tModify Year Tag\n-G\tModify Content Type Tag\n-c\tModify Comments Tag\n");
            return p_failure;
        }

for(int k=1;k<=i;k++)
{
if(edit_view(edit_tag_info,buf,argv)==0)
{
printf("\n ------ edited----------- ");
}
}


return p_success;
}
