
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void menu(){
    /*PLEASE READE ME !! = IN THE MENU , EVEN THOUGH IT LOOKS LIKE INSANELY LONG , I AM JUST PRINF THINGS  , GETTING INFO FROM THE USER AND CALLING THE FUNCTION. */
    /*THUS , THERE IS NOTHING TO EXPLAIN LITERALLY.I HOPE IT IS NOT  A PROBLEM BUT IT IS JUST PRINTF AND SCANF COODES.I USED SWITCH CASE FOR THE MENU .*/
    printf("Welcome to my library system !-_-\n");
    printf("-----------------------------\n");
    int Id,type,choice,publication_year,sort_choice,search_choice,filter_choice;
    int flag =1;
    int n =0;
    char isbn_number[20],name[50],title[50],author[50],feature[50],value[50],filter[50],name_book[50];
      book *head = NULL;
      student *stu_head =NULL;
      stu_head = read_student_file(stu_head);
      head = read_book_file(&n,head);
    while(flag){
        printf("\nPlease choose what do you want\n");
        printf("1->Display the borrowed books\n");         printf("-----------------------------\n");
        printf("2->Add book\n");                           printf("-----------------------------\n");
        printf("3-Delete book\n");                         printf("-----------------------------\n");
        printf("4->Update book\n");                        printf("-----------------------------\n");
        printf("5->Filter and Sort books\n");              printf("-----------------------------\n");
        printf("6->Reverse book\n");                       printf("-----------------------------\n");
        printf("7->Search Books\n");                       printf("-----------------------------\n");
        printf("8->Borrow and return books\n");            printf("-----------------------------\n");
        printf("9->See the library\n");                    printf("-----------------------------\n");
        printf("10->Exit\n");                              printf("-----------------------------\n>>");
        scanf("%d",&choice);
    switch(choice){
        case 1 : 
        printf("Please enter the student ID you want to see the borrowed books : ");
        scanf("%d",&Id);
        display_borrowed_books(stu_head,Id);
        break;
        
        case 2 :
        printf("Please enter the ISBN number : ");
        scanf(" %[^\n]",isbn_number);
        printf("\nPlease enter the title : ");
        scanf(" %[^\n]",title);
        printf("\nPlease enter the author : ");
        scanf(" %[^\n]",author);
        printf("\nPlease enter the publication year : ");
        scanf("%d",&publication_year);
        while(publication_year<0 || publication_year>2023){
        printf("Enter a valid publication year ( 0 - 2023 ) : ");
        scanf("%d",&publication_year);
        }
        if(n != 0 ){
        printf("\nPlease enter the type adding. 0 for FIFO , 1 for LIFO :");
        scanf("%d",&type);
        }
        else {
            printf("For the first added book , you do not need to choose adding type.\n");
        }
    
        if(n == 0 ){
           head = add_book(head,isbn_number,title,author,publication_year,"Available",1);
            n++;
        }
       else  head = add_book(head,isbn_number,title,author,publication_year,"Available",type);
          update_book_txt(head);
          n++;
          break;
      
        case 3 :
        printf("Please enter the ISBN number you want to delete\n");
        scanf(" %[^\n]",isbn_number);
        n--;
         head = delete_books(head,isbn_number);
            update_book_txt(head);
          break;

        case 4 : 
        printf("Please enter the ISBN number you want to update : ");
        scanf(" %[^\n]",isbn_number);
        while(!is_valid_isbn(head,isbn_number)){
            printf("The book which has %s ISBN number was not found in the library\n",isbn_number);
            printf("Please enter a valid  ISBN number you want to update : ");
            scanf(" %[^\n]",isbn_number);
        }
        printf("Please enter the feature you want to update title , author or publication_year : ");
        scanf(" %[^\n]",feature);
        while(strcmp(feature,"isbn_number")==0){
            printf("\nYou cannot update the ISBN number !\n");
            printf("Enter a valid feature you want to update ,( title , author or publication_year) : ");
            scanf(" %[^\n]",feature);
        }
        while(strcmp(feature,"title")!=0 && strcmp(feature,"author")!=0 && strcmp(feature,"publication_year")!=0){
            printf("\nYou entered invalid feature !\n");
            printf("Enter a valid feature you want to update ,( title , author or publication_year) : ");
            scanf(" %[^\n]",feature);
        }
        printf("Please enter the new value of the %s feature : ",feature);
        scanf(" %[^\n]",value);
       
        head = update_books(head,isbn_number,feature,value);
        update_book_txt(head);
         break;
       
        case 5 : 
        printf("Please choose the filter type you want");
        printf("\n0->Filter by author\n");
        printf("1->Filter by publication year\n");
        scanf("%d",&filter_choice); 
        while(filter_choice <0 || filter_choice >1){
            printf("invalid filter choice\n");
            printf("Please choose a valid filter type you want");
            printf("\n0->Filter by author\n");
            printf("1->Filter by publication year\n");
            scanf("%d",&filter_choice);
        }
        if(filter_choice == 0) printf("Please enter the author you want to filter : ");
        else if(filter_choice == 1) printf("Please enter the publication year you want to filter : ");
        scanf(" %[^\n]",filter);
        printf("Please choose the sort type you want");
        printf("\n0->Sort by title\n");
        printf("1->Sort by author\n");
        printf("2->Sort by publication year\n");
        scanf("%d",&sort_choice);
        while(sort_choice < 0 || sort_choice >2){
            printf("invalid sort choice\n");
            printf("Please choose a valid sort type you want");
            printf("\n0->Sort by title\n");
            printf("1->Sort by author\n");
            printf("2->Sort by publication year\n");
            scanf("%d",&sort_choice);
        }
        head = filter_and_sort_books(head,filter_choice,filter,sort_choice);
        break;

        case 6 : 
         head = make_reverse(head,NULL); 
         update_book_txt(head);
          break;

        case 7 :
        printf("Please choose search type \n");
        printf("0->by ISBN Number\n");
        printf("1->by Author\n");
        printf("2->by Title\n");
        scanf("%d",&search_choice);
        while(search_choice <0 || search_choice >2){
            printf("invalid search choice\n");
            printf("Please choose a valid search type \n");
            printf("0->by ISBN Number\n");
            printf("1->by Author\n");
            printf("2->by Title\n");
            scanf("%d",&search_choice);
        }
         if(search_choice== 0) printf("Please enter the ISBN number you want to search : ");
        else if(search_choice== 1) printf("Please enter the author you want to search : ");
        else if(search_choice== 2) printf("Please enter the title you want to search : ");
        scanf(" %[^\n]",feature);
         searchbooks(search_choice,feature,head);
          break;
       
        case 8 : 
        printf("Please choose what do you want\n");
        printf("1-> Borrow Books\n");
        printf("2-> Return Books\n") ;
        scanf("%d",&choice);
        if(choice ==1 ){
            char existed_name[50];
            printf("Please enter the ISBN number you want to borrow : ");
            scanf(" %[^\n]",isbn_number);
            find_name_book(head,isbn_number,name_book);
            if(borrow_books(head,isbn_number) != 0 ){
            printf("Please enter the student ID : ");
            scanf("%d",&Id);
            if(is_valid_id(stu_head,Id,name,existed_name) == 0){
                 printf("This ID is already exist with %s name. No need to enter name again. \n",existed_name);
                 strcpy(name,existed_name);
            }
           else { printf("Please enter the student name : ");
            scanf(" %[^\n]",name);
           }     
            stu_head = add_student(stu_head,Id,name,name_book);
          
            }
        }
        else if(choice==2){
            printf("Please enter the ISBN number you want to return : ");
            scanf(" %[^\n]",isbn_number);
            find_name_book(head,isbn_number,name_book);
            stu_head = delete_student(stu_head,name_book);
            return_books(head,isbn_number);
        }
        else {
            printf("invalid choice\n");
        }
        update_student_txt(stu_head);
        update_book_txt(head);
        break;
       
        case 9 : print_books(head); break;

        case 10 : free(head); free(stu_head); flag = 0; break;

        default : printf("invalid choice\n");
    }
    }
}

