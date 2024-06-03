#include <iostream>
#include <cstdlib>

using namespace std;


enum enGameChoice{Stone = 1, Paper = 2, Scissors = 3};
enum enWinner{Player = 1, Computer = 2,Draw = 3};


struct stRound_Info {
	short Round_Number = 0;
	enGameChoice Player_Choice;
	enGameChoice Computer_Choice;
	enWinner Round_Winner;
	string Round_Winner_Name = "";
};


struct stGame_Result {
	short Game_Rounds = 0;
	short Player_WinTimes = 0;
	short Computer_WinTimes = 0;
	short DrawTimes = 0;
	enWinner Game_Winner;
	string Game_Winner_Name = "";
};



short HowManyRounds() {

	short GameRounds = 1;

	do
	{
		cout << "How Many Rounds ? (1 => 10) \n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}



short Random_Number(short From, short To) {
	return rand() % (To - From + 1) + From;
}


enGameChoice Get_ComputerChoice() {
	return (enGameChoice)Random_Number(1, 3);
}


enGameChoice Read_PlayerChoice() {

	short Choice = 1;

	do
	{
		cout << "\nUr Choice : [1]:Stone , [2]:Paper , [3]:Scissors  ? \n";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}


string Choice_Name(enGameChoice GameChoice) {
	string arr_GameChoice_Name[3] = { "Stone","Paper","Scissors" };

	return arr_GameChoice_Name[GameChoice - 1];
}



enWinner Who_Won_TheRound(stRound_Info Round_Info) {

	if (Round_Info.Player_Choice == Round_Info.Computer_Choice)
		return enWinner::Draw;

	switch (Round_Info.Player_Choice)
	{
	case enGameChoice::Stone:
		if (Round_Info.Computer_Choice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (Round_Info.Computer_Choice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (Round_Info.Computer_Choice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;
}


string Winner_Name(enWinner Winner) {
	string arr_WinnerName[3] = { "Player","Computer","No Winner" };

	return arr_WinnerName[Winner - 1];
}




void set_Winner_ScreenColor(enWinner Winner) {

	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");  
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}
}



void Print_RoundsResult(stRound_Info Round_Info) {

	cout << "__________________ Round [" << Round_Info.Round_Number << "] __________________\n\n";
	cout << "Player Choice    : " << Choice_Name(Round_Info.Player_Choice) << endl;
	cout << "Computer Choice  : " << Choice_Name(Round_Info.Computer_Choice) << endl;
	cout << "Round Winner     : [ " << Winner_Name(Round_Info.Round_Winner) << " ]" << endl;
	cout << "_______________________________________________________________________________\n\n";

	set_Winner_ScreenColor(Round_Info.Round_Winner);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


string Tabs(short NumberOfTabs) {

	string t = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		t += "\t";
		cout << t;
	}
	return t;
}


void ShowGameOverScreen() {

	cout << Tabs(2) << "___________________________________________________________\n\n";
	cout << Tabs(2) << "                     ++ Game Over ++                       \n\n";
	cout << Tabs(2) << "___________________________________________________________\n\n";
}


void ShowFinalGameResult(stGame_Result Game_Result) {

	cout << Tabs(2) << "_______________________[Game Result]_______________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << Game_Result.Game_Rounds << endl;
	cout << Tabs(2) << "Player Won Times   : " << Game_Result.Player_WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times : " << Game_Result.Computer_WinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << Game_Result.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << Game_Result.Game_Winner_Name << endl;

	cout << Tabs(2) << "___________________________________________________________\n\n";

	set_Winner_ScreenColor(Game_Result.Game_Winner);
}


void Reset_Screen() {
	system("cls");
	system("color 0F");
}




enWinner Who_Won_TheGame(short PlayerWinTimes, short ComputerWinTimes) {

	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}



stGame_Result Fill_GameResult(short Game_Rounds, short Player_WinTimes, short Computer_WinTimes, short DrawTimes) {

	stGame_Result Game_Result;

	Game_Result.Game_Rounds = Game_Rounds;
	Game_Result.Player_WinTimes = Player_WinTimes;
	Game_Result.Computer_WinTimes = Computer_WinTimes;
	Game_Result.DrawTimes = DrawTimes;

	Game_Result.Game_Winner = Who_Won_TheGame(Player_WinTimes, Computer_WinTimes);
	Game_Result.Game_Winner_Name = Winner_Name(Game_Result.Game_Winner);

	return Game_Result;
}


/////////////////////////////////////////////////////////////////////////////////////////


stGame_Result Play_Game(short HowManyRounds) {

	stRound_Info Round_Info;

	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins : \n";
		Round_Info.Round_Number = GameRound;
		Round_Info.Player_Choice = Read_PlayerChoice();
		Round_Info.Computer_Choice = Get_ComputerChoice();
		Round_Info.Round_Winner = Who_Won_TheRound(Round_Info);
		Round_Info.Round_Winner_Name = Winner_Name(Round_Info.Round_Winner);


		Print_RoundsResult(Round_Info);



		if (Round_Info.Round_Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (Round_Info.Round_Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
	}

	return Fill_GameResult(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}




void StartGame() {

	char Pass = 'Y';

	do
	{
		Reset_Screen();

		stGame_Result GameResult = Play_Game(HowManyRounds());

		ShowGameOverScreen();
		ShowFinalGameResult(GameResult);

		cout << endl << Tabs(3) << "Do U Want To Play Again ? (Y/N)";
		cin >> Pass;


	} while (Pass == 'Y' || Pass == 'y');
}



int main()
{
	srand((unsigned)time(NULL));


	StartGame();



	system("pause>0");
    return 0;
}