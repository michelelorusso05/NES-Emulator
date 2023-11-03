////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
// FontAsCode exporter v1.0 - Font data exported as an array of bytes                 //
//                                                                                    //
// more info and bugs-report:  github.com/raysan5/raylib                              //
// feedback and support:       ray[at]raylib.com                                      //
//                                                                                    //
// Copyright (c) 2018-2023 Ramon Santamaria (@raysan5)                                //
//                                                                                    //
// ---------------------------------------------------------------------------------- //
//                                                                                    //
//                                                                                    //
// Font name:    PixelNES                                                             //
// Font creator: ....                                                                 //
// Font LICENSE: ....                                                                 //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

#include "../../include/raylib.h"

#define COMPRESSED_DATA_SIZE_FONT_PIXELNES 4336

// Font image pixels data compressed (DEFLATE)
// NOTE: Original pixel data simplified to GRAYSCALE
static unsigned char fontData_Pixelnes[COMPRESSED_DATA_SIZE_FONT_PIXELNES] = { 0xed,
    0xdd, 0x4d, 0x88, 0x24, 0x67, 0x1d, 0xc7, 0xf1, 0xd5, 0x3d, 0x2c, 0xae, 0xb8, 0x20, 0x41, 0x10, 0x77, 0x24, 0x42, 0x72,
    0xd0, 0x83, 0x27, 0x41, 0x6c, 0x82, 0x5e, 0x44, 0xe2, 0x41, 0x76, 0x92, 0x89, 0x95, 0x0c, 0x18, 0x18, 0x74, 0xc8, 0x61,
    0x0f, 0x22, 0x4d, 0xc4, 0x4b, 0x14, 0x14, 0xf6, 0x94, 0x65, 0x37, 0x9e, 0x24, 0x91, 0x1c, 0x96, 0xb0, 0x64, 0x37, 0x35,
    0x6f, 0x3b, 0x90, 0x68, 0x93, 0x9b, 0x42, 0x7a, 0xd9, 0xcb, 0xa2, 0x1e, 0xf4, 0x28, 0x38, 0x41, 0x6f, 0xa2, 0x60, 0xb2,
    0x84, 0xcd, 0xee, 0x5f, 0xba, 0x7a, 0xa6, 0xaa, 0xa7, 0xa6, 0xaa, 0x9e, 0xe7, 0xff, 0xbc, 0x54, 0x57, 0x75, 0x7f, 0xfb,
    0x73, 0xe9, 0xdd, 0xe9, 0x7a, 0x7b, 0xaa, 0x7e, 0xdd, 0x4f, 0x3d, 0xcf, 0xd3, 0xfd, 0xc8, 0x29, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x27, 0x03, 0x49, 0x73, 0x27, 0xff, 0xfa, 0xb6, 0xbc, 0x2d, 0xbf, 0xc8, 0x9e, 0xbd, 0x94, 0x3d, 0x0f, 0xbb,
    0xed, 0xc9, 0x36, 0x87, 0x56, 0xaf, 0x9a, 0x1a, 0x94, 0xfe, 0x32, 0xcc, 0xff, 0x32, 0x34, 0x1e, 0x9b, 0xdd, 0xb6, 0x8a,
    0xe3, 0x35, 0xad, 0x2b, 0x6d, 0x2c, 0xb7, 0xfa, 0xd7, 0x0e, 0x14, 0xe5, 0xf3, 0x49, 0x39, 0x23, 0x67, 0xe4, 0x93, 0x11,
    0xca, 0x58, 0xb3, 0x7f, 0x76, 0x25, 0x67, 0x7f, 0x56, 0xca, 0xaf, 0xd2, 0x94, 0xcb, 0x50, 0x71, 0x2e, 0x75, 0x67, 0xcc,
    0x66, 0x29, 0xed, 0xf5, 0x6a, 0xda, 0x56, 0x17, 0x24, 0x52, 0x3c, 0x4e, 0xfe, 0x75, 0xf2, 0xd8, 0xcf, 0x9e, 0xed, 0xd4,
    0xbc, 0xa2, 0x58, 0x47, 0x92, 0x2f, 0x61, 0x7b, 0xcc, 0x76, 0xaf, 0x2d, 0x1e, 0xc9, 0x89, 0x92, 0x3e, 0x7a, 0xa4, 0xc6,
    0x63, 0xb3, 0xdf, 0xd6, 0xbe, 0xd5, 0xba, 0xc4, 0x58, 0x6e, 0xd5, 0x8f, 0x44, 0x51, 0x16, 0xd3, 0x6d, 0x3e, 0xdf, 0x78,
    0xad, 0xd5, 0x9f, 0x95, 0xa6, 0x32, 0xd6, 0xec, 0x9f, 0xe6, 0x8c, 0xda, 0x9c, 0x95, 0xf2, 0xab, 0x9a, 0xcb, 0xc5, 0x65,
    0xdd, 0x2e, 0x67, 0xcc, 0x66, 0x29, 0xed, 0xf5, 0x2a, 0xc6, 0xb3, 0x43, 0xfe, 0xdb, 0xcc, 0xff, 0x68, 0xe1, 0xf2, 0xff,
    0x56, 0x6f, 0xf3, 0x3f, 0x22, 0xff, 0x73, 0x67, 0x77, 0x1d, 0x37, 0xe7, 0x3f, 0x91, 0x44, 0xae, 0x66, 0x7f, 0xbb, 0x9a,
    0x3d, 0x9f, 0x3c, 0xc6, 0xd9, 0xb3, 0x95, 0xca, 0x6d, 0x7e, 0x5f, 0x7d, 0x56, 0xaa, 0xae, 0x11, 0xf3, 0x27, 0x7b, 0xd5,
    0x52, 0x9b, 0xc6, 0x2b, 0xad, 0x3a, 0xff, 0xda, 0xab, 0xd4, 0xe5, 0x9d, 0x76, 0x5a, 0x57, 0x2c, 0xca, 0x6d, 0x5a, 0xae,
    0x93, 0xff, 0xfb, 0x66, 0xc3, 0x3a, 0x6f, 0x3a, 0xe6, 0x3f, 0xfe, 0x67, 0x89, 0xe9, 0x5d, 0x79, 0xd3, 0xb2, 0x5c, 0xdc,
    0xea, 0x72, 0xf5, 0x67, 0xec, 0xa6, 0x22, 0xc9, 0xf6, 0x7b, 0x57, 0x5d, 0xa7, 0x59, 0x86, 0xfc, 0x6b, 0x3f, 0xe9, 0x9e,
    0x9e, 0x63, 0xfe, 0x93, 0x0e, 0xe7, 0xdf, 0xad, 0x1e, 0xd5, 0xdf, 0xfc, 0x27, 0x73, 0xca, 0xff, 0x75, 0xf2, 0x5f, 0x51,
    0x4a, 0xe3, 0x86, 0x76, 0xac, 0x9f, 0x65, 0xcf, 0x7e, 0x5a, 0xf3, 0x0a, 0x4d, 0xfe, 0x2f, 0xca, 0x45, 0x79, 0x75, 0x66,
    0x7b, 0x93, 0xc7, 0x81, 0xb1, 0xa5, 0xa4, 0xdc, 0x46, 0x54, 0xd4, 0x38, 0x8e, 0xce, 0x63, 0x55, 0xab, 0x4c, 0xf1, 0x98,
    0xd6, 0x4b, 0xec, 0xf2, 0x5f, 0x1c, 0x6f, 0x3f, 0xf2, 0x7f, 0xc3, 0x78, 0x85, 0x69, 0x5b, 0xef, 0xdc, 0x8f, 0xce, 0xe6,
    0xac, 0x14, 0xaf, 0x4a, 0x4a, 0x2d, 0x6e, 0x07, 0x87, 0xff, 0x9b, 0xd4, 0xb4, 0x04, 0xce, 0xbe, 0xca, 0x5c, 0x36, 0xf5,
    0xed, 0x8a, 0xd7, 0x54, 0x77, 0x10, 0x47, 0x7b, 0x3b, 0x36, 0xb4, 0xe4, 0xad, 0x64, 0xaf, 0x1d, 0xe7, 0x47, 0x3e, 0xee,
    0x59, 0xfe, 0xdd, 0xaf, 0xeb, 0x0b, 0x72, 0x41, 0x2e, 0x59, 0xd6, 0xff, 0xcb, 0xdb, 0x73, 0xfb, 0x6c, 0xd2, 0xd6, 0x1a,
    0x8a, 0x57, 0x25, 0x8e, 0xc7, 0xda, 0x46, 0xfe, 0x77, 0x64, 0x4b, 0x6e, 0x9f, 0x78, 0x6f, 0xdc, 0x92, 0x6d, 0xf9, 0xee,
    0x89, 0xd7, 0xee, 0xe7, 0xde, 0xcf, 0xaf, 0x38, 0x7d, 0xef, 0x42, 0xdb, 0x75, 0x49, 0xbf, 0xb6, 0x1c, 0xfd, 0xfd, 0x7f,
    0xb5, 0xd7, 0x9d, 0xee, 0xe4, 0x4d, 0xe7, 0xfd, 0x99, 0xca, 0x2b, 0x6d, 0x19, 0xf2, 0x3f, 0x7d, 0x0f, 0xb0, 0xcb, 0x34,
    0xf9, 0x77, 0x69, 0x31, 0xbc, 0x18, 0xa0, 0x75, 0x91, 0xfc, 0x1f, 0x79, 0x2d, 0x4a, 0xfe, 0x9f, 0xea, 0x59, 0xfe, 0x87,
    0xf9, 0x67, 0x4c, 0x53, 0x5b, 0x5d, 0xe8, 0xfc, 0x97, 0xeb, 0x53, 0x76, 0xf5, 0xff, 0xaa, 0xbd, 0x2e, 0xd7, 0xec, 0x4f,
    0x7a, 0x52, 0x9e, 0x94, 0x5f, 0x96, 0xea, 0xa3, 0xb3, 0xed, 0x6b, 0x9a, 0x7a, 0x31, 0xf9, 0x0f, 0x75, 0x56, 0xda, 0xcf,
    0xff, 0x8b, 0x32, 0x3a, 0xe6, 0x1f, 0x86, 0xfb, 0x8c, 0xea, 0x63, 0x6a, 0xaa, 0xff, 0x4f, 0xd6, 0x7a, 0xb7, 0xf2, 0x4e,
    0xb3, 0xbb, 0xf9, 0xf7, 0x7f, 0x1f, 0x75, 0xb9, 0x6e, 0xdd, 0x7b, 0x65, 0xdc, 0xfa, 0x8c, 0x2f, 0x34, 0xb4, 0x19, 0x69,
    0xfb, 0x29, 0xdb, 0xb8, 0xff, 0x9f, 0xee, 0xef, 0x7a, 0xbe, 0xcd, 0x91, 0x65, 0x89, 0x74, 0xe5, 0x5a, 0x12, 0xab, 0xf6,
    0xd5, 0x76, 0xf3, 0x7f, 0x2d, 0xc8, 0x95, 0xe6, 0xd3, 0x3e, 0x4d, 0xfe, 0xe7, 0x91, 0xff, 0xb3, 0x72, 0xb6, 0xb1, 0xcd,
    0x98, 0xfc, 0x2f, 0x7a, 0xfe, 0x4f, 0x67, 0xd7, 0xc0, 0x75, 0xf2, 0x1f, 0xf5, 0xba, 0xb9, 0x21, 0x37, 0xe4, 0x8f, 0xd9,
    0xda, 0xde, 0xcb, 0x9e, 0xdf, 0x17, 0x91, 0x7f, 0x66, 0xcf, 0xbe, 0xa3, 0x18, 0xff, 0x13, 0x67, 0x24, 0x5f, 0xb9, 0xad,
    0x41, 0x3c, 0xc6, 0x29, 0xc5, 0xce, 0xff, 0xba, 0x3c, 0x2b, 0x97, 0xb3, 0x5a, 0xe6, 0x13, 0xf9, 0xfd, 0xc9, 0x9e, 0xac,
    0xcb, 0xba, 0x7c, 0xa9, 0xb3, 0xf9, 0xf7, 0x3f, 0x2b, 0x31, 0xf3, 0x7f, 0x41, 0xbd, 0x77, 0x6e, 0xdb, 0xb5, 0x79, 0x74,
    0x6d, 0x14, 0x70, 0xd8, 0xeb, 0x66, 0xf6, 0x73, 0xeb, 0x03, 0xab, 0xcf, 0x2d, 0xf2, 0xdf, 0xd6, 0xf8, 0x5f, 0xf2, 0x4f,
    0xfe, 0xeb, 0xda, 0x37, 0xe6, 0x91, 0xff, 0x69, 0x4f, 0x69, 0x52, 0xea, 0x2b, 0x1c, 0x5b, 0xf5, 0x19, 0x97, 0x7b, 0x96,
    0x07, 0xf9, 0x9a, 0x06, 0xc6, 0x2b, 0xad, 0xe8, 0x95, 0x9d, 0xb4, 0xd2, 0x6c, 0xca, 0xa8, 0x83, 0xed, 0x7f, 0x7d, 0xca,
    0xbf, 0x5d, 0x7f, 0x7f, 0xd9, 0x1b, 0xf2, 0xa6, 0xbc, 0x57, 0xd9, 0x4a, 0x98, 0x5a, 0xad, 0xc5, 0x36, 0xff, 0x1b, 0xb2,
    0x21, 0xbf, 0x56, 0xef, 0xdd, 0x46, 0xee, 0x71, 0xc5, 0x76, 0xab, 0xbe, 0x25, 0x34, 0x56, 0x6f, 0xbb, 0xcf, 0xbe, 0x90,
    0x9d, 0xcb, 0x2f, 0x66, 0xcf, 0xd7, 0x24, 0x69, 0x1c, 0xb1, 0xfa, 0x8c, 0xc7, 0xf8, 0xbf, 0xf2, 0xab, 0x52, 0xa7, 0xf1,
    0x7f, 0xfa, 0xbb, 0xb2, 0x36, 0xf2, 0x5f, 0xf5, 0x2e, 0x36, 0x7d, 0xaf, 0x7c, 0xb4, 0xf1, 0xdb, 0x6a, 0xc9, 0x9c, 0xfa,
    0xfc, 0xdc, 0x47, 0xb9, 0x25, 0x0d, 0xe7, 0x32, 0x54, 0xbb, 0x95, 0xdb, 0xde, 0x15, 0x8f, 0x0d, 0xcf, 0xf6, 0xb2, 0x7e,
    0xf4, 0xff, 0xcf, 0xc3, 0x53, 0xe4, 0x7f, 0x21, 0xae, 0x09, 0xf2, 0xdf, 0xbf, 0x73, 0x3d, 0x19, 0x31, 0xf6, 0xd2, 0x9c,
    0xf7, 0xe1, 0xf3, 0xb2, 0x2a, 0x4f, 0xcb, 0x9a, 0x3c, 0x73, 0xf8, 0x4d, 0xa0, 0xbb, 0xb2, 0x2a, 0x4f, 0x1d, 0xfe, 0xdb,
    0x74, 0x56, 0xaa, 0xeb, 0x8c, 0xd5, 0x67, 0xa5, 0x18, 0x97, 0x38, 0xf6, 0xae, 0x95, 0x4d, 0xb6, 0x7a, 0xa5, 0xb4, 0x2e,
    0xfd, 0xf7, 0xff, 0xa7, 0x5b, 0xbf, 0x32, 0xb7, 0x4f, 0xec, 0x58, 0xf9, 0xbf, 0xaa, 0x3c, 0xa2, 0x69, 0xad, 0xe6, 0xbd,
    0xd2, 0xc8, 0xc5, 0xa6, 0xb5, 0x14, 0xaf, 0x2a, 0xc6, 0xff, 0x36, 0x8f, 0x1b, 0x39, 0x79, 0xff, 0x6d, 0xf3, 0x4d, 0xfe,
    0xe2, 0x9a, 0xb9, 0x2b, 0xb7, 0x64, 0x4f, 0x76, 0x65, 0x47, 0xb6, 0x65, 0x5b, 0xb6, 0x0e, 0xb7, 0xfb, 0x23, 0x59, 0x93,
    0x6f, 0xf4, 0x38, 0xff, 0xf5, 0xdf, 0x6e, 0x9d, 0xdf, 0xfe, 0x8c, 0x22, 0xb6, 0x19, 0x5d, 0x08, 0xd8, 0x2a, 0xb3, 0x16,
    0xe8, 0xfb, 0xbf, 0x6b, 0x0b, 0x52, 0x8f, 0xf3, 0xad, 0x13, 0xbd, 0xe9, 0xd4, 0x6b, 0xe8, 0x5f, 0xfe, 0xe2, 0x71, 0xcd,
    0x9c, 0xef, 0x79, 0x5d, 0x8f, 0xfc, 0xbb, 0xe7, 0x7f, 0x35, 0xd0, 0xf5, 0xb7, 0x4a, 0xfe, 0x0f, 0x5b, 0x02, 0xc9, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xae, 0x49, 0x0d, 0x4c, 0xcb, 0x0f, 0x15, 0x4b, 0xa5,
    0x16, 0xaa, 0x7f, 0x45, 0x7f, 0x50, 0xf9, 0xda, 0x81, 0x61, 0xdf, 0x06, 0xea, 0xe3, 0xaa, 0xde, 0x83, 0x50, 0x73, 0x2e,
    0x25, 0xb5, 0x56, 0x02, 0x9d, 0xcd, 0x81, 0xd3, 0x99, 0xfc, 0x96, 0xdc, 0xa9, 0xf5, 0x39, 0xe5, 0xf9, 0x1f, 0x74, 0xfe,
    0x5a, 0x0b, 0xbb, 0x87, 0x3e, 0xc7, 0x34, 0x54, 0xa4, 0xa0, 0x7e, 0xff, 0x87, 0x86, 0xec, 0x34, 0xd3, 0xff, 0x1a, 0x72,
    0x79, 0xbf, 0xdc, 0xe7, 0xde, 0xb1, 0xff, 0x1d, 0xe5, 0xea, 0x79, 0xbe, 0x13, 0x63, 0xde, 0x5c, 0x66, 0x07, 0x4a, 0x2d,
    0xff, 0xf7, 0xb8, 0xcf, 0xc8, 0xc7, 0xf2, 0xb1, 0x3c, 0x90, 0x07, 0xf2, 0x30, 0xa3, 0xfb, 0x1d, 0xe9, 0x93, 0x47, 0xf2,
    0xfe, 0xe1, 0x7a, 0x26, 0x6b, 0x9c, 0xac, 0xf9, 0xcb, 0x96, 0xef, 0x30, 0x2e, 0x67, 0xd2, 0xe7, 0x57, 0xaa, 0xd3, 0xa8,
    0xbf, 0xbc, 0x1d, 0xe3, 0x5a, 0x6b, 0xf7, 0xb7, 0xc1, 0xf5, 0xc7, 0x63, 0x3f, 0x03, 0x55, 0x79, 0x2d, 0xe9, 0x92, 0xe5,
    0x7f, 0xb3, 0x43, 0xf9, 0x3f, 0xe7, 0x75, 0xad, 0x54, 0xe5, 0xff, 0xf8, 0xe3, 0x2b, 0x91, 0xf2, 0x7f, 0x5e, 0xce, 0xcb,
    0x0f, 0xb3, 0xbf, 0xff, 0x5b, 0xde, 0x3f, 0xe6, 0x7f, 0xd9, 0xff, 0x7e, 0x4d, 0xce, 0x37, 0xd6, 0x01, 0xc8, 0xff, 0xa2,
    0xe4, 0x3f, 0x51, 0xd7, 0x66, 0x5d, 0x66, 0x44, 0x4b, 0x0d, 0x25, 0xa1, 0x39, 0xf2, 0x91, 0xd5, 0xf9, 0x0f, 0x5b, 0x5e,
    0x55, 0x9e, 0x90, 0x35, 0xf9, 0x41, 0xb6, 0xc6, 0xbf, 0xe7, 0x73, 0x3c, 0xa5, 0x9e, 0xf5, 0xff, 0x57, 0x65, 0x2b, 0x5b,
    0xd3, 0x8e, 0xfc, 0x2d, 0x5b, 0xf3, 0x8f, 0x65, 0x4d, 0xbe, 0xed, 0x78, 0x26, 0xed, 0x4a, 0xb7, 0x3c, 0x4b, 0xdd, 0x6f,
    0xf2, 0xbf, 0xdc, 0xb1, 0x3a, 0xff, 0x89, 0x22, 0x93, 0xda, 0x73, 0x92, 0xb4, 0x34, 0x63, 0xa3, 0x3e, 0x0d, 0x6e, 0xf9,
    0x49, 0x3c, 0x66, 0x13, 0x24, 0xff, 0xc7, 0x97, 0x9a, 0x7f, 0xfe, 0x7f, 0x9f, 0xaf, 0xf1, 0xf5, 0x08, 0x2d, 0x34, 0xbf,
    0xca, 0xd7, 0xfe, 0x17, 0xf2, 0x4f, 0xfe, 0xa3, 0xe5, 0xff, 0x6a, 0xe5, 0x27, 0x53, 0x7d, 0x4b, 0xd6, 0xd5, 0x99, 0x39,
    0x2c, 0xed, 0xdb, 0x1a, 0xcb, 0x6d, 0x14, 0x2b, 0xc6, 0x19, 0xfb, 0x4d, 0x33, 0x76, 0xce, 0x3f, 0xff, 0xef, 0xb4, 0x94,
    0xff, 0x3f, 0x59, 0xb6, 0xe4, 0x0e, 0x3c, 0xf2, 0xff, 0x82, 0x5c, 0x94, 0xef, 0x19, 0xf3, 0x5f, 0x75, 0xfe, 0x07, 0x33,
    0x73, 0x6a, 0x56, 0xcd, 0x3f, 0xee, 0x7a, 0x4e, 0xea, 0xaf, 0xb5, 0xa6, 0x96, 0xaf, 0xaa, 0x6d, 0xf9, 0xec, 0x61, 0xb8,
    0xfc, 0xbb, 0x65, 0xa7, 0x5b, 0xf7, 0xff, 0x61, 0xe6, 0xb0, 0xd6, 0xbe, 0x27, 0x6b, 0x66, 0x79, 0x8e, 0x9f, 0xff, 0x5b,
    0xd9, 0xac, 0xae, 0x93, 0x79, 0x5d, 0xff, 0x25, 0x22, 0x1f, 0xca, 0xba, 0xac, 0xcb, 0xd7, 0x1d, 0xcb, 0xba, 0xa9, 0x14,
    0xbf, 0x9a, 0xad, 0x79, 0xd2, 0x1e, 0xf0, 0x1f, 0xd9, 0x95, 0x5d, 0xd9, 0xcb, 0xb6, 0xfc, 0x88, 0xaa, 0x8f, 0xc7, 0x3e,
    0xff, 0x1f, 0xe4, 0xb3, 0x28, 0x36, 0xe5, 0xdf, 0xb7, 0xae, 0x11, 0x66, 0xa9, 0x98, 0xb5, 0xa1, 0x78, 0xf9, 0x6f, 0xf3,
    0x78, 0xc8, 0x7f, 0xbc, 0xfc, 0x1f, 0x7f, 0xfc, 0xd7, 0xab, 0xac, 0xcd, 0xa5, 0xf8, 0x57, 0xe7, 0xd9, 0x23, 0xc9, 0x3f,
    0xf9, 0x77, 0xe9, 0x93, 0xb6, 0xab, 0x93, 0x8f, 0x9d, 0x7a, 0x72, 0x8b, 0x1a, 0xeb, 0xd8, 0x38, 0xeb, 0x7b, 0x51, 0x5f,
    0x12, 0xc5, 0x2c, 0xef, 0xe5, 0x5a, 0x56, 0xd5, 0xac, 0xef, 0xa9, 0x57, 0xff, 0x7f, 0xd1, 0xdb, 0x67, 0x9b, 0x7f, 0xb7,
    0x3e, 0xe9, 0xe3, 0xf9, 0x3f, 0xea, 0x11, 0x3c, 0xaf, 0xd8, 0x9a, 0x5d, 0x8d, 0xb7, 0xcd, 0xfc, 0x57, 0x9f, 0x93, 0x50,
    0x75, 0xf2, 0x18, 0x7b, 0x58, 0x77, 0x5d, 0xfb, 0x2c, 0x91, 0xd4, 0x8e, 0xdb, 0x18, 0xaa, 0xcb, 0x2e, 0xe4, 0xfd, 0xac,
    0xa6, 0x9c, 0xdc, 0x7a, 0x72, 0xb4, 0x67, 0x36, 0x7c, 0xff, 0xbf, 0xa6, 0xa7, 0xcf, 0x54, 0xb6, 0xd3, 0xfb, 0xff, 0x8f,
    0xe5, 0x61, 0xe0, 0x33, 0x30, 0xf5, 0x8a, 0x3c, 0xcc, 0xd6, 0x6d, 0xba, 0xff, 0xb7, 0xaf, 0x37, 0xcd, 0x3f, 0xff, 0xf1,
    0xeb, 0x9a, 0x6d, 0xed, 0xa1, 0xcf, 0x12, 0x49, 0xed, 0x95, 0x9a, 0x06, 0xec, 0x3b, 0x5f, 0x84, 0xfc, 0x6f, 0x76, 0x3a,
    0xff, 0xbf, 0x8b, 0x74, 0x06, 0x8e, 0xf2, 0x7f, 0xf4, 0xf8, 0x73, 0x4b, 0xf9, 0x7f, 0x57, 0xce, 0xca, 0x59, 0xf9, 0x6d,
    0xf6, 0xbf, 0x1f, 0xca, 0x07, 0xf2, 0x07, 0xf2, 0x4f, 0xfe, 0x83, 0xde, 0x8d, 0x68, 0xee, 0x59, 0x24, 0xff, 0x44, 0xaa,
    0x2f, 0x89, 0x34, 0xd0, 0x71, 0x69, 0xfb, 0x2d, 0xa7, 0x7e, 0x9e, 0xf5, 0xd4, 0x4f, 0xeb, 0x66, 0xcf, 0xca, 0xb3, 0xf2,
    0x9c, 0x3c, 0x27, 0xeb, 0xf2, 0x29, 0xaf, 0xd2, 0x5f, 0xcf, 0xd6, 0x32, 0x59, 0xdb, 0xdb, 0xd9, 0x9a, 0xdf, 0x91, 0x6d,
    0x79, 0xc5, 0x72, 0xd9, 0x9b, 0xca, 0xd2, 0x2d, 0xe7, 0xdf, 0xdc, 0xce, 0xe0, 0x76, 0x35, 0x72, 0xff, 0xdf, 0x76, 0xdb,
    0xc9, 0xa2, 0xe4, 0x7f, 0xbb, 0xd3, 0xf9, 0x9f, 0x38, 0xad, 0x1e, 0x39, 0xab, 0xfb, 0xf4, 0x7e, 0x54, 0xb1, 0xec, 0x75,
    0xf2, 0x4f, 0xfe, 0x2d, 0x6d, 0xe4, 0x1e, 0xef, 0x70, 0xfe, 0x77, 0x1a, 0xda, 0xb5, 0xec, 0x8f, 0xdc, 0x3c, 0xd6, 0x40,
    0xf3, 0xad, 0xa0, 0xee, 0xe6, 0xff, 0x05, 0x79, 0x43, 0xae, 0xcb, 0x9b, 0x72, 0xd3, 0xe2, 0x08, 0xcb, 0xf9, 0x7f, 0x4d,
    0xae, 0x1d, 0xf3, 0x59, 0xc3, 0x52, 0x9a, 0xd6, 0x28, 0xb7, 0xab, 0xa6, 0xbe, 0x95, 0x78, 0x90, 0xb7, 0x55, 0xdb, 0xb5,
    0x1a, 0x6a, 0xc6, 0x9a, 0xc4, 0xcb, 0x7f, 0xfd, 0xf1, 0xa4, 0x73, 0x1d, 0xff, 0xbb, 0xd1, 0xe1, 0xfc, 0xef, 0x05, 0xf9,
    0x24, 0xd7, 0x8f, 0xba, 0xb2, 0xf7, 0x89, 0xac, 0x97, 0xfe, 0xb9, 0xbc, 0xd6, 0x9e, 0x78, 0xd6, 0xff, 0x93, 0x6c, 0x2d,
    0x47, 0xf7, 0x12, 0xeb, 0xf2, 0xe9, 0x48, 0xdf, 0xff, 0xac, 0x3f, 0xff, 0x5d, 0xfa, 0x0c, 0x5b, 0x8e, 0xf1, 0x7f, 0xe4,
    0xbf, 0x6e, 0x0f, 0x6f, 0x75, 0x3e, 0xff, 0x7d, 0x45, 0xfe, 0x97, 0x3b, 0xff, 0x17, 0xe4, 0x82, 0x5c, 0xca, 0x96, 0xbe,
    0x9b, 0x8d, 0x67, 0xdb, 0xcd, 0xbf, 0xc1, 0xd2, 0xd4, 0x27, 0x6b, 0xea, 0x5d, 0xaf, 0x5e, 0xca, 0x6d, 0x9f, 0x27, 0x7b,
    0x78, 0xb9, 0xb2, 0x6f, 0xd5, 0xb4, 0xad, 0x72, 0xaf, 0xaa, 0x79, 0xac, 0xc1, 0x62, 0xf8, 0x89, 0xec, 0xcb, 0xbe, 0x9c,
    0x51, 0x9f, 0xff, 0xfd, 0x0a, 0x8f, 0xb4, 0xd2, 0xbb, 0x6e, 0x3a, 0x93, 0xe5, 0x9a, 0xbb, 0x66, 0xd4, 0xc0, 0x58, 0x71,
    0xfe, 0xc3, 0xf4, 0xe6, 0xeb, 0xef, 0x44, 0x63, 0xdd, 0x3b, 0xd9, 0xbe, 0x07, 0xb8, 0xf4, 0xe4, 0x25, 0x41, 0xbe, 0xc9,
    0x99, 0x46, 0xfc, 0x5e, 0x7b, 0xe2, 0x38, 0xd6, 0xae, 0xef, 0xae, 0x65, 0xc7, 0x79, 0x36, 0xc8, 0xf9, 0x3f, 0x3f, 0xd7,
    0xde, 0xb5, 0x3e, 0x7d, 0xff, 0x37, 0xf1, 0x68, 0x61, 0x9f, 0xdf, 0xf7, 0x7f, 0xc9, 0x3f, 0xf9, 0x27, 0xff, 0xcb, 0x9d,
    0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0xa4, 0x06, 0x9a, 0x75, 0x0d, 0x1b, 0xe6,
    0x2f, 0xaf, 0x9f, 0xeb, 0xde, 0x6d, 0x29, 0xf3, 0xf1, 0x0c, 0xa2, 0xef, 0xdd, 0xa9, 0x8a, 0x39, 0x06, 0xcc, 0x65, 0xe7,
    0x5e, 0xe2, 0xf3, 0xdf, 0xd6, 0x20, 0xe8, 0x95, 0xd4, 0xe6, 0xb9, 0x9a, 0xf7, 0x52, 0x03, 0xcb, 0x92, 0xa8, 0x37, 0x8c,
    0x92, 0xdd, 0x30, 0x33, 0x79, 0x1f, 0xed, 0xcf, 0xfc, 0xe7, 0x7e, 0x9c, 0xe7, 0xcc, 0x34, 0xbe, 0xbf, 0x4c, 0x1d, 0xfe,
    0x17, 0xd7, 0x43, 0x6f, 0xab, 0xad, 0xdf, 0xce, 0x6e, 0xf3, 0x4a, 0x6a, 0x67, 0xa9, 0xc4, 0x6b, 0x16, 0xf1, 0x78, 0xb3,
    0xf0, 0x93, 0x7f, 0xf2, 0x4f, 0xfe, 0x97, 0x37, 0xff, 0xf6, 0x57, 0x7a, 0xf8, 0xfc, 0xc7, 0x9d, 0x8f, 0xad, 0x58, 0x6f,
    0xa2, 0x2e, 0xc9, 0x45, 0xbe, 0x12, 0x63, 0x9d, 0x2b, 0xfd, 0x95, 0xd4, 0xa7, 0x92, 0x70, 0xbb, 0x9a, 0xdc, 0xca, 0xef,
    0x94, 0xc7, 0x76, 0x7c, 0x5a, 0x02, 0xc8, 0x3f, 0xf9, 0x27, 0xff, 0xe4, 0xbf, 0x8d, 0xfc, 0x97, 0x67, 0x10, 0x8d, 0x95,
    0xff, 0x62, 0x3b, 0x9a, 0xfc, 0x17, 0x73, 0x4a, 0x92, 0x7f, 0x9b, 0xf6, 0xab, 0xe3, 0xde, 0x5a, 0x98, 0xfc, 0x17, 0xb3,
    0x86, 0x56, 0x5f, 0x4d, 0xd5, 0xed, 0x72, 0xfe, 0xf9, 0x77, 0xdf, 0x4e, 0x5f, 0xf2, 0xaf, 0xbd, 0xa7, 0x74, 0xcd, 0xbf,
    0xfb, 0x9d, 0x54, 0x4a, 0xfe, 0x1d, 0xaf, 0xab, 0xc5, 0xc9, 0xbf, 0x6f, 0xab, 0x8b, 0x6b, 0xfe, 0xdd, 0xb7, 0x43, 0xfe,
    0xc9, 0x3f, 0xf9, 0x27, 0xff, 0xdd, 0xcd, 0xff, 0xb4, 0xbe, 0x3f, 0x7d, 0x36, 0xa9, 0xe7, 0xac, 0x44, 0xca, 0xff, 0x74,
    0x9e, 0xf7, 0x62, 0x3b, 0x63, 0x65, 0xfe, 0x0f, 0x22, 0xcd, 0xc9, 0xde, 0x8d, 0x9a, 0x7c, 0xd3, 0x71, 0x95, 0xef, 0xcd,
    0xb4, 0xfd, 0xca, 0x6d, 0xe5, 0xbf, 0xb8, 0x73, 0x1c, 0xa8, 0xcf, 0xd5, 0xbe, 0x8c, 0xe4, 0x92, 0xd5, 0x75, 0xbf, 0x52,
    0xba, 0x7a, 0x66, 0xaf, 0x2e, 0x53, 0xed, 0xbd, 0x28, 0xbf, 0xb1, 0x71, 0xa9, 0xd9, 0x71, 0x05, 0x76, 0xdb, 0xe9, 0x67,
    0xfe, 0x45, 0xb1, 0x1d, 0xff, 0xfe, 0x3f, 0xed, 0x27, 0xb9, 0x44, 0x9f, 0x93, 0xb9, 0x4b, 0x2d, 0x79, 0x21, 0x3f, 0xf5,
    0xda, 0xcf, 0xbf, 0x4f, 0x9b, 0xdc, 0x47, 0x22, 0x32, 0x52, 0x5c, 0xf7, 0xa9, 0x72, 0x16, 0x79, 0xd7, 0xb9, 0xe7, 0x53,
    0xa7, 0x1e, 0x57, 0xf2, 0x4f, 0xfe, 0xbb, 0x93, 0xff, 0x9b, 0x51, 0xf3, 0x7f, 0x4f, 0xee, 0xcb, 0x43, 0xef, 0xfc, 0x3f,
    0x10, 0x91, 0x77, 0xe5, 0x8c, 0x9c, 0x26, 0xff, 0x73, 0xcb, 0x7f, 0xdc, 0xfb, 0xff, 0x24, 0x48, 0xeb, 0x84, 0x44, 0xef,
    0x53, 0x72, 0xbb, 0xd7, 0xf3, 0x1d, 0x21, 0x92, 0x44, 0xbc, 0x46, 0xe2, 0xe6, 0x3f, 0xce, 0x48, 0xa8, 0x38, 0xef, 0x84,
    0x9a, 0x4c, 0x25, 0x2d, 0x7c, 0x3a, 0x92, 0x7f, 0xf2, 0x4f, 0xfe, 0xc9, 0xbf, 0xcf, 0xbe, 0x26, 0xb9, 0x15, 0xcf, 0xf6,
    0xbf, 0x18, 0x2d, 0x1c, 0x61, 0xf2, 0x5f, 0xee, 0xf7, 0x8d, 0x93, 0x7f, 0x4d, 0xeb, 0x9a, 0x69, 0x0f, 0x4d, 0x3d, 0xc4,
    0x9a, 0x52, 0xdf, 0xc8, 0x3d, 0xd6, 0xd1, 0xfc, 0x97, 0xdb, 0xfb, 0x44, 0x31, 0x92, 0xa4, 0x28, 0x2f, 0xf3, 0x19, 0xae,
    0xea, 0x87, 0x1f, 0x57, 0x8e, 0x13, 0xf1, 0xcf, 0x94, 0xb9, 0xbf, 0xbf, 0x1b, 0xf9, 0x8f, 0xf3, 0x09, 0xdb, 0xad, 0xfc,
    0xfb, 0x8e, 0xbf, 0x0a, 0xdf, 0xbb, 0x16, 0x66, 0xfc, 0xa4, 0xb6, 0xd4, 0x9f, 0xef, 0x68, 0xfe, 0x7d, 0xee, 0x95, 0x7d,
    0xc7, 0x85, 0x6a, 0x3e, 0xa7, 0xf5, 0x99, 0xd2, 0x8c, 0x10, 0x24, 0xff, 0xe4, 0x3f, 0x6e, 0xfe, 0xd7, 0x9d, 0xae, 0x91,
    0x1b, 0xe4, 0xbf, 0x37, 0xf9, 0x2f, 0xea, 0x9d, 0x07, 0xa5, 0x9e, 0xef, 0xba, 0xda, 0xe8, 0xa4, 0xae, 0x72, 0xa5, 0xb2,
    0xfe, 0x7a, 0xd0, 0x50, 0x27, 0xaa, 0x1f, 0xff, 0xab, 0xa9, 0xbf, 0x9a, 0xeb, 0xca, 0xe1, 0x32, 0xb9, 0x62, 0x1c, 0x35,
    0x50, 0xdf, 0x4f, 0xae, 0x29, 0x09, 0xdb, 0xd1, 0xe0, 0x27, 0x4b, 0xbd, 0xe8, 0x53, 0xde, 0x94, 0x91, 0xd5, 0x08, 0xd1,
    0x72, 0xa9, 0x6f, 0xc9, 0xae, 0xbc, 0xdc, 0x70, 0x5c, 0xb7, 0x15, 0xc7, 0xa5, 0xcf, 0xbf, 0x5b, 0xf9, 0xcd, 0xde, 0x05,
    0x4c, 0x5e, 0xf1, 0x50, 0x39, 0x92, 0xa4, 0xb8, 0xf3, 0x59, 0x51, 0x8c, 0x0b, 0xd1, 0x2c, 0xe5, 0x9f, 0xff, 0x54, 0xb6,
    0x64, 0x5b, 0xb6, 0x65, 0x47, 0x76, 0x64, 0x57, 0xf6, 0x64, 0x4f, 0x6e, 0xc9, 0xe5, 0x40, 0x77, 0x92, 0x21, 0x5a, 0xa3,
    0xd6, 0x82, 0x8f, 0x89, 0x0a, 0xd5, 0x56, 0xd6, 0xcf, 0xd1, 0x61, 0x76, 0xd6, 0x1a, 0x5a, 0xf2, 0xdc, 0xeb, 0x35, 0x77,
    0x82, 0xb7, 0x7a, 0xdd, 0xf0, 0x68, 0xf5, 0xd2, 0x7f, 0x0a, 0xde, 0xf7, 0x6c, 0x2b, 0x8b, 0x73, 0x5d, 0xf8, 0xe5, 0xbf,
    0xea, 0x71, 0xa7, 0x43, 0xdf, 0xff, 0x5f, 0x25, 0xff, 0x73, 0xc8, 0xff, 0x2a, 0xf9, 0xaf, 0x70, 0x8f, 0xfc, 0x07, 0xf9,
    0xfe, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xd0, 0x8a, 0x5f, 0x0b, 0x1f, 0x38, 0x2d,
    0x95, 0x2a, 0x7e, 0x79, 0x7c, 0xa0, 0x98, 0xe5, 0xca, 0xf4, 0x48, 0xbc, 0x8f, 0x64, 0x58, 0xda, 0xe7, 0x41, 0xf0, 0xe3,
    0xad, 0xdf, 0x56, 0xd3, 0x52, 0xf5, 0x5b, 0x09, 0xbb, 0x87, 0x3e, 0xc7, 0x34, 0xac, 0x5d, 0x6a, 0xa8, 0x38, 0x2f, 0x43,
    0xab, 0xa5, 0x52, 0xe7, 0xdf, 0xb6, 0xd7, 0x6d, 0x67, 0x10, 0x64, 0x29, 0x7d, 0xce, 0xc2, 0xef, 0x9d, 0x86, 0xef, 0x6c,
    0x34, 0x9a, 0x5f, 0x1e, 0x4e, 0x82, 0xcc, 0xd2, 0x58, 0xb7, 0xb7, 0xda, 0x23, 0xf1, 0x99, 0x3d, 0xc6, 0x7d, 0x1e, 0x48,
    0x9f, 0x99, 0x2a, 0xc3, 0xee, 0xa1, 0xcf, 0x31, 0xa5, 0x2d, 0xce, 0x92, 0xee, 0xff, 0xdb, 0xd6, 0x69, 0x07, 0xe6, 0x70,
    0x9a, 0xcf, 0xef, 0x8f, 0x77, 0x2b, 0xff, 0x9b, 0x33, 0xaf, 0x38, 0xe7, 0xf4, 0x29, 0xd6, 0xf4, 0xbe, 0x4b, 0xfe, 0xc9,
    0x3f, 0xf9, 0x77, 0xcf, 0xbf, 0xef, 0x9c, 0x01, 0x89, 0xf1, 0x6a, 0x1b, 0xe5, 0xff, 0x3a, 0x17, 0x60, 0xcf, 0x4d, 0xfb,
    0x30, 0x9d, 0xdf, 0xca, 0x66, 0x4f, 0x13, 0x8f, 0x39, 0x3b, 0x34, 0xf3, 0x83, 0xb8, 0x9f, 0xf3, 0xa4, 0xd5, 0x99, 0x12,
    0xdd, 0xcf, 0x72, 0xd8, 0xb2, 0x0b, 0x75, 0xa5, 0x77, 0xab, 0xb4, 0x7d, 0xe7, 0x1f, 0xec, 0x6f, 0xfe, 0xd3, 0x86, 0x7f,
    0xc7, 0xc9, 0xff, 0x36, 0xf9, 0x27, 0xff, 0xe4, 0xdf, 0xd0, 0x2e, 0xa1, 0x99, 0xd1, 0xdc, 0xf5, 0xca, 0x28, 0xb7, 0x54,
    0xf8, 0xb7, 0x5c, 0x98, 0x5a, 0x18, 0x27, 0x5e, 0xac, 0xd8, 0xcb, 0xe3, 0x73, 0x4e, 0x9e, 0x2a, 0xcd, 0x26, 0xaf, 0x9d,
    0xb3, 0x33, 0x55, 0xcc, 0x0f, 0x6a, 0xd7, 0x7a, 0x53, 0xb5, 0xad, 0x41, 0x84, 0x59, 0x45, 0xf5, 0x4b, 0xd4, 0x1f, 0xcf,
    0xe2, 0xe4, 0xdf, 0xee, 0x18, 0xfd, 0xf3, 0x5f, 0x9e, 0x89, 0xd5, 0x2e, 0xff, 0xc5, 0xb9, 0x0f, 0x95, 0xff, 0x53, 0xca,
    0x19, 0x8d, 0x43, 0x7e, 0x32, 0xcc, 0x43, 0x9b, 0xf7, 0x61, 0xe1, 0x66, 0xfa, 0x6e, 0xf7, 0x8e, 0x34, 0x56, 0x5b, 0x51,
    0x1f, 0xf2, 0xaf, 0x6d, 0x6d, 0x49, 0x02, 0xb5, 0x98, 0xd9, 0xb7, 0x82, 0xa4, 0xe4, 0x9f, 0xfc, 0x93, 0x7f, 0xf2, 0x1f,
    0x2c, 0xff, 0xe5, 0x19, 0xcd, 0x0f, 0xd4, 0xe3, 0x01, 0x96, 0x27, 0xff, 0xf1, 0x67, 0xfa, 0x0f, 0xbd, 0x87, 0x75, 0xfd,
    0xe5, 0x3e, 0x4b, 0x24, 0xb5, 0x77, 0x5c, 0x43, 0x75, 0xd9, 0x75, 0x25, 0xff, 0xd3, 0xbd, 0x9b, 0x3e, 0x9b, 0x9c, 0xcf,
    0x95, 0x48, 0xf9, 0xbf, 0x9a, 0xad, 0xbd, 0xd8, 0xce, 0x58, 0x99, 0xff, 0x03, 0x45, 0xd9, 0xb9, 0x95, 0x92, 0xdb, 0xec,
    0xd4, 0xcb, 0x91, 0xff, 0xf8, 0x33, 0x7d, 0xb7, 0xb5, 0x87, 0x61, 0xe6, 0x56, 0xf7, 0x9f, 0xc3, 0xbd, 0x2b, 0xf9, 0xd7,
    0xd4, 0x7f, 0xfd, 0xeb, 0x4e, 0x76, 0x9f, 0xe4, 0xbe, 0x65, 0x47, 0xfe, 0xc9, 0x3f, 0xf9, 0x27, 0xff, 0x6d, 0xf4, 0x07,
    0xf6, 0x2d, 0xff, 0xd2, 0xe2, 0x18, 0x96, 0x45, 0xbf, 0xff, 0x8f, 0x39, 0x86, 0xa5, 0xfd, 0xfc, 0xc7, 0xbd, 0xff, 0x4f,
    0x82, 0xb4, 0x4e, 0x90, 0x7f, 0xf2, 0x4f, 0xfe, 0xc9, 0x7f, 0xe8, 0xfc, 0xbb, 0x8f, 0x07, 0xe8, 0x5b, 0xfe, 0x35, 0xad,
    0x51, 0x6e, 0x67, 0xaf, 0x28, 0xcb, 0x69, 0x9b, 0xcf, 0xec, 0x38, 0x85, 0xe4, 0x90, 0x5d, 0xab, 0xe1, 0x6c, 0x0b, 0xad,
    0xfd, 0xa8, 0x81, 0xd0, 0xf9, 0xaf, 0x3f, 0x9e, 0x2e, 0xe4, 0x3f, 0xc9, 0xad, 0x78, 0xb6, 0xff, 0x49, 0xe5, 0x31, 0x76,
    0x21, 0xff, 0xe5, 0x74, 0xb6, 0x33, 0x8a, 0x2e, 0xe5, 0xfe, 0x9f, 0xf1, 0x7f, 0x41, 0x8f, 0x27, 0x46, 0xfe, 0xe3, 0x7c,
    0xc2, 0x76, 0xaf, 0xee, 0x94, 0x90, 0x7f, 0xf2, 0x4f, 0xfe, 0xc9, 0x7f, 0xb4, 0xfc, 0xaf, 0x18, 0xfb, 0x25, 0xab, 0xfa,
    0x8b, 0xc7, 0xf4, 0xff, 0x1b, 0xca, 0x52, 0x3b, 0x6a, 0x60, 0x5c, 0x2a, 0x5b, 0xbb, 0x1a, 0xa9, 0x4f, 0x6f, 0xbe, 0xee,
    0xda, 0x88, 0x7d, 0xef, 0x54, 0x5e, 0xf7, 0x41, 0xe3, 0xf1, 0x4c, 0xf6, 0xeb, 0x8a, 0xf7, 0x18, 0x8d, 0xf2, 0xb8, 0x5c,
    0xed, 0x98, 0x06, 0x7d, 0x69, 0x6b, 0xf3, 0x6f, 0x4e, 0x67, 0xe8, 0xfe, 0xc0, 0xb8, 0xdf, 0xce, 0x5c, 0xdc, 0xfe, 0xbf,
    0xbe, 0x7c, 0xff, 0x37, 0xf1, 0xee, 0x2b, 0xee, 0xca, 0xf7, 0x7f, 0xd7, 0x82, 0xf4, 0xd1, 0xfa, 0xf7, 0x69, 0xf6, 0xe7,
    0xfb, 0xbf, 0xe4, 0x9f, 0xfc, 0x2f, 0x4e, 0xfe, 0x57, 0xc9, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x4e, 0x19, 0x54, 0xfe, 0x86, 0x79, 0xdd, 0x2f, 0x99, 0x9f, 0xaa, 0xf9, 0xfd, 0x7f, 0xf3, 0x52, 0xdd, 0xd8,
    0x56, 0xd3, 0x6c, 0x66, 0xfa, 0x6d, 0xd5, 0xaf, 0x77, 0xd8, 0x30, 0x27, 0x7e, 0x3f, 0x97, 0x1a, 0x58, 0x96, 0x44, 0xbd,
    0x61, 0x43, 0xd9, 0x0f, 0x15, 0x25, 0x3e, 0xb4, 0xda, 0xfa, 0x50, 0x75, 0xe5, 0x97, 0xf7, 0x64, 0x79, 0xf2, 0x9f, 0x78,
    0xfc, 0x6a, 0xb2, 0xf6, 0xf7, 0xb0, 0xe7, 0xbf, 0xad, 0xb6, 0x7e, 0x45, 0x3b, 0x6d, 0x71, 0x3e, 0xd1, 0x76, 0x96, 0x4a,
    0xbc, 0xe6, 0x13, 0xb7, 0x9f, 0xe7, 0xc7, 0x5c, 0xe2, 0xa1, 0xe6, 0xf1, 0x6e, 0x9a, 0xcd, 0x88, 0xfc, 0x93, 0x7f, 0xf2,
    0xbf, 0xd8, 0xf9, 0xdf, 0x9c, 0x79, 0xf5, 0xb9, 0xfc, 0x7f, 0x47, 0x4b, 0x94, 0x7f, 0xae, 0x5f, 0xd3, 0xd5, 0x98, 0x2e,
    0x4c, 0xf9, 0x15, 0x47, 0x9e, 0x38, 0xcd, 0xda, 0xa1, 0x9f, 0xe1, 0xd1, 0x6e, 0xae, 0x3a, 0xdd, 0x7a, 0xed, 0x92, 0x6d,
    0x7e, 0xbf, 0x9f, 0x3c, 0x46, 0xf9, 0xbf, 0xce, 0xcd, 0x2c, 0xb1, 0xb9, 0x44, 0x9f, 0xfd, 0xe4, 0x9f, 0xfc, 0x2f, 0x6f,
    0xfe, 0x53, 0xd5, 0x12, 0xe4, 0xbf, 0xdf, 0x4b, 0x0d, 0xac, 0x5a, 0x0d, 0xa7, 0xde, 0x5a, 0x98, 0xfc, 0x97, 0xe7, 0x66,
    0xd5, 0xce, 0x70, 0xe9, 0x9a, 0x7f, 0xbb, 0xed, 0xcc, 0x2f, 0xff, 0xe5, 0xfd, 0xb1, 0x6b, 0x21, 0x26, 0xff, 0x7d, 0x5f,
    0xca, 0xce, 0xe2, 0xe4, 0xdf, 0xb7, 0xd5, 0x25, 0xf1, 0xc8, 0xa9, 0xbe, 0x9d, 0xa6, 0xbd, 0xfc, 0x83, 0xfc, 0x93, 0x7f,
    0xf2, 0x4f, 0xfe, 0xfb, 0x5a, 0x93, 0x6f, 0x9a, 0x75, 0xbe, 0xa8, 0x7d, 0x8e, 0x95, 0xa3, 0x06, 0xda, 0xcd, 0xff, 0x38,
    0xdf, 0x9b, 0x81, 0x7a, 0x26, 0xfd, 0x7d, 0x19, 0xc9, 0x25, 0xab, 0xfc, 0x97, 0xe7, 0x8c, 0x9f, 0x3e, 0xae, 0x66, 0xff,
    0x6b, 0xaa, 0xbd, 0x17, 0xe5, 0x37, 0x36, 0x2e, 0x35, 0xdb, 0x7f, 0x6e, 0xb7, 0x9d, 0x1d, 0xd9, 0x92, 0xdb, 0x96, 0xeb,
    0xd5, 0xe4, 0xbf, 0xd8, 0xff, 0xdb, 0xb2, 0x25, 0x3b, 0x24, 0x7d, 0xa1, 0xf2, 0xaf, 0x6f, 0x57, 0xd2, 0xce, 0xd8, 0xdd,
    0x56, 0xfe, 0x7d, 0xda, 0xe4, 0x3e, 0xca, 0x5b, 0xb0, 0x53, 0xa7, 0x1e, 0xb6, 0xc4, 0xa9, 0x5f, 0x38, 0x51, 0xb4, 0x9d,
    0x6a, 0x7a, 0x5c, 0x13, 0xc5, 0x15, 0x9b, 0xaa, 0x5b, 0x1f, 0x49, 0x3a, 0xf9, 0xd7, 0xe4, 0xff, 0x66, 0xd4, 0xfc, 0xdf,
    0x93, 0xfb, 0xf2, 0xd0, 0x3b, 0xff, 0x0f, 0x44, 0xe4, 0x5d, 0x39, 0x23, 0xa7, 0xc9, 0x3f, 0xf9, 0x9f, 0x53, 0xfe, 0x7d,
    0xee, 0x29, 0xed, 0xc6, 0x6c, 0xd4, 0x3f, 0xdc, 0xee, 0xec, 0xec, 0xb2, 0x12, 0x37, 0xff, 0x71, 0x46, 0x42, 0xc5, 0x79,
    0x27, 0x4c, 0x1d, 0xc7, 0xd3, 0xc5, 0xca, 0x29, 0xf7, 0xff, 0xe4, 0x9f, 0xfc, 0x93, 0x7f, 0xf2, 0xdf, 0x85, 0xfc, 0x6b,
    0x5a, 0xd7, 0xca, 0xdb, 0x2a, 0xf7, 0x4c, 0x9b, 0x7a, 0xa2, 0xc7, 0x8a, 0x76, 0xa5, 0x8d, 0xdc, 0x63, 0x1d, 0xcd, 0x7f,
    0xb9, 0xbd, 0xaf, 0xdc, 0x1e, 0x68, 0xce, 0x7f, 0xb9, 0xfc, 0x4c, 0x2d, 0xa1, 0xd5, 0x4b, 0x4d, 0xfe, 0x3e, 0x08, 0x90,
    0x7f, 0xfb, 0xfe, 0x7e, 0xf2, 0xbf, 0xb8, 0xf7, 0xff, 0xda, 0x6d, 0x25, 0xde, 0xb5, 0x06, 0xd3, 0x52, 0xcf, 0x77, 0x34,
    0xff, 0x3e, 0xf7, 0xca, 0x6e, 0xad, 0x06, 0x9a, 0xa5, 0x7c, 0x46, 0x42, 0x6a, 0xef, 0xb8, 0xc9, 0x3f, 0xf9, 0x8f, 0x97,
    0xff, 0x75, 0xa7, 0xeb, 0xf9, 0x06, 0xf9, 0x27, 0xff, 0x4b, 0xf1, 0xdd, 0xbf, 0xba, 0x7e, 0xf2, 0x83, 0x86, 0xda, 0xa1,
    0x5b, 0xe9, 0x4e, 0xd6, 0x75, 0xa5, 0xb6, 0x4f, 0x79, 0x53, 0x46, 0x56, 0x23, 0x51, 0xcb, 0xf5, 0xcc, 0x2d, 0xd9, 0x95,
    0x97, 0x1b, 0xfb, 0x7f, 0xed, 0x8f, 0x4b, 0x9f, 0x7f, 0xb7, 0xf2, 0x9b, 0xbd, 0x0b, 0x98, 0xbc, 0xe2, 0x61, 0xb6, 0xfc,
    0xe4, 0xd9, 0x8a, 0xd5, 0x35, 0x5d, 0xdc, 0xf9, 0x94, 0x7b, 0xf6, 0xd3, 0x40, 0x4b, 0xf9, 0xe7, 0x3f, 0x95, 0x2d, 0xd9,
    0x96, 0x6d, 0xd9, 0x91, 0x1d, 0xd9, 0x95, 0x3d, 0xd9, 0x93, 0x5b, 0x72, 0xd9, 0x38, 0x3a, 0xc1, 0x7c, 0x27, 0x59, 0x3f,
    0xca, 0x79, 0x96, 0x58, 0x95, 0x28, 0xc2, 0x8d, 0x0e, 0xb3, 0xb3, 0xd6, 0xd0, 0x92, 0xe7, 0xde, 0xff, 0x77, 0x27, 0x78,
    0xab, 0xd7, 0x0d, 0x8f, 0x56, 0x2f, 0xfd, 0xa7, 0xe0, 0x7d, 0xcf, 0xcf, 0xb4, 0x38, 0xa3, 0x06, 0xfd, 0xf2, 0x5f, 0xf5,
    0xb8, 0xd3, 0xb1, 0xef, 0xff, 0xa2, 0xed, 0xfc, 0xaf, 0x92, 0xff, 0x0a, 0xf7, 0xc8, 0x3f, 0xf9, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1c, 0x4c, 0x1f, 0x94, 0x03, 0x40, 0xfe, 0x01, 0x2c, 0x5d, 0xfe, 0xff, 0x0f };

