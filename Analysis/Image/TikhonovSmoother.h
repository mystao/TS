/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
#ifndef TIKHONOVSMOOTHER_H
#define TIKHONOVSMOOTHER_H

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#include "Mask.h"
#include "datahdr.h"
#include "ByteSwapUtils.h"
#include "Region.h"
#include "ChipIdDecoder.h"
#include "ChannelXTCorrection.h"

#include <vector>
#include <string>

#define TIK_MAX_FRAME_CNT (1024)
typedef struct _tikSmoothParams { // (APB)
  int frame_cnt;             // number of frames this matrix is good for. Init to 0;
  int i_low[TIK_MAX_FRAME_CNT]; // for(frame=0; frame<frame_cnt; frame++){
  int i_high[TIK_MAX_FRAME_CNT];// for(i=i_lo[frame]; i<=i_high[frame]; i++){
  int *imatrix[TIK_MAX_FRAME_CNT];   // smoothed[frame]+ = matrix[frame][i] * raw[i];}}
  int denominator;   // smoothed[frame] /= denominator  need this to scale at the end
}tikSmoothParams;

// file format for smoothing file
typedef struct _smoothHeader{
  unsigned int magic; // should be 0xABCDBEEF
  int frame_cnt;
  int denominator;
}smoothHeader;
// rest of file is ints.  matrix ints are divided by .denominator to get the .matrix[i][j] values
// int i_low[cnt]   .frame_cnt entries
// int i_high[cnt]  .frame_cnt entries
// int matrix[row][column] in row-major order. .frame_cnt^2 entries

// this has a lot of numbers in it, generated by a program
extern int tik05_frame_cnt;
extern int tik05_denominator;
extern int tik05_i_low[25];
extern int tik05_i_high[25];
extern int tik05_imatrix[25][25];

extern int tik075_frame_cnt;
extern int tik075_denominator;
extern int tik075_i_low[25];
extern int tik075_i_high[25];
extern int tik075_imatrix[25][25];

extern int tik10_frame_cnt;
extern int tik10_denominator;
extern int tik10_i_low[25];
extern int tik10_i_high[25];
extern int tik10_imatrix[25][25];

extern int tik15_frame_cnt;
extern int tik15_denominator;
extern int tik15_i_low[25];
extern int tik15_i_high[25];
extern int tik15_imatrix[25][25];

extern int tik20_frame_cnt;
extern int tik20_denominator;
extern int tik20_i_low[25];
extern int tik20_i_high[25];
extern int tik20_imatrix[25][25];

//class TikhonovSmoother;

class TikhonovSmoother
{
public:
  TikhonovSmoother(const char *datDirectory, const char *smoothingFile, const char *smoothingInternal);
  ~TikhonovSmoother(){};
  bool LoadMatrix(const char *MatrixFileName);
  void SmoothTrace(short *image, int rows, int cols, int frame_cnt, const char *rawFileName);
  void StretchMatrix(int frame_cnt, int *i_low, int *i_high, int **imatrix);
  bool doSmoothing;
  tikSmoothParams smoothParams;
};


#endif // TIKHONOVSMOOTHER_H