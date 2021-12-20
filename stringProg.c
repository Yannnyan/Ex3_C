#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#define WORD 30
#define TXT 1024
// read from a file here:
FILE *filePointer, *outPointer;

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
int minSeq(int gimatryVal,char * text){
    // iterate untill geting useless value and then check gimatry 
    // if equals then print, else throw the sequence and start again
    int index1=0, index2=0, wordIndex = 0, first =1;
    //printf("hello im minseq\n");
    char *word = (char *) calloc(sizeof(char), WORD);
    //printf("The text is : %s\n",text);
    int GimatryWordVal=0, currentCharVal = 0;
    while(text[index1] != '\0'|| text[index2] == '~'){
        currentCharVal = (int)text[index1];
        // get the next character that is not an empty char
        while((currentCharVal < 65 || (currentCharVal > 90 && currentCharVal < 97) || currentCharVal > 122)
         && text[index1] != '~'){
            index1+=1;
            currentCharVal = text[index1];
        }
        word[wordIndex++] = text[index1];
        if(text[index1] == '~') 
            break;
        if(65 <= currentCharVal && currentCharVal <= 90){
            GimatryWordVal += (currentCharVal -65 +1);
        }
        else if(97 <= currentCharVal && currentCharVal <= 122){
            GimatryWordVal += (currentCharVal - 97 +1);
        }
        // printf("The current character is : %c\n", text[index1]);
        // printf("The Current Gimatry Value is : %d\n", GimatryWordVal );
        index2 = index1 +1;
        // printf("text at index1 is : %c\n", text[index1]);
        // printf("text at index2 is : %c\n", text[index2]);
        while(text[index2] != '\0' && text[index2] != '~'){
            if(GimatryWordVal < gimatryVal){
               // increment gimatry value
                // printf("The current char is : %c\n", text[index2]);
                // printf("The gimatry value is : %d\n", GimatryWordVal);
                currentCharVal = (int)text[index2];
                //printf("The ascii value of the char is : %d", currentCharVal);
                if(65 <= currentCharVal && currentCharVal <= 90){
                    GimatryWordVal += (currentCharVal -65 +1);
                }
                else if(97 <= currentCharVal && currentCharVal <= 122){
                    GimatryWordVal += (currentCharVal - 97 +1);
                }
                word[wordIndex++] = text[index2];
            }
            //
            if(GimatryWordVal == gimatryVal){
                //printf("printing the word\n");
                if(first == 1){
                    fprintf(outPointer,"%s", word);first=0;
                }
                else
                    fprintf(outPointer,"~%s", word);
                free(word);
                word = (char *)calloc(sizeof(char), WORD);
                wordIndex=0;
                GimatryWordVal = 0;
                break;
            }
            if(GimatryWordVal > gimatryVal){
                // reset word
                free(word);
                word = (char *)calloc(sizeof(char), WORD);
                GimatryWordVal = 0;
                wordIndex = 0;
                break;
            }
            index2++;
        }
        
        index1++;
    }
    //word[0] = 's';
    free(word);
    //free(text);
    return 0;


}

