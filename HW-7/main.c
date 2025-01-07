
#include <stdio.h> /*Classic input output library.*/
#include <string.h> /*I used strcmpe in this library.*/
#include <math.h> /*I used sqrt in this library.*/

#define name_input "input.txt"  /*Defining the names of files.*/
#define name_ignore "ignore.txt"
#define name_dictionary "dictionary.txt"

#define threshold 6 /*Defining the threshold value.You may change if you want*/
#define MAX_WORD_SIZE 20  /*Defining the maximum word size.*/
#define MAX_WORD_COUNT 100  /*Defining the maximum word count.*/
#define MAX_INT 150000 /*Defining the maximum integer value.*/

int read_dict(const char * , char [][MAX_WORD_SIZE]);  /*Function prototypes are ready just as you want.*/
int read_text(const char * , const char * , char [][MAX_WORD_SIZE]);
int histogram(const char [][MAX_WORD_SIZE],const int [],int ,const char [][MAX_WORD_SIZE+5+20]);
int find_max(const int [] , int ); /*Finding maximum occurence to find the scale.*/
char* my_strcpy(char* dest, const char* src);
int is_alpha(char ); /*Checking the alpahabet chars.*/
void bubble_sort(char [][MAX_WORD_SIZE],int[] , int [] ,  int,char[][MAX_WORD_SIZE]);
double dissimilarity(char * , char * , char [][MAX_WORD_SIZE], float);
void print_hist(int  [] ,int [] ,  int , int , char [][MAX_WORD_SIZE] , char [][MAX_WORD_SIZE+5+20],char [][MAX_WORD_SIZE]);
int read_words(FILE *, char []);


