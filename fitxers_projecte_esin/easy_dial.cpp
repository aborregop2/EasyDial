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
    else if (t != nullptr and t->_p.nom() == ""){
        phone p;
        t->_p = p;
    }
    return t;
}

easy_dial::easy_dial(const call_registry& R) throw(error){
    vector<phone> v;
    pref_curs = "";
    _arrel = nullptr;
    indefinit = true;
    sb = false;
    
    R.dump(v);
    mergeSortFreq(v);



    size = v.size();

    double *ptr = new double[v.size()];

    for (int i = 0; i < v.size(); ++i){
        ptr[i] = v[i].frequencia();
    }

    arrayFreqs = ptr;
    
    if (v.size() != 0){
         phoneMAX = v[0];
        
    }


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

void easy_dial::resVisitat(node *pt) {
    if (pt != nullptr) {
        if (pt->_p.nom() != "") {
            pt->_visitat = false;
        }

        resVisitat(pt->_esq);
        resVisitat(pt->_cen);
        resVisitat(pt->_dre);
    }
}

string easy_dial::inici() throw(){
    pref_curs = "";
    indefinit = false;
    sb = false;
    resVisitat(_arrel);

    
    if (_arrel != nullptr){
        phone ph;
        node* aux;
        F(_arrel, ph, aux);
        aux->_visitat = true;
        phoneANT = ph;
        return ph.nom();

      
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
       
        
        if (i == p.size() - 1 and p[p.size()-1] == S->_c ){
            pt = S;
        }
    }
    else if (p == ""){
        pt = S;
    }
}

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


string easy_dial::seguent(char c) throw(error){
    node *pt = nullptr;

    if (indefinit){
        throw error(ErrPrefixIndef);
    }

    if (pref_curs != ""){

        
        fistring(_arrel, pref_curs, pt);
        if (c == '\0'){
            if (pt != nullptr and pt->_p.nom() != "" and not pt->_visitat){
                phoneANT = pt->_p;
                pt->_visitat = true;
                return pt->_p.nom();
            } 
        }


        if (pt == nullptr){
            indefinit = true;
            throw error(ErrPrefixIndef);
        }
    }
 
    pref_curs  += c;
    pt = nullptr;
    fistring(_arrel, pref_curs, pt);
    
    
    if (pt == nullptr and (size == 0 or sb == true)){
            indefinit = true;
            throw error(ErrPrefixIndef);
    }
    else if (pt == nullptr){
        sb = true;
        return "";
    }
    
    node* aux = nullptr;
    phone ph;
    
    if (pt->_visitat == false){
        aux = pt;
        ph = pt->_p;
    }
    
    F(pt->_cen, ph, aux);

    if (aux != nullptr and aux->_p.nom() != ""){
        aux->_visitat = true;
    }
    else if (sb == false){
        sb = true; 
        if (aux != nullptr){
            aux->_visitat = false;
        }
        return "";
    }
    else{
        indefinit = true;
        throw error(ErrPrefixIndef);
    }

    phoneANT = ph;

    if (c == '\0'){
        if (aux != nullptr){
            aux->_visitat = false;
        }
        if (pt->_p.nom() != "" and not pt->_visitat){
            return pt->_p.nom();
        }
        else{
            return "";
        }
    }
    return ph.nom();
}

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

string easy_dial::anterior() throw(error){
   
    node *pt = nullptr; 
    node *minT = nullptr;

    if (indefinit){
        throw error(ErrPrefixIndef);
    }

    if (pref_curs == ""){
        indefinit = true;
        throw error(ErrNoHiHaAnterior);
    }


   

    fistring(_arrel, pref_curs, pt);
    phone q = phoneMAX;
    menorFreqT(pt, minT, q);

   
    if (minT != nullptr and sb != true){
        minT->_visitat = false;
    }

    minT = nullptr;
    
  
   

    pref_curs.pop_back();

    if (pref_curs == ""){
        phone aux = phoneMAX;
        menorFreqT(_arrel, minT, aux);
        if (minT != nullptr){
            return minT->_p.nom();
        }
        else{
            return phoneMAX.nom();
        }
    }

    fistring(_arrel, pref_curs, pt);


    if (pt == nullptr){
        indefinit = true;
        throw error(ErrPrefixIndef);
    }

    phone q2 = phoneMAX;
    menorFreqT(pt, minT, q2);

    sb = false;
    phoneANT = minT->_p;
    return minT->_p.nom();

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
    node *aux = nullptr;
    if (phoneANT.nom() == ""){
        F(pt->_cen, ph, aux);
    }
   
    if (pref_curs == ""){
        return phoneMAX.numero();
    }

    if (aux == nullptr and phoneANT.nom() == ""){
        throw error(ErrNoExisteixTelefon);
    }
    if (sb == false){
        return phoneANT.numero();
    }
    else{
        throw error(ErrNoExisteixTelefon);
    }

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
    if (_arrel != nullptr){
        
        node *pt = nullptr;
        fistring(_arrel, pref, pt);

        if (pref == ""){
            recorregutnoms(pt, result);
        }
        else{
            if (pt != nullptr){
                if (pt->_p.nom() != ""){
                    result.push_back(pt->_p.nom());
                }
                recorregutnoms(pt->_cen, result);
            }
        }

        mergeSortNom(result);
    }
}



double easy_dial::longitud_mitjana() const throw(){
    double sum = 0;
   
    for (int i = 0; i < size; i++) {
        sum += arrayFreqs[i];
    }

    double Pr[size];

    for (int i = 0; i < size; i++){
        Pr[i] = arrayFreqs[i] / sum;   //freqs = Pr(s)
    }

    double res = 0;

    for (int i = 0; i < size; ++i){
        res += Pr[i] * i;
    }

    return res;


}