#include <stdio.h>
#include <stdlib.h>


int M[10],N[10],topm = -1,topn = -1;
char a[10];

// Function pointer
typedef void (*Func)(int);
Func victory;


void display(char b[]){
  printf(" %c | %c | %c \n",b[0],b[1],b[2]);
  printf("---|---|---\n");
  printf(" %c | %c | %c \n",b[3],b[4],b[5]);
  printf("---|---|---\n");
  printf(" %c | %c | %c \n",b[6],b[7],b[8]);
}
void victoryX(int a){
  if(a==3){
    printf("X IS THE WINNER!!!");
    exit(0);
  }
}
void victoryY(int a){
  if(a==3){
    printf("O IS THE WINNER!!!");
    exit(0);
  }
}

//single Function to check for X and Y by passing parameters 
void check(int k[10], int XorY) {
    int i,counth1=0,counth2=0,counth3=0,countv1=0,countv2=0,countv3=0,countlc=0,countrc=0;
    
    // to determine whether victoryX or victoryY
    if (XorY == 1)  victory = victoryX;
    else  victory = victoryY;
    
    if (topm >= 2) {
    for(i = 0 ;i < topm + 1; i++) {
      if (k[i] == 1 || k[i] == 2 || k[i] == 3 ) {
          counth1++;
          victory(counth1);
      }
      if (k[i] == 4 || k[i] == 5 || k[i] == 6 ) {
          counth2++;
          victory(counth2);
      }
      if (k[i] == 7 || k[i] == 8 || k[i] == 9 ) {
          counth3++;
          victory(counth3);
      }
      if (k[i] == 1 || k[i] == 4 || k[i] == 7 ) {
          countv1++;
          victory(countv1);
      }
      if (k[i] == 2 || k[i] == 5 || k[i] == 8 ) {
          countv2++;
          victory(countv2);
      }
      if (k[i] == 3 || k[i] == 6 || k[i] == 9 ) {
          countv3++;
          victory(countv3);
      }
      if (k[i] == 1 || k[i] == 5 || k[i] == 9 ) {
          countlc++;
          victory(countlc);
      }
      if (k[i] == 3 || k[i] == 5 || k[i] == 7 ) {
          countrc++;
          victory(countrc);
      }
    }
  }
    
}


void console() {
    int i,chance = 0,place_value;
    for(i=0;i<9;i++)
        a[i]=' ';
    i=0;
    while (i<5){
        if (chance==0){
            g_print("X's turn enter the place no[1-9]\n");
            //scanf("%d",&place_value);
            M[++topm] = place_value;
            a[place_value-1] = 'X';
            display(a);
            check(M, 1); //passing M -> k and 1 -> XorY to "check" Function
            chance = 1;
        }
        if (i==4) break;
        if (chance==1){
            g_print("O's turn enter the place no[1-9]");
            //scanf("%d",&place_value);
            N[++topn] = buttonText();
            a[place_value-1] = 'O';
            display(a);
            check(N, 0); //passing N -> K and 0 -> XorY to "check" Function
            chance = 0;
        }
        i++;
    }
    g_print("MATCH DRAW!!!");
}

int main() {
    console();
}
