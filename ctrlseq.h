#include <iostream>

#ifndef CTRLSEQ_H
#define CTRLSEQ_H

#define BEL "\007"
#define SP " "
#define ESC "\033"
#define DCS ESC "P"
#define APC ESC "_"
#define CSI ESC "["
#define OSC ESC "]"
#define ST ESC "\\"

// misc

#define CLEAR ESC "c"   // clear the screen
#define SAVE ESC "7"    // save position
#define RESTORE ESC "8" // go to saved position
#define ENABLE_INSERT                                                          \
  CSI "2"                                                                      \
      "~"
// set window title to str
#define SET_WINDOW_TITLE(str)                                                  \
  OSC "2"                                                                      \
      ";" #str ST

// DECSET and DECRST functions
// documentation for DECSET and DECRST here:
// https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#:~:text=Automatic%20Newline%20(LNM).-,CSI%20%3F%20Pm%20h,-DEC%20Private%20Mode
// https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#:~:text=Normal%20Linefeed%20(LNM).-,CSI%20%3F%20Pm%20l,-DEC%20Private%20Mode

// DEC private mode set
#define DECSET(n) CSI "?" #n "h"
// DEC private mode reset
#define DECRST(n) CSI "?" #n "l"

#define SHOW_CURSOR DECSET(25)
#define HIDE_CURSOR DECRST(25)
#define SHOW_SCROLLBAR DECSET(30)
#define HIDE_SCROLLBAR DECRST(30)
#define USE_ALT_BUFFER DECSET(1049)
#define USE_MAIN_BUFFER DECRST(1049)

// xterm window manip functions

// perform an xterm window operation
#define XTWINOPS(n, p1, p2) CSI #n ";" #p1 ";" #p2 "t"
// de-minimize terminal
#define DEMINIMIZE XTWINOPS(1)
// minimize terminal
#define MINIMIZE XTWINOPS(2)
// move terminal to (x, y)
#define MOVE_TERMINAL(x, y) XTWINOPS(3, x, y)
// resize terminal to given height and width in pixels
// (omit parameter to keep current, 0 to use display dimension)
#define RESIZE_TERMINAL_PIXELS(height, width) XTWINOPS(4, height, width)
// push terminal to the front of the stacking order
#define PUSH_TO_FRONT XTWINOPS(5)
// push terminal to the back of the stacking order
#define PUSH_TO_BACK XTWINOPS(6)
// refresh terminal window
#define REFRESH_TERMINAL XTWINOPS(7)
// resize terminal to given height and width in characters
// (omit parameter to keep current, 0 to use display dimension)
#define RESIZE_TERMINAL_CHARS(height, width) XTWINOPS(8, height, width)
// unmaximize terminal
#define UNMAXIMIZE XTWINOPS(9, 0)
// maximize terminal
#define MAXIMIZE XTWINOPS(9, 1)
// maximize terminal vertically
#define MAXIMIZE_VERTICALLY XTWINOPS(9, 2)
// maximize terminal horizontally
#define MAXIMIZE_HORIZONTALLY XTWINOPS(9, 3)
// undo fullscreen
#define UNFULSCREEN XTWINOPS(10, 0)
// enable fullscreen
#define FULLSCREEN XTWINOPS(10, 1)
// toggle fullscreen
#define TOGGLE_FULLSCREEN XTWINOPS(10, 2)

// CSI functions

// unused
// request device attributes (tertiary)
// would return terminal identifier
// #define DEVICE_ATTR CSI ">" "c"
// set cursor column (default = [row, 1])
// #define CURS_COL_ABS(n) CSI #n "`" // duplicate of CURS_COL
// set horizontal and vertical position (duplicate of CURS_POS)
// #define HORIZ_VERT_POS(row, column) CSI #row ";" #column "f"

