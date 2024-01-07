#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
 
    string s = easy.inici();
    answers.push_back(s);
    
    if (s == ""){
      answers.push_back("No hi ha telefons amb el prefix en curs.");
      numtelf = 0;
    }
    
    try{
      numtelf = easy.num_telf();
    }
    catch (error e){
      numtelf = 0;
    }
    
    for (unsigned int i = 0; i < input.size(); ++i) {
      try {
        if (input[i] == phone::ENDCHAR) {
          answers.push_back(easy.seguent(phone::ENDPREF));
        }
        else if (input[i] == phone::DELETECHAR) {
          answers.push_back(easy.anterior());
        }
        else{
          string s = easy.seguent(input[i]);
          if (s == ""){
            answers.push_back(" No hi ha telefons amb el prefix en curs.");
            numtelf = 0;
            easy.anterior();
            break;
          }
          else{
            answers.push_back(s);
          }
        }

        try{
          numtelf = easy.num_telf();
        }
        catch (error e){
          numtelf = 0;
        }
        
      } 
      catch (error e) {
        numtelf = 0;
        answers.clear();
        answers.push_back("");
        answers.push_back(e.mensaje());
        break;
      }
  }
  
}
