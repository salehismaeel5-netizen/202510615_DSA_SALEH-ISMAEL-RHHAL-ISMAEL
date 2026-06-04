#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void openHistoryFile();
void openConceptsFile();

int main() {
    int selection;

    do {
        cout << "\n--- FOUNDATIONS AND HISTORY OF C++ ---" << endl;
        cout << "1. View History of C++" << endl;
        cout << "2. Learn C++ Core Concepts" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your selection: ";
        cin >> selection;

        switch (selection) {
            case 1:
                openHistoryFile();
                break;
            case 2:
                openConceptsFile();
                break;
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid selection! Please enter 1, 2, or 3." << endl;
        }
    } while (selection != 3);

    return 0;
}

void openHistoryFile() {
    ifstream targetFile("history.txt");
    string fileLine;

    cout << "\n[Reading history.txt Content]" << endl;
    if (targetFile.is_open()) {
        while (getline(targetFile, fileLine)) {
            cout << fileLine << endl;
        }
        targetFile.close();
    } else {
        cout << "Notice: history.txt file could not be found!" << endl;
    }
}

void openConceptsFile() {
    ifstream targetFile("concepts.txt");
    string fileLine;

    cout << "\n[Reading concepts.txt Content]" << endl;
    if (targetFile.is_open()) {
        while (getline(targetFile, fileLine)) {
            cout << fileLine << endl;
        }
        targetFile.close();
    } else {
        cout << "Notice: concepts.txt file could not be found!" << endl;
    }
}