// insert n blank characters (default = 1)
#define INSERT_BLANKS(n) CSI #n "@"
// shift text left by n positions (default = 1)
#define SHIFT_LEFT(n) CSI #n SP "@"
// shift text right by n positions (default = 1)
#define SHIFT_RIGHT(n) CSI #n SP "A"
// shift cursor up by n positions (default = 1)
#define CURS_UP(n) CSI #n "A"
// shift cursor down by n positions (default = 1)
#define CURS_DOWN(n) CSI #n "B"
// shift cursor right by n positions (default = 1)
#define CURS_RIGHT(n) CSI #n "C"
// shift cursor left by n positions (default = 1)
#define CURS_LEFT(n) CSI #n "D"
// shift cursor n new lines down (default = 1)
#define CURS_NL(n) CSI #n "E"
// shift cursor n new lines up (default = 1)
#define CURS_PRE(n) CSI #n "F"
// set cursor to column x (default = [row, 1])
#define CURS_COL(column) CSI #column "G"
// set cursor column relative to current position (default = [row, col + 1])
#define CURS_COL_REL(x) CSI #x "a"
// set cursor to line y (default = [1, col])
#define CURS_LINE(y) CSI #y "d"
// set cursor line relative to current line (default = [row+1, col])
#define CURS_LINE_REL(y) CSI #y "e"
// set cursor position to [row, column]
#define CURS_POS(row, column) CSI #row ";" #column "H"
// shift cursor right by n tabs (default = 1)
#define CURS_SHIFT_TAB_RIGHT(n) CSI #n "I"
// shift cursor left by n tabs (default = 1)
#define CURS_SHIFT_TAB_LEFT(n) CSI #n "Z"
// erase in display, based on the value of e:
// 0 -> below (default)
// 1 -> above
// 2 -> all
// 3 -> saved lines
#define ERASE_IN_DISPLAY(e) CSI #e "J"
// erase in display, based on the value of e:
// 0 -> selective below (default)
// 1 -> selective above
// 2 -> selective all
// 3 -> selective saved lines
#define SELECTIVE_ERASE_IN_DISPLAY(e) CSI "?" #e "J"
// erase in line, based on the value of e:
// 0 -> right (default)
// 1 -> left
// 2 -> all
#define ERASE_IN_LINE(e) CSI #e "K"
// erase in line, based on the value of e:
// 0 -> selective right (default)
// 1 -> selective left
// 2 -> selective all
#define SELECTIVE_ERASE_IN_LINE(e) CSI "?" #e "K"
// insert n lines, pushing any lines including this one downwards and
// putting the cursor at the start of the line (default = 1)
#define INSERT_LINES(n) CSI #n "L"
// delete n lines including this one, pulling any lines below upwards and
// putting the cursor at the start of the line (default = 1)
#define DELETE_LINES(n) CSI #n "M"
// delete n characters (default = 1)
#define DELETE_CHARS(n) CSI #n "P"
// scroll up n lines (default = 1)
#define SCROLL_UP(n) CSI #n "S"
// scroll down n lines (default = 1)
#define SCROLL_DOWN(n) CSI #n "T"
// erase n character (default = 1)
#define ERASE_CHARS(n) CSI #n "X"
// set scrolling region from top to bottom (default = whole screen)
#define SET_SCROLLING_REGION(top, bottom) CSI #top ";" #bottom "r"

// character attributes

// set text to normal
#define SET_NORMAL                                                             \
  CSI "0"                                                                      \
      "m"
// set text to bold
#define SET_BOLD                                                               \
  CSI "1"                                                                      \
      "m"
// set text to faint
#define SET_FAINT                                                              \
  CSI "2"                                                                      \
      "m"
// set text to italic
#define SET_ITALIC                                                             \
  CSI "3"                                                                      \
      "m"
// set text to underlined
#define SET_UNDERLINED                                                         \
  CSI "4"                                                                      \
      "m"
// set text to blink
#define SET_BLINK                                                              \
  CSI "5"                                                                      \
      "m"
// set text to inverse
#define SET_INVERSE                                                            \
  CSI "7"                                                                      \
      "m"
// set text to hidden
#define SET_HIDDEN                                                             \
  CSI "8"                                                                      \
      "m"
// set text to crossed out
#define SET_STRIKETHROUGH                                                      \
  CSI "9"                                                                      \
      "m"
// set text to doubly underlined
#define SET_DOUBLE_UNDERLINE                                                   \
  CSI "2"                                                                      \
      "1"                                                                      \
      "m"
// turn off bold and faint
#define UNSET_BOLD_FAINT                                                       \
  CSI "2"                                                                      \
      "2"                                                                      \
      "m"
// turn off italics
#define UNSET_ITALIC                                                           \
  CSI "2"                                                                      \
      "3"                                                                      \
      "m"
// turn off underline
#define UNSET_UNDERLINE                                                        \
  CSI "2"                                                                      \
      "4"                                                                      \
      "m"
// turn off blinking
#define UNSET_BLINKING                                                         \
  CSI "2"                                                                      \
      "5"                                                                      \
      "m"
// turn off inverse
#define UNSET_INVERSE                                                          \
  CSI "2"                                                                      \
      "7"                                                                      \
      "m"
// turn off hidden
#define UNSET_HIDDEN                                                           \
  CSI "2"                                                                      \
      "8"                                                                      \
      "m"
// turn off crossed out
#define UNSET_STRIKETHROUGH                                                    \
  CSI "2"                                                                      \
      "9"                                                                      \
      "m"
// set foreground color to black
#define FG_COLOR_BLACK                                                         \
  CSI "3"                                                                      \
      "0"                                                                      \
      "m"
// set foreground color to red
#define FG_COLOR_RED                                                           \
  CSI "3"                                                                      \
      "1"                                                                      \
      "m"
// set foreground color to green
#define FG_COLOR_GREEN                                                         \
  CSI "3"                                                                      \
      "2"                                                                      \
      "m"
// set foreground color to yellow
#define FG_COLOR_YELLOW                                                        \
  CSI "3"                                                                      \
      "3"                                                                      \
      "m"
// set foreground color to blue
#define FG_COLOR_BLUE                                                          \
  CSI "3"                                                                      \
      "4"                                                                      \
      "m"
// set foreground color to magenta
#define FG_COLOR_MAGENTA                                                       \
  CSI "3"                                                                      \
      "5"                                                                      \
      "m"
