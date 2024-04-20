#include "common.h"

ioHandler::ioHandler()
{
    initscr();
    noecho();
    raw();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    refresh();

    int height = LINES;
	int width = (COLS/2)-1;
	int starty = (LINES - height);
	int startx = (COLS - width);
	debugWindow = newwin(height, width, starty, startx);
    ioWindow = newwin(height, width, starty, 0);
    scrollok(debugWindow,TRUE);
    scrollok(ioWindow,TRUE);
    printHeader();
    refresh();
}

ioHandler::~ioHandler(){
    endwin();
}

char ioHandler::handleInput(){
    return getch();
}

void ioHandler::printHeader(){
    int debugY,debugX,ioY,ioX;
    getyx(debugWindow,debugY,debugX);
    getyx(ioWindow,ioY,ioX);

    if (debugY == 0) debugY = 1;
    if (debugX == 0) debugX = 1;
    if (ioY == 0) ioY = 1;
    if (ioX == 0) ioX = 1;

    box(debugWindow, 0, 0);
    box(ioWindow, 0, 0);

    wrefresh(ioWindow);
    wrefresh(debugWindow);

    wmove(debugWindow, 0, 0);
    wmove(ioWindow, 0, 0);

    wprintw(ioWindow,"IOWINDOW");
    wprintw(debugWindow,"DEBUGWINDOW");

    wmove(debugWindow, debugY, debugX);
    wmove(ioWindow, ioY, ioX);

    wrefresh(ioWindow);
    wrefresh(debugWindow);
    //refresh();
}

void ioHandler::printIoChar(char ch){
    if (ch == 0x0A){
        int y,x;
        getyx(ioWindow,y,x);
        wmove(ioWindow,y+1,x);
    }else if (ch == 0x0D){
        int y,x;
        getyx(ioWindow,y,x);
        wmove(ioWindow,y,1);
    }else{
        wprintw(ioWindow,"%c",ch);
    }
    printHeader();
    wrefresh(ioWindow);
    refresh();
}
void ioHandler::printIoString(std::string string){
    int y,x;
    getyx(ioWindow,y,x);
    wmove(ioWindow,y,1);
    wprintw(ioWindow,"%s\n",string.c_str());
    printHeader();
    wrefresh(ioWindow);
    refresh();
}

void ioHandler::printDebugChar(char ch){
    if (ch == 0x0A){
        int y,x;
        getyx(debugWindow,y,x);
        wmove(debugWindow,y+1,x);
    }else if (ch == 0x0D){
        int y,x;
        getyx(debugWindow,y,x);
        wmove(debugWindow,y,1);
    }else{
        wprintw(debugWindow,"%c",ch);
    }
    wprintw(debugWindow,"%c",ch);
    printHeader();
    wrefresh(debugWindow);
    refresh();
}

void ioHandler::printDebugString(std::string string){
    int y,x;
    getyx(debugWindow,y,x);
    wmove(debugWindow,y,1);
    wprintw(debugWindow,"DEBUG: %s\n",string.c_str());
    printHeader();
    wrefresh(debugWindow);
    refresh();
}