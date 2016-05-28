//
//  input.c
//  Course-Project
//
//  Created by Orval on 28.05.16.
//  Copyright (c) 2016 Gillian Holt. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>                                      /* Needed to use toupper */
#include <string.h>                                     /* Needae for strlen */
#include "CDdata.h"                                     /* The header file */



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




                            /* ------ Read CD -------*/


cd_t read_cd ()                                           /* Function of type cd_t (cd_t BECOMES THE TYPE e.g. int, float, char through "typedef"
                                                           which defines "sruct cd_type" as cd_t). This reads in the details of one CD */

                                                        /* This calls the necessary functions e.g. "readIntA" and passes the retun values into the FIELDS
                                                         of the struct e.g cd.tracks. NOTE: Each struct is just one cd */
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
        sscanf( buff, " %[^\n]", &answer );         /*ANSWER HERE IS A POINTER? Yes. This says >>>"ADDRESS OF answer"<<< */
        
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

