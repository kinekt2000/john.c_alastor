// Самое интересное на 129 строке
#include <iostream>
#include <ostream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>


#define INF std::numeric_limits<float>::infinity()

#define GREEDY 0
#define ASTAR 1

struct Vertex;
struct Edge;

struct Edge{
    friend struct Vertex;

    float w;
    class Vertex* from;
    class Vertex* to;

    ~Edge();

private:
    Edge(Vertex *from, Vertex *to, float w);
};


struct Vertex{
    friend class Graph;

    char name;
    std::vector<Edge*> neighbours;

    ~Vertex();

    void addNeighbour(Vertex *other, float w);

private:
    Vertex(char name);
};


Edge::~Edge()
{
    for(auto it = from->neighbours.begin();
        it < from->neighbours.end(); it++)
    {
        if(*it == this){
            from->neighbours.erase(it);
            break;
        }
    }
}


Edge::Edge(Vertex *from, Vertex *to, float w):
    from(from), to(to), w(w)
{
    from->neighbours.push_back(this);
}


Vertex::~Vertex()
{
    for(auto edge: neighbours){
        delete edge;
    }
}


Vertex::Vertex(char name):
    name(name)
{}


void Vertex::addNeighbour(Vertex *other, float w)
{
    new Edge(this, other, w);
}


class Graph{
    std::vector<Vertex*> vertices;


    std::vector<char> greedySearch(Vertex *src, Vertex *dst){
        std::map<char, bool> visited;
        std::vector<Vertex*> stack;
        for(auto v: vertices){
            visited[v->name] = 0;
        }
        stack.push_back(src);
        while(!stack.empty()){
            if(stack.back() == dst)
                break;

            visited[stack.back()->name] = 1;
            std::vector<Edge*> unknownNeighbours;

            for(auto edge: stack.back()->neighbours)
                if(!visited[edge->to->name])
                    unknownNeighbours.push_back(edge);

            if(unknownNeighbours.empty()){
                stack.pop_back();
                continue;
            }

            auto min = *std::min_element(unknownNeighbours.begin(), unknownNeighbours.end(),
                                        [](const Edge* a, const Edge* b){
                                            return a->w < b->w;
                                        });
            stack.push_back(min->to);
        }
        std::vector<char> path;
        for(auto v: stack){
            path.push_back(v->name);
        }
        return path;
    }
    
    
    std::vector<char> astarSearch(Vertex *src, Vertex *dst){
        auto heuristic = [dst](char c){
            return float(std::abs(dst->name - c));
        };
        auto edgeCmp = [&heuristic](const Edge * a, const Edge * b){
            return heuristic(a->to->name) < heuristic(b->to->name);
        };

        std::vector<char> path;

        
        std::vector<Vertex*> closed, open = {src};
        std::map<char, char> prev;
        std::map<char, float> g_val, f_val;

        for(auto v: vertices){
            std::sort(v->neighbours.begin(), v->neighbours.end(), edgeCmp);
            prev[v->name] = 0;
            g_val[v->name] = INF;
            f_val[v->name] = INF;
        }

        g_val[src->name] = 0;
        f_val[src->name] = heuristic(src->name);

        while(!open.empty()){
            // find vertex with min distance (call it u)
            Vertex *u = open.back();
            float f = f_val[u->name];

            for(auto v: open){
                if(f_val[v->name] < f){
                    f = f_val[v->name];
                    u = v;
                }
            }

            // delete u from vertices set
            for(auto it = open.begin(); it < open.end(); it++){
                if(*it == u){
                    open.erase(it);
                    break;
                }
            }
            closed.push_back(u);

            // return if dst spotted
            if(u == dst){
                if(prev[u->name] == 0)
                    path.push_back(u->name);
                else{
                    char u_n = u->name;
                    while(u_n){
                        path.insert(path.begin(), u_n);
                        u_n = prev[u_n];
                    }
                }
                return path;
            }

            // check neighbours
            for(auto edge: u->neighbours){
                auto n = edge->to;
                if(std::find(closed.begin(), closed.end(), n) != closed.end())
                    continue;

                float alt_g = g_val[u->name] + edge->w;
                float alt_f = alt_g + heuristic(n->name);

                if(alt_g < g_val[n->name]){
                    if(std::find(open.begin(), open.end(), n) == open.end())
                        open.push_back(n);
                    g_val[n->name] = alt_g;
                    f_val[n->name] = alt_f;
                    prev[n->name] = u->name;
                }
            }
        }
        return path;
    }


public:
    ~Graph()
    {
        for(auto vertex: vertices){
            delete vertex;
        }
    }


