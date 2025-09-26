#include "terminal.h"

#include <cctype>
#include <csignal>
#include <cstdio>
#include <cstdlib>

using namespace terminal;

// clang-format off

void exit_function(int sig) {
  // clean up terminal before exiting
  cleanup_terminal();
  exit(0);
}

int main(int argc, char const *argv[]) {
  initialize_terminal();

  // terminal.h function testing
  {
    int cols;
    int rows;
    get_terminal_size(&cols, &rows);
    printf("window is %d cols by %d rows\n", cols, rows);
  }

  // to test keyboard and user input related features
  {
    // only tested on linux!!
    struct sigaction *exit_program = new struct sigaction;
    exit_program->sa_handler = &exit_function;
    // ctrl + c -> SIGINT
    sigaction(SIGINT, exit_program, nullptr);
    
    int cols; int rows;
    while (1) {
      get_terminal_size(&cols, &rows);
      // terminal is way too slow to be printing so often, even if it's just a
      // little bit of text. framebuffer needs to be implemented.
      // printf(CLEAR "window size: %d x %d", cols, rows);
      char b[5] = {'\0'};
      int s = read(0, b, 4);
      b[s] = '\0';
      if (s) {
        printf("raw bytes read: ");
        for (int i = 0; i < s; i++) {
          printf("%#2hhx ", b[i]);
        }
        printf("\nread %d chars: %s\n", s, b);
      }
    }
  }
  return 0;
}
