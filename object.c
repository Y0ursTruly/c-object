#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 10 //number of child node structs from a parent node struct
//the larger this number the bigger any one node struct is yet the quicker it works to get data with long string key because the path is shorter

#define b 50 //size of array/(s) in each data struct
//the larger this number the bigger any one data struct is yet it makes things faster it would exist less times to hold a long string

//the structs come first
typedef struct path{
  int piece;
  struct path* next;
}path;
typedef struct data{
  int size; //0 or count of all linked data structs
  int length; //length used in a given data struct
  char string[b]; //text data(string value)
  struct node* object; //object pointer(object value)
  struct data* more; //used to connect several strings
}data;
typedef struct node{
    struct node* key[n+1]; //nodes that link up from text
    struct data* value; //result at the end of a key chain
}node;

//now for the functions
node *newNode(){ //returns new node with pointers at NULL
  node *toReturn=(node*)malloc(sizeof(node));
  for(int i=0;i<n+1;i++){ toReturn->key[i]=NULL; }
  toReturn->value=NULL;
  return toReturn;
}
data *read(){ //reads input and points empty data to NULL
  char tempChar;
  data *input=(data*)malloc(sizeof(data));
  input->object=NULL; input->more=NULL;
  input->size=1; input->length=0;
  data *current=input;
  while( (tempChar=fgetc(stdin))!='\n' ){
    if(current->length==b){
      current->more=(data*)malloc(sizeof(data));
      current=current->more; input->size++;
      current->object=NULL; current->more=NULL;
      current->size=0; current->length=0;
    }
    current->string[current->length++]=tempChar;
  }
  return input;
}
void write(data *output){
  data *current=output;
  do{
    printf("%s",current->string);
    current=current->more;
  }while(current!=NULL);
  printf("\n");
}
path *numToList(int num){
  int power=0;
  path *list=(path*)malloc(sizeof(path));
  path *head=list; list->next=NULL;
  while(num>0){
    int singleDigit=(int)(
      ( (int)(num) % (int)(pow(n,power+1)) )
      / pow(n,power)
    );
    num-=(int)( singleDigit*pow(n,power) );
    head->piece=singleDigit;
    path *newHead=(path*)malloc(sizeof(path));
    newHead->next=head;
    head=newHead; power++;
  }
  return head->next;
}
void setKey(node *object, data *key, data *value){
  node *current=object; data *head=key;
  for(int i=0;i<key->size;i++){
    for(int j=0;j<head->length;j++){
      int index=(int)head->string[j];
      if(index<n){
        if(current->key[index]==NULL){
          current->key[index]=newNode();
        }
        current=current->key[index];
        if((i+1)==key->size && (j+1)==head->length){
          continue; //takes out extra pointer at the end
        }
        if(current->key[n]==NULL){
          current->key[n]=newNode();
        }
        current=current->key[n]; //char separation"symbol"
        continue; //when index takes only one node
      }
      //else(when index takes more than one node)
      path *pathList=numToList(index);
      do{
        int pathIndex=pathList->piece;
        if(current->key[pathIndex]==NULL){
          current->key[pathIndex]=newNode();
        }
        current=current->key[pathIndex];
        path *previous=pathList;
        pathList=pathList->next;
        free(previous);
      }while(pathList!=NULL);
      if((i+1)==key->size && (j+1)==head->length){
        continue; //takes out extra pointer at the end
      }
      if(current->key[n]==NULL){
        current->key[n]=newNode();
      }
      current=current->key[n]; //char separation"symbol"
    }
    head=head->more;
  }
  current->value=value;
}
data *getKey(node *object, data *key){
  node *current=object; data *head=key;
  for(int i=0;i<key->size;i++){
    for(int j=0;j<head->length;j++){
      int index=(int)head->string[j];
      if(index<n){
        if(current->key[index]==NULL){ return NULL; }
        current=current->key[index];
        if((i+1)==key->size && (j+1)==head->length){
          continue; //takes out extra pointer at the end
        }
        if(current->key[n]==NULL){ return NULL; }
        current=current->key[n]; //char separation"symbol"
        continue; //when index takes only one node
      }
      //else(when index takes more than one node)
      path *pathList=numToList(index);
      do{
        int pathIndex=pathList->piece;
        if(current->key[pathIndex]==NULL){ return NULL; }
        current=current->key[pathIndex];
        path *previous=pathList;
        pathList=pathList->next;
        free(previous);
      }while(pathList!=NULL);
      if((i+1)==key->size && (j+1)==head->length){
        continue; //takes out extra pointer at the end
      }
      if(current->key[n]==NULL){ return NULL; }
      current=current->key[n]; //char separation"symbol"
    }
    head=head->more;
  }
  return current->value;
}

//code runs below
int main(void) {
  node *myObject=newNode();
  while(1){
    printf("Enter a key(to set)\n");
    data *myKey=read();
    printf("Enter a value\n");
    data *myValue=read();
    if(getKey(myObject,myKey)!=NULL){
      printf("The key existed and is overwritten\n");
    }
    setKey(myObject,myKey,myValue);
    printf("Enter a key(to search)\n");
    data *result=getKey(myObject,read());
    if(result==NULL){
      printf("\nThe key was not found\n\n");
    }
    else{
      printf("\nThe result is:\n");
      write(result); printf("\n");
    }
  }
}
