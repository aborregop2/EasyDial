#include "call_registry.hpp"

call_registry::call_registry() throw(error) : _arrel(nullptr) {}

call_registry::node* call_registry::cpyCallRegistry(node *n) {
    node *root = nullptr;
    if (n != nullptr) {
        root = new node(n->_tl, nullptr, nullptr, n->_altura);

        node *esq = cpyCallRegistry(n->_fesq);
        node *dret = cpyCallRegistry(n->_fdret);

        root->_fesq = esq;
        root->_fdret = dret;
    }

    return root;
}

call_registry::call_registry(const call_registry& R) throw(error) {
    _arrel = cpyCallRegistry(R._arrel);
}

call_registry& call_registry::operator=(const call_registry& R) throw(error) {
    if (this != &R) {
        _arrel = cpyCallRegistry(R._arrel);
    }

    return *this;
}

void call_registry::deleteCallRegistry(node *n) {
    if (n != nullptr) {
        deleteCallRegistry(n->_fesq);
        deleteCallRegistry(n->_fdret);

        delete n;
    }
}

call_registry::~call_registry() throw() {
    deleteCallRegistry(_arrel);
}

void call_registry::registra_trucada(nat num) throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);
        p->_tl++;
    }
    else {
        //Afegir node amb contador a 1, nom buit i num.
    }
}

void call_registry::assigna_nom(nat num, const string& name) throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);

        phone pr(num, name, p->_tl.frequencia());
        p->_tl = pr;
    }
    else {
        //Afegir node amb contador a 0, name i num.
    }
}

void call_registry::elimina(nat num) throw(error) {

}

void call_registry::findPhone(node *n, node* &p, nat num) {
    if (n != nullptr and p == nullptr) {
        if (n->_tl.numero() < num) {
            findPhone(n->_fesq, p, num);
        }
        else if (n->_tl.numero() > num) {
            findPhone(n->_fdret, p, num);
        }
        else p = n;
    }
}

bool call_registry::conte(nat num) const throw() {
    node *p = nullptr;
    findPhone(_arrel, p, num);

    return p != nullptr;
}

string call_registry::nom(nat num) const throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);

        return p->_tl.nom();
    }
    else {

    }
}

nat call_registry::num_trucades(nat num) const throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);

        return p->_tl.frequencia();
    }
    else {

    }
}

bool call_registry::es_buit() const throw() {
    return _arrel == nullptr;
}

nat call_registry::numNodes(node *n) {
    if (n == nullptr) return 0;
    return numNodes(n->_fesq) + 1 + numNodes(n->_fdret);
}

nat call_registry::num_entrades() const throw() {
    return numNodes(_arrel);
}

void call_registry::inorder(node *n, vector<phone>& V) {
    if (n != nullptr) {
        inorder(n->_fesq, V);
        V.push_back(n->_tl);
        inorder(n->_fdret, V);
    }
}


void call_registry::dump(vector<phone>& V) const throw(error) {
    inorder(_arrel, V);
}