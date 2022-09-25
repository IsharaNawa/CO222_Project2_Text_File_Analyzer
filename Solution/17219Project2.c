/*
***********************************************************************************************

                        CO222-Programming Methodology-Project2
                Word and Character Frequency Finder Program Using C Programming Language


Author:Ishara Nawarathna(K.G.I.S. Nawarathna)
E-Number:E/17/219

***********************************************************************************************
*/

//Importing standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Two linked lists are used here in this program.Depending on the command line argument intended linked list is created

//Creating  and typedeffing the structure for the word linked list
typedef struct word_t{

    char word[104];
    int counter;
    float precentage;
    struct word_t * next;

}wordNode;

//Creating and typedeffing the structure for the char linked list
typedef struct charac_t{

    char character;
    int counter;
    float precentage;
    struct charac_t * next;

}charNode;

//Declaring the head nodes
wordNode * headWord=NULL;
charNode * headChar=NULL;

//Prototyping the functions

//Creating the word linked list for a particular file
void wordList(char filename[]);

//Creating the char linked list for a particular file
void charList(char filename[]);

//Counting total words(or chars)
int totalWords(char c);

//Calculating percentages of each node and assigning them to the linked list
void assignPrecent(char c);

//Make the word alphanumeric
void alphanumeric(char *word);

//Bubblesorting the linked list
void BubblesortList(char c);

//Printing a single char on the graph
void printSingleChar(char charac,float precent,int scaled);

//Printing a single word on the graph
void printSingleWord(char word[],float precent,int maxLength,int maxPrecentLength,int scaled);

//Calculating the number of nodes in the linked list
int TotalNodes(char c);

//Calculating the maximum length of the words in the sorted word linked list
int maxLen(int Noelements);

//Printing the graph for the word linked list
void printWordList(int number,int scaled);

//Printing the graph for the char linked list
void printCharList(int number,int scaled);

//Calculating the number of chars in the linked list for the maximum percentage
int maxPrecentageLength();

//-l Error printing functions
void printLengthError(char progname[]);
void printLenNegative(char proname[]);
void printLenLast(char progname[]);

//Toggle Error Functions
void toggleError(char progname[]);

//No input files error
void noInputFilesError(char progname[]);

//Invalid Options
void invalidOption(char str[],char progname[]);

//Empty file Error Functions
int checkForEmptyNess(char filename[]);
int checkForEmptyNessC(char filename[]);

//Memory Freeing Functions
void freeFunctW();
void freeFunctC();

