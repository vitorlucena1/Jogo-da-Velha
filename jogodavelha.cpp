#include <iostream>
#include <locale.h>
#include <windows.h>
#include <time.h>
using namespace std;

void zera_tabuleiro(char *tabuleiro, int tam){
	for (int i = 0; i < tam; i++){
		for (int j = 0; j < tam; j++){
			*tabuleiro = '\0';
			tabuleiro++;
		}
	}
}
void imprime_tabuleiro(char *tabuleiro, int tam){
	for (int j = 0; j < tam; j++){
		cout << "  " << j + 1 << " ";
	}
	cout << "\n";
	for (int j = 0; j < tam; j++){
		cout << j + 1 << " ";
		for (int k = 0; k < tam; k++){
			if (*tabuleiro != '\0'){
				cout << *tabuleiro;
			}
			else
				cout << " ";
			tabuleiro++;
			if (k < tam - 1)
				cout << " | ";
		}
		cout << "\n";
		printf(" ");
		if (j < tam - 1)
			for (int a = 0; a < tam; a++){
				cout << "---";
				if (tam >= 4)
					cout << "-";
			}
		printf("\n");
	}
}

int verifica_jogada(int tam, int linha, int coluna, char *tabuleiro){
	if (linha < 1 || linha > tam || coluna < 1 || coluna > tam){
		return 0;
	}
	if (*(tabuleiro + (linha - 1) * tam + coluna - 1) != '\0'){
		return 0;
	}
	return 1;
}


int venceu_horizontal(char *tabuleiro, int tam, int vitoria) {
	int cont = 0;
    char *teste;
    for(int i = 0 ; i < tam ;i++){
            cont = 0;
        for(int j = 0 ; j < tam ;j++){
            if(j > 0)
            teste = tabuleiro + tam;
            if(j > 0)
            if(*tabuleiro != '\0'){
                if(*tabuleiro == *teste){
                    cont++;
                }
            }
            else{
                cont=0;
            }
            tabuleiro++;
            if(cont == vitoria-1){
            return 1;
            }
        }
    }
    return 0;
}

int venceu_vertical(char *tabuleiro, int vitoria, int tam) {
    int cont = 0;
    char *teste;
    for(int i = 0 ; i < tam ;i++){
            cont = 0;
        for(int j = 0 ; j < tam ;j++){
            if(j > 0)
            teste = tabuleiro - tam;
            if(j > 0)
            if(*tabuleiro != '\0'){
                if(*tabuleiro == *teste){
                    cont++;
                }
            }
            else{
                cont=0;
            }
            tabuleiro += tam;
            if(cont == vitoria - 1){
            return 1;
            }
        }
        tabuleiro -= tam*(tam-1);
        tabuleiro++;
    }
    return 0;
}

int venceu_diagonal_principal(int tam, char *tabuleiro, int vitoria){
    int cont = 0;
    char *teste;
    for(int i = 0 ; i < tam*tam; i++){
            cont = 0;
        for(int j = 0; j < tam; j++){
            if(j > 0)
            teste = tabuleiro - (tam+1);    
            if(j > 0)
            if(*tabuleiro != '\0'){
                if(*tabuleiro == *teste){
                    cont++;
                }
            }
            else{
                cont = 0;
            }
            tabuleiro += tam+1;
            if(cont == vitoria-1){
            return 1;
            }
        }
        tabuleiro -= tam * (tam-1);
        tabuleiro++;
    }
    return 0;
}

int venceu_diagonal_secundaria(int tam, char *tabuleiro, int vitoria){
    int cont = 0;
    char *teste;
    for(int i = 0; i < tam*tam; i++){
            cont = 0;
        for(int j = 0; j < tam; j++){
            if(j > 0)
            teste = tabuleiro - (tam-1);    
            if(j > 0)
            if(*tabuleiro != '\0'){
                if(*tabuleiro == *teste){
                    cont++;
                }
            }
            else{
                cont = 0;
            }
            tabuleiro += (tam-1);
            if(cont == vitoria-1){
            return 1;
            }
        }
        tabuleiro -=tam * (tam-1);
        tabuleiro++;
    }
    return 0;
}



