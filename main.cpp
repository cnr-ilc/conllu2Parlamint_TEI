


#include "main.h"


  
void aggiornaStat(string nomeTag) {

	if (nomeTag == "s") 
	{
		__tagS++;
		__tagS_Globale++;
	}
	else 
	if (nomeTag == "w") 
	{
		__tagW++;
		__tagW_Globale++;
	}
	else 
	if (nomeTag == "link") 
	{
		__tagLink++;
		__tagLink_Globale++;
	}
	else 
	if (nomeTag == "linkGrp") 
	{
		__tagLinkGrp++;
		__tagLinkGrp_Globale++;
	}
	else 
	if (nomeTag == "pc") 
	{
		__tagPc++;
		__tagPc_Globale++;
	}
	else 
	if (nomeTag == "name") 
	{
		__tagName++;
		__tagName_Globale++;
	}
	
	
};
void clearStat() {

	__tagS = 0;
    __tagW = 0;
    __tagName = 0;
    __tagPc = 0;
    __tagLinkGrp = 0;
    __tagLink = 0;

}

listEntryCupt marca(listEntryCupt elem, listEntryCupt::iterator p, listEntryCupt::reverse_iterator q){

//cerr << "marca: " << p->id << " " << q->id<< endl;

	listEntryCupt result;

	bool inserisci = false;

	listEntryCupt::iterator x;
	for(x = elem.begin(); x != elem.end(); ++x)
	{
		if (x->id == p->id) 
		{
			inserisci = true;
		};
		if (inserisci) 
		{
			result.push_back(*x);
		};
		if (x->id == q->id) 
		{
			inserisci = false;
		};

	}
//cerr << "marca end" << endl;

	return result;
}

   



int parsaCupt(const char* file) {



    ifstream fc;
	string textline;
	string campo;
    string::size_type idx;
	string::size_type idy;
	int base;
    int ntab;
	
	string idProgressivo;
	string forma;
	string dummy;
	string radice;
	string posSpec; // part of speech specifica

	bool concatena = false;
	bool elisione = false;
	

	stringstream __frase;

    fc.open(file);
    if (!fc) 
	{
		cerr << endl << "Non posso leggere " << file << endl;
		return 0;
	}

	
	while (getline(fc,textline,'\n')) 
	{
 //__frase << "TTTT" << textline.find("# ") << textline  << endl;
	   
       //finita la frase si va a capo e si memorizza la frase
	   if (textline.empty()) 
	   {
		  __frase << endl;
		   continue;
	   }

       base = 0;
       ntab = 0;
       idx = textline.find('\t');
	   while (idx != string::npos) {
		  campo = textline.substr(base,idx-base);
          //cout << campo << " # " ;
		  switch (ntab) {
		     case 0:  idProgressivo = campo;break;
             case 1:  forma = campo;break;
			 case 2:  dummy = campo;break;
			 case 3:  dummy = campo;break;
			 case 4:  posSpec = campo;break;
			 case 5:  dummy = campo;break;
			 default:  break;
             };
	     base = idx+1;
	     idx = textline.find('\t',base);
		 ++ntab;
		 };

	   //si controlla se siamo in presenza di una forma con clitico
	   idy = forma.find("-");
	   if (idy + 1 == forma.size()
	   &&  forma.size() > 3)
	   {
		   concatena = true;
		   radice = forma.substr(0,idy);
		   continue;
	   }
	   else 
	   {
		   //si stampa la forma corrente se non va concatenata
		   if (concatena)
		   {
			   //cout << radice << forma << " ";
			   __frase << radice << forma << " ";
			   concatena = false;
			   continue;
		   }
	   }

	   //siamo in presenza di una preposizione articolata
	   idy = idProgressivo.find("-");
	   if (idy != string::npos) 
	   {
		   //caso aprticolare di prep articolata elisa
		   if (forma.find("'") == forma.size() - 1) elisione = true;
		   //caso preposizione articolate: si saltano le due linee successive
		   getline(fc,textline,'\n');
		   getline(fc,textline,'\n');
		   /*** verifico che se idProgressivo è della forma "x-y" allora x+1=y
		   cout << textline << endl;
		   string uno = idProgressivo.substr(0,idy); 
		   string due = idProgressivo.substr(idy+1);
           if (atoi(uno.c_str()) + 1 != atoi(due.c_str())) cout << "#### " << textline << endl;
		   ***/
	   }

	   //caso generale di elisione
       if (forma.find("'") == forma.size() - 1
	   &&  (  posSpec == "RD"
	       || posSpec == "RI"
	       || posSpec == "PC"
	       || posSpec == "E"
	       || posSpec == "B"
	       || posSpec == "DD"
	        ) 
	   ) 
	   {
		   elisione = true;
	   }
		  

	   //stampa senza spazio...
	   if (elisione)
	   {
		   //nel caso di elisione non si mette lo spazio perché freeling non la riconosce 
		   //per esempio freeling tagga bene "dall'alto" ma non "dall' alto"
		   //cout << forma;
		   __frase << forma;
		   elisione = false;
		   continue;
	   }

	   //...o per default con lo spazio   
       //cout << forma << " ";
	   __frase << forma << " ";
	};
     

	fc.close();

	//cout << __frase.str();

	__frase.seekg(std::ios_base::beg);
    while (getline(__frase,textline,'\n')) 
	{
		__testoRicostruito.push_back(textline);
	}

    return 1;
};


