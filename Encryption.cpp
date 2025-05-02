#include <iostream>
#include <string>
using namespace std;

// Function to remove non-letter characters and convert to uppercase
string adjust_message(const string &msg) {
    string adjusted_message;
    for (char ch : msg) {
        if (isalpha(ch)) {
            adjusted_message += toupper(ch);
        }
    }
    return adjusted_message;
}

// Function to perform Route Cipher encryption with the specified path shape
string route_cipher_encryption(string message, int key) {
    // Adjust the input message
    string adjusted_message = adjust_message(message);

    // Calculate the number of rows in the matrix
    int number_of_rows = (adjusted_message.length() + key - 1) / key;

    // Create a 2D array to represent the matrix
    char matrix[number_of_rows][key];
    int index = 0;

    // Fill the matrix with the adjusted message
    for (int i = 0; i < number_of_rows; i++) {
        for (int j = 0; j < key; j++) {
            if (index < adjusted_message.length()) {
                matrix[i][j] = adjusted_message[index++];
            } else {
                matrix[i][j] = 'X'; // Fill empty cells with 'X'
            }
        }
    }

    // Read the matrix in the specified path shape to encrypt the message
    string encrypted_message;
    int start_row = 0; // Starting row index
    int end_row = number_of_rows - 1; // Ending row index
    int start_column = key - 1; // Starting column index
    int end_column = 0; // Ending column index

    while (start_row <= end_row && start_column >= end_column) {
        // Read from top to bottom
        for (int i = start_row; i <= end_row && start_column >= end_column; i++) {
            encrypted_message += matrix[i][start_column];
        }
        start_column--;

        // Read from right to left
        for (int j = start_column; j >= end_column && start_row <= end_row; j--) {
            encrypted_message += matrix[end_row][j];
        }
        end_row--;

        // Read from bottom to top
        for (int i = end_row; i >= start_row && start_column >= end_column; i--) {
            encrypted_message += matrix[i][end_column];
        }
        end_column++;

        // Read from left to right
        for (int j = end_column; j <= start_column && start_row <= end_row; j++) {
            encrypted_message += matrix[start_row][j];
        }
        start_row++;
    }

    return encrypted_message;
}

// Main function for user input and encryption
int main() {
    string message;
    string str_key;
    int key;

    // Input the secret message for encryption
    cout << "Enter the secret message you want to cipher: ";
    cin >> ws;
    getline(cin, message);

    // Input the encryption key
    cout << "Enter the key: ";
    // Validate the input
    while (true) {
        cin >> str_key;

        // Check if input is a positive integer and greater than 1
        if (str_key.find_first_not_of("0123456789") != string::npos || (key = stoi(str_key)) <= 1) {
            cout << "Invalid input. Please enter a positive integer number greater than 1." << endl;
            cout << "Enter the key: ";
            continue;
        }

        // Check if the key is less than or equal to half of the number of characters in the adjusted message
        string adjusted_message = adjust_message(message);
        if (key > adjusted_message.length() / 2) {
            cout << "Invalid input. The key must be less than or equal to half of the number of characters in the message." << endl;
            cout << "Enter the key: ";
            continue;
        }

        // Key successfully validated, ready to perform encryption
        break;
    }

    // Perform encryption and display the ciphered text
    string encrypted_message = route_cipher_encryption(message, key);
    cout << "Ciphered text: " << encrypted_message << endl;

    return 0;
}