// Font characters rectangles data
static const Rectangle fontRecs_Pixelnes[95] = {
    { 4, 4, 21 , 32 },
    { 33, 4, 17 , 19 },
    { 58, 4, 9 , 6 },
    { 75, 4, 14 , 15 },
    { 97, 4, 19 , 19 },
    { 124, 4, 19 , 19 },
    { 151, 4, 19 , 19 },
    { 178, 4, 3 , 6 },
    { 189, 4, 17 , 19 },
    { 214, 4, 17 , 19 },
    { 239, 4, 14 , 15 },
    { 261, 4, 14 , 15 },
    { 283, 4, 3 , 6 },
    { 294, 4, 14 , 3 },
    { 316, 4, 3 , 3 },
    { 327, 4, 19 , 19 },
    { 354, 4, 19 , 19 },
    { 381, 4, 17 , 19 },
    { 406, 4, 19 , 19 },
    { 433, 4, 19 , 19 },
    { 460, 4, 19 , 19 },
    { 4, 44, 19 , 19 },
    { 31, 44, 19 , 19 },
    { 58, 44, 19 , 19 },
    { 85, 44, 19 , 19 },
    { 112, 44, 19 , 19 },
    { 139, 44, 3 , 11 },
    { 150, 44, 3 , 14 },
    { 161, 44, 17 , 15 },
    { 186, 44, 14 , 9 },
    { 208, 44, 17 , 15 },
    { 233, 44, 19 , 19 },
    { 260, 44, 19 , 19 },
    { 287, 44, 19 , 19 },
    { 314, 44, 19 , 19 },
    { 341, 44, 19 , 19 },
    { 368, 44, 19 , 19 },
    { 395, 44, 17 , 19 },
    { 420, 44, 17 , 19 },
    { 445, 44, 19 , 19 },
    { 472, 44, 19 , 19 },
    { 4, 84, 17 , 19 },
    { 29, 84, 19 , 19 },
    { 56, 84, 19 , 19 },
    { 83, 84, 17 , 19 },
    { 108, 84, 19 , 19 },
    { 135, 84, 19 , 19 },
    { 162, 84, 19 , 19 },
    { 189, 84, 19 , 19 },
    { 216, 84, 19 , 19 },
    { 243, 84, 19 , 19 },
    { 270, 84, 19 , 19 },
    { 297, 84, 17 , 19 },
    { 322, 84, 19 , 19 },
    { 349, 84, 19 , 19 },
    { 376, 84, 19 , 19 },
    { 403, 84, 19 , 19 },
    { 430, 84, 17 , 19 },
    { 455, 84, 19 , 19 },
    { 482, 84, 17 , 19 },
    { 4, 124, 19 , 19 },
    { 31, 124, 17 , 19 },
    { 56, 124, 11 , 6 },
    { 75, 124, 22 , 3 },
    { 105, 124, 11 , 6 },
    { 124, 124, 19 , 19 },
    { 151, 124, 19 , 19 },
    { 178, 124, 19 , 19 },
    { 205, 124, 19 , 19 },
    { 232, 124, 17 , 19 },
    { 257, 124, 17 , 19 },
    { 282, 124, 19 , 19 },
    { 309, 124, 19 , 19 },
    { 336, 124, 17 , 19 },
    { 361, 124, 19 , 19 },
    { 388, 124, 19 , 19 },
    { 415, 124, 17 , 19 },
    { 440, 124, 19 , 19 },
    { 467, 124, 19 , 19 },
    { 4, 164, 19 , 19 },
    { 31, 164, 19 , 19 },
    { 58, 164, 19 , 19 },
    { 85, 164, 19 , 19 },
    { 112, 164, 19 , 19 },
    { 139, 164, 17 , 19 },
    { 164, 164, 19 , 19 },
    { 191, 164, 19 , 19 },
    { 218, 164, 19 , 19 },
    { 245, 164, 19 , 19 },
    { 272, 164, 17 , 19 },
    { 297, 164, 19 , 19 },
    { 324, 164, 17 , 19 },
    { 349, 164, 3 , 19 },
    { 360, 164, 17 , 19 },
    { 385, 164, 17 , 6 },
};

