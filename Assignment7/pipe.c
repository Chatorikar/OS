#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

void main()
{
  FILE *file;
  char str[100] ,sentence[500] , FileContent[100]  , s[100];
  int fd1[2] , fd2[2];
  char ch;
  char Char_Str[2];
  FileContent[0] = '\0';


  printf("Enter File Name ");
  scanf("%s",&str);
  file = fopen(str , "w");

  if (file == NULL)
  {
    printf("\n\nFile Doesn't Exists ");
    return;
  }

  printf("\n\nEnter a Sentence :  ");
  scanf("%s",&sentence);


  fprintf(file,"%s",sentence);
  fclose(file);


  if (pipe(fd1)==-1)
   {
       fprintf(stderr, "Pipe Failed" );
       return 1;
   }
   if (pipe(fd2)==-1)
   {
       printf("\n Before Pipe 2");
       fprintf(stderr, "Pipe Failed" );
       return 1;
   }

   if(fork() > 0 )
   {
     close(fd1[0]);
     write(fd1[1] , str , strlen(str)+1);
     close(fd1[0]);
     wait(NULL);

     close(fd2[0]);

     read(fd2[0] , s , 100);
     printf("\n Parent Reading :  ");
     printf("%s" , s);

   }
   else{
     // Chile Process
     char FileName[500];

     close(fd1[1]);

     read(fd1[0] , FileName , 500);
     close(fd1[0]);

     printf("File to be Read :  %s" , FileName);

     file = fopen(FileName,"r");

     if (file == NULL)
     {
       printf("\n File Doesn't Exit : %s" , FileName);
     }
     else{

       while((ch = fgetc(file)) != EOF){
            Char_Str[0] = ch;
            Char_Str[1] = '\0';
            strcat(FileContent,Char_Str);
          }
       printf("\n\n\n FileContent are %s" ,FileContent );
       write(fd2[1] , Char_Str , 1);
       fclose(file);

       close(fd2[1]);

     }

   }

}
