/*
 * =====================================================================================
 *
 *       Filename:  le.cpp
 *
 *    Description:  leitura de arquivos da colecao
 *
 *        Version:  1.0
 *        Created:  08/22/14 13:49:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "le.h"
#include "util.h"

using namespace std;

Le::Le(string a_usuario,string a_item,string a_notas){
    arquivo_usuario = a_usuario;
    arquivo_item = a_item;    
    arquivo_notas = a_notas;
}

void Le::le_tudo(vector<unsigned int>& u,vector<unsigned int>& i,unordered_map< unsigned int,vector< Notas_t> >& n,unordered_map< unsigned int,vector<unsigned int> >& un){
    le_usuarios(u);
    le_itens(i);
    le_notas(n,un);
    //imprime_notas(n);
}

void Le::imprime_notas(unordered_map< unsigned int,vector< Notas_t> > n){
    unordered_map< unsigned int, vector< Notas_t> >::iterator it = n.begin();

    while (it!=n.end()){
	vector<Notas_t>::iterator it_second = it->second.begin();
	while(it_second!=it->second.end()){
	    cout<<it->first<<"\t"<<it_second->usuario_id<<"\t"<<it_second->nota<<"\t"<<it_second->timestamp<<endl;
	    it_second++;
	}
	it++;
    }

}
void Le::imprime_usuarios(vector<unsigned int> u){
    vector< unsigned int>::iterator it = u.begin();

    while (it!=u.end()){
	cout<<(*it)<<endl;
	it++;
    }

}

void Le::imprime_itens(vector<unsigned int> i){
    vector< unsigned int>::iterator it = i.begin();

    while (it!=i.end()){
	cout<<(*it)<<endl;
	it++;
    }

}

void Le::le_usuarios(vector<unsigned int>& u){
    ifstream fd_usuario(arquivo_usuario);
    vector<string> tok;

    if (fd_usuario.is_open()){
        while (!fd_usuario.eof()){
	    string linha;

	    getline(fd_usuario,linha);
	    tokenizar(linha,'|',tok);
	    if (tok.size()>0){
	        //cout<<"==> "<<linha<<" "<<tok.size()<<endl;
	        //o id do usuario sempre estara na frente
	        u.push_back(atoi(tok.front().c_str()));
	    }
	    tok.clear();
	}
        fd_usuario.close();
    }
}

void Le::le_itens(vector<unsigned int>& i){
    ifstream fd_item(arquivo_item);
    vector<string> tok;

    if (fd_item.is_open()){
        while (!fd_item.eof()){
	    string linha;

	    getline(fd_item,linha);
	    tokenizar(linha,'|',tok);
	    if (tok.size()>0){
	       //o id do filme sempre estara na frente
	       i.push_back(atoi(tok.front().c_str()));
	    }
	    tok.clear();
	}
        fd_item.close();
    }
}

void Le::le_notas(unordered_map< unsigned int,vector<Notas_t> >& n,unordered_map< unsigned int,vector<unsigned int> >& un){
    ifstream fd_item(arquivo_notas);
    vector<string> tok;

    if (fd_item.is_open()){
        while (!fd_item.eof()){
	    string linha;
	    Notas_t r;

	    getline(fd_item,linha);
	    tokenizar(linha,'\t',tok);

	    //cout<<"--> "<<tok.size()<<endl;

	    if (tok.size()>0){

		//TODO: converter os tipos a partir de string
		string ts = tok.back();
		tok.pop_back();
		r.timestamp = atol(ts.c_str());

		string ns = tok.back();
		tok.pop_back();
		r.nota = atoi(ns.c_str());

		string is = tok.back();
		tok.pop_back();

		string us = tok.back();
		r.usuario_id = atoi(us.c_str());
		tok.pop_back();

		//mapeando por item
		n[atoi(is.c_str())].push_back(r);
		//mapeando por usuario
		un[r.usuario_id].push_back(r.nota);

		tok.clear();
	    }
	}
        fd_item.close();
    }
}
