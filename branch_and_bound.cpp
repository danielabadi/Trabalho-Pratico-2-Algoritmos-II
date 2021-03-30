#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm> 
#include <queue>
#include "no.hpp"

std::vector<std::pair<double, double>> valores_pesos;

bool ordenacao_por_valor_relativo(const std::pair<double,double> &a, const std::pair<double,double> &b){ 
    return ((a.first / a.second) >= (b.first / b.second)); 
}

bool operator<(const no& a, const no& b) { //necessario para usar a fila de prioridades, ela ordena com base no limite superior de cada no
  return a.limite >= b.limite;
}

float calcula_limite(no no_atual, int num_items, int capacidade){
	float limite = no_atual.valor;

	if (no_atual.peso >= capacidade){
        return 0; 
	}

 	if(no_atual.nivel + 1 < num_items){
        limite += (capacidade - no_atual.peso) * valores_pesos[no_atual.nivel + 1].first / valores_pesos[no_atual.nivel + 1].second; 
 	}

    return limite; 
}


float mochila(int capacidade, int num_items){
    std::priority_queue<no> fila;
    no no_atual = no(-1,0,0,0);
    fila.push(no_atual); 

   	float lucro = 0; 
    while (!fila.empty()){
        no_atual = fila.top(); 
        fila.pop(); 
        if (no_atual.nivel == num_items-1){
            if(lucro < no_atual.valor){
            	lucro = no_atual.valor;
            } 
        } else{
       		int novo_nivel = no_atual.nivel + 1; 
        	float novo_peso = no_atual.peso + valores_pesos[novo_nivel].second; 
        	float novo_valor = no_atual.valor + valores_pesos[novo_nivel].first; 
        	if (novo_peso <= capacidade && novo_valor > lucro){
            	lucro = novo_valor;
        	}
        	no prox_no_com_item = no(novo_nivel,novo_valor,novo_peso, 0); //criando novo no contendo proximo item
        	prox_no_com_item.limite = calcula_limite(prox_no_com_item, num_items, capacidade); 
			if (prox_no_com_item.limite > lucro){
            	fila.push(prox_no_com_item);
			}

			no prox_no_sem_item = no(novo_nivel, no_atual.valor, no_atual.peso, 0); //criando novo no sem proximo item
        	prox_no_sem_item.limite = calcula_limite(prox_no_sem_item, num_items, capacidade);
        	if (prox_no_sem_item.limite > lucro){
            	fila.push(prox_no_sem_item);
        	}
        }
    }
    return lucro; 
} 

int main(int argc, char* argv[]){
	double capacidade, peso, valor;
    int num_items;
	std::ifstream arq;

	if(argc < 2){
		std::cout << "Parametros insuficientes" << "\n";
		return 0;
	}
	
	arq.open(argv[1]); 
	 if(!arq.is_open()){
	 	std::cout << "Arquivo nao encontrado" << "\n";
        return 0;
    }
 
    arq >> num_items >> capacidade;
    for( int i = 0; i < num_items; i++){
    	arq >> valor >> peso;
    	valores_pesos.push_back(std::make_pair(valor, peso));
    }

    std::sort(valores_pesos.begin(),valores_pesos.end(), ordenacao_por_valor_relativo); //ordenando o vector de acordo com o valor relativo
    std::cout << mochila(capacidade, num_items) << "\n";
	return 0;
}