#include<iostream>
#include<vector>
#include <utility>      // std::pair, std::make_pair

#define MAX 4
using namespace std;
//Container 
struct Game_Grid {
	vector <vector<Grid_Cell> > Grid;
};

struct Player {
	short int Wich_Player; //1 , 2
	short int MAX_Depth;
	short int score;
};

struct Grid_Cell {
	struct Player player;
	short int Stone_Num;
	bool IsInUse; //true when the cell is already taken O.W flase
};

//create the gride 
void Initial() {
	Game_Grid G;
	for (short int i = 0; i < MAX; i++) {
		for (short int j = 0; j < MAX; j++) {
			G.Grid[i][j].IsInUse = false;
			G.Grid[i][j].Stone_Num = 0;
		}
	}
}

vector<Game_Grid> successor(Game_Grid G, Player Turn) {
	vector<Game_Grid> Grid_List;
	Game_Grid Temp = G;
	pair<short int, short int> Current;

	for (short int i = 0; i < MAX; i++) {
		for (short int j = 0; j < MAX; j++) {
			Current.first = i;
			Current.second = j;
			if (i > 1)
			{
				Temp = move(Turn, 1, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (i > 1 && j > 1)
			{
				Temp = move(Turn, 2, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (j > 1)
			{
				Temp = move(Turn, 3, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (i < MAX && j < MAX)
			{
				move(Turn, 4, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (i < MAX)
			{
				Temp = move(Turn, 5, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (i < MAX && j > 1)
			{
				Temp = move(Turn, 6, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (j < MAX)
			{
				Temp = move(Turn, 7, Current, Temp);
				Grid_List.push_back(Temp);
			}
			if (i > 1 && j < MAX)
			{
				Temp = move(Turn, 8, Current, Temp);
				Grid_List.push_back(Temp);
			}
		}
	}
	return Grid_List;
}
/*
___ ___ ___ ___
|_8_|_1_|_2_|___|
|_7_|_c_|_3_|___|
|_6_|_5_|_4_|___|
|___|___|___|___|
if c is Current location, numbers show direction

*/
Game_Grid move(Player Turn, short int direction, pair<short int, short int> current_location, Game_Grid G)
{
	pair<short int, short int> next_step;
	switch (direction)
	{
	case 1:
		next_step.first = current_location.first;
		next_step.second = current_location.second + 1;
		break;
	case 2:
		next_step.first = current_location.first + 1;
		next_step.second = current_location.second + 1;
		break;
	case 3:
		next_step.first = current_location.first + 1;
		next_step.second = current_location.second;
		break;
	case 4:
		next_step.first = current_location.first + 1;
		next_step.second = current_location.second - 1;
		break;
	case 5:
		next_step.first = current_location.first;
		next_step.second = current_location.second - 1;
		break;
	case 6:
		next_step.first = current_location.first - 1;
		next_step.second = current_location.second - 1;
		break;
	case 7:
		next_step.first = current_location.first - 1;
		next_step.second = current_location.second;
		break;
	case 8:
		next_step.first = current_location.first - 1;
		next_step.second = current_location.second + 1;
		break;
	}
	short int stonesCount = 1;
	short int allStones = G.Grid[current_location.first][current_location.second].Stone_Num;
	while (0 <= next_step.first <= 4 && 0 <= next_step.second <= 4 && !G.Grid[next_step.first][next_step.second].IsInUse || G.Grid[next_step.first][next_step.second].player.Wich_Player == Turn.Wich_Player)
	{
		G.Grid[next_step.first][next_step.second].IsInUse = true;
		G.Grid[next_step.first][next_step.second].player = Turn;
		current_location = next_step;
		switch (direction)
		{
		case 1:
			next_step.first = current_location.first;
			next_step.second = current_location.second + 1;
			break;
		case 2:
			next_step.first = current_location.first + 1;
			next_step.second = current_location.second + 1;
			break;
		case 3:
			next_step.first = current_location.first + 1;
			next_step.second = current_location.second;
			break;
		case 4:
			next_step.first = current_location.first + 1;
			next_step.second = current_location.second - 1;
			break;
		case 5:
			next_step.first = current_location.first;
			next_step.second = current_location.second - 1;
			break;
		case 6:
			next_step.first = current_location.first - 1;
			next_step.second = current_location.second - 1;
			break;
		case 7:
			next_step.first = current_location.first - 1;
			next_step.second = current_location.second;
			break;
		case 8:
			next_step.first = current_location.first - 1;
			next_step.second = current_location.second + 1;
			break;
		}
		if (0 <= next_step.first <= 4 && 0 <= next_step.second <= 4 && !G.Grid[next_step.first][next_step.second].IsInUse)
		{
			G.Grid[current_location.first][current_location.second].Stone_Num = stonesCount;
			stonesCount++;
		}
		else
			G.Grid[current_location.first][current_location.second].Stone_Num = allStones - stonesCount - 1;
	}
	return G;
}

float MaxValue(Game_Grid G, Player maxplayer, Player minplayer,Game_Grid &best_Grid)
{
	 //if(!Terminal(G)){
	vector<Game_Grid> actions = successor(G, maxplayer);
	float resultVlue = -2.00;
	int i = 0;
	while (!actions.empty())
	{
		Game_Grid current_State = actions[i];i++;
		float currentRating = MinValue(G, maxplayer, minplayer, current_State);
		if (currentRating > resultVlue)
		{
			resultVlue = currentRating;
			best_Grid = current_State;
		}
	}
	return resultVlue;
	//}
	/*else
		return player.score;
	*/
}
float MinValue(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid)
{
	//if(!Terminal(G)){
	vector<Game_Grid> actions = successor(G, minplayer);
	float resultVlue = +2.00;
	int i = 0;
	while (!actions.empty())
	{
		Game_Grid current_State = actions[i]; i++;
		float currentRating = MaxValue(G, maxplayer, minplayer, current_State);
		if (currentRating < resultVlue)
		{
			resultVlue = currentRating;
			best_Grid = current_State;
		}
	}
	return resultVlue;
	//}
	/*else
	return player.score;
	*/
}
Game_Grid miniMAX(Game_Grid G, Player player1, Player player2)
{
	Game_Grid best_Grid = G;
	float i = MaxValue(G, player1, player2, best_Grid);
	return best_Grid;
}