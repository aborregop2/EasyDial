#include "call_registry.hpp"

//θ(1)
call_registry::call_registry() throw(error) : _arrel(nullptr), _size(0) {}

//θ(1)
call_registry::node::node(const phone &tl, node* fesq, node* fdret) throw(error)
    : _tl(tl), _fesq(fesq), _fdret(fdret), _altura(1){

}

//θ(1)
nat call_registry::altura(node *n){
    if (n == nullptr){
        return 0;
    }
    return n->_altura;
}

//θ(1)
int call_registry::factor_equilibri(node *n){
    if (n == nullptr){
        return 0;
    }
    return altura(n->_fesq) - altura(n->_fdret);
}

//θ(1)
call_registry::node* call_registry::rotacio_dreta(node *y){
    node *x = y->_fesq;
    if (x != nullptr){
        node *T2 = x->_fdret;

        x->_fdret = y;
        y->_fesq = T2;

        x->_altura = max(altura(x->_fesq), altura(x->_fdret)) + 1;
        y->_altura = max(altura(y->_fesq), altura(y->_fdret)) + 1;

        return x;
    }
    return y;
}

//θ(1)
call_registry::node* call_registry::rotacio_esquerra(node *x){
    node *y = x->_fdret ;
    if (y != nullptr){
        node *T2 = y->_fesq ;

        y->_fesq = x ;
        x->_fdret = T2;

        y->_altura = max(altura(y->_fesq), altura(y->_fdret)) + 1;
        x->_altura = max(altura(x->_fesq), altura(x->_fdret)) + 1;
        
        return y;
    }
    return x;
}

//θ(log n)
call_registry::node* call_registry::insereix(node *n, phone p){
    if (n == nullptr){
        return new node(p);
    }
    else if (p.numero() < n->_tl.numero()){
        n->_fesq = insereix(n->_fesq, p);
    }
    else if (p.numero() > n->_tl.numero()){
        n->_fdret = insereix(n->_fdret, p);
    }
    else{
        n->_tl = p;
        return n;
    }

    n->_altura = max(altura(n->_fesq), altura(n->_fdret)) + 1;

    int fe = factor_equilibri(n);

    if (fe > 1 and p.numero() < n->_fesq->_tl.numero()){
        return rotacio_dreta(n);
    }

    if (fe < -1 and p.numero() > n->_fdret->_tl.numero()){
        return rotacio_esquerra(n);
    }

    if (fe > 1 and p.numero() > n->_fesq->_tl.numero()){
        n->_fesq = rotacio_esquerra(n->_fesq);
        return rotacio_dreta(n);
    }

    if (fe < -1 and p.numero() < n->_fdret->_tl.numero()){
        n->_fdret = rotacio_dreta(n->_fdret);
        return rotacio_esquerra(n);
    }
    return n;
}

//θ(n)
call_registry::node* call_registry::cpyCallRegistry(node *n) {
    node *root = nullptr;
    if (n != nullptr) {
        root = new node(n->_tl);

        node *esq = cpyCallRegistry(n->_fesq);
        node *dret = cpyCallRegistry(n->_fdret);

        root->_fesq = esq;
        root->_fdret = dret;
       
    }

    return root;
}

//θ(n)
call_registry::call_registry(const call_registry& R) throw(error) : _size(R._size) {
     _arrel = cpyCallRegistry(R._arrel);
     _size = R._size;
}

//θ(n)
call_registry& call_registry::operator=(const call_registry& R) throw(error) {
    if (this != &R) {
        _arrel = cpyCallRegistry(R._arrel);
        _size = R._size;
    }
    
    return *this;
}

//θ(n)
void call_registry::deleteCallRegistry(node *n) {
    if (n != nullptr) {
        deleteCallRegistry(n->_fesq);
        deleteCallRegistry(n->_fdret);

        delete n;
    }
}

//θ(n)
call_registry::~call_registry() throw() {
    deleteCallRegistry(_arrel);
}

//θ(log n)
void call_registry::registra_trucada(nat num) throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);
        ++(p->_tl);
    }
    else {
        phone p(num, "", 1);
        _arrel = insereix(_arrel, p);
        ++_size;
    }
}

//θ(log n)
void call_registry::assigna_nom(nat num, const string& name) throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);

        phone pr(num, name, p->_tl.frequencia());
        p->_tl = pr;
    }
    else {
        phone p(num, name, 0);
        _arrel = insereix(_arrel, p);
        ++_size;        
    }
}

//θ(1)
call_registry::node* call_registry::elimina_maxim (node *n) throw (){
    node * p_orig = n, *father= nullptr ;
    while (n->_fdret != nullptr ) {
        father = n;
        n = n->_fdret;
    }
    
    if (father != nullptr) {
        father->_fdret = n->_fesq ; 
        n->_fesq = p_orig;
    }
    
    return n;
}

