#include <unordered_set>
#include <iostream>
#include <vector>
#include <memory>

template<typename Ctx>
class CanvasItem
{
public:
    void paint() {
        paintForward<Ctx::IsForward>();
    }
    void layout()
    {
        layoutForward<Ctx::IsForward>();
    }

private:
    template<bool forward>
    void layoutForward();

    template<>
    void layoutForward<true>() { std::cout << "Forward\n"; }
    
    template<>
    void layoutForward<false>() { std::cout << "Normal\n"; }

    template<bool forward>
    void paintForward();

    template<>
    void paintForward<true>() { std::cout << "Forward\n"; }

    template<>
    void paintForward<false>() { std::cout << "Normal\n"; }
};

template<bool IsForward>
struct CanvasItemTraits
{
    static constexpr bool IsForward = IsForward;
};

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

    CanvasItem<CanvasItemTraits<true>> a;
    CanvasItem<CanvasItemTraits<false>> b;

    a.layout();
    b.layout();
    return 0;
}
