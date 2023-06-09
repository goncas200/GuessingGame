#include <iostream>
#include <filesystem>
#include <fstream>
#include "GetEnv.h"
#include "Random.h"

using namespace std;
using namespace filesystem;

int main() {
	Random random;
	string appdata = env("APPDATA");
	current_path(appdata);
	bool new_dir = true;
	try {
		current_path("GuessingGameScores2");
		new_dir = false;
	}
	catch (...) {
		system("mkdir GuessingGameScores2");
		current_path("GuessingGameScores2");
	}
	
	int score = 0;
	string name;
	fstream scorefile;
	if (new_dir) {
		scorefile.open("score.txt", ios::out);
		scorefile << "0";
		scorefile.close();
		scorefile.open("username.txt", ios::out);
		cout << "Define your username: ";
		getline(cin, name);
		scorefile << name;
		scorefile.close();
	}

	if (!new_dir) {
		string line;
		scorefile.open("score.txt", ios::in);
		while (getline(scorefile, line)) {
			score = stoi(line);
		}
		scorefile.close();
		scorefile.open("username.txt", ios::in);
		while (getline(scorefile, line)) {
			name = line;
		}
		scorefile.close();
	}

	cout << "Welcome to the game " << name << "\n\n";
start_loop:
	while (true) {
		bool first = true;
		char want_continue[10];
		cout << "Score: " << score << "\n";
		char c_guess[5];
		int guess;
		int num = random.getnum(99);
		bool win = false;
		for (int i = 0; i < 5; ++i) {
			cout << "Choose a number between 0 and 99: ";
			if (!first) {
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
			else first = false;
			scanf_s("%5s", c_guess);
			string s_guess = c_guess;
			if (s_guess == "") goto start_loop;
			for (char i : s_guess) {
				if (i != '1' and i != '2' and i != '3' and i != '4' and i != '5' and i != '6' and i != '7' and i != '8' and i != '9' and i != '0') {
					cout << "It must be an integer\n\n";
					goto start_loop;
				}
			}
			guess = stoi(s_guess);
			if (num < guess) {
				cout << "Too High!\n";
			}
			if (num > guess) {
				cout << "Too Low!\n";
			}
			if (num == guess) {
				cout << "You Won!!!\n";
				++score;
				win = true;
				break;
			}
		}
		if (win) {
			scorefile.open("score.txt", ios::out);
			scorefile << score;
			scorefile.close();
		} 
		else {
			cout << "You Lost!\n";
		}
		cout << "Do you want to continue? [Y/n]: ";
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		fgets(want_continue, 4, stdin);
		string s_want_continue = want_continue;
		if (s_want_continue == "n\n" or s_want_continue == "N\n") {
			return 0;
		}
	}
	return 1;
}