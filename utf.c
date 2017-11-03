#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define cp(x) printf("check point: %d<---\n", x);
#define MAX 4
#define UNVALID 0
#define VALID 1
#define ASCII 2
#define LEADING 3
#define TRAILING 4


int no_of_bytes(char c);
int get_char(char* str, char* dest, int index);
int is_valid(unsigned char c);
int is_valid_ascii(unsigned char c);
int is_valid_leading(unsigned char c);
int is_valid_trailing(unsigned char c);
int check_valid(unsigned char c);
int no_of_tokens(char* p);
int index_of_char(char* src, int index);
int len_sub_str(char* src, int start, int end);
int sub_str(char* src, char* dest, int start, int end);


//~ int main() {
	//~ char st[100] = "ä␢/-Ö␢/␢/␢/␢/␢/Ä";
	//~ char de[5];
	//~ 
	//~ int b = get_char(st, de, 5);
	//~ printf("%s     %d\n", de, b);
	//~ b = get_char(st, de, -1);
	//~ printf("%s     %d\n", de, b);
//~ }


int check_valid(unsigned char c) {
    if(is_valid(c)) {
        if(is_valid_ascii(c)) {
            return ASCII;
        }
        if(is_valid_leading(c)) {
            return LEADING;
        }
        if(is_valid_trailing(c)) {
            return TRAILING;
        }
        return VALID;
    }
    else {
        return UNVALID;
    }
}

int is_valid(unsigned char c) {
    if((c == 0xFF) || (c == 0xFE)) {
        return 0;
    }
    else {
        return 1;
    }
}

int is_valid_ascii(unsigned char c) {
    if((c >= 0x00) && (c <= 0x7F)) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_valid_leading(unsigned char c) {
    if((c >= 0xC0) && (c <= 0xFD)) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_valid_trailing(unsigned char c) {
    if((c >= 0x80) && (c <= 0xBF)) {
        return 1;
    }
    else {
        return 0;
    }
}

int get_char(char* str, char* dest, int index) {
	
	int in = index_of_char(str, index);	
	char ch = str[in];
	int temp = check_valid(ch);
	if(temp == UNVALID) return 0;
	else if(temp == ASCII) {
		dest[0] = ch;
		dest[1] = '\0';
		return in;
	}
	else if(temp == LEADING) {
		dest[0] = ch;
		int no = no_of_bytes(ch);
		int i;
		int ans = in;
		int k = in + 1;
		for(i = 1; i < no; i++, k++) {
			if(TRAILING)
			dest[i] = str[k];
			else return 0;
		}
		dest[i] = '\0';
		return ans;
	}
	else {
		return -1;
	}
}

int index_of_char(char* src, int index) {
	int limit = no_of_tokens(src) ;
	if((index > limit) || (index < 0)) {
		printf("index is out of bounds");
		return -1;
	}
	
	int len = strlen(src);
	int i;
	int check = 0;
	int count = -1;
	for(i = 0; i < len; i++) {
		char temp = src[i];
		check = check_valid(temp);
		if(check == UNVALID){}
		else if(check == ASCII) count++;
		else if(check == LEADING) count++;
		else if(check == TRAILING){}
		else{};
		if(count == index) break;
	}
	return i;
}


int no_of_bytes(char c) {
    unsigned char ch = c;
    unsigned char runner = 128;
    char result = 0;
    int counter = 0;
    
    while(runner > 0) {
        result = ch & runner;
        if(result) {
            counter++;
            runner = (runner >> 1);
        }
        else {
            break;
        }
    }
    
    if(counter <= MAX) {
        return counter;
    }
    
    else { 
        printf("leading utf-8 byte malformed");
        return -1;
    }
    
}

int no_of_tokens(char* p) {
    unsigned char temp;
    int numb = 0;
    int count = 0;
    for(count = 0; ; count++) {
        temp = p[count];
        if(temp == '\0') {
            break;
        }
        if(!((temp >= 0x80) && (temp <= 0xBF))) {
            numb++;
        }
    }
    return numb;
}

int len_sub_str(char* src, int start, int end) {
	if(start >= end) {printf("shit"); return -3;}
	int len = no_of_tokens(src);
	if((start > len) || (start < 0)) return -1;
	if((end > len) || (end < 0)) return -2;
	
	int st = index_of_char(src, start);
	int en = index_of_char(src, end);
	en--;
	
	int ans = en - st;
	ans += 1;
	
	return ans;
		
}


int sub_str(char* src, char* dest, int start, int end) {
	int check = len_sub_str(src, start, end);
	if(check < 0) {printf("fuu");return -1;}
	
	int st = index_of_char(src, start);
	int en = index_of_char(src, end);
	en--;
	int i;
	int k;
	
	for(i = 0, k = st; k <= en; i++, k++) {
		dest[i] = src[k];
	}
	dest[i] = '\0';
	return 1;
		
}



