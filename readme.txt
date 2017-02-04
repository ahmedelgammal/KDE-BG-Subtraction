
Nonparametric Background subtraction classes:

NPBGmodel class
NPBGSubtractor class
KernelLUTable class

you have to rewrite a function to build the background similar to the function BuildNPBGModel.  only change the input reading calls..
(BuildNPBGModel is included only as an example and is not part of the code)

The code to call BG building can be something like:

==
NPBGSubtractor * p = new NPBGSubtractor; 
BuildNPBGModel(pControls,p,50,100,1,1);
==

where the parameters to this function are:

NPBGSubtractor * BGModel : pointer to the BG model.

unsigned int SequenceLength : number of samples for each pixel.

unsigned int TimeWindowSize : Time window for sampling. for example in the call above, the bg will sample 50 points out of 100 frames. this rate will affect how fast the model adapt.

unsigned char SDEstimationFlag : True means to estimate suitable kernel bandwidth to each pixel, False uses a default value.

unsigned char UseColorRatiosFlag: True means use normalized RGB for color (recommended.)


After initializing the bg, you can use the call
NPBGSubtractor::NBBGSubtraction to actually subtract the background from each new frame:

Ex:
((NPBGSubtractor *)pBGModel)->NBBGSubtraction(Frame,FGImage,FilteredFGImage,DisplayBuffers);

parameters are:

unsigned char * Frame : new frame

unsigned char * FGImage : to pass out the resulted FG (must be allocated before call) size imagerows x imagecols unsigned char

unsigned char * FilteredFGImage : to pass out a filtered version of the FG. size imagerows x imagecols unsigned char

unsigned char ** DisplayBuffers : a list of buffers for processing (Array of pointers to unsigned char buffers, each of size imagerows x imagecols)


At each frame also you can call the update function to adapt the bg

NPBGSubtractor::Update(unsigned char * FGMask)
here you pass a mask where pixels with true value will be masked out of the update.

you can change the threshold values using:

void SetThresholds(double th, double alpha) 

th: 0-1 is the probability threshold for a pixel to be a foregroud. typically make it small as 10e-8. the smaller the value the less false positive and more false negative.

alpha: 0-1, for color. typically set to 0.3. this affect shadow
suppression.



Please let me know if you have any questions. elgammal@cs.rutgers.edu

