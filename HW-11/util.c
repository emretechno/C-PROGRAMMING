#include "util.h"

f_tree* add_family(f_tree *root){
      char name_file[50];
    printf("Enter the name of the file : ");
    scanf(" %[^\n]",name_file);
    FILE *fp = fopen(name_file,"a+");
    if(fp == NULL){
        printf("Error in opening file\n");
        return root;
    }
    char name[20],name_father[20],name_mother[20];
    int age;
    printf("\nEnter the name of the person : ");   scanf(" %[^\n]",name);
    printf("\nEnter the age of the person : ");  scanf("%d",&age); 
    printf("\nEnter the name of the father : ");  scanf(" %[^\n]",name_father);
    printf("\nEnter the name of the mother : ");   scanf(" %[^\n]",name_mother);
    if(root ==NULL){
        root = (f_tree*)malloc(sizeof(f_tree));
        strcpy(root->name,name);
        root->age = age;
        root->mother = NULL;
        root->father = NULL;
        fprintf(fp,"Name : %s Age : %d Father : %s Mother :  %s\n",name,age,name_father,name_mother);
        fclose(fp);
        return root;
    }
    f_tree *temp = root;
    while(temp->father != NULL){
        temp = temp->father;
    }
    f_tree *new_node = (f_tree*)malloc(sizeof(f_tree));
    strcpy(new_node->name,name);
    new_node->age = age;
    new_node->mother = NULL;
    new_node->father = NULL;
    fprintf(fp,"Name : %s Age : %d Father : %s Mother :  %s\n",name,age,name_father,name_mother);
    fclose(fp);
    
        return root;
}

int is_exist(f_tree *root , char name[50]){
    f_tree *temp = root;
    while(temp != NULL){
        if(strcmp(temp->name,name) == 0){
            return 1;
        }
        temp = temp->father;
    }
    return 0;

}
void find_name(f_tree *root, char *name ,  char *name_father, char *name_mother){
    f_tree *temp = root;
    while(temp != NULL){
        if(strcmp(temp->name,name) == 0){
            strcpy(name_father,temp->father->name);
            strcpy(name_mother,temp->mother->name);
            return;
        }
        temp = temp->father;
    }
    return;
}

void print_nuclear_family(f_tree *root){
    char name[50];
    printf("Enter the name of the person : ");
    scanf(" %[^\n]",name);
    if(root == NULL){
        printf("No family tree exists\n");
        return;
    }
    f_tree *temp = root;
    while(temp != NULL){
        if(strcmp(temp->name,name) == 0){
            printf("Name : %s Age : %d Father : %s Mother :  %s\n",temp->name,temp->age,temp->father->name,temp->mother->name);
            return;
        }
        temp = temp->father;
    }
    printf("No such person exists\n");
    return;
}
f_tree* remove_family(f_tree *root){
    char name[50];
    printf("Enter the name of the person : ");
    scanf(" %[^\n]",name);
    if(root == NULL){
        printf("No family tree exists\n");
        return root;
    }
    if(strcmp(root->name,name) == 0){
        root = NULL;
        return root;
    }
    f_tree *temp = root;
    while(temp->father != NULL){
        if(strcmp(temp->father->name,name) == 0){
            temp->father = NULL;
            return root;
        }
        temp = temp->father;
    }
    printf("No such person exists\n");
    return root;
}
f_tree *add_person(f_tree *root){
    char name[50];
    printf("Enter the name of the person : ");
    scanf(" %[^\n]",name);
    if(root == NULL){
        printf("No family tree exists\n");
        return root;
    }
    if(strcmp(root->name,name) == 0){
        printf("This person already exists\n");
        return root;
    }
    f_tree *temp = root;
    while(temp != NULL){
        if(strcmp(temp->name,name) == 0){
            printf("This person already exists\n");
            return root;
        }
        temp = temp->father;
    }
    char name_father[50],name_mother[50];
    printf("Enter the name of the father : ");
    scanf(" %[^\n]",name_father);
    printf("Enter the name of the mother : ");
    scanf(" %[^\n]",name_mother);
    temp = root;
    while(temp != NULL){
        if(strcmp(temp->name,name_father) == 0){
            f_tree *new_node = (f_tree*)malloc(sizeof(f_tree));
            strcpy(new_node->name,name);
            new_node->age = 0;
            new_node->mother = NULL;
            new_node->father = temp;
            temp->mother = new_node;
            return root;
        }
        temp = temp->father;
    }
    printf("No such person exists\n");
    return root;
}
void search_relatives(f_tree *root,char name[50]){
    
    if(root == NULL){
        printf("No family tree exists\n");
        return;
    }
    if(strcmp(root->name,name) == 0){
        printf("Name : %s Age : %d Father : %s Mother :  %s\n",root->name,root->age,"NULL","NULL");
        return;
    }
    f_tree *temp = root;
    while(temp != NULL){
        if(strcmp(temp->name,name) == 0){
            printf("Name : %s Age : %d Father : %s Mother :  %s\n",temp->name,temp->age,temp->father->name,temp->mother->name);
            return;
        }
        temp = temp->father;
    }
    printf("No such person exists\n");
    return;
}
void print_family_tree(f_tree *root){
    if(root == NULL){
        return;
    }
    printf("Name : %s Age : %d Father : %s Mother :  %s\n",root->name,root->age,root->father->name,root->mother->name);
    print_family_tree(root->father);
}
void print_relatives(f_tree *root , char name[50]){
    if(root == NULL){
        return;
    }
    if(strcmp(root->name,name) == 0){
        printf("Name : %s Age : %d Father : %s Mother :  %s\n",root->name,root->age,root->father->name,root->mother->name);
        return;
    }
    print_relatives(root->father,name);
    print_relatives(root->mother,name); 

}
void save_family_tree(f_tree *root){
    char name_file[50];
    printf("Enter the name of the file : ");
    scanf(" %[^\n]",name_file);
    FILE *fp = fopen(name_file,"w");
    if(fp == NULL){
        printf("Error in opening file\n");
        return;
    }
    if(root == NULL){
        printf("No family tree exists\n");
        return;
    }
    f_tree *temp = root;
    while(temp != NULL){
        fprintf(fp,"Name : %s Age : %d Father : %s Mother :  %s\n",temp->name,temp->age,temp->father->name,temp->mother->name);
        temp = temp->father;
    }
    fclose(fp);
    printf("The family tree is saved in the file\n");
    return;
}
void remove_family_tree(char *filename){
    FILE *fp = fopen(filename,"r");
    if(fp ==NULL ) {
        printf("There is no such %s file\n",filename);
        return;
    }
     char name[50],f_name[50],m_name[50];
     int age ;
     fscanf(fp,"Name : %s Age : %d Father : %s Mother :  %s\n",name,&age,f_name,m_name);
     printf("%s and %s also will be deleted are u sure ?",f_name,m_name);
    char chioce;
    scanf(" %c",&chioce);
    if(chioce =='y' || chioce== 'Y'){
        if(remove(filename) == 0){
            printf("File deleted successfully\n");
        }
        else{
            printf("Error in deleting file\n");
        }
    }
    else {
        printf("You did not choose delete the file !");
    }

  
     fclose(fp);
}