
/*  main.c
  Course Project Chapter 10_with_functions

  Created by Orval on 14.05.16.
  Copyright (c) 2016 Gillian Holt. All rights reserved.
*/



/* 21.02.2016 New Version to allow storage of up to 100 cds */
/* 24.04.2016 Split into functions */
/* Testing Github */



#include <stdio.h>
#include "CDdata.h"                                     /* The header file */





                                        /* ------ Main Function -------*/

int main()

{
    
    cd_t cds [NO_CDS];                              /* An array of structures each containg one complete CD */
    int count =0;                                   /* The loop counter for inputting the CD details */
    int i;                                          /* The loop counter for outputting the CD details */
    
    
    puts ("============================\n");
    puts ("Welcome to the CD Database. \n");
    printf ("You can store up to %lu CDs. \n", sizeof cds / sizeof cds [0]); /* HOW DOES THIS WORK?
                                                                          Compiler Required unsigned long (lu) because of "sizeof". Was int (%d)*/
                                                                        /*I am getting an ERRONEOUS OUTPUT here it says "you can store up to 1 cds"
                                                                         I see Marks program does the same thing though??*/
                                                                        /* This used to be sizeof price / sizeof price [0] eg. size of the array price / sizeof the first element of that array. Now it is sizeof cds / sizeof cds which of course = 1 */
                                                                        /* Yup! that was his mistake :) */
    puts ("============================\n\n\n");
    
    
    
                                                /* Loop */
    
    for (; ;)                                                       /* forever loop until the user does not want to enter more CDs*/
    {                                                               /* Ask if the user want to enter another CD? */
        if (!yesNo("Have you any more CDs to enter"))               /* If not return value from yesNo == 1 (eg it equals 0) then break. */
            
            break;
        
        puts ("\n\n");
        printf ("Please enter the details of CD %d...\n\n", count+1);
        
        
                                                /* Read in the details of the CD. */
        
        
        cds [count] = read_cd();                                    /* Call the function "read_cd" It returns 1 CD which we then place in the array cds
                                                                     at the location "count" */
        
                                                                    /* Check to see if we have filled up the allocated array space. */
        if (++count == NO_CDS)                                      /* NOTE: The increment happens before the test. */
        {
            enter ("You have reached the storage limit\n"
                   "Press ENTER to continue: ");                    /* NOTE: It is possible to separate two strings with a carriage return 
                                                                     (to make the code more   readable) if each string is surrounded by "" and they will print as one string. */
            break;
        }
    }
                                                /* we print all the CDs to the screen */
    
    for (i =0; i< count; i++)
    {
        
        printf ("\nThe details of CD number %d:\n", i+1);
        puts ("=======================================");                   /* Note puts automatically adds a newline to the output */
        
        print_cd(cds [i]);                                                  /* We pass in the ith element of the array cds to the function "print_cd" 
                                                                             and it prints it out*/
        if (i< count -1)
            puts ("========================================\n");
        
        if (i< count -1)                                                    /* If there are  more stored entries to see... */
        {
            enter ("Please press return to see the next entry");
            
        }
        
    }
                                                                            /* Print a user friendly way to exit the program 
                                                                             (note we are not going to use the depreciated getchar to end.) */
    enter ("Please press return to exit the program");
    
    puts ("Bye :)\n");
    
    
    return 0;
}