int main(int argc, const char * argv[]) {

 char inp_words[MAX_WORD_COUNT][MAX_WORD_SIZE]; /*this is the words user's input.*/
  printf("Enter word(s) ");
  int index = 0;
 printf("Please  enter the words  and write '#' to finish the entry.For example -->(car bus #)\n");  /* as it was # */
 printf("Enter the words : ");
 while( scanf("%s",inp_words[index]) && inp_words[index][0] != '#'){ /*I am taking from user the words by increasing the index one.When user enters '#' the first char of the new string is gonna be "#' and my while is gonna stop."*/
   index++; /*In every word , increase index one.*/
 }
 int total_input = index; /*The total number of user's input.*/
  printf("The words you entered : ");
  for(int u = 0; u < index ; u++){ /* Printing the words user wrote.*/
    printf("%s ",inp_words[u]);
  }
  printf("\n\n");
  int frequencies[MAX_WORD_COUNT] = {0}; /*This is the frequencies of the words in input.txt.*/
    char dict[50001][MAX_WORD_SIZE]; /*This is the dictionary words.*/
    char hist[MAX_WORD_COUNT][MAX_WORD_SIZE+5+20]; /*This is the histogram.*/
    char words[MAX_INT][MAX_WORD_SIZE]; /*This is the words in input.txt.*/
    char new_words[MAX_WORD_COUNT][MAX_WORD_SIZE]; /*This is for the new most similar words. that are not found in dictionary.*/
    int word_flags[MAX_WORD_COUNT] = {0}; /*This is the flags for the words that are not found in dictionary.*/
    int total_dict_words = read_dict(name_dictionary, dict); /*This is the total number of words in dictionary.*/
    double distance; /*This is the distance between the words.*/
    char most_similar_word[MAX_WORD_SIZE]; /*This is the most similar word which I am gonna send it as argument.*/
    int txt_read_words = read_text(name_input, name_ignore, words);  /*This is the total number of words in input.txt.*/
   for(int u =  0 ; u < index ; u++){
    for(int j = 0 ; j < txt_read_words ; j++){
      if(strcmp(inp_words[u],words[j]) == 0){ /*I am just checking the input.txt words and user's word and if they are same , I am just incrasing the frequency of this words*/
        frequencies[u]++;
      }
    }
   }

    
   int total;
if(total_input == 1){ /*If the user entered just one word , I am gonna find the most similar word and print it.No need for histogram in this part.*/
    for(int u = 0 ; u < index ; u++){
      total=0;
      if(frequencies[u] >0)   printf("%s occured %d times\n",inp_words[u],frequencies[u]); /*I am printing the total number of words ocurrences in this printf.*/
    else if(  frequencies[u] == 0 ){ /*But if this word is zero, I must check the most similar word and I should count frequency of this similar word.*/
       distance = dissimilarity(inp_words[u],most_similar_word,dict,threshold); /*This is the distance of similar word and main word.*/
       if(distance != -1 && distance != -2 ) printf("Distance : %lf\n",distance);
       else printf("Distance : Not Found \n");
       
       for(int j = 0 ; j < txt_read_words ; j++){
        if(strcmp(most_similar_word,words[j]) == 0){ /*I am just checking the input.txt words and user's new most similar words and if they are same , I am just increasing the frequency of this words*/
          total++;
        }
       }
       frequencies[u] = total; /*New words frequency will be equal to total.*/
       if(total!= 0 )    printf("There is no ”%s” but ”%s” occured %d times \n",inp_words[u],most_similar_word,frequencies[u]); /*new word occured %d times.*/
       else {
        if(distance == -1 ){ /*new word is the most similiar word to user's word .But it also does not exist in input.txt*/
         printf("”%s” was not found in %s and %s.No Matches.\n",inp_words[u],name_input,name_dictionary);

       }
       else { /*If distance equals -1 mean the word also not exist in dictionary.txt*/
        printf("”%s” not found in %s and  most similar word ”%s” also not found %s No Matches!\n",inp_words[u],name_input,most_similar_word,name_input);
       }
       }
    }
    }
}
else {  /*If total input is more than 1 , means histogram will be used.*/
  for(int u = 0 ; u < index ; u++){
      total=0;
     if(  frequencies[u] == 0 ){ /*If the word does not exist in input.txt we must check it on dictionary,txt to find the most similar word*/
     
       distance = dissimilarity(inp_words[u],most_similar_word,dict,threshold); /*This is my distance calculator.*/
       my_strcpy(new_words[u],most_similar_word);
       if(distance != -1 && distance !=-2 ) printf("Distance : %lf\n",distance); /*If distance is -1  , it like flag and I understand that the word does not exit in dictionary.txt*/
       else printf("Distance : Not Found \n");
        if(distance != -1 && distance != -2 ) word_flags[u] = 1; /*This flag means the user's word change with new similar word.*/
       for(int j = 0 ; j < txt_read_words ; j++){
        if(strcmp(most_similar_word,words[j]) == 0){
          total++; /*Then calculate the new frequency of similar word.*/
        }
       }
       frequencies[u] = total; /*New words frequency will be equal to total.*/
      
    }
    }
      bubble_sort(inp_words,frequencies,word_flags,total_input,new_words); /*I am sorting the words by their frequencies.*/
      int scale = histogram(words,frequencies,total_input,hist); /*I am finding the scale of histogram.*/

      if(scale >1){ /*If scale is more than 1 , I am gonna print the scale.*/
        printf("Scale :%d\n",scale);
      }
    
       print_hist(frequencies,word_flags,total_input,scale,inp_words,hist,new_words); /*I am printing the histogram.*/

}
   
    return 0;
}
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){

FILE *dictionary= fopen(file_name, "r"); /*I am opening the dictionary.txt*/
 if(dictionary == NULL) {
    printf("Error: %s not found\n",name_dictionary); /*If there is no dictionary.txt , I am gonna print error message.*/
    return 1;
  }
  int num_word = 0 , vector_size =0;
   fscanf(dictionary,"num_word=%d, vector_size=%d",&num_word,&vector_size); /*Firstly , I am reading the vector size and num_word.*/
    if(num_word == 0 &&  vector_size == 0){ /*But in dictionary_exp.txt , it writes " num_words , but in dictionary.txt , it write "num_word".That is why I muss add a condition for this situation."*/
      rewind(dictionary);
         fscanf(dictionary,"num_words=%d, vector_size=%d",&num_word,&vector_size); /*If it is not num_word, then read num_words*/

    }

    float vectors[2000][vector_size]; /*Then I am creating vector array.*/
    int index = 0; /*will be my index of dictionary string.*/
    char c;
while( !feof(dictionary)){ /*Until the end of the file , */
int j = 0;
while(c != ' ' && c != EOF){ /*Until the first space  , I read the chars*/
if(is_alpha(c)){ /*They are alpahebetic , but I still want to add an condition to best result.*/
  dict[index][j] = c;
  j++;
}
  c = fgetc(dictionary); /*I am reading the chars.*/

}
dict[index][j] = '\0'; /*I am adding null at the end of the string.*/
if(c == ' '){ /*If there is a space , I am gonna pass it.*/
  while(c != '\n' && c !=EOF ){ /*Until the end of the line , I am gonna pass the chars.*/
    c = fgetc(dictionary);
  }

 c = fgetc(dictionary);
}
index++; /*Increase the index one.*/
}

dict[index][0] = '-';  dict[index][1] = '\0'; /*ADD '-' AT THE END OF THE DICTIONARY ARRAY*/
index++; /*Increase the index one.*/
fclose(dictionary); /*Close the file.*/

    return index;
}
int  read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]){
 FILE *text = fopen(text_file,"r");
    FILE *ignore = fopen(ignore_file,"r");
    if (text == NULL || ignore == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }
    char ignore_arr[20][50];
    int total_ignored = 0;
    int loop = 1;
    while (loop)
    { /* first part , I am counting the ignore words and storing them in array.*/
        switch(read_words(ignore,ignore_arr[total_ignored ]))
        { /*In read_words function , it returns some values and I am using them as flag.*/
            case -1:
                loop = 0; /*When returned -1 , en the loop.*/
                break;
            case -2:
                total_ignored ++; /*When returned -2 , increase the total ignore one.I am counting ignored words.*/
                loop = 0; /*End the loop.*/
                break;
            case 1:
                total_ignored ++; /*When returned 1 , increase the total ignore one.I am counting ignored words.*/
                break;
        }
    }
    loop = 1;
    int flag = 1;
    int size_word = 0;
    while (loop)
    {   /*In this part , I am reading the input.txt and I am storing the words array in this part*/
        switch(read_words(text,words[size_word]))
        {
            case -1:
                loop = 0; /*If case is -1 means it is end of the file.Then I am ending the while loop.*/
                break;
            case -2:
                size_word++; /*When returned -2 , increase the size_word one.I am counting words in this case.*/
                loop = 0;
                break;
            case 1:
                flag = 1;
                for (int i=0; i < total_ignored  ; i++)
                {
                    if (strcmp(ignore_arr[i],words[size_word]) == 0) /*If word  of input are same as ignored word , Then I turning flag 1.*/
                    {
                        flag = 0; /*If flag is 0 , means it is ignored word.*/
                        break;
                    }
                }
                if (flag) size_word++; /*If flag is 1, means it is not ignored words so I can increase size word one.*/
                break;
        }
    }
   
    fclose(text); /*Close the files.*/
    fclose(ignore); /*Close the files.*/
    words[size_word][0] = '-';  words[size_word][1] = '\0'; /*ADD '-' AT THE END OF THE WORDS ARRAY*/
    size_word++; /*Increase the index one because we add -  string.*/
    return size_word; /*Return the size of the words array.*/



}
int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[],int size_occ , const char hist[][MAX_WORD_SIZE+5+20]){
  int scale;
int max_occurence = find_max(occurrences,size_occ); /*After I find the max occurence in the array.I calculate the scale.*/
if( max_occurence > 20){ /*If the max occurence is more than 20 , I am gonna divide it to 20 to find the scale.*/ 
  scale = max_occurence / 20; /*I am dividing the max occurence to 20 to find the scale.*/
  if(max_occurence % 20 != 0 ) scale++; /*If max occurence is not divisible by 20 , I am gonna increase it one  yani tam sayiya yuvarliyorum aslinda.*/
}
else { /*SCALE IS ONE IF ANY OCUCRENCE IS LESS THAN 20.*/
  scale = 1;
}
for(int i = 0 ; i < size_occ ; i++){
  for(int l = 0 ; l < occurrences[i]/scale ; l++){
   // hist[i][l] = '*'; /*I am adding '*' to the histogram.*/ /*IFADE DEGISTIRILEBILIR OLMALIDIR !*/
   /*I mean I think I should assign this stars and plus symbols to char histogram but it is const char thus I cannot able to this.It gives an compiler error.*/
  }
}
/*Cause of const char , I cannot assign * to hist array my compiler gives error.*/
return scale; /*RETURN THE SCALE. AS YOU WANT*/
}



