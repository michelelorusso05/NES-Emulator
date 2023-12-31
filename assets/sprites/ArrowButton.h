////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
// ImageAsCode exporter v1.0 - Image pixel data exported as an array of bytes         //
//                                                                                    //
// more info and bugs-report:  github.com/raysan5/raylib                              //
// feedback and support:       ray[at]raylib.com                                      //
//                                                                                    //
// Copyright (c) 2018-2021 Ramon Santamaria (@raysan5)                                //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

#include "ButtonTexture.h"

// Image data information
#define ARROWBUTTON_WIDTH    18
#define ARROWBUTTON_HEIGHT   34
#define ARROWBUTTON_FORMAT   7          // raylib internal pixel format

static unsigned char ARROWBUTTON_DATA[2448] = { 0x0,
0x0, 0x0, 0x0, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x0,
0x0, 0x0, 0x0, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f,
0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f,
0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f,
0x8f, 0x8f, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x8f,
0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f,
0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f,
0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff };

static unsigned char ARROWBUTTONPRESSED_DATA[2448] = { 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3,
0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcd,
0xcd, 0xcd, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3,
0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0xb3, 0xb1, 0xb4, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b,
0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff, 0x38,
0x38, 0x38, 0xff, 0x38, 0x38, 0x38, 0xff };

ButtonTexture arrowButtonData(ARROWBUTTON_WIDTH, ARROWBUTTON_HEIGHT, ARROWBUTTON_FORMAT, ARROWBUTTON_DATA, ARROWBUTTONPRESSED_DATA);