//
//  output.c
//  Course-Project
//
//  Created by Orval on 28.05.16.
//  Copyright (c) 2016 Gillian Holt. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>                                      /* Needed to use toupper */
#include <string.h>                                     /* Needae for strlen */
#include "CDdata.h"                                     /* The header file */




/* ------ Print to Screen -------*/

int print_cd (cd_t cd)
{
    puts ("=======================================");    /* Note puts automatically adds a newline to the output */
    printf ("Title: %s\n", cd.title);
#ifndef NOARTIST                                         /* This is an ifdef defined in the header file to ignore this code if NOARTIST is defined */
    printf ("Artist: %s\n", cd.artist);
#endif
    printf ("Number of Tracks: %d\n", cd.tracks);
    puts (cd.album? "Album":"Single");
    printf ("Price: %.2f\n", cd.price);
    puts ("========================================\n");
    
    return 0;                                       /* NOTE: Mark shows no retun value but the compiler requires it
                                                     (control reaches end of non void function) so I am retuning 0 */
}


