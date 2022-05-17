#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <fstream>
#include <vector>
#include <string>

typedef enum {
  I_SUCCESS                = 0,
  I_FAILURE_INVALID_NUM    = 1,
  I_FAILURE_INVALID_IMG    = 2,
  I_FAILURE_INVALID_COORD  = 3,
  I_FAILURE_INVALID_COLOR  = 4,
  I_FAILURE_INVALID_BUFFER = 5
} I_RESULT;

struct ImageError {
  bool        isError;
  I_RESULT    reason;
  std::string file;
  int         line;

  void clear() noexcept;

  static ImageError& Ignore();

private:
  static ImageError DONTCARE;
};

struct Image {
  int                width;
  int                height;
  std::vector<Color> pixels;

  Image(int w, int h);

  void  fill(Color const pix, ImageError& error) noexcept;
  Color get_pixel(int x, int y, ImageError& error) const noexcept;
  void  set_pixel(int x, int y, Color const c, ImageError& error) noexcept;

  template <typename Writer>
  void write(std::fstream& os) const {
    Writer{*this}.write(os);
  }

  bool valid_coords(int x, int y, ImageError& error) const noexcept;
  bool valid_coords(int x, int y) const noexcept;
};

#endif
