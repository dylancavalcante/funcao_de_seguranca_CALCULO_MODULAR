#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    int H;
    int G;
    int n;
    int x;
    int n1;
    int a;
    int antigo_G;
    int antigo_n;
    int *lista_n;
    int *lista_G;
    int *lista_quocientes;
    int tamanho;
    int gcd_a_n1;
    int n1_prime;
    int x1;
    int q;
    int r;
    long long a_x1;
    long long a_x1_q;
    long long a_r;
    long long resultado;
}DadosEntrada;

// Protótipos das funções
DadosEntrada recebe_valores();
DadosEntrada calcula_mdc(DadosEntrada dados);
DadosEntrada calcula_inverso(DadosEntrada dados);
DadosEntrada verifica_coprimalidade(DadosEntrada dados);
DadosEntrada verifica_primalidade(DadosEntrada dados);
DadosEntrada calcula_x1(DadosEntrada dados);
DadosEntrada decompoe_x(DadosEntrada dados);
long long mod_pow(long long base, int exp, int mod);
DadosEntrada calcula_exponenciacao(DadosEntrada dados);


DadosEntrada recebe_valores(){
    DadosEntrada dados;

    dados.lista_n = NULL;
    dados.lista_quocientes = NULL;

printf("Digite o valor de H:\n");
scanf("%d", &dados.H);


printf("Digite o valor de G:\n");
scanf("%d", &dados.G);
dados.antigo_G = dados.G; 


printf("Digite o valor de n:\n");
scanf("%d", &dados.n);
dados.antigo_n = dados.n;


printf("Digite o valor de x:\n");
scanf("%d", &dados.x);


printf("Digite o valor de n1:\n");
scanf("%d", &dados.n1);

return dados;
}

DadosEntrada calcula_mdc(DadosEntrada dados){
    int quociente = 0;
    int resto = 0; 
    dados.tamanho = 0;
    int n = dados.n;
    int G = dados.G;

    printf("\n--- CALCULO DE MDC ---\n");
    printf("Com os valores que vc forneceu, primeiramente vamos calcular se %d * %d^-1 e possivel:\n", dados.H, G);

    
    while (n % G != 0){
        quociente = n/G;
        resto = n%G;
        printf("%d = %d * %d + %d\n", n, G, quociente, resto);


        //Contador para saber quantas equações foram no total
        dados.tamanho++;
        dados.lista_n = (int *)realloc(dados.lista_n, dados.tamanho *sizeof(int));
        
        dados.lista_quocientes = (int *)realloc(dados.lista_quocientes, dados.tamanho *sizeof(int));

        dados.lista_n[dados.tamanho - 1] = n;
        dados.lista_quocientes [dados.tamanho - 1] = quociente;

        if (dados.lista_quocientes == NULL || dados.lista_n == NULL){
            printf("houve erro de realocacao de memoria");
            exit(1);
        }

        n = G;
        G = resto;
    }

    if (resto != 1){
        printf("Nao existe inverso do numero %d no dominio %d. Tente outro numero ao inves de %d", dados.antigo_G, dados.antigo_n, dados.antigo_G);
        exit(1);
    }
    else{
        printf("%d * %d^-1 e possivel pois o mdc(%d, %d) = 1\n",dados.antigo_n,dados.antigo_G,dados.antigo_n,dados.antigo_G);
    }
    return dados;
}

