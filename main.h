




#ifndef MAIN_H
#define MAIN_H



#include "type.h"
#include "util.h"
#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>


using std::stringstream;
using std::ofstream;

vectorSentence         __CuptFile;
vectorString           __testoRicostruito;

setString              __depRel;

int __tagS = 0;
int __tagW = 0;
int __tagName = 0;
int __tagPc = 0;
int __tagLinkGrp = 0;
int __tagLink = 0;


long int __tagS_Globale = 0;
long int __tagW_Globale = 0;
long int __tagName_Globale = 0;
long int __tagPc_Globale = 0;
long int __tagLinkGrp_Globale = 0;
long int __tagLink_Globale = 0;


void aggiornaStat(string nomeTag);
void clearStat();


string nomeFileInput(string file); //ritorna il nome del file di input, senza la directory e l'estensione
string dirFileInput(string nomeFile); //ritorna la directory del file di input,
string estraiSeg(string textline); //da una riga contenente "<seg " ritorna il segmento corrente
string generaNomeFileSeg(string dir,string nomeFile,string seg); //genera il nome del file fa parsare

void completaSentence(string nomeFile);//__CuptFile e  __testoRicostruito sono allineati, 
                               //finisce di settare i due attributi testo e source della sentence.
                              //nota che che è il testoRisostruito è isomorfo a quello di partenza 
                             //a meno della spaziatura: il testo esatto andrebbe costruito dal
                            //campo "misc" di ogni ha questa struttura:
                           //start_char=xxxx|end_char=yyyyy

listEntryCupt marca(listEntryCupt elem,listEntryCupt::pointer, listEntryCupt::reverse_iterator q);//ritorna la sottolista di elem da p pa q


void printTestoRicostruito(ostream& out);
void printCuptOriginale(ostream& out);



int parsaCupt(const char* f);//input in formato cupt, per ora interessa solo estrarre la sentence 
int parsaCuptToStruct(const char* f);//parsa tutto l'input in formato cupt e lo mette nelle struttura dati


void ManageXmlCompleto(const char* f, ostream& out);//parsa l'xml completo individua per ogni segmento S il file.ud 
//corrispondente da parsare e sostituisce al tag <seg> con l'ouput di printSeg() 


void gestore(const char* f, stringstream& out); 
//ora in input il programma prende la lista di file della cartella ANNO:
//ANNO è un directory (sottto directoruy di Release) appartenente a { 2013, 2014 .... 2020 }
//     - la lista di file è generata da shell con il comando:
//       ls -C > ls_ANNO.txt

int main(int,char*[]);


void writeOnFile(string nomeFile,string corpoXml);

void controlloErroriUdner(string ref, ostream& out);
void gestorePerControlloErroriUdner(const char* f, stringstream& out);

#endif