#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <gd.h>

#include "qrcode_gd.h"

void get_qrcode(QRCode *qrcode, QRImage *image, long scale) {
	gdImagePtr img;
	int black, white, size;

	size  = qrcode->size * scale;
	img   = gdImageCreate(size, size);	
	black = gdImageColorAllocate(img, 0, 0, 0);
	white = gdImageColorAllocate(img, 255, 255, 255);
	
	gdImageFilledRectangle(img, 0, 0, size, size, white);
	for (int y = 0; y < size; y += scale) {
		for (int x = 0; x < size; x += scale) {
			if (qrcode_getModule(qrcode, x / scale, y / scale))
				gdImageFilledRectangle(img, x, y, x + scale, y + scale, black);
			else
				gdImageFilledRectangle(img, x, y, x + scale, y + scale, white);
		}
	}

	int outsize = 0;
	void *imagedata = gdImagePngPtr(img, &outsize);
	
	image->data = imagedata;
	image->size = outsize;
}