int parsaCuptToStruct(const char* file) {

//cerr <<  "parsaCuptToStruct " << file << endl;

    ifstream fc;
	string textline;
	string campo;
    string::size_type idx;
	int base;
    int ntab;
	
	entryCupt entrata;
	link     relazione;
	sentence frase;
	
    fc.open(file);
    if (!fc) 
	{
		cerr << endl << "Non posso leggere " << file << endl;
		return 0;
	}

	    
	while (getline(fc,textline,'\n')) 
    {
 //cout << textline << endl;
	   
	   //finita la frase
	   if (textline.empty())
	   {
		   //si settano i campi join :: bisognava vedere tutta la frase!
		   listEntryCupt::iterator  p;	   
           for(p = frase.elem.begin();p != frase.elem.end(); ++p) 
		   {
			   if (complexWord(p->id)
			   && (selectEnd(p->misc) == lookStartNextAfterComplex(frase.elem,p,numSubWord(p->id)+1)) )
			   {
				   p->join = true;
			   }
			   else p->join = (selectEnd(p->misc) == lookStartNextAfterComplex(frase.elem,p,1));
	       };
		   __CuptFile.push_back(frase);
		   frase.clear();
		   continue;
	   }

       base = 0;
       ntab = 0;
       idx = textline.find('\t');
	   while (idx != string::npos) 
	   {
		  campo = textline.substr(base,idx-base);
          //cout << campo << " # " ;
		  switch (ntab) 
		  {
			 case 0:  entrata.id = campo;break;
			 case 1:  entrata.form = substr_special(campo);break;
			 case 2:  entrata.lemma = substr_special(campo);break;
			 case 3:  entrata.upos = campo;break;
			 case 4:  entrata.xpos = campo;break;
			 case 5:  entrata.feats = campo;break;
			 case 6:  entrata.head = campo;break;
			 case 7:  entrata.deprel = campo;break;
			 case 8:  entrata.deps = campo;break;
			 case 9:  entrata.misc = campo;break;//misc  è di questa forma: start_char=x|end_char=y
			 case 10:  entrata.named = campo;break;//qui non entra
		  };
	      base = idx+1;
	      idx = textline.find('\t',base);
		  ++ntab;
	   };

	   relazione.name = substrxy(entrata.deprel,":","_");
	   relazione.dipen = entrata.id;
	   relazione.head = entrata.head;

	   __depRel.insert(relazione.name);

	   entrata.named = textline.substr(base);

	   frase.elem.push_back(entrata);
	   if (relazione.name != "_") frase.linkGrp.push_back(relazione);
if (relazione.name == "root" 
&& relazione.head != "0")	   cerr << "Warning Root with head = " << relazione.head << " in: " << file << endl;
	}
    
   
	//prima di uscire immette l'ultima frase.
	if (frase.elem.size() > 0) __CuptFile.push_back(frase);

	fc.close();

    return 1;
};

