#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ADD dest[i] = src[k]

int size_of_result(char* src);
int num_of_commas(int n);
void commatize(char* src, char* dest);
int search_blank_symbol(char* p);
void replace_blanks(char* p);

int spacing = 5;
char comma[] = "❚-❚";
int size_first = 0;
int size_second = 0;

int main() {
    //char str[] = "␢␢␢$-1400001.123456789±100 millions.";
    char str[] = "pi=3.14159265358979323846264338327950288419716939937510582097494459231";  
    printf("original:\n%s\n", str);
    int size = size_of_result(str);
    char result[size + 1];
    commatize(str, result);
    printf("result:\n%s\n", result);
    
}        

int size_of_result(char* src) {
    int len = strlen(src);
    int i;
    char c;
    int counter1 = 0;
    int counter2 = 0;
    int size;
    int mark = 0;
    
    if(search_blank_symbol(src)) size = -6;
    
    for(i = 0; i < len; i++) {
        c = src[i];
        if(isdigit(c) && (c != '0')) {
            break;
        }
        else {

        }        
    }
    
    for(; i < len; i++) {
        c = src[i];
        if(isdigit(c)) {
            if(mark) {
                counter2++;
            }
            else counter1++;
        }
        else {
            if(mark) break;
            
            if(c == '.') {
                mark = 1;
            } 
            else break;
        }
    }
    
    size_first = counter1;
    size_second = counter2;
    int commas = num_of_commas(counter1);
    commas += num_of_commas(counter2);
    size = commas * strlen(comma);
    
    return len + size;
    
}

int num_of_commas(int n) {
	if(spacing <= 0) return 0;
    int no_of_commas = n / spacing;
    if((n % spacing) == 0)
    no_of_commas--;
    return no_of_commas; 
}

int calc_jump(int n) {
	if(spacing <= 0) return 0;
    int num = n % spacing;
    if(num == 0) num = spacing;
    return num;
}

void commatize(char* src, char* dest) {
    if(search_blank_symbol(src)) {
        replace_blanks(src);
    }
    int srclen = strlen(src);
    int initial_jump = calc_jump(size_first);
    int comlen = strlen(comma);
    char c;
    int i = 0;
    int k = 0;
    int p = 0;
    int mark = 0;
    int commas = num_of_commas(size_first);
    // adding initial zeroes and letters NOT to be commatized.
    for(i = 0, k = 0; k < srclen; i++, k++) {
        c = src[k];
        if(isdigit(c)) {
            if(c == '0') {
                ADD;
            }
            else {
                break;
            }
        }
        else ADD;
    }
    //jumps over the first numbers so that commatizing starts
    //at the right position.
    //ie. 1,000,000. instead of 100,000,0.
    for(p = 0; p < initial_jump; p++, i++, k++) {
        ADD;
    }
    //adds comma symbols and correct ammount of jumps between them
    int counter = 0;
    for(; (k < srclen) && (!mark) && (counter < commas); ) {
        
        for(p = 0; p < comlen; p++, i++) {
            dest[i] = comma[p];
        }
        counter++;
        for(p = 0; p < spacing; p++, k++, i++) {
            c = src[k];
            if(c == '.') {
                mark = 1;
                break;
            }
            else {
                ADD;
            }

        }
    }
    ADD;
    i++; k++;
    if(size_second > 0) {
        commas = num_of_commas(size_second);
        counter = 0;
        int cntr = 0;
        while((counter < commas)) {
            
            for(p = 0; (p < spacing) && (cntr < size_second); p++, i++, k++) {
                if(cntr >= size_second) break;
                ADD; cntr++;
            }
            for(p = 0; (p < comlen) && (counter < commas); p++, i++) {
                dest[i] = comma[p];
            }
            counter++;            
        }
    }
    
    for(; k < srclen; i++, k++) {
        ADD;
    }    
    dest[i] = '\0';
    
}

int search_blank_symbol(char* p) {
    //utf-8 encoded space symbol character takes three bytes.
    char arr[] = {226, 144, 162, '\0'};
    int counter = 0;
    int i = 0;
    int k = 0;
    
    for(i = 0; i < 9;) {
        for(k = 0; k < 3; k++, i++) {
            if(p[i] == arr[k]) {
                counter++;
            }
        }        
    }
    if(counter == 9)
    return 1;
    else return 0;
}

void replace_blanks(char* p) {
    int original_length = strlen(p);
    char result[original_length + 1];
    char spaces[] = "   ";
    char left[original_length + 1];
    int i;
    int k;
    for(i = 9, k = 0; i < original_length; i++, k++) {
        left[k] = p[i];
    }
    left[k] = '\0';
    strcpy(result, spaces);
    strcat(result, left);
    strncpy(p, result, original_length);
}

