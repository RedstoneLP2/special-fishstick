#include "common.h"

ioHandler::ioHandler()
{
    initscr();
    noecho();
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
    box(debugWindow, 0, 0);
    box(ioWindow, 0, 0);

    wrefresh(ioWindow);
    wrefresh(debugWindow);

    wprintw(ioWindow,"IOWINDOW");
    wprintw(debugWindow,"DEBUGWINDOW");

    wmove(debugWindow, 1, 1);
    wmove(ioWindow, 1, 1);

    wrefresh(ioWindow);
    wrefresh(debugWindow);
    //refresh();
}

void ioHandler::printIoChar(char ch){
    wprintw(ioWindow,"%c",ch);
    wrefresh(ioWindow);
    refresh();
}
void ioHandler::printIoString(std::string string){
    wprintw(ioWindow,"DEBUG: %s\n",string.c_str());
    wrefresh(ioWindow);
    refresh();
}

void ioHandler::printDebugChar(char ch){
    wprintw(debugWindow,"%c",ch);
    wrefresh(debugWindow);
    refresh();
}

void ioHandler::printDebugString(std::string string){
    wprintw(debugWindow,"DEBUG: %s\n",string.c_str());
    wrefresh(debugWindow);
    refresh();
}