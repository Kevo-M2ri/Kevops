#include "Tree.h"
#include "List.h"

using namespace std;

// Function to parse a CSV line into Pokemon struct
Pokemon parsePokemonLine(const string& line) {
    Pokemon p;
    stringstream ss(line);
    string field;
    int fieldNum = 0;
    
    while (getline(ss, field, ',')) {
        switch (fieldNum) {
            case 0: /* id - skip */ break;
            case 1: p.name = field; break;
            case 2: p.type1 = field; break;
            case 3: p.type2 = field; break;
            case 4: p.hp = stoi(field); break;
            case 5: p.attack = stoi(field); break;
            case 6: p.defense = stoi(field); break;
            case 7: p.special_attack = stoi(field); break;
            case 8: p.special_defense = stoi(field); break;
            case 9: p.speed = stoi(field); break;
            case 10: p.total = stoi(field); break;
        }
        fieldNum++;
    }
    
    return p;
}

// Function to write results to CSV file
void writeToCSV(const vector<Pokemon>& pokemon, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not create output file: " << filename << endl;
        return;
    }
    
    // Write header
    file << "name,type_1,type_2,hp,attack,defense,special_attack,special_defense,speed,total\n";
    
    // Write pokemon data
    for (const Pokemon& p : pokemon) {
        file << p.name << "," << p.type1 << "," << p.type2 << ","
             << p.hp << "," << p.attack << "," << p.defense << ","
             << p.special_attack << "," << p.special_defense << ","
             << p.speed << "," << p.total << "\n";
    }
    
    file.close();
    cout << "\nResults successfully written to: " << filename << endl;
}

// Function to display menu and get user choice
int getUserChoice() {
    int choice;
    cout << "\n=== SEARCH CRITERIA ===" << endl;
    cout << "1. Values less than or equal to a threshold" << endl;
    cout << "2. Values greater than or equal to a threshold" << endl;
    cout << "3. Values equal to a specific value" << endl;
    cout << "Enter your choice (1-3): ";
    
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Invalid input. Please enter 1, 2, or 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    return choice;
}

// Function to get threshold value from user
int getThresholdValue(const string& criterion) {
    int value;
    cout << "Enter threshold value for " << criterion << ": ";
    
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    return value;
}

// Function to handle interactive deletion
void handleDeletion(PokemonList& list) {
    if (list.isEmpty()) {
        cout << "\nNo Pokemon to delete." << endl;
        return;
    }
    
    string deleteName;
    string choice;
    
    cout << "\n=== POKEMON DELETION ===" << endl;
    cout << "Would you like to delete any Pokemon? (y/n): ";
    cin >> choice;
    
    if (choice != "y" && choice != "Y" && choice != "yes" && choice != "Yes") {
        return;
    }
    
    cin.ignore(); // Clear the input buffer
    
    while (true) {
        cout << "\nCurrent Pokemon list:" << endl;
        list.printAll();
        
        cout << "\nEnter Pokemon name to delete (or 'done' to finish): ";
        getline(cin, deleteName);
        
        if (deleteName == "done" || deleteName == "Done" || deleteName == "DONE") {
            break;
        }
        
        if (list.deleteByName(deleteName)) {
            cout << "Successfully deleted: " << deleteName << endl;
            
            if (list.isEmpty()) {
                cout << "All Pokemon have been deleted!" << endl;
                break;
            }
        } else {
            cout << "Pokemon not found: " << deleteName << endl;
            cout << "Make sure to enter the exact name as shown in the list." << endl;
        }
    }
}

int main() {
    cout << "=== POKEMON STATISTICS ANALYZER ===" << endl;
    cout << "Loading Pokemon data..." << endl;
    
    // Read CSV file
    ifstream file("pokemon_stats.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open pokemon_stats.csv" << endl;
        cout << "Please make sure the file is in the current directory." << endl;
        cout << "You can download it from: https://tildegit.org/left_adjoint/cs162/raw/branch/main/assignment3/pokemon_stats.csv" << endl;
        return 1;
    }
    
    string line;
    getline(file, line); // Skip header line
    
    PokemonBST tree;
    int pokemonCount = 0;
    
    // Read and insert all Pokemon into the tree
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                Pokemon p = parsePokemonLine(line);
                tree.insert(p);
                pokemonCount++;
            } catch (const exception& e) {
                cout << "Warning: Error parsing line: " << line << endl;
            }
        }
    }
    file.close();
    
    cout << "Successfully loaded " << pokemonCount << " Pokemon!" << endl;
    cout << "Tree is sorted by: " << tree.getSortingCriterion() << endl;
    
    // Get user's search criteria
    int choice = getUserChoice();
    int threshold = getThresholdValue(tree.getSortingCriterion());
    
    // Perform filtering based on user choice
    PokemonList filteredList;
    string operationDescription;
    
    switch (choice) {
        case 1:
            filteredList = tree.filterLessThanOrEqual(threshold);
            operationDescription = "Pokemon with " + tree.getSortingCriterion() + " <= " + to_string(threshold);
            break;
        case 2:
            filteredList = tree.filterGreaterThanOrEqual(threshold);
            operationDescription = "Pokemon with " + tree.getSortingCriterion() + " >= " + to_string(threshold);
            break;
        case 3:
            filteredList = tree.filterEqual(threshold);
            operationDescription = "Pokemon with " + tree.getSortingCriterion() + " = " + to_string(threshold);
            break;
    }
    
    // Display results
    cout << "\n=== SEARCH RESULTS ===" << endl;
    cout << operationDescription << ":" << endl;
    cout << "Found " << filteredList.size() << " Pokemon matching criteria." << endl;
    
    if (filteredList.isEmpty()) {
        cout << "No Pokemon found matching the specified criteria." << endl;
        return 0;
    }
    
    cout << "\n";
    filteredList.printAll();
    
    // Handle interactive deletion
    handleDeletion(filteredList);
    
    // Write final results to output file
    vector<Pokemon> finalResults = filteredList.getAllPokemon();
    
    if (!finalResults.empty()) {
        writeToCSV(finalResults, "filtered_pokemon.csv");
        cout << "Final count: " << finalResults.size() << " Pokemon" << endl;
    } else {
        cout << "\nNo Pokemon remaining to write to file." << endl;
    }
    
    cout << "\nProgram completed successfully!" << endl;
    return 0;
}