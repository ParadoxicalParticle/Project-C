# TIC TAC TOE
GUI using gtk
<br>
coding in C language
<br>
<h4>Installation on Linux OS</h4>
GTK 3.0 version download (~160 MB)
<br>
For Ubuntu/Debian-based systems:
   sudo apt install libgtk-3-dev
<br>
For Fedora:
   sudo dnf install gtk3-devel
<br>
For Arch Linux:
   sudo pacman -S gtk3
<br>
Verifying the Installation: 
   pkg-config --modversion gtk+-3.0
<br>
<h4>Compilation code</h4>
cc [filename] `pkg-config --cflags --libs gtk+-3.0` -w
<br>
<h4>Output code:</h4>
 ./a.out
