#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to check if username already exists
bool isUsernameTaken(const string& username) {
    ifstream file("users.txt");
    string line, savedUser, savedPass;

    while (getline(file, line)) {
        size_t delimiter = line.find(',');
        savedUser = line.substr(0, delimiter);

        if (savedUser == username) {
            return true;
        }
    }

    return false;
}

// Function to register a new user
void registerUser() {
    string username, password;

    cout << "\n=== Register ===\n";
    cout << "Enter username: ";
    cin >> username;

    if (isUsernameTaken(username)) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << "," << password << endl;
    file.close();

    cout << "Registration successful!\n";
}

// Function to login user
void loginUser() {
    string username, password;
    cout << "\n=== Login ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string line, savedUser, savedPass;
    bool loginSuccess = false;

    while (getline(file, line)) {
        size_t delimiter = line.find(',');
        savedUser = line.substr(0, delimiter);
        savedPass = line.substr(delimiter + 1);

        if (savedUser == username && savedPass == password) {
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        cout << "Login successful. Welcome, " << username << "!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n=== Login & Registration System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
