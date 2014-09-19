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
#include <algorithm>
#include "le.h"

using namespace std;

#ifndef __ITEM_H_
#define __ITEM_H_

#define TOPITEMS 50
#define PRINTTOPITEMS 100

class Item{
    public:
        void normaliza_nota(vector<unsigned int>& u,unordered_map<unsigned int, float>& media,unordered_map<unsigned int,vector<Notas_t> >& n,unordered_map<unsigned int, vector<Notas_usu_t> >&un );
	float computa_sim(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> >& n);
        void  escreve_similaridades(vector<unsigned int> i,unordered_map<unsigned int, vector<Notas_t> > n);
       float  prediz_similaridade_item(unsigned int u,unsigned int i,unordered_map<unsigned int,vector<Notas_usu_t> >& un,unordered_map<unsigned int, vector<Sim_item_t> >& sim_matrix);
        void  prediz_similaridade(vector<unsigned int>& u, vector<unsigned int>& i, unordered_map<unsigned, vector<Notas_usu_t> >& un,unordered_map<unsigned int, vector<Sim_item_t> >& sim_matrix,unordered_map<unsigned int, float>& media);
        void escreve_predicao(unsigned int usuario,vector<Sim_item_t> si);

	//funcoes de teste
	void imprime_media(unordered_map<unsigned int,float> media);
	void imprime_nota(unordered_map<unsigned int,vector<Notas_usu_t> > un);
};

#endif
