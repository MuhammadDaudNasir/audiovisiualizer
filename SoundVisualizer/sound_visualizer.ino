// SOUND VISUALIZER - Arduino Nano + MAX4466 + 8x8 WS2812B Matrix

#include <FastLED.h>
#include <arduinoFFT.h>

// CONFIGURATION
#define LED_PIN     6           // Data pin for LED matrix
#define MIC_PIN     A0          // Analog pin for microphone
#define NUM_LEDS    64          // 8x8 matrix
#define BRIGHTNESS  150         // LED brightness (0-255)
#define SAMPLES     64          // FFT samples (must be power of 2)

// FASTLED SETUP
CRGB leds[NUM_LEDS];
uint8_t mode = 0;              // Current visualization mode
uint8_t numModes = 4;           // Total number of modes
unsigned long lastModeChange = 0;

// FFT SETUP
double vReal[SAMPLES];
double vImag[SAMPLES];
arduinoFFT FFT(vReal, vImag, SAMPLES, 1600);

void setup() {
  // LED setup
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  
  // Mic input
  pinMode(MIC_PIN, INPUT);
  
  Serial.begin(115200);
}

void loop() {
  // Read microphone
  int micValue = analogRead(MIC_PIN);
  
  // Get audio levels
  uint8_t volume = map(micValue, 0, 1023, 0, 255);
  uint8_t bass = getBassLevel();
  uint8_t mid = getMidLevel();
  uint8_t treble = getTrebleLevel();
  
  // Auto-cycle modes every 8 seconds
  if (millis() - lastModeChange > 8000) {
    mode = (mode + 1) % numModes;
    lastModeChange = millis();
    FastLED.clear();
    FastLED.show();
  }
  
  // Display based on mode
  switch(mode) {
    case 0:
      barGraph(volume);
      break;
    case 1:
      spectrumAnalyzer();
      break;
    case 2:
      rippleEffect(volume);
      break;
    case 3:
      equalizerBlocks(bass, mid, treble);
      break;
  }
  
  FastLED.show();
  delay(20);
}

// VISUALIZATION MODES

// Mode 0: Simple Bar Graph
void barGraph(uint8_t level) {
  FastLED.clear();
  
  uint8_t bars = map(level, 0, 255, 0, 8);
  
  for (int x = 0; x < 8; x++) {
    uint8_t barHeight = bars;
    
    for (int y = 0; y < barHeight && y < 8; y++) {
      // Color gradient based on height
      CRGB color = CHSV(map(y, 0, 8, 96, 0), 255, 255); // Green to Red
      leds[XY(x, 7-y)] = color;
    }
  }
}

// Mode 1: Spectrum Analyzer
void spectrumAnalyzer() {
  FastLED.clear();
  
  // Sample audio
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0;
    delayMicroseconds(50);
  }
  
  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();
  
  // Display lower frequencies
  for (int x = 0; x < 8; x++) {
    int bin = x + 1;
    uint8_t height = map(vReal[bin], 0, 500, 0, 8);
    height = constrain(height, 0, 8);
    
    for (int y = 0; y < height; y++) {
      CRGB color = CHSV(map(x, 0, 8, 160, 0), 255, 255);
      leds[XY(x, 7-y)] = color;
    }
  }
}

// Mode 2: Ripple Effect
static uint8_t hue = 0;
void rippleEffect(uint8_t level) {
  // Fade out
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(40);
  }
  
  // Add ripple based on volume
  if (level > 50) {
    hue += 5;
    int center = random8(NUM_LEDS);
    leds[center] = CHSV(hue, 255, 255);
    
    // Spread to neighbors
    int x = center % 8;
    int y = center / 8;
    
    if (x > 0) leds[center-1] = CHSV(hue, 255, 200);
    if (x < 7) leds[center+1] = CHSV(hue, 255, 200);
    if (y > 0) leds[center-8] = CHSV(hue, 255, 200);
    if (y < 7) leds[center+8] = CHSV(hue, 255, 200);
  }
}

// Mode 3: Equalizer Blocks
void equalizerBlocks(uint8_t bass, uint8_t mid, uint8_t treble) {
  FastLED.clear();
  
  // Bass - left side
  for (int x = 0; x < 3; x++) {
    uint8_t h = map(bass, 0, 255, 0, 8);
    for (int y = 0; y < h && y < 8; y++) {
      leds[XY(x, 7-y)] = CRGB(255, 0, 0); // Red for bass
    }
  }
  
  // Mid - center
  for (int x = 3; x < 5; x++) {
    uint8_t h = map(mid, 0, 255, 0, 8);
    for (int y = 0; y < h && y < 8; y++) {
      leds[XY(x, 7-y)] = CRGB(0, 255, 0); // Green for mid
    }
  }
  
  // Treble - right side
  for (int x = 5; x < 8; x++) {
    uint8_t h = map(treble, 0, 255, 0, 8);
    for (int y = 0; y < h && y < 8; y++) {
      leds[XY(x, 7-y)] = CRGB(0, 0, 255); // Blue for treble
    }
  }
}

// HELPER FUNCTIONS

// XY mapping for 8x8 matrix
uint8_t XY(uint8_t x, uint8_t y) {
  return (y * 8) + x;
}

// Get bass level (average of lower frequencies)
uint8_t getBassLevel() {
  uint32_t sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(MIC_PIN);
  }
  return map(sum / 10, 0, 1023, 0, 255);
}

// Get mid level
uint8_t getMidLevel() {
  return getBassLevel(); // Simplified
}

// Get treble level
uint8_t getTrebleLevel() {
  return getBassLevel(); // Simplified
}
