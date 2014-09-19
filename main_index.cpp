/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  arquivo principal do sistema de recomendacao item-based
 *
 *        Version:  1.0
 *        Created:  09/15/14 10:00:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "item.h"

using namespace std;

int main(int argc,char** argv){
    string arquivoUsuario = argv[1];
    string arquivoItem = argv[2];
    string arquivoNotas = argv[3];

    if (argc != 4){
	cout<<"*** Error *** Wrong Number of Arguments "<<endl;
	cout<<"Usage: ./tp2-index userfilename itemfilename ratingfilename"<<endl;
	return -1;
	    
    }

    Le leObj(arquivoUsuario,arquivoItem,arquivoNotas); 
    vector<unsigned int> u,i;

    unordered_map< unsigned int,vector<Notas_t> > n;
    unordered_map< unsigned int,vector<Notas_usu_t> > un;

    unordered_map<unsigned int,float>  media = leObj.le_tudo(u,i,n,un);

    Item itemObj;

    itemObj.normaliza_nota(u,media,n,un);
    //itemObj.imprime_nota(un);
    //itemObj.computa_media_usu(un);
    //itemObj.imprime_media();

    itemObj.escreve_similaridades(i,n);

    return 0;
}


