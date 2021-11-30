Rayyan Bhuiyan, Ryan Wang


## Welcome to the RRT, the Rayyan Ryan Terminal.  

### Features we implemented
Runs commands! 
<br>
* Basic requirements: multiple commands, redirection, piping, and standard commands on linux like `ls`, `rm`, `echo` and more (check bugs for issues, especially with `cd`)
* CLEARS your current shell before 'entering' ours.
* Implemented color on areas such as the current working directory, what you type, output, and the shell name at the very top 
* Removes extra spaces in command line
### Features we tried to implement

- Adding color to the background
- Recording the history (failed miserably)
- Doing more than two commands at a time
- changing directory

<!-- ??? how are these features -->
<!-- - Function Headers
- From arg
- From main -->

### Function Headers (+ descriptions of what they do)
arg.h
```
void runOne(char **cmd);
// Runs a single command
// details: do execvp() and free() for a well-formatted command (cmd)
// Return type: it execs one commands

void runTwo(char **left, char **right);
// Runs multiple commands
// details: same as runOne but takes two commands (left, right)
// Return type: none, it execs two commands

char **userIn(char *user_cmd);
// Mostly a helper function directIn() and directOut()
// details: essentially takes user_cmd (which is user input) into a more proper command pieces
// Return type: char **, breaks user inpput into 'pieces'

void directIn(char **user_cmd);
// Redirects (<)
// details: takes in the user input (user_cmd), parses it, then redirects input (for <)
// Return type: none, does the redirect input

void directOut(char **user_cmd, int i);
// Redirects output (> and >>)
// details: takes in the user input (user_cmd), parses it, then uses a conditional to 
// redirect output based on > or >> 

char *braces(char *user_cmd);
// Removes excess spaces in or around command
// details: takes in a command, and using a simple loop, removes excess spaces and returns processed user_cmd
// returns a char * which is the command without extra spaces

void marioPlant(char **user_cmd);
// Handles pipe commands
// details: reads the parameter user_cmd, then separates the command and the corresponding input and output, and executes
// named as a mario reference (the plant that comes out a pipe)
// no return type, does pipe commands

const char* readArg(char *user_cmd);
// Looks for specific commands we programmed (redirection, piping, multiple commands)
// details: returns the character if its ( | > < ;)
// if the command does not have any special symbol, returns an empty string
// returns a char* which points to a symbol like | < > ; 

char **partitionArg(char *user_cmd, char sep);
// function to break apart an argument with symbols spaces and such. 
// details: Takes in the user given command along with sep which is what to separate the command line by (ex: ; , or a space)
// returns a char **, breaks apart argument
```
palette.h contains color codes we used to color certain texts 


### Bugs:
- If you type an invalid command, you go to next line (it doesn't run or show error)
- You can have two commands on the same line (but not more)
  - can't do exit with multiple commands (`ls ; exit`)
  - can't have multiple redirect commands (`ls > mom ; echo hello > mom`)
  - can't pipe in multiple commands (`echo hello | wc ; ls`)
- Cannot do `ls -a` or `ls -al`
- This code does not have complete `cd` functionality.
  - We were able to make `cd` but that code conflicted with other parts of the assignment (like redirection and echo). We opted to keep those features and abandon `cd`.
  - However, if you would like to see the `cd` functionality (and lose features like redirection and echo) then:
    - uncomment lines `57-62` in `main.c`
    - comment lines `146-151` in `main.c`
