# "Purple Rain" Arduino-powered wearable LED art

*_Purple Rain_* is a wearable LED art piece I made for OmegaCon Spring 2016. Below is a 5 second sample of the art piece in operation.

![Sample of LED art piece](https://i.imgur.com/VzLN8ag.gif)

## Details

In 2014, I modified an OmegaCon badge lanyard with an [Adafruit Gemma][2] microcontroller and a [12-pixel Adafruit Neopixel ring][3]. Each OmegaCon, I make a thematic LED art piece with this modified lanyard, using the [FastLED][1] library.

For Spring 2016, the death of Prince was fresh news, and so I chose to make "Purple Rain", which included this Arduino sketch and white synthetic flower to act as a diffuser.

## Getting the sketch working

For Arduino sketches, **the directory name must match the .ino name**; either rename the .ino, or clone this repo using

    git clone <repo_url> Purple_Rain

Change the `DATA_PIN` constant to address the Digital pin connected to the data line for your LED strip; change the `LED_COUNT` constant to reflect the number of pixels in your strip. If you're not using a Neopixel-compatible WS2812 LED strip, you may need to alter the `addLeds` line and make other changes.

This sketch has been tested with various WS2812-based LED strips connected to various Arduino-compatible boards; however, to get it to upload to the Gemma I needed to use the [Adafruit Arduino IDE][4]--FastLED will not compile _for the Gemma only_ on the Arduino 1.6.5 IDE branch.

The most recent versions of the standard Arduino IDE worked just fine for every other board I tested.

[1]: http://fastled.io
[2]: https://learn.adafruit.com/introducing-gemma/introduction "Adafruit Gemma"
[3]: https://www.adafruit.com/products/1643 "Adafruit 12-pixel Neopixel Ring"
[4]: https://learn.adafruit.com/adafruit-arduino-ide-setup/arduino-1-dot-0-x-ide