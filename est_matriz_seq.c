#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int lin, col; // Define as variáveis de índices e dimensões
#define IDX(i, j) i * lin + j

void bubble_sort (double *matriz, int tam) {
    int i, j; 
    double aux;

    for (i = tam - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (matriz[j] > matriz[j+1]) {
                aux =matriz[j];
                matriz[j]=matriz[j+1];
                matriz[j+1]=aux;
            }
        }
    }
}

void ordena_colunas(double* matriz, int lin, int col) {
    int i;
    
    for (i = 0; i < col; i++) {    
        //manda o endereco do primeiro elemento da coluna, limites inf e sup e a largura da matriz
        bubble_sort(&matriz[i*lin], lin);
    }
} 

void calcula_mediana(double *matriz, double *vet, int lin, int col) {  
     int i=0;
     if((lin-1)%2){ //Quantidade par de elementos
         for (i = 0; i < col; i++) {
            vet[i]=(matriz[(((i*lin)+(i+1)*lin)-1)/2]+matriz[((((i*lin)+(i+1)*lin)-1)/2)+1]);
            vet[i]*=0.5;
            
         }
     }
     else{ //Quantidade ímpar de elementos
         for (i = 0; i < col; i++) {
            vet[i]=matriz[(((i*lin)+(i+1)*lin)-1)/2];
         }
     }
    
 } 

void calcula_moda(double *matriz, double *moda){
    int i, j; 
	double curr_number, moda_number;
	int curr_count, max_count;

	for(i = 0; i < col; i++){
		moda_number = -1;
		max_count = 1;

		curr_number = matriz[IDX(i, 0)];
		curr_count = 1;
        for(j = 1; j < lin; j++){

			if(curr_number == matriz[IDX(i, j)]){
				curr_count++;
				if(curr_count > max_count){
					max_count = curr_count;
					moda_number = curr_number;
				}
			}else{
				curr_number = matriz[IDX(i, j)];
				curr_count = 1;
			}
        }
		moda[i] = moda_number;
    }
}


void calcula_medias(double* matriz, double* medias){
    int i,j;
    double soma_media, soma_harmonica;
    for(i = 0; i < col; i++){

		soma_media = 0;
		soma_harmonica = 0;

        for(j = 0; j < lin; j++){
			const double val = matriz[IDX(i, j)];
            soma_media += val;
            soma_harmonica += (((double)1) / val);
        }

        medias[2 * i] = soma_media / (double) lin; 
        medias[2 * i + 1] = ((double) lin) / soma_harmonica; 
    }   
}

void calcula_variancias(double *matriz, double *medias, double *variancias){
    int i,j;
    double soma;
    for(i = 0; i < col; i++){
        soma = 0;
        for(j = 0; j < lin; j++){
            soma += pow((matriz[IDX(i, j)] - medias[2 * i]),2);
        }
        variancias[3 * i] = soma / (double) (lin - 1); 
		variancias[3 * i + 1] = sqrt(variancias[3 * i]);
		variancias[3 * i + 2] = variancias[3 * i + 1] / medias[2 * i];
    } 
}


int main(int argc,char **argv){
    fscanf(stdin, "%d ", &lin); // Lê a quantidade de linhas da matriz
    fscanf(stdin, "%d\n", &col); // Lê a quantidade de colunas da matriz
    
    double *matriz=(double*) malloc(lin * col * sizeof(double)); // Aloca a matriz

	// Aloca o vetor de media e media harmônica
    double *medias = (double*) malloc(2 * col * sizeof(double)); 
	
	// Aloca o vetor de variância, desvio padrão e coeficiente de variação respectivamente
	// [3 * i] = variância
	// [3 * i + 1] = desvio padrão
	// [3 * i + 2] = coeficiente de variação
    double *variancias = (double*) malloc(3 * col * sizeof(double)); 
	
    double *mediana = (double *) malloc(col * sizeof(double)); // Aloca o vetor de mediana
    double *moda = (double *) malloc(col * sizeof(double)); // Aloca o vetor de moda


	int i, j;
    for(i = 0; i < lin; i++){
        for(j = 0; j < col; j++){
            fscanf(stdin, "%lf ",&(matriz[j*lin+i])); // Lê os dados transpostos em uma matriz de entrada
        }
    }
	printf("\nLida a entrada. Calculando...\n");

    calcula_medias(matriz, medias);
    calcula_variancias(matriz, medias, variancias);

    ordena_colunas(matriz, lin, col);
    calcula_mediana(matriz, mediana, lin, col);
    calcula_moda(matriz, moda);

    for(i = 0; i < col; i++)
        printf("%.1lf ", medias[2 * i]); // Imprime as médias aritméticas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf ",medias[2 * i + 1]); // Imprime as médias harmônicas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf ",mediana[i]); // Imprime as medianas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf ",moda[i]); // Imprime as modas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf ", variancias[3 * i]); // Imprime as variâncias amostrais de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf ", variancias[3 * i + 1]); // Imprime os desvios padrão de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf ", variancias[3 * i + 2]); // Imprime os coeficientes de variação de cada coluna
    printf("\n");

    // Desaloca memória
    free(matriz);
    free(medias);
    free(mediana);
    free(moda);
    free(variancias);
}
