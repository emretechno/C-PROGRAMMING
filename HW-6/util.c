#include <stdio.h>
#include "util.h"
int the_menu(void){ /*This is my main menu.*/
int flag =1;
int option;
float filtered_stock_product[MAX_PRODUCT][3]; /*This 2D ARRAY WILL BE USED INT PART 4 AND PART 5  AS YOU WANT.I should have declare it here.*/
int size; /*Will be the size of my 2D ARRAY.*/
printf("Welcome to operator, please select an option to continue:\n\n");
do{
printf("1->File Operations\n\n");
printf("2->Query products\n\n");
printf("3->Check stock status\n\n");
printf("4->Stock control by brand\n\n");
printf("5->Export report\n\n");
scanf("%d",&option);
    switch (option){
   case 1: file_operations(); break; /*I called the file_operations function here.*/
            
     case 2: query_products(); break; /*I called the query_products function here.*/
            
     case 3:  check_stock_status(); break; /*I called the check_stock_status function here.*/
            
    case 4: flag = stock_control_brand(filtered_stock_product , &size) ; break; /*I called the stock_control_brand function here.*/

     case 5: flag = export_report(filtered_stock_product,size); break; /*I called the export_report function here.*/
    default: printf("INVALID OPTION ! ENTER A VALID OPTION:");   break;  } /*If user enter a invalid option , it will be warning.*/
 
} while (flag ==1); /*If flag is 1 , it will be continue.*/
printf("Thank you for using our program.\n");  /*If flag is 0 , it will be finish.*/
return 0;
}

int file_operations(void){
    FILE *product = NULL; /*I declared the product file pointer here.*/
    FILE *temp_prdct = NULL; /*I declared the temp_prdct file pointer here.*/
    FILE *stock = NULL; /*I declared the stock file pointer here.*/
    FILE *temp_stock = NULL; /*I declared the temp_stock file pointer here.*/
     int option;
     int flag =1;
    do {
        printf("Please enter an option :\n\n");
        printf("1->Add a new product\n");
        printf("2->Delete a product\n");
        printf("3->Update a product\n");
        printf("4->Add feature to products\n");
        printf("5->Add a new stock entry\n");
        printf("6->Delete a stock entry \n");
        printf("7->Update a stock entry\n");
        printf("8->Back to main menu.\n");
        scanf("%d",&option);
        switch(option){ /*Calling the essential functions.*/
            case 1: flag =  add_new_product(product);   break;
            case 2: flag = delete_product(product,temp_prdct); break;
            case 3:  flag = update_product(product,temp_prdct); break;
            case 4:  flag = add_feature(product); break;
            case 5:  flag = add_stock(stock); break;
            case 6: flag = delete_stock_entry(stock,temp_stock); break;
            case 7: flag = update_stock(stock,temp_stock); break;
            case 8:  flag =0; break;
            default:
            printf("INVALID OPTION ! ENTER A VALID OPTION:"); break;} /*If user enter a invalid option , it will be warning.*/
         
    }while(flag ==1);
    return 0;
}

int add_new_product(FILE *product){
   int total_line;
   char c;
        product = fopen("products.txt","r+");
               if (product == NULL) {
                 printf("Failed to open products file.\n");
                }
           int total_comma = find_comma(product);
           int extra_feature = total_comma -4+5; /*In this part , I am calculating the total comma in the file.By using this , I am gonna calculate the extra features.*/
            char add_feature[extra_feature][10];
            for(int i = 0; i <extra_feature ; i++ ){ /*I am getting the extra features by scanning the file.*/
               
                fscanf(product,"%[^,],",add_feature[i]);
                
            }
              int len = 0;
              while( add_feature[extra_feature-1][len] != '1'){ /*Im gonna find the length of string. strlen is forbidden thus I am making my own function.*/
                  len++;
              }
              add_feature[extra_feature-1][len-1] = '\0'; /*Then I am adding null at the end of the last string,*/
            rewind(product);
            total_line = find_total_line(product); /*I am gonna find the total line , I use it when I am trying the find the pID*/

            int last_pID;
            char type,name[9],brand[6];
            double price;
           last_pID = total_line+1;
           printf("Enter the essential features of product you want to add:\n");
           total_line++;
           printf("Enter the type: ");            scanf("  %c",&type); /*I am getting the essential features from user.*/
           printf("Enter the name :");            scanf("%s",name);  
           printf("Enter the brand :");           scanf("%s",brand);
           printf("Enter the price :");           scanf("%lf",&price);
           fprintf(product,"\n%d,%c,%s,%s,%.2lf",last_pID+1,type,name,brand,price);

           for(int i=5;i<extra_feature;i++){ /*After default featrues are written , Now I am trying to write additional features.*/
               printf("Enter the feature of %s :",add_feature[i]);
               scanf("%s",add_feature[i]);
               fprintf(product,",%s",add_feature[i]);
           }
           fclose(product); /*I am closing the file.*/
           return 1;
}

