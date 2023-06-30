#include <iostream>
#include <string>
#include <fstream> // Para usar arquivos .txt
#include <regex> // Para usar expressões regulares
#include "tree.h" // Inclui funções e estruturas para manipulação de árvores 

using namespace std;


// Função para criar um novo nó
struct Node* newNode(int iPayload)
{
    // Aloca memória para o novo nó
    struct Node* newNode = new struct Node; 
    // Atribui o dado ao novo nó
    newNode->iData = iPayload;
    // Atribui nullptr aos ponteiros para os nós filhos
    newNode->ptrLeft = nullptr; 
    newNode->ptrRight = nullptr;
    return newNode;
}


// Função para inserir um novo nó na árvore binária de busca
struct Node* insertNode(struct Node* ptrNode, int iPayload)
{
    // Se a árvore estiver vazia, retorna o novo nó
    if (ptrNode == nullptr)
    {
        ptrNode = newNode(iPayload);
        return ptrNode;
    }
    // Caso contrário, percorre a árvore recursivamente até encontrar a posição correta
    else if(iPayload < ptrNode->iData)
    {
        ptrNode->ptrLeft = insertNode(ptrNode->ptrLeft, iPayload);
    }
    else
    {
        ptrNode->ptrRight = insertNode(ptrNode->ptrRight, iPayload); 
    }
    
    return ptrNode;
}

// Função para imprimir a árvore binária de busca
void printTree(struct Node* ptrNode)
{
    // Se o nó inicial não for nulo, imprime o dado e percorre recursivamente a árvore
    if (ptrNode != nullptr)
    {
        cout << " " << ptrNode->iData;
        printTree(ptrNode->ptrLeft);
        printTree(ptrNode->ptrRight);
    }
    
}
Node* stringToTree(Node* ptrNode, string strTree)
{
    // Verificar se a string está vazia
    if (strTree.empty())
    {
        return nullptr;
    }
    
    // Expressão regular para separar os elementos entre vírgulas
    regex separator(",");
    sregex_token_iterator iterator(strTree.begin(), strTree.end(), separator, -1);
    sregex_token_iterator endIterator;
    
    
    // Percorrer os elementos separados e inserir na árvore
    while (iterator != endIterator) 
    {
        // Verificar se o elemento é válido
        if (isdigit(*iterator->str().begin()))
        {
            // Converter o elemento para inteiro
            int iElement = stoi(*iterator);
            
            // Inserir o elemento na árvore
            ptrNode = insertNode(ptrNode, iElement);
        }
        else
        {
            cout << "Erro: a árvore deve conter apenas números inteiros." << endl;
            return nullptr;
        }
        
        
        ++iterator;
    }
    
    return ptrNode;
}



// Função para criar uma árvore binária de busca a partir de dados digitados
struct Node* inputTree()
{
    // Cria um ponteiro para o nó raiz e o inicializa como nulo
    struct Node* ptrRoot = nullptr;

    // Variável para armazenar os dados digitados
    string strTree;

    // Solicita os dados ao usuário
    cout << "Digite os dados da sua árvore separados por vírgula: ";
    cin >> strTree;


    // Chama a função para criar a árvore
    ptrRoot = stringToTree(ptrRoot, strTree);
    
    return ptrRoot;
}



// Função para criar uma árvore binária de busca a partir de um arquivo .txt
struct Node* txtToTree(string strPath)
{
    // Cria um ponteiro para o nó raiz e o inicializa como nulo
    struct Node* ptrRoot = nullptr;

    // Variável para armazenar o conteúdo do arquivo
    ifstream inputFile;

    // Abre o arquivo   
    inputFile.open(strPath);

