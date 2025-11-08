#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

using namespace std;

class Grid {
private:
    char** grid;
    int size;

public:
    Grid(int n = 0) : size(n) {
    if (size <= 0) {
        throw std::invalid_argument("Error: Grid size must be a positive integer.");
    }
        grid = new char*[size];
        for (int i = 0; i < size; ++i) {
            grid[i] = new char[size];
            for (int j = 0; j < size; ++j) {
                grid[i][j] = ' ';
            }
        }
    }

    // Fill the grid in a diamond pattern
    void fillGrid(string message) {
        int row = size / 2; 
        int col = 0;
        int left_limit_col = 0;
        int right_limit_col = size - 1;
        int upper_limit_row = 0;
        int lower_limit_row = size - 1;
        int index = 0;
        bool upright = true, downright = false, downleft = false, upleft = false;

        while (index < message.length()) {
            if (grid[row][col] == ' ') {
                grid[row][col] = message[index++];
            }

            if (upright) {
                // Move diagonally up-right
                if (row > upper_limit_row && col < right_limit_col) {
                    row--;
                    col++;
                } else {
                    // Change direction to downward-right
                    upper_limit_row ++;
                    upright = false;
                    downright = true;
                    if (col == right_limit_col) {
                        row++;
                    }
                }
            } else if (downright) {
                // Move diagonally down-right
                if (row < right_limit_col && col < right_limit_col) {
                    row++;
                    col++;
                } else {
                    // Change direction to downward-left
                    right_limit_col --;
                    downright = false;
                    downleft = true;
                    if (row == lower_limit_row) {
                        col--;
                    }
                }
            } else if (downleft) {
                // Move diagonally down-left
                if (row < lower_limit_row && col > left_limit_col) {
                    row++;
                    col--;
                } else {
                    // Change direction to up-left
                    lower_limit_row --;
                    downleft = false;
                    upleft = true;
                    if (col == left_limit_col) {
                        row--;
                    }
                }
            } else if (upleft) {
                // Move diagonally up-left
                if (row > upper_limit_row && col > left_limit_col) {
                    row--;
                    col--;
                } else {
                    // Change direction to up-right
                    upleft = false;
                    upright = true;
                    if (col == left_limit_col) {
                        col++;
                        left_limit_col++;
                    
                    }
                }
            }
        }

        // Fill remaining empty spaces with random characters
        srand(time(0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = 'A' + rand() % 26;
                }
            }
        }
    }

    string decode(const vector<vector<char>>& grid) {
    string decodedMessage = "";
    int size = grid.size();
    int row = size / 2; // Start from the middle row
    int col = 0;
    int left_limit_col = 0;
    int right_limit_col = size - 1;
    int upper_limit_row = 0;
    int lower_limit_row = size - 1;
    int index = 0;
    bool upright = true, downright = false, downleft = false, upleft = false;

    vector<vector<bool>> visited(size, vector<bool>(size, false));

        while (index < size * size) {
        if (!visited[row][col]) {
            decodedMessage += grid[row][col];
            visited[row][col] = true;
        }
            if (upright) {
                // Move diagonally up-right
                if (row > upper_limit_row && col < right_limit_col) {
                    row--;
                    col++;
                } else {
                    // Change direction to downward-right
                    upper_limit_row++;
                    upright = false;
                    downright = true;
                    if (col == right_limit_col) {
                        row++;
                    }
                }
            } else if (downright) {
                // Move diagonally down-right
                if (row < lower_limit_row && col < right_limit_col) {
                    row++;
                    col++;
                } else {
                    // Change direction to downward-left
                    right_limit_col--;
                    downright = false;
                    downleft = true;
                    if (row == lower_limit_row) {
                        col--;
                    }
                }
            } else if (downleft) {
                // Move diagonally down-left
                if (row < lower_limit_row && col > left_limit_col) {
                    row++;
                    col--;
                } else {
                    // Change direction to up-left
                    lower_limit_row--;
                    downleft = false;
                    upleft = true;
                    if (col == left_limit_col) {
                        row--;
                    }
                }
            } else if (upleft) {
                // Move diagonally up-left
                if (row > upper_limit_row && col > left_limit_col) {
                    row--;
                    col--;
                } else {
                    // Change direction to up-right
                    upleft = false;
                    upright = true;
                    if (col == left_limit_col) {
                        col++;
                        left_limit_col++;
                    }
                }
            }

             if (row == size / 2 && col == size/2) {
                decodedMessage += grid[row][col];
                 break;
             }

            index++;
        }

    return decodedMessage;
}

    void printGrid() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << (grid[i][j] == ' ' ? "  " : string(1, grid[i][j]) + " ");
            }
            cout << endl;
        }
    }

    ~Grid() {
        for (int i = 0; i < size; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    vector<vector<char>> getEncodedGrid() const {
        vector<vector<char>> encodedgrid;
        for (int i = 0; i < size; ++i) {
            encodedgrid.push_back(vector<char>(grid[i], grid[i] + size));
        }
        return encodedgrid;
    }

};
vector<vector<char>> createGrid(const std::string& input) {
    int length = input.length();
    int rows = std::sqrt(length);
    int cols = length / rows;

    if (rows * cols < length) {
        rows++;
    }

    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < length) {
                grid[i][j] = input[index++];
            }
        }
    }
    for (const auto& row : grid) {
        for (char ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }

    return grid;
    
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int user_input;
    string user_message_option_1;
    string user_message_option_2;
    string encodedmessage;
    string decodedmessage;
    vector<vector<char>> encodedGrid;

    do {
        cout << "***************************************************\n"
                "* 1, Enter a message                              *\n"
                "* 2, Load a message from a file                   *\n"
                "* 3, Encode a message                             *\n"
                "* 4, Decode a message                             *\n"
                "* 5, Save the message & decoded message to a file *\n"
                "* 6, Quit                                         *\n"
                "***************************************************\n";
        cout << "Enter your choice (1-6): ";
        cin >> user_input;
        
        clearInputBuffer();

        switch (user_input) {
            case 1: {
                cout << "You selected: Enter a message\n";
                do {
                    cout << "What is your message: ";
                    getline(cin, user_message_option_1);
                    if (user_message_option_1.empty()) {
                        cout << "Message cannot be empty. Please enter a message.\n";
                    }
                } while (user_message_option_1.empty());
                cout << "Your message is: " << user_message_option_1 << endl;
                break;
            
            }
            case 2: {
                int user_input2;
                cout << "You selected: Load a message from a file\n";
                cout << "********************************************************\n"
                        "* 1, Enter a file name                                 *\n"
                        "* 2, Use default file name                             *\n"
                        "********************************************************\n";
                cout << "Enter your choice (1-2): ";
                cin >> user_input2;

                string filename;
                if (user_input2 == 1) {
                    cout << "Enter the file name: ";
                    cin >> filename;
                } else if (user_input2 == 2) {
                    filename = "/Users/peterlewis/Desktop/VSCODE/C++/Assignment/TEST FILES/defaultfile";
                } else {
                    cout << "Invalid choice." << endl;
                    break;
                }

                ifstream infile(filename);
                if (!infile) {
                    cout << "Error opening file." << endl;
                    break;
                }
                getline(infile, user_message_option_2);
                infile.close();

                cout << "Loaded message: " << user_message_option_2 << endl;
                break;
            }

case 3: {
                cout << "You selected: Encode a message\n";
                cout << "Enter a message to encode: ";
                getline(cin, encodedmessage);

                string modifiedMessage;
                for (char c : encodedmessage) {
                    if (c != ' ') {
                        modifiedMessage += toupper(c);
                    }
                }

                int user_selection;
                int size;
                cout << "***************************************************\n"
                        "* 1, Select size of Grid                          *\n"
                        "* 2, Use default Grid size                        *\n"
                        "***************************************************\n";
                cout << "Enter your choice (1-2): ";
                cin >> user_selection;

                if (user_selection == 1) {
                    while (true) {
                        cout << "Enter size of grid: ";
                        if (!(cin >> size)) {
                            cout << "Invalid input. Please enter a valid integer.\n";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else if (size < ceil(sqrt(modifiedMessage.length() * 2 - 1))) {
                            cout << "Grid size is too small, enter a bigger size.\n";
                        } else {
                            break;
                        }
                    }
                } else {
                    size = ceil(sqrt(modifiedMessage.length() * 2 - 1));
                    size = size % 2 == 0 ? size + 1 : size; 
                }

                Grid grid(size);
                grid.fillGrid(modifiedMessage);
                grid.printGrid();
                encodedGrid = grid.getEncodedGrid();

                break;
            }
                case 4: {
                    int user_input4;
                    cout << "You selected: Decode a message\n";
                    cout << "********************************************************\n"
                        << "* 1, Decode saved message - from option 1              *\n"
                        << "* 2, Decode saved message from file - from option 2    *\n"
                        << "* 3, Decode encoded message - from option 3            *\n"
                        << "********************************************************\n";
                    cout << "Enter your choice (1-3): ";
                    cin >> user_input4;
                    cin.ignore();

                    string message_to_decode;
                    vector<vector<char>> grid;

                    switch (user_input4) {
                        case 1:
                            message_to_decode = user_message_option_1;
                            decodedmessage = user_message_option_1;
                            {
                                string noSpacesMessage;
                                for (char c : message_to_decode) {
                                    if (c != ' ') {
                                        noSpacesMessage += toupper(c);
                                    }
                                }
                                grid = createGrid(noSpacesMessage);
                            }
                            break;
                        case 2:
                            message_to_decode = user_message_option_2;
                            decodedmessage = user_message_option_2;
                            {
                                string noSpacesMessage;
                                for (char c : message_to_decode) {
                                    if (c != ' ') {
                                        noSpacesMessage += toupper(c);
                                    }
                                }
                                grid = createGrid(noSpacesMessage);
                            }
                            break;
                        case 3:
                            grid = encodedGrid; 
                            decodedmessage = encodedmessage;
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            continue;
                    }

                    if (!grid.empty() && (grid.size() % 2 != 0)) {
                        Grid gridObj(grid.size());
                        string decodedMessage = gridObj.decode(grid);
                        cout << "Decoded message: " << decodedMessage << endl;
                    } else {
                        cout << "The grid is empty or the length of the encoded message is not a square of an odd integer. Cannot decode the message." << endl;
                    }
                    break;
                }

                case 5: {
                    int user_input5;
                    int user_input5_2;
                    cout << "You selected: Save the message to a file\n";
                    cout << "********************************************************\n"
                            "* 1, Save message and encoded message                  *\n"
                            "* 2, Save message and decoded message                  *\n"
                            "********************************************************\n";
                    cout << "Enter your choice (1-2): ";
                    cin >> user_input5;
                    clearInputBuffer();

                    if (user_input5 != 1 && user_input5 != 2) {
                        cout << "Invalid choice." << endl;
                        break;
                    }

                    cout << "********************************************************\n"
                            "* 1, Enter a file name                                 *\n"
                            "* 2, Use default file name                             *\n"
                            "********************************************************\n";
                    cout << "Enter your choice (1-2): ";
                    cin >> user_input5_2;
                    clearInputBuffer();

                    string filename;
                    if (user_input5_2 == 1) {
                    cout << "Enter the file name: ";
                    getline(cin, filename);
                    if (filename.empty()) {
                        cout << "Error: File name cannot be empty." << endl;
                        break;
                    }
                    } else if (user_input5_2 == 2) {
                        filename = "defaultfile2.txt";
                    } else {
                        cout << "Invalid choice." << endl;
                        break;
                    }

                    ofstream outfile(filename);
                    if (!outfile) {
                        cout << "Error opening file." << endl;
                        break;
                    }

                    if (user_input5 == 1) {
                        outfile << "Message: " << encodedmessage << endl;
                        outfile << "Encoded Message: " << endl;
                        for (const auto& row : encodedGrid) {
                            for (const char& ch : row) {
                                outfile << ch << " ";
                            }
                            outfile << endl;
                        }
                    } else if (user_input5 == 2) {
                        string decodedMessage;
                        if (!encodedGrid.empty()) {
                            Grid gridObj(encodedGrid.size());
                            decodedMessage = gridObj.decode(encodedGrid);
                        }
                        outfile << "Message: " << decodedMessage << endl;
                        outfile << "Decoded Message: " << decodedMessage << endl;
                    }

                    outfile.close();
                    cout << "Message saved to file: " << filename << endl;
                    break;
                }

        case 6: {
            cout << "Exiting the program...\n";
            break;
        }
        default:
            cout << "Invalid input. Please enter a number from 1 to 6.\n";
            break;
    }
} while (user_input != 6);

return 0;
}
