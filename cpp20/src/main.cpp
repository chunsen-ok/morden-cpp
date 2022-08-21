#include <unordered_set>
#include <iostream>

class Edge;

class Vertex
{
public:
    void add_edge(const std::shared_ptr<Edge>& edge)
    {
        if (auto it = mEdges.find(edge); it == mEdges.end()) {
            mEdges.insert(edge);
        }
    }

private:
    std::unordered_set<std::shared_ptr<Edge>> mEdges;
};

class Edge
{
public:
    static std::shared_ptr<Edge> create(const std::shared_ptr<Vertex>& v0, const std::shared_ptr<Vertex>& v1)
    {
        auto edge = std::make_shared<Edge>(v0, v1);
        v0->add_edge(edge);
        v1->add_edge(edge);
    }

protected:
    Edge(const std::shared_ptr<Vertex>& v0, const std::shared_ptr<Vertex>& v1)
        : v0(v0)
        , v1(v1)
    {
        
    }

private:
    std::weak_ptr<Vertex> v0;
    std::weak_ptr<Vertex> v1;
};

class Graph
{
public:
    
};

int main()
{
    auto v0 = std::make_shared<Vertex>();
    auto v1 = std::make_shared<Vertex>();
    Edge::create(v0, v1);

    return 0;
}
