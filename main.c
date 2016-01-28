#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void Create();
void Load();
int Query(char Search[20]);
void Add();
void Delete();
void Modify();
void Print();
void Save();
void clean();
int valid(char num[]);
void sort();
void split(char string[100],char spliter);

typedef struct{
    char lastname[20];
    char firstname[20];
    char address[50];
    char city[20];
    char number[20];
}Contacts;

Contacts person[100];
int Counter=0;

int main()
{
    int run=1;char operation[7];
    printf("                        Welcome to the Phone-Book\n");
    // Choose option to start with
    while(run){
        printf("Choose to (1)Create a file or to (2)Load a file: ");
        scanf("%s",operation);
        if(strcmp(operation,"Create")==0||strcmp(operation,"create")==0||strcmp(operation,"1")==0){
            Create();
            break;
        }else if(strcmp(operation,"Load")==0||strcmp(operation,"load")==0||strcmp(operation,"2")==0){
            Load();
            break;
        }else{
            printf("Invalid Choice please reenter\n");
        }
    }
    //Give the User a list of operation he can use
    printf("Operations you can use:\n");
    printf("1.Load\n2.Query\n3.Add\n4.Delete\n5.Modify\n6.Print\n7.Save\n8.Quit\n");
    while(run){
        // Reading the operation used
        printf("Enter Operation: ");
        scanf("%s",operation);
        if(strcmp(operation,"Load")==0||strcmp(operation,"load")==0||strcmp(operation,"1")==0){
            printf("\n");
            Load();
            printf("\n");
        }else if(strcmp(operation,"Query")==0||strcmp(operation,"query")==0||strcmp(operation,"2")==0){
            printf("\n");
            char Search[20];
            printf("Enter The Last Name: ");
            scanf("%s",Search);
            Query(Search);
            printf("\n");
        }else if(strcmp(operation,"Add")==0||strcmp(operation,"add")==0||strcmp(operation,"3")==0){
            printf("\n");
            Add();
            printf("\n");
        }else if(strcmp(operation,"Delete")==0||strcmp(operation,"delete")==0||strcmp(operation,"4")==0){
            printf("\n");
            Delete();
            printf("\n");
        }else if(strcmp(operation,"Modify")==0||strcmp(operation,"modify")==0||strcmp(operation,"5")==0){
            printf("\n");
            Modify();
            printf("\n");
        }else if(strcmp(operation,"Print")==0||strcmp(operation,"print")==0||strcmp(operation,"6")==0){
            printf("\n");
            Print();
            printf("\n");
        }else if(strcmp(operation,"Save")==0||strcmp(operation,"save")==0||strcmp(operation,"7")==0){
            printf("\n");
            Save();
            printf("\n");
        }else if(strcmp(operation,"Quit")==0||strcmp(operation,"quit")==0||strcmp(operation,"8")==0){
            printf("\n");
            while(run){
                char Checker[5];
                printf("Do you want to Save before you quit ?!\n     1.Yes   2.No   ..");
                scanf("%s",Checker);
                if(strcmp(Checker,"Yes")==0||strcmp(Checker,"yes")==0||strcmp(Checker,"1")==0){
                    Save();
                    break;
                }else if(strcmp(Checker,"No")==0||strcmp(Checker,"no")==0||strcmp(Checker,"2")==0){
                    break;
                }else{
                    printf("Answer is not valid\n\n");
                }
            }
            printf("\n                        Thanks for using the Phone-Book\n");
            printf("                        Made by: Ahmed Magdy Ibrahim\n");
            break;
        }else{
            printf("Invalid operation please reenter\n");
            printf("\n");
            continue;
        }
        // Screen Cleaner
        printf("Press any key to Continue\n");
        getch();
        system("cls");
        printf("                        Welcome to the Phone-Book\n");
        //Give the User a list of operation he can use
        printf("Operations you can use:\n");
        printf("1.Load\n2.Query\n3.Add\n4.Delete\n5.Modify\n6.Print\n7.Save\n8.Quit\n");
    }
    Sleep(1500);
    return 0;
}

void Create(){
    FILE *file;
    char filename[30];
    printf("Please Enter the Name of the File you want to Create(ex: data.txt): ");
    scanf("%s",filename);
    file=fopen(filename,"w");
    printf("                             File Created\n");
    fclose(file);
}