// set foreground color to cyan
#define FG_COLOR_CYAN                                                          \
  CSI "3"                                                                      \
      "6"                                                                      \
      "m"
// set foreground color to white
#define FG_COLOR_WHITE                                                         \
  CSI "3"                                                                      \
      "7"                                                                      \
      "m"
// set foreground color to default
#define FG_COLOR_DEFAULT                                                       \
  CSI "3"                                                                      \
      "9"                                                                      \
      "m"
// set background color to black
#define BG_COLOR_BLACK                                                         \
  CSI "4"                                                                      \
      "0"                                                                      \
      "m"
// set background color to red
#define BG_COLOR_RED                                                           \
  CSI "4"                                                                      \
      "1"                                                                      \
      "m"
// set background color to green
#define BG_COLOR_GREEN                                                         \
  CSI "4"                                                                      \
      "2"                                                                      \
      "m"
// set background color to yellow
#define BG_COLOR_YELLOW                                                        \
  CSI "4"                                                                      \
      "3"                                                                      \
      "m"
// set background color to blue
#define BG_COLOR_BLUE                                                          \
  CSI "4"                                                                      \
      "4"                                                                      \
      "m"
// set background color to magenta
#define BG_COLOR_MAGENTA                                                       \
  CSI "4"                                                                      \
      "5"                                                                      \
      "m"
// set background color to cyan
#define BG_COLOR_CYAN                                                          \
  CSI "4"                                                                      \
      "6"                                                                      \
      "m"
// set background color to white
#define BG_COLOR_WHITE                                                         \
  CSI "4"                                                                      \
      "7"                                                                      \
      "m"
// set background color to default
#define BG_COLOR_DEFAULT                                                       \
  CSI "4"                                                                      \
      "9"                                                                      \
      "m"
// set foreground color using r, g, and b values
#define FG_COLOR_RBG(r, g, b)                                                  \
  CSI "3"                                                                      \
      "8"                                                                      \
      ";"                                                                      \
      "2"                                                                      \
      ";" #r ";" #g ";" #b "m"
// set baground color using r, g, and b values
#define BG_COLOR_RBG(r, g, b)                                                  \
  CSI "4"                                                                      \
      "8"                                                                      \
      ";"                                                                      \
      "2"                                                                      \
      ";" #r ";" #g ";" #b "m"

#define QUICK_PRINT(args) std::cout << args;
#define PRINT_TEST(name, args) QUICK_PRINT(name " / " args " || ")
void feature_test() {
  // clear screen first
  QUICK_PRINT(CLEAR)
  // test save and restore
  PRINT_TEST("SAVE/RESTORE", "12345678" SAVE "~~" RESTORE "90")
  // insert blanks
  PRINT_TEST("BLANKS", "1234" INSERT_BLANKS(2) "78")
  // text shift left/right
  PRINT_TEST("TEXT SHIFT LEFT/RIGHT", "\n" SAVE "12345678" SHIFT_LEFT(
                                          2) "cont" RESTORE SHIFT_RIGHT(2) "\n")
  // cursor directions
  PRINT_TEST("CURSOR U/D/L/R", "UL" CURS_RIGHT() "UR" CURS_DOWN() CURS_LEFT(
                                   2) "LR" SAVE CURS_LEFT(5) "LL" RESTORE)
  // new lines
  PRINT_TEST("NEW LINES", CURS_NL(2) "2 down" CURS_PRE() "1 up" CURS_NL(
                              2) "2 down once more")
  // column manip
  PRINT_TEST("CURS COL", "\n"
                         "123" CURS_COL_REL(5) "90" CURS_COL() "abc45678"
                                                               "\n")
  // line manip
  PRINT_TEST("CURS LINE",
             "123" CURS_LINE_REL() "456" SAVE CURS_LINE() "~~~" RESTORE "\n")
  // position
  PRINT_TEST("POSITION", SAVE "look at the top left corner ;3" CURS_POS(
                             0, 0) "~~REPLACED~~" RESTORE "\n")
  // cursor shift left/right
  PRINT_TEST("CURS TAB LEFT/RIGHT",
             "\n" SAVE "0t" RESTORE CURS_SHIFT_TAB_RIGHT(2) SAVE
             "2t" RESTORE CURS_SHIFT_TAB_LEFT(1) "1t"
                                                 "\n")
  // erase functions
  PRINT_TEST("ERASE DISPLAY/LINE", "123" CURS_DOWN() "456" CURS_UP() SAVE
             "789" RESTORE ERASE_IN_DISPLAY(0) ERASE_IN_LINE(0))
  // insert/delete lines
  PRINT_TEST("INSERT/DELETE LINES",
             "\n"
             "only this line should be left" CURS_DOWN(
                 1) "this line should be "
                    "gone" CURS_DOWN(
                        1) "this as "
                           "wel"
                           "l" CURS_DOWN(1) "yet this one stays" CURS_UP(2)
                               DELETE_LINES(2) "aaaaaaaaaaaa" INSERT_LINES(
                                   2) "bbbbbbbbbbbb" CURS_DOWN(2))
  //
}

#endif