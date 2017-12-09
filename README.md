# ArduinoCandleEffectNeoPixel

(C) 2017 Alain van Hanegem
This is 'simple candle' effect using a 12-led neopixel ring. It uses 3 values of yellow and red and fades to new randomized group values at 10Hz rate. The program runs at 100Hz to update the leds. It really gives a nice effect of a candle moving.


## Hardware

This is the neopixel used: https://www.adafruit.com/product/1643

You can use any Arduino, having 5V to power your Neopixel ring and provide a 

In case you'll be using a LI-ion/PO powered solution, make sure to connect your neopixel to Vbat, as there probably isn't any 5V available from your battery.

## License 

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).

## Notes
* Using neopixel strips: use a 470 ohm resistor on your data line to protect the first LED from spikes that can occur.
* Using rings: no need to add extra; the resistor is already on the ring

## Acknowledgments

* Created for inspiration and fun
