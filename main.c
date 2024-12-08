#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

typedef GtkWidget * layout;

//global declarations
//front-end
layout button[9];
layout Turn;
layout mainDisplay();
layout aWindow; //after Window
layout bWindow; //before Window;
layout resetButton;
int computer_move(int k[9]) ;

int Count = 0;
int *count = &Count;
int robot = 0;
int *Robot = &robot;
int alive = 1; //for quitting after winning
int *Alive = &alive;

//back-end
int M[9],N[9],topm = -1,topn = -1;
int i,chance = 0,place_value,mode;
// Function pointer
typedef void (*Func)(int);
Func victory;
int check(int k[9], int XorY, int mode);

//Functions to shorten code
int freeWill(int condition, char array[], int index1, int index2, int index3) {
    if (condition == 2) {
        if (array[index1] == ' ') return index1 + 1 ;
        if (array[index2] == ' ') return index2 + 1 ;
        if (array[index3] == ' ') return index3 + 1 ;
    }
    return -1;
}
char b[9]; // = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int buttonPressed[9];

// START 
void buttonText(layout widget, int data) {
    int move = 0; 
    //button clicking only once 
    if (buttonPressed[data] == 0 && alive == 1)  {
        buttonPressed[data] = 1;
        (*count)++; 
        if (Count <= 9) {
            char* Text = (Count % 2 == 0 && robot == 0) ? "O" : "X" ;
            char* player = (Count % 2 == 0 || robot == 1) ? "Player X" : "Player O" ;
            //g_print("count = %d, buttonNumber = %d\n",Count, data);
            gtk_button_set_label(widget, Text);
            gtk_label_set_text(Turn, player);

            b[data] = (Text == "O" && robot == 0) ? 'O' : 'X';
            // display func from BACKEND
            g_print("\t %c | %c | %c \n",b[0],b[1],b[2]);
            g_print("\t---|---|---\n");
            g_print("\t %c | %c | %c \n",b[3],b[4],b[5]);
            g_print("\t---|---|---\n");
            g_print("\t %c | %c | %c \n",b[6],b[7],b[8]);

            //win condition check
            if (robot == 0) {
                if (Count % 2 == 0) {
                    N[++topn] = data + 1;
                    check(N, 0, 0);
                } else {
                    M[++topm] = data + 1;
                    check(M, 1, 0);
                }
                if (Count < 9 && alive == 1) g_print("\n%s\'s turn, enter the place no[1-9]\n", player);
                //(backend) 
            } 
            else { //robot == 1
                M[++topm] = data + 1;
                check(M, 1, 0);

                //for 'O'
                if (Count <= 9 && alive == 1) {
                    if (M[topm] == 9 &&  M[topm - 1] == 2 && Count == 3) move = 6;
                    else if (M[topm] == 3 &&  M[topm - 1] == 8 && Count == 3) move = 6;
                    else if (M[topm] == 1 &&  M[topm - 1] == 8 && Count == 3) move = 4;
                    else {
                        move = check(N, 0, 1);
                        if (move == 25) move = check(M, 1, 1);
                        if (move == 25) {
                            if (M[0] == 5) {
                                if (b[(M[topm]- 6)- 1] == ' ') move = M[topm] - 6;
                                else move = computer_move(M);
                            } 
                            else move = computer_move(M);
                        }
                    }
                    N[++topn] = move;
                    b[move - 1] = 'O';
                    buttonPressed[move - 1] = 1;
                    gtk_button_set_label(button[move - 1], "O");
                
                    g_print("\nBot played at no- %d\n",move);
                    g_print("\t %c | %c | %c \n",b[0],b[1],b[2]);
                    g_print("\t---|---|---\n");
                    g_print("\t %c | %c | %c \n",b[3],b[4],b[5]);
                    g_print("\t---|---|---\n");
                    g_print("\t %c | %c | %c \n",b[6],b[7],b[8]);
                
                    //g_print("count = %d, buttonNumber = %d, move = %d\n",Count, data, move);
                    check(N, 0, 0);
                }
                //for O
                (*count)++;
                if (Count < 9 && alive == 1) g_print("\nX\'s turn, enter the place no[1-9]\n");
                //(backend) 
            }
        } 
        if (Count >= 9 && alive == 1) {
            gtk_label_set_text(Turn, "MATCH DRAW!!!"); 
            gtk_button_set_label(resetButton, "Play Again");
            g_print("\nMATCH DRAW!!!\n");
        } else {
            return;
        }
    }
}

void resetValues() {
    int i;
    for (i = 0; i < 9; i++) {
        b[i] = ' '; 
        buttonPressed[i] = 0;
        M[i] = 0;
        N[i] = 0;
    }
    *count = 0;
    *Alive = 1;
    *Robot = 0;
    topm = topn = -1;
}

