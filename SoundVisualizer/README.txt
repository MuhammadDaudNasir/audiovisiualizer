LIBRARIES NEEDED:

1. FastLED
   - Library Manager search: "FastLED"
   - Author: Daniel Garcia
   - Version: 3.6.0+

2. arduinoFFT  
   - Library Manager search: "arduinoFFT"
   - Author: ArduinoGetStarted
   - Version: 1.6.0+


INSTALL IN ARDUINO IDE:
1. Open Arduino IDE
2. Go to Tools → Library Manager
3. Search and install each library above


BOARD SETTINGS:
- Board: Arduino Nano
- Processor: ATmega328P (Old Bootloader)
- Port: (select your Nano's port)


WIRING:
Arduino Nano → Component
D6 → WS2812B LED Matrix DIN
A0 → MAX4466 OUT
5V → MAX4466 VCC, LED Matrix VCC
GND → MAX4466 GND, LED Matrix GND


UPLOAD:
1. Connect Arduino Nano via USB
2. Select correct Port in Tools → Port
3. Click Upload button
4. Open Serial Monitor (115200) to see debug output