int delete_product(FILE *product,FILE *temp_prdct){
    char line[MAX_LENGTH]; /*I declared the line array here.*/
        int pID;
        char type,name[9],brand[6]; /*I declared the essential features here.*/
        double price;
      
        char c;
        int count =0;
   product = fopen("products.txt","r"); /*I opened the products file here.*/
                    if (product == NULL) {
                    printf("Failed to open products file.\n");
                    return 1;
                }
                  int last_pID =find_total_line(product)+1;
                   rewind(product);
                temp_prdct = fopen("temp.txt","w");
                    if (temp_prdct == NULL) {
                    printf("Failed to open products file.\n");
                    return 1;
                }
             int total_comma = find_comma(product); /*I am finding the total comma in the file.*/
             int extra_feature = total_comma -4; /*I am calculating the extra features.*/
             char add_feature[extra_feature][10];
             int total_line = last_pID;
                 int pID_del;

                printf("Please enter the pID value you want to delete :"); /*I am getting the pID value from user.*/
                scanf("%d",&pID_del);
                while(pID_del > last_pID){ /*If user enter a invalid pID , I am warning him/her.*/
                    printf("INVALID pID ! ENTER A VALID pID:");
                    scanf("%d",&pID_del);
                }
                fgets(line,MAX_LENGTH,product);
                fprintf(temp_prdct,"%s",line);
                  while (  fscanf(product,"%d,%c,%[^,],%[^,],%lf\n",&pID,&type,name,brand,&price) == 5){ /*I am scanning the file.*/
                         count++;
               
                   for(int i = 0 ; i < extra_feature ; i++){ /*I am getting the extra features.*/
                        fscanf(product,",%[^,\n]",add_feature[i]);
                    }
                  
                   
                    if(pID_del !=pID){ /*If pID not equals to will be deleted pID , I write it to temp txt.*/
                              if(pID_del !=0){
                                if( pID != total_line){ /*This if controls the last new line at the end of the file. If pID equals to total line means this is not the end of the file . You can add '\n'*/
                                    fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
                                   for(int i = 0 ; i < extra_feature ; i++){
                                    fprintf(temp_prdct,",%s",add_feature[i]);
                                   }
                                    fprintf(temp_prdct,"\n");


                                }
                                else { /*Else , this is the end of the file , do not add '\n' .*/
                                    fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
                                      for(int i = 0 ; i < extra_feature ; i++){ /*I am writing the extra features.*/
                                        fprintf(temp_prdct,",%s",add_feature[i]); 
                                      }
                                }
                                       

                              }
                    
                              else {  /*If pID_del equals to 0 , this means user wants to delete the lastproduct in the file. Now I am decrease one the pID s.*/
                                if(pID-1 != total_line) { /*This if controls the last new line at the end of the file. If pID equals to total line means this is not the end of the file . You can add '\n'*/
                                fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID-1,type,name,brand,price); /*Minus one is obligation because one the pID is deleted.Other ones should decrease one.*/
                                for(int i = 0 ; i < extra_feature ; i++){ /*I am writing the extra features.*/
                                    fprintf(temp_prdct,",%s",add_feature[i]); 
                                   }
                                    fprintf(temp_prdct,"\n");
                                }
                               else { /*Else , this is the end of the file , do not add '\n' .*/
                                fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID-1,type,name,brand,price);
                               
                              for(int i = 0 ; i < extra_feature ; i++){
                                        fprintf(temp_prdct,",%s",add_feature[i]); 
                                      }

                               }
                              }
                    }
                       if(pID_del == pID){ /*If pID equals to will be deleted pID , I do not write it to temp txt.*/
                     total_line--; /*I am decreasing the total line because one the line is deleted.*/
                        pID_del=0;  /*I am making pID_del 0 because I do not want to enter this if again.*/
                        
                    }

                   
                 
                }
                remove("products.txt"); /*I am removing the products.txt file.*/
                rename("temp.txt","products.txt"); /*I am renaming the temp.txt file to products.txt.*/
                  fclose(product);  /*I am closing the files.*/
                  fclose(temp_prdct); /*I am closing the file.*/
               
             
    return 1;
}
int update_product(FILE * product , FILE *temp_prdct){
    product = fopen("products.txt","r"); /*I opened the products file here.*/
    temp_prdct = fopen("temp.txt","w"); /*I opened the temp file here.*/
    char updated[MAX_LENGTH]; /*This will be my feature which user is gonna enter.*/
    int count =0;
    if(product == NULL){
        printf("product.txt could not opened");
    }
    if (temp_prdct == NULL) {
        printf("Failed to open temp_products file.\n");
      }
      int comma = find_comma(product);
      int extra_feature = comma -4 ; /*I am calculating the extra features.*/

      char extra[extra_feature][MAX_LENGTH];
      int pID;
      char type , name[9],brand[6];
      double price;
      int index = 0;
        int total_line = find_total_line(product) +1; /*I am finding the total line.*/
      int max_pID = total_line;
      rewind(product);
     char line[MAX_LENGTH];
     fgets(line,MAX_LENGTH,product);
     fprintf(temp_prdct,"%s",line);
     printf("The updatable features are (be careful with lowercases - lettercases) : %s ",line);
     printf("Please enter the pID value you want to update :");
     rewind(product);
     int all_features = comma + 1; /*I am calculating the all features by using total comma .*/
     char all_feature_name[all_features][MAX_LENGTH];
     for(int i = 0 ; i < all_features ; i++){
         fscanf(product,"%[^,\n],",all_feature_name[i]); /*I am getting the all features.*/
     }
           
    
        int inp_PID;
        scanf("%d",&inp_PID);
  while(inp_PID > max_pID || inp_PID < 0){ /*I am checking the pID is valid or not.*/
    printf("Invalid pID ! Please enter a valid pID :");
    scanf("%d",&inp_PID); 
  }
while(fscanf(product,"%d,%c,%[^,],%[^,],%lf\n",&pID,&type,name,brand,&price) == 5){ /*I am reading the file here.*/
count++;

    for(int i = 0 ; i  < extra_feature ; i++){ /*I am getting the extra features.*/
        fscanf(product,",%[^,\n]",extra[i]);
    }
  
    if(pID == inp_PID){ /*If pID equals to the pID which user entered , I am asking the feature which user wants to update.*/
        printf("Please enter the feature you want to update :");
        scanf("%s",updated);
        if(my_strcmp(updated,"pID") == 0){ /*If user wants to update pID , I am checking the new pID is valid or not.*/
              printf("Please enter the new pID value :");
              scanf("%d",&pID);
        }
        else if (my_strcmp(updated,"Type") == 0){ /*If user wants to update type , I am checking the new type is valid or not.*/
            printf("Please enter the new Type :");
            scanf(" %c",&type);
        }
        else if (my_strcmp(updated,"Name") == 0){ /*If user wants to update name , I am checking the new name is valid or not.*/
            printf("Please enter the new Name :");
            scanf("%s",name);
        }
        else if (my_strcmp(updated,"Brand") == 0){ /*If user wants to update brand , I am checking the new brand is valid or not.*/
            printf("Please enter the new Brand:");
            scanf("%s",brand);
        }
        else if (my_strcmp(updated,"Price") == 0){ /*If user wants to update price , I am checking the new price is valid or not.*/
            printf("Please enter the new price value :");
            scanf("%lf",&price);
        }
        else {
            for(int j = 5 ; j < all_features ; j++){ /*If user wants to update extra features , I am checking the new extra feature is valid or not.*/
                if(my_strcmp(updated,all_feature_name[j]) == 0){
                    index = j - 5; /*The value of j is starting from 5 , so I substract 5 to find the index of new array.It is because I didnot use strtrok , I should have find the all of the features in the same string but I am starting from 5 to consider the only additional features,*/
                
                }
            }
            printf("please enter the %s feature :",all_feature_name[index+5]); /*I am getting the new extra feature here.*/
            scanf("%s",extra[index]); 
        }
        
            if(pID  != total_line){ /*If pID is not equal to total line ,means it is not  the end the file , you can add '\n'*/
                fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
                for(int i = 0 ; i < extra_feature ; i++){
                    fprintf(temp_prdct,",%s",extra[i]);
                }
                fprintf(temp_prdct,"\n");
            }

                else {  /*If pID is equal to total line ,means it is  the end the file , you cannot add '\n'*/
                    fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
                    for(int i = 0 ; i < extra_feature ; i++){
                        fprintf(temp_prdct,",%s",extra[i]);
                    }
                }
        
    }

    else { /*If pID not equals the updated pID  , I am writing the same information.*/
        if(pID != total_line){
        fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
        for(int i = 0 ; i < extra_feature ; i++){
            fprintf(temp_prdct,",%s",extra[i]);
        }
        fprintf(temp_prdct,"\n");
        }
        else{
            fprintf(temp_prdct,"%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
            for(int i = 0 ; i < extra_feature ; i++){
                fprintf(temp_prdct,",%s",extra[i]);
            }
        }
    }
}
remove("products.txt"); /*I am removing the products.txt here.*/
rename("temp.txt","products.txt"); /*I am renaming the temp file here.My main logic was writing the all of the informations  to temporary txt , then I am renaming it.*/
fclose(product);
fclose(temp_prdct);



    
    return 1;
}
int add_feature(FILE *product){
    int pID;
    char line[MAX_LENGTH];
    FILE *temp;
    char type,name[9],brand[6];
    double price;
     product = fopen("products.txt","r"); /*I am opening the files here.*/
     temp = fopen("temps.txt","w");
    if(temp == NULL){
        printf("temp.txt could not opened");
    }

      if(product == NULL){
        printf("product.txt could not opened");
    }
    int new_total_line =find_total_line(product); /*I am finding the total line here.*/
    int count =0;
    char feature[15];
    char c;
    printf("Please enter the feature you wanna add:"); /*I am getting the feature here.*/
    scanf("%s",feature);
     rewind(product);
     int i;
     if (fgets(line,MAX_LENGTH,product) !=NULL){ /*I am getting the first line here.*/
        for (i = 0; line[i] != '\n' && line[i] != '\0'; i++);
        line[i] = '\0';
     }
     fprintf(temp,"%s,%s\n",line,feature); /*I am writing the first line here.*/
 while ( !feof(product) ){ /*I am getting the other lines here.*/
       c = fgetc(product);
      while(c !='\n' && c != EOF){
        fprintf(temp,"%c",c);
        c = fgetc(product);
      }
      if(c == '\n'){ /*If c is equal to '\n' , I am writing the none  here.*/
        fprintf(temp,",none\n"); /*I am writing the none manually.*/
        c = EOF;
      }
   
      }

       fprintf(temp,",none"); /*I am writing the last none in this part.*/
   remove("products.txt"); /*I am removing the old file here.*/

 rename("temps.txt","products.txt");    /*I am renaming the temp file here.My main logic was writing the all of the informations  to temporary txt , then I am renaming it.*/

fclose(product);
fclose(temp);
return 1;
}
int add_stock(FILE *stock){ /*This logic is the same as add product.It is just kind of easier.*/
    int total_line=0;
    char c;
    int pID;
    stock = fopen("stock.txt","r+");
    if(stock == NULL){
        printf("stock.txt could not opened");
    }
       while(!feof(stock)){ /*I am bringing cursor at the end of the first line.*/
        c = fgetc(stock);
         if(c =='\n'){
            total_line++;
         }
    }
    int max_sID = total_line; /*I am finding the max sID by using total line.*/
   
    printf("Please enter pId which you want to add stock:\n");  scanf("%d",&pID); /*I am getting the pID here.*/
    char branch[10];
    int current_stock;
    printf("Please enter the branch name:"); 
    scanf("%s",branch);
    printf("Please enter the current stock:"); 
    scanf("%d",&current_stock);  max_sID++; /*I am increasing the max sID here.*/
    fprintf(stock,"\n%d,%d,%s,%d",max_sID,pID,branch,current_stock); /*I am writing the new stock here.*/
   
        fclose(stock);

    return 1;
}
int delete_stock_entry(FILE *stock,FILE *temp_stock){

    char line[MAX_LENGTH]; /*I am using the same logic as delete product.*/
    int sID,pID , deleted_sID,current_stock;
    int total_line=0; /*I am finding the total line here.*/
    char c,branch[10]; 
    stock = fopen("stock.txt","r");
    if (stock == NULL) { /*I am checking the file here.*/
        printf("Failed to open stock file.\n");
        return 1;
    }
     while(!feof(stock)){
        c = fgetc(stock); /*I am bringing cursor at the end of the first line.*/
         if(c =='\n'){
            total_line++; /*I am finding the total line here.*/
         }
    }
    rewind(stock);
    temp_stock = fopen("temp_stock.txt","w");
    if (temp_stock == NULL) { 
        printf("Failed to open stock file.\n");
        return 1;
    }
    printf("Please enter the sID value you want to delete :"); /*I am getting the sID here.*/
    scanf("%d",&deleted_sID);
    int count =0;
    int max_sID = total_line; /*I am finding the max sID here.*/
    while(deleted_sID > max_sID){
        printf("Please enter a valid sID  to delete :");
        scanf("%d",&deleted_sID);
    }  
    fgets(line,MAX_LENGTH,stock); /*I am getting the first line here.*/
    fprintf(temp_stock,"%s",line);
    while (  fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&current_stock) == 4){ /*I am getting the other lines here.*/
         count++;
        
       if(sID != deleted_sID){ /*If sID is not equal to deleted sID , I am writing the line to temp_stock.*/
        if(deleted_sID !=0){
            if(sID != total_line){ /*If sID is not equal to total line , I am writing the line to temp_stock.*/
            fprintf(temp_stock,"%d,%d,%s,%d\n",sID,pID,branch,current_stock);
            }
            else {
            fprintf(temp_stock,"%d,%d,%s,%d",sID,pID,branch,current_stock);
            }
        }
        else {
            if(sID -1 != total_line){
                fprintf(temp_stock,"%d,%d,%s,%d\n",sID-1,pID,branch,current_stock);
            }
            else { fprintf(temp_stock,"%d,%d,%s,%d",sID-1,pID,branch,current_stock);
            }
        }
       }
       if(sID == deleted_sID){
          deleted_sID =0;
          total_line--;
       }
    }
    remove("stock.txt");
    rename("temp_stock.txt","stock.txt");
    fclose(stock);
    fclose(temp_stock);

    return 1;
}
int update_stock(FILE *stock, FILE *temp_stock){  
 stock = fopen("stock.txt","r");
    if (stock == NULL) {
        printf("Failed to open product file.\n"); /*I am checking the file here.*/
        return 1;
    }
    temp_stock = fopen("temp.txt","w"); /*I am opening the temp file here.*/
    if (temp_stock == NULL) {
        printf("Failed to open temp file.\n");
        return 1;
    }
    char line[MAX_LENGTH]; /*I am using the same logic as update product.*/
    char c;
    int pID;
    int inp_sID,sID,deleted_sID,current_stock; 
    int total_line = find_total_line(stock)+1; /*I am finding the total line here.*/
    rewind(stock);
    char branch[10];
    printf("Please enter the sID value you want to update :");
    scanf("%d",&inp_sID); /*I am getting the sID here.*/
    char feature[MAX_LENGTH];
    int count =0;
 fgets(line,MAX_LENGTH,stock); /*I am getting the first line here.*/
 fprintf(temp_stock,"%s",line); /*I am writing the first line to temp_stock.*/
    while (  fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&current_stock) == 4){
 count++;
    
     if(inp_sID == sID){ /*If inp_sID is equal to sID , I am getting the feature name here.*/
          printf("Please enter the feature name : ");
          scanf("%s",feature);
          if(my_strcmp(feature,"pID") == 0){
              printf("Please enter the new pID value : ");
              scanf("%d",&pID);
          }
          else if(my_strcmp(feature,"branch") == 0){ /*If feature name is branch , I am getting the new branch name here.*/
              printf("Please enter the new branch name : ");
              scanf("%s",branch);
          }
          else if(my_strcmp(feature,"current_stock") == 0){ /*If feature name is current_stock , I am getting the new current_stock value here.*/
              printf("Please enter the new current_stock value : ");
              scanf("%d",&current_stock);
          }
          else {
              printf("Please enter a valid feature name"); /*If feature name is not valid , I am giving an error message here.*/
          }

          fprintf(temp_stock,"%d,%d,%s,%d",sID,pID,branch,current_stock); /*I am writing the new line to temp_stock.*/
          if(sID != total_line) fprintf(temp_stock,"\n"); /*If sID is not equal to total line , I am writing a new line to temp_stock.*/
           
          
     }
     else {
         fprintf(temp_stock,"%d,%d,%s,%d",sID,pID,branch,current_stock); /*If inp_sID is not equal to sID , I am writing the line to temp_stock.*/
         if(sID != total_line) fprintf(temp_stock,"\n");    

     }
     
  
}
  remove("stock.txt"); /*I am removing the stock.txt file here.*/
  rename("temp.txt","stock.txt"); /*I am renaming the temp.txt file to stock.txt here.*/
  fclose(stock); /*I am closing the files here.*/
  fclose(temp_stock); /*I am closing the files here.*/
