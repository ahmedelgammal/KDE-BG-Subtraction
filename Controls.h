#ifndef __CONTROLS__
#define __CONTROLS__

#include "Tracker.h"
#include "TrackerDlg.h"


typedef struct{
	CString FileName;
	UINT StartFrame;
	UINT StopFrame;
	UINT FrameStep;
	UINT PadDigits;
	UINT InputFormat;
	BOOL useTM;
	BOOL useColor;

	double ThresholdValue1;
	double ThresholdValue2;
	double AlphaValue;

	unsigned int rows;
	unsigned int cols;
	CTrackerDlg * pDlg;
} PlayControls;

typedef struct{
	unsigned int FrameNumber;
	float DisplayTime;
	float LoadTime;
	float BGSubTime;
	float TotalTime;
	
} PerformanceCounters;

/*--------------------macros-----------------------------*/

// TIMED_FUNCTION macro call the function "fn" and measure
// the time required to execute this function and add that
// to "x"

#define TIMED_FUNCTION(fn,x) \
{			\
	LARGE_INTEGER t1,t2,f;  \
	QueryPerformanceFrequency(&f);\
	QueryPerformanceCounter(&t1);\
	(fn);\
	QueryPerformanceCounter(&t2);	\
	(x)+=(float) (1000.0*(float)(t2.QuadPart - t1.QuadPart) / f.QuadPart); \
} 


#endif