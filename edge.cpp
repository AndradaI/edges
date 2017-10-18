#include"edge.hpp"

edge::edge(){
    this->ancestoredge = new Node();
    this->childedge = new Node();
    if( ancestoredge->left() == childedge){
        which = left;
    }
    else{
        which = right;
    }
}

edge::~edge(){
    delete this->ancestoredge;
    delete this->childedge;
}

void edge::create(Node *n, int index){
    if( n->tipNumber() == 0 ){
        create(n->left(), index);
        create(n->right(), index);
        index++;
    }
    this->ancestoredge = n->parent();
    this->childedge = n;
    this->childedge->assignIndex(index);
    return;
}

bool edge::IsMyEdge(Node* n){
    if( n == this->get_anc() && (n->left() == this->get_child() || n->right() == this->get_child() )) return true;
    return false;
}

Node* Node::FindNode(Node *n){
    if( this->tipNumber() == n->tipNumber()) return this;
    else{
        Node *p = this->left()->FindNode(n);
        Node *s = this->right()->FindNode(n);
        if( p!= nullptr) return p;
        if( s!= nullptr) return s;
    }
    return nullptr;
}

Node* edge::FindEdge(Tree *myTree){
    if( myTree->isrooted()){
        Node *anc = myTree->rootNode()->FindNode(this->get_anc());
        if( anc->left() == this->get_child()) return anc->left();
        if( anc->right() == this->get_child()) return anc->right();
    }
    return nullptr;
}

Tree edge::moveEdge(Tree *myTree, edge *newEdge){
    //Remove Edge
    Node *child = this->FindEdge(myTree);
    Node *anc = child->parent();
    Node *anc_par_leftOrRight;
    Node *anc_par = anc->parent();
    Node *anc_leftOrRight;
    if( this->which == left){
        if( anc->parent()->left() == anc){
            anc_par_leftOrRight = anc->parent()->left();
            anc_par_leftOrRight = anc->right();
            anc_par = nullptr;
            anc_leftOrRight = anc->right();
            anc_leftOrRight = nullptr;
        }
        else{
            anc_par_leftOrRight = anc->parent()->right();
            anc_par_leftOrRight = anc->right();
            anc_par = nullptr;
            anc_leftOrRight = anc->right();
            anc_leftOrRight = nullptr;
        }
    }
    else{
        if( anc->parent()->left() == anc){
            anc_par_leftOrRight = anc->parent()->left();
            anc_par_leftOrRight = anc->left();
            anc_par = nullptr;
            anc_leftOrRight = anc->left();
            anc_leftOrRight = nullptr;
        }
        else{
            anc_par_leftOrRight = anc->parent()->right();
            anc_par_leftOrRight = anc->left();
            anc_par = nullptr;
            anc_leftOrRight = anc->left();
            anc_leftOrRight = nullptr;
        }
    }

    Node *newEdge_anc_right = newEdge->get_anc()->right();
    Node *newEdge_anc_left = newEdge->get_anc()->left();
    Node *newEdge_child_parent = newEdge->get_child()->parent();
    //Add SubTree to newedge
    if( newEdge->which == left){
        newEdge_anc_right = anc;
        newEdge_child_parent = anc;
        newEdge_anc_left = nullptr;
        anc_par = newEdge->get_anc();
        anc_leftOrRight = newEdge->get_child();
    }
    else{
        newEdge_anc_left = anc;
        newEdge_child_parent = anc;
        newEdge_anc_right = nullptr;
        anc_par = newEdge->get_anc();
        anc_leftOrRight = newEdge->get_child();
    }

    return *myTree;
}


