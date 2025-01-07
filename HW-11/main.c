
#include "util.h"


int main(){
    f_tree *root = NULL;
    printf("Family Tree System Menu : \n");
    int flag =1;
    int choice;
    do{

printf("1->Add Family Tree \n");
printf("2->Remove Family Tree\n");
printf("3->Load Family Tree\n");
printf("0->Exit\n>>");
scanf("%d",&choice);
switch(choice){
 case 1 : 
 printf("1->Add node \n");
 printf("2->Save Family Tree\n");
 printf("0->Exit\n>>");
   int chc;
  scanf("%d",&chc);
    switch(chc){
        case 1 : 
        root = add_family(root);
        printf("Family Tree added successfully\n");
        break;
    
        case 2 : 
        printf("The family tree is saved in the file\n");
        break;

    
        case 0 : 
        
        break;
    }
 break;

 case 2 : 
   printf("Enter the filename you want to delete : ");
          char filename[50];

     scanf(" %[^\n]",filename);
     remove_family_tree(filename);
 break ; 

 case 3 : 
 printf("Listing family trees : \n");
 printf("Please select an operation \n");
 printf("1->Add new person\n");
 printf("2->Remove person\n");
 printf("3->Print a Person's nuclear family\n");
 printf("4->Search Relatives of given person\n");
 printf("5->Return the main menu\n>>");
 int ch;
 scanf("%d",&ch);
 switch(ch){
     case 1 : 
        root = add_person(root);
     break;

     case 2 : 
    
     break;

     case 3 : 
     print_nuclear_family(root);
     break;

     case 4 : 
        printf("Enter the name of the person : ");
        char given_name[50];
        scanf(" %[^\n]",given_name);
        printf("Please select type of relatives : \n");
        printf("1->Parents\n");
        printf("2->Spouse\n");
        printf("3->Children\n");
        printf("4->Grandparents\n");
        printf("5->Cousins\n>>");
        int chc; scanf("%d",&chc);
        if(chc == 1){
            printf("\nPrinting parents of %s : \n",given_name);
            
        }
        else if(chc == 2){
            printf("Printing spouse of %s : \n",given_name);
        }
        else if(chc == 3){
            printf("Printing children of %s : \n",given_name);
        }
        else if(chc == 4){
            printf("Printing grandparents of %s : \n",given_name);
        }
        else if(chc == 5){
            printf("Printing cousins of %s : \n",given_name);
        }
        else{
            printf("Invalid choice\n");
        }
        search_relatives(root,given_name);
     break;
     case 5 :
     break;
 }
 break;

 case 0 : 
 flag = 0;
 break;

}
    }while(flag);
    return 0 ;
}