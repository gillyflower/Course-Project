//
//  main.c
//  Course Project Chapter 10_with_functions
//
//  Created by Orval on 14.05.16.
//  Copyright (c) 2016 Gillian Holt. All rights reserved.
//

//
//  main.c
//  Course Project Chapter 10
//
//  Created by Orval on 24.04.16.
//  Copyright (c) 2016 Gillian Holt. All rights reserved.
//

//The fflush/scanf Problem:
/*First line of man fflush reads: The function fflush() forces a write of all user-space buffered data for the given output or update stream. cnicutar has the right answer for how to skip unwanted input, but in addition to that you should read the docs of the functions you're using. And check their return value... as your call above will have returned EOF and set errno = EBADF to signal your wrongful use of the function. Ignoring return values is bad, bad, bad */

/*This is well explained in the C FAQ. See also: explanation. The proposed solutions:
 
 Quit using scanf. Use fgets and the sscanf
 Use this to eat the newline
 
 while((c = getchar()) != '\n' && c != EOF);  discards the character
 The fact that flushing stdin works on some implementations is wrong.
 
 Some vendors do implement fflush so that fflush(stdin) discards unread characters, although portable programs cannot depend on this.*/

/*
 I also found this -
 int myint;
 char buff[BUFSIZ];
 fgets( buff, sizeof buff, stdin );
 sscanf( buff, "%d", &myint );
 */

// This last one works but it ignores everything after the first space. Solution is to use "%[^\n]"

/* The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
 
 Declaration
 Following is the declaration for fgets() function.
 
 char *fgets(char *str, int n, FILE *stream)
 Parameters
 str -- This is the pointer to an array of chars where the string read is stored.
 
 n -- This is the maximum number of characters to be read (including the final null-character). Usually, the length of the array passed as str is used.
 
 stream -- This is the pointer to a FILE object that identifies the stream where characters are read from. */



// 21.02.2016 New Version to allow storage of up to 100 cds




// 24.04.2016 Split into functions
// Create function called "output" to display details of one cd
// Create function called "enter" which takes one parameter - a string - which displays that string then waits for the user to press ENTER
// Create a function callled "yesno" that - like enter - displays its string parameter the reads one character from the keyboard until that char is a Y or a N then returns a value of 1 or 0
//Create a function "readInt"
//Create a function "readFloat"
//Create a function "readString" (Note that functions cannot return arrays but that array parameters can be modified by the function)
// Create a function to trim the newline character if there is one.
// Create a prototype for each function and put them in the header file


#include <stdio.h>
#include <ctype.h>              // Needed to use toupper
#include <string.h>             // Needae for strlen
#include "CDdata.h"             // The header file




int output (char title[], char artist[], int tracks, int album, float price)
{
    puts ("=======================================");                   // Note puts automatically adds a newline to the output
    printf ("Title: %s\n", title);
#ifndef NOARTIST                                                        // Think this is a MACRO. I need to check this
    printf ("Artist: %s\n", artist);
#endif
    printf ("Number of Tracks: %d\n", tracks);
    puts (album? "Album":"Single");
    printf ("Price: %.2f\n", price);
    puts ("========================================\n");
    
    return 0;                               // NOTE: Mark shows no retun value but the compiler requires it (control reaches end of non void function) so I am retuning 0
}

// enter ()
// Prompt the user for input and ask them to press enter

int enter (char prompt [])
{
    char buff[BUFSIZ];                      //Declares an array of size BUFFSIZ which is a constant defined in <stdio.h>
    
    
    fputs (prompt, stdout);                 // Prints the passed in prompt to the screen.
    fgets( buff, sizeof buff, stdin );      // I'm sure there is an easier way to do this in this case. He is just collecting the "Return" character!
    sscanf( buff, "%*c");                   //scan the keyboard buffer and throw awway the characters you find
    
    return 0;                               // NOTE: Mark shows no retun value but the compiler requires it (control reaches end of non void function) so I am retuning 0
}



// YesNo ()
// Ask the user a question and prompt for a Y or N (y or n) answer. No other answer will be acceptable.
// Function returns 1 for a Y and 0 for a N.

