
// Port of the Arduno "Button" library

#ifndef _PICO_STDLIB_H
    #include "pico/stdlib.h"
#endif

#ifndef Button_h
#define Button_h

class Button
{
	public:
		Button(unsigned int pin, unsigned int debounce_us = 100000)
        :  _pin(pin)
        ,  _delay(debounce_us)
        ,  _state(true)
        ,  _ignore_until(0)
        ,  _has_changed(false)
        {
        }

		void begin()
        {
            gpio_init(_pin);
            gpio_set_dir(_pin, GPIO_IN);
            gpio_pull_up(_pin);
        }

		bool read()
        {
            // ignore pin changes until after this delay time
            if (_ignore_until > time_us_32())
            {
                // ignore any changes during this period
            }
            
            // pin has changed 
            else if (gpio_get(_pin) != _state)
            {
                _ignore_until = time_us_32() + _delay;
                _state = !_state;
                _has_changed = true;
            }
            
            return _state;
        }

		bool toggled()
        {
            read();
            return has_changed();
        }

		bool pressed()
        {
            {
                return (read() == PRESSED && has_changed());
            }
        }

		bool released()
        {
            {
                return (read() == RELEASED && has_changed());
            }
        }

		bool has_changed()
        {
            {
                if (_has_changed)
                {
                    _has_changed = false;
                    return true;
                }
                return false;
            }
        }
		
		const static bool PRESSED = false;
		const static bool RELEASED = true;
	
	private:
		unsigned int  _pin;
		unsigned int _delay;
		bool     _state;
		unsigned int _ignore_until;
		bool     _has_changed;
};

#endif