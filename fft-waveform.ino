include "arduinoFFT.h"  // include library for FFT algorithm

int micPin = A0;  // pin for the microphone
int resPin = A1;  // pin for the variable resistor

// FFT variables
arduinoFFT FFT = arduinoFFT();
double vReal[128], vImag[128];

void setup() {
  // set the micPin and resPin as inputs
  pinMode(micPin, INPUT);
  pinMode(resPin, INPUT);

  // initialize the FFT algorithm
  FFT.Windowing(vReal, 128, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
}

void loop() {
  // read the waveform value from the microphone
  int micValue = analogRead(micPin);

  // read the resistance value from the variable resistor
  int resValue = analogRead(resPin);

  // map the resistance value to the range 30-1200
  resValue = map(resValue, 0, 1023, 30, 1200);

  // calculate the 10% window around the dominant frequency
  // (assuming a sample rate of 8000Hz)
  int window = resValue / 100 * 800;
  int minFreq = resValue - window;
  int maxFreq = resValue + window;

  // add the waveform sample to the FFT input array
  vReal[micValue] = (double)micValue;

  // run the FFT algorithm
  FFT.Compute(vReal, vImag, 128, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, 128);

  // find the index of the dominant frequency in the waveform
  int maxIndex = 0;
  double maxValue = 0;
  for (int i = 0; i < 128; i++) {
    if (vReal[i] > maxValue) {
      maxValue = vReal[i];
      maxIndex = i;
    }
  }

  // check if the dominant frequency is within the 10% window
  bool inWindow = (maxIndex >= minFreq && maxIndex <= maxFreq);

  // set the output value based on whether the dominant frequency is in the window
  int output = inWindow ? 100 : 255;

  // output the result
  Serial.write(output);
}