// Font glyphs info data
// NOTE: No glyphs.image data provided
static const GlyphInfo fontGlyphs_Pixelnes[95] = {
    { 32, 0, 26, 21, { 0 }},
    { 33, 0, 7, 18, { 0 }},
    { 34, 0, 7, 10, { 0 }},
    { 35, 0, 9, 16, { 0 }},
    { 36, 0, 7, 21, { 0 }},
    { 37, 0, 7, 21, { 0 }},
    { 38, 0, 7, 21, { 0 }},
    { 39, 0, 7, 5, { 0 }},
    { 40, 0, 7, 18, { 0 }},
    { 41, 0, 7, 18, { 0 }},
    { 42, 0, 9, 16, { 0 }},
    { 43, 0, 9, 16, { 0 }},
    { 44, 0, 23, 5, { 0 }},
    { 45, 0, 15, 16, { 0 }},
    { 46, 0, 23, 5, { 0 }},
    { 47, 0, 7, 21, { 0 }},
    { 48, 0, 7, 21, { 0 }},
    { 49, 0, 7, 18, { 0 }},
    { 50, 0, 7, 21, { 0 }},
    { 51, 0, 7, 21, { 0 }},
    { 52, 0, 7, 21, { 0 }},
    { 53, 0, 7, 21, { 0 }},
    { 54, 0, 7, 21, { 0 }},
    { 55, 0, 7, 21, { 0 }},
    { 56, 0, 7, 21, { 0 }},
    { 57, 0, 7, 21, { 0 }},
    { 58, 0, 15, 5, { 0 }},
    { 59, 0, 15, 5, { 0 }},
    { 60, 0, 9, 18, { 0 }},
    { 61, 0, 12, 16, { 0 }},
    { 62, 0, 9, 18, { 0 }},
    { 63, 0, 7, 21, { 0 }},
    { 64, 0, 7, 21, { 0 }},
    { 65, 0, 7, 21, { 0 }},
    { 66, 0, 7, 21, { 0 }},
    { 67, 0, 7, 21, { 0 }},
    { 68, 0, 7, 21, { 0 }},
    { 69, 0, 7, 18, { 0 }},
    { 70, 0, 7, 18, { 0 }},
    { 71, 0, 7, 21, { 0 }},
    { 72, 0, 7, 21, { 0 }},
    { 73, 0, 7, 18, { 0 }},
    { 74, 0, 7, 21, { 0 }},
    { 75, 0, 7, 21, { 0 }},
    { 76, 0, 7, 18, { 0 }},
    { 77, 0, 7, 21, { 0 }},
    { 78, 0, 7, 21, { 0 }},
    { 79, 0, 7, 21, { 0 }},
    { 80, 0, 7, 21, { 0 }},
    { 81, 0, 7, 21, { 0 }},
    { 82, 0, 7, 21, { 0 }},
    { 83, 0, 7, 21, { 0 }},
    { 84, 0, 7, 18, { 0 }},
    { 85, 0, 7, 21, { 0 }},
    { 86, 0, 7, 21, { 0 }},
    { 87, 0, 7, 21, { 0 }},
    { 88, 0, 7, 21, { 0 }},
    { 89, 0, 7, 18, { 0 }},
    { 90, 0, 7, 21, { 0 }},
    { 91, 0, 7, 18, { 0 }},
    { 92, 0, 7, 21, { 0 }},
    { 93, 0, 7, 18, { 0 }},
    { 94, 0, -1, 13, { 0 }},
    { 95, 0, 26, 21, { 0 }},
    { 96, 0, -1, 13, { 0 }},
    { 97, 0, 7, 21, { 0 }},
    { 98, 0, 7, 21, { 0 }},
    { 99, 0, 7, 21, { 0 }},
    { 100, 0, 7, 21, { 0 }},
    { 101, 0, 7, 18, { 0 }},
    { 102, 0, 7, 18, { 0 }},
    { 103, 0, 7, 21, { 0 }},
    { 104, 0, 7, 21, { 0 }},
    { 105, 0, 7, 18, { 0 }},
    { 106, 0, 7, 21, { 0 }},
    { 107, 0, 7, 21, { 0 }},
    { 108, 0, 7, 18, { 0 }},
    { 109, 0, 7, 21, { 0 }},
    { 110, 0, 7, 21, { 0 }},
    { 111, 0, 7, 21, { 0 }},
    { 112, 0, 7, 21, { 0 }},
    { 113, 0, 7, 21, { 0 }},
    { 114, 0, 7, 21, { 0 }},
    { 115, 0, 7, 21, { 0 }},
    { 116, 0, 7, 18, { 0 }},
    { 117, 0, 7, 21, { 0 }},
    { 118, 0, 7, 21, { 0 }},
    { 119, 0, 7, 21, { 0 }},
    { 120, 0, 7, 21, { 0 }},
    { 121, 0, 7, 18, { 0 }},
    { 122, 0, 7, 21, { 0 }},
    { 123, 0, 7, 18, { 0 }},
    { 124, 0, 7, 5, { 0 }},
    { 125, 0, 7, 18, { 0 }},
    { 126, 0, -1, 18, { 0 }},
};

// Font loading function: Pixelnes
static Font LoadFont_Pixelnes(void)
{
    Font font = { 0 };

    font.baseSize = 32;
    font.glyphCount = 95;
    font.glyphPadding = 4;

    // Custom font loading
    // NOTE: Compressed font image data (DEFLATE), it requires DecompressData() function
    int fontDataSize_Pixelnes = 0;
    unsigned char *data = DecompressData(fontData_Pixelnes, COMPRESSED_DATA_SIZE_FONT_PIXELNES, &fontDataSize_Pixelnes);
    Image imFont = { data, 512, 256, 1, 2 };

    // Load texture from image
    font.texture = LoadTextureFromImage(imFont);
    UnloadImage(imFont);  // Uncompressed data can be unloaded from memory

    // Assign glyph recs and info data directly
    // WARNING: This font data must not be unloaded
    font.recs = (Rectangle*) fontRecs_Pixelnes;
    font.glyphs = (GlyphInfo*) fontGlyphs_Pixelnes;

    return font;
}