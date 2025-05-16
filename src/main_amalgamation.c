#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

/*
Projeto que cria um sistema para poder criar, armazenar, comprar e gerenciar produtos de mercado, simulando uma base de dados para um mercado
*/

/*
TODO:
[X] Produzir o código da função sbPushString
[ ] Fazer a verificação de dados, pois existe a possibilidade de que ao coletar algum dado quando registrando algum produto ocorra um erro pois o ciente não está digitando o tipo de dados corretos, ou digitou algum caractere errado
[ ] Implementar um sistema de non-case-sensetive, permetindo que ao usuario digitar alguma informação e ao processa-la não irá existir problemas em caso de letras em modo case-sensitive
[ ] Verificar o problema de casting de string pra C quando lendo um input do usuario, esse problema ocorre na função de nome createProduct na seção PRODUCT HANDLE SECTION
[ ] Implementar todas as função faltantes na seção de Products Handle
[ ] implementar algumas caracteristicas mais complexas no banco de dados como sistema de quantidade do mesmo produto, a soma total dos valores desse produto

TODO EVERITIME:
[ ] Verificar a necessidade de retirar alguma seção que não será mais usada no código
*/

/*
------------------------------------------------------------------------------------------------
                                        DECLARATION SECTION
------------------------------------------------------------------------------------------------
*/

//To work with strings in some good way
typedef struct {
    char* array;
    int size;
    int index;
}StringBuilder;

//The products structure to handle the products
typedef struct {
    char* name;
    int price;
    int kg;
}Product;

typedef struct {
    Product* product;
    int index;
    int size;
}Product_Database;
Product_Database product_database = {0};

//STRING BUILDER DECLARATION
void sbInit(StringBuilder* str, int initialCapacity);
void sbPushChar(StringBuilder* str, char ch);
void sbResize(StringBuilder* str);
char* sbGetContent(StringBuilder* str);
void sbPushString(StringBuilder* str, char* input);
void sbFree(StringBuilder* str);

//TERMINAL INTERFACE DECLARATION
void readUserInput(StringBuilder* str);
void processUserInput(char* userInput);
void help_prompt();

//PRODUCT DATABASE HANDLE DECLARATION
void pdDbInit(Product_Database* pd_db, int  initialCapacity);
void pdDbResize(Product_Database* pd_db);
void pdDbInsertProduct(Product_Database* pd_db, Product* product);
Product pdDbGetProduct(Product_Database* pd_db, int index);
Product pdDbGetProductByName(Product_Database* pd_db, char* product_name);
void pdDbFree(Product_Database* pd_db);

//PRODUCT DECLARATION

/*
------------------------------------------------------------------------------------------------
                                        UTILS SECTION
------------------------------------------------------------------------------------------------
*/
#define PRODUCTS_DATABASE_PATH "products_database"

//Coleta um arquivo a partir de sua path e Retorna um FILE* para poder trabalhar com este arquivo. Retorna NULL se o arquivo não for aberto de forma bem sucedida
FILE* getFile(char* file_path, char* open_mode) {
    FILE* file;
    file = fopen(file_path, open_mode);

    return file;
}

void writeFile(FILE* file, char* content) {
    fputs(content, file);
}

char* readFile(FILE* file) {
    char buffer[1024] = {0};
    while(fgets(buffer, 1024, file) != NULL) {
        printf("%s\n", buffer);
    }
}

/*
------------------------------------------------------------------------------------------------
                                PRODUCT DATABASE HANDLES CODE SECTION
------------------------------------------------------------------------------------------------
*/

void pdDbInit(Product_Database* pd_db, int initialCapacity) {
    int capacity;
    if (initialCapacity == 0) {
        capacity = 1024;
    }
    else {
        capacity = initialCapacity;   
    }

    pd_db->product = (Product*) malloc(sizeof(Product) * capacity);
}

void pdDbResize(Product_Database* pd_db) {
    pd_db->size *= 2;
    pd_db->product = (Product*) realloc(pd_db->product, sizeof(Product) * pd_db->size);
}

void pdDbInsertProduct(Product_Database* pd_db, Product* product) {
    if (pd_db->index == pd_db->size) {
        pdDbResize(pd_db);
    }
    
    pd_db->product[pd_db->index].name = product->name;
    pd_db->product[pd_db->index].price = product->price;
    pd_db->product[pd_db->index].kg = product->kg;

    pd_db->index++;
}

Product pdDbGetProduct(Product_Database* pd_db, int index) {
    return pd_db->product[index];
}

Product pdDbGetProductByName(Product_Database* pd_db, char* product_name) {
    for (int x = 0; x < pd_db->size; x++) {
        if (strcmp(product_name, pd_db->product[x].name) == 0) {
            return pd_db->product[x];
        }
    }
}

void pdDbDeleteProduct(Product_Database* pd_db, int index) {
    int found = 0;
    
    for (int x = 0; x < pd_db->index; x++) {
        if(pd_db->product[x] == index) {
            found = 1;
        }
        if (found && x < list->size - 1) {
            pd_db->product[x] = pd_db->product[x + 1];
        }
    }
    
    if (found) {
        pd_db->index--;
    }
}

//Essa função é responsável por lidar com a opção de compra do produto, isto é, diminuir a quantia de produtos disponíveis, isto é, realizar uma baixa no produto, e também aumentar diminuir o valor (quantia total de dinheiro em mercadoria) da quantidade de itens na base de dados 
void pdDbPurchaseProduct() {
    
}

void pdDbFree(Product_Database* pd_db) {
    free(pd_db->product);
    pd_db->index = 0;
    pd_db->size = 0;
}

/*
------------------------------------------------------------------------------------------------
                                    PRODUCT HANDLES CODE SECTION
------------------------------------------------------------------------------------------------
*/

