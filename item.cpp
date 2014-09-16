/*
 * =====================================================================================
 *
 *       Filename:  item.cpp
 *
 *    Description:  Arquivo que contem classes e funcoes para computar a 
 *    similaridade entre itens
 *
 *        Version:  1.0
 *        Created:  09/12/14 16:21:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "item.h"	

void Item::computa_media_usu(unordered_map< unsigned int,vector<unsigned int> >& un){
    unordered_map< unsigned int,vector<unsigned int> >::iterator it_u = un.begin();

    while (it_u!=un.end()){
	vector<unsigned int>::iterator it_r = (*it_u).second.begin();
	float m = 0;
	while(it_r!=(*it_u).second.end()){
	    m += (*it_r);
	    it_r++;
	}
	m  = m / (*it_u).second.size();

	media[(*it_u).first] = m;

	it_u++;
    }
}

void Item::imprime_media(){
   unordered_map< unsigned int,float>::iterator it = media.begin();

   while (it != media.end()){
       cout<<it->first<<" "<<it->second<<endl;
       it++;
   }
}


//dado um item a e um item b, retorna as respectivas intersecoes a_out 
//e b_out com relação aos usuarios em comum. Precisa retornas duas 
//saidas, pq embora tenham os usuarios em cum iguais, as notas atribuidas 
//para cada item eh diferente
void Item::intersecao(unsigned int a,unsigned int b,unordered_map<unsigned int, vector<Notas_t> > n,vector<Notas_t>& a_out,vector<Notas_t>& b_out){
    vector<Notas_t>::iterator it_a = n[a].begin();

    while (it_a != n[a].end()){
        vector<Notas_t>::iterator it_b = n[b].begin();

	while (it_b != n[b].end()){
	   // cout<<"--> "<<(*it_a).usuario_id <<" "<< (*it_b).usuario_id<<endl;
	    if ((*it_a).usuario_id == (*it_b).usuario_id){
		a_out.push_back((*it_a));
		b_out.push_back((*it_b));
	    }
	    it_b++;
	}

	it_a++;
    }
}

float Item::computa_sim(unsigned int a,unsigned int b,unordered_map< unsigned int,vector<Notas_t> >& n){

    vector<Notas_t>  inter_a,inter_b;

    intersecao(a,b,n,inter_a,inter_b);

    if (inter_a.size() == 0) return 0;

    float denominadora = 0;
    float denominadorb = 0;
    float numerador = 0;
    for(int i=0;i<inter_a.size();i++){
	unsigned int ua = inter_a[i].usuario_id;
	float mediaua = media[ua];
	numerador += (inter_a[i].nota-mediaua)*(inter_b[i].nota-mediaua);
	denominadora += (inter_a[i].nota-mediaua)*(inter_a[i].nota-mediaua); 
	denominadorb += (inter_b[i].nota-mediaua)*(inter_b[i].nota-mediaua); 
    }


    return (numerador)/(sqrt(denominadora)*sqrt(denominadorb));
}

void Item::escreve_similaridades(vector<unsigned int> i,unordered_map<unsigned int, vector<Notas_t> > n){
    //computa a similaridade entre todos os itens
    vector<unsigned int>::iterator it_a = i.begin();
    vector<unsigned int>::iterator it_b;

    ofstream sim_fd("sim.txt",ios::out);
    for (;it_a!=i.end();it_a++){
	for(it_b=it_a+1;it_b!=i.end();it_b++){
	    float s = computa_sim((*it_a),(*it_b),n);
	    sim_fd << setprecision(5) << s<<endl;
	}
    } 
    sim_fd.close();
}

