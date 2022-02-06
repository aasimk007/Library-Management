#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

#define FILENAME "ProgrammingLabProject.bin"
#define FILEHEADERSIZE sizeof(sfileheader)

//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} date;

//file header
typedef struct
{
    int a;
} sfileheader;

//structure for book info
typedef struct
{
    int bookid;
    char book[50];
    char author[50];
    char studentname[50];
    char studentaddr[300];
    char issue[5];
    date issuedate;
} bookinfo;

//this function verifies that a file has been created or not
int filestatus(const char *path)
{
    //try to open file
    FILE *pl=fopen(path,"rb");
    int status;
    if(pl!=NULL)
    {
        status=1; //file exists
        fclose(pl); //close file
    }
    else
    {
        status=0; //file does not exist
    }
    return status;
}

//this function creates the file if it does not exist
void initial()
{
    FILE *pl=NULL;
    int status=0;
    status=filestatus(FILENAME);
    if(!status)
    {
        //create the file
        pl=fopen(FILENAME,"wb");
        fclose(pl);
    }
}

//this function opens the file and adds the book and its details
void addbook()
{
    bookinfo addbookinfo;
    FILE *pl=NULL;
    pl=fopen(FILENAME,"ab+");
    if(pl==NULL)
    {
        printf("\nFile is not opened\n");
        _exit(1);
    }
    printf("\nEnter the details\n");
    printf("Book ID Number = ");
    fflush(stdin);
    scanf("%d",&addbookinfo.bookid);
    printf("Book Name = ");
    fflush(stdin);
    scanf("%s",addbookinfo.book);
    printf("Author Name = ");
    fflush(stdin);
    scanf("%s",addbookinfo.author);
    printf("Details entered successfully\n\n");
    fwrite(&addbookinfo,sizeof(addbookinfo),1,pl);
    fclose(pl);
}

//this function opens the file and asks the user to enter the book name which he wants to search
void searchbooks()
{
    int found=0;
    char book[50];
    bookinfo addbookinfo;
    FILE *pl=NULL;
    pl=fopen(FILENAME,"rb");
    if(pl==NULL)
    {
        printf("\nFile is not opened\n");
        _exit(1);
    }
    printf("\nEnter the book name to search\n");
    scanf("%s",book);
    fgets(addbookinfo.book,50,stdin);
    while(fread(&addbookinfo,sizeof(addbookinfo),1,pl))
    {
        if(!strcmp(addbookinfo.book,book))
        {
            found=1;
            break;
        }
    }
    if(found)
    {
        printf("Book ID Number = %d\n",addbookinfo.bookid);
        printf("Book Name = %s\n",addbookinfo.book);
        printf("Book Author = %s\n",addbookinfo.author);
        if(addbookinfo.issue=='Yes')
        {
            printf("Issued = Yes\n");
        }
        else
        {
            printf("Issued = No\n");
        }
    }
    else
    {
        printf("No record found\n");
    }
    fclose(pl);
}

//this function opens the file and display all the stored books details
void viewbooks()
{
    int found=0;
    char book[50];
    bookinfo addbookinfo;
    FILE *pl=NULL;
    unsigned int countbook=1;
    pl=fopen(FILENAME,"rb");
    if(pl==NULL)
    {
        printf("\nFile is not opened\n");
        _exit(1);
    }
    while(fread(&addbookinfo,sizeof(addbookinfo),1,pl))
    {
        printf("%d\n",countbook);
        printf("Book ID Number = %d\n",addbookinfo.bookid);
        printf("Book Name = %s\n",addbookinfo.book);
        printf("Book Author = %s\n",addbookinfo.author);
        if(addbookinfo.issue=='Yes')
        {
            printf("Issued = Yes\n");
        }
        else
        {
            printf("Issued = No\n");
        }
        found=1;
        ++countbook;
    }
    fclose(pl);
    if(!found)
    {
        printf("No record found\n");
    }
}

//this function issues the book to a student
void issuebook()
{
    int bookissue=0;
    sfileheader fileheaderinfo;
    char book[50];
    bookinfo addbookinfo;
    FILE *pl=NULL;
    pl=fopen(FILENAME,"rb+");
    if(pl==NULL)
    {
        printf("\nFile is not opened\n");
        _exit(1);
    }
    printf("\nEnter book ID to issue\n");
    scanf("%d",&bookissue);
    while(fread(&addbookinfo,sizeof(addbookinfo),1,pl))
    {
        if(addbookinfo.bookid==bookissue)
        {
            printf("\nEnter the details\n");
            printf("Student Name = ");
            fflush(stdin);
            scanf("%s",addbookinfo.studentname);
            printf("Student Address = ");
            fflush(stdin);
            scanf("%s",addbookinfo.studentaddr);
            printf("Date (in format dd/mm/yyyy) = ");
            fflush(stdin);
            scanf("%d/%d/%d",&addbookinfo.issuedate.dd,&addbookinfo.issuedate.mm,&addbookinfo.issuedate.yyyy);
            printf("Issued (Enter 'Y') = ");
            fflush(stdin);
            scanf("%s",addbookinfo.issue);
            printf("Book issued\n\n");
            fwrite(&addbookinfo,sizeof(addbookinfo),1,pl);
        }
        else
        {
            printf("Record not found\n");
        }
    }
    fclose(pl);
}

//this function takes the issued book back
void takebook()
{
    int found=0;
    int takeback=0;
    sfileheader fileheaderinfo;
    char book[50];
    bookinfo addbookinfo;
    FILE *pl=NULL;
    pl=fopen(FILENAME,"ab+");
    if(pl==NULL)
    {
        printf("\nFile is not opened\n");
        _exit(1);
    }
    printf("\nEnter book ID to take back\n");
    scanf("%d",&takeback);
    while(fread(&addbookinfo,sizeof(addbookinfo),1,pl))
    {
        if(addbookinfo.bookid!=takeback)
        {
            fflush(stdin);
            strcpy(addbookinfo.studentname,"None");
            fflush(stdin);
            strcpy(addbookinfo.studentaddr,"None");
            fflush(stdin);
            addbookinfo.issue='No';
            fflush(stdin);
            addbookinfo.issuedate.dd=0;
            fflush(stdin);
            addbookinfo.issuedate.mm=0;
            fflush(stdin);
            addbookinfo.issuedate.yyyy=0;
            fwrite(&addbookinfo,sizeof(addbookinfo),1,pl);
        }
        else
        {
            found=1;
            printf("Record not found\n");
        }
    }
    fclose(pl);
}

//main function
int main()
{
    int select;
    initial();
    printf("Library management System Project\n\n");
    do
    {
        printf("Main Menu\n");
        printf("1. Add new book\n");
        printf("2. Search books\n");
        printf("3. View books\n");
        printf("4. Issue book\n");
        printf("5. Take issued book back\n");
        printf("6. Exit\n\n");
        printf("Enter your choice\n");
        scanf("%d",&select);
        switch(select)
        {
            case 1: addbook();
            break;
            case 2: searchbooks();
            break;
            case 3: viewbooks();
            break;
            case 4: issuebook();
            break;
            case 5: takebook();
            break;
            case 6: _exit(1);
            break;
            default: printf("Invalid choice. Please enter a valid choice");
        }
    }
    while(select!=0);
    return 0;
}