void Load(){
    // Loading File and Check for it's presences
    char filename[30];
    FILE *file;;
    do{
        printf("Please Enter the Name of the File you want to Load(ex: data.txt): ");
        scanf("%s",filename);
        if(fopen(filename,"r")== NULL){
         printf("File Not Found\n");
        }
    }while(fopen(filename,"r")== NULL);
    file=fopen(filename,"r");
    // Clean the Array of Struct
    clean();
    // Getting data to array of Struct
    Counter=0;
    char loader[100];
    while(fgets(loader,100,file)!=NULL){
        split(loader,',');
        Counter++;
    }
    fclose(file);
    printf("                        File Loaded Successfully\n");
}

int Query(char Search[20]){
    // Search for Contacts and check for their presence
    int i,founder=0;
    for(i=0;i<Counter;i++){
        if(strcmp(person[i].lastname,Search)==0){
            // Printing the data of the found contact
            printf("\nLast Name: %s\n",person[i].lastname);
            printf("First Name: %s\n",person[i].firstname);
            printf("Address: %s\n",person[i].address);
            printf("City: %s\n",person[i].city);
            printf("Number: %s\n",person[i].number);
            founder++;
        }
    }
    // In case there is no contact with that name
    if(founder==0){
        printf("There is no Contact with that Last Name\nor the first letter must be capital or small letter\n");
    }
    return founder;
}

void Add(){
    printf("Enter the Last Name: ");
    scanf("%s",person[Counter].lastname);
    printf("Enter the First Name: ");
    scanf("%s",person[Counter].firstname);
    printf("Enter the Address: ");
    gets(person[Counter].address); // must be add because the first gets does not work
    gets(person[Counter].address);
    printf("Enter the City: ");
    gets(person[Counter].city);
    printf("Enter the Number: ");
    scanf("%s",person[Counter].number);
    while(!valid(person[Counter].number)){
        printf("InValid Number\n");
        printf("Enter the Number: ");
        scanf("%s",person[Counter].number);
    }
    Counter++;
}

void Delete(){
    // Deleting a Contact
    char lastSearch[20],firstSearch[20];
    int founder=0,i;
    printf("Enter the Last Name: ");
    scanf("%s",lastSearch);
    for(i=0;i<Counter;i++){ // Search for that last name
        if(strcmp(person[i].lastname,lastSearch)==0){
            founder++;
        }
    }
    if(founder==0){ // In case there is no contact with that last name
        printf("There is no Contact with that Last Name\nor the first letter must be capital or small letter\n");
    }else{
        founder=0;
        printf("Enter the First Name: ");
        scanf("%s",firstSearch);
        for(i=0;i<Counter;i++){
            if(strcmp(person[i].firstname,firstSearch)==0&&strcmp(person[i].lastname,lastSearch)==0){
                // Contact found and deleted
                *person[i].lastname='\0';
                *person[i].firstname='\0';
                *person[i].address='\0';
                *person[i].city='\0';
                *person[i].number='\0';
                founder++;
            }
        }
        if(founder==0){ // In case there is no contact with that first name
            printf("There is no Contact with that First Name\nor the first letter must be capital or small letter\n");
        }
    }
}

void Modify(){
    char Search[20];
    printf("Enter The Last Name: ");
    scanf("%s",Search);
    int founder,i;
    founder=Query(Search);//<==
    if(founder==0){
        return;
    }else if(founder>1){
        char firstSearch[20];
        printf("\nChoose on of the Contacts by the First Name: ");
        scanf("%s",firstSearch);
        for(i=0;i<Counter;i++){
            if(strcmp(person[i].firstname,firstSearch)==0&&strcmp(person[i].lastname,Search)==0){
                printf("\nEdit the Last Name: ");
                scanf("%s",person[i].lastname);
                printf("Edit the First Name: ");
                scanf("%s",person[i].firstname);
                printf("Edit the Address: ");
                gets(person[Counter].address); // must be add because the first gets does not work
                gets(person[i].address);
                printf("Edit the City: ");
                gets(person[i].city);
                printf("Edit the Number: ");
                scanf("%s",person[i].number);
                while(!valid(person[i].number)){
                    printf("InValid Number\n");
                    printf("Enter the Number: ");
                    scanf("%s",person[i].number);
                }
            }
        }
    }else{
        for(i=0;i<Counter;i++){
            if(strcmp(person[i].lastname,Search)==0){
                printf("Edit the Last Name: ");
                scanf("%s",person[i].lastname);
                printf("Edit the First Name: ");
                scanf("%s",person[i].firstname);
                printf("Edit the Address: ");
                gets(person[Counter].address); // must be add because the first gets does not work
                gets(person[i].address);
                printf("Edit the City: ");
                gets(person[i].city);
                printf("Edit the Number: ");
                scanf("%s",person[i].number);
                while(!valid(person[i].number)){
                    printf("InValid Number\n");
                    printf("Enter the Number: ");
                    scanf("%s",person[i].number);
                }
            }
        }
    }
}

