#ifndef utf
#define utf

/*
 * these are functions that help out dealing with myltibyte charactes.
 * Its easy when you only mange ascii which is one character per char
 * unit. But weird characters like ÄΣ❖❤ﺝЯ␢ dont fit into just one
 * char. because chars are already used to store ascii characters.
 * UTF-8 is one of the most popular solutions.
 * It concists of a multibyte sequence. usually 1-4 bytes (1-4 chars)
 * with the first char either being within ascii range, thus being a 
 * character by its own. Or a leading byte, that tells how many
 * trailing bytes will follow that together build up a single character.
 * Thus one char per character doesnt apply anymore. Since one
 * character could consist of one, two, three or more bytes.
 * Instead other methods must be used to count letters in a string etc.
 * And this is where this header comes in.
 */
 

#define MAX 4
#define UNVALID 0
#define VALID 1
#define ASCII 2
#define LEADING 3
#define TRAILING 4
 
// this function tests if the char is a valid utf-8 byte in a more
// general sense.
int is_valid(unsigned char c);

// checks if the char is an ascii byte according to utf-8.
int is_valid_ascii(unsigned char c);

// checks if the char is a leading char containing info about
// the number of trailing bytes.
int is_valid_leading(unsigned char c);

// checks if the byte is a typical trailing byte usually following
// after a leading byte.
int is_valid_trailing(unsigned char c);

// combines the above mentioned validity checks and returns
// the kind of byte it is.
int check_valid(unsigned char c);

// in: leading byte. Out, returns Int number of trailing bytes expected.
//including the leading byte. 
int no_of_bytes(char c);

// returns number of actual characters cointained in a array of chars.
//As opposed to the ammount of bytes they are comprised of.
int no_of_tokens(char* p);

// gets the char at index token, that is the number of the visible
//actual character and puts all the bytes its comprised of in dest.
//returns -1 if something goes wrong, or the index of the actual char
//in src where the visibal character starts.
int get_char(char* str, char* dest, int index);

//returns the underlying index of the leading byte of the bytes that
//are responsible of rendering the human visible character at the point
//index. The index being used as an argument is the index beginning
//at 0 of the letters or characters actually being countable
//by a human.
int index_of_char(char* src, int index);

//returns how many chars the substring is comprised of.
//end argument being exclusive. Thus to get last character one must
//actually set end parameter to the index where '\0' would be
//situated
int len_sub_str(char* src, int start, int end);

//takes the substring between start inclusive and end exclusive,
//then copies that string to dest, and appends '\0' to the end.
int sub_str(char* src, char* dest, int start, int end);



#endif

