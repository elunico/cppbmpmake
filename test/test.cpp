//
// Created by Thomas Povinelli on 5/9/22.
//

#include "../color.h"
#include "../ibmp.h"
#include "../image.h"
#include <criterion/criterion.h>

TestSuite(COLOR);

Test(COLOR, test_Color_make_color)
{
  Color c{0, 0, 0};
  cr_assert_eq(c.red, 0);
  cr_assert_eq(c.green, 0);
  cr_assert_eq(c.blue, 0);
}

Test(COLOR, test_Color_make_color_different)
{
  Color c{255, 127, 12};
  cr_assert_eq(c.red, 255);
  cr_assert_eq(c.green, 127);
  cr_assert_eq(c.blue, 12);
}

Test(COLOR, test_Color_make_color_max)
{
  Color c{255, 255, 255};
  cr_assert_eq(c.red, 255);
  cr_assert_eq(c.green, 255);
  cr_assert_eq(c.blue, 255);
}

TestSuite(IMAGE);

Test(IMAGE, test_I_init_image)
{
  Image img{10, 10};
  cr_assert_eq(img.width, 10);
  cr_assert_eq(img.height, 10);
  //  cr_assert_neq(img.pixels, NULL);
}

Test(IMAGE, test_I_init_image_different)
{
  Image img{20, 20};
  cr_assert_eq(img.width, 20);
  cr_assert_eq(img.height, 20);
  //  cr_assert_neq(img.pixels, NULL);
}

Test(IMAGE, test_I_init_image_invalid_num)
{
  Image img{0, 0};
}


Test(IMAGE, test_I_get_pixel)
{
  Image img{10, 10};
  img.set_pixel(0, 0, Color{0, 0, 0}, ImageError::Ignore());
  img.set_pixel(1, 0, Color{255, 255, 255}, ImageError::Ignore());
  Color pix = img.get_pixel(0, 0, ImageError::Ignore());
  cr_assert_eq(pix.red, 0);
  cr_assert_eq(pix.green, 0);
  cr_assert_eq(pix.blue, 0);
  pix = img.get_pixel(1, 0, ImageError::Ignore());
  cr_assert_eq(pix.red, 255);
  cr_assert_eq(pix.green, 255);
  cr_assert_eq(pix.blue, 255);
}

Test(IMAGE, test_I_set_pixel_outofbounds)
{
  Image      img{10, 10};
  ImageError error{};
  img.set_pixel(-1, 0, Color{0, 0, 0}, error);
  cr_assert_eq(error.reason, I_FAILURE_INVALID_COORD);
  error.clear();
  img.set_pixel(0, -1, Color{0, 0, 0}, error);
  cr_assert_eq(error.reason, I_FAILURE_INVALID_COORD);
  error.clear();
  img.set_pixel(10, 0, Color{0, 0, 0}, error);
  cr_assert_eq(error.reason, I_FAILURE_INVALID_COORD);
  error.clear();
  img.set_pixel(0, 10, Color{0, 0, 0}, error);
  cr_assert_eq(error.reason, I_FAILURE_INVALID_COORD);
  error.clear();
}

TestSuite(BMP);

Test(BMP, test_B_image_padding_size)
{
  {
    Image    img{10, 10};
    BMPFiler filer{img};
    cr_assert_eq(filer.image_padding_size(), 2);
  }

  {
    Image    img{4, 4};
    BMPFiler filer{img};
    cr_assert_eq(filer.image_padding_size(), 0);
  }

  {
    Image    img{1, 1};
    BMPFiler filer{img};
    cr_assert_eq(filer.image_padding_size(), 1);
  }

  {
    Image    img{259, 259};
    BMPFiler filer{img};
    cr_assert_eq(filer.image_padding_size(), 3);
  }
}

Test(BMP, test_B_file_header_size)
{
  cr_assert_eq(BMPFiler::file_header_size, 14);
}

Test(BMP, test_B_bmp_header_size)
{
  cr_assert_eq(BMPFiler::bmp_header_size, 40);
}

Test(BMP, test_B_image_data_size)
{
  Image    img{10, 10};
  BMPFiler filer{img};
  cr_assert_eq(filer.image_data_size(), img.height * img.width * 3 + filer.image_padding_size() * 10);
}

Test(BMP, test_B_file_size)
{
  Image    img{10, 10};
  BMPFiler filer{img};

  cr_assert_eq(filer.file_size(), filer.file_header_size + filer.bmp_header_size + img.width * img.height * 3 +
                                      filer.image_padding_size() * img.height);
}