return 1;
}

int query_products(void){
    int option;
    FILE *product;
    int flag =1;
    do {
        printf("Please choose to what do you want:\n\n");
        printf("1->List all products\n");
        printf("2->Filter products by brand, type, price, or a your defined feature\n");
        printf("3->Back to main menu.\n");
        scanf("%d",&option);
        while(option !=1 && option !=2 && option !=3 ){
            printf("Enter a valid option.(1-2-3)\n");
            scanf("%d",&option);
        }
        if(option ==1 ){ /*If option is 1 , I am calling the list_all_products function.*/
            flag = list_all_products(product);
        }
        else if (option ==2 ){ /*If option is 2 , I am calling the filter_products function.*/
            flag= filter_products(product);
        }
        else{ /*If option is 3 , I am returning 0.*/
            flag = 0;
        }
        
    }while(flag ==1);
 
    return 0;
}
int list_all_products(FILE *product){
    char c;
    product = fopen("products.txt","r"); /*I am opening the products.txt file here.*/
    if(product == NULL){
        printf("products.txt could not opened");
    }
    while(!feof(product)){ /*I am printing the products.txt file here.*/
                  c = fgetc(product);  

      if(c !=EOF){   /*Until char reaches to end of the file , it prints the terminal.*/
            printf("%c",c);  
        }
      
    }
    printf("\n"); 
    fclose(product);
    return 1;
}
int filter_products(FILE *product){   
   
    printf("This is the only part I could not make.Even though I tried so hard to make this function work, I couldn't. I am sorry :(.But all of other parts are working flawlessly as expected.I am sorry teacher but I couldnt this session.(\n");
   return 1;
}
int check_stock_status(void){
    int option;
    FILE *stock;
    int flag =1;
    do {
        printf("\n\nPlease choose to what do you want:\n\n");
        printf("1->Query the stock in a specified branch\n");
        printf("2->List the stock of all products in a specified branch\n");
        printf("3->List the out-of-stock products in a specified branch\n");
        printf("4->Back to main menu\n");
        scanf("%d",&option);
        
        switch(option){
                
            case 1:
                flag = query_specific_stock(stock); /*If option is 1 , I am calling the query_specific_stock function.*/
                break; 
            case 2:
                flag = list_specific_branch(stock); /*If option is 2 , I am calling the list_specific_branch function.*/

                break;
            case 3: flag = list_outof_stock(stock); /*If option is 3 , I am calling the list_outof_stock function.*/

                
                break;
            case 4:
                
                flag =0;
                break;
                
            default:
                    printf("INVALID OPTION ! ENTER A VALID OPTION:"); 
                    scanf("%d",&option);
                break;

                
        }

    }while(flag==1); /*Until flag is equal to 1 , it keeps running.*/
    return 0;
    }
