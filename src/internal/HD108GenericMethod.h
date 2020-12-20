/*-------------------------------------------------------------------------
NeoPixel library helper functions for HD108 using general Pins.

Modified by Brayden McLean

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

// must also check for arm due to Teensy incorrectly having ARDUINO_ARCH_AVR set
#if defined(ARDUINO_ARCH_AVR) && !defined(__arm__)
#include "TwoWireBitBangImpleAvr.h"
#else
#include "TwoWireBitBangImple.h"
#endif


template<typename T_TWOWIRE> class HD108MethodBase
{
public:
    HD108MethodBase(uint8_t pinClock, uint8_t pinData, uint16_t pixelCount, size_t elementSize, size_t settingsSize) :
        _sizeData(2 * pixelCount * elementSize + settingsSize),
        _sizeEndFrame((pixelCount + 15) / 8), // 16 = div 2 (bit for every two pixels) div 8 (bits to bytes)
        _wire(pinClock, pinData)
    {
        _data = static_cast<uint8_t*>(malloc(_sizeData));
        memset(_data, 0, _sizeData);
    }

#if !defined(__AVR_ATtiny85__) && !defined(ARDUINO_attiny)
    HD108MethodBase(uint16_t pixelCount, size_t elementSize, size_t settingsSize) :
        HD108MethodBase(SCK, MOSI, pixelCount, elementSize, settingsSize)
    {
    }
#endif

    ~HD108MethodBase()
    {
        free(_data);
    }

    bool IsReadyToUpdate() const
    {
        return true; // dot stars don't have a required delay
    }

#if defined(ARDUINO_ARCH_ESP32)
    void Initialize(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
    {
        _wire.begin(sck, miso, mosi, ss);
    }
#endif

    void Initialize()
    {
        _wire.begin();
    }

    void Update(bool)
    {
        // Serial.println("Updating Strip - Begin Transaction");
        const uint8_t startFrame[16] = { 0x00 }; //Send 128 0 bits. (Sixteen null bytes)
        
        _wire.beginTransaction();
        // start frame
        _wire.transmitBytes(startFrame, sizeof(startFrame));

        // Serial.println("Updating Strip - Write Data");
        // data
        // Serial.println(*_data, HEX);
        _wire.transmitBytes(_data, _sizeData);

        // Serial.println("Updating Strip - End Transaction");
        // end frame      
        // one 1 bit for every pixel (Eight 1s for every 8 pixels)
        for (size_t endFrameByte = 0; endFrameByte < _sizeEndFrame; endFrameByte++)
        {
            // Serial.println(0xFF, HEX);
            _wire.transmitByte(0x00);
        }
        
        _wire.endTransaction();
    }

    uint8_t* getData() const
    {
        return _data;
    };

    size_t getDataSize() const
    {
        return _sizeData;
    };

private:
    const size_t   _sizeData;   // Size of '_data' buffer below
    const size_t   _sizeEndFrame;

    T_TWOWIRE _wire;
    uint8_t* _data;       // Holds LED color values
};

typedef HD108MethodBase<TwoWireBitBangImple> HD108Method;

#if !defined(__AVR_ATtiny85__) && !defined(ARDUINO_attiny)
#include "TwoWireSpiImple.h"
typedef HD108MethodBase<TwoWireSpiImple<SpiSpeed40Mhz>> HD108Spi40MhzMethod;
typedef HD108MethodBase<TwoWireSpiImple<SpiSpeed20Mhz>> HD108Spi20MhzMethod;
typedef HD108MethodBase<TwoWireSpiImple<SpiSpeed10Mhz>> HD108Spi10MhzMethod;
typedef HD108MethodBase<TwoWireSpiImple<SpiSpeed2Mhz>> HD108Spi2MhzMethod;
typedef HD108Spi10MhzMethod HD108SpiMethod;
#endif
