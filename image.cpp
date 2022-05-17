#include "image.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <ios>

Image::Image(int w, int h): width(w), height(h), pixels(w * h)
{
  if (w < 1 || h < 1)
    throw "Invalid image size";
}

/* static */ ImageError& ImageError::Ignore()
{
  DONTCARE.isError = false;
  DONTCARE.reason  = I_SUCCESS;
  DONTCARE.file    = "";
  DONTCARE.line    = 0;
  return DONTCARE;
}

/* static */ ImageError ImageError::DONTCARE = {false, (I_RESULT) 0, "", 0};

void ImageError::clear() noexcept
{
  isError = false;
  reason  = I_SUCCESS;
  file    = "";
  line    = 0;
}

bool Image::valid_coords(int x, int y) const noexcept
{
  return valid_coords(x, y, ImageError::Ignore());
}

bool Image::valid_coords(int x, int y, ImageError& error) const noexcept
{
  if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
    error.isError = true;
    error.reason  = I_FAILURE_INVALID_COORD;
    error.file    = __FILE__;
    error.line    = __LINE__;
    return false;
  }
  return true;
}

Color Image::get_pixel(int x, int y, ImageError& error) const noexcept
{
  if (!valid_coords(x, y, error))
    return black;

  return this->pixels[y * this->width + x];
}

void Image::set_pixel(int x, int y, Color const c, ImageError& error) noexcept
{
  if (!valid_coords(x, y, error))
    return;

  this->pixels[y * this->width + x] = c;
}

void Image::fill(Color const pix, ImageError& error) noexcept
{
  for (int i = 0; i < this->height; i++)
    for (int j = 0; j < this->width; j++)
      this->set_pixel(i, j, pix, error);
}

template<typename R, typename A, typename B>
std::function<R(A, B)> unpair(std::function<R(std::pair<A, B>)> f) {
  return [&f](A a, B b) { return f(std::make_pair(a, b)); };
}