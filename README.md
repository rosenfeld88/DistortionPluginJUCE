# DistortionPluginJUCE
This is a simple distortion plugin created with JUCE.

File Organization:

Builds/MacOSX - contains the actual VST and AU plugin files (Build.MacOSX/build/Debug) as well as the XCode project files. 

JuceLibraryCode - self-explanatory. Contains library code imported from JUCE.

MATLAB - Matlab prototyping.

Source - Source code (.cpp and .h files).

Plugin Controls:

Gain – Input gain applied before clipping function.
Volume - Distortion output volume.
Blend - Wet/dry mix.
Tone - Controls IIR lowpass filter cutoff frequency (1 kHz to 20kHz).
Clip Type - Clipping function (arc tangent, hyperbolic tangent, and soft-max). Arc tangent is the most tame clipping function, while soft-max is the most intense. Each have varying tonalities. 
