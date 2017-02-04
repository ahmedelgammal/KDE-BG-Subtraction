/*
 *
 * Copyright 2001 by Ahmed Elgammal All  rights reserved.
 *
 * Permission to use, copy,  or modify this software and  its documentation
 * for  educational  and  research purposes only and without fee  is hereby
 * granted, provided  that this copyright notice and the original authors's
 * name appear  on all copies and supporting documentation.  If individual
 * files are  separated from  this  distribution directory  structure, this
 * copyright notice must be included.  For any other uses of this software,
 * in original or  modified form, including but not limited to distribution
 * in whole or in  part, specific  prior permission  must be  obtained from
 * Author or UMIACS.  These programs shall not  be  used, rewritten, or  
 * adapted as  the basis  of  a commercial  software  or  hardware product 
 * without first obtaining appropriate licenses  from Author. 
 * Other than these cases, no part of this software may be used or
 * distributed without written permission of the author.
 *
 * Neither the author nor UMIACS make any representations about the 
 * suitability of this software for any purpose.  It is provided 
 * "as is" without express or implied warranty.
 *
 * Ahmed Elgammal
 * 
 * University of Maryland at College Park
 * UMIACS
 * A.V. Williams Bldg. 
 * CollegePark, MD 20742
 * E-mail:  elgammal@umiacs.umd.edu
 *
 **/



#include "stdafx.h"
#include "Controls.h"
#include "InputReader.h"
#include "NPBGBuild.h"


BuildNPBGModel(PlayControls * pControls,
			   NPBGSubtractor * BGModel,
			   unsigned int SequenceLength,
			   unsigned int TimeWindowSize,
			   unsigned char SDEstimationFlag,
			   unsigned char UseColorRatiosFlag)
{
	unsigned int rows,cols,color_channels;

	
  CString FileName,FrameName;
  unsigned int StartFrame,StopFrame,FrameStep,InputFormat,PadDigits;
	unsigned int FrameIndex;
  unsigned int useColorFlag;
	unsigned char lUseColorRatiosFlag;
	
  FileName  =pControls->FileName;	
  StartFrame=pControls->StartFrame;
  StopFrame =pControls->StopFrame;	
  FrameStep =pControls->FrameStep;
  InputFormat =pControls->InputFormat;
  PadDigits = pControls->PadDigits;

  useColorFlag=pControls->useColor;

	lUseColorRatiosFlag = UseColorRatiosFlag & useColorFlag;

  // Get Image Size ...
  rows=pControls->rows;
  cols=pControls->cols;
  color_channels=(useColorFlag ? 3 : 1);

  	// intialize input stream
	InputReader * InputStream=new InputReader(InputFormat,useColorFlag,rows,cols);
	InputStream->Initialize(FileName,PadDigits);

	// initialize displays

	//Display PlayDisplay;
	InputStream->PlayDisplay.OpenDisplay(useColorFlag,cols,rows,"Display");

	
	// initialize memory buffers..
	unsigned char * ImageBuffer = new unsigned char [rows*cols*color_channels];

	BGModel->Intialize(rows,cols,color_channels,SequenceLength,TimeWindowSize,SDEstimationFlag,lUseColorRatiosFlag);

	FrameIndex	= StartFrame;

	while (FrameIndex <= StopFrame){

		// Get input frame
		InputStream->GetFrame(FrameIndex,ImageBuffer);

		// add frame to the background
		BGModel->AddFrame(ImageBuffer);

		FrameIndex +=FrameStep;
				
		
	}

	BGModel->Estimation();

	InputStream->Stop();
	
	// free memory buffers...
	delete ImageBuffer;
	delete InputStream;



	return 0;


}