//θ(1)
call_registry::node* call_registry::ajunta(node *n1 , node *n2 ) throw (){
    if (n1 == nullptr) {
        return n2;
    }
    if (n2 == nullptr) {
        return n1;
    }
    node *p = elimina_maxim(n1);
    p->_fdret = n2;
    return p ;
}

//θ(n)
void call_registry::recalcula_altures(node *p){
    if (p != nullptr){
        recalcula_altures(p->_fesq);
        recalcula_altures(p->_fdret);
        p->_altura = max(altura(p->_fesq), altura(p->_fdret)) + 1;
    }
}

//θ(log n)
call_registry::node* call_registry::esborra(node *n, nat num){

    if (n != nullptr){
        if (num < n->_tl.numero()){
            n->_fesq = esborra(n->_fesq, num);
        }
        else if (num > n->_tl.numero()){
            n->_fdret = esborra(n->_fdret, num);
        }
        else{
            node *p = n;
            n = ajunta(n->_fesq , n->_fdret);
            delete (p);
            if (n != nullptr){
                recalcula_altures(n->_fesq);
            }
        }
  
    }
        if (n != nullptr){
            n->_altura = max(altura(n->_fesq), altura(n->_fdret)) + 1;

            int fe = factor_equilibri(n);

            if (fe > 1 and num < n->_fesq->_tl.numero()){
                return rotacio_dreta(n);
            }

            if (fe < -1 and num > n->_fdret->_tl.numero()){
                return rotacio_esquerra(n);
            }

            if (fe > 1 and num > n->_fesq->_tl.numero()){
                n->_fesq = rotacio_esquerra(n->_fesq);
                return rotacio_dreta(n);
            }

            if (fe < -1 and num < n->_fdret->_tl.numero()){
                n->_fdret = rotacio_dreta(n->_fdret);
                return rotacio_esquerra(n);
            }
        }
        return n;
    }

//θ(log n)
void call_registry::elimina(nat num) throw(error) {
    if (this->conte(num)){
        _arrel = esborra(_arrel, num);
        --_size;
    }
    else{
        throw error(ErrNumeroInexistent); 
    }
}

//θ(log n)
void call_registry::findPhone(node *n, node* &p, nat num) {
    if (n != nullptr and p == nullptr) {
        if (n->_tl.numero() < num) {
            findPhone(n->_fdret, p, num);
        }
        else if (n->_tl.numero() > num) {
            findPhone(n->_fesq, p, num);
        }
        else p = n;
    }
}

//θ(log n)
bool call_registry::conte(nat num) const throw() {
    node *p = nullptr;
    findPhone(_arrel, p, num);

    return p != nullptr;
}

//θ(h)
string call_registry::nom(nat num) const throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);

        return p->_tl.nom();
    }
    else {
       throw error(ErrNumeroInexistent); 
    }
}

//θ(h)
nat call_registry::num_trucades(nat num) const throw(error) {
    if (this->conte(num)) {
        node *p = nullptr;
        findPhone(_arrel, p, num);

        return p->_tl.frequencia();
    }
    else {
        throw error(ErrNumeroInexistent); 
    }
}

//θ(1)
bool call_registry::es_buit() const throw() {
    return _arrel == nullptr;
}

//θ(1)
nat call_registry::num_entrades() const throw() {
    return _size;
}

//θ(n)
void call_registry::inorder(node *n, vector<phone>& V) {
    if (n != nullptr) {
        inorder(n->_fesq, V);
        if (n->_tl.nom() != "") {
            V.push_back(n->_tl);
        }
        inorder(n->_fdret, V);
    }
}

//θ(n log(n))
void call_registry:: mergeSortNoms(vector<phone> &V){
    if(V.size() > 1){
        int half = V.size()/2;
        vector<phone> vleft;
        for(unsigned int i = 0; i < half; ++i){
            vleft.push_back(V[i]);
        }
        vector<phone> vright;
        for(unsigned int i = half; i < V.size(); ++i){
            vright.push_back(V[i]);
        }

        mergeSortNoms(vleft);
        mergeSortNoms(vright);

        unsigned int i = 0, j = 0, k = 0;
    

        while(i < vleft.size() and j < vleft.size()){
            if (vleft[i].nom() < vright[j].nom()){
                V[k] = vleft[i];
                ++i;
            }
            else{
                V[k] = vright[j];
                ++j;
            }
            k++;
        }
        
        while (i < vleft.size()){
            V[k] = vleft[i];
            ++i;
            ++k;
        }


        while (j < vright.size()){
            V[k] = vright[j];
            ++j;
            ++k;
        }

    }
} 

//θ(n log(n))
void call_registry::dump(vector<phone>& V) const throw(error) {
    inorder(_arrel, V);
    mergeSortNoms(V);
    bool iguals = false;
    for (unsigned int i = 1; i < V.size() and not iguals; ++i) {
        if (V[i].nom() == V[i-1].nom()) {
            iguals = true;
        }
    }

    if (iguals){
        throw error(ErrNomRepetit);
    }
}

