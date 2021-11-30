#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include "palette.h"
#include "arg.h"
#include "main.h"


int main()
{
  // clears screen
  system("clear");
	//system("Color E1");

  // to store the user input
	char user_cmd[200];
  // stores the current working directory
	char filepath[100];

  // variables to track processes 
	int k, status;
	int p = getpid();

  // the heading is yellow
  // printf(YELLOW);
  printf("RRT (Created by Rayyan Bhuiyan and Ryan Wang)\n \n");
  printf(RESET);
  char** args;

  // while we are in the shell
	while (p == getpid())
	{
    // start off by printing the cwd and $ symbol to emulate terminal
    // we're making this a blue color
    printf(CYAN);
		printf("%s$ ",getcwd(filepath, 100));

    // this makes the user input a green color
    printf(GREEN);
    fgets(user_cmd, sizeof(user_cmd) - 1, stdin);
    printf(RESET);

    const char* s = readArg(user_cmd);

  //========================
  // leave this block commented if you want redirect/echo

    // char** args = userIn(user_cmd);
    // // making sure args is correct (removing trailing \n)
    // char *args_str = *args;
    // char last = args_str[strlen(args_str)-1];
    // if (last == '\n')
    //   args_str[strlen(args_str)-1] = 0; 

  //========================


    //howMany(user_cmd);
		int i = fork();
    
    // if forking doesnt work
    if (i < 0)
    {
      printf("error: could not fork :: %s\n",strerror(errno));
      return errno; 
    }

    // in forked process
    if (i)
		{
      // to stop parent process from running till child is done
			k = wait(&status);

			if (WEXITSTATUS(status) == 1)
			{
        char last = args[1][strlen(args[1])-1];
        if (last == '\n')
          args[1][strlen(args[1])-1] = 0;
        // printf("args[1] path is: '%s'", args[1]);

        // change directories
        // status = chdir(path);
        status = chdir(args[1]);
              
        // if error with taking the user input
				int error = status;
				if (error == -1)
					printf("%s\n", strerror(errno));
      }
			
			if (WEXITSTATUS(status) == 2)
				exit(0);
		}
    else
		{
      // char** args = userIn(user_cmd);
      char **user_cmds_parsed;
      if (s[0] == ';') // SEMICOLON
      {
        user_cmds_parsed = partitionArg(user_cmd, ';');
        runTwo(userIn(user_cmds_parsed[0]), userIn(user_cmds_parsed[1]));
        free(user_cmds_parsed);
        return 0;
      }
      else if (s[0] == '>') // REDIRECT OUTPUT
      {
        printf("113 is running");
        user_cmds_parsed = partitionArg(user_cmd, '>');
        if (s[1] == '>')
        // for appending output
          directOut(user_cmds_parsed, 1);
        else
        // for > 
          directOut(user_cmds_parsed, 0);
        free(user_cmds_parsed);
        return 0;
      }
      else if (s[0] == '<') // REDIRECT INPUT
      {
        user_cmds_parsed = partitionArg(user_cmd, '<');
        directIn(user_cmds_parsed);
        free(user_cmds_parsed);
        return 0;
      }
      else if (s[0] == '|') // PIPING
      {
        user_cmds_parsed = partitionArg(user_cmd, '|');
        marioPlant(user_cmds_parsed);
        free(user_cmds_parsed);
        return 0;
      }


  // ===================
  // comment this if you want cd functionality

    char** args = userIn(user_cmd);
    // making sure args is correct (removing trailing \n)
    char *args_str = *args;
    char last = args_str[strlen(args_str)-1];
    if (last == '\n')
      args_str[strlen(args_str)-1] = 0; 

  // ===================

    // if user wants to change directory
    if (strcmp(args[0], "cd") == 0)
      return 1;

    // if user wants to exit
    if (strcmp(args[0], "exit") == 0)
      return 2;

    // runs the built in commands
    // printf("*args1: '%s'", *args1);
    runOne(args);
		}
	}
	return 0;
}
