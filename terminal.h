#include "termctl.h"

/*
 * perform initialization of necessary library components.
 * call this at the start of your program. only use once.
 */
void term_init() {
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
}

/*
 * perform cleanup of library components.
 * call this whenever your program closes. only use once.
 *
 * if this function call is skipped (e.g. premature exit due to crash),
 * users may have to restart their terminal to restore normal function.
 */
void term_cleanup() {
  // reset to initial attributes
  *terminal_attrs = *initial_attrs;
  set_terminal_attrs();
  // destroy structs
  delete terminal_attrs;
  delete initial_attrs;
}