string nomeFileInput(string nomeFile) {

	//toglie la directory se c'è al nome del file
	string::size_type idx;
	idx = nomeFile.rfind('/');
	if (idx != string::npos) nomeFile = nomeFile.substr(idx + 1);

	//toglie l'estensione ".ud.udner" se c'è al nome del file
	idx = nomeFile.rfind(".ud.udner");
	if (idx != string::npos) nomeFile = nomeFile.substr(0, idx);

	//togle l'estensione ".xml" se c'è al nome del file
	idx = nomeFile.rfind(".xml");
	if (idx != string::npos) nomeFile = nomeFile.substr(0, idx);

	return nomeFile;
};

string dirFileInput(string nomeFile) {

	//toglie la directory se c'è al nome del file
	string::size_type idx;
	idx = nomeFile.rfind('/');
	if (idx != string::npos) nomeFile = nomeFile.substr(0,idx);

	return nomeFile;
};

void completaSentence(string nomeFile) {

   nomeFile = nomeFileInput(nomeFile);

   int id = 1;
   vectorString::iterator  p;
   vectorSentence::iterator  q;
   for(p = __testoRicostruito.begin(),q = __CuptFile.begin(); p != __testoRicostruito.end(); ++p, ++q, ++id) 
   {
	   q->testo  = *p;
	   char ss[8];
	   itoa(id,ss,10);
	   string id_progressivo(ss);
	   q->source = nomeFile + "." + id_progressivo;
	}


};

string estraiSeg(string textline) {
//textline inizia a meno di spazi per "<seg "
//ritorna ".segxxx" con xxx numero del segmento
	
//cerr <<  "estraiSeg: " << textline << endl; 

    string::size_type idx;
	string::size_type idy;

	idx = textline.find("xml:id=\"");
	idy = textline.find("\">");

	if (idx != string::npos
	&&  idy != string::npos
	&&  idx < idy)
	{
//cerr <<  " == " << textline.substr(idx+8,idy-(idx+8)) << endl;
		return textline.substr(idx+8,idy-(idx+8));
	}
	else
	{
		return "error";
	}

}; 

string generaNomeFileSeg(string dir,string nomeFile,string seg) {

	
	//return __DIR + nomeFile + "." + seg + ".ud.udner";

	//modifica 13.04.2021 cambio:
	//return dir + nomeFile + "__" + seg + ".ud.udner";
	//in: 
	return dir + seg + ".ud.udner";
}; 




void ManageXmlCompleto(const char* file, ostream& out) {

    ifstream fc;
	string textline;
    string::size_type idx;

	string nomeFile = nomeFileInput(file);
	string __DIR_BASE = dirFileInput(file);
	//string __DIR_BASE_UDNER = __DIR_BASE + "/udner__" + nomeFile + "/";
	string __DIR_BASE_UDNER = __DIR_BASE + "/" + nomeFile + "/";

	int __offset = 10;

	string seg; //segmento corrente
	string nfs; //nome file del segmento corrente
	
	
	fc.open(file);
    if (!fc) 
	{
		cerr << endl << "Non posso leggere " << file << endl;
		return;
	}

	//modifica 31.03.2021 della seconda linea dell'input
	if (getline(fc,textline,'\n')) out << textline << endl;
    if (getline(fc,textline,'\n')) 
	{
		idx = textline.find("\" xml:lang=");
		if (idx != string::npos) 
		{
			textline = textline.substr(0,idx) + ".ana" + textline.substr(idx);
		}
		out << textline << endl;
	}

	//modifica 31.03.2021 della sesta e settima linea dell'input //sostituisco [ParlaMint] con [ParlaMint.ana]
	if (getline(fc, textline, '\n')) out << textline << endl;
	if (getline(fc, textline, '\n')) out << textline << endl;
	if (getline(fc, textline, '\n')) out << textline << endl;
	if (getline(fc, textline, '\n'))
	{
		idx = textline.find("]</title>");
		if (idx != string::npos)
		{
			textline = textline.substr(0, idx) + ".ana" + textline.substr(idx);
		}
		out << textline << endl;
	};
	if (getline(fc, textline, '\n'))
	{
		idx = textline.find("]</title>");
		if (idx != string::npos)
		{
			textline = textline.substr(0, idx) + ".ana" + textline.substr(idx);
		}
		out << textline << endl;
	};
	    
	while (getline(fc,textline,'\n')) 
    {
 //cout << textline << endl;

		idx = textline.find("<seg ");
	    if (idx != string::npos)
	    {
		    seg = estraiSeg(textline);
			nfs = generaNomeFileSeg(__DIR_BASE_UDNER,nomeFile,seg);
			parsaCuptToStruct(nfs.c_str()); 
            printSeg(out, __offset , nomeFileInput(nfs), __CuptFile);
			__CuptFile.clear();
	    }
		else
		{
			//modifica 31.03...................................
			idx = textline.find("1388</idno>");
			if (idx != string::npos)
			{
				textline = textline.substr(0, idx) + "1405</idno>";
			}
			out << textline << endl;
		}
	}
}


