#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>

#ifndef TERMCTL_H
#define TERMCTL_H

// !~~~ NON-TOGGLEABLE FEATURES ~~~!
// these are features that have a return value
// most of these are implemented using:
//   sys/ioctl.h on linux and posix systems

/*
 * get the dimensions of the terminal window, in characters
 *
 * @param cols pointer to an `int`, where the horizontal size will be stored
 * @param rows pointer to an `int`, where the vertical size will be stored
 */
void get_window_size(int *cols, int *rows) {
  struct winsize s = {};
  ioctl(0, TIOCGWINSZ, &s);
  *cols = s.ws_col;
  *rows = s.ws_row;
}

// !~~~ TOGGLEABLE FEATURES ~~~!
// these are features that enable or disable a certain terminal effect
// most of these are implemented using:
//   termios.h and ctrlseq.h on linux and posix systems

// start of termios function macros
// clang-format off

// storage for current terminal attributes
termios *terminal_attrs = new termios;

termios *initial_attrs = new termios;

// get current terminal attributes
#define get_terminal_attrs() tcgetattr(0, terminal_attrs);

// set current terminal attributes
#define set_terminal_attrs() tcsetattr(0, TCSANOW, terminal_attrs);

#define enable_feature(feat) terminal_attrs->c_lflag |= feat; set_terminal_attrs();
#define disable_feature(feat) terminal_attrs->c_lflag &= ~feat; set_terminal_attrs();
#define toggle_feature(feat) terminal_attrs->c_lflag ^= feat; set_terminal_attrs();

// enable echo to the terminal
#define enable_echo() enable_feature(ECHO);
// disable echo to the terminal
#define disable_echo() disable_feature(ECHO);
// toggle echo to the opposite of its current state
#define toggle_echo() toggle_feature(ECHO);


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

#endif // TERMCTL_H