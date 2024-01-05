#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
  answers.push_back(easy.inici())

  for (unsigned int i = 0; i < input.size(); ++i) {
    if (input[i] == phone::ENDCHAR) {
        answers.push_back(easy.seguent(phone::ENDPREF));
      }
      else if (input[i] == phone::DELETE) {
        answers.push_back(easy.anterior());
      }
      else {
        answers.push_back(easy.seguent(input[i]));
      }
    }

    numtelf = easy.num_telf();
}
