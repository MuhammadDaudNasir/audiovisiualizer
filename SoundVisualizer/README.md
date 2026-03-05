# Arduino Nano Sound Visualizer

A 3D-printed sound visualizer that reacts to ambient sound using an Arduino Nano, MAX4466 microphone, and 8x8 WS2812B LED matrix.

## Features

- 4 visualization modes: Bar Graph, Spectrum Analyzer, Ripple Effect, Equalizer Blocks
- Auto-cycles between modes every 8 seconds
- Adjustable microphone gain (via MAX4466 potentiometer)
- Compact 3D-printed enclosure with engraved labels

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
