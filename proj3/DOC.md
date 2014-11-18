Installation
======

Installing the system calls, the guide from Dr. Griff was followed.

The list of system call files that are needed are as follows:

  GlobalDef.c
  SaveVariable.c
  GetVariable.c
  NextVariable.c
  
No special algorithms were used in these files, they are mostly very straight foward and consist of basic C functions.

Algorithms
----------

Scanner
======

The scanner takes in a line of input, and returns a token and its type each time it is called.  The scanner returns false once the end of line has been reached.  There are two parts to the scanner: the tokenizer and the classifier.  

The tokenizer breaks up the line of input into seperate tokens.  Utilizing STL functions made this rather simple; each iteration, the next white space character was found, and the tokens were then extracted between white space.  A special case involving strings needed to be handled, since white space should be preserved within them.  After the tokens have been extracted, classification follows. This was done simply by checking the format using if-else statements.

Parser
======

Our parsing engine uses a state machine based approach. Each state
consumes a token, performs an action, then returns the next state.
Each line of input begins in a `null state`, and most (properly
formatted) lines will end on an `end state`. 

A list of states and who they connect to:

- null --> comment, defprompt, cd, arg, set
  - this is the parent state
- comment --> comment 
  - comment will continue to consume all tokens
- defprompt -> end
  - defprompt will consume a string token or return an error
- cd -> end
  - cd will consime a word then execute chdir()
- arg -> arg, end
  - arg will consume word, string, or variable until it sees none, or
    a <bg> token. when it runs out of valid tokens it will exec them
- assignto -> 

Features
--------

Bugs
----
