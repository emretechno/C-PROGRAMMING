#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define filename "linkedlist.bin"
 /*DEFINING THE ESSENTIAL STRUCTS*/
typedef struct node {
    void *data;
    struct node *next;
}node; 
typedef struct { 
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;
typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
}Asset2;
typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
}Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
}Asset4;
void fillLinkedList(node **head);
void serialize_linked_list(node *head); 
void deserialize_linked_list(node **head);
void print_list(node *head);
void dealloc_list(node *head);

int main(){
    srand(time(NULL)); // I use srand function to generate random numbers.
    node* deconstucturedhead = NULL; /*This will be my head of deserialized linked list.*/
    node *head = NULL; /*This will be  my head of generated linked list..*/
    fillLinkedList(&head); /*I fill the linked list by using fillLinkedList function.*/
    serialize_linked_list(head); /*I serialize the linked list by using serialize_linked_list function.*/

    printf("------------------------------------THE LIST BEFORE SERIALIZATION------------------------------------\n\n");
    print_list(head); /*I print the linked list by using print_list function.*/

    deserialize_linked_list(&deconstucturedhead); /*Then I read the binary file by using fread.*/

    printf("------------------------------------THE LIST AFTER DESERIALIZATION------------------------------------\n\n");
    print_list(deconstucturedhead); /*I print the linked list by using print_list function.*/

    dealloc_list(head); /*Do not forget to deallocate the linked list.*/
    dealloc_list(deconstucturedhead); /*Do not forget to deallocate the linked list.*/

    return 0;
}


void fillLinkedList(node **head){
    int num_of_asset = rand()%11 +10; // 10-20 arası rastgele sayı üretir.
    int i;
    /*All of the codes in this for have same logic.Thus , there is no need to explain the all of the codes and I hope it is not a problem for this homework.*/
    printf("Total number of assets: %d\n",num_of_asset); /*I print the total number of assets.*/ 
    for(i = 0 ; i < num_of_asset ; i++){

        int choice = rand()%4 +1;
        
         if(choice == 1){
            Asset1 *asset1 = (Asset1*)malloc(sizeof(Asset1));  // I allocate memory for the asset1.
            strcpy(asset1->type,"Asset1");
            asset1->ivals[0] = rand()%100;
            asset1->svals[0] = (double) (rand() % 10000) / 100; // I assign random values to the asset1.
            node *newNode = (node*)malloc(sizeof(node)); // I allocate memory for the node.
            newNode->data = asset1;  
            newNode->next = *head; // I assign the node to the head.
            *head = newNode;
         }
         else if(choice ==2 ){

            Asset2 *asset2 = (Asset2*)malloc(sizeof(Asset2));
            strcpy(asset2->type,"Asset2");
            asset2 ->ivals[0] = rand()%100;
            asset2 ->ivals[1] = rand()%100;
            asset2 ->svals[0] = (double) (rand() % 10000) / 100;
            asset2 ->svals[1] = (double) (rand() % 10000) / 100;
            node *newNode2 = (node*)malloc(sizeof(node));
            newNode2->data = asset2;
            newNode2->next = *head;
            *head = newNode2;
            }
            else if(choice == 3){
            Asset3 * asset3 = (Asset3*)malloc(sizeof(Asset3));
            strcpy(asset3->type,"Asset3");
            strcpy(asset3->string1,"Burak");
            strcpy(asset3->string2,"Koca");
            node *newNode3 = (node*)malloc(sizeof(node));
            newNode3->data = asset3;
            newNode3->next = *head;
            *head = newNode3;
            }
            else if (choice == 4){
            Asset4 *asset4 = (Asset4*)malloc(sizeof(Asset4));
            strcpy(asset4->type,"Asset4");
            asset4->value1 = (double) (rand() % 10000) / 100;
            asset4->value2 = (float) (rand() % 10000) / 100;
            asset4->value3 = (double) (rand() % 10000) / 100;
            node *newNode4 = (node*)malloc(sizeof(node));
            newNode4->data = asset4;
            newNode4->next = *head;
            *head = newNode4;
            }
        
        }
    }