int find_max(const int occurences[] , int size){
  int max = occurences[0]; /*Firstly , every ocurrence will be zero then I am gonna count.*/
  for(int i = 1 ; i < size ; i++){
    if(occurences[i] > max){ /*If there is any greater than max.*/
      max = occurences[i]; /*It is the new max value,*/
    }
  }
  return max; /*Returning max to find the scale.*/
}


int is_alpha(char c){ /*I am just checking if my char is alphabetic or not.*/
 
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    else return 0;
}


double dissimilarity(char * w1, char *w2, char dict[][MAX_WORD_SIZE], float thresshold){

FILE *dictionary= fopen(name_dictionary, "r"); /*I am opening the dictionary.txt*/
  if(dictionary == NULL) {
      printf("Error: %s not found\n",name_dictionary); /*If there is no dictionary.txt , I am gonna print error message.*/
      return 1;
    }
    int num_word = 0 , vector_size =0; /*I am declaring the num_word and vector_size.*/
 char dictt[255]; /*I am declaring the dictt string to read the dictionary.txt.*/

    
     fscanf(dictionary,"num_word=%d, vector_size=%d",&num_word,&vector_size); /*Firstly , I am reading the vector size and num_word.*/
    if(num_word == 0 &&  vector_size == 0){
      rewind(dictionary);
         fscanf(dictionary,"num_words=%d, vector_size=%d",&num_word,&vector_size);  /*But in dictionary_exp.txt , it writes " num_words , but in dictionary.txt , it write "num_word".That is why I muss add a condition for this situation."*/
    }
        float vectors[2000][vector_size]; /*Then I am creating vector array.*/

int i =0;
int tot_vector = 0;
    while( fscanf(dictionary,"%s",dictt) == 1){ /*After I pass the string */
      tot_vector = 0;
  for(int  j = 0 ; j < vector_size ; j++){
    fscanf(dictionary,"%f",&vectors[i][j]); /*I am scanning the vector sizes and I am gonna use them later.*/
    tot_vector++; /*Increase the indexes.*/
  }


 
i++;
}
   int index1 = -1; /*Thil will be my flag index.*/
   double distance =0;
   for(int s = 0 ; s <= num_word ; s++){
    if(strcmp(w1,dict[s]) == 0){ /*When I find the word in dictionary.*/
      index1 = s;  /*I store index and use break because there is no need to look other words.*/
      break;
    }
   }
    if(index1 == -1){ /*If index is -1 ,  means the word does not exist in dictionary.txt.Thus I return -1 as distance and it will be my also distance flag.*/
      printf("WARNING!There is no ”%s” in %s\n",w1,name_dictionary); /*I am printing the warning message.*/
      return -1;
    }
   int last_index = -1;
   double min = 0;
   for(int j = 0 ; j < vector_size ; j++){ /*In this part ,I assume that the minimum distance between my words is 0th word.Then I am gonna calculate all of the other distances and I check if is there any less than this minumum value.*/
     min += pow(vectors[index1][j] - vectors[0][j],2); /*I am calculating the distance between the words.*/
   }
   min = sqrt(min); /*I am taking the square root of the distance.*/
   for(int index2 = 1 ; index2 <num_word ; index2++ ){
     distance = 0;
     for(int j = 0 ; j < vector_size ; j++){

        distance += pow(vectors[index1][j] - vectors[index2][j],2); /*Now I am calculating the every other words to find the less then above minimum value.*/
      
      }
     if(index2 != index1){ /*If indexes are same , distance will be 0 and  the most similar word will be itself.Thus I prevent this exception.*/
      distance = sqrt(distance); /*I am taking the square root of the distance.*/ 
      if(distance <=min  && distance <=thresshold){  /*Distance must be less than threshold.By means of equality symbol ,I choose the last equal word.You may change if you want*/
        min = distance; /*If new distance les than min , then it will be new minimum value.*/
        last_index = index2; /*I am storing the index of minumum word,*/
      }
     }
     
   }
   int k = 0;
   if( last_index == -1){
     printf("There is no similar word for this threshold value\n");
      return -2;
      /*If last index is -1 , means there is no similar word.*/
   }
   while(dict[last_index][k] != '\0'){ /*In this part , I am copying the my new most similar word. I am  gonna use it in main function as name 'most_similar_word'*/
      w2[k] = dict[last_index][k]; /*Just copying.*/
      k++;
   }
   
   w2[k] = '\0'; /*Do not forget to add null at the en of the string*/
  fclose(dictionary);
  return min; /*returning the min value.*/

}
void bubble_sort(char inp_words[][MAX_WORD_SIZE],int frequencies[] ,int word_flags [] , int size,char new_words[][MAX_WORD_SIZE] ){ /*It isjust a bubble sort process.*/
   /*All of these arrays have same indexes.That is why when I swap one array  ,then I also must swap the all of the other arrays of indexes. */
   for(int gecis = 1 ; gecis < size ; gecis++){
    for(int j = 0 ; j < size-1 ; j++){
      if(frequencies[j] < frequencies[j+1]){ /*If previous frequency less than next frequency , I swap them to sort them from biggest to lowest.*/
        int temp = frequencies[j];
        frequencies[j] = frequencies[j+1]; /*Swapping*/
        frequencies[j+1] = temp;
        char temp2[MAX_WORD_SIZE],temp3[MAX_WORD_SIZE];
        my_strcpy(temp2,inp_words[j]); /*Also strings must be copied to do not lose their indexes,*/
        my_strcpy(inp_words[j],inp_words[j+1]); /*Swapping.*/
        my_strcpy(inp_words[j+1],temp2); /*swapping*/
        my_strcpy(temp3,new_words[j]); /*Also strings must be copied to do not lose their indexes,*/
        my_strcpy(new_words[j],new_words[j+1]); /*Swapping.*/
        my_strcpy(new_words[j+1],temp3); /*swapping*/
        int temp4 = word_flags[j];
        word_flags[j] = word_flags[j+1]; /*Swapping*/
        word_flags[j+1] = temp4; /*Swapping*/
      }
    }
   }


}

