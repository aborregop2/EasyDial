#include "easy_dial.hpp"

//θ(n log(n))
void mergeSortFreq(vector<phone> &V){
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

        mergeSortFreq(vleft);
        mergeSortFreq(vright);

        unsigned int i = 0, j = 0, k = 0;
    

        while(i < vleft.size() and j < vright.size()){
            if (vleft[i].frequencia() > vright[j].frequencia()){
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

//θ(1)
easy_dial::node::node(const char &c, node* esq, node* cen, node* dre, bool v) throw(error):
_c(c), _esq(esq), _cen(cen), _dre(dre), _visitat(v){
}

//θ(log s)
easy_dial::node* easy_dial::insereix(node *t, nat i, const string &k, phone ph){
    if (t == nullptr) {
        t = new node(k[i]);
        phone p;
        t->_p = p;
        try {
            if (i < k.length()-1) {
                t->_cen = insereix(t->_cen, i+1, k, ph);
            }
        }
        catch (...) {
            delete t;
            throw;
        }
    } 
    else {
        if (t->_c > k[i]) {
            t->_esq = insereix(t->_esq, i, k, ph);
        }
        else if (t->_c < k[i]) {
            t->_dre = insereix(t->_dre, i, k, ph);
        }
        else {
            t->_cen = insereix(t->_cen, i+1, k, ph);
        }
    }

    if (i == k.size()-1 and t != nullptr and k[k.size()-1] == t->_c){
        t->_p = ph;   
    }
    else if (t != nullptr and t->_p.nom().empty()){
        phone p;
        t->_p = p;
    }

    return t;
}

//θ(n log(n)))
easy_dial::easy_dial(const call_registry& R) throw(error){
    vector<phone> v;
    _pref_curs = "";
    _arrel = nullptr;
    _indefinit = true;
    _stringBuit = false;
    _fiprefZ = false;
    
    R.dump(v);
    mergeSortFreq(v);

    _size = v.size();

    phone *ptr = new phone[_size];

    for (int i = 0; i < _size; ++i){
        ptr[i] = v[i];
    }
 
    _arrayPhones = ptr;
    
    if (_size != 0){
         _phoneMAX = v[0]; 
    }


    int j = 0;
    for(int i = 0; i < _size; ++i){
        _arrel = insereix(_arrel, j, v[i].nom(), v[i]);
    }
   

    int *ptrp = new int[_size];
    
    for (unsigned int i = 0; i < _size; ++i){
        _indefinit = false;
        bool trobat = false;
        phone ph;
        node* aux;
        F(_arrel, ph, aux);
        aux->_visitat = true;
        string auxiliar = ph.nom();
        

        for (unsigned int j = 0; j <= _arrayPhones[i].nom().size() and not trobat; ++j){
            if (auxiliar == _arrayPhones[i].nom()){
                ptrp[i] = _pref_curs.size();
                trobat = true;
            }
            else{
                if(_pref_curs.size() == _arrayPhones[i].nom().size()){
                    ptrp[i] = _pref_curs.size() + 1;
                    trobat = true;
                }
                else{
                    auxiliar = this->seguent(_arrayPhones[i].nom()[j]);
                }
            }
            
        }
        
        _pref_curs = "";
        _stringBuit = false;
        _fiprefZ = false;
        resVisitat(_arrel);

    }

    _indefinit = true;
    _arrayPulsacions = ptrp;
}

//θ(s)
easy_dial::node* easy_dial::cpyeasydial(node *p){
    node *root = nullptr;
    if (p != nullptr){
        root = new node(p->_c);
        root->_esq = cpyeasydial(p->_esq);
        root->_cen = cpyeasydial(p->_cen);
        root->_dre = cpyeasydial(p->_dre);
    }
    return root;
}

//θ(s)
easy_dial::easy_dial(const easy_dial& D) throw(error){
    _arrel = cpyeasydial(D._arrel);
}

//θ(s)
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
    if (this != &D){
        _arrel = cpyeasydial(D._arrel);
    }
    return *this;
}

//θ(s)
void easy_dial::delete_easy_dial(node *p){
    if (p != nullptr){
        delete_easy_dial(p->_esq);
        delete_easy_dial(p->_cen);
        delete_easy_dial(p->_dre);

        delete(p);
    }
}

//θ(s)
easy_dial::~easy_dial() throw(){
    delete_easy_dial(_arrel);
}

//θ(s)
void easy_dial::resVisitat(node *pt) {
    if (pt != nullptr) {
        if (not pt->_p.nom().empty()) {
            pt->_visitat = false;
        }

        resVisitat(pt->_esq);
        resVisitat(pt->_cen);
        resVisitat(pt->_dre);
    }
}

//θ(s)
string easy_dial::inici() throw(){
    _pref_curs = "";
    _indefinit = false;
    _stringBuit = false;
    _fiprefZ = false;
    resVisitat(_arrel);

    if (_arrel != nullptr){
        phone ph;
        node* aux;
        F(_arrel, ph, aux);
        aux->_visitat = true;
        _phoneANT = ph;
        return ph.nom();
    }

    return "";
}

//θ(log l)
void easy_dial::fistring(node *S, string p, node* &pt, int i){
    if (S != nullptr and i != p.size()){
        
        if (p[i] < S->_c){
            fistring(S->_esq, p, pt, i);
        }
        else if (p[i] > S->_c){
            fistring(S->_dre, p, pt, i);
        }
        else if (p[i] == S->_c){
            fistring(S->_cen, p, pt, i + 1);
        }
         
        if (i == p.size() - 1 and p[p.size()-1] == S->_c){
            pt = S;
        }
    }
    else if (p.empty()){
        pt = S;
    }
}

//θ(s)
void easy_dial::F(node* S, phone &ph, node *&aux) { 
    if (S != nullptr){
        if (ph < S->_p and not S->_visitat){
            ph = S->_p;
            aux = S;
        }

        F(S->_esq, ph, aux);
        F(S->_cen, ph, aux);
        F(S->_dre, ph, aux);

    }
}

//θ(s)
string easy_dial::seguent(char c) throw(error) {
    if (_indefinit) {
        throw error(ErrPrefixIndef);
    }

    if (not _pref_curs.empty()) {
        node *pt = nullptr;
        fistring(_arrel, _pref_curs, pt);

        if (c == phone::ENDPREF and pt != nullptr and not pt->_p.nom().empty() and !pt->_visitat) {
            _phoneANT = pt->_p;
            pt->_visitat = true;
            _fiprefZ = true;
            return pt->_p.nom();
        }

        if (pt == nullptr) {
            _indefinit = true;
            throw error(ErrPrefixIndef);
        }
    }

    if (_fiprefZ) {
        _fiprefZ = false;
    }

    _pref_curs += c;

    node *pt = nullptr;
    fistring(_arrel, _pref_curs, pt);

    if ((pt == nullptr and (_size == 0 or _stringBuit)) or (pt == nullptr and _stringBuit)) {
        _indefinit = true;
        throw error(ErrPrefixIndef);
    } 
    else if (pt == nullptr) {
        _stringBuit = true;
        return "";
    }

    node *aux = nullptr;
    phone ph;

    if (not pt->_visitat) {
        aux = pt;
        ph = pt->_p;
    }

    F(pt->_cen, ph, aux);

    if (aux != nullptr and not aux->_p.nom().empty()) {
        aux->_visitat = true;
    } 
    else if (not _stringBuit) {
        _stringBuit = true;

        if (aux != nullptr) {
            aux->_visitat = false;
        }
        
        return "";
    } 
    else {
        _indefinit = true;
        throw error(ErrPrefixIndef);
    }

    _phoneANT = ph;
    return ph.nom();
}

//θ(s)
void easy_dial::menorFreqT(node *p, node *&f, phone &min){
    
    if (p != nullptr){
        if (p->_visitat == true and p->_p < min){
            f = p;
            min = p->_p;
        }

        menorFreqT(p->_esq, f, min);
        menorFreqT(p->_cen, f, min);
        menorFreqT(p->_dre, f, min);

    }
}

//θ(s)
string easy_dial::anterior() throw(error) {
                                                            
    if (_indefinit) {
        throw error(ErrPrefixIndef);
    }

    if (_pref_curs.empty()) {
        if (_phoneMAX == _phoneANT) {
            _indefinit = true;
            throw error(ErrNoHiHaAnterior);
        } 
        else {
            _phoneANT = _phoneMAX;
            return _phoneMAX.nom();
        }
    }

    node *pt = nullptr;
    node *minT = nullptr;

    fistring(_arrel, _pref_curs, pt);
    phone q = _phoneMAX;
    menorFreqT(pt, minT, q);

    if (minT != nullptr and not _stringBuit) {
        minT->_visitat = false;
    }

    minT = nullptr;

    if (_fiprefZ) {
        _fiprefZ = false;
    } 
    else {
        _pref_curs.pop_back();
    }

    if (_pref_curs.empty()) {
        phone aux = _phoneMAX;
        menorFreqT(_arrel, minT, aux);
        if (minT != nullptr) {
            _phoneANT = minT->_p;
            return minT->_p.nom();
        } 
        else {
            _phoneANT = _phoneMAX;
            return _phoneMAX.nom();
        }
    }

    fistring(_arrel, _pref_curs, pt);

    if (pt == nullptr) {
        _indefinit = true;
        throw error(ErrPrefixIndef);
    }

    phone q2 = _phoneMAX;
    menorFreqT(pt, minT, q2);

    _stringBuit = false;

    if (minT == nullptr) {
        _phoneANT = _phoneMAX;
        return _phoneMAX.nom();
    }

    _phoneANT = minT->_p;

    return minT->_p.nom();
}

//θ(s)
nat easy_dial::num_telf() const throw(error) {
    if (_indefinit) {
        throw error(ErrPrefixIndef);
    }

    node *pt = nullptr;
    fistring(_arrel, _pref_curs, pt);

    if (pt == nullptr) {
        throw error(ErrNoExisteixTelefon);
    }

    phone ph;
    node *aux = nullptr;
    if (_phoneANT.nom().empty()) {
        F(pt->_cen, ph, aux);
    }

    if (_pref_curs.empty()) {
        if (_phoneMAX != _phoneANT) {
            phone aux_phone = _phoneMAX;
            node *minT = nullptr;
            menorFreqT(_arrel, minT, aux_phone);
            if (minT != nullptr) {
                return minT->_p.numero();
            } 
            else {
                return _phoneMAX.numero();
            }
        } 
        else {
            return _phoneMAX.numero();
        }
    }

    if (aux == nullptr and _phoneANT.nom().empty()) {
        throw error(ErrNoExisteixTelefon);
    }

    if (not _stringBuit) {
        return _phoneANT.numero();
    } 
    else {
        throw error(ErrNoExisteixTelefon);
    }
}

//θ(s)
void easy_dial::recorregutnoms(node *pt, vector<string> &result){
    if (pt != nullptr){
        if (not pt->_p.nom().empty()){
            result.push_back(pt->_p.nom());
        }

        recorregutnoms(pt->_esq, result);
        recorregutnoms(pt->_cen, result);
        recorregutnoms(pt->_dre, result);
    } 
}


//θ(n log(n))
void easy_dial::mergeSortNom(vector<string> &V){
        if(V.size() > 1){
        int half = V.size()/2;
        vector<string> vleft;
        for(unsigned int i = 0; i < half; ++i){
            vleft.push_back(V[i]);
        }
        vector<string> vright;
        for(unsigned int i = half; i < V.size(); ++i){
            vright.push_back(V[i]);
        }

        mergeSortNom(vleft);
        mergeSortNom(vright);

        unsigned int i = 0, j = 0, k = 0;
    

        while(i < vleft.size() and j < vright.size()){
            if (vleft[i] < vright[j]){
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

//θ(log l)
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
    if (_arrel != nullptr){
        
        node *pt = nullptr;
        fistring(_arrel, pref, pt);

        if (pref.empty()){
            recorregutnoms(pt, result);
        }
        else{
            if (pt != nullptr){
                if (not pt->_p.nom().empty()){
                    result.push_back(pt->_p.nom());
                }
                recorregutnoms(pt->_cen, result);
            }
        }

        mergeSortNom(result);
    }
}


//θ(n)
double easy_dial::longitud_mitjana() const throw(){
    double sum = 0, res = 0;
    for (int i = 0; i < _size; i++) {
        sum += _arrayPhones[i].frequencia();
    }

    for (int i = 0; i < _size; ++i){
        res += ((_arrayPhones[i].frequencia() / sum) * _arrayPulsacions[i]);
    }

    return res;
}