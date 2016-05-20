//
//  CDdata.h
//  Course Project Chapter 10
//
//  Created by Orval on 24.04.16.
//  Copyright (c) 2016 Gillian Holt. All rights reserved.
//


#define NO_CDS 100
#define TITLE_SIZE 60
#define ARTIST_SIZE 60
//#define NOARTIST


typedef struct cd_type cd_t;


                                    /*----- Prototypes of functions -----*/

int output (char title[], char artist[], int tracks, int album, float price);
int enter (char prompt []);
int yesNo (char prompt []);
int readIntA (char prompt []);
int readIntB (char prompt []);
float readFloat (char prompt []);
int readString (char prompt [], char answer[]);
cd_t read_cd ();
int print_cd (cd_t cd);




struct cd_type
{
    
    
    char title [TITLE_SIZE+1];
#ifndef NOARTIST
    char artist [ARTIST_SIZE+1];
#endif
    int tracks;
    float price;
    int album;                          /* Boolean - is the cd an album? */
    
};



