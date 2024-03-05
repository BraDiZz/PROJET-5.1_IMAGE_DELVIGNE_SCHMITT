// ----------------------------------------------------------------------------
// Filename        : image_ppm.c
// Description     :
// Created On      : Tue Mar 31 13:26:36 2005
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define allocation_tableau(nom, type, nombre) \
if( (nom = (type*) calloc (nombre, sizeof(type) ) ) == NULL ) \
{\
 printf("\n Allocation dynamique impossible pour un pointeur-tableau \n");\
 exit(1);\
}

typedef unsigned char OCTET;

/*===========================================================================*/
void ignorer_commentaires(FILE * f)
{
  unsigned char c;
  while((c=fgetc(f)) == '#')
    while((c=fgetc(f)) != '\n');
  fseek(f, -sizeof(unsigned char), SEEK_CUR);
}
/*===========================================================================*/


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


void dilatation_binaire(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){

   int tmp=1;
   int boool=0;

   for(int i=0;i<nH;i++){
      for(int j=0;j<nW;j++){
         ImgOut[i*nW+j]=ImgIn[i*nW+j];
      }
   }

   for(int i=1;i<nH-1;i++){
      for(int j=1;j<nW-1;j++){
         boool=0;
         for(int k=i-tmp;k<i+tmp+1;k++){
            for(int m=j-tmp;m<j+tmp+1;m++){
               //printf("i=%d j=%d k=%d m=%d et imgout=%d\n",i,j,k,m,ImgOut[k*nW+m]);
               if(ImgIn[k*nW+m]==0){
                  boool=1;
               }
            }
         }
         if(boool==1)ImgOut[i*nW+j]=0;
      }
   }
}

void erosion_binaire(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){

   int tmp=1;
   int boool=0;

   for(int i=0;i<nH;i++){
      for(int j=0;j<nW;j++){
         ImgOut[i*nW+j]=ImgIn[i*nW+j];
      }
   }

   for(int i=1;i<nH-1;i++){
      for(int j=1;j<nW-1;j++){
         boool=0;
         for(int k=i-tmp;k<i+tmp+1;k++){
            for(int m=j-tmp;m<j+tmp+1;m++){
               //printf("i=%d j=%d k=%d m=%d et imgout=%d\n",i,j,k,m,ImgOut[k*nW+m]);
               if(ImgIn[k*nW+m]==255){
                  boool=1;
               }
            }
         }
         if(boool==1)ImgOut[i*nW+j]=255;
      }
   }
}

void difference(OCTET *ImgIn,OCTET *ImgDil, OCTET *ImgOut, int nH, int nW){

   int tmp=1;
   int boool=0;

   for(int i=0;i<nH;i++){
      for(int j=0;j<nW;j++){
         ImgOut[i*nW+j]=ImgIn[i*nW+j];
      }
   }

   for(int i=1;i<nH-1;i++){
      for(int j=1;j<nW-1;j++){
         if(ImgIn[i*nW+j]==ImgDil[i*nW+j])ImgOut[i*nW+j]=255;
         else ImgOut[i*nW+j]=0;
      }
   }
}

void erosion_gris(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){

   int min = 255;
   int tmp = 1;

   for(int i=0;i<nH;i++){
      for(int j=0;j<nW;j++){
         ImgOut[i*nW+j]=ImgIn[i*nW+j];
      }
   }

   for(int i=1;i<nH-1;i++){
      for(int j=1;j<nW-1;j++){
         min = 255;
         for(int k=i-tmp;k<i+tmp+1;k++){
            for(int m=j-tmp;m<j+tmp+1;m++){
               //printf("i=%d j=%d k=%d m=%d et imgout=%d\n",i,j,k,m,ImgOut[k*nW+m]);
               if(ImgIn[k*nW+m]<min){
                  min=ImgIn[k*nW+m];
                  //printf("min = %d\n",min);
               }
            }
         }
         ImgOut[i*nW+j]=min;
      }
   }
}

void dilatation_gris(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){

   int max = 0;
   int tmp = 1;

   for(int i=0;i<nH;i++){
      for(int j=0;j<nW;j++){
         ImgOut[i*nW+j]=ImgIn[i*nW+j];
      }
   }

   for(int i=1;i<nH-1;i++){
      for(int j=1;j<nW-1;j++){
         max= 0;
         for(int k=i-tmp;k<i+tmp+1;k++){
            for(int m=j-tmp;m<j+tmp+1;m++){
               //printf("i=%d j=%d k=%d m=%d et imgout=%d\n",i,j,k,m,ImgOut[k*nW+m]);
               if(ImgIn[k*nW+m]>max){
                  max=ImgIn[k*nW+m];
                  //printf("min = %d\n",min);
               }
            }
         }
         ImgOut[i*nW+j]=max;
      }
   }
}

double getPSNRcolor(unsigned char* dataIn1, unsigned char* dataIn2, int width, int height){ // Calcule le PSNR entre les 2 images couleurs dataIn1 et dataIn2 (formule dans cahier)
    int sommeR = 0;
    int sommeG = 0;
    int sommeB = 0;
    for(int x = 0; x < height ; ++x){
        for(int y = 0; y < width*3; y+=3)
        {
            int In1_R = (int) dataIn1[x*width*3 + y + 0];
            int In1_G = (int) dataIn1[x*width*3 + y + 1];
            int In1_B = (int) dataIn1[x*width*3 + y + 2];
            int In2_R = (int) dataIn2[x*width*3 + y + 0];
            int In2_G = (int) dataIn2[x*width*3 + y + 1];
            int In2_B = (int) dataIn2[x*width*3 + y + 2];

            sommeR += pow(In1_R - In2_R,2);
            sommeG += pow(In1_G - In2_G,2);
            sommeB += pow(In1_B - In2_B,2);
        }
    }

    double taille = width * height;
    double EQM_R = sommeR / taille;
    double EQM_G = sommeG / taille;
    double EQM_B = sommeB / taille;
    double EQM_RGB = (1./3) * (EQM_R + EQM_G + EQM_B);
    double PSNR = 10 * log10(pow(255,2)/EQM_RGB);
    return PSNR;
}

double getPSNRgrey(unsigned char* dataIn1, unsigned char* dataIn2, int width, int height){ // Calcule le PSNR entre les 2 images couleurs dataIn1 et dataIn2 (formule dans cahier)
    int somme = 0 ;
    for(int x = 0; x < height ; ++x){
        for(int y = 0; y < width; y++)
        {
            int In1 = (int) dataIn1[x*width + y + 0];
 
            int In2 = (int) dataIn2[x*width + y + 0];

            somme += pow(In1 - In2,2);
        }
    }

    double taille = width * height;
    double EQM = somme / taille;

    double PSNR = 10 * log10(pow(255,2)/EQM);
    return PSNR;
}

int min(int a, int b){
   if(a<=b) return a;
   else return b;
}

int max(int a, int b){
   if(a>=b) return a;
   else return b;
}