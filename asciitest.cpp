#include "mcurses.h"

int main(){
    mcurses* curses = new mcurses(1,1,1,1);
    /*int input;
    printf("ASCIITEST, (c) mrybs, 2022\n"
           "Press any key, <Esc> to exit\n");
    while(1){
        input = curses->getch();
        if((input == 0) || (input == 0xe0)){
            input = curses->getch();
            cout << "Extended code ASCII:\t";
        }
        else cout << "Code ASCII:\t";
        cout << input << endl;
        if(input == 27) return 0;
    }*/
    int key;

    printf("KBDASCII, (c) A. Frolov, 1997\n"
           "Press any key, <Esc> to exit\n");

    for(;;)
    {
        // Читаем символ
        key = curses->getch();
        if((key == 0) || (key == 0xe0))
        {
            key = curses->getch();
            printf("Extended code ASCII:\t" );
        }
        else
            printf( "Code ASCII:\t");

        printf("%d\n",key);
        if(key == 27)
            break;
    }
}