void serialize_linked_list(node *head){ 
    FILE *binaryFile = fopen(filename,"wb");
    if(binaryFile == NULL){
        printf("File could not be opened\n");
        exit(1);
    }
    node *temp = head; 
    int i =1;
      while(temp !=NULL){ /*I write the linked list to binary file by using fwrite.*/
        if(strcmp(((Asset1*)(temp->data))->type ,"Asset1") == 0 ) { /*I determine the type of asset by using strcmp function which is in string.h*/
            fwrite(((Asset1*)(temp->data))->type,sizeof(char),20,binaryFile);
            fwrite(((Asset1*)(temp->data))->ivals,sizeof(int),1,binaryFile);
            fwrite(((Asset1*)(temp->data))->svals,sizeof(double),1,binaryFile);
        }
        else if (strcmp(((Asset2*)(temp->data))->type, "Asset2") == 0 ){ /*Same logic with the above one.*/
            fwrite(((Asset2*)(temp->data))->type,sizeof(char),20,binaryFile);
            fwrite(((Asset2*)(temp->data))->ivals,sizeof(int),2,binaryFile);
            fwrite(((Asset2*)(temp->data))->svals,sizeof(double),2,binaryFile); 
        } 
        else if (strcmp(((Asset3*)(temp->data))->type, "Asset3") == 0 ){ /*Same logic with the above one.*/
            fwrite(((Asset3*)(temp->data))->type,sizeof(char),20,binaryFile);
            fwrite(((Asset3*)(temp->data))->string1,sizeof(char),50,binaryFile);
            fwrite(((Asset3*)(temp->data))->string2,sizeof(char),50,binaryFile);
        }
        else if (strcmp(((Asset4*)(temp->data))->type, "Asset4") == 0 ){ /*Same logic with the above one.*/
            fwrite(((Asset4*)(temp->data))->type,sizeof(char),20,binaryFile);
            fwrite(&((Asset4*)(temp->data))->value1,sizeof(double),1,binaryFile);
            fwrite(&((Asset4*)(temp->data))->value2,sizeof(float),1,binaryFile);
            fwrite(&((Asset4*)(temp->data))->value3,sizeof(double),1,binaryFile);
        }
        temp = temp->next;
        i++;
      }
    fclose(binaryFile); /*Closing the file is important.*/
}
void deserialize_linked_list(node **head){
    FILE *binary_file = fopen(filename,"rb");
    if(binary_file == NULL){
        printf("File could not be opened\n");
        exit(1);
    }
char type[20];
while(fread(type,sizeof(char),20,binary_file) != 0){ /*I read the binary file by using fread.Until my fscan value is 0 means there is nothing to read more , my loop is gonna run.*/
    node *newNode = malloc(sizeof(node));
    newNode->next = NULL;
    if(strcmp(type,"Asset1") == 0){ /*I determine the type of asset by using strcmp function which is in string.h*/
        Asset1 *asset1 = (Asset1*)malloc(sizeof(Asset1));
        strcpy(asset1->type,"Asset1");
        fread(asset1->ivals,sizeof(int),1,binary_file); /*Then I read the values in order.*/
        fread(asset1->svals,sizeof(double),1,binary_file);
        newNode->data = asset1; /*I assign the data to the node.*/
    } 
    else if(strcmp(type,"Asset2") == 0){ /*Same logic , After I determine the type of asset, then I read them in order.*/
        Asset2 *asset2 = (Asset2*)malloc(sizeof(Asset2));
        strcpy(asset2->type,"Asset2");
        fread(asset2->ivals,sizeof(int),2,binary_file);
        fread(asset2->svals,sizeof(double),2,binary_file);
        newNode->data = asset2;
    }
    else if(strcmp(type,"Asset3") == 0){
        Asset3 *asset3 = (Asset3*)malloc(sizeof(Asset3));
        strcpy(asset3->type,"Asset3");
        fread(asset3->string1,sizeof(char),50,binary_file);
        fread(asset3->string2,sizeof(char),50,binary_file);
        newNode->data = asset3;
    }
    else if(strcmp(type,"Asset4") == 0){
        Asset4 *asset4 = (Asset4*)malloc(sizeof(Asset4));
        strcpy(asset4->type,"Asset4");
        fread(&asset4->value1,sizeof(double),1,binary_file);
        fread(&asset4->value2,sizeof(float),1,binary_file);
        fread(&asset4->value3,sizeof(double),1,binary_file);
        newNode->data = asset4;
    }
    if(*head ==NULL){
        *head = newNode;
    }
    else{ /*I add the new node to the end of the linked list means FIFO.It is not important for this homeworks I guess because I could not see anything about adding type.*/
        node *temp = *head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }

}
  
    fclose(binary_file);
}
void print_list(node *head){
      node *temp = head;
      /*My loop is gonna run until the linked list finish.*/
      while(temp != NULL){ /*I print the linked list by using while loop.*/ 
        if(strcmp(((Asset1*)temp->data)->type,"Asset1") == 0)
            printf("Type : Asset1 ivals[0]: %d  svals[0]: %lf\n",((Asset1*)temp->data)->ivals[0],((Asset1*)temp->data)->svals[0]);
        
        else if(strcmp(((Asset2*)temp->data)->type,"Asset2") == 0)
            printf("Type : Asset2: svals[0]: %d  svals[1]: %d ivals[0] : %lf ivals[1] :  %lf\n",((Asset2*)temp->data)->ivals[0],((Asset2*)temp->data)->ivals[1],((Asset2*)temp->data)->svals[0],((Asset2*)temp->data)->svals[1]);
        
        else if(strcmp(((Asset3*)temp->data)->type,"Asset3") == 0)
            printf("Type : Asset3: string1: %s  string2: %s\n",((Asset3*)temp->data)->string1,((Asset3*)temp->data)->string2);
        
        else if(strcmp(((Asset4*)temp->data)->type,"Asset4") == 0)
            printf("Type : Asset4: value1:  %lf  value2:  %f value3: %lf\n",((Asset4*)temp->data)->value1,((Asset4*)temp->data)->value2,((Asset4*)temp->data)->value3);
        
        temp = temp->next; /*I assign the next node to the temp.*/
      }
}
void dealloc_list(node *head){
    /*Do not forget to deallocate the linked list.*/
    node *aux = NULL;
    node *temp =head;
    while(temp != NULL){
        aux = temp;
        temp = temp->next;
        free(aux);
    }
}