void aggiungiStat(stringstream& out) {

	//long pos;
    //stringstream stat;
	string::size_type idx;
	stringstream copia;

	bool trovato = false;
    
    string textline;
	string elem;

	//while (elem != "</namespace>") 
	//while (elem != "<TEI") 
	while (!trovato && getline(out,textline,'\n'))	
	{
//cerr << "textline : " << textline << endl;
		idx = textline.find("</namespace>");
		if (idx != string::npos) 
		{
			printStat(copia, 10);
			trovato = true;
			copia << textline << endl;
		}
		else copia << textline << endl;
	}

	while (getline(out,textline,'\n'))	
	{
//cerr << "textline : " << textline << endl;
		copia << textline << endl;
	}


	out.str(std::string()); //azzera lo stringstream
//cerr << "LENGHT copia: " << (copia.str()).size() << endl;

	//out << copia.str();
    out.str(copia.str());  // ok, così lo copia!!

//cerr << "LENGHT out: " << (out.str()).size() << endl;

	//pos = out.tellp();
//cerr << "long pos == " << pos << endl;
	//printStat(stat, 10);

    //out.seekp(pos);
    //out << stat.str();
}



void gestore(const char* file, stringstream& out) {

//se è un file xml lo passa a ManageXmlCompleto()


    ifstream fc;
	string textline;
    string::size_type idx;
	
	fc.open(file);
    if (!fc) 
	{
		cerr << endl << "Non posso leggere " << file << endl;
		return;
	}

	string __DIR_BASE = dirFileInput(file);
//cerr << "__DIR_BASE : " << __DIR_BASE << endl;

	if (!__DIR_BASE.empty()) __DIR_BASE += "/";

	while (getline(fc,textline,'\n')) 
    {
//cerr << "textline : " << textline << endl;
		idx = textline.find(".xml");
	    if (idx != string::npos)  
	    {
//cerr << endl << "analizzo : " << textline << endl;
			ManageXmlCompleto((__DIR_BASE + textline).c_str(),out);
            aggiungiStat(out);
			writeOnFile(__DIR_BASE + nomeFileInput(textline) + ".ana.xml" ,out.str());
//printInclude(cerr, nomeFileInput(textline) + ".ana.xml");
//printStatGlobale(cerr, 10);
			out.str(std::string()); //ripulisce lo stringstream
			out.clear();
			clearStat();//e azzera le statistiche
	    }
		else
		{
			//non fa nulla
		}
	}
	printStatGlobale(cerr, 10);
}

int main(int argc,char* argv[]) {

/*****/	
   
	stringstream sout;

   // parsing della riga di comando.
	if (argc != 2) { //si memorizza in arg0 il nome dell'exec (senza path)
	//if (argc != 3) { //si memorizza in arg0 il nome dell'exec (senza path)
	                 string arg0 = argv[0];
	                 string::size_type idx;
					 idx = arg0.rfind('\\');
					 arg0 = arg0.substr(idx+1);
	                 cerr << endl 
		                  << "Usage: " << endl 
						  << "$ "
						  << arg0
						  //<< " input "
						  //<< " imputXmlCompleto "
						  << " ls_anno_sedute "
						  << endl
                          << endl;
	                 return -1;}

   
   
   //parsaCuptToStruct(argv[1]); 
   //parsaCupt(argv[1]);   
   //completaSentence(argv[1]); // il nome del file è anche il valore da dare all'attributo "xml:id" del tag "seg" 
   //printSeg(cout, 4 , nomeFileInput(argv[1]), __CuptFile);
   
   //ManageXmlCompleto(argv[1],cout);
  
// _________________________________________________________________________________
//
//    Assumo che l'eseguibile stia sotto Release e 
//    che ci siano sotto relase le cartelle: 
//    2013, 2014, ... , 2020
//    ognuna contenente varie sedute xml 
//    con associate le anaili in conll dei segmenti che la costituiscono, 
//    residenti in una cartella con lo stesso nome della seduta preceduta da "udner_"
//___________________________________________________________________________________


	gestore(argv[1],sout);
	//gestorePerControlloErroriUdner(argv[1], sout);

   //printTestoRicostruito(cerr);
   //printCuptOriginale(cout);

	setString::iterator  p;
	for (p = __depRel.begin(); p != __depRel.end(); ++p)
	{
//		cerr << "# " << *p << " @" << endl;
	}

 
  
   return 1;
};