void Print(){
    // Sorting
    sort();
    int i;
    //Printing
    for(i=0;i<Counter;i++){
        if(*person[i].lastname!='\0'){
            printf("\nLast Name: %s\n",person[i].lastname);
            printf("First Name: %s\n",person[i].firstname);
            printf("Address: %s\n",person[i].address);
            printf("City: %s\n",person[i].city);
            printf("Number: %s\n",person[i].number);
        }
    }

}

void Save(){
    FILE *file;
    char filename[30];
    int i;
    printf("Enter the name of the file you want to Save in(ex: data.txt): ");
    scanf("%s",filename);
    file=fopen(filename,"w");
    for(i=0;i<Counter;i++){
        if(*person[i].lastname!='\0'){
            fprintf(file,"%s,%s,%s,%s,%s\n",person[i].lastname,person[i].firstname,person[i].address,person[i].city,person[i].number);
        }
    }
    fclose(file);
    printf("                        File Saved Successfully\n");
}

void clean(){
    int i;
    // All Contacts deleted
    for(i=0;i<100;i++){
        *person[i].lastname=0;
        *person[i].firstname=0;
        *person[i].address=0;
        *person[i].city=0;
        *person[i].number=0;
    }
}

int valid(char num[]){
    int i;
    for(i=0;i<strlen(num);i++){
        if(num[i]<48||num[i]>57){
            return 0;
        }
    }
    return 1;
}

void sort(){
    Contacts temp;
    int i,j;
    for(i=0;i<Counter;i++){
        for(j=i+1;j<Counter;j++){
            if(strcmp(person[i].lastname,person[j].lastname)>0){
                temp=person[i];
                person[i]=person[j];
                person[j]=temp;
            }else if(strcmp(person[i].lastname,person[j].lastname)==0){
                if(strcmp(person[i].firstname,person[j].firstname)>0){
                    temp=person[i];
                    person[i]=person[j];
                    person[j]=temp;
                }else if(strcmp(person[i].firstname,person[j].firstname)==0){
                    if(strcmp(person[i].number,person[j].number)>0){
                        temp=person[i];
                        person[i]=person[j];
                        person[j]=temp;
                    }
                }
            }
        }
    }

}

void split(char string[100],char spliter){
    int i,j,flag=1;
    for(i=0,j=0;string[i]!='\0';i++,j++){
        switch(flag){
        case 1:// splitting the last name
            if(string[i]!=spliter){
                person[Counter].lastname[j]=string[i];
            }else{
                person[Counter].lastname[j]='\0';
                j=-1;
                flag++;
            }
            break;
        case 2:// splitting the first name
            if(string[i]!=spliter){
                person[Counter].firstname[j]=string[i];
            }else{
                person[Counter].firstname[j]='\0';
                j=-1;
                flag++;
            }
            break;
        case 3:// splitting the address
            if(string[i]!=spliter){
                person[Counter].address[j]=string[i];
            }else{
                person[Counter].address[j]='\0';
                j=-1;
                flag++;
            }
            break;
        case 4:// splitting the city
            if(string[i]!=spliter){
                person[Counter].city[j]=string[i];
            }else{
                person[Counter].city[j]='\0';
                j=-1;
                flag++;
            }
            break;
        case 5:// splitting the number
            if(string[i]!=spliter&&string[i]!='\n'){
                person[Counter].number[j]=string[i];
            }else{
                person[Counter].number[j]='\0';
                j=-1;
                flag++;
            }
            break;
        }
    }
}
