
#include <fstream>

#include "color.h"
#include "ibmp.h"
#include "image.h"
#include <iostream>

void test()
{
  Image i{4, 4};
  i.fill(Color{0, 0, 0}, ImageError::Ignore());
  i.set_pixel(0, 0, Color{255, 0, 0}, ImageError::Ignore());
  i.set_pixel(0, 1, Color{255, 0, 0}, ImageError::Ignore());
  i.set_pixel(0, 2, Color{255, 0, 0}, ImageError::Ignore());
  i.set_pixel(0, 3, Color{255, 0, 0}, ImageError::Ignore());

  std::fstream f{"test.bmp", std::ios::binary | std::ios::out};
  i.write<BMPFiler>(f);
  f.close();
}

Image random_image(int w, int h, int depth)
{
  if (depth < 1)
    depth = 2;

  Image img{w, h};

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      byte r = (((double) (rand() % depth)) / (double) depth) * 255;
      byte g = (((double) (rand() % depth)) / (double) depth) * 255;
      byte b = (((double) (rand() % depth)) / (double) depth) * 255;
      img.set_pixel(j, i, Color{r, g, b}, ImageError::Ignore());
    }
  }

  return img;
}

void read_input()
{

  int read_count = 0;
  int max_cols   = 0;
  int cols       = 0;
  int lines      = 0;
  int cin;

  std::vector<char> buf{};

  while (std::cin.good() && !std::cin.eof()) {
    std::cin >> cin;
    read_count++;
    if (cin == '\n') {
      lines++;
      if (cols > max_cols) {
        max_cols = cols;
      }
      cols = 0;
    } else {
      cols++;
    }
    buf.push_back(cin);
  }

  printf("Got %d, %d", max_cols, lines);

  Image img{max_cols, lines};
  printf("Image: %d, %d\n", img.width, img.height);

  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < max_cols; j++) {
      Color clr = buf[i * max_cols + j] == '1' ? white : black;
      img.set_pixel(j, i, clr, ImageError::Ignore());
      printf("Color at %d, %d = Color(%d, %d, %d)\n", j, i, clr.red, clr.green, clr.blue);
    }
  }

  std::fstream f{"test.bmp", std::ios::binary | std::ios::out};
  img.write<BMPFiler>(f);
  f.close();
}

int main()
{
  Image i = Image{5, 5};

  i.fill(white, ImageError::Ignore());
  i.fill(black, ImageError::Ignore());

  i.set_pixel(2, 2, white, ImageError::Ignore());

  std::fstream f{"test.bmp", std::ios::out | std::ios::binary};
  i.write<BMPFiler>(f);

  f.close();
  return 0;
}
