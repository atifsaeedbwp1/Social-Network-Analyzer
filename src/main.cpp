#include <iostream>
#include <iomanip>
#include <algorithm>
#include "SocialNetworkGraph.h"
#include "GraphAlgorithms.h"

using namespace std;

// Display main menu
void displayMenu() {
    cout << "\n========== SOCIAL NETWORK ANALYZER ==========\n";
    cout << "1. Load Network from File\n";
    cout << "2. Display Network Statistics\n";
    cout << "3. Show Degree Centrality\n";
    cout << "4. Find Shortest Path\n";
    cout << "5. Show Connected Components\n";
    cout << "6. Get Friend Recommendations\n";
    cout << "7. Exit\n";
    cout << "============================================\n";
    cout << "Enter choice: ";
}

// Display network statistics
void displayStatistics(const SocialNetworkGraph& graph) {
    cout << "\n--- Network Statistics ---\n";
    cout << "Total Users: " << graph.getUserCount() << "\n";
    cout << "Total Connections: " << graph.getEdgeCount() << "\n";
}

// Display degree centrality rankings
void displayDegreeCentrality(const SocialNetworkGraph& graph) {
    auto centrality = GraphAlgorithms::calculateDegreeCentrality(graph);
    
    // Sort users by degree (highest to lowest)
    vector<pair<string, int>> sorted(centrality.begin(), centrality.end());
    sort(sorted.begin(), sorted.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    cout << "\n--- Degree Centrality (Top 10) ---\n";
    cout << left << setw(20) << "User" << "Connections\n";
    cout << string(35, '-') << "\n";
    
    for (int i = 0; i < min(10, (int)sorted.size()); i++) {
        cout << left << setw(20) << sorted[i].first 
                  << sorted[i].second << "\n";
    }
}

// Interactive shortest path finder
void findShortestPathInteractive(const SocialNetworkGraph& graph) {
    string source, destination;
    cout << "\nEnter source user: ";
    cin >> source;
    cout << "Enter destination user: ";
    cin >> destination;
    
    auto path = GraphAlgorithms::findShortestPath(graph, source, destination);
    
    if (path.empty()) {
        cout << "No path found between " << source << " and " << destination << "\n";
    } else {
        cout << "\nShortest Path (Length: " << path.size() - 1 << "):\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
}

// Display all connected components
void displayConnectedComponents(const SocialNetworkGraph& graph) {
    auto components = GraphAlgorithms::findConnectedComponents(graph);
    
    cout << "\n--- Connected Components ---\n";
    cout << "Total Components: " << components.size() << "\n\n";
    
    for (size_t i = 0; i < components.size(); i++) {
        cout << "Component " << (i + 1) << " (Size: " << components[i].size() << "):\n";
        for (const auto& user : components[i]) {
            cout << "  - " << user << "\n";
        }
        cout << "\n";
    }
}

// Show friend recommendations for a user
void showRecommendations(const SocialNetworkGraph& graph) {
    string user;
    cout << "\nEnter user name: ";
    cin >> user;
    
    auto recommendations = GraphAlgorithms::generateRecommendations(graph, user);
    
    if (recommendations.empty()) {
        cout << "No recommendations available for " << user << "\n";
    } else {
        cout << "\n--- Friend Recommendations for " << user << " ---\n";
        for (size_t i = 0; i < recommendations.size(); i++) {
            cout << (i + 1) << ". " << recommendations[i] << "\n";
        }
    }
}

int main() {
    SocialNetworkGraph graph;
    bool networkLoaded = false;
    
    cout << "Welcome to Social Network Analyzer!\n";
    
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        
        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1: {
                string filename;
                cout << "Enter filename (or press Enter for 'network.txt'): ";
                cin.ignore();
                getline(cin, filename);
                
                if (filename.empty()) {
                    filename = "network.txt";
                }
                
                if (graph.loadFromFile(filename)) {
                    cout << "Network loaded successfully from " << filename << "!\n";
                    networkLoaded = true;
                    displayStatistics(graph);
                } else {
                    cout << "Error: Could not load file " << filename << "\n";
                }
                break;
            }
            
            case 2:
                if (!networkLoaded) {
                    cout << "Please load a network first.\n";
                } else {
                    displayStatistics(graph);
                }
                break;
            
            case 3:
                if (!networkLoaded) {
                    cout << "Please load a network first.\n";
                } else {
                    displayDegreeCentrality(graph);
                }
                break;
            
            case 4:
                if (!networkLoaded) {
                    cout << "Please load a network first.\n";
                } else {
                    findShortestPathInteractive(graph);
                }
                break;
            
            case 5:
                if (!networkLoaded) {
                    cout << "Please load a network first.\n";
                } else {
                    displayConnectedComponents(graph);
                }
                break;
            
            case 6:
                if (!networkLoaded) {
                    cout << "Please load a network first.\n";
                } else {
                    showRecommendations(graph);
                }
                break;
            
            case 7:
                cout << "Thank you for using Social Network Analyzer!\n";
                return 0;
            
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
