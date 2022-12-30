#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
//mycode
typedef struct document document;
typedef struct sentence sentence;
typedef struct paragraph paragraph;
typedef struct word word;
char* line(int* p,char* text){
    char* n=(char*)malloc(sizeof(char));
    int j=0;
    for(int i=*p;text[i]!='\0';i++){
        if(text[i]=='\n'||text[i]==' '||text[i]=='.'){
            *p=i;
            return n;
        }
        else{
        n[j]=text[i];
        j++;
        n=(char*)realloc(n,(j+1)*sizeof(char));
        if(text[i+1]==' '||text[i+1]=='\n'||text[i+1]=='.'){
            n[j]='\0';
        }
        }
    }
    return n;
}
word* w(int* p,char* text,int* size){
    word* n=(word*)malloc(sizeof(word));
    int j=0;
    for(int i=*p;text[i]!='\0';i++){
            n[j].data=line(&i,text);
            j++;
            if(text[i]=='\n'||text[i]=='.'){
                *size=j;
                *p=i;
            return n;
            }
            if(!(text[i+1]=='\n'||text[i+1]==' '||text[i+1]=='.'))
            n=(word*)realloc(n,(j+1)*sizeof(word));
        }
    
    return n;
}
sentence* se(int* p,char* text,int* size){
    sentence* n=(sentence*)malloc(sizeof(sentence));
    int j=0;
    for(int i=*p;text[i]!='\0';i++){
            int s=0;
            n[j].data=w(&i,text,&s);
            n[j].word_count=s;
            j++;
            if(text[i]=='\n'){
                *p=i;
                *size=j;
            return n;
            }
            if(!(text[i+1]=='\n'))
            n=(sentence*)realloc(n,(j+1)*sizeof(sentence));
        
    }
    return n;
}
paragraph* par(int* p,char* text,int* size){
    paragraph* n=(paragraph*)malloc(sizeof(paragraph));
    int j=0;
    for(int i=*p;text[i]!='\0';i++){
            int s=0;
            n[j].data=se(&i,text,&s);
            n[j].sentence_count=s;
            j++;
            if(!(text[i+1]=='\0'))
            n=(paragraph*)realloc(n,(j+1)*sizeof(paragraph));
    }
    *size=j;
    return n;
}
struct document get_document(char* text) {
    document c;
    int size=0;
    int i=0;
    c.data=par(&i,text, &size);
    c.paragraph_count=size;
    return c;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
   return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[k-1].data[m-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