int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "Portuguese_Brazil");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int num_jogadores;
	char imprime_nome[] = "|---------------------------|\n|*******JOGO DA VELHA*******|\n|---------------------------|\n";
	int tam = 3, gravidade;
	int linha, coluna, vitoria = 3, venceu = 0;
	cout << imprime_nome;
	cout << "Digite a quantidade de jogadores: ";
	cin >> num_jogadores;
	char nomes[num_jogadores][1000], simbolos[num_jogadores];
	for (int i = 0; i < num_jogadores; i++){
		cout << "Digite o nome do jogador " << i + 1 << ": ";
		scanf(" %[^\n]s", nomes[i]);
	}
	system("cls");
	cout << imprime_nome;
	cout << "Boa sorte aos jogadores ";
	for (int i = 0; i < num_jogadores; i++){
		cout << nomes[i];
		if (i + 1 == num_jogadores)
			break;
		cout << ", ";
	}
	cout << "! \n\n";
	for (int i = 0; i < num_jogadores; i++){
		cout << "Digite o símbolo do jogador " << nomes[i] << ": ";
		cin >> simbolos[i];
	}
	cout << "Digite o tamanho do tabuleiro: ";
	cin >> tam;
	cout << "Digite 1 se desejar ligar ou 0 para não ligar a gravidade: ";
	scanf(" %d", &gravidade);
	char tabuleiro[tam][tam];
	zera_tabuleiro(*tabuleiro, tam);
	for (int i = 0; i <= tam * tam; i++){
		SetConsoleTextAttribute(hConsole, rand() % 16 + 1);
		cout << i << endl;
		system("cls");
		cout << imprime_nome;
		imprime_tabuleiro(*tabuleiro, tam);

		if (gravidade == 1){
			cout << "Gravidade Ativada\n";
			if (i < tam * tam){
				cout << "***Vez de " << nomes[i % num_jogadores] << "***\n";
				cout << "Digite a posição para jogar: ";
				cin >> linha >> coluna;
				while(tabuleiro[linha][coluna-1] == '\0'){
				cout << "Posição inválida! Tente novamentea\n";
				cin >> linha >> coluna;
				}

				while (!verifica_jogada(tam, linha, coluna, tabuleiro[0])){
					cout << "Posição inválida! Tente novamenteb\n";
					cin >> linha >> coluna;
				}

				tabuleiro[linha - 1][coluna - 1] = simbolos[i % num_jogadores];
			}
		}
		else if (gravidade == 0){
			if (i < tam * tam){
			cout << "***Vez de " << nomes[i % num_jogadores] << "***\n";
			cout << "Digite a posição para jogar: ";
			cin >> linha >> coluna;
			while (!verifica_jogada(tam, linha, coluna, tabuleiro[0])){
				cout << "Posição inválida! Tente novamente\n";
				cin >> linha >> coluna;
			}

			tabuleiro[linha - 1][coluna - 1] = simbolos[i % num_jogadores];
				
			}

		}
		venceu = venceu_horizontal(tabuleiro[0], tam, vitoria);
        if(venceu == 0){
        	    venceu = venceu_vertical(tabuleiro[0],vitoria,tam);
        	    system("cls");
		}

        if(venceu == 0){
        	    venceu = venceu_diagonal_secundaria(tam,tabuleiro[0],vitoria);
        	    system("cls");		
		}
        if(venceu == 0){
            venceu = venceu_diagonal_principal(tam, tabuleiro[0], vitoria);
        	system("cls");
		}	
        if(venceu == 1){
         	system("cls");
			cout << imprime_nome;
        	imprime_tabuleiro(tabuleiro[0], tam);
        	cout <<"O Vencedor é: " << nomes[i % num_jogadores] <<"!";
        	break;
        }
	}

	return 0;
}