void createProduct() {
    printf("Iniciando o sistema para poder criar um produto\n\n");

    Product product = {0};

    StringBuilder product_name;
    StringBuilder product_price;
    StringBuilder product_kg;

    sbInit(&product_name, 10);
    sbInit(&product_price, 10);
    sbInit(&product_kg, 10);

    printf("Digite o nome do produto\n");
    readUserInput(&product_name);
    product.name = sbGetContent(&product_name);

    printf("Digite o preço do produto\n");
    readUserInput(&product_price);
    product.price = (int) sbGetContent(&product_price);

    printf("Digite o kg do produto\n");
    readUserInput(&product_kg);
    product.kg = (int) sbGetContent(&product_kg);

    pdDbInsertProduct(&product_database, &product);

    printf("As seguintes informações foram registradas\n");
    printf("NOME DO PRODUTO: %s\n", sbGetContent(&product_name));
    printf("PREÇO DO PRODUTO: %s\n", sbGetContent(&product_price));
    printf("KG DO PRODUTO: %s\n", sbGetContent(&product_kg));

    /*
    StringBuilder user_input;
    sbInit(&user_input, 10);
    printf("\nVocê deseja adicionar um novo produto? Y/N\n");

    readUserInput(&user_input);
    if(strcmp("Y", sbGetContent(&user_input)) == 0) {
        createProduct();
    }
    */

    sbFree(&product_name);
    sbFree(&product_price);
    sbFree(&product_kg);

}

void deleteProduct() {
    StringBuilder user_input = {0};

    sbInit(&user_input);
    
    printf("Por favor, digite o nome do produto a ser deletado\n");
    readUserInput(&user_input);

    printf("Buscando o produto na base de dados\n");
    for (int x = 0; x < pd_db->index; x++) {
        
    }

}

void deleteProductByName() {
    
}

void buyProduct() {

}

void buyProductByName() {

}

void editProduct() {

}

void editProductByName() {

}

void listAllProducts(Product_Database* pd_db) {
    for (int x = 0; x < pd_db->index; x++) {
        printf("Product Name: %s\n", pd_db->product[x].name);
        printf("Product Price: %s\n", pd_db->product[x].price);
        printf("Product KG: %s\n", pd_db->product[x].kg);
    }
}

/*
------------------------------------------------------------------------------------------------
                            TERMINAL USER INTERFACE CODE SECTION
------------------------------------------------------------------------------------------------
*/

void readUserInput(StringBuilder* str) {
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF) {
        sbPushChar(str, ch);
    }
    sbPushChar(str, '\0');
}

void processUserInput(char* userInput) {
    
    //INTERFACE COMMANDS
    if (strcmp(userInput, "help") == 0) {
        help_prompt();
    }
    else if (strcmp(userInput, "exit") == 0) {
        printf("Saindo...");
        exit(0);
    }
    
    //PRODUCTS COMMANDS
    else if (strcmp(userInput, "create_product") == 0) {
        createProduct();
    }
    else if (strcmp(userInput, "delete_product") == 0) {
        printf("Starting the delete product handle\n");
        deleteProduct();
    }
    else if (strcmp(userInput, "buy_product") == 0) {
        buyProduct();
    }

    else if (strcmp(userInput, "list_products") == 0) {
        printf("Listando todos os produtos cadastrados no sistema e suas informações\n");
        listAllProducts(&product_database);
    }

    else {
        printf("comando \"%s\" nao encontrado, digite \"help\" para uma lista de comandos\n", userInput);
    }
}

//Escreve na tela todos os comandos possíveis para serem executados pelo usuário
void help_prompt() {
    printf("help           - demonstra essa mensagem\n");
    printf("create_product - incializa o sistema para criar um produto\n");
    printf("delete_product - incializa o sistema para poder deleter um produto\n");
    printf("buy_product    - simula a compra de um produto por um cliente\n");
    printf("list_products  - Informa todos os produtos cadastrados e suas informações\n");
}

/*
------------------------------------------------------------------------------------------------
                            STRINB BUILDER CODE SECTION
------------------------------------------------------------------------------------------------
*/

void sbInit(StringBuilder* str, int initialCapacity) {
    str->array = (char*) malloc(sizeof(char) * initialCapacity);
    str->index = 0;
    str->size = initialCapacity;
}

void sbResize(StringBuilder* str) {
    str->size *= 2;
    str->array = (char*) realloc(str->array, sizeof(char) * str->size);
}

void sbPushChar(StringBuilder* str, char ch) {
    if (str-> index == str->size) {
        sbResize(str);
    }
    str->array[str->index] = ch;
    str->index++;
}

char* sbGetContent(StringBuilder* str) {
    return str->array;
}

void sbPushString(StringBuilder* str, char* input) {
    //T0D0: Pegar o string inpit, coletar a quantia de caracteres e colocar os caracteres 1 a 1 usando a função pushChar()
    int string_size = strlen(input);
    for (int x = 0; x < string_size; x++) {
        sbPushChar(str, input[x]);
    }

}

void sbFree(StringBuilder* str) {
    free(str->array);
    str->index = 0;
    str->size = 0;
}

/*
------------------------------------------------------------------------------------------------
                                        DATABASE HANDLE SECTION
------------------------------------------------------------------------------------------------
*/

void writeDatabase() {

}

void readDatabase() {

}


int main () {
    pdDbInit(&product_database, 1024);

    printf("Sistema de gerenciamento de produtos via terminal. Digite help para listar comandos\n");

    StringBuilder userInput = {0};
    while (true) {
        sbInit(&userInput, 1024);

        printf("Shell> ");
        readUserInput(&userInput);

        processUserInput(sbGetContent(&userInput));

        sbFree(&userInput);
    }

    return 0;
}