#ifndef __BITUTIL_H__
#define __BITUTIL_H__

/*
    This file is part of Page Layout Detection Tools.

    This code is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this code; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

namespace pagetools{

class BitUtil{
public:
    static const unsigned char *bitcount();
    static const unsigned char *invbits();

private:
    static BitUtil *instance_;
    unsigned char *bitcount_;
    unsigned char *invbits_;
    BitUtil();
};

}// namespace pagetools

#endif//__BITUTIL_H__
