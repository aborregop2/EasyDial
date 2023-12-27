#include "easy_dial.hpp"





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
    

        while(i < vleft.size() and j < vleft.size()){
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


easy_dial::node::node(const char &c, node* esq, node* cen, node* dre, bool v) throw(error): //Hay que poner phone
_c(c), _esq(esq), _cen(cen), _dre(dre), _visitat(v){
}




easy_dial::node* easy_dial::insereix(node *t, nat i, const string &k, phone ph){
    if (t == nullptr) {
        t = new node(k[i]);
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
        else { // (t->_c == k[i])
            t->_cen = insereix(t->_cen, i+1, k, ph);
        }
    }
    if (i == k.size()-1 and t != nullptr){
        
        t->_p = ph;
    }
    else if (t != nullptr){
        phone p;
        t->_p = p;
    }
    return t;
}




easy_dial::easy_dial(const call_registry& R) throw(error){
    vector<phone> v;
    pref_curs = "";
    size = 0;
    seg = 0;
    indefinit = false; //falta poner todo a false
    R.dump(v);
    mergeSortFreq(v);
    int j = 0;
    for(int i = 0; i < v.size(); ++i){
        _arrel = insereix(_arrel, j, v[i].nom(), v[i]);
        
    }
}

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

easy_dial::easy_dial(const easy_dial& D) throw(error){
    _arrel = cpyeasydial(D._arrel);
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
    if (this != &D){
        _arrel = cpyeasydial(D._arrel);
    }
    return *this;
}

void easy_dial::delete_easy_dial(node *p){
    if (p != nullptr){
        delete_easy_dial(p->_esq);
        delete_easy_dial(p->_cen);
        delete_easy_dial(p->_dre);

        delete(p);
    }
}

easy_dial::~easy_dial() throw(){
    delete_easy_dial(_arrel);
}

string easy_dial::inici() throw(){
    pref_curs = "";
    size = 0;
    seg = 0;
    indefinit = false;
    if (_arrel != nullptr){ 
        string res;
        node *rec = _arrel;
        while (rec != nullptr){
            res += rec->_c;
            rec = rec->_cen;
        }
        return res;
    }
    return "";
    
}


void easy_dial::fistring(node *S, string p, node* &pt, int i){//i == 0
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
        if (i == p.size() - 1){
            pt = S;
        }
    }
}

void easy_dial::F(node* S, phone &ph){ 
    /*node *pt = nullptr;
    fistring(S, p, pt);*/   //-> Hay que llamarlas cuando se llame a F nuestra S es pt

    if (S != nullptr){
        if (ph < S->_p and not S->_visitat){
            ph = S->_p;
        }

        F(S->_esq, ph);
        F(S->_cen, ph);
        F(S->_dre, ph);

        if (ph == S->_p){
            S->_visitat = true;
        }
    }
}


string easy_dial::seguent(char c) throw(error){
  node *pt = nullptr;

  if (pref_curs != ""){

        if (indefinit){
            throw error(ErrPrefixIndef);
        }
        
        fistring(_arrel, pref_curs, pt);

        if (pt == nullptr){
            indefinit = true;
            throw error(ErrPrefixIndef);
        }
   }

    pref_curs += c;

    fistring(_arrel, pref_curs, pt);

    phone ph;
    F(pt, ph);


    return ph.nom();
}

string easy_dial::anterior() throw(error){
   
    node *pt = nullptr; 

    if (indefinit){
        throw error(ErrPrefixIndef);
    }

    if (pref_curs == ""){
        throw error(ErrNoHiHaAnterior);
    }

    pref_curs.pop_back();

    fistring(_arrel, pref_curs, pt);

    if (pt == nullptr){
        indefinit = true;
        throw error(ErrPrefixIndef);
    }

    phone ph;
    F(pt, ph);

    return ph.nom();

}

nat easy_dial::num_telf() const throw(error){

    if (indefinit){
        throw error(ErrPrefixIndef);
    }

    node *pt = nullptr;

    fistring(_arrel, pref_curs, pt);

    if (pt == nullptr){
        throw error(ErrNoExisteixTelefon);
    }

    phone ph;
    F(pt, ph);

    return ph.numero();


}

void easy_dial::recorregutnoms(node *pt, vector<string> &result){
    if (pt != nullptr){
        if (pt->_p.nom() != ""){
            result.push_back(pt->_p.nom());
        }
        recorregutnoms(pt->_esq, result);
        recorregutnoms(pt->_cen, result);
        recorregutnoms(pt->_dre, result);
    }
    
}

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
    

        while(i < vleft.size() and j < vleft.size()){
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

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
    node *pt = nullptr;
    fistring(_arrel, pref, pt);
    recorregutnoms(pt, result);
    mergeSortNom(result);
}

double easy_dial::longitud_mitjana() const throw(){

}