# arduino-cavitation-sensor
## Arduino pump cavitation sensor-controller

Plugin for Arduino that gets a waveform from a microphone (sensor) and a variable resistor (control knob) value in the range 30-1200 Hz as inputs, and outputs voltage level 3 if the waveform contains the dominant frequency in the 10% window defined by the control knob, or voltage level 5 if the waveform does not contain the dominant frequency in the 10% window. 

This code uses a Fast Fourier Transform (FFT) algorithm to analyze the waveform and find dominant frequency. Controller temporarily reduces power of electric pump if the microphone detects sound of cavitation in the output pipeline. Control knob is used to set frequency that is considered as cavitation event. 