int main(int argc,char * argv[])
{   //handling arguments
    if(argc==1){
        noInputFilesError(argv[0]);
    }

    int toggleCIndicator=0;
    int toggleWIndicator=0;
    int listIndex=0;
    int scaledIndicator=0;
    int listIndicator=0;

    int counter;

    for(counter=1;counter<argc;counter++){
        if(strcmp(argv[counter],"-c")==0){
            toggleCIndicator = 1 ;
        }else if(strcmp(argv[counter],"-w")==0){
            toggleWIndicator = 1 ;
        }else if(strcmp(argv[counter],"-l")==0){
            listIndex = counter + 1;
            if(listIndex==argc){
                printLenLast(argv[0]);
            }

            listIndicator = atoi(argv[listIndex]);

            if(listIndicator==0 && strcmp("0",argv[listIndex])!=0){
                printLengthError(argv[0]);

            }

            if(strcmp("0",argv[listIndex])==0){
                exit(0);
            }

            if(listIndicator<0){
                printLenNegative(argv[0]);
            }
            int i;
            if(listIndicator!=0){
                for(i=0;argv[listIndex][i]!='\0';i++){
                    if(argv[listIndex][i]=='.'){
                        printLengthError(argv[0]);
                    }
                }
            }

        }else if(strcmp(argv[counter],"--scaled")==0){
            scaledIndicator = 1;
        }else{
            if(argv[counter][0]=='-'){
                invalidOption(argv[counter],argv[0]);
            }
        }
    }

    //Handling the toggle(-w and -c)

    if(toggleCIndicator==1 && toggleWIndicator==1){
        toggleError(argv[0]);
    }

    if(toggleCIndicator==0 && toggleWIndicator==0){

        int empty=0;
        int noinput=0;
        int added=0;
        for(counter=1;counter<argc;counter++){

            if(argv[counter][0]=='-' || listIndex==counter || atoi(argv[counter])!=0){
                continue;
            }else{
                noinput=1;

                if(checkForEmptyNess(argv[counter])==0){
                    empty=1;


                }else{
                    wordList(argv[counter]);
                    added=1;
                }
            }
        }
        if(headWord!=NULL){
            assignPrecent('w');
            BubblesortList('w');
            if(listIndex ==0){printWordList(10,scaledIndicator);}
            else{printWordList(listIndicator,scaledIndicator);}


        }else{
            if(empty==0 && noinput==0 && added==0){noInputFilesError(argv[0]);}
            if(empty==1 && noinput==1 && added==0){printf("No data to process\n");}
        }

    }

    if(toggleCIndicator==1 && toggleWIndicator==0){
        int empty=0;
        int noinput=0;
        int added=0;
        for(counter=1;counter<argc;counter++){

            if(argv[counter][0]=='-' || listIndex==counter || atoi(argv[counter])!=0){
                continue;
            }else{
                noinput=1;
                if(checkForEmptyNess(argv[counter])==0){
                    empty=1;


                }else{
                    charList(argv[counter]);
                    added=1;
                }
            }
            }

        if(headChar!=NULL){
            assignPrecent('c');
            BubblesortList('c');
            if(listIndex ==0){printCharList(10,scaledIndicator);}
            else{printCharList(listIndicator,scaledIndicator);}
        }else{
            if(empty==0 && noinput==0 && added==0){noInputFilesError(argv[0]);}
            if(empty==1 && noinput==1 && added==0){printf("No data to process\n");}

        }

    }

    if(toggleCIndicator==0 && toggleWIndicator==1){
        int empty=0;
        int noinput=0;
        int added=0;
        for(counter=1;counter<argc;counter++){

            if(argv[counter][0]=='-' || listIndex==counter || atoi(argv[counter])!=0){
                continue;
            }else{
                noinput=1;
                if(checkForEmptyNess(argv[counter])==0){
                    empty=1;


                }else{
                    wordList(argv[counter]);
                    added=1;
                }

            }
        }

        if(headWord!=NULL){
            assignPrecent('w');
            BubblesortList('w');
            if(listIndex ==0){printWordList(10,scaledIndicator);}
            else{printWordList(listIndicator,scaledIndicator);}


        }else{
            if(empty==0 && noinput==0 && added==0){noInputFilesError(argv[0]);}
            if(empty==1 && noinput==1 && added==0){printf("No data to process\n");}
        }

    }

    if(headWord!=NULL){freeFunctW();}

    if(headChar!=NULL){freeFunctC();}

    return 0;
}

//This function takes a single file and converts it to a word linked list
void wordList(char filename[]){

    FILE * fpointer=fopen(filename,"r");

    char add[104];

    while(fscanf(fpointer, "%s", add) != EOF ){

        alphanumeric(add);

        if(strcmp(add,"")==0){
            continue;
        }

        if(headWord==NULL){
            wordNode * temp = (wordNode*)malloc(sizeof(wordNode));
            temp->counter=0;
            strcpy(temp->word,add);
            temp->counter += 1;
            temp->next=headWord;
            headWord=temp;
        }

        else{

            wordNode * counter;

            int indicator=0;

            for(counter=headWord;counter!=NULL;counter=counter->next){
                if(strcmp(add,counter->word)==0){
                    counter->counter += 1;
                    indicator = 10;
                    break;
                }
            }


            if(indicator==0){
                wordNode * temp = (wordNode*)malloc(sizeof(wordNode));
                temp->counter=0;
                strcpy(temp->word,add);
                temp->counter+=1;
                temp->next=headWord;
                headWord=temp;
            }
        }
    }
    fclose(fpointer);
}

