/* String Central
 * CS 480 - Assignment 2
 * 
 * By Andrew Stebenne
 * 4 February, 2015
 *
 *
 * String Central is a function which processes input strings according to a
 * selected function from an array of [pointers to] functions which modify
 * strings. 
 *
 * Here, giving the main function an input string will cause it to print out
 * the result of all the available transformations on that string.
 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* char_double(char* str);
char* char_shift(char* str);
char* char_flip(char* str);


char* char_double(char* str)
{
    int length = strlen(str);
    // Output should be twice the length of the input
    char* output = malloc( sizeof(char) * length * 2 );
    char* str_iterator = str;
    char* out_iterator = output;

    // Copy the i'th char into the i'th and i+1'th spots
    while( *str_iterator )
    {
        // Copy into the i'th position
        *out_iterator = *str_iterator;
        out_iterator++;
        // Copy into the i+1'th position
        *out_iterator = *str_iterator;
        out_iterator++;

        // Now move the pointer to str forward
        str_iterator++;
    }

    return output;

}

char* char_shift(char* str)
{   // For each letter at position i in the input string, the output string
    // should have the same letter at position 2*i, plus the next
    // letter at position (2*i) + 1

    int length = strlen(str);
    // Output should be twice the length of the input
    char* output = malloc( sizeof(char) * length * 2 );
    char* str_iterator = str;
    char* out_iterator = output;
    char temp;

    while( *str_iterator )
    {
        // Copy the i'th char into the i'th spot
        *out_iterator = *str_iterator;
        out_iterator++;
        // Copy (str[i] + 1) into position i+1
        temp = *str_iterator + 1;
        *out_iterator = temp;
        out_iterator++;
        str_iterator++;
    }

    return output;
    
}

char* char_flip(char* str)
{   // Should reverse upper and lower cases in the input string

    int length = strlen(str);
    // Output should be twice the length of the input
    char* output = malloc( sizeof(char) * length * 2 );
    char* str_iterator = str;
    char* out_iterator = output;

    while( *str_iterator )
    {
        if( islower( *str_iterator ) )
        {
            *out_iterator = toupper(*str_iterator);
        }
        else if( isupper( *str_iterator ) )
        {
            *out_iterator = tolower(*str_iterator);
        }
        else
        {   // If it's not a letter, just leave it alone.
            *out_iterator = *str_iterator;
        }

        out_iterator++;
        str_iterator++;
    }
    return output;

}


char** string_central(
        char* (*functions[])(char*),
        char* input_string )
{
    // Pointer into the function array
    char* (*f_iterator)(char*) = *functions;

    // Length of the input string
    int length = strlen(input_string); 

    // out_array will hold three pointers to the strings we've modified.
    char** out_array;
    out_array = malloc( sizeof(char*) * 4 );
    out_array[0] = malloc( sizeof(char) * length * 2 );
    out_array[1] = malloc( sizeof(char) * length * 2 );
    out_array[2] = malloc( sizeof(char) * length );
    out_array[3] = malloc( sizeof(char) );

    // Copy from the output of (the function that we are currently pointing
    // at) into (the corresponding space in out_array), iterate and do the
    // same again.
    strcpy( out_array[0], functions[0](input_string) );
    strcpy( out_array[1], functions[1](input_string) );
    strcpy( out_array[2], functions[2](input_string) );
    strcpy( out_array[3], "\0" );

    return out_array;

}


int main( int argc, char* argv[] )
{
    char* (*first)(char*) = char_double;
    char* (*second)(char*) = char_shift;
    char* (*third)(char*) = char_flip;

    char* ( *processors[] )( char* ) = {first, second, third, NULL};
    
    // out_array will hold pointers to the strings we processed
    char** out_array = string_central( processors, argv[1] );

    // Iterator to read from out_array
    char** read_out = out_array;
    while( *read_out )
    {
        printf( "%s\n", *read_out );
        read_out++;
    }


    return 0;
    
}
