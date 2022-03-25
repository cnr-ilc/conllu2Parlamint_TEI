


#include "util.h"


string substr_special(string s) {

	//cerr << s << " --substr_special--> "; 

	string result;
	string::size_type idx;

	for (int i = 0; i != s.size(); ++i)
	{
		if (s[i] == '<')  result += "&lt;";
		else
			if (s[i] == '>')  result += "&gt;";
			else
				if (s[i] == '\'') result += "&apos;";
				else
					if (s[i] == '"')  result += "&quot;";
					else
						if (s[i] == '&')
						{
							if (s.find("&amp;") == i
								|| s.find("&lt;") == i
								|| s.find("&gt;") == i
								|| s.find("&apos;") == i
								|| s.find("&quot;") == i)
								result += "&";
							else result += "&amp;";
						}
						else result += s[i];
	};

	//if (s != result) cerr << s << " --substr_special--> " << utf8toLatin(result.c_str()) << endl; ;
	//cerr << result << "#" << endl; 

	return result;
}




string substrxy(string s,string x,string y) {

	string::size_type idx;
	
	idx = s.find(x);
    if (idx == string::npos) 
	{
	}
	else 
	{
		return s.substr(0,idx) + y + substrxy(s.substr(idx+x.size()),x,y);
	}

	return s;
};


#include <locale>

#include <sys/stat.h>
#include <sys/types.h>

//#if defined(__OS_WIN)
#if defined(_WIN32)
#include <io.h> 
#endif


bool openDir(string __OutputDir) {

//cerr << "------ openDir(): " << __OutputDir << endl;

    if (!__OutputDir.empty()) 
	{
#if defined(__OS_LINUX) 
        if (access(__OutputDir.c_str(), 0) == 0) //linux do not know  _access() nor <io.h> [but it know access()] 
#else 
		__OutputDir = substrxy(__OutputDir,"/","\\");
        if (_access(__OutputDir.c_str(), 0) == 0) //windows know _access()
#endif
       {
            struct stat status;
            stat(__OutputDir.c_str(), &status);
            if (status.st_mode & S_IFDIR) 
			{
//cerr << "------ The directory exists." << endl; 
                return true;
            } 
			else 
			{
//cerr << "------ The path you entered is a file." << endl;
				return false;
            }
        } 
		else 
		{
//cerr << "------ Path doesn't exist." << endl;
            string command("mkdir ");
            command += __OutputDir;
//cerr << "------ exe system call" << endl;
            system(command.c_str());
//cerr << "------ end system call" << endl;
            return true;

        }
        //cerr << "Setting up finalPaths with output directory:     " << __OutputDir << endl << endl;
              

    } 
	else 
	{
       return false;
    }

}

string toLower(string s) {
     std::transform(s.begin(),s.end(),
               s.begin(),
               tolower);
  
     return s;
};


string pairNotEmpty(string attr, string value) {
//ritorna la string " attr=value" sse value != empty()

	return ((value.empty()) ? "" : " " + attr + "=" + virg(value));

}


string virg(string s) {
//mette s tra virgolette 

	return "\"" + s + "\"";
}


string space(int c) {
//ritorna una stringa con c spazi 

     string result;
     for(int i =0; i < c; ++i) result += " ";

	 return result;

}


string tagOpen(string tag) {
	return "<" + tag + ">"; 
};
string tagClose(string tag) {
	return "</" + tag + ">"; 
};
string tagOpenWith(string tag,string attr) {

	aggiornaStat(tag);

	return "<" + tag + " " + attr + "="; 
};
string tagClose() {
	return ">"; 
};



string selectInit(string misc) {//misc è di questa forma: start_char=x|end_char=y
	
	string::size_type idx;
	string::size_type idy;

	idx = misc.find("=");
    idy = misc.find("|");
	if (idx != string::npos
	&&  idx != string::npos) 
	     return misc.substr(idx+1,idy-(idx+1));
	else return "errorSelectInit";

};
string selectEnd(string misc) {//misc è di questa forma: start_char=x|end_char=y

	string::size_type idx;

	idx = misc.find("end_char=");
    if (idx != string::npos) 
	     return misc.substr(idx+9);
	else return "errorSelectEnd";
}




string addIdProgressivo(string xmlId, int n) {
	
   char ss[8];
   itoa(n,ss,10);
   string ncast(ss);
   return xmlId + "." + ncast;

};
       
/***************
bool lookJoinUltimoElemento(listEntryCupt& elem, listEntryCupt::iterator from, int look) {

//cerr << "lookJoinUltimoElemento da: " << from->id << endl;
	listEntryCupt::iterator q;
	for(q = from; q != elem.end() & look != 0; --look)
	{
		++q;
	}

//cerr << "lookJoinUltimoElemento a: " << q->id << endl;
//if (q->join) cerr << "join == true" << endl; else cerr << "join == false" << endl;

	return q->join;
}
************/

  
bool complexWord(string id) {
//cerr << "complexWord: " << id << endl;

	string::size_type idy;
	idy = id.find("-");

    return (idy != string::npos);

};


