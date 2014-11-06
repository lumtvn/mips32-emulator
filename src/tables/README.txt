this readme contains informacion concerning the use of a lookup table to store the prequisites of each and every operation to be simulated in the program.

As explained in the source files comments, the lookup function was taken from the book "C Programming", written by Kharnegan and Ritchie. The idea was to leave this functions untouched. So all the operation information is stored in the form of a string separated by commas. The information then is retrieved by calling the function "lookup", using as a name, the proper operation code for prequisites search.

The problem is, not all operations have the same type prequisites, and certainly not the same amount. This bring difficulties for setting a protocol in which the strings will be stored. Instead of comming up with an algohithm to store information in a string, i just made this table. This table explains what does the string represent for each command, in the moment of installing its prequisites.

The amount of items depends on the operation, but the first item is always the amount of items that the operation has, so its easier to parse and we make sure we get the exact amount of items we need for that specific operation.

ADD - 

1 - number of arguments: 3
2 - bits from