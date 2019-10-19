#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>



struct student{
    int roll;
    char name[50];
    int age;
}s;

int menu()
{   
    int choice;

    printf("\n\n\n    1) Create File    ");                      
    printf("\n    2) Add    Record  ");                     
    printf("\n    3) Show   Record   ");                    
    printf("\n    4) Search Record  ");                     
    printf("\n    5) Update Record ");                      
    printf("\n    6) Delete Record ");
    printf("\n\n Enter your Choice : ");
    scanf("%d", &choice);

    return choice;
}


void Create(char filename[10])
{
    char buffer[50];
    
    if(access(filename , 0))
    {
        if( open(filename , O_WRONLY | O_CREAT | O_TRUNC  , 0777) == -1)
        { 
            printf("\n\n Please try Again\n\n");
           
        }
        else
        {
            printf("\n\n File Created ...\n\n\n ");
            snprintf(buffer , 50 , "ls -l | grep %s" , filename);
            system(buffer);
            printf("\n\n\n");
        }
        
    }
    else
    {
        printf("\n\n File is Exists \n\n\n Try another Name ");

        snprintf(buffer , 50 , "ls -l | grep %s" , filename);
        system(buffer);

    }
}


void Insert(char filename[50])
{
    struct student s1;
    int fd;

    fd = open(filename , O_WRONLY | O_APPEND);

    printf("\n\n Enter ID : ");
    scanf("%d" , &s1.roll);

    printf("\n\n Enter Name : ");
    scanf("%s" , s1.name);

    printf("\n\n Enter age : ");
    scanf("%d" , &s1.age);

    write(fd , &s1 , sizeof(s1));

    close(fd);

}

void Display(char fileaname[50])
{
    struct student s1;
    int flag = 0 , fd;
    if(!access(fileaname , 0))
        fd = open(fileaname , O_RDONLY );
    else
    {
        printf("\n\n File is not exits");
        return;
    }
    
    printf("\n\t\t\t Roll No \t Name \t\t Age" );
    while(read(fd , &s1 , sizeof(s1)))
    {
        printf("\n\t\t\t %d \t\t %s \t\t %d" , s1.roll , s1.name , s1.age);
        flag = 1;
    }
    if(!flag)
    {
        printf("\n\n Please Insert Record First");
    }
}

void Search(char filename[50])
{
    int roll , fd;
    struct student s1;
    printf("\n\n Enter Roll No  : ");
    scanf("%d" , &roll);

    fd = open(filename , O_RDONLY);
    printf("\n\t\t\t Roll No \t Name \t\t Age" );
    while(read(fd , &s1 , sizeof(s1)))
    {
        if(s1.roll == roll)
        {
             printf("\n\t\t\t %d \t\t %s \t\t %d" , s1.roll , s1.name , s1.age);
            return;
        }
    }
    printf("\n\n Record Not Found ");
}


void Update(char filename[50])
{
    int roll , fd;
    struct student s1;
    
    printf("\n\n Enter Roll No  : ");
    scanf("%d" , &roll);

    fd = open(filename , O_RDWR);
    printf("\n\t\t\t Roll No \t Name \t\t Age" );
    while(read(fd , &s1 , sizeof(s1)))
    {
        if(s1.roll == roll)
        {
            printf("\n\t\t\t %d \t\t %s \t\t %d" , s1.roll , s1.name , s1.age);
            printf("\n\n Enter Name : ");
            lseek(fd , -sizeof(s1) , SEEK_CUR);
            scanf("%s" , s1.name);
            write(fd , &s1 , sizeof(s1));
            printf("\n\n\n Data Updated .. ");
            return;
        }
    }
    printf("\n\n Record Not Found ");
}


void Delete(char filename[20])
{
    int roll , fd , flag = 0 , fd_temp;
    struct student s1;
    
    printf("\n\n Enter Roll No  : ");
    scanf("%d" , &roll);

    fd = open(filename , O_RDWR);
    fd_temp = open("temp.txt" , O_RDWR | O_CREAT | O_TRUNC);

    
    printf("\n\t\t\t Roll No \t Name \t\t Age" );
    
    while(read(fd , &s1 , sizeof(s1)))
    {
        if(s1.roll == roll)
        {
            printf("\n\t\t\t %d \t\t %s \t\t %d" , s1.roll , s1.name , s1.age);
            printf("\n\n Record Delete Sucessfully");
            flag = 1;
            
            //write(fd , &s1 , sizeof(s1));
           // read(fd , &s1 , sizeof(s1));
            //lseek(fd , -sizeof(s1) , SEEK_CUR);
            //write(fd , &s1 , sizeof(s1));
            continue;
        }
        write(fd , &s1 , sizeof(s1));
    }

    if(flag)
    {
        remove(filename);
        rename("temp.txt" , filename);
    }
    else
    {
        printf("\n\n Record Not FOund ");
        remove("temp.txt");
    }
    
}



int main()
{   
    char filename[10];
    char buffer[50];
    int flag = 0;
    while (1)
    {
        switch (menu())
        {
        case 1:
                printf("\n\n Enter File Name : ");
                scanf("%s" , filename);
                Create(filename);
                flag = 1;
                break;
        case 2:
                if(flag && strlen(filename) != 0)
                    Insert(filename);
                else
                {
                    printf("\n\n Enter File Name : ");
                    scanf("%s" , filename);
                    Create(filename);
                    Insert(filename);
                    flag = 1;
                }           
            break;
       
        case 3:
            
               if( flag  || strlen(filename) != 0) 
                    Display(filename);
                else
                {
                    printf("\n\n Enter File Name : ");
                    scanf("%s" , filename);
                    Display(filename);   
                }
                
                break;
        case 4: 

                if( flag  || strlen(filename) != 0) 
                    Search(filename);
                else
                {
                    printf("\n\n Enter File Name : ");
                    scanf("%s" , filename);
                    Search(filename);   
                }
              break;  
        
        case 5: 

                if( flag  || strlen(filename) != 0) 
                    Update(filename);
                else
                {
                    printf("\n\n Enter File Name : ");
                    scanf("%s" , filename);
                    Update(filename);   
                }
              break;  

        case 6: 

                if( flag  || strlen(filename) != 0) 
                    Delete(filename);
                else
                {
                    printf("\n\n Enter File Name : ");
                    scanf("%s" , filename);
                    Delete(filename);   
                }
              break;  

        
        default:
            break;
        }    

    }
    
}
