#include "SocialNetworkGraph.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

SocialNetworkGraph::SocialNetworkGraph() : edgeCount(0) {}

// Add bidirectional friendship between two users
void SocialNetworkGraph::addEdge(const string& user1, const string& user2) {
    adjacencyList[user1].push_back(user2);
    adjacencyList[user2].push_back(user1);
    edgeCount++;
}

// Load network from file in edge list format
bool SocialNetworkGraph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string user1, user2;
        
        // Read each edge from file
        if (iss >> user1 >> user2) {
            addEdge(user1, user2);
        }
    }
    
    file.close();
    return true;
}

const vector<string>& SocialNetworkGraph::getNeighbors(const string& user) const {
    static const vector<string> emptyVector;
    auto it = adjacencyList.find(user);
    return (it != adjacencyList.end()) ? it->second : emptyVector;
}

vector<string> SocialNetworkGraph::getAllUsers() const {
    vector<string> users;
    for (const auto& pair : adjacencyList) {
        users.push_back(pair.first);
    }
    return users;
}

int SocialNetworkGraph::getUserCount() const {
    return adjacencyList.size();
}

int SocialNetworkGraph::getEdgeCount() const {
    return edgeCount;
}

bool SocialNetworkGraph::hasUser(const string& user) const {
    return adjacencyList.find(user) != adjacencyList.end();
}