int yesNo (char prompt [])                  // EXAMPLE SAYS IT NEEDS TO BE AN INTEGER FUNCTION
// Prompt string to be passed in. Should not include a question mark.

{
    
    
    char buff[BUFSIZ];                      /* Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> */
    //memset(buff,0,sizeof(buff));            /* set the buffer with all zeros so that there is no garbage values in the buffer before it is used. */
    char answer;
    
    
    
    for (; ;)
        
    {
        fputs (prompt, stdout);             // Display the question to the user.
        fputs (" Y/N? ", stdout);            // Add a space and then a helpful prompt to the string passed in.
        
        
        fgets( buff, sizeof buff, stdin );
        sscanf( buff, " %[^\n]", &answer );  //ANSWER HERE IS A POINTER?
        
        
        
        
        
        
        // Process the Answer
        
        answer = toupper (answer);          /* Convert to uppercase. */
        if (answer == 'Y')
            return 1;                       /* Return is called here not at the end of the function! This is aparently fine to do. */
        /*"else" is not required here. WHY?? */
        if (answer == 'N')
            return 0;
        
        /* "else" is not required here either. WHY?? */
        
        
        printf("Error - only 'y/Y' or 'n/N' are allowed\n");    /* Error prompt on incorrect user input. */
        /* THIS IS PRODUCING ERRONEOUS OUTPUT. If the answer is not y or n the prompt is followed by
         "Database" or sometimes "atabase". It seems something is remaining in the output buffer?? */
        /* Its worse than that Jim. I just managed to get it to crash by typing zukzukzukzuk. Somehow this is getting put into bad memory addresses or something */
    }
    
}



/* readIntA () The simple version. I'm not sure if this is going to have a problem with the newline? If so use readIntB */
/* I was having a problem for a long time that yesNo would fail and skip ahead every second call. I traced it to a newline being left from this integer read */
/* Ask the user a question and read an integer answer from the keyboard. */
/* This now works because while((c = getchar()) != '\n' && c != EOF); */

int readIntA (char prompt [])
{
    
    int answer;
    int c;
    
    fputs (prompt, stdout);                 // Display the question to the user.
    scanf( "%d", &answer );                 // Trying %d and ^\n here as I am looking for an integer.
    while((c = getchar()) != '\n' && c != EOF);     /* Using this to eat the newline. It loops until it finds either a newline/return or EOF */
    
    
    return answer;
}

// readIntB () The more complicated version.
// Ask the user a question and read an integer answer from the keyboard.

int readIntB (char prompt [])
{
    char buff[BUFSIZ];                      //Declares an array of size BUFFSIZ which is a constant defined in <stdio.h>
    int answer;
    
    fputs (prompt, stdout);                 // Display the question to the user.
    fgets( buff, sizeof buff, stdin );
    sscanf( buff, "%d[^\n]", &answer );     // Trying %d and ^\n here as I am looking for an integer.
    
    return answer;
}

// readFloat ()
// Ask the user a question and read a floating point answer from the keyboard.


float readFloat (char prompt [])
{
    char buff[BUFSIZ];                      //Declares an array of size BUFFSIZ which is a constant defined in <stdio.h>
    float answer;
    
    fputs (prompt, stdout);                 // Display the question to the user.
    fgets( buff, sizeof buff, stdin );
    sscanf( buff, "%f[^\n]", &answer );     // Trying %d and ^\n here as I am looking for a float.
    
    
    return answer;
}


// readString ()
// Ask the user a question and prompt for a string answer.
// In the provided solution Mark Virtue is using an entirely different solution which involves calling the function trimnewline and passing in the 'answer' variable from this function.
// He is also using the parameter "MAX" to set the max read length. We dont need this as we are using "BUFSIZ"

