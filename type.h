


#ifndef TYPE_H
#define TYPE_H

#pragma warning(disable : 4786)


#include <iostream>
#include <set>
#include <string> 
#include <map>
#include <list>
#include <vector>

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

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
     


using std::ifstream;
using std::string;
using std::setw;
using std::set;
using std::list;
using std::map;
using std::multimap;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::getline;
//using std::pair;
//using std::make_pair;
using std::ostream;
using std::stringstream;


struct entryCupt;
struct sentence;
struct link;

typedef list<string>          listString;
typedef list<entryCupt>       listEntryCupt;
typedef list<link>            listLink;
typedef vector<sentence>      vectorSentence;
typedef vector<string>        vectorString;
typedef vector<listEntryCupt> vectorListEntryCupt;
typedef set<int>              setInt;
typedef set<string>           setString;

typedef map<int,string>       mapIntXString;
typedef map<string,int>       mapStringXInt;
typedef map<string,string>    mapStringXString;



struct link {
       
       string     name;
       string     head;
       string     dipen;

       void inline print(ostream& os) 
	   {
		    os <<  name        << '\t' 
			   <<  head        << '\t' 
			   <<  dipen       << endl;
	  };

};


struct entryCupt {
       
       string     id;
       string     form;
       string     lemma;
       string     upos;
       string     xpos;
       string     feats;
       string     head;
       string     deprel;
       string     deps;
       string     misc;
       string     named;
	   bool       join;

       void inline print(ostream& os) 
	   {
		    os <<  id          << '\t' 
			   <<  form        << '\t' 
			   <<  lemma       << '\t' 
			   <<  upos        << '\t' 
			   <<  xpos        << '\t' 
			   <<  feats       << '\t' 
			   <<  head        << '\t' 
			   <<  deprel      << '\t' 
			   <<  deps        << '\t' 
			   <<  misc        << '\t' 
			   <<  named       << endl;
	  };
                           
};       


struct sentence {
       
       string        testo;
	   string        source;
       listEntryCupt elem;
	   listLink      linkGrp;

	   void inline clear() 
	   {
		   elem.clear();
		   linkGrp.clear();
	   }
       
       void inline print(ostream& out)
	   {
		    out << source << endl;
			out << testo << endl;
            listEntryCupt::iterator p;
            for(p = elem.begin(); p != elem.end(); ++p) 
            {
				p->print(out);
			}
			listLink::iterator q;
			for(q = linkGrp.begin(); q != linkGrp.end(); ++q) 
            {
				q->print(out);
			}
			out << endl;
	   };
}; 







#endif
