#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  DEFAULT = 0,
  COMMAND_UNKNOWN = 1,
  EXIT_COMMAND = 2,
  ECHO_COMMAND = 3
} STATUS;

STATUS handle_input_from_user(char *input, size_t input_length);
void handle_echo_command(char *input, size_t input_length);
void handle_unknown_command(char *input, size_t input_length);

int main(int argc, char *argv[]) {

  setbuf(stdout, NULL);
  char input[1024];
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

    if(strcmp(input, "exit") == 0)
      return EXIT_COMMAND;

    if(strncmp(input, "echo ", 5) == 0) 
      return ECHO_COMMAND;

    return COMMAND_UNKNOWN;
}

void handle_echo_command(char *input, size_t input_length)
{
  printf("%s\n", input + 5);
  memset(input, 0, input_length);
}

void handle_unknown_command(char *input, size_t input_length)
{
    printf("%s: command not found\n", input);
    memset(input, 0, input_length);
}