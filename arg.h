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