int numSubWord(string msd) {

//cerr << "numSubWord of: " << msd;

	string::size_type idy;
	string spanInit;
	string spanEnd;

	int x;//int corrispondente a spanInit
	int y;//int corrispondente a spanEnd

	int result = 0;

	idy = msd.find("-");
	if (idy != string::npos)
	{
		//caso preposizione articolate e clitici	
		spanInit = msd.substr(0,idy);
		spanEnd  = msd.substr(idy+1);
		x = atoi(spanInit.c_str());
		y = atoi(spanEnd.c_str());
		result = y-x+1;
		if (result <= 0) cerr << "warning span: " << msd << endl;
	};

//cerr << " ....is: " << result << endl;

	return result;

};

	


string lookStartNextAfterComplex(listEntryCupt& elem, listEntryCupt::iterator from, int look) {

//cerr << "lookStartNextAfterComplex da: " << from->id << endl;
	listEntryCupt::iterator q;
	for(q = from; (q != elem.end()) && (look != 0); --look)
	{
		++q;
	}

//if (q != elem.end()) cerr << "lookStartNextAfterComplex a: " << q->id << " ----> " <<  selectInit(q->misc) << endl;

return ((q != elem.end()) ? selectInit(q->misc) : "finita");
}

void printSeg(ostream& out, int offset, string xmlIdVal , vectorSentence& __segCupt) {

	int n = 1;

	out << space(offset);
	out << tagOpenWith("seg","xml:id");
    out << virg(xmlIdVal);
	out << tagClose();
    out << endl;

	vectorSentence::iterator  p;
    for(p = __segCupt.begin(); p != __segCupt.end(); ++p) 
    {
		 printSentence(out, offset + 4, addIdProgressivo(xmlIdVal,n++),p->elem,p->linkGrp);
	};

	out << space(offset);
	out << tagClose("seg");
	out << endl;

};


void openNamed(ostream& out, string tag, int offset) {
//apre il tag <name> 
//tag è della forma B-xxx
	out << space(offset);
	out << tagOpenWith("name","type");
	out << virg(tag.substr(2));
	out << tagClose();
    out << endl;
}

void closeNamed(ostream& out, int offset) {
//chiude il tag <name>
	out << space(offset);
	out << tagClose("name");
	out << endl;
}

string tagBIO(string named) {

	string::size_type idy;

	idy = named.find("B-");
	if (idy == 0) return "B-";

    idy = named.find("I-");
	if (idy == 0) return "I-";

	return "--";

}; 

