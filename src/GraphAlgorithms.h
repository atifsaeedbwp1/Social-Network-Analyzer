#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "SocialNetworkGraph.h"
#include <map>

using namespace std;

class GraphAlgorithms {
public:
    // Calculate degree centrality for all users
    static map<string, int> calculateDegreeCentrality(const SocialNetworkGraph& graph);
    
    // Find shortest path between two users using BFS
    static vector<string> findShortestPath(
        const SocialNetworkGraph& graph,
        const string& source,
        const string& destination
    );
    
    // Find all connected components using DFS
    static vector<vector<string>> findConnectedComponents(const SocialNetworkGraph& graph);
    
    // Generate friend recommendations based on mutual connections
    static vector<string> generateRecommendations(
        const SocialNetworkGraph& graph,
        const string& user,
        int maxRecommendations = 5
    );

private:
    // Helper function for DFS traversal
    static void dfsHelper(
        const SocialNetworkGraph& graph,
        const string& user,
        unordered_set<string>& visited,
        vector<string>& component
    );
};

#endif
