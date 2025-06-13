#include "List.h"

// Function to read one line from the CSV file and turn it into a Pokemon
Pokemon parseOneLine(const string& line) {
    Pokemon p;  // Create a new Pokemon (starts with default values)

    // Use stringstream to split the line at commas
    stringstream ss(line);
    string piece;
    int fieldNumber = 0;

    // Read each piece separated by commas
    while (getline(ss, piece, ',')) {
        // Figure out which field this piece belongs to
        if (fieldNumber == 0) {
            // Field 0 is the ID number - we don't need to store this
        } else if (fieldNumber == 1) {
            p.name = piece;
        } else if (fieldNumber == 2) {
            p.type1 = piece;
        } else if (fieldNumber == 3) {
            p.type2 = piece;  // This might be empty for single-type Pokemon
        } else if (fieldNumber == 4) {
            p.hp = stoi(piece);  // stoi converts string to integer
        } else if (fieldNumber == 5) {
            p.attack = stoi(piece);
        } else if (fieldNumber == 6) {
            p.defense = stoi(piece);
        } else if (fieldNumber == 7) {
            p.special_attack = stoi(piece);
        } else if (fieldNumber == 8) {
            p.special_defense = stoi(piece);
        } else if (fieldNumber == 9) {
            p.speed = stoi(piece);
        } else if (fieldNumber == 10) {
            p.total = stoi(piece);
        }
        fieldNumber++;
    }

    return p;
}

// Function to save Pokemon to a CSV file
void savePokemonToFile(const vector<Pokemon>& pokemonList, const string& filename) {
    // Try to create/open the file for writing
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Could not create the file " << filename << endl;
        return;
    }

    // Write the header line first
    file << "name,type_1,type_2,hp,attack,defense,special_attack,special_defense,speed,total" << endl;

    // Write each Pokemon as a line in the file
    for (int i = 0; i < pokemonList.size(); i++) {
        const Pokemon& p = pokemonList[i];
        file << p.name << "," << p.type1 << "," << p.type2 << ","
             << p.hp << "," << p.attack << "," << p.defense << ","
             << p.special_attack << "," << p.special_defense << ","
             << p.speed << "," << p.total << endl;
    }

    file.close();
    cout << "SUCCESS: Saved " << pokemonList.size() << " Pokemon to " << filename << endl;
}

// Function to get user's choice for search type
int getUserChoice() {
    int choice;

    cout << "\n===========================================" << endl;
    cout << "What kind of search do you want to do?" << endl;
    cout << "1. Find Pokemon with stats LESS than or equal to a number" << endl;
    cout << "2. Find Pokemon with stats GREATER than or equal to a number" << endl;
    cout << "3. Find Pokemon with stats EXACTLY equal to a number" << endl;
    cout << "===========================================" << endl;
    cout << "Enter your choice (1, 2, or 3): ";

    // Keep asking until we get a valid choice
    while (true) {
        cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3) {
            break;  // Valid choice - exit the loop
        } else {
            cout << "Please enter 1, 2, or 3: ";
        }
    }

    return choice;
}

// Function to get the number from the user
int getNumberFromUser(const string& description) {
    int number;
    cout << "Enter the " << description << " value: ";
    cin >> number;
    return number;
}

// Function to let the user delete Pokemon from the list
void letUserDeletePokemon(PokemonList& list) {
    if (list.isEmpty()) {
        cout << "The list is empty - nothing to delete!" << endl;
        return;
    }

    string answer;
    cout << "\nDo you want to delete any Pokemon from this list? (yes/no): ";
    cin >> answer;

    if (answer != "yes" && answer != "y" && answer != "Yes" && answer != "Y") {
        cout << "Okay, keeping all Pokemon in the list." << endl;
        return;
    }

    // Clear the input buffer so getline works correctly
    cin.ignore();

    string pokemonName;
    while (true) {
        cout << "\n--- Current Pokemon List ---" << endl;
        list.printAll();

        cout << "\nEnter the name of a Pokemon to delete (or type 'done' to stop): ";
        getline(cin, pokemonName);

        if (pokemonName == "done" || pokemonName == "Done" || pokemonName == "DONE") {
            cout << "Finished deleting Pokemon." << endl;
            break;
        }

        bool wasDeleted = list.deleteByName(pokemonName);
        if (wasDeleted) {
            cout << "SUCCESS: Deleted " << pokemonName << " from the list." << endl;

            if (list.isEmpty()) {
                cout << "The list is now empty!" << endl;
                break;
            }
        } else {
            cout << "ERROR: Could not find '" << pokemonName << "' in the list." << endl;
            cout << "Make sure you type the name exactly as shown above." << endl;
        }
    }
}

// The main function - this is where the program starts
int main() {
    cout << "=========================================" << endl;
    cout << "    POKEMON STATISTICS ANALYZER" << endl;
    cout << "=========================================" << endl;
    cout << "Loading Pokemon data from file..." << endl;

    // Step 1: Try to open the CSV file
    ifstream file("pokemon_stats.csv");
    if (!file.is_open()) {
        cout << "ERROR: Could not find the file 'pokemon_stats.csv'" << endl;
        cout << "Make sure the file is in the same folder as this program." << endl;
        cout << "You can download it from:" << endl;
        cout << "https://tildegit.org/left_adjoint/cs162/raw/branch/main/assignment3/pokemon_stats.csv" << endl;
        return 1;  // Exit the program with an error code
    }

    // Step 2: Read all Pokemon from the file and put them in our tree
    PokemonTree tree;
    string line;
    int pokemonCount = 0;

    // Skip the first line (it's just the column headers)
    getline(file, line);

    // Read each line and turn it into a Pokemon
    while (getline(file, line)) {
        if (!line.empty()) {  // Make sure the line isn't blank
            try {
                Pokemon p = parseOneLine(line);
                tree.insert(p);  // Add the Pokemon to our tree
                pokemonCount++;
            } catch (...) {
                // If something goes wrong parsing this line, just skip it
                cout << "Warning: Skipped a line that couldn't be parsed." << endl;
            }
        }
    }
    file.close();

    cout << "SUCCESS: Loaded " << pokemonCount << " Pokemon into the tree!" << endl;
    cout << "The tree is sorted by: " << tree.getSortDescription() << endl;

    // Step 3: Let the user choose what kind of search they want
    int userChoice = getUserChoice();
    int searchValue = getNumberFromUser(tree.getSortDescription());

    // Step 4: Do the search and create a list of results
    PokemonList results;
    string searchDescription;

    if (userChoice == 1) {
        results = tree.findLessOrEqual(searchValue);
        searchDescription = "Pokemon with " + tree.getSortDescription() + " <= " + to_string(searchValue);
    } else if (userChoice == 2) {
        results = tree.findGreaterOrEqual(searchValue);
        searchDescription = "Pokemon with " + tree.getS