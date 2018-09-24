def decompose_frame(frame):
  '''Decompose Frame Bits.

  2bit and 1bit images are encoded and written to Registers at 0x10, 0x13, 0x15, and 0x16.

  Basically, each byte contains either four pixels for 2bit images, or 8 pixels for 1bit images.
  The schemes are:

  - DTM1 - 2bit image goes in _old_ `SRAM`.
  - DTM2 - 2bit image goes in _new_ `SRAM`.
  - DTM3 - 1bit image (8 pixel per byte) goes to _old_ `SRAM`.
  - DTM4 - 1bit image (8 pixel per byte) goes to _new_ `SRAM`.

  The encoding scheme for register 0x10 is as following:

  ┌───┐ ┌───┬───┐┌───┬───┐┌───┬───┐┌───┬───┐
  │ 1 │ │   │   ││   │   ││   │   ││   │   │
  └───┘ └───┴───┘└───┴───┘└───┴───┘└───┴───┘
   DC   ─ 7 ─── 8 Bits Transmission ──── 0 ─

        ─────────                            Px (n-4)
                 ─────────                   Px (n-3)
                          ─────────          Px (n-2)
                                   ───────── Px (n-1)

  Each data byte is shifted left by two bits to obtain the complete frame.
  '''
  # XXX: We have magic numbers here!
  c_pxs = np.zeros(240 * 240)

  buff_size = len(frame)

  if buff_size == 14400:
    # We have DTM1 or DTM2 with 2 bits image.
    # The Composed image is 4x the size of frame.
    for i in range(4):
      c_pxs[3 - i::4] = (frame >> (2 * i)) & 0b11
  elif buff_size == 7200:
    # We have DTM3 or DTM4 with 1 bit image. Hence there are 8 pixels per byte.
    for i in range(8):
      c_pxs[7 - i::8] = (frame >> i & 0b1)

  return c_pxs.reshape(240, 240)


def bin_pixel_value(value, depth=2):
  '''Bin a pixel value to the specified bits'''

  if value < 0.1:
    return 0b00
  elif value < 0.6:
    return 0b01
  elif value < 0.9:
    return 0b10
  else:
    return 0b11

def compose_byte(pxs):
  # pxs is the 4 pixel chunk from flat frame
  composed = 0
  for i, px in enumerate(pxs):
    composed = (composed << 2) | bin_pixel_value(px)

  return composed


def encode_frame(frame):
  '''Encode a frame
  The encoding scheme was described in `decompose_frame`. This function
  does the reverse.

  To properly encode a greyscale image, we would need to replace pixel values
  using a lookup table.

  Since we have two possible image schemes, at 2bits and 1bit, there'll be either
  4 or 8 pixel data packed into single frame.

  For 1bit images, the scheme is pretty simple: We use a binary image.
  Given a 2D image buffer, we stack the rows horizontally and then take 8 elements
  from the beginning and pack.

  The MSB in the packed byte is the first element, and so on.

  For 2 bit images, we define a simple lookup table for pixel values:

  `0b00` if value < 0.1
  `0b01` if value < 0.6
  `0b10` if value < 0.9
  `0b11` otherwise.


  ┌───┐ ┌───┬───┐┌───┬───┐┌───┬───┐┌───┬───┐
  │ 1 │ │   │   ││   │   ││   │   ││   │   │
  └───┘ └───┴───┘└───┴───┘└───┴───┘└───┴───┘
   DC   ─ 7 ─── 8 Bits Transmission ──── 0 ─

        ─────────                            Px (n-4)
                 ─────────                   Px (n-3)
                          ─────────          Px (n-2)
                                   ───────── Px (n-1)

  '''
  # XXX: We have magic numbers here!
  framebuffer = np.zeros(120 * 120)

  # Flatten the frame and create a
  fgrps = np.split(frame.ravel(), 14400)

  return [compose_byte(x) for x in fgrps]


def serialize_frame(uid, image):
  serialized = (py_(image)
    .thru(encode_frame)
    .map(lambda byte: f'0x{byte:02x}')
    .thru(lambda x: pformat(x, compact=True, indent=2))
    .replace('[', ' ')
    .replace(']', ',')
    .replace('\'', '')
    .value())

  key = py_(uid).snake_case().to_upper().value()

  declaration = f'''
unsigned short BMP_{key}[] = {{
{serialized}
}};
  '''

  return declaration


header_fmt = '''
#ifndef __BITMAP_H__
#define __BITMAP_H__

{payload}

#endif
'''
