#include "terminal.h"

#include <cctype>
#include <csignal>
#include <cstdio>
#include <cstdlib>

// clang-format off

void exit_function(int sig) {
  // all changes we want to roll back after testing
  {
    enable_echo();
  }
  exit(0);
}

int main(int argc, char const *argv[]) {
  term_init();

  // testing for non-toggleable features
  {
    int cols;
    int rows;
    get_window_size(&cols, &rows);
    printf("window is %d cols by %d rows\n", cols, rows);
  }

  // all changes that we want to perform for testing
  {
    disable_echo();
  }

  // to test keyboard and user input related features
  {
    // sigaction is posix only
    #if defined(__unix__)
    struct sigaction *exit_program = new struct sigaction;
    exit_program->sa_handler = &exit_function;
    // ctrl + c -> SIGINT
    sigaction(SIGINT, exit_program, nullptr);
    
    int cols; int rows;
    while (1) {
      get_window_size(&cols, &rows);
      // terminal is way too slow to be printing so often, even if it's just a
      // little bit of text. framebuffer needs to be implemented.
      // printf(CLEAR "window size: %d x %d", cols, rows);
      char b[5] = {'\0'};
      int s = read(0, b, 4);
      b[s+1] = '\0';
      if (s) {
        printf("raw bytes read: ");
        for (int i = 0; i < s; i++) {
          printf("%#2hhx ", b[i]);
        }
        printf("\nread %d chars: %s\n", s, b);
      }
    }
    #endif
  }
  return 0;
}
