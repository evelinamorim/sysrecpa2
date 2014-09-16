/*
 * =====================================================================================
 *
 *       Filename:  util.cpp
 *
 *    Description:  implementacao de algumas funcoes uteis para este sistema
 *
 *        Version:  1.0
 *        Created:  08/22/14 14:04:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "util.h"


void tokenizar(string s,char sep,vector<string>& v){
       string::iterator it = s.begin();

       string palavra = "";
       while(it!=s.end()){

            while (it!=s.end() && *it == sep) it++;

    	    palavra = "";

	    while (it!=s.end() && *it != sep){
    	       palavra += *it;
	       it++;
	    }

    	    if (palavra.size() > 0){ 
		//cout<<">>> "<<palavra<<endl;
		v.push_back(palavra);
	    }
    	    
      }
		      
}