student *add_student(student *head ,int stu_id , char *name , char *borrowed_books){
   if(head == NULL){ //If linked list empty , it opens a head .
    student *temp = (student*)malloc(sizeof(student)); /*Opening a new memory for the new added list.*/
    temp->stu_id = stu_id; /*Assigning the values to the new list.*/
    strcpy(temp->name,name);
    strcpy(temp->borrowed_books,borrowed_books);
    temp->next = head;
    head = temp; /*This if creates the head.After the first list , This if condition wont be used.*/
    return head;
   }

   else { /*Else , it adds to end of the linked list. (FIFO)*/
         student *temp = head;
         while(temp->next != NULL) temp = temp->next; /*Until I reach to end of linked list , I continue to go*/
         student *new_student = (student*)malloc(sizeof(student)); /*I create a new student with dynamic array.*/
         new_student->stu_id = stu_id;  /*I assign the values to the new student.*/
         strcpy(new_student->name,name);
         strcpy(new_student->borrowed_books,borrowed_books);
         new_student->next = NULL; 
         temp->next = new_student; /*The tails is assigned to new tail.*/
            printf("The student is added successfully\n");
         return head;
   }
}

student *delete_student(student *head ,char *name_book){ /*After I foound the name of the book by using ISBN number , I delete it by using this name.*/
 student *temp = head; 
 student *prev = NULL; /*I create a prev pointer to delete the node.*/
    if(head == NULL){ /*If the linked list is empty , it prints the warning.*/
            printf("The student list is empty!\n");
            return head;
        }

 if(strcmp(temp->borrowed_books,name_book) == 0 ){ /*If we are deleting the first node(head)*/
     temp  = head;
     head = temp->next;
        free(temp);
        printf("The student is deleted successfully\n");    
        return head;
 }

 while(temp !=NULL && strcmp(temp->borrowed_books,name_book)!=0){ /*If we are deleting the other nodes.*/
     prev = temp; /*I CANNOT LOSE THE PREVIOUS LIST BEFORE THE DEKETEDE INE*/
     temp = temp->next;
 }
if(temp == NULL){ /*After the while , if temps in null means there is no such a student because my while continues until found the name book*/
    printf("The student was not found in the student list!\n");
    return head;
}
else {
    prev->next = temp->next; /*Else , if there , we delete*/
    free(temp);
     printf("The student  is deleted successfully\n");
    return head;
}
}
 int is_exist_student(student *head , int Id){ 
        student *temp = head;
        while(temp !=NULL){
            if(temp->stu_id == Id) return 1; /*If there is a student Id which was taken by a student , it returns 1.*/
            temp = temp->next;
        }
        return 0; /*Else , it returns 0.*/
    }