// NO CHANGE
void play1v1_bot(layout widget, int data) {
    resetValues();
    *Robot = data;
    //local declarations
    layout hbox[3];
    layout window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(window, 200);  //gtk_widget_set_size_request(window, 600, 600);

    //main box
    layout vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    layout backMain = gtk_button_new_with_label("Home");
    g_signal_connect(backMain, "clicked", G_CALLBACK(mainDisplay), NULL);
    layout alignHome = gtk_alignment_new(1, 0, 0, 0);
    gtk_container_add(alignHome, backMain);
    gtk_container_add(vbox, alignHome);

    Turn = gtk_label_new("Player X");
    gtk_container_add(vbox, Turn);
    
    int i, j;
    for(i = 0; i < 9; i++) {
        button[i] = gtk_button_new_with_label(" ");
        g_signal_connect(button[i], "clicked", G_CALLBACK(buttonText), i);
        gtk_widget_set_size_request(button[i], 75, 75);
    }
    i = 0;
    for (j = 0; j < 3; j++) {
        //adding boxes(containing 3 buttons each) to main box and window
        hbox[j] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_container_add(hbox[j], button[i]);
        gtk_container_add(hbox[j], button[++i]);
        gtk_container_add(hbox[j], button[++i]);
        gtk_container_add(vbox, hbox[j]);
        i++;
    }

    resetButton = gtk_button_new_with_label("Reset");
    g_signal_connect(resetButton, "clicked", G_CALLBACK(play1v1_bot), robot);
    gtk_container_add(vbox, resetButton);

    layout alignment = gtk_alignment_new(0.5, 0.35, 0, 0);
    gtk_container_add(alignment, vbox);
    
    gtk_container_add(window, alignment);

    g_print("\nPlayer X's turn, enter the place no[1-9]\n");

    aWindow = window; 
    displayFinal(aWindow);
}
// BACKEND    BACKEND    BACKEND   BACKEND

// NO CHANGE TO BACKEND FUNCTIONS (for now)
void victoryX(int a){
    if(a==3){
    gtk_label_set_text(Turn, "\tGAME OVER \nX  IS  THE  WINNER !!!");
    gtk_button_set_label(resetButton, "Play Again"); 
    g_print("X IS THE WINNER!!!\n");
    *Alive = 0; //dead
  }
}

void victoryY(int a){
  if(a==3){
    gtk_label_set_text(Turn, "\tGAME OVER \nO  IS  THE  WINNER !!!"); 
    gtk_button_set_label(resetButton, "Play Again");  
    g_print("O IS THE WINNER!!!\n");
    *Alive = 0; //dead
  }
}

int check(int k[9], int XorY, int mode) {
    int i,counth1=0,counth2=0,counth3=0,countv1=0,countv2=0,countv3=0,countlc=0,countrc=0;
    
    // to determine whether victoryX or victoryY
    if (XorY == 1)  victory = victoryX;
    else  victory = victoryY;
    
    if (topm >= 1) {
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
            // for(j = 1; j < 5; j++) {
            //     if (k[i] == j || k[i] == 5 || k[i] = 10-j)
            // }
        }
    }
    if (mode == 1) {
        if (topn == -1) {
            if (b[4] == ' ') return 5;
            else return 1;
        }
        if(topm >= 1){
            if (freeWill(counth1, b, 0, 1, 2) != -1) return freeWill(counth1, b, 0, 1, 2);
            if (freeWill(counth2, b, 3, 4, 5) != -1) return freeWill(counth2, b, 3, 4, 5);
            if (freeWill(counth3, b, 6, 7, 8) != -1) return freeWill(counth3, b, 6, 7, 8);
            if (freeWill(countv1, b, 0, 3, 6) != -1) return freeWill(countv1, b, 0, 3, 6);
            if (freeWill(countv2, b, 1, 4, 7) != -1) return freeWill(countv2, b, 1, 4, 7);
            if (freeWill(countv3, b, 2, 5, 8) != -1) return freeWill(countv3, b, 2, 5, 8);
            if (freeWill(countlc, b, 0, 4, 8) != -1) return freeWill(countlc, b, 0, 4, 8);
            if (freeWill(countrc, b, 2, 4, 6) != -1) return freeWill(countrc, b, 2, 4, 6);
            return 25; 
        }
    }
}

int computer_move(int k[9]) {
    if (b[(k[topm] - 1) - 1] == ' ') return k[topm] - 1 ;
    if (b[(k[topm] + 1) - 1] == ' ') return k[topm] + 1 ;
    if (b[(k[topm] - 3) - 1] == ' ') return k[topm] - 3 ;
    if (b[(k[topm] + 3) - 1] == ' ') return k[topm] + 3 ;
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') return i + 1;
    }
}
// NO CHNAGE TO BACKEND 

void displayFinal(layout window) {

    gtk_window_maximize(window);
    gtk_widget_show_all(window);
    gtk_widget_hide(bWindow);
    bWindow = window;
    
}

layout mainDisplay() {

    resetValues();
    layout window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(window, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    layout vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    layout oneV1 = gtk_button_new_with_label("Play 1v1");
    g_signal_connect(oneV1, "clicked", G_CALLBACK(play1v1_bot), 0);
    gtk_container_add(vbox, oneV1);

    layout vsComp = gtk_button_new_with_label("Against bot");
    g_signal_connect(vsComp, "clicked", G_CALLBACK(play1v1_bot), 1);
    gtk_container_add(vbox, vsComp);

    layout alignment = gtk_alignment_new(0.5,0.5,0.2,0.2);
    gtk_container_add(alignment, vbox);
    gtk_container_add(window, alignment);

    aWindow = window;

    displayFinal(aWindow);
}

// MAIN FUCNTION     MAIN FUCNTION     MAIN FUCNTION  
int main(int argc, char *argv[]) {
    // call only functions
    gtk_init(&argc, &argv);
    mainDisplay();

    gtk_main();
    
    return 0;
}

//END
