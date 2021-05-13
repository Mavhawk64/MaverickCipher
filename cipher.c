#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int range = '~' - ' ';
// int range = 'z' - 'a';
void encode();
void decode();
void output(char *);
char *getWords();
// int *fillRandoms(int,int);
int main(int argc, char *argv[]) {
  printf(
      "===============\n  Cipher Menu\n===============\n1. Encode\n2. "
      "Decode\n");
  short a = 0;
  scanf("%hi", &a);
  printf("Your response was interpreted as: %s.\n",
         a != 2 ? "Encode" : "Decode");
  if (a != 2) {
    encode();
  } else {
    decode();
  }
  return 0;
}

void encode() {
  printf(
      "===============\n Encoding Menu\n===============\nDo you have a seed? "
      "(y/n)\n");
  char b;
  scanf("\n%c", &b);
  unsigned long seed = 0;
  if (b == 'y' || b == 'Y') {
    printf("Enter seed: ");
    scanf("%lu", &seed);
  } else {
    time_t t;
    seed = (unsigned)time(&t);
  }
  printf("Your seed is: %lu.\n", seed);
  srand(seed);
  char *words = getWords();
  //  int *rands = fillRandoms(seed, strlen(words));
  //  int *indices;
  //  for(int i = 0; i < strlen(words); i++) {
  //      indices = (int) words[i];
  //      indices++;
  //  }
  //printf("%s\n", words);
  for (int j = 0; j < strlen(words); j++) {
    // Check if it is in bounds.
    if (words[j] <= '~' && words[j] >= ' ') {
      int ran = rand() % range;
      words[j] = (words[j] + ran - ' ') % range + ' ';
    }
  }
  output(words);
}

void decode() {
  printf("===============\n Decoding Menu\n===============\n");
  unsigned long seed = 0;
  printf("Enter seed: ");
  scanf("%lu", &seed);
  srand(seed);
  char *words = getWords();
  for (int j = 0; j < strlen(words); j++) {
    // Check if it is in bounds.
    if (words[j] <= '~' && words[j] >= ' ') {
      words[j] -= ' ';
      int ran = rand() % range;
      words[j] -= ran;
      while (words[j] < 0) {
        words[j] += range;
      }
      words[j] += ' ';
    }
  }
  output(words);
}

char *getWords() {
  printf(
      "===============\n  Input Menu\n===============\n1. File Input\n2. Text "
      "Input (Less than 256 characters.)\n");
  short i = 0;
  scanf("%hi", &i);
  char *input;
  if (i == 1) {
    input = (char *)malloc(sizeof(char));
    FILE *f;
    char name[20];
    printf("Name of file (With .txt Extension): ");
    scanf("%s", name);
    f = fopen(name, "r");
    if (f == NULL) {
      printf("File not opened correctly. Please try again.\n");
      return getWords();
    }
    int p = 0;
    while (1) {
      char temp = fgetc(f);
      if (temp < 0) {
        temp = 0;
      }
      input = (char *)realloc(input, (p + 1) * sizeof(char));
      input[p] = temp;
      p++;
      if (feof(f)) break;
    }
    // printf("Entered Data:\n%s\n", input);
    fclose(f);
  } else {
    printf("String Input: ");
    static char str[256];
    scanf("\n%[^\n]%*c", str);
    input = str;
  }
  return input;
}

void output(char *words) {
  printf("===============\n  Output Menu\n===============\n");
  printf(
      "How would you like your string to be printed?\n1. File\n2. On Screen\n");
  int d;
  scanf("\n%d", &d);
  if (d == 1) {
    FILE *f;
    char name[20];
    printf("Name of file (With .txt Extension): ");
    scanf("%s", name);
    f = fopen(name, "w");
    fputs(words, f);
    fclose(f);
    printf("Data saved to %s file.\n", name);
  } else {
    printf("Here is your returned text:\n%s\n", words);
  }
}