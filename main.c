#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  DEFAULT = 0,
  COMMAND_UNKNOWN = 1,
  EXIT_COMMAND = 2,
  ECHO_COMMAND = 3,
  TYPE_COMMAND = 4
} STATUS;

STATUS handle_input_from_user(char *input, size_t input_length);
void handle_echo_command(char *input, size_t input_length);
void handle_unknown_command(char *input, size_t input_length);
void handle_type_command(char *input, size_t input_length, char *builtins[], int number_of_builtins);

int main(int argc, char *argv[]) {

  setbuf(stdout, NULL);
  char input[1024];

  char *builtins[] = {
    "type",
    "echo",
    "exit"
  };

  STATUS status = DEFAULT;

  while(status != EXIT_COMMAND)
  {
    status = handle_input_from_user(input, sizeof(input));
    switch(status)
    {
      case COMMAND_UNKNOWN:
      {
        handle_unknown_command(input, sizeof(input));
        break;
      }
      case ECHO_COMMAND:
      {
        handle_echo_command(input, sizeof(input));
        break;
      }
      case TYPE_COMMAND:
      {
        handle_type_command(input, sizeof(input), builtins, sizeof(builtins) / sizeof(builtins[0]));
        break;
      }
    }
  }
  return 0;
}

STATUS handle_input_from_user(char *input, size_t input_length)
{
    printf("$ ");

    if(fgets(input, input_length, stdin) == NULL)
      return EXIT_COMMAND;
    else
      input[strcspn(input, "\n")] = '\0';

    char input_copy[1024];
    char *command;
    strcpy(input_copy, input);
    command = strtok(input_copy, " ");

    if(strcmp(command, "exit") == 0) 
      return EXIT_COMMAND;
    if(strcmp(command, "echo") == 0) 
      return ECHO_COMMAND;
    if(strcmp(command, "type") == 0)
      return TYPE_COMMAND;

    return COMMAND_UNKNOWN;
}

void handle_echo_command(char *input, size_t input_length)
{
    strtok(input, " ");
    char *argument = strtok(NULL, "");

    if(argument != NULL)
    {
      printf("%s\n", argument);
    }
    else
      printf("USAGE: %s <text>\n", input);
}

void handle_unknown_command(char *input, size_t input_length)
{
    printf("%s: command not found\n", input);
}

void handle_type_command(char *input, size_t input_length, char *builtins[], int number_of_builtins)
{
  int builtin_found = 0;
  char *type = strtok(input, " ");
  char *argument = strtok(NULL, " ");

  if(argument != NULL)
  {
    for(int i = 0; i < number_of_builtins; i++)
    {
      if(strcmp(argument, builtins[i]) == 0)
      {
        printf("%s is a shell builtin\n", argument);
        builtin_found = 1;
        break;
      }
    }
    if(builtin_found != 1)
      printf("%s: not found\n", argument);
  }
  else 
    printf("USAGE: %s <command>\n", type);
}