void printSentence(ostream& out, int offset, string xmlIdVal, listEntryCupt& elem, listLink& linkGrp) {

	int n = 1;
	string::size_type idy;

	string spanInit;
	string spanEnd;

	int x;//int corrispondente a spanInit
	int y;//int corrispondente a spanEnd

	//__________________________________Var per l'automa che tratta la named entity recognition______________

	enum stato {STATO__0, STATO__1};

	stato s = STATO__0;
	int rientro = 3;
	string t; 

	//________________________________________________________________________________________________________

	bool internal = false; //true sse siamo all'interno di elemnti composti (prep art o clit)
	int elemDaStampare = 0; //mi dice quanti elementi ci sono ancora da stampere 
	                       //normalmente sono 2: (caso prep art)
                          //possono essere anche 3 nel caso dei clitici

	out << space(offset);
	out << tagOpenWith("s", "xml:id");
	out << virg(xmlIdVal);
	out << tagClose();
	out << endl;

	listEntryCupt::iterator p;
	for(p = elem.begin(); p != elem.end(); ++p) 
	{
		//________Automa per la gestione della Named Entity Recognition
        
		t = tagBIO(p->named);

		switch (s)
		{
		case STATO__0:
		    if (t == "B-")
			{
				openNamed(out,p->named,offset+4);
				offset += rientro;
				s = STATO__1;
			}
			else //t == "--"
			{
				//non si fa nulla
				//s = STATO_0;
			};
			break;
	    case STATO__1 : 
			if (t == "B-")
			{
				//closeNamed(out,offset-rientro+4);
				//openNamed(out,p->named,offset-rientro+4);
				if (!internal) closeNamed(out,offset-rientro+4);
				if (!internal) openNamed(out,p->named,offset-rientro+4);
				//s = STATO__1
			}
			else
			if (t == "I-")
			{
				//non si fa nulla
				//s = STATO_1;
			} 
			else //t == "--"
			{
				//offset -= rientro;
				//closeNamed(out,offset+4);
				//s = STATO__0;
				if (!internal) offset -= rientro;
				if (!internal) closeNamed(out, offset + 4);
				if (!internal) s = STATO__0;
			};
			break;
		};

		//_____________________________________________________________

		//gestione preposizioni articolate e clitici
		idy = p->id.find("-");
		if (idy != string::npos)
		{//caso preposizione articolate e clitici
			spanInit = p->id.substr(0,idy);
			spanEnd  = p->id.substr(idy+1);
			x = atoi(spanInit.c_str());
			y = atoi(spanEnd.c_str());
		    elemDaStampare = y-x+1;
			if (elemDaStampare <= 0) cerr << "warning span: " << xmlIdVal + p->id << endl;
/******  Non serve più 18.03.2011
			if (lookJoinUltimoElemento(elem,p,elemDaStampare)) p->join = true;
//if ( p->join) cerr << "p->join == true" << endl; else cerr << "p->join == false" << endl;
*******/
			printElemComposto(out, offset + 4, xmlIdVal + "." + p->id,*p);
			internal = true;
			
		}
		else 
		{
			if (internal)
			{
				 printElemInternoAlComposto(out, offset + 7, addIdProgressivo(xmlIdVal,n++),*p);
				 --elemDaStampare;
				 if (elemDaStampare == 0) 
				 {
					 //chiude il tag (corripondente all'entrata il cui id ha il trattino) rimasto in sospeso 
					 out << space(offset +4);
					 out << tagClose("w");
	                 out << endl;
					 internal = false;
				 };
			}
			else printElem(out, offset + 4, addIdProgressivo(xmlIdVal,n++),*p);
		}
        
	}

if (s == STATO__1) 
{
	closeNamed(out,offset-rientro+4);
	cerr << "WARNING name entity not close: " <<  xmlIdVal << endl;
}
	printLink(out, offset + 4,linkGrp,xmlIdVal);
	out << space(offset);
	out << tagClose("s");
	out << endl;
};
void printElem(ostream& out, int offset, string xmlIdVal, entryCupt& entrata) {
   
	//ci sarebbe da aggiungere qui printNameEntity()
	// o dentro printSentence?!?!

	
	//cerr << entrata.upos << " " << entrata.lemma << endl;

	if (entrata.upos == "PUNCT")
	{
		out << space(offset);
	    out << tagOpenWith("pc","xml:id");
        out << virg(xmlIdVal);

		out << endl;
		out << space(offset + 3);
		out << pairNotEmpty("pos",entrata.xpos);

		if (entrata.feats == "_")
			 out << endl << space(offset + 3) << pairNotEmpty("msd", "UPosTag=" + entrata.upos);
		else out << endl << space(offset + 3) << pairNotEmpty("msd", "UPosTag=" + entrata.upos + "|" + entrata.feats);

		if (entrata.join) 
		{
			out << endl;
		    out << space(offset + 3);
		    out << pairNotEmpty("join","right");
		}

	    out << tagClose();
		out << entrata.form;
        out << tagClose("pc");	
        out << endl;
	}
	else 
	{
		out << space(offset);
	    out << tagOpenWith("w","xml:id");
        out << virg(xmlIdVal);

		out << endl;
		out << space(offset + 2);

		out << pairNotEmpty("lemma",entrata.lemma);

		out << endl;
		out << space(offset + 2);

		out << pairNotEmpty("pos",entrata.xpos);

		if (entrata.join) 
		{
			out << endl;
		    out << space(offset + 2);
		    out << pairNotEmpty("join","right");
		}

		out << endl;
		out << space(offset + 2);

		if (entrata.feats == "_")
			 out << pairNotEmpty("msd", "UPosTag=" + entrata.upos);
		else out << pairNotEmpty("msd","UPosTag=" + entrata.upos + "|" + entrata.feats);

	    out << tagClose();
		out << entrata.form;
        out << tagClose("w");	
        out << endl;
	}

};


void printElemComposto(ostream& out, int offset, string xmlIdVal, entryCupt& entrata) {
//stampa l'elemento in cui al campo id c'è il trattino (preposizione articolare o clitici)
//dal chiamante va chiuso il tag
	out << space(offset);
	out << tagOpenWith("w","xml:id");
    out << virg(xmlIdVal);
	if (entrata.join) 
		{
			out << endl;
		    out << space(offset + 2);
		    out << pairNotEmpty("join","right");
		}
    out << tagClose();
	out << entrata.form;
    out << endl;

}; 

void closeElemComposto(ostream& out, int offset) {

	out << space(offset);
    out << tagClose("w");	
    out << endl;
};