void printTestoRicostruito(ostream& out) 
{
   vectorString::iterator  p;
   for(p = __testoRicostruito.begin(); p != __testoRicostruito.end(); ++p) 
   {
	   out << *p << endl;
	}
} 

void printCuptOriginale(ostream& out)
{
   vectorSentence::iterator  p;
   for(p = __CuptFile.begin(); p != __CuptFile.end(); ++p) 
   {
	   p->print(out);
	}
};


void writeOnFile(string nomeFile,string corpoXml) {

//cerr << "------ writeOnFile(): " << nomeFile << endl;


	ofstream file;
    
	file.open(nomeFile.c_str());
    if (!file) 
	{ 
cerr << endl << "------ Non posso aprire " << nomeFile << endl;
		return;
	}

	file << corpoXml.c_str();

	file.close();

};


void controlloErroriUdner(string ref, ostream& out) {

	bool complexInName = false;

	int n = 1;

	vectorSentence::iterator  q;
	for (q = __CuptFile.begin(); q != __CuptFile.end(); ++q,n++)
	{
		listEntryCupt frase = q->elem;
		listEntryCupt::iterator  p;
		for (p = frase.begin(); p != frase.end(); ++p)
		{
			if (complexInName)
			{
				if (p->named == "-") 
				{
					out << "@WARNING: ComplexInNamed...... ref: " << ref  << " frase: " << n  << " id: " << p->id << endl;
				}
				complexInName = false;
			}
			if (complexWord(p->id)
			&& p->named != "-")
			{
				//out << "__INIT_POTENTIAL_WARNING: ComplexInNamed...... " << seduta << " ## " << p->id << " @@ " << p->named << endl;
				complexInName = true;
			}
		}
	}

};

void gestorePerControlloErroriUdner(const char* file,  stringstream& out) {

	ifstream fc;
	string textline;
	string::size_type idx;

	fc.open(file);
	if (!fc)
	{
		cerr << endl << "Non posso leggere_1 " << file << endl;
		return;
	}

	string __DIR_BASE = dirFileInput(file);
	//cerr << "__DIR_BASE : " << __DIR_BASE << endl;

	if (!__DIR_BASE.empty()) __DIR_BASE += "/";

	while (getline(fc, textline, '\n'))
	{
		//cerr << "textline : " << textline << endl;
		idx = textline.find(".xml");
		if (idx != string::npos)
		{
			//cerr << endl << "analizzo : " << textline << endl;
			string __file = (__DIR_BASE + textline).c_str();
			
			ifstream __fc;
			string __textline;
			string::size_type __idx;

			string nomeFile = nomeFileInput(__file);
			string __DIR_BASE = dirFileInput(__file);
			//string __DIR_BASE_UDNER = __DIR_BASE + "/udner__" + nomeFile + "/";
			string __DIR_BASE_UDNER = __DIR_BASE + "/" + nomeFile + "/";

			string seg; //segmento corrente
			string nfs; //nome file del segmento corrente

			__fc.open(__file);
			if (!__fc)
			{
				cerr << endl << "Non posso leggere_2 " << __file << endl;
				return;
			}
				
			while (getline(__fc, __textline, '\n'))
			{
//cout << "$$$ " << __textline << endl;
				__idx = __textline.find("<seg ");
				if (__idx != string::npos)
				{
					seg = estraiSeg(__textline);
					nfs = generaNomeFileSeg(__DIR_BASE_UDNER, nomeFile, seg);
					parsaCuptToStruct(nfs.c_str());
					controlloErroriUdner(seg,cout);
					__CuptFile.clear();
				}	
			}
		}
	}

}

