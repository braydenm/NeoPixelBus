/*-------------------------------------------------------------------------
HD108ColorFeatures provides feature classes to descriF color order and
color depth for NeoPixelBus template class when used w. 16bit HD108 strips

Written by Brayden McLean

-------------------------------------------------------------------------
This file is part of a modified NeoPixelBus library.

NeoPixelBus is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

NeoPixelBus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with NeoPixel.  If not, see
<http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------*/
#pragma once

class HD1083Elements
{
public:
    static const size_t PixelSize = 8; // still requires 4 to be sent

    static uint8_t* getPixelAddress(uint8_t* pPixels, uint16_t indexPixel)
    {
        return pPixels + indexPixel * PixelSize;
    }
    static const uint8_t* getPixelAddress(const uint8_t* pPixels, uint16_t indexPixel)
    {
        return pPixels + indexPixel * PixelSize;
    }

    static void replicatePixel(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        while (pPixelDest < pEnd) //do this the same number of times as there are pixels
        {
            *pPixelDest++ = pPixelSrc[0];
            *pPixelDest++ = pPixelSrc[1];
            *pPixelDest++ = pPixelSrc[2];
            *pPixelDest++ = pPixelSrc[3];
            *pPixelDest++ = pPixelSrc[4];
            *pPixelDest++ = pPixelSrc[5];
            *pPixelDest++ = pPixelSrc[6];
            *pPixelDest++ = pPixelSrc[7];
        }
    }

    static void movePixelsInc(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
        }
    }

    static void movePixelsInc_P(uint8_t* pPixelDest, PGM_VOID_P pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        const uint8_t* pSrc = (const uint8_t*)pPixelSrc;
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
        }
    }

    static void movePixelsDec(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pDestBack = pPixelDest + (count * PixelSize);
        const uint8_t* pSrcBack = pPixelSrc + (count * PixelSize);
        while (pDestBack > pPixelDest)
        {
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
        }
    }

    typedef RgbColor ColorObject;
};

class HD1084Elements
{
public:
    static const size_t PixelSize = 8;

    static uint8_t* getPixelAddress(uint8_t* pPixels, uint16_t indexPixel) 
    {
        return pPixels + indexPixel * PixelSize;
    }
    static const uint8_t* getPixelAddress(const uint8_t* pPixels, uint16_t indexPixel)
    {
        return pPixels + indexPixel * PixelSize;
    }

    static void replicatePixel(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = pPixelSrc[0];
            *pPixelDest++ = pPixelSrc[1];
            *pPixelDest++ = pPixelSrc[2];
            *pPixelDest++ = pPixelSrc[3];
        }
    }

    static void movePixelsInc(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
        }
    }

    static void movePixelsInc_P(uint8_t* pPixelDest, PGM_VOID_P pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        const uint8_t* pSrc = (const uint8_t*)pPixelSrc;
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
        }
    }

    static void movePixelsDec(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pDestBack = pPixelDest + (count * PixelSize);
        const uint8_t* pSrcBack = pPixelSrc + (count * PixelSize);
        while (pDestBack > pPixelDest)
        {
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
        }
    }

    typedef RgbwColor ColorObject;
};


class HD1083ElementsNoSettings : public HD1083Elements
{
public:
    typedef NeoNoSettings SettingsObject;
    static const size_t SettingsSize = 0;

    static void applySettings(uint8_t*, const SettingsObject&)
    {
    }

    static uint8_t* pixels(uint8_t* pData)
    {
        return pData;
    }

    static const uint8_t* pixels(const uint8_t* pData)
    {
        return pData;
    }
};

class HD1084ElementsNoSettings : public HD1084Elements
{
public:
    typedef NeoNoSettings SettingsObject;
    static const size_t SettingsSize = 0;

    static void applySettings(uint8_t*, const SettingsObject&)
    {
    }

    static uint8_t* pixels(uint8_t* pData)
    {
        return pData;
    }

    static const uint8_t* pixels(const uint8_t* pData)
    {
        return pData;
    }
};

/* RGB Feature -- HD108s ship in RGB order */
class HD108RgbFeature : public HD1083ElementsNoSettings
{
public:
    static void applyPixelColor(uint8_t* pPixels, uint16_t indexPixel, ColorObject color)
    {
        uint8_t* p = getPixelAddress(pPixels, indexPixel);

        *p++ = 0xff; // brightness b/g/r at max for first 16 bits //1bbb bbgg gggr rrrr
        *p++ = 0xff; 

        *p++ = color.R;
        *p++ = 0x00; //Least significant 8 bits, currently not used.

        *p++ = color.G;
        *p++ = 0x00;

        *p++ = color.B;
        *p++ = 0x00;
    }

    static ColorObject retrievePixelColor(const uint8_t* pPixels, uint16_t indexPixel)
    {
        ColorObject color;
        const uint8_t* p = getPixelAddress(pPixels, indexPixel);

        p++; // ignore the first byte
        p++; // ignore the second byte
        color.R = *p++; *p++;
        color.G = *p++; *p++;
        color.B = *p;

        return color;
    }

    static ColorObject retrievePixelColor_P(PGM_VOID_P pPixels, uint16_t indexPixel)
    {
        ColorObject color;
        const uint8_t* p = getPixelAddress((const uint8_t*)pPixels, indexPixel);

        pgm_read_byte(p++); // ignore the first byte
        p++; // skip second byte
        color.R = pgm_read_byte(p++); p++;
        color.G = pgm_read_byte(p++); p++;
        color.B = pgm_read_byte(p);

        return color;
    }

};

// class HD108LrgbFeature : public HD1084ElementsNoSettings //not set up for 16bit yet
// {
// public:
//     static void applyPixelColor(uint8_t* pPixels, uint16_t indexPixel, ColorObject color)
//     {
//         uint8_t* p = getPixelAddress(pPixels, indexPixel);

//         *p++ = 0xE0 | (color.W < 31 ? color.W : 31); // upper three bits are always 111
//         *p++ = color.R;
//         *p++ = color.G;
//         *p = color.B;
//     }

//     static ColorObject retrievePixelColor(const uint8_t* pPixels, uint16_t indexPixel)
//     {
//         ColorObject color;
//         const uint8_t* p = getPixelAddress(pPixels, indexPixel);

//         color.W = (*p++) & 0x1F; // mask out upper three bits
//         color.R = *p++;
//         color.G = *p++;
//         color.B = *p;

//         return color;
//     }

//     static ColorObject retrievePixelColor_P(PGM_VOID_P pPixels, uint16_t indexPixel)
//     {
//         ColorObject color;
//         const uint8_t* p = getPixelAddress((const uint8_t*)pPixels, indexPixel);

//         color.W = pgm_read_byte(p++) & 0x1F; // mask out upper three bits
//         color.R = pgm_read_byte(p++);
//         color.G = pgm_read_byte(p++);
//         color.B = pgm_read_byte(p);

//         return color;
//     }

// };