int atBash(char * word, char * text){
    char c = word[0];
    int currentCharIndex=0;
    int wordLength = 0;
    int  index=0;
    while(c != '\0'){
        (wordLength)+=1;
        c = word[++index];
    }
    char * atbashWord = (char *) calloc(sizeof(char), (wordLength+1));
    char * reverseAtbashWord = (char *) calloc(sizeof(char), (wordLength+1));
    int currentIndex =0;
    int currCharValue;
    //init the atbash word
    while(word[currentIndex] != '\0'){
        currCharValue = (int)word[currentIndex];
        if(97 <= currCharValue && currCharValue <= 122){
            atbashWord[currentIndex] = (char) (122 - (currCharValue - 97));
            currentIndex+=1;
            //printf("atbash is : %s\n", atbashWord);
        }
        else if(65 <= currCharValue && currCharValue <= 90){
            atbashWord[currentIndex] = (char) (90 - (currCharValue - 65));
            currentIndex+=1;
            //printf("atbash is : %s\n", atbashWord);
        }
       // printf("current char is %d\n", word[currentIndex]);
        if(word[currentIndex] == '\0'){
            break;
        }
    }
    atbashWord[currentIndex] = '\0';
    currentIndex = 0; index = wordLength-1;
    //printf("getting the reverse atbash values, index is : %d\n",index);
    while(index >=0 ){
        //printf("The current char is : %c\n",atbashWord[index]);
        reverseAtbashWord[currentIndex++] = atbashWord[index--];
    }
    reverseAtbashWord[currentIndex] = '\0';
    //printf("Reverse atbash is : %s\n", reverseAtbashWord);
    char nextChar = text[currentCharIndex++];
    //printf("this char is : %c", nextChar);
    int index1=0,index2=0,first =1;

    while(nextChar != '~'){
       //printf("Current char is : %d\n", nextChar);
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
        if(index1 == (wordLength)){
            if(first == 1){
                fprintf(outPointer,"%s",atbashWord);first = 0;
            }
            else{
                fprintf(outPointer,"~%s", atbashWord);
            }
        }
        if(index2 == (wordLength)){
            if(first == 1){
                fprintf(outPointer,"%s",reverseAtbashWord);first = 0;
            }
            else{
                fprintf(outPointer,"~%s", reverseAtbashWord);
            }
        }
        nextChar = text[currentCharIndex++];
    }
    free(atbashWord);
    free(reverseAtbashWord);
    return 0;
}

int minSeqWithEmpty(char *wordABC, char * text){
    int asciWordTable[92]={0}, asciSeqTable[92]={0};
    char nextChar;
    int nextCharValue, nextIndex=1, wordLen = 0;;
    nextChar = wordABC[0];
    if(nextChar == '\0')return 0;
    // initialize the asci values for the word received
    while(nextChar != '\0' && nextChar != '~'){
        wordLen +=1;
        nextCharValue = (int) nextChar;
        if(nextCharValue > 32 && nextCharValue < 126){
            asciWordTable[nextCharValue-33] +=1;
        }
        nextChar = wordABC[nextIndex++];
    }
    
    char minSeq[wordLen];
    int minSeqIndex = 0, minSeqLength = 0, first =1;
    nextChar = text[0]; nextIndex = 1;
    
    for(int i=0; text[i] != '~'; i++){
        nextCharValue = (int) text[i];
        if(nextCharValue > 32)
        for(int j = i; text[j] != '~'; j++){
            nextCharValue = (int) text[j];
            minSeq[minSeqIndex] = '\0';
            if(minSeqLength == wordLen){
                //fprintf(outPointer,"%d\n", i);
                if(first == 1){
                    fprintf(outPointer,"%s", minSeq);first=0;
                }
                else{
                    fprintf(outPointer,"~%s",minSeq);
                }
                for(int k = 0; k < strlen(minSeq); k++){
                    if((int)minSeq[k] > 32){
                        asciSeqTable[(int)minSeq[k] - 33] = 0;
                    }
                }

                minSeqLength = 0;
                minSeqIndex = 0;
            }
            if(nextCharValue > 32){
            if(asciWordTable[nextCharValue-33] > asciSeqTable[nextCharValue-33]){
                asciSeqTable[nextCharValue-33]+=1;
                minSeq[minSeqIndex++] = text[j];
                minSeqLength+=1;
            }
            else{
                for(int k = 0; k < strlen(minSeq); k++){
                    if((int)minSeq[k] > 32){
                        asciSeqTable[(int)minSeq[k] - 33] = 0;
                    }
                }
                minSeqLength = 0;
                minSeqIndex = 0;
                break;
            }
            }
            else{
                minSeq[minSeqIndex++] = text[j];
            }
        }

    }

    // while(nextChar != '~'){
    //     nextCharValue = (int) nextChar;
    //     if(minSeqLength == wordLen){
    //         if(first == 1){
    //             fprintf(outPointer, "%s", minSeq);
    //             //fprintf(outPointer,"%c", nextChar);
    //             first =0;
    //         }
    //         else{
    //             fprintf(outPointer,"~%s", minSeq);
    //             //fprintf(outPointer,"%c", nextChar);
    //         }
    //         minSeq[minSeqIndex] = '\0';
    //         minSeqIndex = 0;
    //         int curCharVal;
    //         while(minSeq[minSeqIndex] != '\0'){
    //             curCharVal = (int)minSeq[minSeqIndex++];
    //             if(curCharVal > 32 && curCharVal < 126){
    //                 asciSeqTable[curCharVal - 33] = 0;
    //             }
    //         }
    //         minSeqIndex = 0;
    //         minSeqLength = 0;
    //     }
    //     if(nextCharValue >= 33){
    //     // append char to minSeq and update asci table bucket
    //     if(asciWordTable[nextCharValue-33] > asciSeqTable[nextCharValue-33]){
    //         minSeq[minSeqIndex++] = nextChar;
    //         asciSeqTable[nextCharValue-33]+=1;
    //         minSeqLength +=1;
    //     }
    //     // if the asci bucket is exceeding its word table asci then delete the current minSeq
    //     // and re initialize the asci min seq table
    //     else{
    //         minSeq[minSeqIndex] = '\0';
    //         //fprintf(outPointer,"%s\n", minSeq);
    //         minSeqIndex = 0;
    //         int curCharVal;
    //         while(minSeq[minSeqIndex] != '\0'){
    //             curCharVal = (int)minSeq[minSeqIndex++];
    //             if(curCharVal > 32 && curCharVal < 126){
    //                 asciSeqTable[curCharVal - 33]=0;
    //             }
    //         }
    //         minSeqIndex = 0;
    //         minSeqLength = 0;
    //         //nextIndex = (nextIndex - strlen(minSeq)) + 1;
    //     }
    //     }
    //     nextChar = text[nextIndex++];
    // }
    //fprintf(outPointer,"%d", minSeqLength);

    return 0;
}

