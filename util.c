//
// Created by Julien on 16/02/2017.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

/*
    GESTION PILE
*/
// Fonction d'initialisation de la Pile
Stack* initStack(){
    Stack* stack = malloc(sizeof( *stack ));
    stack->top = NULL;

    return stack;
}

StackV2* initStackV2(){
    StackV2* stack = malloc(sizeof( *stack ));
    stack->top = NULL;

    return stack;
}


void pushV2(StackV2* stack, int* tab, int row){
    NodeV2* newTop = malloc( sizeof( *newTop ));
    if( stack == NULL || newTop == NULL ){
        printf("Erreur : stack or newTop NULL.\n");
        exit(-1);
    }

    newTop->tab = copyTab(tab, row);
    newTop->next = stack->top;
    stack->top = newTop;
}

// Ajout d'une sauvegarde de matrice dans la Pile
// IMPORTANT : Copie par Valeur faite automatiquement lors du push (on duplique la matrice actuelle | 2 pointeurs)
//                          ^-----> void createNewMatrice(int** matrix);
void push(Stack* stack, int** matrix, int row, int col){
    Node* newTop = malloc(sizeof( *newTop ));
    if( stack == NULL || newTop == NULL ){
        printf("Erreur : stack or newTop NULL.\n");
        exit(-1);
    }

    newTop->matrix = copyMatrix(matrix, row, col);
    newTop->next = stack->top;
    stack->top = newTop;
}


int* popV2(StackV2* stack){
    int* tmpTab;

    if( stack->top != NULL ){
        tmpTab = stack->top->tab;
        NodeV2* node = stack->top;
        stack->top = stack->top->next;
        free(node);
    }
    else{
        printf("Erreur : top NULL.\n");
        exit(-1);
    }

    return tmpTab;
}

// Retirement du premier élément de la Pile
// Renvoie une matrice
int** pop(Stack* stack){
    if( stack == NULL ){
        printf("Erreur : stack NULL.\n");
        exit(-1);
    }

    int** tmpMatrice;

    if( stack->top != NULL ){
        tmpMatrice = stack->top->matrix;
        Node* node = stack->top;
        stack->top = stack->top->next;
        free(node); // Libération du noeud qui n'est plus utilisé.
    }
    else{
        printf("Erreur : top NULL.\n");
        exit(-1);
    }

    return tmpMatrice;
}

int* popV2_n_time(StackV2* stack, int nTime){
    for(int i=0; i < nTime-1; ++i){
        free(popV2(stack));
    }

    return popV2(stack);
}

int** pop_n_time(Stack* stack, int nTime, int row){
    for(int i=0; i < nTime-1; ++i){
        wipeMatrix(pop(stack), row);
    }

    return pop(stack);
}

void wipeStackV2(StackV2* stack, int row){
    while( stack->top != NULL){
        free(stack->top->tab); // Libération du tableau de int
        NodeV2* top = stack->top;
        stack->top = stack->top->next;
        free(top);
    }

    free(stack);
}

// Suppression et libération de mémoire pour toutes les matrices contenues dans la pile
// Suppression de libération de mémoire de la pile
void wipeStack(Stack* stack, int row){
    while( stack->top != NULL ){
        wipeMatrix(stack->top->matrix, row); // Libération de la mémoire allouée pour la matrice
        Node* top = stack->top;
        stack->top = stack->top->next;
        free(top); // Libération du noeud dépilé
    }

    free(stack); // Libération de la pile
}

void printAllStackV2(StackV2* stack, int row){
    NodeV2* index = stack->top;

    printf("-- AFFICHAGE PILE MATRICE --\n");
    while( index != NULL ){
        printTab(index->tab, row);
        index = index->next;
    }
    printf("-- FOND DE PILE --\n");
}

// Affiche toutes les matrices stockées dans la pile
void printAllStack(Stack* stack, int row, int col){
    Node* index = stack->top;

    printf("-- AFFICHAGE PILE MATRICE --\n");
    while( index != NULL ){
        printMatrix(index->matrix, row, col);
        index = index->next;
    }
    printf("-- FOND DE PILE --\n");
}