void display_borrowed_books(student *head,int Id){
    student*temp = head;
    if(temp == NULL){
        printf("The student list is empty!\n");
        return;
    } 
    if(!is_exist_student(head,Id)){ /*If there is no student Id which was taken by a student , it prints the warning.*/
        printf("The student who has %d Id not found in the student list!\n",Id);
        return;
    }

    printf("The borrowed books who has  %d Id student: \n", Id); /*Else , it prints the borrowed books.*/
    while(temp !=NULL){
        if(temp->stu_id == Id){
            printf("->%s\n",temp->borrowed_books);
        }
        temp = temp->next;
    }
    
}

void update_student_txt(student *head){
    student *temp = head;
  FILE *tmp = fopen("temp.txt","w"); /*I create a temp file to update the students.txt*/
    while(temp !=NULL){
         fprintf(tmp,"%s,%s,%d\n",temp->borrowed_books,temp->name,temp->stu_id);       /*I print all of the student list.*/   
        temp = temp->next;
    }
    fclose(tmp);
    remove("students.txt"); /*I remove the students.txt*/
    rename("temp.txt","students.txt"); /*I rename the temp.txt to students.txt*/
}

int is_valid_id(student *head , int id,char *name,char *existed_name){
    student  *temp = head;
    while(temp != NULL){
        if(temp->stu_id == id && strcmp(temp->name,name) !=0) {
              strcpy(existed_name,temp->name);
              return 0; /* That id is exist but user tries to add different name from the existed one name It prints an error.*/

        }
        temp = temp->next;
    }
    return 1;
}

