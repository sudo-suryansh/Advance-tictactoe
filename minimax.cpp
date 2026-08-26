#include<iostream>
#include<string>
#include <chrono>
#include <thread>
#include <ctime>
using namespace std;
bool retry = true;
bool debug = false;
int tries = 0;
char space[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
int rules[8][3]={
    {0,1,2},{3,4,5},{6,7,8},
    {0,3,6},{1,4,7},{2,5,8},
    {0,4,8},{2,4,6}
};

int drawBoard(){
    system("cls");
    cout<<"      |      |      \n";
    cout<<"   "<<space[0]<<"  |"<<"   "<<space[1]<<"  |"<<"   "<<space[2]<<"  \n";
    cout<<"______|______|______\n";
    cout<<"      |      |      \n";
    cout<<"   "<<space[3]<<"  |"<<"   "<<space[4]<<"  |"<<"   "<<space[5]<<"  \n";
    cout<<"______|______|______\n";
    cout<<"      |      |      \n";
    cout<<"   "<<space[6]<<"  |"<<"   "<<space[7]<<"  |"<<"   "<<space[8]<<"  \n";
    cout<<"      |      |      \n";
    return 0;
}


int checkWin(){ // 0=ongoing, 1=X win, 2=O win, 3=tie
    for(int i=0;i<8;i++){
        int a=rules[i][0], b=rules[i][1], c=rules[i][2];
        if(space[a]!=' ' && space[a]==space[b] && space[b]==space[c])
            return (space[a]=='X') ? 1 : 2;
    }
    for(int i=0;i<9;i++) if(space[i]==' ') return 0;
    return 3;
}

int declareResult(bool pvp){
    if(checkWin()==1){
        drawBoard();
        pvp? cout<<"PLAYER X WINS!!"<<endl:cout<<"PLAYER WINS!!"<<endl;
        return 1;
    }
    if(checkWin()==2){
        drawBoard();
        pvp? cout<<"PLAYER O WINS!!"<<endl:cout<<"AI WINSS!!"<<endl;
        return 1;
    }
    if(checkWin()==3){
        drawBoard();
        cout<<"TIE"<<endl;
        return 1;
    }
    return 0;
}

int minMax(bool turn){
    int result = checkWin();
    if(result!=0){
        if(result == 2) return  1; 
        if(result == 1) return -1; 
        return 0;
    }
    int bestAI=-2;
    if(turn){
        for(int i=0;i<9;i++){
            if(space[i]==' '){
                space[i]='O';
                int bestScore = minMax(false);
                space[i]=' ';
                if(bestScore>bestAI){
                    bestAI=bestScore;
                }
            }
        }
        if(debug) cout<<"AI: "<<bestAI<<endl;
        
        return bestAI;
    }
    else{
        int bestHuman=2;
        for(int i=0;i<9;i++){
            if(space[i]==' '){
                space[i]='X';
                int bestScore = minMax(true);
                space[i]=' ';
                if(bestScore<bestHuman){
                    bestHuman=bestScore;
                }
            }
        }
        if(debug) cout<<"HUMAN: "<<bestHuman<<endl;
        return bestHuman;
    }
}

int ai(){
    int bestAI=-2;
    int bestMove=-1;
    for(int i=0;i<9;i++){
        if(space[i]==' '){
            space[i]='O';
            int bestScore = minMax(false);
            space[i]=' ';
            if(bestScore>bestAI){
                bestAI=bestScore;
                bestMove=i;
            }
        }
    }
    space[bestMove]='O';
    return 0;
}


int heuristicAI(bool diff){
    for(int i = 0; i<8;i++){
        int a = rules[i][0];
        int b = rules[i][1];
        int c = rules[i][2];
        if(space[a]==' '&&space[b]==space[c]&&space[b]=='O') {
           space[a]='O';
           return 0;
        }
        else if(space[b]==' '&&space[a]==space[c]&&space[a]=='O') {
           space[b]='O';
           return 0;
        }
        else if(space[c]==' '&&space[a]==space[b]&&space[a]=='O') {
           space[c]='O';
           return 0;
        }
    }
    for(int i = 0; i<8;i++){
        int a = rules[i][0];
        int b = rules[i][1];
        int c = rules[i][2];
        if(space[a]==' '&&space[b]==space[c]&&space[b]=='X') {
           space[a]='O';
           return 0;
        }
        else if(space[b]==' '&&space[a]==space[c]&&space[a]=='X') {
           space[b]='O';
           return 0;
        }
        else if(space[c]==' '&&space[a]==space[b]&&space[a]=='X') {
           space[c]='O';
           return 0;
        }
    }

    if(!diff){
        srand(time(NULL));
        while(true){
            int i = rand() % 9;
            if(space[i] == ' '){
                space[i] = 'O';
                return 0;
            }
        } 
    }

    if(diff){
        if(space[4]==' '){
            space[4]='O';
            return 0;
        }

        else if(space[4]=='X'){
                if(tries<2){
                for(int i = 0; i<3;i+=2){
                    int a = rules[i][0];
                    int b = rules[i][2];//0 2
                    if(space[a]==' '||space[b]==' '){
                        if(tries == 1)
                            space[b] = 'O';
                        else
                            space[a] = 'O';

                        tries++;
                        return 0;
                    }
                }
            }
        }

        else if(space[4]=='O'&&space[0]=='X'&&space[8]=='X'){
            if(space[1]==' '){
                space[1]='O';
                return 0;
            }
            else if(space[7]==' '){
                space[7]='O';
                return 0;
            }
        }
        else if(space[4]=='O'&&space[2]=='X'&&space[6]=='X'){
            if(space[1]==' '){
                space[1]='O';
                return 0;
            }
            else if(space[7]==' '){
                space[7]='O';
                return 0;
            }
        }

        while(true){
            int i = rand() % 9;
            if(space[i] == ' '){
                space[i] = 'O';
                return 0;
            }
        }
    }
    return 0;
}

int human(bool &retry, bool pvp, bool flip){
    cout<<"Enter pos for your move: ";
    int pos;
    if(!(cin>>pos)){
        retry=true;
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }
    if(pos>9||pos<1){
        retry=true;
        return 0;

    }
    if(space[pos-1]==' '){
        if(pvp && !flip){
            space[pos-1]='X';
        }
        if(pvp && flip){
            space[pos-1]='O';
        }
        if(!pvp){
            space[pos-1]='X';
        }
        retry = false;
        return 0;
    }
    else{retry = true;return 0;}

    
    return 0;

}
int main(){
    int choice;
    while(true){
        cout<<"ENTER GAME MODE: "<<endl;
        cout<<"1. PVP\n2. AI VS PLAYER\n:";
        if(!(cin>>choice)){
            retry=true;
            cin.clear();
            cin.ignore(10000, '\n');
            system("cls");
        }
        if(choice>2||choice<1){
            continue;
        }
        break;
    }

    if(choice==1){
        bool run = true;
        while(run){
            drawBoard();
            retry=true;
            while(retry){
                human(retry, true, true);
            }
            if(checkWin()!=0){ declareResult(true); return 0;}

            drawBoard();
            retry=true;
            while(retry){
                human(retry, true, false);
            }
            drawBoard();

            if(checkWin()!=0){ declareResult(true); return 0;}
        }   
    }

    if(choice==2){
        int choice;
        while(true){
            cout<<"ENTER GAME DIFFICULTY: "<<endl;
            cout<<"1. EASY\n2. MEDIUM\n3. HARD\n4. IMPOSSIBLE (it really is):";
            if(!(cin>>choice)){
                retry=true;
                cin.clear();
                cin.ignore(10000, '\n');
                system("cls");
            }
            if(choice>4||choice<1){
                continue;
            }
            break;
        }
        //EASY MODE (randomness)
        if(choice==1){
            while(true){
                drawBoard();
                retry=true;
                while(retry){
                    human(retry, false, false);
                }
                drawBoard();
                if(checkWin()!=0){ declareResult(false); return 0;}
                srand(time(NULL));
                while(true){
                    int i = rand() % 9;
                    if(space[i] == ' '){
                        space[i] = 'O';
                        break;
                    }
                }
                drawBoard();
                
                if(checkWin()!=0){ declareResult(false); return 0;}
            }  
        }
        if(choice==2){
            while(true){
                drawBoard();
                retry=true;
                while(retry){
                    human(retry, false, false);
                }
                drawBoard();
                if(checkWin()!=0){ declareResult(false); return 0;}
                
                heuristicAI(false);
                drawBoard();

                if(checkWin()!=0){ declareResult(false); return 0;}
            }
        }
        if(choice==3){
            while(true){
                drawBoard();
                retry=true;
                while(retry){
                    human(retry, false, false);
                }
                drawBoard();
                if(checkWin()!=0){ declareResult(false); return 0;}
                
                heuristicAI(true);
                drawBoard();

                if(checkWin()!=0){ declareResult(false); return 0;}
            }
        }
    }

    debug = false;
    cout<<"\nDo you want to see AI thinking tree ?(Y/N): ";
    char choice2;cin>>choice2;
    
    if(choice2=='Y'||choice2=='y'){
        debug=true;
    }
    
    while(true){
        drawBoard();
        retry=true;
        while(retry){
            human(retry, false, false);
        }
        if(checkWin()!=0){ declareResult(false); return 0;}
        
        ai();
        drawBoard();
        
        if(checkWin()!=0){ declareResult(false); return 0;}
    }



    return 0;
}