DadosEntrada calcula_inverso(DadosEntrada dados ){
    printf("\n--- CALCULO DE INVERSO (algoritmo de euclides) ---\n");
    printf("\nAgora vamos calcular o numero inverso de %d :\n", dados.antigo_G);
    //Calculando inverso
    int n_original = dados.antigo_n;
    int coef_n =0;
    int coef_G = 1;

    for (int i = dados.tamanho -1; i >=0; i--){
    int temp = coef_n;
    coef_n = coef_G;
    coef_G = temp - coef_G * dados.lista_quocientes[i];
    printf("%d = %d - %d * %d\n", coef_G, temp, coef_G, dados.lista_quocientes[i]);
    }

    if (coef_G < 0){
        coef_G += n_original;
    }
    printf("\no inverso de %d no universo Z %d e: %d\n", dados.antigo_G,dados.antigo_n, coef_G);
    dados.a = ((dados.H*coef_G) % n_original);
    printf("\nO resultado da conta final:\n");
    printf("(%d/%d) mod %d = (%d * %d^-1) mod %d = (%d * %d) mod %d \n", dados.H, dados.antigo_G, dados.antigo_n, dados.H, dados.antigo_G, dados.antigo_n, dados.H, coef_G, dados.antigo_n);
    printf("= %d\n", dados.a);

    return dados;

}
DadosEntrada verifica_coprimalidade(DadosEntrada dados) {
    int a = dados.a, b = dados.n1;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    dados.gcd_a_n1 = a;
    
    printf("\n--- COPRIALIDADE a e n1 ---\n");
    if (dados.gcd_a_n1 != 1) {
        printf("[AVISO] a (%d) e n1 (%d) têm MDC %d\n", 
              dados.a, dados.n1, dados.gcd_a_n1);
    } else {
        printf("a e n1 sao coprimos (MDC = 1)\n");
    }
    return dados;
}

DadosEntrada verifica_primalidade(DadosEntrada dados) {
    int n = dados.n1;
    if (n <= 1) dados.n1_prime = 0;
    else if (n <= 3) dados.n1_prime = 1;
    else if (n % 2 == 0 || n % 3 == 0) dados.n1_prime = 0;
    else {
        dados.n1_prime = 1;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                dados.n1_prime = 0;
                break;
            }
        }
    }
    
    printf("\n--- PRIMALIDADE DE n1 ---\n");
    printf("%d e primo? %s\n", dados.n1, dados.n1_prime ? "Sim" : "Nao");
    return dados;
}

DadosEntrada calcula_x1(DadosEntrada dados) {
    if (dados.n1_prime) {
        dados.x1 = dados.n1 - 1;
        printf("\n--- CALCULO DE x1 (Fermat) ---\n");
        printf("x1 = %d - 1 = %d\n", dados.n1, dados.x1);
    } else {
        int n = dados.n1;
        int result = n;
        for (int p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                result -= result / p;
            }
        }
        if (n > 1) result -= result / n;
        dados.x1 = result;
        printf("\n--- CALCULO DE x1 (Euler) ---\n");
        printf("φ(%d) = %d\n", dados.n1, dados.x1);
    }
    return dados;
}

DadosEntrada decompoe_x(DadosEntrada dados) {
    dados.q = dados.x / dados.x1;
    dados.r = dados.x % dados.x1;
    printf("\n--- DECOMPOSICAO DE x ---\n");
    printf("%d = %d * %d + %d\n", dados.x, dados.x1, dados.q, dados.r);
    return dados;
}

long long mod_pow(long long base, int exp, int mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

DadosEntrada calcula_exponenciacao(DadosEntrada dados) {
    printf("\n--- EXPONENCIACAO MODULAR ---\n");
    dados.a_x1 = mod_pow(dados.a, dados.x1, dados.n1);
    printf("a^x1 mod n1 = %lld\n", dados.a_x1);
    
    dados.a_x1_q = mod_pow(dados.a_x1, dados.q, dados.n1);
    printf("(a^x1)^q mod n1 = %lld\n", dados.a_x1_q);
    
    dados.a_r = mod_pow(dados.a, dados.r, dados.n1);
    printf("a^r mod n1 = %lld\n", dados.a_r);
    
    dados.resultado = (dados.a_x1_q * dados.a_r) % dados.n1;
    return dados;
}

int main() {
    DadosEntrada dados = recebe_valores();
    dados = calcula_mdc(dados);
    dados = calcula_inverso(dados);
    dados = verifica_coprimalidade(dados);
    dados = verifica_primalidade(dados);
    dados = calcula_x1(dados);
    dados = decompoe_x(dados);
    dados = calcula_exponenciacao(dados);

    printf("\n--- RESULTADO FINAL ---\n");
    printf("(%lld * %lld) mod %d = %lld\n", 
           dados.a_x1_q, dados.a_r, dados.n1, dados.resultado);

    free(dados.lista_n);
    free(dados.lista_quocientes);
    
    
    return 0;
}