/*
 * This file is part of Krita
 *
 * Copyright (c) 2007 Michael Thaler <michael.thaler@physik.tu-muenchen.de>
 *
 * ported from the deskew gimp plugin
 * Copyright (C) 2007 Karl Chen <quarl@cs.berkeley.edu>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


// TODO: remove that
#define LCMS_HEADER <lcms.h>
// TODO: remove it !

#include <kdebug.h>

#include <kis_iterators_pixel.h>

#include "kritafact.h"
//#include "deskew.h"

KritaFactory::KritaFactory(KisPaintDeviceSP src, const QRect& rect)
{
    mX = rect.x();
    mY = rect.y();
    mWidth = rect.width();
    mHeight = rect.height();
    mSrc = src;
    kdDebug() << "mX:" << mX << " mY: " << mY << " mWidth: " << mWidth << " mHeight:" << mHeight << endl;
}

// read a BWImage (packed black&white image) from Gimp

KSharedPtr<BWImage>
KritaFactory::create() {

    // quarl 2007-03-03
    //     TODO: this could be a parameter, but for now I don't think we need it.

    Q_INT32 black_threshold = 100;
    Q_INT32 bpp = mSrc->pixelSize();

    KSharedPtr<BWImage> image = KSharedPtr<BWImage>(new BWImage(mWidth, mHeight));

    // A pixel in a BWImage is one bit. The bytewidth is the number of bytes of one row in the
    // image. It is given by bytewidth=(w+7)/8;
    unsigned int bytewidth = image->bytewidth();
    //padmask are the remaining bits in the last byte of the row that are not used
    unsigned char padmask=0xFF<<((mWidth+7)%8);

    // quarl 2007-03-03
    //     Round up to nearest multiple of 8, so that in the loop below we
    //     don't have to worry about going over.  We don't care what the
    //     values.

    // w+8 is poor man's round-up-to-nearest-multiple-of-8 (fixme)
    Q_UINT8 *row = new Q_UINT8[bpp*(mWidth + 8)];
    
    //iterate over all rows in the image
    for (Q_INT32 y = mY; y < mY + mHeight; y++) {
        //get a pointer to the current row of the BWImage
        Q_UINT8* b_row = image->scanline(y);
        //read data from the current row of the src layer
        mSrc->readBytes(row, mX, y, mWidth, 1);
        //iterate over all bytes of the current row of the BWImage
        for (int jb = 0; jb < bytewidth; ++jb) {
            unsigned char byte = 0;
            //the index of the first pixel of the current byte of the current row of the BWImage
            unsigned int j = jb * 8; 
            for (int ji = 0; ji < 8; ++ji, ++j) { //iterate over the bytes of the image
                // unsigned int bpixel = 0;

                // quarl 2007-03-03
                //     Very crappy way to convert RGB/grayscale to B&W, but
                //     the results of running Radon on it are fine, and it's
                //     cheap.
                //iterate over the bytes of the source image
                Q_INT32 color[3];
                QColor c;
                //kdDebug() << "r: " << (int)bytes[0] << " g: " << (int)bytes[1] << " b: " << (int)bytes[2] << endl;
                mSrc->colorSpace()->toQColor(row + bpp * j, &c);
                color[0] = c.red();
                color[1] = c.green();
                color[2] = c.blue();
                
                for (int k = 0; k < 3; ++k) {
                    if (color[k] < black_threshold) {
                        // black pixel => set this bit

                        // bpixel = 1;
                        byte |= (1 << ji);//set bit
                        break;
                    }
                }
            }
            b_row[jb] = byte;
        }
        //add pad mask at the end
        b_row[bytewidth-1] &= padmask;
    }

    return image;
}
