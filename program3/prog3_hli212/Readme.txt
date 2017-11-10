


Name: Heng Li
hli212

-----------------------------------------------

Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what typedefs did you change and why?
I changed the NODE struct, I added:
 left_nodes (amount of nodes in left subtree)
 right_node (amount of nodes in the right subtree)

I think this will be easier when doing the rebalancing, because I can access the size of the left and right subtree in O(1) time.

I also changed the BST:
 For bst_sb_work
 I added an int to keep track of the work done for rebalancing






-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  
I modified :
void bst_insert(BST * t, int x)
    call the contains function to check if the tree already has the value--- log n
    if the tree does not have the vaue then insert it                    --- log n
    walk along the path of inserted value check if need to rebalance     --- log n (generally)
        if need balance then rebalance it
    overall runtime log n + log n + log n = 3 log n ---> O(log n)

int bst remove
    call the contains function to check if the tree already has the value--- log n
    if the tree does have the vaue then delete it                        --- log n
    walk along the path of deleted value check if need to rebalance      --- log n (generally)
        if need balance then rebalance it
    overall runtime log n + log n + log n = 3 log n ---> O(log n)

NODE * from_arr(int *a, int n)
    added some bookkeeping stuff




-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?

For remove_r():
call the contains function to check if the tree already has the value--- log n
if the tree does have the vaue then delete it                        --- log n
walk along the path of deleted value check if need to rebalance      --- log n (generally)
if need balance then rebalance it
overall runtime log n + log n + log n = 3 log n ---> O(log n)

void bst_insert(BST * t, int x)
call the contains function to check if the tree already has the value--- log n
if the tree does not have the vaue then insert it                    --- log n
walk along the path of inserted value check if need to rebalance     --- log n (generally)
if need balance then rebalance it
overall runtime log n + log n + log n = 3 log n ---> O(log n)

NODE * from_arr(int *a, int n)
added some bookkeeping stuff, those code are constant runtime, so does not affect the origional runtime








-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


bst_to_array level of completion:  _____5______  


-----------------------------------------------
bst_get_ith level of completion:  ______5_____  

    How did you ensure O(h) runtime?

    ANSWER: Because I modified the NODE typedefs, added left_nodes and right_nodes.
		    With number of left_nodes and number of right_nodes, and the root's index,
            I can know my current position as I walk along the tree
            So as I walk along the tree, all I need to do is check if current postion == i

            This will give theta(log n) there for it ensure O(h)

-----------------------------------------------
bst_get_nearest level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: First I walk a long the tree until I find compare to the root of the tree decide to go to left or right.
            If x < r->val, then it will check the right_most node of the left subtree to check if x is between the largest value in the left
                subtree and the r->val, if x is then choose which ever the one that closer to x
                if x is not between, then recusively call get_nearest
            If x > r->val, then it will check the left_most node of the right subtree to check if x is between the smallest value in the right
                subtree and r->val, if x isthen choose which ever the one that's closer to x
                if x is not between, then recusively call get_nearest

  
-----------------------------------------------
bst_num_geq level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER:
   Find the node that's contains largest value that's less than x,
   Then check if it's right tree value is greater than x, if it is, then 
   The return value of bst_num_geq is size(t) - size(subtree->left) - 1

-----------------------------------------------
bst_num_leq level of completion:  ______5______

    How did you ensure O(h) runtime?

    ANSWER: bst_num_leq(x) = size(t) - bst_num_geq(x) + 1;

-----------------------------------------------
bst_num_range level of completion:  _____5_______

    How did you ensure O(h) runtime?

    ANSWER: bst_num_range = size(t) - ((size(t) - bst_num_leq(min) ) + (size(t) - bst_num_geq(max)))

-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: _____5______


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

I built my own test based on test.c, basically inserting and removing a few extra nodes.
I also used michel's test on piazza to test all the function.
I did professor's t0, t1, t0_prime. However, at least on my machine i could not get the max runtime.
    But I am confident that my funtions' runtimes are asymptotically the same as required runtime.