    // Verifica se o arquivo foi aberto corretamente
    if (inputFile.is_open()) 
    {
        // Variável para armazenar o conteúdo do arquivo
        string strConteudo((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));

        // Fecha o arquivo
        inputFile.close();

        // Chama a função para criar a árvore a partir do conteúdo do arquivo
        ptrRoot = stringToTree(ptrRoot, strConteudo);

    } 
    // Caso contrário, exibe uma mensagem de erro
    else 
    {
        cout << "Erro ao abrir o arquivo." << endl;
    }

    return ptrRoot;
}

// Função para verificar se uma árvore binária de busca é perfeita (se todos os nós tem 0 ou 2 filhos)
bool isPerfectTree(struct Node* ptrNode)
{
    // Se a árvore estiver vazia, retorna falso
    if (ptrNode == nullptr)
    {
        return false;
    }
    // Se o nó não tiver filhos, retorna verdadeiro
    else if (ptrNode->ptrLeft == nullptr && ptrNode->ptrRight == nullptr)
    {
        return true;
    }
    // Se o nó tiver apenas um filho, retorna falso
    else if (ptrNode->ptrLeft == nullptr || ptrNode->ptrRight == nullptr)
    {
        return false;
    }
    // Se o nó tiver dois filhos, verifica recursivamente se os filhos também são perfeitos
    else
    {
        // Caso um dos filhos não seja perfeito, retorna falso
        return isPerfectTree(ptrNode->ptrLeft) && isPerfectTree(ptrNode->ptrRight);
    }
    
}


// Função que permite usuário fornecer um elemento para ser inserido na árvore
struct Node* inputInsertNode(struct Node* ptrNode)
{
    // Variável para armazenar o elemento a ser inserido
    int iPayload;

    // Solicita o elemento ao usuário
    cout << "Digite o elemento a ser inserido: ";
    cin >> iPayload;

    // Chama a função para inserir o elemento na árvore
    ptrNode = insertNode(ptrNode, iPayload);

    return ptrNode;
}

// Função para remover um nó da árvore binária de busca
struct Node* removeNode(struct Node* ptrNode, int iPayload)
{
    // Se a árvore estiver vazia, retorna o novo nó
    if (ptrNode == nullptr)
    {
        return ptrNode;
    }

    // Se o valor do nó atual é igual ao valor a ser removido
    else if(iPayload == ptrNode->iData)
    {
        // Se o nó não tiver filhos
        if (ptrNode->ptrLeft == nullptr and ptrNode->ptrRight == nullptr)
        {
            // Exclui o nó e retorna nulo 
            free(ptrNode);
            return nullptr;
        }

        // Se o nó tiver apenas o filho direito
        else if (ptrNode->ptrLeft == nullptr)
        {
            // Cria um ponteiro para armazenar temporariamente o filho direito do nó que será excluído
            struct Node* ptrRightTemp = ptrNode->ptrRight;

            // Exclui o nó
            free(ptrNode);

            // Retorna o filho direito do nó excluído
            return ptrRightTemp;
        }

        // Se o nó tiver apenas o filho esquerdo
        else if (ptrNode->ptrRight == nullptr)
        {
            // Cria um ponteiro para armazenar temporariamente o filho esquerdo do nó que será excluído
            struct Node* ptrLeftTemp = ptrNode->ptrLeft;

            // Exclui o nó
            free(ptrNode);

            // Retorna o filho esquerdo do nó excluído
            return ptrLeftTemp;
        }
        
        // Se o nó tiver dois filhos, retorna o nó com o menor valor da subárvore direita
        else
        {
            // Cria um ponteiro para o nó com o menor valor da subárvore direita
            struct Node* ptrMinRight = ptrNode->ptrRight;

            // Percorre a subárvore direita até o nó mais à esquerda (menor valor)
            while (ptrMinRight->ptrLeft != nullptr) ptrMinRight = ptrMinRight->ptrLeft;

            // Atribui o valor do nó com o menor valor da subárvore direita ao nó atual
            ptrNode->iData = ptrMinRight->iData;

            // Remove o nó com o menor valor da subárvore direita
            ptrNode->ptrRight = removeNode(ptrNode->ptrRight, ptrMinRight->iData);

            return ptrNode;
        }
    }