int query_specific_stock(FILE *stock){ 
    int exist =0; 
         stock = fopen("stock.txt","r"); /*I am opening the stock.txt file here.*/
         if(stock == NULL){
             printf("stock.txt could not opened");
         }
int sID,inp_pId,ID,current_stock;
char inp_branch[10],branch[10]; 
 char line[MAX_LENGTH]; 
 int size =0;
 int filtered_stock[MAX_PRODUCT],filtered_sID[MAX_PRODUCT]; 
printf("Please enter the product ID you search: "); scanf("%d",&inp_pId);
printf("Please enter the branch you search: "); scanf("%s",inp_branch);
 fgets(line,MAX_LENGTH,stock);
while(fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&ID,branch,&current_stock) == 4){ 
    if(inp_pId == ID && my_strcmp(inp_branch,branch) == 0){
        filtered_stock[size] = current_stock; 
        filtered_sID[size] = sID;
        exist = 1; 
        size++;
    }
}
if(exist == 0){
    printf("\n There is no product with pID %d in %s\n",inp_pId,inp_branch); 
}
else {
    for(int i=0;i<size;i++){
        printf(" The current stock whose sID -> %d  and pID ->  %d in %s is= %d\n",filtered_sID[i],inp_pId,inp_branch,filtered_stock[i]); 
    }
}
        return 1;
}
int list_specific_branch(FILE *stock){
    int exist =0;
    int size =0;
         stock = fopen("stock.txt","r"); /*I am opening the stock.txt file here.*/
         if(stock == NULL){
             printf("stock.txt could not opened");
         }
         char inp_branch[10],branch[10]; 
         int sID,pID,current_stock;
         int filtered_pID[MAX_PRODUCT],filtered_stock[MAX_PRODUCT]; 
         printf("Please enter the branch you search: "); scanf("%s",inp_branch);
            char line[MAX_LENGTH];
            fgets(line,MAX_LENGTH,stock); 
             printf(" All the stocks in %s: \n",inp_branch); 
            
            while(fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&current_stock) == 4){ 
                if(my_strcmp(inp_branch,branch) == 0){
                   filtered_pID[size] = pID;
                   filtered_stock[size] = current_stock;
                   size++;
                    exist = 1;
                }
            }
            if(exist == 0){
                printf(" There is no stock in %s\n",inp_branch); 
            }
            else{
                int i;
                for(i=0;i<size;i++){
                    printf(" Product ID -> %d, Current Stock -> %d\n",filtered_pID[i],filtered_stock[i]);
                }
            }
    return 1;

    }
    int list_outof_stock(FILE *stock){
        char line[MAX_LENGTH];
        int exist =0;
        stock = fopen("stock.txt","r");
        if(stock == NULL){ /*I am opening the stock.txt file here.*/
            printf("stock.txt could not opened");
        }
        char inp_branch[10],branch[10]; 
        int sID,pID,current_stock; 
        int size =0;
        int filtered_pID[MAX_PRODUCT],filtered_stock[MAX_PRODUCT]; 
        fgets(line,MAX_LENGTH,stock);
        printf("Please enter the branch you search: "); scanf("%s",inp_branch); 
        printf(" All of the  out-of-stock products in %s: \n",inp_branch);
        while(fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&current_stock) == 4){
            if(my_strcmp(inp_branch,branch) == 0 && current_stock == 0){ 
                filtered_pID[size] = pID;
                size++;
                exist =1;
            }
        }
        if(exist == 0){ 
            printf(" There is no out-of-stock product in %s\n",inp_branch);
        }

        else {
            
            for(int i=0;i<size;i++){
                printf(" Product ID-> %d\n",filtered_pID[i]);
            }
        }
