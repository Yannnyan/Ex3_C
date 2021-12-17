#include <stdio.h>
#include <stdlib.h>
#define WORD 30
#define TXT 1024
// read from a file here:
FILE *filePointer;

char *retMinSeq(){
    char * minseq;
    minseq = (char *)malloc(WORD*sizeof(char));
    char nextChar = fgetc(filePointer);
    int nextIndex=0;
    while(nextChar != '~' || nextChar != ' ' || nextChar != '\n' || nextChar != '\t'){
        minseq[nextIndex++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    minseq[nextIndex] = '\0';
    return minseq;
}

int gimatryValue(char *sequence){
    if(sizeof(sequence) == 1){
        return 0;
    }
    char nextChar = sequence[0];
    int currentIndex = 1;
    int gimatryVal=0;
    int curCharVal;
    while(nextChar != '\0' && nextChar != '~'){
        curCharVal = (int)nextChar;
        if(97 <= curCharVal && curCharVal <= 122){
            gimatryVal += curCharVal-96;
        }
        else if(65 <= curCharVal && curCharVal <= 90){
            gimatryVal += curCharVal-64;
        }
        nextChar = sequence[currentIndex++];
    }
    //printf("word received is : %s\n", sequence);
    //printf("Value of read word is : %d\n", gimatryVal);
    return gimatryVal;
}
int minSeq(int gimatryVal){
    // iterate untill geting useless value and then check gimatry 
    // if equals then print, else throw the sequence and start again
    char nextChar = fgetc(filePointer);
    char *word;
    word = (char *) malloc(WORD *sizeof(char));
    int nextIndex = 0;
    int true = nextChar == '~' ? 0 : 1;
    //printf("true is : %d\n", true);
    while(true == 1){
        if(nextChar == '\n' || nextChar == '\t' || nextChar == ' ' || nextChar == '~'){
            if(nextChar == '~'){
                true = 0;
            }
            word[nextIndex] = '\0';
            //printf("word passed to gimatryValue is %s\n: ", (word));
            int gimatSeqVal = gimatryValue(word);
            if(gimatSeqVal == gimatryVal){
                printf("%s\n",word);
            }
            nextIndex=0;
            word = (char *)realloc(word, WORD * sizeof(char));
        }
        //printf("current char is : %c\n",nextChar);
        if(nextChar != '~')
            word[nextIndex++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    free(word);
    //printf("ended minSeq\n");
    return 0;


}

int atBash(char * word){
    char c = word[0];
    int *wordLength = (int *) malloc(sizeof(int));
    *wordLength = 0;
    int  index=0;
    while(c != '\0'){
        *(wordLength)+=1;
        c = word[++index];
    }
    char * atbashWord = (char *) malloc(*(wordLength) * sizeof(char));
    char * reverseAtbashWord = (char *) malloc(*(wordLength) * sizeof(char));
    int currentIndex =0;
    int currCharValue;
    while(word[currentIndex] != '\0'){
        currCharValue = (int)word[currentIndex];
        if(97 <= currCharValue && currCharValue <= 122){
            atbashWord[currentIndex] = (char) (122 - (currCharValue - 97));
            reverseAtbashWord[*(wordLength)-currentIndex++] = (char) (122 - (currCharValue - 97));
            printf("atbash is : %s\n", atbashWord);
            printf("reverse atbash is : %s\n",reverseAtbashWord);
        }
        else if(65 <= currCharValue && currCharValue <= 90){
            atbashWord[currentIndex] = (char) (90 - (currCharValue - 65));
            reverseAtbashWord[*(wordLength)-currentIndex++] = (char) (90 - (currCharValue - 65));
            printf("atbash is : %s\n", atbashWord);
            printf("reverse atbash is : %s\n",reverseAtbashWord);
        }
    }
    char nextChar = getc(filePointer);
    int index1=0,index2=0;

    while(nextChar != '~'){
        if(nextChar != ' ' || nextChar != '\n' || nextChar != '\t'){
            if(nextChar == atbashWord[index1]){
                index1++;
            }
            else{
                index1 = 0;
            }
            if(nextChar == reverseAtbashWord[index2]){
                index2++;
            }
            else{
                index2 = 0;
            }
        }
        if(index1 == *(wordLength)){
            printf("%s~",atbashWord);
        }
        if(index2 == *(wordLength)){
            printf("%s~",reverseAtbashWord);
        }
        nextChar = getc(filePointer);
    }
    return 0;
}

int minSeqWithEmpty(int *wordABC){
    return 0;


}
int main(int argc, char* argv[]){
    // init word
    if(argc == 2){filePointer = fopen(argv[1], "r");}
    else{
        return 1;
    }
    char word[(WORD * sizeof(char))];
    char nextChar = fgetc(filePointer);
    int index =0;
    while(nextChar != '\n' && nextChar != '~'){
        word[index++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    word[index] = '\0';
    //printf("word receive is : %s\n",word);
    // print not valid if word[0] = '\0' if needed
    if(word[0] == '\0'){
        printf("cannot find word!");
        return 1;
    }
    //printf("%s", word);
    // calculate gimatric values of the word

    int gimatryWord = 0;
    int abc[52];
    index = 0;
    int charVal;
    do {
        charVal = (int) word[index++];
        if((charVal > 96 && charVal < 123)){
            // increment small letter
            abc[charVal - 97] +=1;
            gimatryWord += (charVal-96);
        }
        else if(charVal > 64 && charVal < 91){
            // increment big letter
            abc[charVal -65 + 26] +=1;
            gimatryWord += (charVal - 65);
        }
    }while(word[index] != '\0');
    //printf("gimatry value of the word is : %d\n ", gimatryWord);
    //enter code here:
    minSeq(gimatryWord);

    // reset to point to the first text char
    filePointer = fopen(argv[1],"r");
    while(fgetc(filePointer) != '\n'){};
    atBash(word);

    filePointer = fopen(argv[1],"r");
    while(fgetc(filePointer) != '\n'){};
    minSeqWithEmpty(abc);

    fclose(filePointer);
    return 0;
}
