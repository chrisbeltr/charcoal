#include "termctl.h"
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
    struct sigaction *exit_program = new struct sigaction;
    exit_program->sa_handler = &exit_function;
    // ctrl + c -> SIGINT
    sigaction(SIGINT, exit_program, nullptr);
    while (1) {
      // absolutely nothing mwahahahaha
    }
  }
  return 0;
}