student *read_student_file(student *stu_head ){
    int Id;
    char name[50],borrowed_book[50];
 FILE *std = fopen("students.txt","r");
    if(std == NULL){ /*If the file is not found , it prints the warning.*/
        printf("The students.txt is not found\n");
        return NULL;
    }
    while(!feof(std)){ /*If the file is empty , it returns NULL.*/
        fscanf(std,"%[^,],%[^,\n],%d\n",borrowed_book,name,&Id); /*I read the file by using fscanf and with regex.*/
        stu_head = add_student(stu_head,Id,name,borrowed_book); /*I add the students to linked list.*/
    }
    return stu_head; /*I return the head of the linked list.*/
  fclose(std);
}


book * add_book(book *head ,char *isbn_number,char *title , char *author , int publication_year,char *status,int type){
/*It is the same logic as add student*/
  if(type == 1){ // LIFO
             book *new_book = (book*)malloc(sizeof(book)); /*I create a new book.*/
                new_book->publication_year = publication_year;
                strcpy(new_book->author,author);
                strcpy(new_book->isbn_number,isbn_number);
                strcpy(new_book->title,title);
                strcpy(new_book->borrowed_status,status);
                new_book->next = head;  /*I assign the head to new book because I am using last in first out technic.*/
                head = new_book; /*I assign the new book to head.*/
                return head; /*I return the head.*/
      }

  else if(type==0){ // FIFO 
             book *temp = head;
             while(temp ->next != NULL)     temp = temp->next; /*Until I reach to end of linked list , I continue to go*/
             book *new_book = (book*)malloc(sizeof(book)); /*I create a new book with dynamic array.*/
             new_book->publication_year = publication_year;
             strcpy(new_book->author,author);
             strcpy(new_book->isbn_number,isbn_number);
             strcpy(new_book->title,title);
             strcpy(new_book->borrowed_status,status);
             new_book->next = NULL; /*I assign the new book to NULL because I am using first in first out technic.*/
             temp->next = new_book; /*I assign the new book to end of the linked list.*/
             return head;

       }
else {
    printf("invalid type\n"); /*If the type is not 0 or 1 , it prints the warning.*/
    return head;
}

}   

book *read_book_file(int *n , book * head){ /*I read the books.txt file by using fscanf and with regex.*/
   
    char isbn_number[20],title[50],author[50],borrowed_status[50];
    int publication_year;

     FILE *Book = fopen("books.txt","r");
       if(Book == NULL){
           printf("The books.txt is not found\n");
           return NULL;
       }
     while(!feof(Book)){ 
         fscanf(Book,"%[^,],%[^,],%[^,],%d,%s\n",isbn_number,title,author,&publication_year,borrowed_status); /*I read the file by using fscanf and with regex.*/
         if(*n == 0 )  head = add_book(head,isbn_number,title,author,publication_year,borrowed_status,1); /*For the first reading , I must add LIFO .*/
         else  head = add_book(head,isbn_number,title,author,publication_year,borrowed_status,0); /*But the other one , I should add the end(FIFO)*/
         (*n)++;
     }
    fclose(Book);
 return head;
}  

int is_possible_delete(book *head , char *isbn_number){
    book *temp = head; /*The borrowed status book cannot deleted.*/
    while(temp !=NULL){
        if(strcmp(temp->isbn_number,isbn_number)==0 && strcmp(temp->borrowed_status,"Borrowed")==0) return 0; /*If the book is borrowed , it returns 0 because it cannot be deleted..*/
        temp = temp->next;
    }
    return 1; /*Else , it returns 1.*/
}