void print_hist(int  frequencies[] ,int word_flags[] ,  int size , int scale , char inp_words[][MAX_WORD_SIZE] , char hist[][MAX_WORD_SIZE+5+20],char new_words[][MAX_WORD_SIZE]){
  for(int i = 0 ; i < size ; i++){
    if(word_flags[i] == 1 ){
     printf("”%s” -> ”%s” ",inp_words[i],new_words[i]); /*IF FLAG IS ONE , EQUALS MY WORD IS CHANGED.THUS I GOTTA ADD ALSO NEW SIMILAR WORD.*/
   for(int s = 0 ; s<=25 - (strlen(inp_words[i]) + strlen(new_words[i])) ; s++){ /*Hepsini ayni hizada yazmak icin bu spaceleri ekliyorum.*/
  
     printf(" "); /*I am just adding spaces to make my output more beautiful.*/
    }
    }

     else{
       printf("”%s” ",inp_words[i]); /*ELSE ,FLAG IS ZERO  MEANS THE WORD DID NOT CHANGE.*/
             for(int l = 0 ; l <=31-strlen(inp_words[i]); l++){ /*Hepsini ayni hizada yazmak sart ,dolayisiyla nizami bir goruntu icin bu spaceleri ekliyorum.*/
              printf(" "); /*I am just adding spaces to make my output more beautiful.*/
             }

     }
     
        if(frequencies[i]!=0){ /*If frequency is not zero  , means there will be output either + or * .*/
          if(word_flags[i] == 1){ /*If flag is 1  , means the word is changed and I must write + instead of * .*/
             for(int j = 1 ; j <=frequencies[i]/scale ; j++){ /*Print as many as frequency / scale value */
          printf("+");
           hist[i][j] = '+';
        }
          }
          else { /*Else means flag is 0 . If flag is zero , I can understand that the word did not change and I am gonna print *. */
        for(int j = 1; j <=frequencies[i]/scale ; j++){
          printf("*"); /*I could not use hist array because it is const char and I cannot assign any single thing in histogram  function..*/
          hist[i][j] = '*';
        }
          }
        }
       else {
        printf("NO MATCHES"); /*If frequency is 0 , output will be ”NO MATCHES”*/
       }
        printf("\n"); /*Do not forget add new line xd.*/
       }
}


int read_words(FILE *fptr,char word[])
{
    char c;
    while (!feof(fptr) && ((fscanf(fptr,"%c",&c)) && (!is_alpha(c))));
    if (feof(fptr)) return -1; /*If file in end , return -1;*/

    int indx = 1;
    word[0] = c;
    while (!feof(fptr) && (fscanf(fptr,"%c",&word[indx])) && (is_alpha(word[indx])))
    { /*In this part , I am reading the word if my char is alphabetic.*/
        indx++; /*Then increase the index one.*/
    }
    word[indx] = '\0';
    if (feof(fptr)) return -2; /*if is it end of file , return -2;*/
    if (indx >= 12) return -3; /*If the word is more than 12 , return -3;*/
    else return 1;
}

char* my_strcpy(char* dest, const char* src){ /*To make my process faster , I needed this function 6 times.*/
    int i = 0;
    while (src[i] != '\0') { /*I am just checking the end of the string.*/
        dest[i] = src[i]; /*I am just copiying one string's char to another*/
        i++;
    }
    dest[i] = '\0'; /*I am adding null at the end of the string.*/
    return dest; /*I am returning the dest string.*/
}
