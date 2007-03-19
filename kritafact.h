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

#ifndef KRITAFACT_H
#define KRITAFACT_H

// quarl 2007-03-03 initial version

#include <qrect.h>

#include <kis_types.h>

#include "bwfactory.h"

using pagetools::BWFactory;
using pagetools::BWImage;

class KritaFactory: public BWFactory
{
public:
    KritaFactory(KisPaintDeviceSP src, const QRect& rect);
    virtual KSharedPtr<BWImage> create();
private:
    //GimpDrawable *drawable_;
    Q_INT32 mX;
    Q_INT32 mY;
    Q_INT32 mWidth;
    Q_INT32 mHeight;
    KisPaintDeviceSP mSrc;
};

#endif//KRITAFACT_H
