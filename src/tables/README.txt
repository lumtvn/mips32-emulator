this readme contains information concerning the tables in this folder

table op_info.t

this table contains all the information concerning an operation. using the lookup function and this table, we can hash an operation to its operating items such as opcode,number of arguments, etc. Each line of the table has the next format:

OPERATION item1,item2,item3...

each line is brought to the program and parsed using strtok function

The amount of items depends on the operation, but the first item is always the amount of items that the operation has, so its easier to parse and we make sure we get the exact amount of items we need for that specific operation.

The order of the items is not random, it follows a specific protocol that every operation in the table must follow in order to the program to understand each prequisite of the operation. The order is as follows:

item 1: total items (1 is the minimum)
item 2: operation SPECIAL code
item 3: number of arguments required for the operation