void printElemInternoAlComposto(ostream& out, int offset, string xmlIdVal, entryCupt& entrata) {
//stampa degli elementi che compongono un elemento complesso (preposizione articolata o clitico)

    out << space(offset);
	out << tagOpenWith("w","xml:id");
//aggiunta 20.04.2021
	__tagW_Globale--;
    __tagW--;
//Fine aggiunta: 
//praticamente dentro tagOpenWith() e solo lì, viene chiamata aggiornaStat() che incrementa il tag di apertura,
//in questo caso __tagW_Globale e __tagW:
//li decremnto in modo  da annullare l'incremento!
    out << virg(xmlIdVal);	
	out << endl;

	out << space(offset + 2);
	out << pairNotEmpty("norm",entrata.form);
	out << endl;

	out << space(offset + 2);
	out << pairNotEmpty("lemma",entrata.lemma);
	out << endl;

	out << space(offset + 2);
	out << pairNotEmpty("pos",entrata.xpos);
	out << endl;

	out << space(offset + 2);
	if (entrata.feats == "_")
	     out << pairNotEmpty("msd", "UPosTag=" + entrata.upos);
	else out << pairNotEmpty("msd","UPosTag=" + entrata.upos + "|" + entrata.feats);
	out << "/";
	out << tagClose();
	out << endl;
};


string creaTarget(string xmlId, string head, string dipen) {

	string result;
	string headCompleto;
	string dipenCompleto;

	if (head == "0") 
		 headCompleto = "#" + xmlId;
	else headCompleto = "#" + xmlId + "."  + head;
    
	dipenCompleto = "#" + xmlId + "." + dipen;

	return (headCompleto + " " + dipenCompleto);

};

void printLink(ostream& out, int offset, listLink& linkGrp, string xmlId) {

	
	out << space(offset);
	out << tagOpenWith("linkGrp", "targFunc");
	out << virg("head argument");
	out << pairNotEmpty("type","UD-SYN");
	out << tagClose();
	out << endl;
	listLink::iterator q;
	for(q = linkGrp.begin(); q != linkGrp.end(); ++q) 
    {
		out << space(offset+3);
	    out << tagOpenWith("link","ana");
	    out << virg("ud-syn:" + q->name);
		out << endl;
		out << space(offset+3+5);
	    out << pairNotEmpty("target",creaTarget(xmlId,q->head,q->dipen));
	    out << "/";
	    out << tagClose();
	    out << endl;	
	}
	out << space(offset);
    out << tagClose("linkGrp");
	out << endl;
    
};


string itoa(int g) {

	char ss[8];
	itoa(g,ss,10);
	string result(ss);

	return result;
};

void printStat(ostream& out, int offset)  {

//out << endl << "printStat::::::::: " << endl;	

	if (__tagS != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("s");
	    out << pairNotEmpty("occurs",itoa(__tagS));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagW != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("w");
	    out << pairNotEmpty("occurs",itoa(__tagW));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagName != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("name");
	    out << pairNotEmpty("occurs",itoa(__tagName));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagPc != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("pc");
	    out << pairNotEmpty("occurs",itoa(__tagPc));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagLinkGrp != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("linkGrp");
	    out << pairNotEmpty("occurs",itoa(__tagLinkGrp));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagLink != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("link");
	    out << pairNotEmpty("occurs",itoa(__tagLink));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};

    
};

void printStatGlobale(ostream& out, int offset)  {

//out << endl << "printStat::::::::: " << endl;	

	if (__tagS_Globale != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("s");
	    out << pairNotEmpty("occurs",itoa(__tagS_Globale));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagW_Globale != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("w");
	    out << pairNotEmpty("occurs",itoa(__tagW_Globale));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagName_Globale != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("name");
	    out << pairNotEmpty("occurs",itoa(__tagName_Globale));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagPc_Globale != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("pc");
	    out << pairNotEmpty("occurs",itoa(__tagPc_Globale));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagLinkGrp_Globale != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("linkGrp");
	    out << pairNotEmpty("occurs",itoa(__tagLinkGrp_Globale));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};
    if (__tagLink_Globale != 0)
	{
		out << space(offset);
	    out << tagOpenWith("tagUsage", "gi");
	    out << virg("link");
	    out << pairNotEmpty("occurs",itoa(__tagLink_Globale));
	    out << "/";
	    out << tagClose();
	    out << endl;
	};

    
};

void printInclude(ostream& out, string nomeFileAna)  {

	int offset = 2;
	
	out << space(offset);
	out << "<xi:include xmlns:xi=\"http://www.w3.org/2001/XInclude\"";
	out << endl;
	out << space(offset);
	out << pairNotEmpty("href",nomeFileAna);
	out << "/";
	out << tagClose();
	out << endl;

    
};