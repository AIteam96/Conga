#include<iostream>
#include<vector>
#define Max 4

//Container 
struct Game_Grid{
    vector <vector<Grid_Cell> > Grid;
    short int size;
}

struct Player{
    short int Wich_Player; //1 , 2
    short int Max_Depth;
}

struct Grid_Cell{
    struct player p;
    short int Stone_Num;
    bool IsInUse;
}

//create the gride 
void Initial(){
    vector<vector<Grid_Cell> > G;
    for (short int i = 0 ; i < Max ; i++){
        for (short int j = 0 ; j < Max ; j++){
            G.Grid[i][j].IsInUse = false;
            G.Grid[i][j].Stone_Num = 0;
        }
    }
}
    
vector<Game_Grid> successor(Game_Grid G , Player Turn){
    vector<Game_Grid> Grid_List;
    Game_Grid Temp = G;
    for (short int i = 0 ; i < Temp.size ; i++){
        for (short int j = 0 ; j <Temp.size ; j++){

            if(j < Temp.size && Temp.Grid[i][j+1].Wich_Player == turn || Temp.Grid[i][j+1].Wich_Player.IsInUse == false){
                Temp.Grid[i][j+1].Stone_Num ++;
                Temp.Grid[i][j+1].IsInUse = true;
                Temp.Grid[i][j+1].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }

            if(j > 0 && Temp.Grid[i][j-1].Wich_Player == turn || Temp.Grid[i][j-1].Wich_Player.IsInUse == false){
                Temp.Grid[i][j-1].Stone_Num ++;
                Temp.Grid[i][j-1].IsInUse = true;
                Temp.Grid[i][j-1].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }
            
            if(i < Temp.size && Temp.Grid[i+1][j].Wich_Player == turn || Temp.Grid[i+1][j].Wich_Player.IsInUse == false){
                Temp.Grid[i+1][j].Stone_Num ++;
                Temp.Grid[i+1][j].IsInUse = true;
                Temp.Grid[i+1][j].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }

            if(i > 0 && Temp.Grid[i-1][j].Wich_Player == turn || Temp.Grid[i-1][j].Wich_Player.IsInUse == false){
                Temp.Grid[i-1][j].Stone_Num ++;
                Temp.Grid[i-1][j].IsInUse = true;
                Temp.Grid[i-1][j].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }

            if((i > 0 &&  j > 0) && Temp.Grid[i-1][j-1].Wich_Player == turn || Temp.Grid[i-1][j-1].Wich_Player.IsInUse == false){
                Temp.Grid[i-1][j-1].Stone_Num ++;
                Temp.Grid[i-1][j-1].IsInUse = true;
                Temp.Grid[i-1][j-1].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }

            if((i < Temp.size && j < Temp.size ) && Temp.Grid[i+1][j-1].Wich_Player == turn || Temp.Grid[i+1][j-1].Wich_Player.IsInUse == false){
                Temp.Grid[i+1][j-1].Stone_Num ++;
                Temp.Grid[i+1][j-1].IsInUse = true;
                Temp.Grid[i+1][j-1].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }

            if((i > 0 && j < Temp.size ) && Temp.Grid[i-1][j+1].Wich_Player == turn || Temp.Grid[i-1][j+1].Wich_Player.IsInUse == false){
                Temp.Grid[i-1][j+1].Stone_Num ++;
                Temp.Grid[i-1][j+1].IsInUse = true;
                Temp.Grid[i-1][j+1]].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }

            if((i < Temp.size && j < Temp.size ) && Temp.Grid[i+1][j+1].Wich_Player == turn || Temp.Grid[i+1][j+1].Wich_Player.IsInUse == false){
                Temp.Grid[i+1][j+1].Stone_Num ++;
                Temp.Grid[i+1][j+1].IsInUse = true;
                Temp.Grid[i+1][j+1]].Wich_Player = Turn;
                Grid_List.push_back(Temp);
            }
        }
    }
    return Grid_List;
}