int main(int argc, char* argv[]){
    // init word
    filePointer = stdin;
    outPointer = stdout;
    char word[(WORD * sizeof(char))];
    char nextChar = fgetc(filePointer);
    char text[TXT], text1[TXT], text2[TXT];
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
    index = 0;
    nextChar = fgetc(filePointer);
    while(nextChar != '~'){
        text[index++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    text[index] = '~';
    //printf(" The text received is : %s\n",text);
    strcpy(text1,text);
    strcpy(text2,text);
    int gimatryWord = 0;
    index = 0;
    int charVal;
    //printf("setting the word");
    do {
        charVal = (int) word[index++];
        if((charVal > 96 && charVal < 123)){
            // increment small letter
            gimatryWord += (charVal-96);
        }
        else if(charVal > 64 && charVal < 91){
            // increment big letter
            gimatryWord += (charVal - 64);
        }
    }while(word[index] != '\0');
    //printf("gimatry value of the word is : %d\n ", gimatryWord);
    //enter code here:
    //filePointer = fopen(argv[1],"r");
    fprintf(outPointer,"Gematria Sequences: ");
    minSeq(gimatryWord,text);
    //printf("%c",fgetc(filePointer));

    // reset to point to the first text char
    //filePointer = stdin;
    //while(fgetc(filePointer) != '\n'){};
    fprintf(outPointer,"\nAtbash Sequences: ");
    atBash(word,text1);

    //filePointer = stdin;
    //while(fgetc(filePointer) != '\n'){};
    fprintf(outPointer,"\nAnagram Sequences: ");
    minSeqWithEmpty(word,text2);

    fclose(filePointer);
    return 0;
}
