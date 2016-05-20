
/*  main.c
  Course Project Chapter 10_with_functions

  Created by Orval on 14.05.16.
  Copyright (c) 2016 Gillian Holt. All rights reserved.
*/



/* 21.02.2016 New Version to allow storage of up to 100 cds */
/* 24.04.2016 Split into functions */
/* Testing Github */



#include <stdio.h>
#include <ctype.h>                                      /* Needed to use toupper */
#include <string.h>                                     /* Needae for strlen */
#include "CDdata.h"                                     /* The header file */







                                        /* ------ Read CD -------*/


cd_t read_cd ()                                           /* Function of type cd_t (cd_t BECOMES THE TYPE e.g. int, float, char through "typedef"
                                                           which defines "sruct cd_type" as cd_t). This reads in the details of one CD */

                                                        /* This calls the necessary functions e.g. "readIntA" and passes the retun values into the FIELDS
                                                         of the struct e.g cd.tracks. NOT: Each struct is just one cd */
{
    
    cd_t cd;
    
        /* Read in the details of the CD. */
        readString ("Title?", cd.title);
#ifndef NOARTIST
        readString ("Artist?", cd.artist);
#endif
        cd.tracks  = readIntA("Number of tracks?");             /* Pass in the question we want to ask "Number of tracks"
                                                                     and readIntA will echo this to the user and return their input to "tracks"*/
        cd.album  = yesNo ("Is the CD an Album");               /* Note there is no question mark and space here as the function is doing that for us.
                                                                     This is just to show it can be done that way. */
        cd.price  = readFloat ("Retail price (e.g. 4,95)? ");
        
    
        return cd;
    
}





                                        /* ------ Print to Screen -------*/

int output (char title[], char artist[], int tracks, int album, float price)
{
    puts ("=======================================");    /* Note puts automatically adds a newline to the output */
    printf ("Title: %s\n", title);
#ifndef NOARTIST                                         /* This is an ifdef defined in the header file to ignore this code if NOARTIST is defined */
    printf ("Artist: %s\n", artist);
#endif
    printf ("Number of Tracks: %d\n", tracks);
    puts (album? "Album":"Single");
    printf ("Price: %.2f\n", price);
    puts ("========================================\n");
    
    return 0;                                       /* NOTE: Mark shows no retun value but the compiler requires it
                                                     (control reaches end of non void function) so I am retuning 0 */
}

                                        /* ------ Prompt User -------*/

int enter (char prompt [])
{
    char buff[BUFSIZ];                              /*Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> */
    
    fputs (prompt, stdout);                         /* Prints the passed in prompt to the screen. */
    fgets( buff, sizeof buff, stdin );              /* I'm sure there is an easier way to do this in this case. He is just collecting the "Return" character! */
    sscanf( buff, "%*c");                           /* scan the keyboard buffer and throw awway the characters you find */
    
    return 0;                                       /* NOTE: Mark shows no retun value but the compiler requires it
                                                     (control reaches end of non void function) so I am retuning 0 */
}


                                        /* ------ Read Yes No -------*/

                                                    /* Returns 1 for a Y and 0 for a N. */
int yesNo (char prompt [])                          /* EXAMPLE SAYS IT NEEDS TO BE AN INTEGER FUNCTION
                                                     Prompt string to be passed in. Should not include a question mark. */

