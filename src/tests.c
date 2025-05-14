#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/*
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

void sbPushString(StringBuilder* str, const char* input) {
    //T0D0: Pegar o string inpit, coletar a quantia de caracteres e colocar os caracteres 1 a 1 usando a função pushChar()
}

void sbFree(StringBuilder* str) {
    free(str->array);
    str->index = 0;
    str->size = 0;
}
*/

typedef struct {
    char* name;
    int price;
    int kg;
}Product;

typedef struct {
    Product product[10];
    int index;
}Product_Database;
Product_Database product_dabase;

void insert_product(Product* product, Product_Database* pd_db) {
    pd_db->product[pd_db->index].name = product->name;
    pd_db->product[pd_db->index].price = product->price;
    pd_db->index ++;
}

int getProductDatabaseIndex(Product_Database* pd_db) {
    printf("Coletando a quantidade de produtos cadastrados\n");
    return pd_db->index;
}

void printAllProducts(Product_Database* pd_db) {
    for(int x = 0; x < pd_db->index; x++) {
        printf("Product Name: %s\n", pd_db->product[x].name);
        printf("Product Price: %d\n", pd_db->product[x].price);
        printf("Product KG: %d\n", pd_db->product[x].kg);
        printf("\n");
    }
}

Product get_product (int index, Product_Database* pd_db) {
    return pd_db->product[index];
}

int main() {
    Product banana = {0};
    banana.name = "Banana 10KG";
    banana.price = 35;
    banana.kg = 10;
    insert_product(&banana, &product_dabase);

    Product pera = {0};
    pera.name = "Pera";
    pera.price = 10;
    pera.kg = 3;
    insert_product(&pera, &product_dabase);

    printAllProducts(&product_dabase);

    initSomething(0);

    return 0;
}