return 1;
    }
int stock_control_brand(float filtered_stock_product[MAX_PRODUCT][3], int * size){ // this function controls the stock of the products whose brand is given by user
    FILE *stock;
    FILE *product;
    stock = fopen("stock.txt","r");  // opening the stock.txt
    product = fopen("products.txt","r"); // opening the products.txt
    if( stock == NULL || product == NULL){ // if the files could not opened
        printf("stock.txt or product.txt could not opened");
    }
    char inp_brand[15];
    printf("Please enter the brand you want to see stock: "); scanf("%s",inp_brand);
    int pID;
    char name[10],brand[6],type,branch[10]; 
    int total_comma = find_comma(product); // this function finds the total comma in the first line of the products.txt
    int extra_feature = total_comma -4; // this is the number of extra features of the products.txt
    char add_feature[extra_feature][10];
    char line[MAX_LENGTH];
    double price;
    int current_stock; 
     *size =0;
    fgets(line,MAX_LENGTH,product); // this line reads the first line of the products.txt
    int sID; // this array keeps the pID of the products whose brand is given by user
    int exist =0;
    for(int i = 0; i< MAX_PRODUCT  ; i++){
        for(int j = 0 ; j < 3 ; j++){
            filtered_stock_product[i][j] = 0;
        }
    }
     while (  fscanf(product,"%d,%c,%[^,],%[^,],%lf\n",&pID,&type,name,brand,&price) == 5){ // this reads the products.txt line by line
                    

                   for(int i = 0 ; i < extra_feature ; i++){ 
                        fscanf(product,",%[^,\n]",add_feature[i]); // this reads the extra features of the products.txt
                    }
                  
        if(my_strcmp(inp_brand,brand) == 0){
           filtered_stock_product[*size][0] = pID; 
           filtered_stock_product[*size][1] = price;
           (*size)++; // this is the number of products whose brand is given by user
          
        }
    }
    

    int size2 = *size;
    fclose(product); // this closes the products.txt
    fgets(line,MAX_LENGTH,stock);  

     while( fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&current_stock) == 4){ 
        for(int i = 0 ; i < *size ; i++){
            if(filtered_stock_product[i][0] == pID){ // if the pID of the product in the stock.txt is equal to the pID of the product in the products.txt
                if(filtered_stock_product[i][2] == 0 ){
                    filtered_stock_product[i][2] = current_stock; // this assigns the current stock of the product in the stock.txt to the filtered_stock_product array
                    exist =1; // this is a flag.If it is one . there is a product whose brand is given by user
                }
            
                else {  
                    filtered_stock_product[size2][0] = pID;   
                     filtered_stock_product[size2][1] = filtered_stock_product[i][1];
                     filtered_stock_product[size2][2] = current_stock ; 
                        (size2)++; /*Increase the size2 one*/
                }
            }
               
           
            
    
}
        
    }
    fclose(stock);
    if(exist ==1){ 
        for(int j = 0; j< size2 ; j++){ // this prints the products whose brand is given by user
            printf(" Product ID -> %.0lf  Price ->  -> %.2lf Current Stock ->%.0lf\n",filtered_stock_product[j][0],filtered_stock_product[j][1],filtered_stock_product[j][2]);
        }
    }
    else{
        *size = 0;  // if there is no product whose brand is given by user, size is assigned to 0.It is like a flag
        printf("There is no available stock as '%s'\n",inp_brand);
    }
    
