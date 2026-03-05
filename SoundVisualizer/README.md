# The Arduino Nano Sound Visualizer

An Arduino Nano, MAX4466 microphone, and 8x8 WS2812B LED matrix are used in this 3D-printed sound visualizer that responds to background noise.

# Features

Bar Graph, Spectrum Analyzer, Ripple Effect, and Equalizer Blocks are the four visualization modes.
switches between modes automatically every eight seconds.
Microphone gain that may be adjusted with a MAX4466 potentiometer
Hardware in a small 3D-printed box with engraved identifying well hopefully idk because my 3d modeling skills are shit 

as for why i made this honestly idk i like hack club and this is my first project so yay!
## Hardware

- Arduino Nano
- GY-MAX4466 Electret Microphone Amplifier
- 8x8 WS2812B NeoPixel LED Matrix
- Half-size breadboard
- 3D printed case (STL files included)

## Wiring

| Nano Pin | Component |
|----------|-----------|
| D6 | LED Matrix DIN |
| A0 | MAX4466 OUT |
| 5V | MAX4466 VCC, LED VCC |
| GND | MAX4466 GND, LED GND |

## 3D Printed Parts

Print the STL files in the `case/` folder:
- `sound_viz_body.stl` - Main case body
- `sound_viz_lid.stl` - Top lid
- `sound_viz_grille.stl` - Microphone grille

Recommended print settings: 0.2mm layer height, PLA material

## Libraries Required

- FastLED (by Daniel Garcia)
- arduinoFFT (by ArduinoGetStarted)

## License

MIT License

# images
 <img width="1800" height="1169" alt="Screenshot 2026-03-05 at 5 09 29 PM" src="https://github.com/user-attachments/assets/f589c844-3052-4cfa-a3bd-8147b75ca5ac" />
<img width="1800" height="1169" alt="Screenshot 2026-03-05 at 5 09 37 PM" src="https://github.com/user-attachments/assets/bf90dc3d-d8fe-41fe-b0d2-a3073dc294d4" /><img width="1800" height="1169" alt="Screenshot 2026-03-05 at 5 09 41 PM" src="https://github.com/user-attachments/assets/f0ec8548-deea-46e2-bce8-6118876a05a4" />
![Screenshot 2026-03-05 at 5 09 29 PM](https://github.com/user-attachments/assets/28965fa2-f872-40eb-9230-ee7a472eb830)

