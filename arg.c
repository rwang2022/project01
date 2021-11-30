#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include "palette.h"
#include "arg.h"

#define IN_ENTRY 0
#define OUT_ENTRY 1

// To run a single command
void runOne(char **cmd) // no return type
{
  // exec given command, then free memory
  printf(GREEN);
	execvp(cmd[0], cmd);
	free(cmd);
}

// with multiple command
void runTwo(char **left, char **right) // no return type
{

	int i = fork();
	int k, status;
	if (i)
  // to stop from running until child process has exit
	{ // if the first command process has finished run the second one
		k = wait(&status);
		runOne(right);
	}
	else
	{
		runOne(left);
	}
}

// to take in a command
char **userIn(char *user_cmd) // returns a double pointer
{
	char **args;
	char *curr = user_cmd;
	char *elem;
  int arg_count = 0;
  // allocate memory
  args = malloc(sizeof(char *) * 5);
	while (curr)
	{
    // separates the command by spaces into an array containing each 'piece'
		elem = strsep(&curr, " ");
		if (strcmp(elem, ""))
			args[arg_count] = elem;
		else
			arg_count--;
		arg_count++;
	}

  // if more memory is needed
	if (arg_count > 5)
		args = realloc(args, sizeof(char *) * arg_count);
	return args;
}

// for redirecting input (<)
void directIn(char **user_cmd) // returns nothing
{
  // 'saves' the user input in the double pointer
	char **parsed_user_cmd = userIn(user_cmd[0]);
	int file_desc = open(userIn(user_cmd[1])[0], O_RDONLY);
	
  // to create copy of the file descriptor
  int stdin_dup = dup(IN_ENTRY);
	dup2(file_desc, IN_ENTRY);
  // runs the command
  printf(GREEN);
	execvp(parsed_user_cmd[0], parsed_user_cmd);
  // makes the file descriptor stdin_dup
	dup2(stdin_dup, IN_ENTRY);
}

// for redirecting output (> and >>)
void directOut(char **user_cmd, int i) // returns nothing
{
  // take in the  input
	char **parsed_user_cmd = userIn(user_cmd[0]);
	char *n = userIn(user_cmd[1])[0];
	int file_desc;
	if (i) // if i is true, append (>>)
  { // for >> 
		file_desc = open(n, O_WRONLY | O_APPEND | O_CREAT, 0644); // appending
  }
  else
  { // for > 
		file_desc = open(n, O_WRONLY | O_TRUNC | O_CREAT, 0644); // truncating
  }
  int stdout_dup = dup(OUT_ENTRY);
	dup2(file_desc, OUT_ENTRY);

  //executes  command
  printf(GREEN);
	execvp(parsed_user_cmd[0], parsed_user_cmd);
	//designates a file descriptor
  dup2(stdout_dup, OUT_ENTRY);
	close(file_desc);
}

// braces (function to remove excess spaces around or within command)
char *braces(char *user_cmd) // returns a char pointer
{
  int index; 
  int x;
  for(index=x=0; user_cmd[index]; ++index)
  {
    if(!isspace(user_cmd[index]) || (index > 0 && !isspace(user_cmd[index-1])))
      {
        user_cmd[x++] = user_cmd[index];
      }
  }
  // to end string
  user_cmd[x] = '\0';
  // returns string without extra spaces
  return user_cmd;
}

// mario reference-- the plant that comes out a pipe
void marioPlant(char **user_cmd) // no return type
{
	FILE *input, *output;
	char read_buffer[100];
  // left side of the |
	char *left_side = user_cmd[0];
  // right side of the |  
	char *right_side = user_cmd[1];

  //removes all spaces on the left and right side
  braces(left_side);
	braces(right_side);

  //reads in from the input aka left side (ls | wc ---> ls)
	input = popen(left_side, "r");
  // outputs using the right side command (ls | wc ---> wc)
	output = popen(right_side, "w");

  // reads input into stream
	while (fgets(read_buffer, 100, input) != NULL)
	{ // puts the output
		fputs(read_buffer, output);
	}
  // to close the streams opened by the popen
	pclose(input);
	pclose(output);
}


/*
//function we tried to use for giving a warning message if u input more than two commands
void howMany(char **com)
{
  char **args = userIn(com);
  int num;
  num = sizeof(args)/sizeof(args[0]);

  if (num > 2)
  {
    printf("Please dont provide more than two commands");
  } 
  
}
*/

// character                    symbol
// ;	                          1
// >		                        2	
// >>		                        3
// <		                        4
// |		                        5
// Looks for specific commands we programmed, tracks what specific tool
const char* readArg(char *user_cmd) // returns a pointer to a char
{
  int i;  
  int len = strlen(user_cmd);
  for (i = 0; i < strlen(user_cmd); i++) 
  {
    char* s = &(user_cmd[i]);
    if (*s=='>'||*s=='<'||*s==';'||*s=='|') 
    {
      if ((i+1 < len) && (user_cmd[i+1]=='>'))
      {
        return ">>";
      }
      return s;
    }
  }
  return "";
}


// function to break apart an argument with symbols spaces and such. 
// sep is argument like ; < etc
char **partitionArg(char *user_cmd, char sep) // returns a double pointer referring to user command separated
{
	char **cmds = malloc(8 * sizeof(char *));
	char *curr = user_cmd;
	char *elem;
	int count = 0;
  // goes through command, separ
	while (curr)
	{
    // separates elem
		elem = strsep(&curr, &sep);
		if (strcmp(elem, ""))
			cmds[count] = elem;
		else
			count--;
		count++;
	}
	if (count > 8)
		cmds = realloc(cmds, sizeof(char *) * count);
	return cmds;
}