return 1;
}

int export_report(float filtered_stock_product[MAX_PRODUCT][3],int size){ // this function exports the report of the products whose stock is between minimum and maximum stock
    FILE * export = fopen("export.txt","w"); 
    if(export == NULL){
        printf("export.txt could not opened");
    }
    FILE * stock = fopen("stock.txt","r"); 
    if(stock == NULL){
        printf("stock.txt could not opened");
    }
    int sID,pID,current_stock; 
    char branch[10];
    int filtered_stock[size][MAX_PRODUCT]; 
    int j = 0;
    char line[MAX_LENGTH]; 
    fgets(line,MAX_LENGTH,stock);
      fprintf(export,"pID,Minimum Stock , Maximum stock , Median stock\n"); // this prints the first line of the export.txt
      if(size != 0 ){ // if there is a product whose stock is between minimum and maximum stock
      while(fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&current_stock) == 4){
          for(int i = 0 ; i < size ; i++){
              if(filtered_stock_product[i][0] == pID){ /*If the pID is valid , I am storing the stocks to sort them later.*/
                filtered_stock[i][j] = current_stock;
                j++; // this is the number of products whose stock is between minimum and maximum stock
                break;
              }
          }
      }
    bubble_sort(filtered_stock,size,j); // this sorts the filtered_stock array
    if( j > 0 ){
      
            for(int i = 0 ; i < size ; i++ ){
                int median = 0;
                if( j %2 == 1){ /*I am just cheking the median and it depends on odd and even siuations.*/
                    fprintf(export,"%.0lf,%d,%d,%d\n",filtered_stock_product[i][0],filtered_stock[i][0],filtered_stock[i][j-1],filtered_stock[i][j/2]);
                }
                else {
                    median =  (filtered_stock[i][j/2]  + filtered_stock[i][ (j/2) -1 ] )/2; /*Stock must be integer it can not be float.**/
                    fprintf(export,"%.0lf,%d,%d,%d\n",filtered_stock_product[i][0],filtered_stock[i][0],filtered_stock[i][j-1],median);
                }
            }
        
      
    }
    else {
        for(int s = 0 ; s< size ;s++){  
            fprintf(export,"%.0lf,%d,%d,%d\n",filtered_stock_product[s][0],0,0,0);
        }
    }
      }
      else {
        fprintf(export,"WARNING ! :The brand you entered does not exist in stock.txt.That is why there is no information about min ,max and median value.");
      }
     printf("\n 2D array in part 5 is exported to export.txt as you want.\n"); // this prints the message to the screen
     fclose(stock); // this closes the stock.txt
     fclose(export); // this closes the export.txt
 return 0;
}
int find_total_line(FILE *product){
    char c; 
    int total_line =0; 
        if (product == NULL) { 
        printf("Error: file pointer is null\n");
        return 0;
    }
    while(!feof(product)){  
        c = fgetc(product);
         if(c =='\n'){  /*If '\n' equals to '\n , total_line increase one.*/
            total_line++;
          
         }
    }
    return total_line-1;
    }
