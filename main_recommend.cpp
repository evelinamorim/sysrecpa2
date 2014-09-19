/*
 * =====================================================================================
 *
 *       Filename:  main_recommend.cpp
 *
 *    Description:  arquivo principal que recomenda itens
 *
 *        Version:  1.0
 *        Created:  09/16/14 12:49:56
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
	cout<<"Usage: ./tp2-recommend userfilename itemfilename ratingfilename"<<endl;
	return -1;
	    
    }

    Le leObj(arquivoUsuario,arquivoItem,arquivoNotas); 
    vector<unsigned int> u,i;

    unordered_map< unsigned int,vector<Notas_t> > n;
    unordered_map< unsigned int,vector<Notas_usu_t> > un;
    unordered_map<unsigned int, vector<Sim_item_t> > sim_matrix;

    unordered_map<unsigned int,float> media = leObj.le_tudo(u,i,n,un);
    leObj.le_similaridade(sim_matrix);

    Item itemObj;

    itemObj.normaliza_nota(u,media,n,un);

    itemObj.prediz_similaridade(u,i,un,sim_matrix,media);


    return 0;
}


