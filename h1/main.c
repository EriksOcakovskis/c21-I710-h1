//
//  main.c
//  h1
//
//  Created by Eriks Ocakovskis on 04/10/2017.
//  Copyright © 2017 Eriks Ocakovskis. All rights reserved.
//
// The program should output the differences
// between consecutive values as the index increases.
//
// Output should be printed as a comma separated list of values
// on a single line to stdout.
//

#include <stdio.h>
#include <stdlib.h>

int fileToString(const char** f , char** str) {
    long fLength = 0;
    char* temp;
    
    FILE* fp = fopen(*f, "r");
    
    if (!fp) {
        return 1;
    }

    fseek (fp, 0, SEEK_END);
    fLength = ftell(fp);
    rewind(fp);
    temp = malloc(sizeof(char)*(fLength + 1));
    
    if (!temp)
    {
        fclose(fp);
        return 1;
    }
    
    fread(temp, sizeof(char), fLength, fp);
    temp[fLength] = '\0';
    *str = temp;

    fclose(fp);
    return 0;
}

int main(int argc, const char * argv[]) {
    char* _inputString;
    const char* FILE_NAME;
    int _valuePairCount = 0;
    int _digit = 0;
    int _indexFromValuePair = 0;
    
    if (argv[1]) {
        FILE_NAME = argv[1];
    } else {
        FILE_NAME = "input.txt";
    }
    
    int errorCode = fileToString(&FILE_NAME, &_inputString);
    
    if (errorCode == 1) {
        return 1;
    }
    
    char* _valueStore = malloc(1 * sizeof(char));

    if (_inputString) {
        for (int i=0; _inputString[i] != '\0'; ++i) {
            if (_inputString[i] == ',') {
                _valuePairCount++;
            }
        }
    }
    
    if (_valuePairCount <= 1) {
        printf("%i", 0);
        return 0;
    }
    
    int _rl[_valuePairCount];
    
    for (int i=0; _inputString[i] != '\0'; ++i) {
        switch (_inputString[i]) {
            case ',':
                //index ends
                
                _indexFromValuePair = atoi(_valueStore);
                
                _valueStore[_digit-1] = '\0';
                _digit = 0;
                break;
            case ';':
                //value pair ends
                
                _rl[_indexFromValuePair] = atoi(_valueStore);
                
                _valueStore[_digit-1] = '\0';
                _digit = 0;
                break;
            default:
                _valueStore[_digit] = _inputString[i];
                _digit++;
                break;
        }
    }
    _rl[_indexFromValuePair] = atoi(_valueStore);
    
    for(int i=0; i < _valuePairCount - 1; ++i)
    {
        printf("%i",_rl[i+1] - _rl[i]);
        
        if (i < (_valuePairCount -2)) {
            printf(",");
        }
    }
    
    free(_inputString);
    free(_valueStore);
    return 0;
}
