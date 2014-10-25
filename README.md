# Stack Simulator

Nothing fancy here, just your average stack simulator. Useful for explaining what a stack is, how it works and for some basic reverse engineering/assembly programming sessions. 

Compile:

    make
    make clear

Usage: 

    ./stack -n ROWS -m COLS -w SIZE

ROWS being the number of rows needed (i.e. the maximum number of elements "stackable"), COLS the length wanted for each row, and SIZE the actual size of each word. 



    ./stack -n 10 -m 20 -w 4

Output: 

        sp    bp
      0028  0024
                    +--------------------+
     -0x28 -0x24    |                    |
                    +--------------------+
     -0x24 -0x20    |                    |
                    +--------------------+
     -0x20 -0x1c    |                    |
                    +--------------------+
     -0x1c -0x18    |                    |
                    +--------------------+
     -0x18 -0x14    |                    |
                    +--------------------+
     -0x14 -0x10    |                    |
                    +--------------------+
     -0x10 -0x0c    |                    |
                    +--------------------+
     -0x0c -0x08    |                    |
                    +--------------------+
     -0x08 -0x04    |                    |
                    +--------------------+
     -0x04   -      |                    | <= bp
                    +--------------------+
                                           <= sp

Commands available:

    push string : push 'string' in the stack
    pop         : pop the value pointed by sp and print it
    mov val, reg: mov 'val' in 'reg'
    add off, reg: add 'off' to 'reg'
    sub off, reg: subtract 'off' from 'reg'

(*reg* being either *sp* or *bp*)
