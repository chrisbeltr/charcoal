#include <memory>
#include <vector>

namespace charcoal {

#define CHAR_TYPE char16_t

class window {
private:
  // private data

  int width;
  int height;

  std::vector<CHAR_TYPE> buffer;
  std::vector<CHAR_TYPE> border;

  using children_list = std::vector<std::shared_ptr<window>>;
  children_list children;

public:
  // public data

  static std::vector<CHAR_TYPE> default_border;

public:
  // functions

  window(const int &width, const int &height) {
    this->width = width;
    this->height = height;

    this->buffer.reserve(width * height);
  }
  window() {
    // window with minimum height while leaving space for a border
    window(1, 1);
  }

  int resize(const int &width, const int &height);
  int set_border(const CHAR_TYPE &ul, const CHAR_TYPE &ur, const CHAR_TYPE &ll,
                 const CHAR_TYPE &lr, const CHAR_TYPE &horiz,
                 const CHAR_TYPE &vert);
  int set_border(const std::vector<CHAR_TYPE> &chars);
  int set_border(const std::shared_ptr<std::vector<CHAR_TYPE>> &chars);
};

} // namespace charcoal