book *delete_books(book *head , char *isbn_number){ /*I delete the books by using ISBN number.*/
book *temp = head; 
book *prev = NULL;

 if(temp == NULL){
        printf("The linked list is empty!\n"); /*If the link is empty , give error print.*/
        return head;
     }
 if(!is_possible_delete(head,isbn_number)){ /*If book is not deletable , then given a warning.*/
    printf("%s ISBN Number book was borrowed before.You cannot delete it before returning !",isbn_number); return head; }

 if(strcmp(temp->isbn_number,isbn_number)==0){ /*If the book is first node , I delete it.*/
    temp = head; 
    head = temp->next;
    free(temp);
    return head;
 }
while(temp != NULL && strcmp(temp->isbn_number,isbn_number)!=0){ /*If the book is not first node , I delete it by using while loop.*/
    prev = temp;
    temp = temp->next;
}
if(temp == NULL){
    printf("The book is not found in this linked list!\n");
    return head; /*If the book is not found , I give a warning.*/
}
else {
    prev->next = temp->next; 
    free(temp); /*Else , I delete it.*/
    return head;
}
}

int is_valid_isbn(book *head , char *isbn_number){
    book *temp = head;
    while(temp !=NULL){
        if(strcmp(temp->isbn_number,isbn_number)==0) return 1; /*If the book is exist , it returns 0.*/
        temp = temp->next;
    }
    return 0; /*Else , it returns 1.*/
}

book *update_books(book *head , char *isbn_number,char *feature , char *value){
book *temp = head;

if(temp == NULL){
        printf("The library list is empty!\n");
    return head;
}

while( temp != NULL && strcmp(temp->isbn_number,isbn_number)!=0){
    
    temp = temp->next;
}
if(temp == NULL){
    printf("The book which has %s isbn number was not found in this linked list!\n",isbn_number);
    return head;
}
else { /*I update the book by using strcmp and strcpy.*/
    if(strcmp(feature,"publication_year") == 0)  temp->publication_year = atoi(value);
    else if(strcmp(feature,"title") == 0) strcpy(temp->title,value);
    else if(strcmp(feature,"author") == 0) strcpy(temp->author,value);
    else if(strcmp(feature,"isbn_number") == 0) strcpy(temp->isbn_number,value);
     printf("The book is updated successfully\n");
    return head;
}


}
book *filter_and_sort_books(book *head , int filter_choice , char *filter , int sort_choice){
    printf("\nThe filtered library by %s and sorted by %s: \n",filter,sort_choice==0 ? "title" : sort_choice==1 ? "author" : "publication year");
int flag =1;
book *temp = head;

    if(head ==NULL){
            printf("The library list is empty!\n");
            return head;
    }
if(filter_choice>1 || filter_choice <0){ /*Check if it is valid choice.*/
    printf("invalid filter choice\n");
    return head;
}
if(filter_choice == 0 ){ /*If the filter choice is 0 , I filter by author.*/
    if(sort_choice == 0 ){ /*If the sort choice is 0 , I sort by title.*/
         for(int j = 65 ; j<=122 ; j++){ /*These are the ASCII values of alphabetic chars.I use this to sort the all of the filtered linked list.*/
            temp = head;
            while(temp !=NULL){
                if(temp->title[0] == j  && strcmp(temp->author,filter) == 0){
         printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
            printf("*********************\n");
              temp = temp->next;
                        flag =0; /*If the book is found , I assign the flag to 0.*/
                }
                  else temp = temp->next; /*Else , I continue to go.*/
            }
         }
    }
    else if(sort_choice == 1){ /*The same logic.After I use forl loop to sort the filtered list by author , Then I assing flag 0.*/
         for(int j = 65 ; j<=122 ; j++){
            temp = head;
            while(temp !=NULL){  
                if(temp->author[0] == j  && strcmp(temp->author,filter) == 0){
        printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
          printf("*********************\n");
                        temp = temp->next;
                        flag =0;
                }
                  else temp = temp->next;
            }
         }
    }

   else if(sort_choice == 2){
        for(int j =  0; j<=2023; j++){ /*In this part , I am using the years to sort the books.There is an error message if the year is less than 0 or more than 2023*/
            temp = head;
            while(temp !=NULL){
                 if(temp->publication_year == j && strcmp(temp->author,filter) == 0){
                  flag =0;
             printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
             temp = temp->next;
            printf("*********************\n");

            }
            else temp = temp->next; 
        }

        }
    }


}
else if(filter_choice == 1 ){ /*This is the same as above.Only difference is I filter it by publication year.*/

       if(sort_choice == 0 ){
         for(int j = 65 ; j<=122 ; j++){   /*Sorting by title by using alpahetic ascii values of characters.*/
            temp = head;
            while(temp !=NULL){
                if(temp->title[0] == j  && temp->publication_year == atoi(filter)){
                    printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
              printf("*********************\n");

                        temp = temp->next;
                        flag =0;
                }
                  else temp = temp->next;
            }
         }
    }
    
    else if(sort_choice == 1){
         for(int j = 65 ; j<=122 ; j++){ /*Sorting by author by using for loop*/
            temp = head;
            while(temp !=NULL){
                if(temp->author[0] == j  && temp->publication_year == atoi(filter)){
                printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
                        temp = temp->next;
                        flag =0;
                }
                  else temp = temp->next;
            }
         }
    }

else if(sort_choice == 2){
   temp = head;
   while(temp !=NULL){
         if(temp->publication_year == atoi(filter)){ /*there is no sort for this choice because I have alread filtered the same publication year :d*/
              flag =0;
              printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
              temp = temp->next;
              printf("*********************\n");
    }
          else temp = temp->next;
      }
    }

}
     if(flag == 1 ) printf("\nWarning ! The book was not found in filtered as %s!\n",filter);

if(filter_choice != 0 && filter_choice !=1) printf("\n\ninvalid filter choice\n"); /*If the filter choice is not 0 or 1 , it prints the warning.*/

return head;
}

