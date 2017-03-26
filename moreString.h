#ifndef MORE_STRING_H
#define MORE_STRING_H

#define TRUE	1	//success 
#define	FALSE	0	//error


void toLowercase(char * dest, char * origin, unsigned int nMax);
/*	Function toLowerCase

	Copies up to nMax characters from the origin string to the dest string. Any uppercase
letters will be copied as lowercase in dest. Any other type of character will be copied
as-is. Origin will not be modified in either case.
	Note that nMax does NOT include the string terminator, which will be added at the end
regardless of whether all of origin could be copied before reaching nMax or not. */

float getFloat(char * string, int * errorFlag);
unsigned int getUnsInt(char * string, int * errorFlag);
/*	Functions getFloat and getUnsInt
	
	Returns the float / unsigned int contained in the string. If the string did not contain
a number in the format specified, errorFlag will be FALSE (0), otherwise it will be TRUE (1).
	If there was an error, the number returned by the function will be meaningless */


#endif //MORE_STRING_H