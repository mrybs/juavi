#include "../../mcurses.h"
#include <random>

using namespace std;

int randomINT(int min, int max);
void renderSnake(bool snake[][20], mcurses* screen, string color, string bgColor);

int main(){
    const float x = 20, y = 20, aspect = 2;
    float fruitx = randomINT(0, x-1), fruity = randomINT(0,y-1);
    bool snake[int(x)][int(y)];
    /*for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            snake[i][j] = false;
        }
    }*/
    mcurses* scr = new mcurses(x, y, aspect, 24);
    scr->drawBackground("GREEN");
    //snake[int(x/2)][int(y/2)] = true;
    renderSnake(snake, scr, "BLACK", "GREEN");
    //scr->drawPoint(fruitx, fruity, "RED");
    scr->setCursor(0, y+1);
    return 0;
}

void renderSnake(bool snake[][20], mcurses* screen, string color, string bgColor){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(snake[i][j])
                screen->drawPoint(i, j, color);
            else
                screen->drawPoint(i, j, bgColor);
        }
    }
}

int randomINT(int min, int max){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(min,max);
    return dist6(rng);
}