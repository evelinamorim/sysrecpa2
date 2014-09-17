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

bool compara_sim_item(Sim_item_t a,Sim_item_t b){
    return (a.similaridade>b.similaridade);
}

void Item::computa_media_usu(unordered_map< unsigned int,vector<Notas_usu_t> >& un){
    unordered_map< unsigned int,vector<Notas_usu_t> >::iterator it_u = un.begin();

    while (it_u!=un.end()){
	vector<Notas_usu_t>::iterator it_r = (*it_u).second.begin();
	float m = 0;
	while(it_r!=(*it_u).second.end()){
	    m += (*it_r).nota;
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


float Item::computa_sim(unsigned int a,unsigned int b,unordered_map<unsigned int, vector<Notas_t> >& n){
    vector<Notas_t>::iterator it_a = n[a].begin();

    float numerador = 0;
    float denominadora = 0;
    float denominadorb = 0;
    while (it_a != n[a].end()){
        vector<Notas_t>::iterator it_b = n[b].begin();

	while (it_b != n[b].end()){
	   // cout<<"--> "<<(*it_a).usuario_id <<" "<< (*it_b).usuario_id<<endl;
	    if ((*it_a).usuario_id == (*it_b).usuario_id){
	       unsigned int ua = (*it_a).usuario_id;
	       float mediaua = media[ua];
	       numerador += ((*it_a).nota-mediaua)*((*it_b).nota-mediaua);
	       denominadora += ((*it_a).nota-mediaua)*((*it_a).nota-mediaua); 
	       denominadorb += ((*it_b).nota-mediaua)*((*it_b).nota-mediaua); 
	    }
	    it_b++;
	}

	it_a++;
    }

    if (denominadora!=0 && denominadorb!=0){
       return (numerador)/(sqrt(denominadora)*sqrt(denominadorb));
    }else{
	return 0;
    }

}


void Item::escreve_similaridades(vector<unsigned int> i,unordered_map<unsigned int, vector<Notas_t> > n){
    //computa a similaridade entre todos os itens
    vector<unsigned int>::iterator it_a = i.begin();
    vector<unsigned int>::iterator it_b;

    ofstream sim_fd("sim.txt",ios::out);
    for (;it_a!=i.end();it_a++){
	for(it_b=it_a+1;it_b!=i.end();it_b++){
	    float s = computa_sim((*it_a),(*it_b),n);
	    sim_fd << (*it_a) << " "<< (*it_b) << " " << setprecision(4) << s<<endl;
	}
    } 
    sim_fd.close();
}

void Item::prediz_similaridade(vector<unsigned int> u, vector<unsigned int> i,unordered_map<unsigned int,vector<Notas_usu_t> > un,unordered_map<unsigned int, vector<Sim_item_t> > sim_matrix){

    vector<unsigned int>::iterator it_u = u.begin();
    vector<unsigned int>::iterator it_i;

    vector<Sim_item_t> items_similares;

    while (it_u!=u.end()){

	it_i = i.begin();

	while(it_i!=i.end()){

	    //cout<<"--> "<<un.size()<<" "<<un[(*it_u)].size()<<" "<<(*it_u)<<endl;
	    vector<Notas_usu_t>::iterator it_un = un[(*it_u)].begin(); 
            bool pertence = false;
	    float num = 0.0;
	    float den = 0.0;

	    while (it_un != un[(*it_u)].end()){
		if ((*it_un).item != (*it_i)){
		    //cout<<"==> "<<(*it_un).item <<" "<< (*it_i)<<endl;
		    //cout<<">> "<<sim_matrix.size()<<" "<<sim_matrix[(*it_un).item].size()<<endl;
		    float sim_iu = sim_matrix[(*it_un).item][(*it_i)-1].similaridade;
		    //soh um teste
		    if (sim_matrix[(*it_un).item][(*it_i)].item != ((*it_i)-1)){
			cout<<"OUCH!"<<endl;
		    }
		    num += sim_iu*((*it_un).nota);
		    den += sim_iu;
		}else{
		    pertence = true;
		    break;
		}
		it_un++;
	    }
	    if (!pertence){
		Sim_item_t si;
		si.item = (*it_i);
		//nao eh similaridade. eh a nota
		si.similaridade = num/den;
		items_similares.push_back(si);
	    }
	    it_i++;
	}
	sort(items_similares.begin(),items_similares.end(),compara_sim_item);
	escreve_predicao((*it_u),items_similares);
	it_u++;
    }
}

void Item::escreve_predicao(unsigned int usuario,vector<Sim_item_t> si){
    ofstream pred_fd("pred.out",ios::out|ios::app);

    if (pred_fd.is_open()){
	for (int i = 0;i<TOPITEMS;i++){
	    pred_fd<<usuario<<" "<<si[i].item<<" "<<si[i].similaridade<<endl;
	}
        pred_fd.close();
    }
}