    // Se o elemento a ser removido for menor que o elemento do nó atual, percorre a árvore recursivamente até encontrar a posição correta
    else if(iPayload < ptrNode->iData)
    {
        ptrNode->ptrLeft = removeNode(ptrNode->ptrLeft, iPayload);
    }

    // Se o elemento a ser removido for maior que o elemento do nó atual, percorre a árvore recursivamente até encontrar a posição correta
    else 
    {
        ptrNode->ptrRight = removeNode(ptrNode->ptrRight, iPayload); 
    }
    
    return ptrNode;
}

// Função que permite usuário fornecer um elemento para ser removido da árvore
struct Node* inputRemoveNode(struct Node* ptrNode)
{
    // Variável para armazenar o elemento a ser removido
    int iPayload;

    // Solicita o elemento ao usuário
    cout << "Digite o elemento a ser removido: ";
    cin >> iPayload;

    // Chama a função para remover o elemento da árvore
    ptrNode = removeNode(ptrNode, iPayload);

    return ptrNode;
}

// Função para deletar a árvore binária de busca
void deleteTree(struct Node* ptrNode) 
{
    if (ptrNode != nullptr) 
    {
    // Deletar recursivamente a sub-árvore esquerda
    deleteTree(ptrNode->ptrLeft);

    // Deletar recursivamente a sub-árvore direita
    deleteTree(ptrNode->ptrRight);

    // Deletar o nó atual
    ptrNode->ptrLeft = nullptr;
    ptrNode->ptrRight = nullptr;
    ptrNode = nullptr;
    delete ptrNode;
    }
}



// Função que calcula a altura da árvore
int calculateHeight( struct Node* prtNode) {
    if (prtNode == NULL)
        return 0;
    else {
        // Calcula a altura das subárvores esquerda e direita
        int leftHeight = calculateHeight(prtNode->ptrLeft);
        int rightHeight = calculateHeight(prtNode->ptrRight);
        
        // Retorna a altura do nó atual somada à altura da subárvore mais alta
        return 1 + max(leftHeight, rightHeight);
    }
}

// Função auxiliar para obter o mínimo entre dois valores inteiros
int getMin(int a, int b) {
    return (a < b) ? a : b;
}

// Função auxiliar para obter o máximo entre dois valores inteiros
int getMax(int a, int b) {
    return (a > b) ? a : b;
}

// Função auxiliar para calcular as estatísticas da árvore
void calculateTreeStats(struct Node* prtNode, treeStats& tsStats) {
    if (prtNode == nullptr) {
        return;
    }

    // Atualiza as estatísticas com base no nó atual
    tsStats.iNumNodes++;
    tsStats.iMinValue = getMin(tsStats.iMinValue, prtNode->iData);
    tsStats.iMaxValue = getMax(tsStats.iMaxValue, prtNode->iData);

    // Verifica se o nó atual é uma folha
    if (prtNode->ptrLeft == nullptr && prtNode->ptrRight == nullptr) {
        tsStats.iNumLeaves++;
    }

    // Calcula as estatísticas das subárvores esquerda e direita recursivamente
    calculateTreeStats(prtNode->ptrLeft, tsStats);
    calculateTreeStats(prtNode->ptrRight, tsStats);
}

// Inicializa as estatísticas da árvore
treeStats getTreeSize(Node* ptrNode) {
    treeStats tsStats;
    tsStats.iNumNodes = 0;
    tsStats.iMinValue = ptrNode->iData;
    tsStats.iMaxValue = ptrNode->iData;
    tsStats.iNumLeaves = 0;

    // Calcula as estatísticas da árvore
    calculateTreeStats(ptrNode, tsStats);

    return tsStats;
}