/*
GESTION MATRICE
*/
void printTab(int* tab, int row){
    int i;

    char str[999999];
    sprintf(str, "{");
    for(i=0; i < row; ++i){
        sprintf(str, "%s %d", str, tab[i]);
        if( i < row-1 )
            sprintf(str, "%s,", str);
    }
    sprintf(str, "%s }\n", str);

    printf("%s", str);
}


// Affiche une matrice row*col
void printMatrix(int** matrix, int row, int col){
    int i, j;

    char str[999999];
    sprintf(str, "{\n");

    for(i = 0; i < row; ++i){
        for(j = 0; j < col; ++j){
            sprintf(str, "%s[ %d ]", str, matrix[i][j]);
        }
        sprintf(str, "%s\n", str);
    }
    sprintf(str, "%s}\n", str);

    printf("%s", str);
}

void resetTab(int* tab, int row){
    for(int i=0; i < row; ++i)
        tab[i] = - 1;
}

// Remet à 0 une matrice row*col
void resetMatrix(int** matrix, int row, int col){
    for(int i=0; i < row; ++i){
        for(int j=0; j < col; ++j){
            matrix[i][j] = 0;
        }
    }
}

int* createNewTab(int nbElement){
    return malloc( nbElement * sizeof(int) );
}

// Créer une nouvelle matrice row*col
int** createNewMatrix(int row, int col){
    int** newMatrix = malloc( row * sizeof(int*));
    if(newMatrix != NULL){
        for(int i = 0; i < row; ++i){
            newMatrix[i] = createNewTab(col);
            if( (newMatrix[i] == NULL) ){
                printf("Erreur : newMatrice[%d] NULL.\n", i);
                exit(-1);
            }
        }
    }
    else{
        printf("Erreur : newMatrice, première dimension NULL.\n");
        exit(-1);
    }

    resetMatrix(newMatrix, row, col);
    return newMatrix;
}

void wipeMatrix(int** matrix, int row){
    for(int i=0; i < row; ++i){
        free(matrix[i]); // Libération deuxième dimension
    }
    free( matrix); // Libération première dimension
}

int* copyTab(int* tab, int nbElement){
    int* newTab = createNewTab(nbElement);
    for(int i=0; i < nbElement; ++i){
        newTab[i] = tab[i];
    }

    return newTab;
}
// Copie par valeur d'une matice row*col vers une nouvelle row*col
int** copyMatrix(int** sourceMatrix, int row, int col){
    int** newMatrix;
    newMatrix = createNewMatrix(row, col);
    for(int i=0; i < row; ++i){
        for(int j=0; j < col; ++j){
            newMatrix[i][j] = sourceMatrix[i][j];
        }
    }

    return newMatrix;
}

/*// Fonction qui a pour but de vérifier si il existe un 1 dans une colonne donnée
// Renvoie le numéro de ligne si trouvé
// Sinon -1
int checkForConstraintInCol(int** matrix, int number_of_the_col, int nbTotalRow){
    for(int i=0; i < nbTotalRow; ++i){
        if( matrix[i][number_of_the_col] == 1 )
            return i;
    }
    return -1;
}

// Fonction qui a pour but de vérifier si il existe un 1 dans une ligne donnée
// Renvoie le numéro de colonne si trouvé
// Sinon -1
int checkForConstraintInRow(int** matrix, int number_of_the_row, int nbTotalCol){
    for(int i=0; i < nbTotalCol; ++i){
        if( matrix[number_of_the_row][i] == 1 )
            return i;
    }
    return -1;
}*/


int checkForConstraintInDiagonal(int** matrix, int number_of_the_row, int number_of_the_col, int nbTotalRow, int nbTotalCol){
    int i=number_of_the_row;
    int j=number_of_the_col;

    int violatedConstraint = nbTotalRow;

    //recherche dans la diagonale haut-gauche
    while( i > 0 && j > 0){
        --i;
        --j;

        if(matrix[i][j] == 1){
            if( i < violatedConstraint ){
                violatedConstraint = i;
            }
        }
    }

    i=number_of_the_row;
    j=number_of_the_col;

    //recherche diagonale haut-droite
    while( i > 0 && j < nbTotalCol) {
        --i;
        ++j;

        if(matrix[i][j] == 1){
            if( i < violatedConstraint ){
                violatedConstraint = i;
            }
        }
    }

    if( violatedConstraint < nbTotalRow )
        return violatedConstraint;
    else
        return -1;
}


