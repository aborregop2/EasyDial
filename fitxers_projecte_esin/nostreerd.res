###!----------------------------------------------
###!                                              
###! MODUL DIALOG
###!
###!----------------------------------------------
###1 call_registry buit
###!----------------------------------------------
###!
#init cc01 call_registry
#dump

##
#init easi01 easy_dial cc01
#dialog ""
 No hi ha telefons amb el prefix en curs. 
0
## No hi ha telefons amb el prefix en curs. 
##0
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#dump

##
#init easi01 easy_dial cc01
#dialog "m"
 Prefix en curs indefinit. 
0
## Prefix en curs indefinit. 
##0
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###2 call_registry (1 string)
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "maria"
#r 300
#dump
300 maria 1 
##300 maria 1 
#init easi01 easy_dial cc01
#dialog ""
maria 
300
##maria 
##300
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###3 call_registry (2 strings) sense prefix en comú
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "jose"
#as 301 "maria"
#r 300
#r 300
#dump
301 maria 0 300 jose 2 
##301 maria 0 300 jose 2 
#init easi01 easy_dial cc01
#dialog ""
jose 
300
##jose 
##300
#dialog "j"
jose 
300
##jose  No hi ha telefons amb el prefix en curs. 
##0
#dialog "m"
jose maria 
301
##jose maria 
##301
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###4 call_registry (2 strings) amb un simbol en comu
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "miguel"
#as 301 "maria"
#r 300
#r 300
#dump
301 maria 0 300 miguel 2 
##301 maria 0 300 miguel 2 
#init easi01 easy_dial cc01
#dialog ""
miguel 
300
##miguel 
##300
#dialog "m"
miguel maria 
301
##miguel maria 
##301
#dialog "ma"
miguel maria 
301
##miguel maria  No hi ha telefons amb el prefix en curs. 
##0
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###5 call_registry (2 strings) amb dos simbols en comu
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "manuel"
#as 301 "maria"
#r 300
#r 300
#dump
301 maria 0 300 manuel 2 
##301 maria 0 300 manuel 2 
#init easi01 easy_dial cc01
#dialog ""
manuel 
300
##manuel 
##300
#dialog "m"
manuel maria 
301
##manuel maria 
##301
#dialog "ma"
manuel maria 
301
##manuel maria  No hi ha telefons amb el prefix en curs. 
##0
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###6 call_registry (2 strings) amb tres simbols en comu
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "maria"
#r 300
#r 300
#dump
301 maria 0 300 mar 2 
##301 maria 0 300 mar 2 
#init easi01 easy_dial cc01
#dialog ""
mar 
300
##mar 
##300
#dialog "m"
mar maria 
301
##mar maria 
##301
#dialog "ma"
mar maria 
301
##mar maria  No hi ha telefons amb el prefix en curs. 
##0
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###7 call_registry (2 strings) igual que (6) canviant les frequencies
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "maria"
#r 301
#r 301
#dump
300 mar 0 301 maria 2 
##300 mar 0 301 maria 2 
#init easi01 easy_dial cc01
#dialog ""
maria 
301
##maria 
##301
#dialog "m"
maria mar 
300
##maria mar 
##300
#dialog "ma"
maria mar 
300
##maria mar  No hi ha telefons amb el prefix en curs. 
##0
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###8 call_registry (3 strings) tots els prefixes diferents
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "antonio"
#as 301 "sara"
#as 302 "victor"
#r 300
#r 300
#r 301
#dump
302 victor 0 301 sara 1 300 antonio 2 
##302 victor 0 301 sara 1 300 antonio 2 
#init easi01 easy_dial cc01
#dialog ""
antonio 
300
##antonio 
##300
#dialog "s"
antonio sara 
301
##antonio sara 
##301
#dialog "v"
antonio victor 
302
##antonio victor 
##302
#dialog "a"
antonio 
300
##antonio  No hi ha telefons amb el prefix en curs. 
##0
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###9 call_registry (3 strings) tots els prefixes diferents canviant frequencies
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "antonio"
#as 301 "sara"
#as 302 "victor"
#r 301
#r 301
#r 302
#dump
300 antonio 0 302 victor 1 301 sara 2 
##300 antonio 0 302 victor 1 301 sara 2 
#init easi01 easy_dial cc01
#dialog ""
sara 
301
##sara 
##301
#dialog "s"
sara 
301
##sara  No hi ha telefons amb el prefix en curs. 
##0
#dialog "v"
sara victor 
302
##sara victor 
##302
#dialog "a"
sara antonio 
300
##sara antonio 
##300
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###10 call_registry (3 strings) tots els prefixes diferents canviant frequencies
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "antonio"
#as 301 "sara"
#as 302 "victor"
#r 302
#r 302
#r 301
#dump
300 antonio 0 301 sara 1 302 victor 2 
##300 antonio 0 301 sara 1 302 victor 2 
#init easi01 easy_dial cc01
#dialog ""
victor 
302
##victor 
##302
#dialog "s"
victor sara 
301
##victor sara 
##301
#dialog "v"
victor 
302
##victor  No hi ha telefons amb el prefix en curs. 
##0
#dialog "a"
victor antonio 
300
##victor antonio 
##300
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###11 call_registry (3 strings) dos prefixes = (1 simbol) i un diferent
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "victor"
#as 301 "valentin"
#as 302 "rosa"
#r 302
#r 302
#r 301
#dump
300 victor 0 301 valentin 1 302 rosa 2 
##300 victor 0 301 valentin 1 302 rosa 2 
#init easi01 easy_dial cc01
#dialog "vi"
rosa valentin victor 
300
##rosa valentin victor 
##300
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "victor"
#as 301 "valentin"
#as 302 "rosa"
#r 301
#r 301
#r 302
#dump
300 victor 0 302 rosa 1 301 valentin 2 
##300 victor 0 302 rosa 1 301 valentin 2 
#init easi01 easy_dial cc01
#dialog "r<v"
valentin rosa valentin victor 
300
##valentin rosa valentin victor 
##300
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "victor"
#as 301 "valentin"
#as 302 "rosa"
#r 300
#r 300
#r 302
#dump
301 valentin 0 302 rosa 1 300 victor 2 
##301 valentin 0 302 rosa 1 300 victor 2 
#init easi01 easy_dial cc01
#dialog "v<r"
victor valentin victor rosa 
302
##victor valentin victor rosa 
##302
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "victor"
#as 301 "valentin"
#as 302 "rosa"
#r 302
#r 302
#r 300
#dump
301 valentin 0 300 victor 1 302 rosa 2 
##301 valentin 0 300 victor 1 302 rosa 2 
#init easi01 easy_dial cc01
#dialog "va"
rosa victor valentin 
301
##rosa victor valentin 
##301
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###12 call_registry (3 strings) tres prefixes = (1 simbol)
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "victor"
#as 301 "valentin"
#as 302 "veronica"
#r 300
#r 300
#r 301
#dump
302 veronica 0 301 valentin 1 300 victor 2 
##302 veronica 0 301 valentin 1 300 victor 2 
#init easi01 easy_dial cc01
#dialog "ve"
victor valentin veronica 
302
##victor valentin veronica 
##302
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "victor"
#as 301 "valentin"
#as 302 "veronica"
#r 302
#r 302
#r 301
#dump
300 victor 0 301 valentin 1 302 veronica 2 
##300 victor 0 301 valentin 1 302 veronica 2 
#init easi01 easy_dial cc01
#dialog "vi"
veronica valentin victor 
300
##veronica valentin victor 
##300
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###13 call_registry (3 strings) tres prefixes = (3 simbols)
###!----------------------------------------------
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "mari
#as 302 "maria"
#r 300
#r 300
#r 301
#dump
302 maria 0 301 mari 1 300 mar 2 
##302 maria 0 301 mari 1 300 mar 2 
#init easi01 easy_dial cc01
#dialog "ma"
mar mari maria 
302
##mar mari maria 
##302
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "mari
#as 302 "maria"
#r 301
#r 301
#r 302
#dump
300 mar 0 302 maria 1 301 mari 2 
##300 mar 0 302 maria 1 301 mari 2 
#init easi01 easy_dial cc01
#dialog "ma"
mari maria mar 
300
##mari maria mar 
##300
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "mari
#as 302 "maria"
#r 302
#r 302
#r 301
#dump
300 mar 0 301 mari 1 302 maria 2 
##300 mar 0 301 mari 1 302 maria 2 
#init easi01 easy_dial cc01
#dialog "ma"
maria mari mar 
300
##maria mari mar 
##300
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "mari
#as 302 "maria"
#r 300
#r 300
#r 302
#init easi01 easy_dial cc01
#dialog "ma"
mar maria mari 
301
##mar maria mari 
##301
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "mari
#as 302 "maria"
#r 301
#r 301
#r 300
#init easi01 easy_dial cc01
#dialog "ma"
mari mar maria 
302
##mari mar maria 
##302
#cc01 destroy
#easi01 destroy
###!
#init cc01 call_registry
#as 300 "mar"
#as 301 "mari
#as 302 "maria"
#r 302
#r 302
#r 300
#init easi01 easy_dial cc01
#dialog "ma"
maria mar mari 
301
##maria mar mari 
##301
#cc01 destroy
#easi01 destroy
###!
###!
###!
###!----------------------------------------------
###14 call_registry (5 strings) utilitzant |
###!----------------------------------------------
###!
#init cc02 call_registry
#as 500 maria
#as 501 maruchi
#as 502 marisol
#as 503 marisa
#as 504 marimar
#as 505 mar
#r 500
#r 501
#r 502
#r 503
#r 504
#r 505
#r 500
#r 501
#r 502
#r 503
#r 504
#r 500
#r 501
#r 502
#r 503
#r 500
#r 501
#r 502
#r 500
#r 501
#r 500
#init easi02 easy_dial cc02
#dialog "mar|"
maria maruchi marisol marisa mar 
505
##maria maruchi marisol marisa mar 
##505
#cc02 destroy
#easi02 destroy
###!
###!
###!
###!----------------------------------------------
###!                                              
###15 call_registry mitja tots els recorreguts
###!
###!----------------------------------------------
###!
#init cc03 call_registry
#as 600 "jose"
#as 601 "manolo"
#as 602 "miguel"
#as 603 "mari"
#as 604 "manoli"
#as 605 "marisa"
#as 606 "marisol"
#as 607 "maria"
#as 608 "antonio"
#r 600
#r 601
#r 602
#r 603
#r 604
#r 605
#r 606
#r 607
#r 608
#r 600
#r 601
#r 602
#r 603
#r 604
#r 605
#r 606
#r 607
#r 600
#r 601
#r 602
#r 603
#r 604
#r 605
#r 606
#r 600
#r 601
#r 602
#r 603
#r 604
#r 605
#r 600
#r 601
#r 602
#r 603
#r 604
#r 600
#r 601
#r 602
#r 603
#r 600
#r 601
#r 602
#r 600
#r 601
#r 600
#init easi03 easy_dial cc03
Error::easy_dial:31:Prefix en curs indefinit.
#dialog mi<aria<<<n<<<a
