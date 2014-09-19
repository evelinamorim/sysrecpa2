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

bool compara_sim(Sim_item_t a,Sim_item_t b){
    return (a.similaridade>b.similaridade);
}

Le::Le(string a_usuario,string a_item,string a_notas){
    arquivo_usuario = a_usuario;
    arquivo_item = a_item;    
    arquivo_notas = a_notas;
}

unordered_map<unsigned int,float> Le::le_tudo(vector<unsigned int>& u,vector<unsigned int>& i,unordered_map< unsigned int,vector< Notas_t> >& n,unordered_map< unsigned int,vector<Notas_usu_t> >& un){
    le_usuarios(u);
    le_itens(i);
    return le_notas(n,un);
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

unordered_map<unsigned int,float> Le::le_notas(unordered_map< unsigned int,vector<Notas_t> >& n,unordered_map< unsigned int,vector<Notas_usu_t> >& un){
    ifstream fd_item(arquivo_notas);
    vector<string> tok;
    unordered_map<unsigned int,float> media;

    if (fd_item.is_open()){
        while (!fd_item.eof()){
	    string linha;
	    Notas_t r;
	    Notas_usu_t ur;

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
		ur.item = atoi(is.c_str());

		string us = tok.back();
		r.usuario_id = atoi(us.c_str());
		tok.pop_back();

		if (media.find(r.usuario_id)!= media.end()){
		    media[r.usuario_id] += r.nota;
		}else{
		    media[r.usuario_id] = r.nota;
		}

		//mapeando por item
		//n[ur.item].push_back(r);

		//mapeando por usuario
		ur.nota = r.nota;
		ur.timestamp = r.timestamp;

		un[r.usuario_id].push_back(ur);

		tok.clear();
	    }
	}
        fd_item.close();

	unordered_map<unsigned int,float>::iterator it_media = media.begin();
	while (it_media != media.end()){
	    it_media->second = it_media->second/(un[it_media->first].size());
	    it_media++;
	}
    }

    return media;
}

void Le::le_similaridade(unordered_map<unsigned int, vector<Sim_item_t> >& sim_matrix){

    ifstream sim_arq("sim.txt",ios::in);
    vector<string> tok;

    if (sim_arq.is_open()){
        while (!sim_arq.eof()){
	    string linha;
	    Sim_item_t r;

	    getline(sim_arq,linha);
	    tokenizar(linha,' ',tok);

	    //cout<<"--> "<<tok.size()<<endl;

	    if (tok.size()>0){

		string sim12 = tok.back();
		tok.pop_back();
		r.similaridade = atof(sim12.c_str());

		string i2 = tok.back();
		tok.pop_back();
		unsigned int item2 = atoi(i2.c_str());

		string i1 = tok.back();
		tok.pop_back();
		unsigned int item1 = atoi(i1.c_str());

		//mapeando item 1
		r.item = item2;
		sim_matrix[item1].push_back(r);

		//mapeando item 2
		r.item = item1;
		sim_matrix[item2].push_back(r);

		tok.clear();
	    }
	}
        sim_arq.close();
    }

    //ordenar cada item de acordo com a similaridade
    unordered_map<unsigned int, vector<Sim_item_t> >::iterator it_sim_matrix = sim_matrix.begin();
    while (it_sim_matrix!=sim_matrix.end()){
	sort(it_sim_matrix->second.begin(),it_sim_matrix->second.end(),compara_sim);
	it_sim_matrix++;
    }

    sim_arq.close();
}
