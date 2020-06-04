#include <ncurses.h>

class Pane {
protected :
int width_, height_;
int x_, y_;
WINDOW *win_;
public:
Pane(int x, int y, int w, int h) :x_(x), y_(y), width_(w), height_(h){
win_ = newwin(h, w, y, x);
}
virtual ~Pane(){
delwin(win_);
}
virtual void draw(){
box(win_, 0, 0);
wrefresh(win_);
}
};

class InfoPane : public Pane {
public:
InfoPane(int x, int y, int w, int h) : Pane(x,y,w,h){}
void draw(){
init_pair(2, COLOR_GREEN, COLOR_BLACK);
wattron(win_, COLOR_PAIR(2));
for (int i=0; i<height_; i++)
mvwhline(win_, i, 0, ACS_CKBOARD, width_);
mvwprintw(win_, 0,0, "INFO PANE");
wattroff(win_, COLOR_PAIR(2));
wrefresh(win_);
}
};

class HelpPane : public Pane {
public:
HelpPane(int x, int y, int w, int h) : Pane(x,y,w,h){}
void draw(){
init_pair(3, COLOR_WHITE, COLOR_BLACK);
wattron(win_, COLOR_PAIR(3));
for (int i=0; i<height_; i++)
mvwhline(win_, i, 0, ACS_CKBOARD, width_);
mvwprintw(win_, 0,0, "HELP PANE");
wattroff(win_, COLOR_PAIR(3));
wrefresh(win_);
}
};

class NextPane : public Pane {
public:
NextPane(int x, int y, int w, int h) : Pane(x,y,w,h){}
void draw(){
init_pair(4, COLOR_BLUE, COLOR_BLACK);
wattron(win_, COLOR_PAIR(4));
for (int i=0; i<height_; i++)
mvwhline(win_, i, 0, ACS_CKBOARD, width_);
mvwprintw(win_, 0,0, "NEXT PANE");
wattroff(win_, COLOR_PAIR(4));
wrefresh(win_);
}
};


class BoardPane : public Pane {
public:
BoardPane(int x, int y, int w, int h) : Pane(x,y,w,h){}
void draw(){
init_pair(5, COLOR_BLUE, COLOR_BLACK);
wattron(win_, COLOR_PAIR(5));
mvwhline(win_, 0, 0, ACS_HLINE, width_);
mvwvline(win_, 1, 0, ACS_VLINE, height_ - 5);
mvwvline(win_, 1, width_-1, ACS_VLINE, height_ - 5);
mvwhline(win_, height_ - 5, 0, ACS_HLINE, width_);
mvwhline(win_,  0, 0, ACS_ULCORNER, 1);
mvwhline(win_,  0,21, ACS_URCORNER, 1);
mvwhline(win_, 19, 0, ACS_LLCORNER, 1);
mvwhline(win_, 19,21, ACS_LRCORNER, 1);
for (int i=0; i<height_-6;i++)
mvwhline(win_, i+1, 1, ACS_CKBOARD, width_-2);
wattroff(win_, COLOR_PAIR(5));
wrefresh(win_);
}
};

class StatPane : public Pane {
public:
StatPane(int x, int y, int w, int h) : Pane(x,y,w,h){}
void draw(){
init_pair(6, COLOR_RED, COLOR_BLACK);
wattron(win_, COLOR_PAIR(6));
box(win_, 0, 0);
mvwprintw(win_, 0, 5, "STATISTICS");
wattroff(win_, COLOR_PAIR(6));
wrefresh(win_);
}
};

class Tetris {
Pane *infoPane_, *helpPane_, *nextPane_, *boardPane_, *statPane_;
public:
Tetris(){
initscr();
start_color();
cbreak();
refresh();
infoPane_ = new InfoPane(1,1,25,5);
helpPane_ = new HelpPane(1,6,25,12);
nextPane_ = new NextPane(1,18,25,5);
boardPane_ = new BoardPane(30,0,22,24);
statPane_ = new StatPane(60,3,20,20);
}
~Tetris(){
delete infoPane_;
delete helpPane_;
delete nextPane_;
delete boardPane_;
delete statPane_;
endwin();
}

void play(){
int input;
updateScreen();
input = getch();
}

void updateScreen(){
infoPane_->draw();
helpPane_->draw();
nextPane_->draw();
boardPane_->draw();
statPane_->draw();
}
};

int main(){
Tetris t;
t.play();
}
