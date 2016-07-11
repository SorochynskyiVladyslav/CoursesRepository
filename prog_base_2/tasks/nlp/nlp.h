#ifndef NLP_H_INCLUDED
#define NLP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS_IN_SENTENCE 100
#define MAX_SENTENCES_IN_TEXT 1000

typedef struct word_s * word_t;
word_t word_new (char* buf);
void word_free (word_t self);

typedef struct sentence_s * sentence_t;
sentence_t sentence_new (char* buf);
void sentence_free (sentence_t self);
void sentence_toWords(sentence_t self);
int sentence_countLength (sentence_t self);

typedef struct text_s * text_t;
text_t text_new(char* buf);
void text_free (text_t self);
void text_toSentences (text_t self);

void text_swapSentences (text_t self, int index1, int index2);
void text_sortSentences (text_t self);
char* text_getSentenceWithCommas (text_t self, int index);
void text_writeToFile (text_t self, FILE* fw);









#endif // NLP_H_INCLUDED
