


Name: Heng Li

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.
-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class ans in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.

I defined each priority struct to have one more int variable to record what index are they in the heap
i.e.
typedef struct Node
{
int ID;
double priority;
int index;
}

I defined my heap with an aditional array that acts as a map, and uses ID as index for each Node
struct pq
{
Node** q;
Node** map;///
int size;
int capacity;
int minheap;
}

ID of each priority is an index of another array that points to the same priority Node struct.
I have two array Node pointers. One array is the heap, the other one is the map. For map array,
I use ID as index for each priority Node.








-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?

Everytime I insert a priority Node, I have to check the map array, see if the ID is already exist.
Variefy if the ID is a valid ID that's between 0 and the capacity.
Because I have each Node keep track of their index in the heap, so everytime I percolat up or down, I have to
update their index.






-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?

After my implementation of the map, every time i delete the top, I have to make sure I also delete the Node in the map.





-----------------------------------------------
Explain how your implementation of bst_change_priority worked,
why it is correct and why it achieves the runtime requirement.

my pq_change_priority uses the parameter id, then it will check if that
id is valid or not. if it is valid and exists in the map, then it will update the Node's priority.
Then it will percolat up the node, then percolate down the node to make sure that the heap is still a valid minheap or maxheap.

Change priority theta(1)
percolate up    theta(log n)
percolate down  theta(log n)
that(1) + theta(log n) + theta(log n)  is still theta(log n)
so the runtime meets the requirement theta(log n)








-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?

I added the map array that uses each id as index.
So for pq_get_priority, all I need to do is to access the Node pointer to get the priority value.
Which enables O(1) runtime









