


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
remove_r(r, int x) --> NODE *remove_r(NODE *r, int x, int *success, int pre_val)
insert(r, int x) --> int insert(NODE** r, int x, int pre_bal)
NODE * from_arr(int *a, int n)




-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?

For insert():
I changed the return type to int, it will return 1 if successfully inserted 0 if did not.
(This does not change the runtime)
Then I changed the parameters that if need to (NODE** r, int x, int pre_bal)
pre_bal == 1, then root will do the rebalance, == 0 then the parent is balanced even after the insertion.

Changing from NODE* r to NODE** r is because I want the function to return an int, and I still want to be able to change the NODE 
This is just for bookkeeping purposes, so the runtime will not change.
Then I added automatic rebalance, as we proved in class even after adding the size balancing to it the runtime will still be generally the same log n

For remove_r():
I added int pre_bal:
Again this is for size balancing, and we have proved that after adding size balancing the runtime is still generally the same log n

I also modified for bookkeeping, and again they are all O(1) runtime, so they do not change runtime

For from_arr():
I only modified for bookkeeping, again the additional code has O(1), they do not change the runtime.

For all the code I modified, I try my best to ensure they have constant runtime, except for the rebalancing. But we already proved they don't really matter.







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
		So when doing get_ith, all the function does is compare
 if left_nodes + 1 is equal to i or not. 
 if left_node + 1 is less than i then recursively call on the right subtree
 if left_node +1 is greater than i then recursively call on the left subtree
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

I built my own test based on test.c, basically inserting and removing a few extra nodes. I also used michel's test on piazza to test all the function.
I will I did prof's test suits for runtime earlier.







