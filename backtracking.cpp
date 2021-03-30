#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

std::vector<std::pair<double, double>> valores_pesos;

double mochila(int pos_vector, double peso_atual, double valor_atual, int num_items){
	if(peso_atual < 0){
		return valor_atual - valores_pesos[pos_vector-1].first;
	} else if(peso_atual == 0 || pos_vector == num_items){
		return valor_atual;
	} else {
		double novo_peso = peso_atual - valores_pesos[pos_vector].second;
		double novo_valor =  valor_atual + valores_pesos[pos_vector].first;
		double peso_1 = mochila(pos_vector+1, novo_peso, novo_valor, num_items);
		double peso_2 = mochila(pos_vector+1, peso_atual, valor_atual, num_items);
		if(peso_1 >= peso_2){
			return peso_1;
		} 
		return peso_2;
	}
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
    for(int i = 0; i < num_items; i++){
    	arq >> valor >> peso;
    	valores_pesos.push_back(std::make_pair(valor, peso));    
    }
    
    std::cout << mochila(0, capacidade, 0, num_items) << "\n";
	return 0;
}