// !~~~ INCLUDES ~~~!
#include <unistd.h>
#if defined(__linux__) || defined(__APPLE__)
#include <sys/ioctl.h>
#include <termios.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

#ifndef TERMINAL_H
#define TERMINAL_H

// !~~~ DATA ~~~!

#if defined(__linux__) || defined(__APPLE__)
termios *terminal_attrs = new termios;
termios *initial_attrs = new termios;
#endif

// !~~~ FUNCTIONS ~~~!

/*
 * get the dimensions of the terminal window, in characters
 *
 * @param cols pointer to an `int`, where the horizontal size will be stored
 * @param rows pointer to an `int`, where the vertical size will be stored
 */
int get_window_size(int *cols, int *rows) {
#if defined(__linux__) || defined(__APPLE__)
  struct winsize s = {};
  ioctl(0, TIOCGWINSZ, &s);
  *cols = s.ws_col;
  *rows = s.ws_row;
  return 0;
#elif defined(_WIN32)
  printf("not implemented on windows yet.");
  return 1;
#endif
}

/*
 * perform initialization of necessary library components.
 * call this at the start of your program. only use once.
 */
int term_init() {
#if defined(__linux__) || defined(__APPLE__)
  tcgetattr(STDIN_FILENO, terminal_attrs);
  *initial_attrs = *terminal_attrs;
  // disabling cannonical mode does the following:
  // input can be read without pressing enter
  // read() can be non-blocking
  // line editing (done by the terminal) is disabled
  terminal_attrs->c_lflag &= ~(ECHO | ICANON);
  // edit the termios struct to configure the read() behavior we want
  // namely, we want read() to return immediately
  terminal_attrs->c_cc[VMIN] = 0;
  terminal_attrs->c_cc[VTIME] = 0;

  // set the new attributes
  tcsetattr(STDIN_FILENO, TCSANOW, terminal_attrs);

  return 0;
#elif defined(_WIN32)
  printf("initialization not required on windows yet.");
  return 1;
#endif
}

/*
 * perform cleanup of library components.
 * call this whenever your program closes. only use once.
 *
 * if this function call is skipped (e.g. premature exit due to crash),
 * users may have to restart their terminal to restore normal function.
 */
int term_cleanup() {
#if defined(__unix__) || defined(__APPLE__)
  // reset to initial attributes
  *terminal_attrs = *initial_attrs;
  tcsetattr(STDIN_FILENO, TCSANOW, initial_attrs);
  // destroy structs
  delete terminal_attrs;
  delete initial_attrs;
  return 0;
#elif defined(_WIN32)
  printf("cleanup not required on windows yet.");
  return 1;
#endif
}

#endif