#ifndef SOCIAL_NETWORK_GRAPH_H
#define SOCIAL_NETWORK_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class SocialNetworkGraph {
private:
    unordered_map<string, vector<string>> adjacencyList; // Stores graph as adjacency list
    int edgeCount; // Total number of edges in the graph

public:
    SocialNetworkGraph();
    
    // Add bidirectional edge between two users
    void addEdge(const string& user1, const string& user2);
    
    // Load network from file
    bool loadFromFile(const string& filename);
    
    // Get all neighbors of a user
    const vector<string>& getNeighbors(const string& user) const;
    
    // Get list of all users in the network
    vector<string> getAllUsers() const;
    
    // Get total number of users
    int getUserCount() const;
    
    // Get total number of connections
    int getEdgeCount() const;
    
    // Check if user exists in network
    bool hasUser(const string& user) const;
};

#endif
