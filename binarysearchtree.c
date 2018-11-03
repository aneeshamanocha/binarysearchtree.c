//insert (root ndoe, datum), clear (root node), print (root node), find (return int of depth)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    char datum;
    struct node* left;
    struct node* right;
} Node;

int insert(Node ** first, char datum);
void clear(Node ** current);
void goBabyGroot(Node *first);
int find(Node * first, char datum);
int delete(Node ** first, char datum);
Node* rightMost(Node *first);

int main(void){
    srand(time(NULL));
    Node* first= NULL;

    /*for(int i=0;i<5;i++){
        insert(&first, i+97);
    }*/

    insert(&first, 'k');
    insert(&first, 'z');
    insert(&first, 'a');
    insert(&first, 'a');
    insert(&first, 'b');
    printf("Find: %d\n", find(first, 'z'));
    goBabyGroot(first);
    delete(&first, 'a');
    puts("");
    //delete(&first, 'a');
    //delete(&first, 'g');
    goBabyGroot(first);
    return 0;
}


int insert(Node ** first, char datum){
  if((*first)==NULL){
      Node * new = malloc(sizeof(Node));
      new->datum=datum;
      new->left=NULL;
      new->right=NULL;
      *first=new;
      return 0;
  }  else{
        if(((*first)->datum) < datum) {
          //insert(&((*first)->right), datum);
          return 1 + insert(&((*first)->right), datum);
        }
        else {
          //insert(&((*first)->left),datum);
          return 1 + insert(&((*first)->left), datum);
        }
      }
}

void clear(Node ** current){
    if ((*current) == NULL) return;
    else{
        clear(&((*current)->left));
        clear(&((*current)->right));
        free(*current);
        *current=NULL;
    }
}

//print
void goBabyGroot(Node * first){
  static int depth = 0;
    if (first==NULL){
      depth = 0;
    }
    else{
        if(first->right!=NULL){
            depth++;
            goBabyGroot(first->right);
            depth--;
            for(int i=0;i<depth;i++){
                printf(" ");
            }
            puts("|");
        }
        for(int k=0;k<depth-1;k++)
            printf(" ");
        printf("-%c\n",first->datum);
        if(first->left!=NULL){
            for(int i=0;i<depth;i++){
                printf(" ");
            }
            puts("|");
            depth++;
            goBabyGroot(first->left);
            depth--;
        }
    }
}

int find(Node * first, char datum){
  if(first==NULL){
      return -1;
  } else{
      if((first)->datum == datum) {
        return 0;
      }
      else {
        if((first)->datum < datum) {
          return 1 + find((first)->right, datum);
        } else {
          return 1 + find((first)->left, datum);
        }
      }
  }
  return 0;
}

int delete(Node ** first, char datum){
  //if datum isn't found, return 0;
  if(*first == NULL){
    return 0;
  }

  if((*first)->datum > datum) {
      return delete(&((*first)->left), datum);
  }

  if((*first)->datum < datum){
      return delete(&((*first)->right), datum);
  }

  //check if it doesn't have children
  if((*first)->left == NULL && (*first)->right == NULL){
    free(*first);
    (*first) = NULL;
    return 1;
  }
  //if datum found
  //check if it has one child
  if(((*first)->left == NULL) ^ ((*first)->right == NULL)) {
    //find which child has datum & assign to to left child
    Node *only = ((*first)->left) != NULL ? (*first)->left : (*first)->right;
    //Node *tmp = *first;
    //assign child to parent
    (*first)->datum = only->datum;
    (*first)->left = only->left;
    (*first)->right = only->right;
    free(only);
    return 1;
  }

  //if node has two children
  Node *rightest = rightMost((*first)->left);
  (*first)->datum = rightest->datum;
  delete(&rightest, rightest->datum);
  return 1;

}

Node* rightMost(Node *first){
  //if first right is null, return deferenced first
  if((first)->right == NULL) {
    return first;
  } else {
    return rightMost(first->right);
  }
}
