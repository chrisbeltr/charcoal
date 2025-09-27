#include "window.h"

using namespace charcoal;

std::vector<CHAR_TYPE> window::default_border = {L'┏', L'┓', L'┗',
                                                 L'┛', L'━', L'┃'};

int window::resize(const int &width, const int &height) {
  this->width = width;
  this->height = height;
  this->buffer.resize(width * height);
  return 0;
}

int window::set_border(const CHAR_TYPE &ul, const CHAR_TYPE &ur,
                       const CHAR_TYPE &ll, const CHAR_TYPE &lr,
                       const CHAR_TYPE &horiz, const CHAR_TYPE &vert) {
  return 0;
}
int window::set_border(const std::vector<CHAR_TYPE> &chars) { return 0; }
int window::set_border(const std::shared_ptr<std::vector<CHAR_TYPE>> &chars) {
  return 0;
}

#include <cstdint>
#include <cstdio>
int main() {
  window w = window();
  window t = window(2, 4);

  w.resize(200, 50);
  int x = 6;
  int y = 7;
  t.resize(x, y);

  printf("%llud\n", sizeof(wchar_t));

  w.set_border(w.default_border);
}