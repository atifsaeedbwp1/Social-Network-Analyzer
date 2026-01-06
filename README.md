# Social Network Analyzer

A C++ console application that analyzes social networks using graph theory and implements core graph algorithms.

## Features

- **Degree Centrality**: Calculate the influence of users based on their connections
- **Shortest Path (BFS)**: Find the shortest connection path between two users
- **Connected Components (DFS)**: Identify separate communities in the network
- **Friend Recommendations**: Suggest new friends based on mutual connections

## Requirements

- C++ compiler with C++17 support (GCC, Clang, MSVC)
- Standard Template Library (STL)

## Compilation

```bash
g++ -std=c++17 -o SocialNetworkAnalyzer.exe main.cpp SocialNetworkGraph.cpp GraphAlgorithms.cpp
```

## Usage

1. Run the compiled executable:
```bash
.\SocialNetworkAnalyzer.exe
```

2. Choose from the menu options:
   - Load network from file (default: network.txt)
   - Display network statistics
   - Show degree centrality rankings
   - Find shortest path between users
   - Display connected components
   - Get friend recommendations

## Network Data Format

The network data file should contain edges in the following format:
```
user1 user2
user3 user4
...
```

Each line represents a bidirectional friendship between two users.

## Sample Usage

1. Load the sample network (network.txt)
2. View statistics to see total users and connections
3. Check degree centrality to find the most connected users
4. Find shortest path: e.g., from "Alice" to "William"
5. Get recommendations for any user

## Project Structure

- `SocialNetworkGraph.h/cpp` - Core graph data structure
- `GraphAlgorithms.h/cpp` - Graph algorithm implementations
- `main.cpp` - Console interface and application logic
- `network.txt` - Sample network data

## Algorithms Implemented

- **BFS** (Breadth-First Search) for shortest path
- **DFS** (Depth-First Search) for connected components
- **Degree Centrality** calculation
- **Friend-of-Friend** recommendation system


