#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <limits>

#include "List.hpp"
#include "Command.hpp"
#include "Player.hpp"

using namespace std;

const int MAX_PLAYERS = 100;
Player players[MAX_PLAYERS];
int playerCount = 0;

void loadCommands(List<Command>& list) {
    ifstream file("commands.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open commands.csv\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cmd, desc, ptsStr;

        if (!getline(ss, cmd, ',')) continue;
        getline(ss, desc, ',');
        getline(ss, ptsStr, ',');

        int pts = 1;
        try {
            pts = stoi(ptsStr);
        }
        catch (...) {
            pts = 1;
        }

        list.insertAtFront(Command(cmd, desc, pts));
    }

    file.close();
}

void saveCommands(List<Command>& list) {
    ofstream file("commands.csv");
    Node<Command>* pCur = list.getpHead();
    while (pCur) {
        file << pCur->data.command << "," << pCur->data.description << "," << pCur->data.points << "\n";
        pCur = pCur->pNext;
    }
    file.close();
}

void loadPlayers() {
    ifstream file("profiles.csv");
    string line;
    playerCount = 0;

    while (getline(file, line) && playerCount < MAX_PLAYERS) {
        stringstream ss(line);
        string name, scoreStr;

        if (!getline(ss, name, ',') || !getline(ss, scoreStr, ',')) {
            continue;
        }

        try {
            players[playerCount++] = Player(name, stoi(scoreStr));
        }
        catch (...) {
            continue;
        }
    }

    file.close();
}

void savePlayers() {
    ofstream file("profiles.csv");
    for (int i = 0; i < playerCount; ++i) {
        file << players[i].name << "," << players[i].score << "\n";
    }
    file.close();
}

Player* findPlayer(const string& name) {
    for (int i = 0; i < playerCount; ++i) {
        if (players[i].name == name) return &players[i];
    }
    return nullptr;
}

void gameRules() {
    cout << "\n-- Game Rules --\n";
    cout << "You will be given Linux commands and must match them with the correct descriptions.\n";
    cout << "Each correct answer awards points; incorrect ones reduce your score.\n\n";
}

void playGame(Player* player, List<Command>& commandList, int questionCount) {
    vector<Command> pool;
    Node<Command>* pCur = commandList.getpHead();
    while (pCur) {
        pool.push_back(pCur->data);
        pCur = pCur->pNext;
    }

    if (pool.size() < 4) {
        cout << "Not enough commands to play.\n";
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    int correctCount = 0;

    for (int i = 0; i < questionCount; ++i) {
        random_shuffle(pool.begin(), pool.end());
        Command& correct = pool[0];

        vector<string> options = {
            pool[0].description,
            pool[1].description,
            pool[2].description,
            pool[3].description
        };

        random_shuffle(options.begin(), options.end());

        cout << "\nQ" << i + 1 << ": What does the command '" << correct.command << "' do?\n";
        for (int j = 0; j < 4; ++j)
            cout << j + 1 << ". " << options[j] << "\n";

        int ans;
        cout << "Your answer (1-4): ";
        cin >> ans;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ans < 1 || ans > 4) {
            cout << "Invalid answer. Skipped.\n";
            continue;
        }

        if (options[ans - 1] == correct.description) {
            cout << "Correct!\n";
            player->score += correct.points;
            correctCount++;
        }
        else {
            cout << "Wrong. Correct: " << correct.description << "\n";
            player->score -= 1;
        }
    }

    cout << "\nScore: " << player->score << " (" << correctCount << "/" << questionCount << " correct)\n";
}

void menu() {
    List<Command> commandList;
    loadCommands(commandList);
    loadPlayers();

    while (true) {
        cout << "\n--- Linux Command Matching Game ---\n";
        cout << "1. Game Rules\n";
        cout << "2. Play New Game\n";
        cout << "3. Load Previous Game\n";
        cout << "4. Add Command\n";
        cout << "5. Remove Command\n";
        cout << "6. Display All Commands\n";
        cout << "7. Save and Exit\n";
        cout << "Your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            gameRules();
        }
        else if (choice == 2) {
            string name;
            int num;
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "How many questions? ";
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Player* p = findPlayer(name);
            if (!p) {
                players[playerCount++] = Player(name);
                p = &players[playerCount - 1];
            }

            playGame(p, commandList, num);

        }
        else if (choice == 3) {
            string name;
            cout << "Enter your name: ";
            getline(cin, name);
            Player* p = findPlayer(name);
            if (p) {
                cout << "Welcome back, " << name << ". Score: " << p->score << "\n";
            }
            else {
                cout << "Player not found.\n";
            }

        }
        else if (choice == 4) {
            string cmd, desc;
            int pts;
            cout << "Enter command: ";
            getline(cin, cmd);
            cout << "Enter description: ";
            getline(cin, desc);
            cout << "Enter point value: ";
            cin >> pts;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (commandList.exists(cmd)) {
                cout << "Command already exists.\n";
            }
            else {
                commandList.insertAtFront(Command(cmd, desc, pts));
                cout << "Command added.\n";
            }

        }
        else if (choice == 5) {
            string cmd;
            cout << "Enter command to remove: ";
            getline(cin, cmd);
            if (commandList.removeNode(cmd)) {
                cout << "Removed successfully.\n";
            }
            else {
                cout << "Command not found.\n";
            }

        }
        else if (choice == 6) {
            commandList.displayAll();

        }
        else if (choice == 7) {
            saveCommands(commandList);
            savePlayers();
            cout << "Game saved. Bye!\n";
            break;

        }
        else {
            cout << "Invalid option.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
