#include"node.hpp"
#include"Tree.hpp"
enum side{ left = 0, right = 1};
class edge{
    Node* ancestoredge;
    Node* childedge;
    bool which;
public:
    edge();
    ~edge();
    Node* get_anc(){return ancestoredge;};
    Node* get_child(){return childedge;};
    void create(Node *n, int index);
    bool IsMyEdge(Node *n);
    Node* FindEdge(Tree *myTree);
    Tree moveEdge( Tree *myTree, edge *newedge);
};