//This function takes a single file and converts it to a character linked list
void charList(char filename[]){

    FILE * fpointer=fopen(filename,"r");

    char c;

    while(1){

        c = fgetc(fpointer);

        if(c==EOF){
            break;
        }

        if(isalnum(c)!=0){
            c=tolower(c);

            if(headChar==NULL){
                charNode * temp = (charNode*)malloc(sizeof(charNode));
                temp->counter=0;
                temp->character=c;
                temp->counter += 1;
                temp->next=headChar;
                headChar=temp;
            }


            else{

                charNode * counter;

                int indicator=0;

                for(counter=headChar;counter!=NULL;counter=counter->next){
                    if(c==counter->character){
                        counter->counter += 1;
                        indicator = 10;
                        break;
                    }
                }


                if(indicator==0){
                    charNode * temp = (charNode*)malloc(sizeof(charNode));
                    temp->counter=0;
                    temp->character=c;
                    temp->counter+=1;
                    temp->next=headChar;
                    headChar=temp;
                }
            }
        }
    }
    fclose(fpointer);
}

//This function counts the total number of words/chars in a linked list
int totalWords(char c){
    int total=0;
    if(c=='w'){



        wordNode * counter;

        for(counter=headWord;counter!=NULL;counter=counter->next){

            total += counter->counter;

        }



        }
    else if(c=='c'){



        charNode * counter;

        for(counter=headChar;counter!=NULL;counter=counter->next){

            total += counter->counter;

        }


    }

        return total;

}

//This function assigns percentages to a linked list
void assignPrecent(char c){

    if(c=='w'){
        wordNode * counter;
        float precent=0.00;
        int total = totalWords(c);

        for(counter=headWord;counter!=NULL;counter=counter->next){
            precent = (float)counter->counter/(float)total*100.00;
            counter->precentage=precent;

        }
    }

    else if(c=='c'){
        charNode * counter;
        float precent=0.00;
        int total = totalWords(c);

        for(counter=headChar;counter!=NULL;counter=counter->next){
            precent = (float)counter->counter/(float)total*100.00;
            counter->precentage=precent;

        }
    }

}

//This function does the preprocessing
void alphanumeric(char * word){

    char newArray[104];
    int counter;
    int essCount=0;

    for(counter=0;word[counter]!='\0';counter++){

        if(isalnum(word[counter])!=0){
            newArray[essCount]=tolower(word[counter]);
            essCount++;
        }
    }

    strcpy(word,newArray);

    word[essCount]='\0';

}

//This function sorts a linked list in bubble sort algorithm
void BubblesortList(char c){

    if(c=='w'){

        wordNode * i, *j;

        for(i=headWord;i->next!=NULL;i=i->next){

            for(j=i->next;j!=NULL;j=j->next){

                if(i->counter<=j->counter){

                    int temp_count = i->counter;
                    float temp_precent = i->precentage;
                    char temp_word[104];
                    strcpy(temp_word,i->word);

                    i->counter=j->counter;
                    i->precentage=j->precentage;
                    strcpy(i->word,j->word);

                    j->counter=temp_count;
                    j->precentage=temp_precent;
                    strcpy(j->word,temp_word);

                    }
            }

        }

    }else if(c=='c'){

        charNode * i, *j;

        for(i=headChar;i->next!=NULL;i=i->next){

            for(j=i->next;j!=NULL;j=j->next){

                if(i->counter<=j->counter){

                    int temp_count = i->counter;
                    float temp_precent = i->precentage;
                    char temp_char = i->character;

                    i->counter=j->counter;
                    i->precentage=j->precentage;
                    i->character=j->character;

                    j->counter=temp_count;
                    j->precentage=temp_precent;
                    j->character=temp_char;

                    }
            }

        }

    }

}

//This function check whether if the file is empty or not
int checkForEmptyNess(char filename[]){

    FILE * fpointer =fopen(filename,"r");

    if(fpointer==NULL){
        printf("Cannot open one or more given files\n");
        exit(0);
    }

    char word[104];

    int counter=0;

    while(fscanf(fpointer,"%s",word)!=EOF){

        alphanumeric(word);

        for(counter=0;word[counter]!='\0';counter++){}
        break;

    }

    return counter;

}

