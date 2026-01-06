#include "GraphAlgorithms.h"
#include <queue>
#include <algorithm>

using namespace std;

// Calculate degree centrality for all users
map<string, int> GraphAlgorithms::calculateDegreeCentrality(const SocialNetworkGraph& graph) {
    map<string, int> centrality;
    vector<string> users = graph.getAllUsers();
    
    for (const auto& user : users) {
        centrality[user] = graph.getNeighbors(user).size();
    }
    
    return centrality;
}

// Find shortest path using BFS algorithm
vector<string> GraphAlgorithms::findShortestPath(
    const SocialNetworkGraph& graph,
    const string& source,
    const string& destination
) {
    if (!graph.hasUser(source) || !graph.hasUser(destination)) {
        return {};
    }
    
    unordered_map<string, string> parent; // Track path
    unordered_set<string> visited;
    queue<string> q;
    
    q.push(source);
    visited.insert(source);
    parent[source] = "";
    
    // BFS traversal
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        
        if (current == destination) {
            // Reconstruct path from destination to source
            vector<string> path;
            string node = destination;
            
            while (node != "") {
                path.push_back(node);
                node = parent[node];
            }
            
            reverse(path.begin(), path.end());
            return path;
        }
        
        // Explore neighbors
        for (const auto& neighbor : graph.getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    
    return {}; // No path found
}

// DFS helper for finding connected components
void GraphAlgorithms::dfsHelper(
    const SocialNetworkGraph& graph,
    const string& user,
    unordered_set<string>& visited,
    vector<string>& component
) {
    visited.insert(user);
    component.push_back(user);
    
    // Recursively visit all unvisited neighbors
    for (const auto& neighbor : graph.getNeighbors(user)) {
        if (visited.find(neighbor) == visited.end()) {
            dfsHelper(graph, neighbor, visited, component);
        }
    }
}

// Find all connected components using DFS
vector<vector<string>> GraphAlgorithms::findConnectedComponents(const SocialNetworkGraph& graph) {
    vector<vector<string>> components;
    unordered_set<string> visited;
    vector<string> users = graph.getAllUsers();
    
    for (const auto& user : users) {
        if (visited.find(user) == visited.end()) {
            vector<string> component;
            dfsHelper(graph, user, visited, component);
            components.push_back(component);
        }
    }
    
    return components;
}

// Generate friend recommendations using friend-of-friend algorithm
vector<string> GraphAlgorithms::generateRecommendations(
    const SocialNetworkGraph& graph,
    const string& user,
    int maxRecommendations
) {
    if (!graph.hasUser(user)) {
        return {};
    }
    
    // Get all direct friends
    unordered_set<string> directFriends;
    for (const auto& friend1 : graph.getNeighbors(user)) {
        directFriends.insert(friend1);
    }
    
    // Find friends of friends
    map<string, int> potentialFriends; // Count mutual friends
    
    for (const auto& friend1 : directFriends) {
        for (const auto& friend2 : graph.getNeighbors(friend1)) {
            // Skip self and direct friends
            if (friend2 != user && directFriends.find(friend2) == directFriends.end()) {
                potentialFriends[friend2]++;
            }
        }
    }
    
    // Sort by number of mutual friends
    vector<pair<string, int>> sorted(potentialFriends.begin(), potentialFriends.end());
    sort(sorted.begin(), sorted.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Return top recommendations
    vector<string> recommendations;
    for (int i = 0; i < min(maxRecommendations, (int)sorted.size()); i++) {
        recommendations.push_back(sorted[i].first);
    }
    
    return recommendations;
}
