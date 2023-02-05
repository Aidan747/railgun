#ifndef GPIO_H
#define GPIO_H

#define ULL unsigned long long

#include <pigpio.h> 
#include <static_block.hpp>
#include <cstdint>

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <exception>
#include <iostream>


int operator"" _Hz(ULL freq) {return freq;}
int operator"" _KHz(ULL freq) {return freq * 1000;}
int operator"" _MHz(ULL freq) {return freq * 1000000;}

namespace PinState {
    enum {
        HIGH = 1,
        LOW = 0,
        
        INPUT = 1,
        OUTPUT = 0
    };
};

class GPIO {

    int pin;
    int state;
    inline static bool initialized = false;
  
    public:
        GPIO() {
            if(!initialized) {
                gpioInitialise();
                initialized = true;
            }
        }

        GPIO(int pin, int type) {
            this->pin = pin;
            if(!initialized) {
                gpioInitialise();
                initialized = true;
            }
            gpioSetMode(pin, type);
        }

        void write(int state) {
            gpioWrite(pin, state);
            this->state = state;
        }
        void startPWM(long double freq, float dutyCycle) {
            gpioHardwarePWM(pin, freq, dutyCycle);
        }

};

class I2CException: public std::exception
{
  public:
    I2CException(const char* message) : message_(message) {}
    virtual const char* what() const throw() { return message_; }

  private:
    const char* message_;
};

class I2C {
    private:
      int bus_;
      int slaveAddress_;
      int file_;
      char filename_[20];
    public:
      I2C(int bus, int slaveAdress) {
        snprintf(filename_, 19, "/dev/i2c-%d", bus_);
        if ((file_ = open(filename_, O_RDWR)) < 0) {
            throw I2CException("Failed to open the I2C device");
        }

      }
};

// template <class T>
// class Pin : public T{
//     Pin(int pin, int mode) : T(pin, mode) {
        
//     }
// };

#endif