void searchbooks(int search_choice , char *search_value , book *head){
    int flag =0;
book *temp = head;
if(head ==NULL){
            printf("The library list is empty!\n");
            return;
    }

if(search_choice>3 || search_choice <0){
    printf("invalid search choice\n");
    
} 
printf("\nThe library which is searched by %s : \n",search_value);
while(temp != NULL){
if(search_choice== 0){ /*If search choice = 0 , means the user searched by ISBN NUMBER.SO I CHECK IF THERE IS A ISBN NUMBER*/
    if(strcmp(temp->isbn_number,search_value)==0){
        flag =1; /*If there is , I assign the flag to 1 IT WILL CONTROL MY WARNING MESSAGE.*/
     printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);

        temp = temp->next;
        printf("*********************\n");
       
    }
    else temp = temp->next; /*Else , I continue to go.*/
}
else if(search_choice == 1){
    if(strcmp(temp->author,search_value)==0){ /*If search choice = 1 , means the user searched by AUTHOR.SO I CHECK IF THERE IS A AUTHOR*/
        flag =1;
      printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);

        temp = temp->next;
        printf("*********************\n");
    }
    else temp = temp->next; /*Else , I continue to go.*/
}

 else if(search_choice == 2){ /*If search choice = 2 , means the user searched by TITLE.SO I CHECK IF THERE IS A TITLE*/
    if(strcmp(temp->title,search_value)==0){
        flag =1;
  printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s \n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);

        temp = temp->next;
        printf("*********************\n");
      
    }
    else temp = temp->next;
 }
}
  if(flag == 0 ) printf("\nWarning ! The book was not found in library!\n"); /*If the flag is 0 , means there is no such a book in the library.*/
}
             /*Every logic is same */
