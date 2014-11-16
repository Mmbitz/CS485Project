Instalation
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
