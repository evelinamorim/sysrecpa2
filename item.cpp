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

#define MIN(a,b) \
             ({ __typeof__ (a) _a = (a); \
	                      __typeof__ (b) _b = (b); \
	                    _a < _b ? _a : _b; })

#define MAX(a,b) \
             ({ __typeof__ (a) _a = (a); \
	                      __typeof__ (b) _b = (b); \
	                    _a > _b ? _a : _b; })

#define ABS(a) \
             ({ __typeof__ (a) _a = (a); \
	                    _a > 0 ? _a : -_a; })

bool compara_sim_item(Sim_item_t a,Sim_item_t b){
    return (a.similaridade>b.similaridade);
}

void Item::imprime_media(unordered_map<unsigned int,float> media){
   unordered_map< unsigned int,float>::iterator it = media.begin();

   while (it != media.end()){
       cout<<it->first<<" "<<it->second<<endl;
       it++;
   }
}

void Item::normaliza_nota(vector<unsigned int>& u,unordered_map<unsigned int, float> &media,unordered_map<unsigned int,vector<Notas_t> >& n,unordered_map<unsigned int, vector<Notas_usu_t> >& un){
    vector<unsigned int>::iterator it_u = u.begin();

    while (it_u!=u.end()){
	int tam = un[(*it_u)].size();
	for(int i=0;i<tam;i++){
	    Notas_t r;
	    un[(*it_u)][i].nota = un[(*it_u)][i].nota - media[(*it_u)];
	    unsigned int item = un[(*it_u)][i].item;
	    
	    r.usuario_id = (*it_u);
	    r.nota = un[(*it_u)][i].nota; 
	    r.timestamp = un[(*it_u)][i].timestamp; 
	    n[item].push_back(r);
	}
	it_u++;
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
	       numerador += (*it_a).nota*(*it_b).nota;
	       denominadora += (*it_a).nota*(*it_a).nota; 
	       denominadorb += (*it_b).nota*(*it_b).nota; 
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

float Item::prediz_similaridade_item(unsigned int u,unsigned int i,unordered_map<unsigned int,vector<Notas_usu_t> >& un,unordered_map<unsigned int, vector<Sim_item_t> >& sim_matrix){

    //montar top-k filmes em comum
    vector<Notas_usu_t> topitems;
    vector<float> topsim;
    vector<Sim_item_t>::iterator it_sim = sim_matrix[i].begin();
    vector<Sim_item_t>::iterator it_sim_end = sim_matrix[i].end();

    vector<Notas_usu_t>::iterator it_un_begin = un[u].begin(); 
    vector<Notas_usu_t>::iterator it_un_end = un[u].end();

    while (it_sim!=it_sim_end){

        vector<Notas_usu_t>::iterator it_un = it_un_begin; 
	bool contido = false;
        while (it_un != it_un_end){
	    if ((*it_un).item==i){
		contido = true;
		break;
	    }
	    if ((*it_un).item == (*it_sim).item){
                 topitems.push_back((*it_un));
	         topsim.push_back((*it_sim).similaridade);
	    }
	    it_un++;
        }

	if (contido){
	    //caso contrario este item nao precisa ser avaliado 
	    topitems.clear();
            break;
	} 
	if (topitems.size() == TOPITEMS)
	    break;

	it_sim++;
    }

    //montar similaridade com estes items
    bool pertence = false;
    float num = 0.0;
    float den = 0.0;

    vector<Notas_usu_t>::iterator it_topitems = topitems.begin();
    int i_topsim = 0;
    while (it_topitems != topitems.end()){
	num += topsim[i_topsim]*((*it_topitems).nota);
	den += ABS(topsim[i_topsim]);
	i_topsim++;
	it_topitems++;
    }

    if (den!=0)
        return num/den;
    else return 0;
}

void Item::prediz_similaridade(vector<unsigned int>& u, vector<unsigned int>& i,unordered_map<unsigned int,vector<Notas_usu_t> >& un,unordered_map<unsigned int, vector<Sim_item_t> >& sim_matrix,unordered_map<unsigned int, float>& media){

    vector<unsigned int>::iterator it_u = u.begin();
    vector<unsigned int>::iterator it_i;

    vector<Sim_item_t> items_similares;

    while (it_u!=u.end()){

	it_i = i.begin();

	while(it_i!=i.end()){
	      float sim_item = prediz_similaridade_item((*it_u),(*it_i),un,sim_matrix);

 	     Sim_item_t si;
	     si.item = (*it_i);
	     //nao eh similaridade. eh a nota
	     si.similaridade = round(MIN(5,media[(*it_u)]+sim_item));
	     items_similares.push_back(si); 
	    
	     it_i++;
	}
	sort(items_similares.begin(),items_similares.end(),compara_sim_item);
	escreve_predicao((*it_u),items_similares);
	items_similares.clear();
	it_u++;
    }
}

void Item::escreve_predicao(unsigned int usuario,vector<Sim_item_t> si){
    ofstream pred_fd("pred.out",ios::out|ios::app);

    int tam = MIN(PRINTTOPITEMS,si.size());
    if (pred_fd.is_open()){
	for (int i = 0;i<tam;i++){
	    pred_fd<<usuario<<" "<<si[i].item<<" "<<si[i].similaridade<<endl;
	}
        pred_fd.close();
    }
}

void Item::imprime_nota(unordered_map<unsigned int,vector<Notas_usu_t> > un){
    unordered_map<unsigned int,vector<Notas_usu_t> >::iterator it_un = un.begin();
    
    while (it_un!=un.end()){

	vector<Notas_usu_t>::iterator it_notas = it_un->second.begin();

	while(it_notas!=it_un->second.end()){
	    cout<<it_un->first<<" "<<it_notas->item<<" "<<it_notas->nota<<endl;
	    it_notas++;
	}
	it_un++;
    }
}