void print_books(book *head){ /*In this part , I am just printing the linked list until it is null with while.*/
book *temp = head;
if(temp == NULL){
    printf("The library list is empty!\n");
    return;
}
while(temp !=NULL){ /*Print until it is null.*/
  printf("ISBN NUMBER :  %s , Title : %s , Author : %s , Publication Year : %d , Reserved Status : %s\n",temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status);
       printf("*********************\n");
     temp = temp->next;
}
}

book * make_reverse(book *head,book *reverse_head){ 
book *temp = head;
if(head == NULL){
    printf("The library list is empty!\n");
    return head;
}
while(temp != NULL){ /*In this part , I Am adding the existed list as LIFO logic.*/
    reverse_head = add_book(reverse_head,temp->isbn_number,temp->title,temp->author,temp->publication_year,temp->borrowed_status,1);
    temp = temp->next;
}
print_books(reverse_head); /*Also print it to terminal to inform the user.*/
return reverse_head; 
}

 int borrow_books(book *head , char *isbn_number){
    if(head == NULL){
        printf("The library list is empty!\n");
        return 0;
    }
    book *temp = head;
    while(temp !=NULL && strcmp(temp->isbn_number,isbn_number)!=0){

        temp = temp->next;
    }
    if(temp ==NULL){ /*After this while , there are two change,First one is temp is null means the isbn number was not found.*/
        printf("The book which has %s ISNB Number was not found in the library\n",isbn_number); return 0;
    }
    else { /*Else , make available to borrowed because user borrowed it*/
        if(strcmp(temp->borrowed_status,"Available")==0){
            strcpy(temp->borrowed_status,"Borrowed");
            return 1;
        }
        else { /*If borrwed status is not available , mean is it borrowed,Thus borrowed book cannot borrowed again.*/
            printf("The book is already borrowed.You cannot borrow !\n"); 
            return 0;
        }
    }

      
}

int return_books(book *head , char *isbn_number){ /*Same logic but this time ,  I should delete the user because he/she returned the bppl*/
       if(head == NULL){
        printf("The library list is empty!\n");
        return 0;
    }
    book *temp = head;
    while(temp !=NULL && strcmp(temp->isbn_number,isbn_number)!=0){ /*In this while , I am trying to find the isbn number user wrote,*/

        temp = temp->next;
    }
    if(temp ==NULL){ /*If it is null , Means there is no such isbn number*/
        printf("The book which has %s ISNB Number was not found in the library\n",isbn_number); return 0;
    }
    else {
        if(strcmp(temp->borrowed_status,"Borrowed")==0){ /*The book must be borrwed status to return*/
            strcpy(temp->borrowed_status,"Available");
            printf("The book status has changed  successfully\n");
            return 1;
        }
        else { /*Else , the book is available means cannot be returned.*/
            printf("\nThe book was not borrowed before.You cannot return to available book.\n"); 
            return 0;
        }
    }

    
}

void find_name_book(book *head , char *isbn_number , char *name){ /*Here , I am trying to find the name of book by using ISBN number which is written by user,*/
    book *temp = head;
    if(temp == NULL){
        return;
    }
    while(temp !=NULL && strcmp(temp->isbn_number,isbn_number)!=0){
        temp = temp->next;
    }
    if(temp == NULL){
        printf("The book was not found in the library\n");
        return;
    }
    else { /*If it is not null , then I copy the name of book.*/
        strcpy(name,temp->title);
    }

}

void update_book_txt(book *head){
    /*The main logic in this function is that  I print the all of the books to the temp txt , Then I change its name so that there is my updated txt file*/
    FILE *temp = fopen("temp.txt","w");
    book *temp2 = head;
    if(temp2 == NULL){
        printf("The library list is empty!\n");
        return;
    }
    while(temp2 !=NULL){
        fprintf(temp,"%s,%s,%s,%d,%s\n",temp2->isbn_number,temp2->title,temp2->author,temp2->publication_year,temp2->borrowed_status);
        temp2 = temp2->next;
    }
    fclose(temp);
    remove("books.txt");
    rename("temp.txt","books.txt");
}