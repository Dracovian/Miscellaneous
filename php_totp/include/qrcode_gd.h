#ifndef __QRCODE_GD_H
#define __QRCODE_GD_H

#include "qrcode.h"
#include "global.h"

typedef struct _ImgStruct {
	byte *data;
	int size;
} QRImage;

void get_qrcode(QRCode *, QRImage *, long);

#endif // __QRCODE_GD_H