int readString (char prompt [], char answer[]) // Functions cant return a string so we pass in another paramater "answer" which will be "modified" by the function when it runs.
{                                               // HAD TO SET FUNCTION TYPE TO CHAR TO STOP IT RETURNING NUMBERS
    char buff[BUFSIZ];                      //Declares an array of size BUFFSIZ which is a constant defined in <stdio.h>
    
    
    
    fputs (prompt, stdout);                 // Display the question to the user.
    fgets( buff, sizeof buff, stdin );
    sscanf( buff, "%[^\n]", answer );      // NOTE: NO AMPERSAND before answer. I had it in but comp complained so I took it out.
    
    
    
    return 0;                               // NOTE: Mark shows no retun value but the compiler requires it (control reaches end of non void function) so I am retuning 0
    
}




int main()

{
    // Declare variables
    
    //char type;                // used to read in the album/single info !!and is used to read user input (y/n)!!
    //char buff[BUFSIZ];    //Declares an array of size BUFFSIZ which is a constant defined in <stdio.h>
    
    //char buff[BUFSIZ];    //Declares an array of size BUFFSIZ which is a constant defined in <stdio.h> NOT USED IN THIS VERSION.
    //This belongs to the new fgets procedure I am trying (see also above)(line 69 etc)
    //char c;             //this varible belonged to the new while procedure I am using to discard the newline (line 79)
    
    char title [NO_CDS][TITLE_SIZE+1];     // Array of arrays for title
#ifndef NOARTIST
    char artist [NO_CDS][ARTIST_SIZE+1];    // Array of arrays for artist
#endif
    int tracks [NO_CDS];         // number of tracks on the album
    int album [NO_CDS];          // boolean - is album?
    float price [NO_CDS];        // float because it has decimal places
    int count =0;             // The loop counter for inputting the CD details
    int i;                    // The loop counter for outputting the CD details
    
    
    puts ("============================\n");
    puts ("Welcome to the CD Database. \n");
    printf ("You can store up to %lu CDs. \n", sizeof price/ sizeof price [0]); //COMPILER WARNING: Required unsigned long (lu) because of "sizeof". Was int (%d).
    puts ("============================\n\n\n");
    
    // Loop until the user does not want to enter more CDs
    
    for (; ;)                                                       //forever loop
    {
        // Ask if the user want to enter another CD?
        
        if (!yesNo("Have you any more CDs to enter"))             // If not return value from yesNo == 1 (eg it equals 0) then break.
            
            break;
        
        puts ("\n\n");
        printf ("Please enter the details of CD %d...\n\n", count+1);
        
        // Read in the details of the CD.
        
        
        readString ("Title?", title[count]);
#ifndef NOARTIST
        readString ("Artist?", artist[count]);
#endif
        tracks [count] = readIntA("Number of tracks?");           // Pass in the question we want to ask "Number of tracks" and readIntA will echo this to the user and return
        // their input to "tracks"
        album [count] = yesNo ("Is the CD an Album");               // Note there is no question mark and space here as the function is doing that for us. This is just to show
        // it can be done that way.
        
        price [count] = readFloat ("Retail price (e.g. 4,95)? ");
        
        /* Check to see if we have filled up the allocated array space. */
        
        if (++count == NO_CDS)      /* NOTE: The increment happens before the test. */
        {
            enter ("You have reached the storage limit\n"
                   "Press ENTER to continue: ");           /* NOTE: It is possible to separate two strings with a carriage return (to make the code more readable)
                                                            if each string is surrounded by "" and they will print as one string. */
            break;
        }
    }
    
    
    // we print all the CDs to the screen
    
    for (i =0; i< count; i++)
    {
        
        printf ("\nThe details of CD number %d:\n", i+1);
        puts ("=======================================");                   // Note puts automatically adds a newline to the output
        
        output (title[i], artist[i], tracks[i], album[i], price[i]);
        if (i< count -1)
            puts ("========================================\n");
        
        if (i< count -1)                                                    // If there are  more stored entries to see...
        {
            enter ("Please press return to see the next entry");
            
        }
        
    }
    
    
    // Print a user friendly way to exit the program (note I dont know if this will work as we are not going to use the depreciated getchar to end. Yes it works)
    
    enter ("Please press return to exit the program");
    
    puts ("Bye :)\n");
    
    
    return 0;
}