int checkForConstraintV2(int* tab, int value, int positionOfValue, int nbTotalRow, int nbTotalCol, int setUp){
    int constraintID = nbTotalRow;

    for(int i=0; i < positionOfValue; ++i){
        if( tab[i] == value ){
            constraintID = i;
            break;
        }
    }

    // Application de contraintes supplémentaires pour les reines :
    if( setUp == 1 ){

        printf("Check Constraint Diagonale !\n");

        // Décalage Gauche :
        int decalage = value;
        int index = positionOfValue;

        while( index > 0 && decalage > 0 ){
            --decalage;
            --index;

            printf("tab(%i) = %d == %d ?\n", index, tab[index], decalage);

            if( tab[index] == decalage ){
                if( index < constraintID ){
                    constraintID = index;

                    printf("HG %d\n", constraintID);
                }
            }
        }

        index = positionOfValue;
        decalage = value;

        while( index > 0 && decalage < nbTotalCol){
            ++decalage;
            --index;

            if( tab[index] == decalage ){
                if( index < constraintID ){
                    constraintID = index;

                    printf("HD %d\n", constraintID);
                }
            }
        }
    }

    if( constraintID == nbTotalRow )
        return -1;

    return constraintID;
}


// Fonction qui a pour but de vérifier si il existe un 1 dans une colonne donnée
// Renvoie le numéro de ligne si trouvé
// Sinon -1
int checkForConstraintInCol(int** matrix, int number_of_the_col, int nbTotalRow){
    for(int i=0; i < nbTotalRow; ++i){
        if( matrix[i][number_of_the_col] == 1 )
            return i;
    }
    return -1;
}

// Fonction qui a pour but de vérifier si il existe un 1 dans une ligne donnée
// Renvoie le numéro de colonne si trouvé
// Sinon -1
int checkForConstraintInRow(int** matrix, int number_of_the_row, int nbTotalCol){
    for(int i=0; i < nbTotalCol; ++i){
        if( matrix[number_of_the_row][i] == 1 )
            return i;
    }
    return -1;
}

void fillColumns(int **domaines, int i, int j, int nbPigeons, int value){
    for(int k = i + 1; k < nbPigeons; ++k)
        domaines[k][j] = value;
}

void fillDiagonal(int **domaines, int i, int j, int nbPigeons, int value){
    for(int k = i; k < nbPigeons; ++k) {
        domaines[k][k] = value;
        domaines[k][-(i-k)] = value;
    }
}

// Fonction d'initialisation de la Pile
Pile* initPile(){
    Pile* stack = malloc(sizeof( *stack ));
    stack->top = NULL;

    return stack;
}

// Ajout d'une sauvegarde de matrice dans la Pile
// IMPORTANT : Copie par Valeur faite automatiquement lors du push (on duplique la matrice actuelle | 2 pointeurs)
//                          ^-----> void createNewMatrice(int** matrix);
void pushPile(Pile* stack, int value){
    Noeud* newTop = malloc(sizeof( *newTop ));
    if( stack == NULL || newTop == NULL ){
        printf("Erreur : stack or newTop NULL.\n");
        exit(-1);
    }

    newTop->pos = value;
    newTop->next = stack->top;
    stack->top = newTop;
}

// Retirement du premier élément de la Pile
// Renvoie une matricer
int popPile(Pile* stack){
    if( stack == NULL ){
        printf("Erreur : stack NULL.\n");
        exit(-1);
    }

    int pos;

    if( stack->top != NULL ){
        pos = stack->top->pos;
        Noeud* node = stack->top;
        stack->top = stack->top->next;
        free(node); // Libération du noeud qui n'est plus utilisé.
    }
    else{
        printf("Erreur : top NULL.\n");
        exit(-1);
    }

    return pos;
}
