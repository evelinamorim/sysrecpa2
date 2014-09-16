/*
 * =====================================================================================
 *
 *       Filename:  le.h
 *
 *    Description:  le os arquivos importantes para o problema: usuarios, items e notas
 *
 *        Version:  1.0
 *        Created:  08/22/14 10:37:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

#ifndef __LE_H_
#define __LE_H_

typedef struct notas{
    unsigned int usuario_id;
    float nota;
    long unsigned int timestamp;
}Notas_t;

class Le{
    string arquivo_usuario;
    string arquivo_item;    
    string arquivo_notas;
    public:
        Le(string a_usuario,string a_item,string a_notas);

	void le_tudo(vector<unsigned int>& u,vector<unsigned int>& i,unordered_map< unsigned int,vector<Notas_t> >& n,unordered_map< unsigned int,vector<unsigned int> >& un);
	void le_usuarios(vector<unsigned int>& u);
	void le_itens(vector<unsigned int>& i);
	void le_notas(unordered_map< unsigned int,vector< Notas_t> >& n,unordered_map< unsigned int,vector<unsigned int> >& un);

	/**  funcoes de teste**/
	void imprime_notas(unordered_map< unsigned int,vector< Notas_t> > n);
	void imprime_usuarios(vector< unsigned int> u);
	void imprime_itens(vector< unsigned int> i);

};

#endif
