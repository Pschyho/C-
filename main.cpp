#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int field[4][4];
int slot[4];

struct coord {
    int x;
    int y;
};

bool isFilled(int n){
    if (n!=0){
        return true;
    }
    else{
        return false;
    }
}
//************************************
//algorithm
bool isSlotFilled(int n){
    return slot[n]!=0;
}

bool hasSlotFilled(){
    bool filled = false;
    for ( int i =0; i<4; ++i){
        if (isSlotFilled(i)){
            filled=true;
        }
    }
    return filled;
}

bool hasSlotFilledFrom(int n ){
    bool filled=false;
    while (n<4 && !filled){
        filled=isSlotFilled(n);
        ++n;
    }
    return filled;
}

void moveFirst(){
    int x=0;
    while (!isSlotFilled(x)){
        ++x;
    }
    int saver = slot[x];
    slot[x]=0;
    slot[0]=saver;
}

int firstFilledFrom(int n){  //should be only used when there is a filled slot
    while (!isSlotFilled(n)){
        ++n;
    }
    return n;
}

void step(){
    int counter=0;
    int last;
    if (hasSlotFilled()){
        moveFirst();
        last=0;
        counter++;
        bool wasMerge=false;
        while (counter<4 && hasSlotFilledFrom(counter)){
            int firstfilled=firstFilledFrom(counter);

            //compare last and first
            if (!wasMerge && slot[last]==slot[firstfilled]){
                slot[last]*=2;
                slot[firstfilled]=0;
                wasMerge=true;
            }
            else{
                int saver =slot[firstfilled];
                slot[firstfilled]=0;
                slot[++last]=saver;
                wasMerge=false;
            }
            ++counter;
        }
    }
}
//************************************

void show(int n){
    if (isFilled(n)){
        cout<<n;
    }
    else{
        cout<<" ";
    }
}


void display(){
    system("CLS");
    cout<<"-----------------------------------"<<endl;
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"| ";
    show(field[0][0]);
    cout<<"\t | ";
    show(field[0][1]);
    cout<<"\t  | ";
    show(field[0][2]);
    cout<<"\t  | ";
    show(field[0][3]);
    cout<<"\t  |\n";
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"| ";
    show(field[1][0]);
    cout<<"\t | ";
    show(field[1][1]);
    cout<<"\t  | ";
    show(field[1][2]);
    cout<<"\t  | ";
    show(field[1][3]);
    cout<<"\t  |\n";
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"| ";
    show(field[2][0]);
    cout<<"\t | ";
    show(field[2][1]);
    cout<<"\t  | ";
    show(field[2][2]);
    cout<<"\t  | ";
    show(field[2][3]);
    cout<<"\t  |\n";
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"| ";
    show(field[3][0]);
    cout<<"\t | ";
    show(field[3][1]);
    cout<<"\t  | ";
    show(field[3][2]);
    cout<<"\t  | ";
    show(field[3][3]);
    cout<<"\t  |\n";
    cout<<"|  \t | \t  | \t  | \t  |"<<endl;
    cout<<"-----------------------------------"<<endl;
}

void fillUpField(){
    for ( int i=0; i<4; ++i){
        for ( int j=0; j<4; ++j){
            field[i][j]=0;
        }
    }
}

void startGame(){
    srand (time(NULL));
    for ( int i =0; i<2;++i){
        bool isFreeCoord = false;
        while (!isFreeCoord){
            int cordX = rand() % 4;
            int cordY = rand() % 4;
            if (field[cordX][cordY]==0){
                isFreeCoord=true;
                field[cordX][cordY]=2;
            }
        }
    }
}

bool isOver(){
    int i=0;
    bool over=false;
    while (i<4 && !over){
        int j=0;
        while (j<4 && !over){
            if (field[i][j]==2048){
                over=true;
            }
            ++j;
        }
        ++i;
    }
    return over;
}

bool isFull(){
    bool full =true;
    int i=0;
    while (i<4 && full){
        int j=0;
        while (j<4 && full){
            if (field[i][j]==0){
                full=false;
            }
            ++j;
        }
        ++i;
    }
    if (full){
        for (int i=0; i<4; ++i){
            for (int j=0; j<3; ++j){
                if (field[i][j]==field[i][j+1] || field[j][i]==field[j+1][i]){
                    full=false;
                }
            }
        }
     return full;
    }
    else {
        return full;
    }


}

int main()
{
    fillUpField();
    startGame();
    display();
    srand (time(NULL));
    char move;
    coord firstemptycell;
    coord firstfilled;
    while (!isOver() && !isFull()){
        cin>>move;
        int savefield[4][4];
        for (int i=0; i<4; ++i){
            for (int j =0; j<4; ++j){
                savefield[i][j]=field[i][j];
            }
        }
        if (move=='w'){
            for ( int i =0; i<4; ++i){
                for (int j =0; j<4; ++j){
                    slot[j]=field[j][i];
                }
                step();
                for (int j=0; j<4; ++j){
                    field[j][i]=slot[j];
                }
            }
        }
        else if (move=='a'){
            for ( int i =0; i<4; ++i){
                for (int j =0; j<4; ++j){
                    slot[j]=field[i][j];
                }
                step();
                for (int j=0; j<4; ++j){
                    field[i][j]=slot[j];
                }
            }
        }
        else if (move=='s'){
            for ( int i =0; i<4; ++i){
                for (int j =0; j<4; ++j){
                    slot[3-j]=field[j][i];
                }
                step();
                for (int j=0; j<4; ++j){
                    field[j][i]=slot[3-j];
                }
            }
        }
        else if (move=='d'){
            for ( int i =0; i<4; ++i){
                for (int j =0; j<4; ++j){
                    slot[3-j]=field[i][j];
                }
                step();
                for (int j=0; j<4; ++j){
                    field[i][j]=slot[3-j];
                }
            }
        }
        else{
            continue;
        }
        bool wasAnyChange=false;
        int i=0;
        while (i<4 && !wasAnyChange){
            int j =0;
            while (j<4 && !wasAnyChange){
                if (savefield[i][j]!=field[i][j]){
                    wasAnyChange=true;
                }
                ++j;
            }
            ++i;
        }
        bool isFreeCoord = false;
        while (!isFreeCoord && wasAnyChange){
            int cordX = rand() % 4;
            int cordY = rand() % 4;
            if (field[cordX][cordY]==0){
                isFreeCoord=true;
                field[cordX][cordY]=2;
            }
        }
        display();

    }
    if (isOver()){
    cout<<"Congratulation, you won!";
    }
    else{
    cout<<"You lost!";
    }
    return 0;
}