    int addVertex(char name)
    {
        for(auto vertex: vertices){
            if(vertex->name == name)
                return 1; // Node allready exists
        }

        auto vertex = new Vertex(name);
        vertices.push_back(vertex);
        return 0;
    }


    int addVertex(char name, char from, float w)
    {
        for(auto vertex: vertices){
            if(vertex->name == name)
                return 1; // Node allready exists
        }

        Vertex *neighbour = nullptr;

        if(from != 0 && from != name){
            int isIn = 0;
            for(auto vertex: vertices){
                if(vertex->name == from){
                    neighbour = vertex;
                    isIn = 1;
                    break;
                }
            }
            if(!isIn){
                return 2; // Neighbour doesn't exist;
            }
        }

        auto vertex = new Vertex(name);
        neighbour->addNeighbour(vertex, w);
        vertices.push_back(vertex);
        return 0;
    }


    int delVertex(char name)
    {
        for(auto it = vertices.begin();
            it < vertices.end(); it++)
        {
            if((*it)->name == name){
                delete *it;
                vertices.erase(it);
                return 0;
            }
        }

        return 1; // Vertex doesn't exist
    }


    // connect two vertices
    // if any of the vertices doesn't exist, creates it and returns nonzero
    int connectVertices(char from_n, char to_n, float w)
    {
        int ret = 0;
        Vertex *from = nullptr;
        Vertex *to = nullptr;

        for(auto vertex: vertices){
            if(vertex->name == from_n)
                from = vertex;
            if(vertex->name == to_n)
                to = vertex;
            if(from != nullptr && to != nullptr) break;
        }

        if(from == nullptr){
            from = new Vertex(from_n);
            vertices.push_back(from);
            ret = 1;
        }
        if(to == nullptr){
            to = new Vertex(to_n);
            vertices.push_back(to);
            if(ret) ret = 3;
            else ret = 2;
        }

        from->addNeighbour(to, w);
        return ret;
    }


    std::vector<char> search(char src_n, char dst_n, bool type = 0){
        Vertex *src = nullptr;
        Vertex *dst = nullptr;

        std::vector<char> path;

        for(auto vertex: vertices){
            if(vertex->name == src_n)
                src = vertex;
            if(vertex->name == dst_n)
                dst = vertex;
            if(src != nullptr && dst != nullptr) break;
        }

        if(src == nullptr || dst == nullptr)
            return path;

        if(type == 0){
            path = greedySearch(src, dst);
        }
        else{
            path = astarSearch(src, dst);
        }

        return path;
    }



    void print(std::ostream& os){
        for(auto vertex: vertices){
            if(vertex->neighbours.size() == 0)
                os << vertex->name << " isolated" << std::endl;
            else{
                for(auto edge: vertex->neighbours){
                    os << edge->from->name << " " << edge->to->name << " " << edge->w << std::endl; 
                }
            }
        }
    }
};



int main(){
    auto graph = new Graph;

    char src, dst;
    std::cin >> src >> dst;
    char from, to;
    float len;
    
    while(std::cin >> from && std::cin >> to && std::cin >> len){
        graph->connectVertices(from, to, len);
    }

    auto path = graph->search(src, dst, ASTAR);

    for(auto c: path){
        std::cout << c;
    }

    return 0;
}