{
    char buff[BUFSIZ];                              /* Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> */
    char answer;
    
    for (; ;)                                       /* Read user input and loop until correct input given */
        {
        fputs (prompt, stdout);                     /* Display the question to the user. */
        fputs (" Y/N? ", stdout);                   /* Add a space and then a helpful prompt to the string passed in. */
        fgets( buff, sizeof buff, stdin );
        sscanf( buff, " %[^\n]", &answer );         /*ANSWER HERE IS A POINTER? */
        
                                                    /* Process the Answer */
        answer = toupper (answer);                  /* Convert to uppercase. */
        if (answer == 'Y')
            return 1;                               /* Return is called here not at the end of the function! This is aparently fine to do. */
                                                    /*"else" is not required here. WHY?? */
        if (answer == 'N')                          /* "else" is not required here either. WHY?? */
            return 0;
        
        printf("Error - only 'y/Y' or 'n/N' are allowed\n");    /* Error prompt on incorrect user input. */
        
                                                    /* THIS IS PRODUCING ERRONEOUS OUTPUT. If the answer is not y or n the prompt is followed by
                                                    "Database" or sometimes "atabase". It seems something is remaining in the output buffer?? */
                                                    /* Its worse than that Jim. I just managed to get it to crash by typing zukzukzukzuk.
                                                    Somehow this is getting put into bad memory addresses or something */
    }
    
}


                                        /* ------ Read Integer -------*/

                                                    /* I was having a problem for a long time that yesNo would fail and skip ahead every second call.
                                                     I traced it to a newline being left from this integer read */
                                                    /* This now works because while((c = getchar()) != '\n' && c != EOF); */

int readIntA (char prompt [])
{
    int answer;
    int c;
    
    fputs (prompt, stdout);                         /* Display the question to the user. */
    scanf( "%d", &answer );                         /* Trying %d and ^\n here as I am looking for an integer. */
    while((c = getchar()) != '\n' && c != EOF);     /* Using this to eat the newline. It loops until it finds either a newline/return or EOF */
    
    return answer;
}

                                        /* ------ Read Integer -------*/

                                                    /* Im not using this one as the simpler version works */

int readIntB (char prompt [])
{
    char buff[BUFSIZ];                              /* Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> */
    int answer;
    
    fputs (prompt, stdout);                         /* Display the question to the user. */
    fgets( buff, sizeof buff, stdin );
    sscanf( buff, "%d[^\n]", &answer );             /* Trying %d and ^\n here as I am looking for an integer. */
    
    return answer;
}


                                        /* ------ Read Float -------*/


float readFloat (char prompt [])
{
    char buff[BUFSIZ];                              /* Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> */
    float answer;
    
    fputs (prompt, stdout);                         /* Display the question to the user. */
    fgets( buff, sizeof buff, stdin );
    sscanf( buff, "%f[^\n]", &answer );             /* Trying %d and ^\n here as I am looking for a float. */
    
    return answer;
}
                                        /* ------ Resd String -------*/


                                                    /* In the provided solution Mark Virtue is using an entirely different construct
                                                     which involves calling the function trimnewline and passing in the 'answer' variable from this function.
                                                     He is also using the parameter "MAX" to set the max read length. We dont need this as we are using "BUFSIZ" */

int readString (char prompt [], char answer[])      /* Functions cant return a string so we pass in another paramater "answer"
                                                     which will be "modified" by the function when it runs. */
{                                                   /* HAD TO SET FUNCTION TYPE TO CHAR TO STOP IT RETURNING NUMBERS */
    char buff[BUFSIZ];                              /* Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> */
    
    fputs (prompt, stdout);                         /* Display the question to the user. */
    fgets( buff, sizeof buff, stdin );
    sscanf( buff, "%[^\n]", answer );               /* NOTE: NO AMPERSAND before answer. I had it in but compiler complained so I took it out. */
    
    return 0;                                       /* NOTE: Mark shows no retun value but the compiler requires it
                                                     (control reaches end of non void function) so I am retuning 0 */
}


                                        /* ------ Main Function -------*/

int main()

{
    
    cd_t cds [NO_CDS];                              /* An array of structures each containg one complete CD */
    int count =0;                                   /* The loop counter for inputting the CD details */
    int i;                                          /* The loop counter for outputting the CD details */
    
    
    puts ("============================\n");
    puts ("Welcome to the CD Database. \n");
    printf ("You can store up to %lu CDs. \n", sizeof cds / sizeof cds); /* HOW DOES THIS WORK?
                                                                          Compiler Required unsigned long (lu) because of "sizeof". Was int (%d) */
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
