


Sample test program(s) for the bst project.



t0.c:  builds a BST of size N by inserting
       sequentially values 1..N.

       N is given as a command-line parameter.

       The test:

           If size-balancing has been correctly
           implemented, this entire insertion sequence
           should take NlogN time.

           The test code runs a calibration procedure
           to create an appropriate runtime budget (with
           a reasonable amount of wiggle room to account
           for variability in runtime constants).

           It then runs the test.

      Usage example for N=1000:

           ./t0 1000

      Comments:  small values for N are not likely to give
           meaningful information.

           I would start with N=500 as a minimum.


t1.c
      Extension of t1.c th
      t includes deletion of the even 
      integers in the range.
