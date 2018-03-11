// Exercises in computer graphics in OpenGL using C. The fourth semester of study.
// Tomasz Wisniewski
// Exercises 1-10 / Part 1 of 1 set.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TABSIZE 20

// ---------------------------------------------------
// ZADANIE 1
// ---------------------------------------------------
void rng_t(int *tab, int size) {
    srand(time(NULL));

    for (int i = 0 ; i < size ; i++) {
        tab[i] = rand() % size;
    }
}

void inverse(int *tab , int size) {
    int tmp;
    for (int i = 0 ; i <= (size/2); i++) {

        tmp = tab[size - i - 1];
        tab[size - i - 1] = tab[i];
        tab[i] = tmp;
    }
}

void display_tab(int *tab, int size) {
    for (int i = 0 ; i < TABSIZE ; i++)
        printf("%3d ", tab[i]);
    printf("\n");
}

void zad1() {
    int tab[TABSIZE];
    rng_t(tab, TABSIZE);
    printf("zad 1:\n");
    display_tab(tab , TABSIZE);

    inverse(tab, TABSIZE);
    display_tab(tab , TABSIZE);
}
// ---------------------------------------------------
// ZADANIE 2
// ---------------------------------------------------

struct zesp {
    float a , b ;
};

struct zesp Dodaj(struct zesp z1 , struct zesp z2) {
    struct zesp z;
    z.a = z1.a + z2.a;
    z.b = z1.b + z2.b;

    return z;
}

void zad2() {

    struct zesp z1 , z2 , result;
    z1.a = 2;
    z1.b = 3;

    z2.a = 5;
    z2.b = 10;

    result = Dodaj(z1 , z2);

    printf("zad 2: z1 + z2  = %0.3f %0.3f\n", result.a , result.b);
}

// ---------------------------------------------------
// ZADANIE 3
// ---------------------------------------------------

long power(long a, long n) {

    long result = 1;
    for (int i = 0 ; i < n ; i++) {
        result = result * a;
    }

    return result;
}

void zad3() {
    printf("zad 3: power %ld\n" , power(2 , 5));
}

// ---------------------------------------------------
// ZADANIE 4
// ---------------------------------------------------

struct maxmin {
    int max , min; 
};

struct maxmin szukaj(int *tab, int n) {

    struct maxmin result;

    int lMin , lMax;
    int first = 0 ;

    if (!first) {
        lMin = lMax = tab[0];
        first = 1;
    }

    for (int i = 0 ; i < n ; i++) {
        if (tab[i] < lMin) lMin = tab[i];
        if (tab[i] > lMax) lMax = tab[i];
    }

    // sanity check
    printf("zad 4: min : %d\t max: %d\n", lMin, lMax);

    result.min = lMin;
    result.max = lMax;

    return result;
}


void zad4() {
    int tab[TABSIZE];
    rng_t(tab, TABSIZE);
    display_tab(tab, TABSIZE);

    struct maxmin stru;
    stru = szukaj(tab , TABSIZE);
}

// ---------------------------------------------------
// ZADANIE 5
// ---------------------------------------------------
int parzysta(int a) {
    if (a % 2 == 0)
        return 1;
    else return 0;
}

void zad5(){
    srand(time(NULL));
    int input = rand() % 127 + 33; 

    printf("zad 5: podana liczba --->  %d\t" , input);
    printf("funk parzysta --->  %d\n" , parzysta(input));

};
// ---------------------------------------------------
// ZADANIE 6
// ---------------------------------------------------
int sprawdz(int *tab, int n, int a) {
    for (int i = 0 ; i < n ; i++) {
        if (tab[i] == a)
            return i;
    }

    return -1;
}

void zad6() {
    int tab[TABSIZE];
    int rng = rand() % TABSIZE; // automat do testu

    rng_t(tab, TABSIZE);
    printf("\nzad 6: a = %d  , jest w tab %d \n" , rng , sprawdz(tab, TABSIZE, rng));
    display_tab(tab , TABSIZE);

};
// ---------------------------------------------------
// ZADANIE 7
// ---------------------------------------------------
int przepisz(int *tab, int *tab2 , int n) {

    for (int i = 0; i < n ; i++) {
        if (tab[i] > 0)
            tab2[i] = tab[i];
        else tab2[i] = 0;
    }

    return n;
}

void zad7() {

    int tab[TABSIZE];
    int tab2[TABSIZE];
    rng_t(tab, TABSIZE);

    printf("\nzad 7: %d \n", przepisz(tab, tab2 , TABSIZE));
}

// ---------------------------------------------------
// ZADANIE 8
// ---------------------------------------------------

double srednia(int *tab, int n){
    double result;
    double sum = 0;
    long count;

    for (int i = 0 ; i < n ; i++, count++)
        sum = sum + tab[i];
    
    result = sum / count;
    return result;
}

void zad8() {

    int tab[TABSIZE];
    rng_t(tab, TABSIZE);

    printf("zad 8: %f \n" , srednia(tab , TABSIZE));

}
// ---------------------------------------------------
// ZADANIE 9
// ---------------------------------------------------
int palindrom (char *tab, int n) {

    for (int i = 0 ; i <= (n/2) ; i++){
        if (tab[i] == tab[n - i - 1])
            printf("%c = %c , " , tab[i] , tab[n - i - 1]);
        else {
            printf("%c != %c , " , tab[i] , tab[n - i - 1]);
            printf("\n");
            return -1;
        }
    }

    printf("\n");
    return 0;
}

void zad9() {
    char *word = "kajak";
    int len = strlen(word);

    char *word2 = "kajAk";
    int len2 = strlen(word2);

    printf("zad 9:\n");
    printf("%d \n" , palindrom(word , len));
    printf("%d \n" , palindrom(word2 , len2));
}
// ---------------------------------------------------
// ZADANIE 10
// ---------------------------------------------------
char max_znak(FILE *f, int *n) {

    int chars[256] = {0};
    char byte;

    fseek(f, 0L, SEEK_END); 
    long fend = ftell(f);
    fseek(f, 0L , SEEK_SET);

    for (long position = 0 ; position < fend; position++) {
        fseek(f, position , SEEK_SET);
        byte = getc(f);
        chars[byte] = chars[byte] + 1;
    }

    fclose(f);

    int max = 0;
    char result = 0;
    for (int i = 0 ; i < 256 ; i++) {
        if (max < chars[i]) {
            max = chars[i];
            result = i ;
        }
    }

    *n = max;
    return result;
}

void zad10() {
    char *fname = "data.txt";
    FILE *fout = fopen(fname, "w+");

    char *line1= "When the code is executed, it creates a new file data.txt in current directory and writes two lines.";
    char *line2= "\nHere is the second line.";

    fputs(line1, fout);
    fputs(line2, fout);
    fclose(fout);

    int frequency = 0;
    char freq_c;
    freq_c = max_znak(fopen(fname, "rb"), &frequency);

    printf("zad 10: ASCII: %c %d  freq:  %d  \n", freq_c, freq_c, frequency);

}

// ---------------------------------------------------
// MAIN
// ---------------------------------------------------

int main() {
  zad1(); 
  zad2();
  zad3();
  zad4();
  zad5(); 
  zad6();
  zad7();
  zad8();
  zad9();
  zad10();

}
