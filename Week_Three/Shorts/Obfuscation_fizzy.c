#include <stdio.h>
int main(void){int max = 100;for(int i = 0; i < max; i++){if(i % 3 == 0 && i % 5 == 0){printf("FIZZBUZZ!!!\n");continue;}else if (i % 3 == 0){printf("Fizz!\n");continue;}else if (i % 5 == 0){printf("Buzz!\n");continue;}else{printf("%i\n", i);}}}