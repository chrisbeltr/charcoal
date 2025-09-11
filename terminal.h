#include "termctl.h"

#ifndef TERMINAL_H
#define TERMINAL_H

/*
 * perform initialization of necessary library components.
 * call this at the start of your program. only use once.
 */
void term_init() {
#if defined(__unix__) || defined(__APPLE__)
  get_terminal_attrs();
  *initial_attrs = *terminal_attrs;
  // disabling cannonical mode does the following:
  // input can be read without pressing enter
  // read() can be non-blocking
  // line editing (done by the terminal) is disabled
  disable_feature(ICANON);
  // edit the termios struct to configure the read() behavior we want
  // namely, we want read() to return immediately
  terminal_attrs->c_cc[VMIN] = 0;
  terminal_attrs->c_cc[VTIME] = 0;
#elif defined(_WIN32)
  printf("initialization not required on windows yet.");
  // exit(1);
#endif
}

/*
 * perform cleanup of library components.
 * call this whenever your program closes. only use once.
 *
 * if this function call is skipped (e.g. premature exit due to crash),
 * users may have to restart their terminal to restore normal function.
 */
void term_cleanup() {
#if defined(__unix__) || defined(__APPLE__)
  // reset to initial attributes
  *terminal_attrs = *initial_attrs;
  set_terminal_attrs();
  // destroy structs
  delete terminal_attrs;
  delete initial_attrs;
#elif defined(_WIN32)
  printf("cleanup not required on windows yet.");
#endif
}

#endif