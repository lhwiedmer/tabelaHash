Implementação da tabela hash

Luiz Henrique Murback Wiedmer - GRR20221234

1. Estruturas de Dados
Não foi utilizada uma estrutura de dadso para representar a tabela em si, ao invés disso foi utilizado um vetor de ponteiros para listas duplamente encadeadas. Essas listas possuem um ponteiro para nodoHash que representa seu início e outro ponteiro do mesmo tipo para o seu final. Já os nodos tem um inteiro como chave, um ponteiro para o nodo anterior e outro para o próximo.

2. Funções

2.1. Hash
A função de hash retorna um size_t que é o mod(resto da divisão inteira) entre a chave k e o tamanho da tabelaHash.  

2.2. Inserir
A função recebe um vetor de ponteiros para listaHash, que representa a tabelaHash, um inteiro sem sinal que é o tamanho do vetor de ponteiros e uma chave inteira que será inserida.
Ela primeiramente verifica se o ponteiro presente no indice do vetor calculado pelo hash está apontando para NULL ou para uma lista, caso seja para NULL a lista é incializa, e caso contrário, a chave a ser inserida é buscada na tabelaHash já que duplicatas não são aceitas. Caso já haja um nodo com a chave na tabela, a função termina e retorna NULL. Caso contrário, cria um nodo com a chave passada como parâmetro e o insere no fim da lista de índice calculado pela função de hash.

2.3. Buscar
A função recebe um vetor de ponteiros para listaHash, que representa a tabelaHash, um inteiro sem sinal que é o tamanho do vetor de ponteiros e uma chave inteira que será buscada.
Ela busca pela chave na lista de índice calculado pela função hash. Caso o nodo com a chave seja encontrado ele é retornado, caso contrário é retornado NULL.
 
2.4. Excluir
A função recebe um vetor de ponteiros para listaHash, que representa a tabelaHash, um inteiro sem sinal que é o tamanho do vetor de ponteiros e um ponteiro para o nodoHash que será excluído.

2.4.1. Único nodo da lista
Início e fim da lista passam a apontar para NULL e o nodo atual é excluído.

2.4.2. Primeiro nodo da lista
O início da lista passa a ser o próximo nodo, o ponteiro para o nodo anterior do próximo nodo passa a apontar para NULL e o nodo atual é excluído.

2.4.3. Último nodo da lista
O fim da lista passa a ser o nodo anterior, o ponteiro para o próximo nodo do nodo anterior passa a apontar para NULL e o nodo atual é excluído.

2.4.4. Entre dois nodos
O nodo anterior e o próximo nodo são conectados e o nodo atual é excluído.

2.5. Imprimir
A função recebe um vetor de ponteiros para listaHash, que representa a tabelaHash e um inteiro sem sinal que é o tamanho do vetor de ponteiros.
Ela imprime inteiramente a tabelaHash, sempre com o índice ao lado da sua lista e NULL ao final, começando pela lista de índice 0 e seguindo de forma crescente até o fim da tabela. Nos casos em que não houver elementos em uma lista, é apenas escrito NULL no lugar deles.

2.6. Liberar Tabela Hash
A função recebe um vetor de ponteiros para listaHash, que representa a tabelaHash e um inteiro sem sinal que é o tamanho do vetor de ponteiros.
Libera a memória da tabelaHash, de maneira a percorrer cada lista do fim ao início, começando pela lista de índice 0 e seguindo de forma crescente até o fim da tabela.
