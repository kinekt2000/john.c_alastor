#include <iostream>
#include <ostream>
#include <fstream>

#include <string>
#include <limits>
#include <algorithm>

#include <vector>
#include <stack>
#include <map>

class Graph{
    using Vertex = char;
    std::map<Vertex, std::map<Vertex, long int>> adjMatrix; // [from][to]
    std::map<Vertex, std::map<Vertex, long int>> flow;

public:
    void addPair(Vertex a, Vertex b, long int capacity){
        adjMatrix[a][b] = capacity;
    }

    long int iFordFulkerson(Vertex src, Vertex snk){
        flow.clear();
        auto residualFlow = adjMatrix;
        long int max_flow = 0;

        auto findWay = [this, &residualFlow](Vertex src, Vertex dst){
            std::stack<Vertex> stack;
            std::map<Vertex, bool> visited;
            std::map<Vertex, Vertex> prev;

            stack.push(src);
            while(!stack.empty()){
                auto u = stack.top();
                if(u == dst) break;

                stack.pop();
                visited[u] = 1;
                std::vector<Vertex> neighbours;
                for(auto p: residualFlow[u]){
                    if(!visited[p.first] && p.second > 0)
                        neighbours.push_back(p.first);

                }

                std::sort(neighbours.begin(), neighbours.end(),
                          [u, &residualFlow](const Vertex &a, const Vertex &b)
                          {return residualFlow[u][a] < residualFlow[u][b];});

                for(auto n: neighbours){
                    stack.push(n);
                    prev[n] = u;
                }
            }
            return prev;
        };

        auto prev = findWay(src, snk);
        while(prev.count(snk) > 0){
            long int path_flow = std::numeric_limits<long int>::max();
            auto temp = snk;

            while(temp != src){
                path_flow = std::min(path_flow, residualFlow[prev[temp]][temp]);
                temp = prev[temp];
            }

            max_flow += path_flow;
            temp = snk;
            while(temp != src){
                auto from = prev[temp];
                residualFlow[from][temp] -= path_flow;
                residualFlow[temp][from] += path_flow;
                temp = prev[temp];
            }

            prev = findWay(src, snk);
        }

        for(auto from_p: adjMatrix)
            for(auto to_p: from_p.second){
                auto iFlow = to_p.second - residualFlow[from_p.first][to_p.first];
                flow[from_p.first][to_p.first] = (iFlow < 0) ? 0 : iFlow;
            }

        return max_flow;
    }

    const auto& getFlow() const{
        return flow;
    }

};


int main(){
    Graph graph;

     // get number of edges
    int N;
    std::cin >> N;

    // get src and dst of path
    char src, snk;
    std::cin >> src >> snk;

    // get graph (two points and length between)
    char from, to;
    long int len;    
    for(int i = 0; i < N; i++){
        std::cin >> from >> to >> len;
        graph.addPair(from, to, len);
    }

    auto max_flow = graph.iFordFulkerson(src, snk);
    std::cout << max_flow << std::endl;

    for(auto from_p: graph.getFlow()){
        for(auto to_p: from_p.second){
            std::cout << from_p.first << " "
                      << to_p.first << " "
                      << to_p.second << std::endl;
        }
    }

    return 0;
}