int checkForEmptyNessC(char filename[]){

    FILE * fpointer =fopen(filename,"r");

    if(fpointer==NULL){
        printf("Cannot open one or more given files\n");
        exit(0);
    }

    int counter=0;

    while(1){
        char c = fgetc(fpointer);

        if(c==EOF){
            break;
        }

        if(isalnum(c)!=0){
            counter=tolower(c);
        break;

        }
    }

    return counter;
}

//This function gets a file and makes a LL and returns Total number of nodes in it
int TotalNodes(char c){
    int nodeCounter=0;
    if(c=='w'){

    wordNode * counter;



    for(counter=headWord;counter!=NULL;counter=counter->next){

        nodeCounter++;

    }



    }
    else if(c=='c'){

    charNode * counter;



    for(counter=headChar;counter!=NULL;counter=counter->next){

        nodeCounter++;

    }



    }
    return nodeCounter;
}

//Returns the maximum number of chars for the maximum percentage
int maxPrecentageLength(){

    //After bubblesorting

    float maxPrecent = headWord->precentage;

    if(maxPrecent==100.00){
        return 7;
    }
    if(maxPrecent>=10.00){
        return 6;
    }
    else{
        return 5;
    }
}

//This function returns a max Length of a already word in already created LL
int maxLen(int Noelements){

    wordNode*counter;

    int maxlen=0;

    int elecounter=0;

    if(Noelements>=TotalNodes('w')){

        for(counter=headWord;counter!=NULL;counter=counter->next){

            if(strlen(counter->word)>=maxlen){
                maxlen=strlen(counter->word);
            }
        }
    }
    else{

        wordNode * end;

        for(counter=headWord;counter!=NULL;counter=counter->next){
            if(elecounter==Noelements){
                end = counter;
                break;
            }
            elecounter++;
        }

         for(counter=headWord;counter!=end;counter=counter->next){

            if(strlen(counter->word)>=maxlen){
                maxlen=strlen(counter->word);
            }

        }

    }

    return maxlen;

}

//This function gets a char,float and scaled option and then print the corresponding graph for a single char
void printSingleChar(char charac,float precent,int scaled){

    int counter1;
    float counter2;
    int preLength;

    float maxPrecent = headChar->precentage;
    if(maxPrecent==100.00){preLength=7;}
    else if(maxPrecent>=10.00){preLength=6;}
    else{preLength=5;}

    int len=80-4-preLength;

    float cofac = len/maxPrecent;

    for(counter1=0;counter1<3;counter1++){
        if(counter1==1){
            printf(" %c \u2502",charac);
        }
        else{
            printf("   \u2502");
        }

        if(scaled==0){
            counter2=0;
            while(counter2<precent*0.70-1){
                printf("\u2591");
                counter2++;
            }
        }else if(scaled==1){
            counter2=0;
            int a;
            if(precent==maxPrecent){a=0;}else{a=1;}
            while(counter2<precent*cofac-a){
                printf("\u2591");
                counter2++;
            }
        }

    if(counter1==1){
        printf("%.2f%%",precent);
        }

    printf("\n");
    }

    printf("   \u2502\n");

}

//This function gets a char,float and scaled option and then print the corresponding graph for a single word
void printSingleWord(char word[],float precent,int maxLength,int maxPrecentLength,int scaled){

    int counter1;
    float counter2;
    int printableWidth=77-maxLength-maxPrecentLength;
    int sec1 = 2+maxLength;
    int i;

    float maxPer=headWord->precentage;
    //int preLength=maxPrecentageLength();

    float cofac = printableWidth/maxPer;

    for(counter1=0;counter1<3;counter1++){
        if(counter1==1){

            printf(" %s",word);
            int a=1+strlen(word);
            int looplen=sec1-a;
            for(i=0;i<looplen;i++){
                printf(" ");
            }

            printf("\u2502");


        }else{
            for(i=0;i<sec1;i++){printf(" ");}
            printf("\u2502");

        }

        if(scaled==0){
        counter2=0;
        while(counter2<precent*printableWidth/100-1){
                printf("\u2591");
                counter2++;
        }

        }else if(scaled==1){
        counter2=0;
        int a;
        if(precent==maxPer){a=0;}
        else{a=1;}
        while(counter2<precent*cofac-a){
                printf("\u2591");
                counter2++;
        }


        }

        if(counter1==1){
                printf("%.2f%%",precent);
            }

            printf("\n");


    }

    for(i=0;i<sec1;i++){printf(" ");}
    printf("\u2502\n");

}

