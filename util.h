


#ifndef UTIL_H
#define UTIL_H

#pragma warning(disable : 4786)


#include <iostream>
#include <fstream>
#include <set>
#include <string> 
#include <map>
#include <list>
#include <vector>
#include <algorithm>

using std::set;
using std::string;
using std::map;
using std::pair;
using std::list;
using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::make_pair;
using std::ostream;
using std::boolalpha;


#include "type.h"


extern vectorSentence         __CuptFile;

extern int __tagS;
extern int __tagW;
extern int __tagName;
extern int __tagPc;
extern int __tagLinkGrp;
extern int __tagLink;

extern long int __tagS_Globale;
extern long int __tagW_Globale;
extern long int __tagName_Globale;
extern long int __tagPc_Globale;
extern long int __tagLinkGrp_Globale;
extern long int __tagLink_Globale;

extern void aggiornaStat(string nomeTag);



string substr_special(string s); //caratteri speciali xml


string itoa(int g);

string tagOpen(string tag);                    //ritorna <tag>
string tagClose(string tag);                   //ritorna </tag>
string tagOpenWith(string tag,string attr);    //ritorna <tag attr=
string tagClose();                             //ritorna > 

string pairAttrVal(string attr, string value); //ritorna la string " attr=value" sse value != empty()
string virg(string s);//mette s tra virgolette 
string space(int c);//ritorna una stringa con c spazi 


string toLower(string s);

bool complexWord(string id);
int numSubWord(string msd);

string lookStartNextAfterComplex(listEntryCupt& elem, listEntryCupt::iterator from, int look);
//from punta a un elemento complesso (prep art o clit):
//ritorna il valore associato a start_char della word successiva
//look mi dice da quanti elementi è formata la parola puntata da from



//bool lookJoinUltimoElemento(listEntryCupt& elem, listEntryCupt::iterator from, int look);
//guarda il campo join di elem[from+look] e ritorna il suo valore

string substrxy(string s,string x,string y);
bool openDir(string __OutputDir);

string addIdProgressivo(string xmlId, int n); // ritorna la stringa xmlId.n

string selectInit(string misc);//misc è di questa forma: start_char=x|end_char=y
string selectEnd(string misc);//misc è di questa forma: start_char=x|end_char=y

void printSeg(ostream& out, int offset, string xmlIdVal, vectorSentence& __segCupt);
void printSentence(ostream& out, int offset, string xmlIdVal, listEntryCupt& elem, listLink& linkGrp);
void printElem(ostream& out, int offset, string xmlIdVal, entryCupt& entrata);
void printElemComposto(ostream& out, int offset, string xmlIdVal, entryCupt& entrata); 
//stampa l'elemento in cui al campo id c'è il trattino (preposizione articolare o clitici)
void closeElemComposto(ostream& out, int offset);//chiude il tag <w>
void printElemInternoAlComposto(ostream& out, int offset, string xmlIdVal, entryCupt& entrata);
//stampa degli elementi che compongono un elemento complesso (preposizione articolata o clitico)
void printLink(ostream& out, int offset, listLink& linkGrp, string xmlId);

void printStat(ostream& out, int offset);
void printStatGlobale(ostream& out, int offset);

void printInclude(ostream& out, string nomeFileAna);

void openNamed(ostream& out, string tag, int offset);//apre il tag <name>
void closeNamed(ostream& out, int offset);//chiude il tag <name>

string creaTarget(string xmlId, string head, string dipen);

string tagBIO(string named);

#endif
