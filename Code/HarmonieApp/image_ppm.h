// ----------------------------------------------------------------------------
// Filename        : image_ppm.c
// Description     :
// Created On      : Tue Mar 31 13:26:36 2005
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

typedef unsigned char OCTET;

#define allocation_tableau(nom, type, nombre) \
if( (nom = (type*) calloc (nombre, sizeof(type) ) ) == NULL ) \
    {\
            printf("\n Allocation dynamique impossible pour un pointeur-tableau \n");\
            exit(1);\
    }


/*===========================================================================*/
void ignorer_commentaires(FILE * f)
{
    unsigned char c;
    while((c=fgetc(f)) == '#')
        while((c=fgetc(f)) != '\n');
    fseek(f, -sizeof(unsigned char), SEEK_CUR);
}
/*===========================================================================*/

int indiceImg(int i, int j, int width, int height){
    if(i >= height){
        printf("i trop grand \n");

    }
    if(i < 0){
        printf("i trop petit \n");
    }
    if(j >= width){
        printf("j trop grand\n");
    }
    if(j < 0){
        printf("j trop petit\n");
    }
    return i * width + j;

}

int indiceLineImgCouleur(int indice, int nW){
    //on veut retourner retourne l'indice de la ligne
    int i;

    i = indice/(nW*3); //partie entiere ligne
    //j = (3*nW)*i; colonne

    return i;



}

int indiceColImgCouleur(int indice, int nW){
    //on veut retourner retourne l'indice de la ligne
    int j;

    j = indice%(nW*3);

    return j;


}

int getIndiceIjImgCouleur(int i, int j, int nW, int nH){

    //on veut retourner l'indice
    if(i >= nH){
        printf("i trop grand");
    }
    if(i <0 ){
        printf("i trop petit");
    }

    if(j >= nW*3){
        printf("j trop grand");
    }
    if(j < 0 ){
        printf("j trop petit");
    }

    int indice = i*(nW * 3)+j;

    return indice;

}


/*===========================================================================*/
void ecrire_image_ppm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
    FILE *f_image;
    int taille_image = 3*nb_colonnes * nb_lignes;

    if( (f_image = fopen(nom_image, "wb")) == NULL)
    {
        printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(f_image,"P6\r") ;                               /*ecriture entete*/
        fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

        if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
            != (size_t)(taille_image))
        {
            printf("\nErreur d'ecriture de l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        fclose(f_image);
    }
}
/*===========================================================================*/

/*===========================================================================*/
void lire_nb_lignes_colonnes_image_ppm(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
    FILE *f_image;
    int max_grey_val;

    /* cf : l'entete d'une image .ppm : P6                   */
    /*				       nb_colonnes nb_lignes */
    /*    			       max_grey_val          */


    if( (f_image = fopen(nom_image, "rb")) == NULL)
    {
        printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(f_image, "P6 ");
        ignorer_commentaires(f_image);
        fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
        fclose(f_image);
    }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_ppm(char  nom_image[], OCTET *pt_image, int taille_image)
{
    FILE *f_image;
    int  nb_colonnes, nb_lignes, max_grey_val;
    taille_image=3*taille_image;

    if( (f_image = fopen(nom_image, "rb")) == NULL)
    {
        printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(f_image, "P6 ");
        ignorer_commentaires(f_image);
        fscanf(f_image, "%d %d %d%*c",
               &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

        if( (fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
            !=  (size_t)(taille_image))
        {
            printf("\nErreur de lecture de l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        fclose(f_image);
    }
}

/*===========================================================================*/
/*===========================================================================*/

void planR(OCTET *pt_image, OCTET *src, int taille_image){
    int i;
    for (i=0; i<taille_image; i++){
        pt_image[i]=src[3*i];
    }
}

/*===========================================================================*/
/*===========================================================================*/

void planV(OCTET *pt_image, OCTET *src, int taille_image){
    int i;
    for (i=0; i<taille_image; i++){
        pt_image[i]=src[3*i+1];
    }
}

/*===========================================================================*/
/*===========================================================================*/

void planB(OCTET *pt_image, OCTET *src, int taille_image){
    int i;
    for (i=0; i<taille_image; i++){
        pt_image[i]=src[3*i+2];
    }
}

/*===========================================================================*/
/*===========================================================================*/

void ecrire_image_pgm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
    FILE *f_image;
    int taille_image = nb_colonnes * nb_lignes;

    if( (f_image = fopen(nom_image, "wb")) == NULL)
    {
        printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(f_image,"P5\r") ;                               /*ecriture entete*/
        fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

        if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
            != (size_t) taille_image)
        {
            printf("\nErreur de lecture de l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        fclose(f_image);
    }
}
/*===========================================================================*/

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
    FILE *f_image;
    int max_grey_val;

    /* cf : l'entete d'une image .pgm : P5                    */
    /*				       nb_colonnes nb_lignes */
    /*    			       max_grey_val          */


    if( (f_image = fopen(nom_image, "rb")) == NULL)
    {
        printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(f_image, "P5 ");
        ignorer_commentaires(f_image);
        fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
        fclose(f_image);
    }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_pgm(char  nom_image[], OCTET *pt_image, int taille_image)
{
    FILE *f_image;
    int  nb_colonnes, nb_lignes, max_grey_val;

    if( (f_image = fopen(nom_image, "rb")) == NULL)
    {
        printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(f_image, "P5 ");
        ignorer_commentaires(f_image);
        fscanf(f_image, "%d %d %d%*c",
               &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

        if( (fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
            !=  (size_t) taille_image)
        {
            printf("\nErreur de lecture de l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        fclose(f_image);
    }
}
/*===========================================================================*/