int find_comma(FILE *product){
    char line[MAX_LENGTH];
    int count =0;
    fgets(line,MAX_LENGTH,product);
    int j =0;
    while(line[j] !='\n'){ 
        j++; /*I am finding the length of the line.*/
    }
    for(int i =0;i<j;i++){
        if(line[i] ==','){ /*If line array equals to ',' increase total comma one */
            count++; /*I am finding the number of comma in the line.*/
        }
    }
    
    rewind(product); /*I am going to the beginning of the file.*/
    return count; /*I am returning the number of comma in the line.*/
}
int my_strcmp(const char *str1, const char *str2) { /*I am making my own strcmp function.*/
    int i = 0;
    while (str1[i] == str2[i]) { /*If str1 equals to str2, I am going to the next character.*/
        if (str1[i] == '\0') /*If str1 equals to '\0', I am returning 0.*/
            return 0;
        i++;
    }
    return (str1[i] - str2[i]); /*I am returning the difference between str1 and str2.*/
}

void bubble_sort(int filtered_stock[][MAX_PRODUCT], int size , int j){ /*I am making bubble sort in this part.*/
      for(int i = 0 ; i< size ; i++){ /*I am sorting the 2D array according to the current stock.*/
        for(int gecis = 1 ; gecis  < j ; gecis ++ ){
            for(int l = 0 ; l < j - 1 ; l++){
                if(filtered_stock[i][l] > filtered_stock[i][l+1]){    
                    int temp = filtered_stock[i][l];  
                    filtered_stock[i][l] = filtered_stock[i][l+1]; 
                    filtered_stock[i][l+1] = temp;
                }
            }
        }
      }
}