//This function prints a graph for word list
void printWordList(int number,int scaled){

    wordNode * counter;
    int i;

    if(number==0){exit(0);}

    int totalN =TotalNodes('w');

    int sec= 2+maxLen(number);

    int sec2 =80-sec-1;

    if(number>=totalN){
        printf("\n");
        for(counter=headWord;counter!=NULL;counter=counter->next){
            printSingleWord(counter->word,counter->precentage,maxLen(number),maxPrecentageLength(),scaled);

        }

    for(i=0;i<sec;i++){printf(" ");}
     printf("\u2514");

    for(i=0;i<sec2;i++){printf("\u2500");}

    printf("\n");


    }else{

        int count=0;

        wordNode * end;

        for(counter=headWord;counter!=NULL;counter=counter->next){
            if(count==number){
                end = counter;
                break;
            }
            count++;
        }

        printf("\n");

        for(counter=headWord;counter!=end;counter=counter->next){
            printSingleWord(counter->word,counter->precentage,maxLen(number),maxPrecentageLength(),scaled);

        }
        for(i=0;i<sec;i++){printf(" ");}
        printf("\u2514");

        for(i=0;i<sec2;i++){printf("\u2500");}

        printf("\n");

    }

}

//This function prints a graph for char list
void printCharList(int number,int scaled){

    charNode * counter;

    if(number==0){exit(0);}

    int totalN=TotalNodes('c');

    if(number>=totalN){

        printf("\n");

    for(counter=headChar;counter!=NULL;counter=counter->next){
        printSingleChar(counter->character,counter->precentage,scaled);
    }

    printf("   \u2514");

    for(int i=0;i<76;i++){
        printf("\u2500");
    }

    printf("\n");

    }

    else{

    int count=0;

    charNode * end;

    for(counter=headChar;counter!=NULL;counter=counter->next){
        if(count==number){
            end = counter;
            break;
        }
        count++;
    }

    printf("\n");

    for(counter=headChar;counter!=end;counter=counter->next){
        printSingleChar(counter->character,counter->precentage,scaled);
    }

    printf("   \u2514");

    for(int i=0;i<76;i++){
        printf("\u2500");
    }

    printf("\n");

    }
}

//Error printing functions

//When the next value of l is not an integer
void printLengthError(char progname[]){

    printf("Invalid options for [-l]\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",progname);
    exit(0);

}

//When the next value of l is not a positive integer
void printLenNegative(char progname[]){

    printf("Invalid option(negative) for [-l]\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",progname);
    exit(0);
}

//When the integer is not given for l
void printLenLast(char progname[]){

    printf("Not enough options for [-l]\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",progname);
    exit(0);

}

//when -c and -w both entered
void toggleError(char progname[]){

    printf("[-c] and [-w] cannot use together\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",progname);
    exit(0);
}

//When input files are not given
void noInputFilesError(char progname[]){

    printf("No input files were given\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",progname);
    exit(0);

}

//When wrong option is entered
void invalidOption(char str[],char progname[]){

    printf("Invalid option [%s]\n",str);
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",progname);
    exit(0);

}

//Freeing the Word linked list
void freeFunctW(){

    wordNode * counter;

    for(counter=headWord;counter!=NULL;counter=counter->next){
        wordNode * temp = headWord;
        headWord = headWord->next;
        free(temp);


    }

}

//Freeing the Char linked list
void freeFunctC(){

    charNode * counter;

    for(counter=headChar;counter!=NULL;counter=counter->next){
        charNode * temp = headChar;
        headChar = headChar->next;
        free(temp);


    }

}



//The End of the source code
