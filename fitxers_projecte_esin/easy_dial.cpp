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
            if (vleft[i].frequencia() < vright[j].frequencia()){
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


easy_dial::node::node(const char &c, node* esq, node* cen, node* dre) throw(error): //Hay que poner phone
_c(c), _esq(esq), _cen(cen), _dre(dre){
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

string easy_dial::seguent(char c) throw(error){
    pref_curs += c;
    return pref_curs;
}

string easy_dial::anterior() throw(error){
    if (pref_curs.size() > 0)
    pref_curs.pop_back();
    return pref_curs;
}

nat easy_dial::num_telf() const throw(error){

}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){

}

double easy_dial::longitud_mitjana() const throw(){

}