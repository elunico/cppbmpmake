#include "ibmp.h"
#include <ostream>

BMPFiler::BMPFiler(Image const& image): image(image) {}

void BMPFiler::write(std::fstream& out)
{
  write_file_header(out);
  write_bmp_header(out);
  write_pixel_data(out);
}

void BMPFiler::write_file_header(std::fstream& out)
{
  out.put('B');
  out.put('M');
  out.put(file_size() >> 24);
  out.put(file_size() >> 16);
  out.put(file_size() >> 8);
  out.put(file_size());
  out.put(0);
  out.put(0);
  out.put(0);
  out.put(0);
  out.put(file_header_size);
  out.put(file_header_size >> 8);
  out.put(0);
  out.put(0);
}

void BMPFiler::write_bmp_header(std::fstream& out)
{
  out.put(40);
  out.put(0);
  out.put(0);
  out.put(0);
  out.put(image.width >> 24);
  out.put(image.width >> 16);
  out.put(image.width >> 8);
  out.put(image.width);
  out.put(image.height >> 24);
  out.put(image.height >> 16);
  out.put(image.height >> 8);
  out.put(image.height);
  out.put(0);
  out.put(1);
  out.put(0);
  out.put(24);
  for (int i = 16; i < 40; i++) {
    out.put(0);
  }
}

void BMPFiler::write_pixel_data(std::fstream& out)
{
  for (int i = image.height - 1; i >= 0; i--) {
    for (int j = image.width - 1; j >= 0; j--) {
      Color c = image.get_pixel(j, i, ImageError::Ignore());
      out.put(c.blue);
      out.put(c.green);
      out.put(c.red);
    }
  }
}

int BMPFiler::image_padding_size()
{
  return (4 - ((image.width * 3) % 4)) % 4;
}

int BMPFiler::image_data_size()
{
  return image_padding_size() * image.height + image.width * image.height * (int) sizeof(Color);
}

int BMPFiler::file_size()
{
  return file_header_size + bmp_header_size + image_data_size();
}