// Função que calcula o tamanho da árvore
int calculateSize(struct Node* ptrNode) {
    if (ptrNode == nullptr)
        return 0;

    int iLeftSize = calculateSize(ptrNode->ptrLeft);
    int iRightSize = calculateSize(ptrNode->ptrRight);

    return iLeftSize + iRightSize + 1;
}

// Função auxiliar para verificar se a árvore é completa
bool isCompleteTree(struct Node* ptrNode, int iIndex, int iSize) {
    // Verifica se o nó atual é nulo, indicando o final da subárvore
    if (ptrNode == nullptr)
        return true;

    //Verifica se o índice atual ultrapassou o tamanho total da árvore, indicando que a subárvore não é completa
    if (iIndex >= iSize)
        return false;

    return isCompleteTree(ptrNode->ptrLeft, 2 * iIndex + 1, iSize) &&
           isCompleteTree(ptrNode->ptrRight, 2 * iIndex + 2, iSize);
}

// Função que verifica se a árvore é completa
bool isCompleteTree(struct Node* ptrNode) {
    int iSize = calculateSize(ptrNode);

    return isCompleteTree(ptrNode, 0, iSize);
}

// Função que adiciona um ponteiro do nó de uma arvóre em uma fila
void enqueueNode(struct QueueNode** ptrQueue, struct Node* ptrNode, int iLevel)
{
    // Cria um novo nó da fila e atribui o ponteiro do nó da árvore
    struct QueueNode* ptrNewQueueNode = new struct QueueNode;
    ptrNewQueueNode->ptrCurrentNode = ptrNode;
    ptrNewQueueNode->iHeight = iLevel;
    ptrNewQueueNode->ptrNext = nullptr;

    // Se a fila estiver vazia, o novo nó será o primeiro
    if (*ptrQueue == nullptr)
    {
        (*ptrQueue) = ptrNewQueueNode;
    }

    // Se a fila não estiver vazia, o novo nó será adicionado ao final da fila
    else
    {
        struct QueueNode* ptrCurrent = *ptrQueue;
        while (ptrCurrent->ptrNext != nullptr) ptrCurrent = ptrCurrent->ptrNext;
        ptrCurrent->ptrNext = ptrNewQueueNode;
    }
}


// Função para imprimir a árvore binária de busca utilizando BFS
void printTreeBFS(struct Node* ptrNode)
{
    struct QueueNode* ptrQueueRoot = nullptr;

    // Se a árvore estiver vazia, retorna
    if (ptrNode == nullptr)
    {
        return;
    }

    // Variável para armazenar a altura atual
    int iCurrentHeight = 0;

    // Adiciona o nó raiz na fila
    enqueueNode(&ptrQueueRoot, ptrNode, iCurrentHeight);

    cout << endl;

    // Enquanto a fila não estiver vazia
    while (ptrQueueRoot != nullptr)
    {
        // Se a altura do nó atual for diferente da altura anterior, pula uma linha
        if (ptrQueueRoot->iHeight != iCurrentHeight)
        {
            cout << endl;
            iCurrentHeight = ptrQueueRoot->iHeight;
        }

        // Imprime o valor do nó atual
        cout << ptrQueueRoot->ptrCurrentNode->iData << " ";

        // Adiciona os filhos do nó atual na fila
        if (ptrQueueRoot->ptrCurrentNode->ptrLeft != nullptr) enqueueNode(&ptrQueueRoot, ptrQueueRoot->ptrCurrentNode->ptrLeft, ptrQueueRoot->iHeight + 1);
        if (ptrQueueRoot->ptrCurrentNode->ptrRight != nullptr) enqueueNode(&ptrQueueRoot, ptrQueueRoot->ptrCurrentNode->ptrRight, ptrQueueRoot->iHeight + 1);

        // Remove o nó atual da fila e libera a memória
        struct QueueNode* ptrTemp = ptrQueueRoot;
        ptrQueueRoot = ptrQueueRoot->ptrNext;
        free(ptrTemp);
    }

    cout << endl;
}