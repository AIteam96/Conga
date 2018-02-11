#include<iostream>
#include<vector>
#include <utility>      // std::pair, std::make_pair
#include <fstream> 

#define Max 4
using namespace std;

struct Player {
	short int Wich_Player; //1 , 2
	short int Max_Depth;
	short int score;
};

struct Grid_Cell {
	struct Player player;
	short int Stone_Num;
	bool IsInUse; //true when the cell is already taken O.W flase
};

//Container 
struct Game_Grid {
	vector <vector<Grid_Cell> > Grid;
};

//create the gride and  
Game_Grid Initial() {
	vector<vector<Grid_Cell> > Grid(Max, vector<Grid_Cell>(Max));
	ofstream file;
	file.open("C:\\Users\\Lenovo\\Documents\\Visual Studio 2015\\Projects\\CongaGame\\CongaFile.txt");
	for (short int i = 0; i < Max; i++) {
		for (short int j = 0; j < Max; j++) {
			Grid[i][j].IsInUse = false;
			file << "E/0/0  ";
			Grid[i][j].Stone_Num = 0;
			Grid[i][j].player.Wich_Player = 0;
		}
		file << "\n";
	}
	file.close();
	Game_Grid G;
	G.Grid = Grid;
	return G;
}
void UpdateFile(Game_Grid G) {
	ofstream file;
	file.open("C:\\Users\\Lenovo\\Documents\\Visual Studio 2015\\Projects\\CongaGame\\CongaFile.txt");
	for (short int i = 0; i < Max; i++) {
		for (short int j = 0; j < Max; j++) {
			file << G.Grid[i][j].IsInUse << "/" << G.Grid[i][j].Stone_Num << "/" << G.Grid[i][j].player.Wich_Player;
		}
	}
}

