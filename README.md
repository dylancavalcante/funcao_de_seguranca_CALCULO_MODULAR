#Cálculo Modular e Exponenciação Eficiente (QUESTÃO 9 PROVA)

| Aluno: Dylan Portela Cavalcante | Matrícula: 231026984 |


Este programa realiza cálculos de divisão modular e exponenciação eficiente usando o Teorema de Euler/Fermat. Ele é útil para resolver problemas em criptografia, teoria dos números e algoritmos modulares.

## 📜 Como executar?
Apenas compile o arquivo functions.c com o compilador disponível em sua máquina para linguagem c e preencha os parâmetros.

---

## 🛠️ Funcionalidades Principais
1. **Cálculo de inverso modular** (usando o Algoritmo Estendido de Euclides).
2. **Verificação de coprimalidade** (MDC entre números).
3. **Teste de primalidade** (para aplicar o Teorema de Fermat).
4. **Cálculo da função totiente de Euler** (φ(n)).
5. **Exponenciação modular eficiente** (método binário).

---

## 📥 Entradas do Programa
| Parâmetro | Descrição | Exemplo |
|-----------|------------|---------|
| **`H`** | Numerador da divisão modular. | `38` |
| **`G`** | Denominador da divisão modular. Deve ser coprimo com `n`. | `79` |
| **`n`** | Módulo para a divisão `H⊘G`. | `252` |
| **`x`** | Expoente para a exponenciação final. | `100` |
| **`n1`** | Módulo final para o cálculo `a^x mod n1`. | `7` |

---

## 📜 Funções e Estrutura do Código

### Estrutura `DadosEntrada`
Armazena todos os dados do processo:
```c
typedef struct {
    int H, G, n, x, n1;         // Entradas do usuário
    int a;                       // Resultado da divisão modular (a = H/G mod n)
    int antigo_G, antigo_n;      // Valores originais de G e n
    int *lista_n, *lista_quocientes; // Usados no Algoritmo de Euclides
    int tamanho;                 // Número de passos no Euclides
    int gcd_a_n1, n1_prime;      // Resultados das verificações
    int x1, q, r;                // Decomposição do expoente
    long long a_x1, a_x1_q, a_r; // Valores intermediários
    long long resultado;         // Resultado final
} DadosEntrada;

