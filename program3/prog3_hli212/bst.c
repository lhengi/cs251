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
    int work;
};

BST * bst_create(){
  BST * t = malloc(sizeof(struct bst));
  t->root = NULL;
   t->work = 0;
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


/* Retstoring prof's code
static NODE * insert(NODE *r, int x, int* succes)
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
        *succes = 1;
        return leaf;
    }

    if(r->val == x)
    return r;
    
    if(x < r->val)
    {
        
        r->left = insert(r->left, x, succes);
        if(*succes == 1)
            r->left_nodes++;
        return r;
    }
    else
    {
        
        r->right = insert(r->right, x,succes);
        if(*succes == 1)
            r->right_nodes++;
        return r;
    }

}
*/
/*
static NODE * insert(NODE *r, int x){
    NODE *leaf;
    if(r == NULL){
        leaf = malloc(sizeof(NODE));
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->val = x;
        return leaf;
    }
    
    if(r->val == x)
        return r;
    if(x < r->val){
        r->left = insert(r->left, x);
        return r;
    }
    else {
        r->right = insert(r->right, x);
        return r;
    }
}
 */

//inorder
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

/*
 * Write the (recursive) helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n)
{
    int m;
    NODE *root;
    
    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->val = a[m];
    root->left = from_arr(a, m);
    root->left_nodes = m;
    root->right = from_arr(&(a[m+1]), n-(m+1));
    root->right_nodes = n - m-1;
    return root;
    
}

BST * bst_from_sorted_arr(int *a, int n)
{
    
    BST * t = bst_create();
    
    t->root = from_arr(a, n);
    
    return t;
}

NODE* rebalance(BST* t, NODE* r)
{
    BST* new_sub = bst_create();
    new_sub->root = r;
    int new_r_len = bst_size(new_sub);
    int* new_r = bst_to_array(new_sub) ;// this will covert tree r to a sorted array
    new_sub = bst_from_sorted_arr(new_r, new_r_len);
    t->work += new_r_len;
    
    return new_sub->root;
    
}


// how about an iterative version?
static NODE *insert_i(NODE *r, int x)
{
    return NULL;
}

// return 1 if successfully inserted, 0 otherwise
static int insert(BST* t, NODE** r, int x, int pre_bal)
{
    NODE* leaf;
    if(*r == NULL)
    {
        leaf = malloc(sizeof(NODE));
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->val = x;
        leaf->left_nodes = 0;
        leaf->right_nodes = 0;
        *r = leaf;
        return 1;
    }
    
    // when encounter duplicate value
    if((*r)->val == x)
    {
        return 0;
    }
    
    int succes = 0;
    int current_bal = 0;
    int next_bal = 0;
    if(x < (*r)->val)
    {
        if((pre_bal == 0 &&(*r)->left_nodes >= 2*(*r)->right_nodes + 1))
            current_bal = 1;
        
        if(current_bal || pre_bal)
            next_bal = 1;

        
        succes = insert(t, &((*r)->left), x,next_bal);
        if(succes == 1)
        {
            (*r)->left_nodes++;
            
            if(current_bal == 1)
            {
                *r = rebalance(t,*r);
            }
        }
        
        return succes;
    }
    //int cmp_left = 2*(*r)->left_nodes +1;
    if(pre_bal == 0 && ( (*r)->right_nodes >= 2*(*r)->left_nodes +1))
        current_bal = 1;
    
    if(current_bal || pre_bal)
        next_bal = 1;
    
    succes = insert(t, &((*r)->right), x, next_bal);
    if(succes == 1)
    {
        (*r)->right_nodes++;
        if(current_bal == 1)
        {
            *r = rebalance(t,*r);
        }
    }
    return succes;
}

void bst_insert(BST * t, int x){
    //int succes = 0;
    //t->root = insert(t->root, x);
    insert(t,&(t->root), x,0);
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

static NODE *remove_r(BST* t, NODE *r, int x, int *success, int pre_val)
{
    NODE   *tmp;
    int sanity;

    if(r==NULL)
    {
        *success = 0;
        return NULL;
    }
    int current_bal = 0;
    int next_bal = 0;
    
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
        if(pre_val == 0 && 2*(r->right_nodes -1) + 1 < r->left_nodes)
            current_bal = 1;
        if(current_bal || pre_val)
            next_bal = 1;
        
        r->right = remove_r(t,r->right, r->val, &sanity,next_bal);
        r->right_nodes--;
        if(current_bal)
            r = rebalance(t,r);
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
        if(pre_val == 0 && 2*(r->left_nodes -1) + 1 < r->right_nodes)
            current_bal = 1;
        if(current_bal || pre_val)
            next_bal = 1;
        
        r->left = remove_r(t,r->left, x, success,next_bal);
        if(*success == 1)
        {
            r->left_nodes--;
            if(current_bal)
                r = rebalance(t,r);
        }
    }
    else
    {
        if(pre_val == 0 && 2*(r->right_nodes -1) + 1 < r->left_nodes)
            current_bal = 1;
        if(current_bal || pre_val)
            next_bal = 1;
        
        r->right = remove_r(t,r->right, x, success,next_bal);
        if(*success == 1)
        {
            r->right_nodes--;
            if(current_bal)
                r = rebalance(t,r);
        }
    }
    return r;

}


int bst_remove(BST * t, int x)
{
    int success;
    t->root = remove_r(t,t->root, x, &success,0);
    return success;
}


// now size function is O(1)
static int size(NODE *r)
{

    if(r==NULL) return 0;
    return r->left_nodes + r->right_nodes + 1;
}
int bst_size(BST * t)
{
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
    
}*/


int get_ith(NODE* r, int i,int tree_size)
{
    if(r == NULL)
    {
        fprintf(stderr, "r is NULL");
        return -99999999;
    }
    if(r->left_nodes + 1 == i || i == tree_size - r->right_nodes)
        return r->val;
    if(i <= r->left_nodes)
        return get_ith(r->left, i, tree_size);
    
    return get_ith(r->right, i, tree_size);
}


// get the ith smallest value
int bst_get_ith(BST *t, int i)
{
    if(i > bst_size(t) || i <= 0)
    {
        fprintf(stderr, "*** Error, There is no i th element in the tree\n");
        return -999999;
    }
    //int current_position = 0;
    return get_ith(t->root, i,bst_size(t));
}

int get_left_most(NODE* r)
{
    if(r == NULL)
    {
        fprintf(stderr, "GET most left, the node is null in the first place\n");
        return -999999999;
    }
    if(r->left == NULL)
        return r->val;
    
    return get_left_most(r->left);
}

int get_right_most(NODE* r)
{
    if(r == NULL)
    {
        fprintf(stderr, "Get most right, the node is null in the first place\n");
        return -9999999;
    }
    
    
    if(r->right == NULL)
        return r->val;
    return get_right_most(r->right);
}

int get_nearest(NODE* r, int x)
{
    
    if(r->val == x)
        return r->val;
    
    if(x < r->val)
    {
        
        if(r->left == NULL)
        {
            return r->val;
        }
        
        
        if(r->left->val <= x)
        {
            return get_nearest(r->left, x);
        }
        
        // handle if x is between r and r left most node
        int right_most = get_right_most(r->left);
        
        // if x is not between r and r left most node
        // then if must be on the r's left sub tree
        if(right_most >= x)
            return get_nearest(r->left, x);
        
        int distance_from_sub = x - right_most;
        int distance_from_root = r->val - x;
        if(distance_from_sub < distance_from_root)
            return right_most;
        return r->val;
    }
    
    if(r->right == NULL)
        return r->val;
    if(r->right->val >= x)
        return get_nearest(r->right, x);
    
    int left_most = get_left_most(r->right);
    
    // if x is not between root and left most
    // then it must be on the r's right subtree
    if(left_most <= x)
        return get_nearest(r->right, x);
    int distance_from_sub = left_most - x;
    int distance_from_root = x - r->val;
    if(distance_from_sub < distance_from_root)
        return left_most;
    return r->val;
    
}


int bst_get_nearest(BST *t, int x)
{
    if(t == NULL)
    {
        fprintf(stderr, "The tree is not initialized\n");
        return -999999;
    }
    
    return get_nearest(t->root, x);
}

int num_geq(NODE* r, int x)
{
    if(r == NULL)
        return 0;
    if(r->val >= x)
    {
        return num_geq(r->left, x) + r->right_nodes + 1;
    }
    return num_geq(r->right, x);
}
int bst_num_geq(BST *t, int x)
{
    return num_geq(t->root, x);
}

/*
int num_leq(NODE* r, int x)
{
    if(r == NULL)
        return 0;
    if(r->val > x)
        return num_leq(r->left, x);
    return size(r);
    
}*/

int bst_num_leq(BST* t, int x)
{
    return bst_size(t) - bst_num_geq(t, x) + 1;
}


int bst_num_range(BST* t, int min, int max)
{
    int total_size = bst_size(t);
    int total_greater_than_min = bst_num_geq(t, min);
    int total_less_than_max = bst_num_leq(t, max);
    int num_range = (total_size - total_less_than_max) + (total_size - total_greater_than_min);
    num_range = total_size - num_range;
    return num_range;
}

int bst_sb_work(BST* t)
{
    
    
    return 0;
}


int max_sb_height(int n) {
    unsigned int big;
    
    if(n<=0) return -1;
    if(n==1) return 0;
    big = (n-1) - (n/3);  // makes as imbalanced as possible within rules
    //    of being size-balanced
    
    return 1 + max_sb_height(big);
}






















