#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

typedef GtkWidget * layout;

//global declarations
//front-end
void play1v1(int argc, char* argv[]);
layout Turn;
layout mainDisplay();
layout aWindow; //after Window
layout bWindow; //before Window;
layout resetButton;

int Count = 0;
int* count = &Count;
int ButtonNum = 0;
int *buttonNum = &ButtonNum;

//back-end
int M[10],N[10],topm = -1,topn = -1;
// Function pointer
typedef void (*Func)(int);
Func victory;
void check(int k[10], int XorY);

//funtion for window
typedef layout (*win)();

char b[9]; // = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int buttonPressed[9];

// START 
void buttonText(layout widget, int data) {
    int i; 
    //button clicking only once 
    if (buttonPressed[data-1] == 0)  {
        buttonPressed[data-1] = 1;
        (*count)++; 
        if (Count <= 9) {
            char* Text = (Count % 2 == 0) ? "O" : "X" ;
            char* player = (Count % 2 == 0) ? "Player X" : "Player O" ;
            //g_print("count = %d, buttonNumber = %d",count, data);
            gtk_button_set_label(widget, Text);
            gtk_label_set_text(Turn, player);

            //(backend)
            for (i = 0; i < 9; i++) {
                if (i == data-1) b[i] = (Text == "O") ? 'O' : 'X'; 
            }
            
            // display func from BACKEND
            g_print("\t %c | %c | %c \n",b[0],b[1],b[2]);
            g_print("\t---|---|---\n");
            g_print("\t %c | %c | %c \n",b[3],b[4],b[5]);
            g_print("\t---|---|---\n");
            g_print("\t %c | %c | %c \n",b[6],b[7],b[8]);
            
            //win condition check
            if (Count % 2 == 0) {
                N[++topn] = data;
                check(N, 0);
            } else {
                M[++topm] = data;
                check(M, 1);
            }
            if (Count < 9) g_print("\n%s\'s turn, enter the place no[1-9]\n", player);
            //(backend) 
        } 
        if (Count == 9) {
            gtk_label_set_text(Turn, "MATCH DRAW!!!"); 
            gtk_button_set_label(resetButton, "Play Again");
            g_print("\nMATCH DRAW!!!\n");
        } else {
            return;
        }
    }
}
    
//NO CHANGE
layout button(layout Button) {
    Button = gtk_button_new_with_label(" ");
    g_signal_connect(Button, "clicked", G_CALLBACK(buttonText),++(*buttonNum));
    gtk_widget_set_size_request(Button, 75, 75);
    return Button;
}

//NO CHANGE 
layout box(layout buttonX, layout buttonY, layout buttonZ) {
    layout hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    gtk_container_add(hbox, button(buttonX));
    gtk_container_add(hbox, button(buttonY));
    gtk_container_add(hbox, button(buttonZ));

    return hbox;
}

void resetValues() {
    int i;
    for (i = 0; i < 9; i++) {
        b[i] = ' '; 
        buttonPressed[i] = 0;
    }
    *count = 0;
    *buttonNum = 0;
    topm = topn = -1;
}
layout reset(int argc, char* argv[]) {
    resetValues();

    //display window after Reset
    play1v1(argc, argv);
}

// NO CHANGE
void play1v1(int argc, char* argv[]) {
    //local declarations
    layout button[9], hbox[3];
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
    
    int j, i = 0;
    for (j = 0; j < 3; j++) {
        //adding boxes(containing 3 buttons each) to main box and window
        hbox[j] = box(button[i], button[++i], button[++i]);
        gtk_container_add(vbox, hbox[j]);
        i++;
    }

    resetButton = gtk_button_new_with_label("Reset");
    g_signal_connect(resetButton, "clicked", G_CALLBACK(reset),NULL);
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
    gtk_label_set_text(Turn, "GAME OVER"); 
    g_print("X IS THE WINNER!!!\n");
  }
}

void victoryY(int a){
  if(a==3){
    gtk_label_set_text(Turn, "GAME OVER"); 
    g_print("O IS THE WINNER!!!\n");
  }
}

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
    g_signal_connect(oneV1, "clicked", G_CALLBACK(play1v1), NULL);
    gtk_container_add(vbox, oneV1);

    layout vsComp = gtk_button_new_with_label("Against bot");
    //g_signal_connect(vsComp, "clicked", G_CALLBACK(), NULL);
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