float Heurestic1(Game_Grid G, Player player) {

	short int grid_way = 0;
	for (short int i = 0; i < Max; i++) {
		for (short int j = 0; j < Max; j++) {
			short int cell_way = 0;
			if (G.Grid[i][j].player.Wich_Player != player.Wich_Player) {
				//condition1
				if (j < 4) {
					if (!G.Grid[i][j + 1].IsInUse || !G.Grid[i][j + 1].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition2
				if (i < 4 && j < 4) {
					if (!G.Grid[i + 1][j + 1].IsInUse || !G.Grid[i + 1][j + 1].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition3
				if (i < 4) {
					if (!G.Grid[i + 1][j].IsInUse || !G.Grid[i + 1][j].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition4
				if (i < 4 && j > 1) {
					if (!G.Grid[i + 1][j - 1].IsInUse || !G.Grid[i + 1][j - 1].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition5
				if (j > 1) {
					if (!G.Grid[i][j - 1].IsInUse || !G.Grid[i][j - 1].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition6
				if (i > 1 && j > 0) {
					if (!G.Grid[i - 1][j - 1].IsInUse || !G.Grid[i - 1][j - 1].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition7
				if (i > 1) {
					if (!G.Grid[i - 1][j].IsInUse || !G.Grid[i - 1][j].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}
				//condition8
				if (i > 1 && j < 4) {
					if (!G.Grid[i - 1][j + 1].IsInUse || !G.Grid[i - 1][j + 1].player.Wich_Player != player.Wich_Player) { cell_way++; }
				}

			}
			grid_way = grid_way + cell_way;
		}
	}
	return (grid_way / 128);
}

float Heurestic2(Game_Grid G, Player player , pair<short int, short int> current_location) {
	short int stone = 0;
	//condition1
	if (current_location.second < 4) {
		if (G.Grid[current_location.first][current_location.second + 1].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first][current_location.second + 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first][current_location.second + 1].Stone_Num;
		}
	}
	//condition2
	if (current_location.first < 4 && current_location.second < 4) {
		if (G.Grid[current_location.first + 1][current_location.second + 1].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first + 1][current_location.second + 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first + 1][current_location.second + 1].Stone_Num;
		}
	}
	//condition3
	if (current_location.first < 4) {
		if (G.Grid[current_location.first + 1][current_location.second].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first + 1][current_location.second + 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first + 1][current_location.second + 1].Stone_Num;
		}
	}
	//condition4
	if (current_location.first < 4 && current_location.second > 1) {
		if (G.Grid[current_location.first + 1][current_location.second - 1].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first + 1][current_location.second - 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first + 1][current_location.second - 1].Stone_Num;
		}
	}
	//condition5
	if (current_location.second > 1) {
		if (G.Grid[current_location.first][current_location.second - 1].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first][current_location.second - 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first][current_location.second - 1].Stone_Num;
		}
	}
	//condition6
	if (current_location.first > 1 && current_location.second > 0) {
		if (G.Grid[current_location.first - 1][current_location.second - 1].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first - 1][current_location.second - 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first - 1][current_location.second - 1].Stone_Num;
		}
	}
	//condition7
	if (current_location.first > 1) {
		if (G.Grid[current_location.first - 1][current_location.second].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first - 1][current_location.second].Stone_Num >= stone) {
			stone = G.Grid[current_location.first - 1][current_location.second].Stone_Num;
		}
	}
	//condition8
	if (current_location.first > 1 && current_location.second < 4) {
		if (G.Grid[current_location.first - 1][current_location.second + 1].player.Wich_Player != player.Wich_Player &&
			G.Grid[current_location.first - 1][current_location.second + 1].Stone_Num >= stone) {
			stone = G.Grid[current_location.first - 1][current_location.second + 1].Stone_Num;
		}
	}
	return (stone / 10);

}
float HeuresticAverage(Game_Grid G, Player player, pair<short int, short int> current_location) {
	float h1 = Heurestic1(G, player);
	float h2 = Heurestic2(G, player, current_location);
	return (h1 + h2) / 2;
}
vector<Game_Grid> successor(Game_Grid G, Player Turn) {
	vector<Game_Grid> Grid_List;
	Game_Grid Temp = G;
	pair<short int, short int> Current;

	for (short int i = 0; i < Max; i++) {
		for (short int j = 0; j < Max; j++) {
			Current.first = i;
			Current.second = j;
			//condition1
			if (i > 1)
			{
				Temp = move(Turn, 1, Current, Temp);
				Grid_List.push_back(Temp);
			}
			//condition2
			if (i > 1 && j > 1)
			{
				Temp = move(Turn, 2, Current, Temp);
				Grid_List.push_back(Temp);
			}
			////condition3
			if (j > 1)
			{
				Temp = move(Turn, 3, Current, Temp);
				Grid_List.push_back(Temp);
			}
			//condition4
			if (i < Max && j < Max)
			{
				move(Turn, 4, Current, Temp);
				Grid_List.push_back(Temp);
			}
			//condition5
			if (i < Max)
			{
				Temp = move(Turn, 5, Current, Temp);
				Grid_List.push_back(Temp);
			}
			//condition6
			if (i < Max && j > 1)
			{
				Temp = move(Turn, 6, Current, Temp);
				Grid_List.push_back(Temp);
			}
			//condition7
			if (j < Max)
			{
				Temp = move(Turn, 7, Current, Temp);
				Grid_List.push_back(Temp);
			}
			//condition8
			if (i > 1 && j < Max)
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
	short int stonesCount = 1;
	short int allStones = G.Grid[current_location.first][current_location.second].Stone_Num;

	while (0 <= current_location.first <= 4 && 0 <= current_location.second <= 4 && (!G.Grid[current_location.first][current_location.second].IsInUse || G.Grid[current_location.first][current_location.second].player.Wich_Player == Turn.Wich_Player))

		while (0 < next_step.first <= 4 && 0 < next_step.second <= 4 && !G.Grid[next_step.first][next_step.second].IsInUse || G.Grid[next_step.first][next_step.second].player.Wich_Player == Turn.Wich_Player)

		{
			switch (direction)
			{
			case 1:
				next_step.first = current_location.first;
				next_step.second = current_location.second + 1;
				UpdateFile(G);
				break;
			case 2:
				next_step.first = current_location.first + 1;
				next_step.second = current_location.second + 1;
				UpdateFile(G);
				break;
			case 3:
				next_step.first = current_location.first + 1;
				next_step.second = current_location.second;
				UpdateFile(G);
				break;
			case 4:
				next_step.first = current_location.first + 1;
				next_step.second = current_location.second - 1;
				UpdateFile(G);
				break;
			case 5:
				next_step.first = current_location.first;
				next_step.second = current_location.second - 1;
				UpdateFile(G);
				break;
			case 6:
				next_step.first = current_location.first - 1;
				next_step.second = current_location.second - 1;
				UpdateFile(G);
				break;
			case 7:
				next_step.first = current_location.first - 1;
				next_step.second = current_location.second;
				UpdateFile(G);
				break;
			case 8:
				next_step.first = current_location.first - 1;
				next_step.second = current_location.second + 1;
				UpdateFile(G);
				break;
			}
			if (0 <= next_step.first <= 4 && 0 <= next_step.second <= 4 && !G.Grid[next_step.first][next_step.second].IsInUse)
			{
				G.Grid[current_location.first][current_location.second].Stone_Num = stonesCount;
				stonesCount++;
				G.Grid[next_step.first][next_step.second].IsInUse = true;
				G.Grid[next_step.first][next_step.second].player = Turn;
				current_location = next_step;
			}
			else
			{
				G.Grid[current_location.first][current_location.second].Stone_Num = allStones - stonesCount - 1;
				G.Grid[next_step.first][next_step.second].IsInUse = true;
				G.Grid[next_step.first][next_step.second].player = Turn;
				current_location = next_step;
			}
		}

	return G;
}

bool Terminal(Game_Grid G, Player player)
{
	for (short int i = 1; i <= 4; i++)
	{
		for (short int j = 1; j <= 4; j++)
		{
			short int way = 8;
			if (G.Grid[i][j].player.Wich_Player == player.Wich_Player)
			{
				if ((i == 1 && j == 1) || (i == 1 && j == 4) || (i == 4 && j == 1) || (i == 4 && j == 4))
				{
					way = 3;
				}
				if ((i == 1 && 2 <= j <= 3) || (i == 4 && 2 <= j <= 3) || (2 <= i <= 3 && j == 1) || (2 <= i <= 3 && j == 4))
				{
					way = 5;
				}
				if (j > 1)
				{
					if (G.Grid[i][j + 1].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i][j + 1].IsInUse == true)
						way--;
				}
				if (j < 4)
				{
					if (G.Grid[i][j - 1].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i][j - 1].IsInUse == true)
						way--;
				}
				if (i > 1)
				{
					if (G.Grid[i - 1][j].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i - 1][j].IsInUse == true)
						way--;
					if (j > 1)
					{
						if (G.Grid[i - 1][j + 1].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i - 1][j + 1].IsInUse == true)
							way--;
					}
					if (j < 4)
					{
						if (G.Grid[i - 1][j - 1].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i - 1][j - 1].IsInUse == true)
							way--;
					}
				}
				if (i < 4)
				{
					if (G.Grid[i + 1][j].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i + 1][j].IsInUse == true)
						way--;
					if (j > 1)
					{
						if (G.Grid[i + 1][j + 1].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i + 1][j + 1].IsInUse == true)
							way--;
					}
					if (j < 4)
					{
						if (G.Grid[i + 1][j - 1].player.Wich_Player != G.Grid[i][j].player.Wich_Player || G.Grid[i + 1][j - 1].IsInUse == true)
							way--;
					}
				}
			}
			if (way > 0)
				return false;
		}
	}
	player.score = -1;
	return true;
}
float MaxValue(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid)
{
	if (!Terminal(G, maxplayer)) {
		vector<Game_Grid> actions = successor(G, maxplayer);
		float resultVlue = -2.00;
		int i = 0;
		while (!actions.empty())
		{
			Game_Grid current_State = actions[i]; i++;
			float currentRating = MinValue(G, maxplayer, minplayer, current_State);
			if (currentRating > resultVlue)
			{
				resultVlue = currentRating;
				best_Grid = current_State;
			}
		}
		return resultVlue;
	}
	else
	{
		minplayer.score = 1;
		return maxplayer.score;
	}
}
float MinValue(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid)
{
	if (!Terminal(G, minplayer)) {
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
	}
	else
	{
		maxplayer.score = 1;
		return minplayer.score;
	}

}
Game_Grid minimax(Game_Grid G, Player player1, Player player2)
{
	Game_Grid best_Grid = G;
	float i = MaxValue(G, player1, player2, best_Grid);
	return best_Grid;
}
float max(float a, float b)
{
	a > b ? a : b;
}
float min(float a, float b)
{
	a > b ? b : a;
}
float MaxValue_Pruning(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid, float alpha, float beta)
{
	if (!Terminal(G, maxplayer)) {
		vector<Game_Grid> actions = successor(G, maxplayer);
		float resultVlue = -2.00;
		int i = 0;
		while (!actions.empty())
		{
			Game_Grid current_State = actions[i]; i++;
			float currentRating = MinValue_Pruning(G, maxplayer, minplayer, current_State, alpha, beta);
			if (currentRating > resultVlue)
			{
				resultVlue = currentRating;
				best_Grid = current_State;
			}
			if (resultVlue >= beta)
				return resultVlue;
			alpha = max(alpha, resultVlue);
		}
		return resultVlue;
	}
	else
	{
		minplayer.score = 1;
		return maxplayer.score;
	}
}
float MinValue_Pruning(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid, float alpha, float beta)
{
	if (!Terminal(G, minplayer)) {
		vector<Game_Grid> actions = successor(G, minplayer);
		float resultVlue = +2.00;
		int i = 0;
		while (!actions.empty())
		{
			Game_Grid current_State = actions[i]; i++;
			float currentRating = MaxValue_Pruning(G, maxplayer, minplayer, current_State, alpha, beta);
			if (currentRating < resultVlue)
			{
				resultVlue = currentRating;
				best_Grid = current_State;
			}
			if (resultVlue >= alpha)
				return resultVlue;
			beta = min(beta, resultVlue);
		}
		return resultVlue;
	}
	else
	{
		maxplayer.score = 1;
		return minplayer.score;
	}
}
Game_Grid minimax_pruning(Game_Grid G, Player player1, Player player2)
{
	Game_Grid best_Grid = G;
	float i = MaxValue_Pruning(G, player1, player2, best_Grid, -2.00, 2.00);
	return best_Grid;
}

float MaxValue_Pruning_depth(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid, float alpha, float beta)
{
	if (!Terminal(G, maxplayer)) {
		maxplayer.Max_Depth--;
		vector<Game_Grid> actions = successor(G, maxplayer);
		float resultVlue = -2.00;
		int i = 0;
		while (!actions.empty())
		{
			Game_Grid current_State = actions[i]; i++;
			float currentRating = MinValue_Pruning_depth(G, maxplayer, minplayer, current_State, alpha, beta);
			if (currentRating > resultVlue)
			{
				resultVlue = currentRating;
				best_Grid = current_State;
			}
			if (resultVlue >= beta)
				return resultVlue;
			alpha = max(alpha, resultVlue);
		}
		return resultVlue;
	}
	else
	{
		minplayer.score = 1;
		return maxplayer.score;
	}

}
float MinValue_Pruning_depth(Game_Grid G, Player maxplayer, Player minplayer, Game_Grid &best_Grid, float alpha, float beta)
{
	if (!Terminal(G, minplayer)) {
		if (minplayer.Max_Depth == 0)
		{
			int i = 0;
			vector<Game_Grid> actions = successor(G, minplayer);
			while (!actions.empty())
			{
				best_Grid = actions[i]; i++;

				return Heurestic1(best_Grid, minplayer);
			}
		}
		minplayer.Max_Depth--;
		vector<Game_Grid> actions = successor(G, minplayer);
		float resultVlue = +2.00;
		int i = 0;
		while (!actions.empty())
		{
			Game_Grid current_State = actions[i]; i++;
			float currentRating = MaxValue_Pruning_depth(G, maxplayer, minplayer, current_State, alpha, beta);
			if (currentRating < resultVlue)
			{
				resultVlue = currentRating;
				best_Grid = current_State;
			}
			if (resultVlue >= alpha)
				return resultVlue;
			beta = min(beta, resultVlue);
		}
		return resultVlue;
	}
	else
	{
		maxplayer.score = 1;
		return minplayer.score;
	}
}
Game_Grid minimax_pruning_depth(Game_Grid G, Player player1, Player player2, int depth)
{
	Game_Grid best_Grid = G;
	player1.Max_Depth = depth;
	player2.Max_Depth = depth;
	float i = MaxValue_Pruning_depth(G, player1, player2, best_Grid, -2.00, 2.00);
	return best_Grid;

}