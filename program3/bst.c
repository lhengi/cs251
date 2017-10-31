#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;
    int left_nodes;
    int right_nodes;

};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
};

BST * bst_create(){
  BST * t = malloc(sizeof(struct bst));
  t->root = NULL;
  return t;
}


static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST * t){
    free_r(t->root);
    free(t);
}

static NODE * insert(NODE *r, int x)
{
    NODE *leaf;
    if(r == NULL)
    {
        leaf = malloc(sizeof(NODE));
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->val = x;
        leaf->left_nodes = 0;
        leaf->right_nodes = 0;
        return leaf;
    }

    if(r->val == x)
    return r;
    
    if(x < r->val)
    {
        r->left_nodes++;
        r->left = insert(r->left, x);
        return r;
    }
    else
    {
        r->right_nodes++;
        r->right = insert(r->right, x);
        return r;
    }

}

// how about an iterative version?
static NODE *insert_i(NODE *r, int x)
{
    return NULL;
}


void bst_insert(BST * t, int x){
    t->root = insert(t->root, x);
}

int bst_contains(BST * t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;  
}

// Find the smallest value in subtree r
static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

// Find the largest value in subtree r
static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success)
{
    NODE   *tmp;
    int sanity;

    if(r==NULL)
    {
        *success = 0;
        return NULL;
    }
    
    if(r->val == x)
    {
        *success = 1;

        if(r->left == NULL)
        {

            tmp = r->right;
            free(r);
            return tmp;
        }
        if(r->right == NULL)
        {
            tmp = r->left;
            free(r);
            return tmp;
        }
        
        // if we get here, r has two children
        r->val = min_h(r->right);
        r->right = remove_r(r->right, r->val, &sanity);
        if(!sanity)
        {
            printf("ERROR:  remove() failed to delete promoted value?\n");
        }
        else
        {
            
        }
        return r;
    }
    

    if(x < r->val)
    {
        r->left = remove_r(r->left, x, success);
        if(*success == 1)
            r->left_nodes--;
    }
    else
    {
        r->right = remove_r(r->right, x, success);
        if(*success == 1)
            r->right_nodes--;
    }
    return r;

}


int bst_remove(BST * t, int x)
{
    int success;
    t->root = remove_r(t->root, x, &success);
    return success;
}

static int size(NODE *r){

    if(r==NULL) return 0;
    return size(r->left) + size(r->right) + 1;
}
int bst_size(BST * t){

    return size(t->root);
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST * t){
    return height(t->root);

}

int bst_min(BST * t){
    return min_h(t->root);
}

int bst_max(BST * t){
    return max_h(t->root);
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d]\n", r->val);
  inorder(r->right);

}
void bst_inorder(BST * t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d\n", r->val);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST * t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

/* 
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
    /* FILL IN FUNCTION */
    if(r==NULL) {
        indent(margin);
        printf("NULL \n");
    } else {
        indent(margin);
        preorder(r->left, margin+3);
        preorder(r->right, margin+3);
        printf("%d\n", r->val);
    }
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST * t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

/* 
 * Write the (recursive) helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
int m;
NODE *root;

    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->val = a[m];
    root->left = from_arr(a, m);
    root->right = from_arr(&(a[m+1]), n-(m+1));
    return root;

}

BST * bst_from_sorted_arr(int *a, int n){

  BST * t = bst_create();

  t->root = from_arr(a, n);

  return t;
}

//inorder
//return 1 when success, 0 otherwise
void to_array(NODE* r, int* array, int* index)
{
    if(r == NULL)
        return;
    to_array(r->left, array, index);
    array[*index] = r->val;
    (*index)++;
    to_array(r->right, array, index);
    
}

int * bst_to_array(BST * t)
{
    int* array = malloc(sizeof(int)*bst_size(t));
    int index = 0;
    to_array(t->root, array,&index);
    return array;
}


int get_ith(NODE* r, int i, int* current_position)
{
    if(*current_position == i)
    {
        return r->val;
    }
    if(r == NULL)
        return 0;
    
    //only return 0 or the ith value, so it's ok to add
    int return_var = 0;
    return_var += get_ith(r->left, i, current_position);
    *current_position += 1;
    return_var += get_ith(r->right, i, current_position);
    *current_position += 1;
    
    return return_var;
    
}


// get the ith smallest value
int bst_get_ith(BST *t, int i)
{
    if(i > bst_size(t))
    {
        fprintf(stderr, "Ther is no i th element in the tree");
        return -999999;
    }
    
    int current_position = 0;
    return get_ith(t->root, i, &current_position);
}








//


























