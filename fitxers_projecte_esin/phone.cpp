#include "phone.hpp"

  phone::phone(nat num, const string& name, nat compt) throw(error) 
  	: _num(num), _nom(name), _compt(compt) {
      for(unsigned int i = 0; i < name.size(); ++i){
        if (name[i] == DELETECHAR or name[i] == ENDCHAR or name[i] == ENDPREF){
          throw error(ErrNomIncorrecte);
        }
      }
    }

  phone::phone(const phone& T) throw(error)
   	: _num(T._num), _nom(T._nom), _compt(T._compt) {}

  phone& phone::operator=(const phone& T) throw(error) {
		if (this != &T) {
			_num = T._num;
			_nom = T._nom;
			_compt = T._compt;
		}
	
		return *this;
  }

  phone::~phone() throw() {}

  nat phone::numero() const throw() {
  		return _num;
  }

  string phone::nom() const throw() {
  		return _nom;
  }

  nat phone::frequencia() const throw() {
    	return _compt;
  }

  phone& phone::operator++() throw() {
  
		_compt++;
			
		return *this;
    	
  }

  phone phone::operator++(int) throw() {

		phone p(*this);
    	_compt++;
    	
    	return p;

  }

  bool phone::operator==(const phone& T) const throw() {
	  	return not (*this != T);
  }
  
  bool phone::operator!=(const phone& T) const throw() {

		if (_compt != T._compt) return true;
		else return _nom != T._nom;
  }
  
  bool phone::operator<(const phone& T) const throw() {

	  	if (_compt < T._compt) return true;
	  	else if (_compt == T._compt) return _nom < T._nom;
	
	  	return false;
  }
  
  bool phone::operator>(const phone& T) const throw() {
  
		if (_compt > T._compt) return true;
		else if (_compt == T._compt) return _nom > T._nom;
		
		return false;
  }
  
  bool phone::operator<=(const phone& T) const throw() {
		return not (*this > T);
  }
  
  bool phone::operator>=(const phone& T) const throw() {
		return not (*this < T);
  }

