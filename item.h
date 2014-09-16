/*
 * =====================================================================================
 *
 *       Filename:  item.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/14 16:22:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unordered_map>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>  
#include "le.h"

using namespace std;

#ifndef __ITEM_H_
#define __ITEM_H_

class Item{
    unordered_map<unsigned int,float> media;    
    public:
        //computa a media de nota de cada usuario
	void computa_media_usu(unordered_map< unsigned int,vector<unsigned int> >& un);
	//dado um item a e um item b, retorna as respectivas intersecoes a_out 
	//e b_out com relação aos usuarios em comum. Precisa retornas duas 
	//saidas, pq embora tenham os usuarios em cum iguais, as notas atribuidas 
	//para cada item eh diferente
        void intersecao(unsigned int a,unsigned int b,unordered_map<unsigned int, vector<Notas_t> > n,vector<Notas_t>& a_out,vector<Notas_t>& b_out);
	float computa_sim(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> >& n);
        void  escreve_similaridades(vector<unsigned int> i,unordered_map<unsigned int, vector<Notas_t> > n);

	//funcoes de teste
	void imprime_media();
};

#endif
