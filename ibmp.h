#ifndef IBMP_H
#define IBMP_H

#include "color.h"
#include "fstream"
#include "image.h"

struct BMPFiler {
  static const int file_header_size = 14;
  static const int bmp_header_size  = 40;
  static const int pixel_size       = 3;

  Image const& image; // reference to image to be written

  BMPFiler(Image const& image);

  void write(std::fstream& out);

  void write_file_header(std::fstream& out);

  void write_bmp_header(std::fstream& out);

  void write_pixel_data(std::fstream& out);

  int image_padding_size();

  int image_data_size();

  int file_size();
};

#endif
