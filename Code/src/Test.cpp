// test_couleur.cpp : Seuille une image en niveau de gris
#include <stdio.h>
#include "image_ppm.h"

class Test{
  public:
    static int RunTest(int argc, char* argv[])
    {
      char cNomImgLue[250], cNomImgEcrite[250];
      int nH, nW, nTaille, S;
      //char color;
      int R,G,B,contraste;
      int valR,valG,valB;
      
      if (argc != 7) 
        {
          printf("Usage: ImageIn.ppm ImageOut.pgm R G B contraste\n"); 
          exit (1) ;
        }
      
      sscanf (argv[1],"%s",cNomImgLue) ;
      sscanf (argv[2],"%s",cNomImgEcrite);
      sscanf (argv[3],"%d",&R);
      sscanf (argv[4],"%d",&G);
      sscanf (argv[5],"%d",&B);
      sscanf (argv[6],"%d",&contraste);
      //  sscanf (argv[3],"%c",&color);
      printf("RGB = %d %d %d\n",R,G,B );

      //printf("color = %c\n",color);


      OCTET *ImgIn, *ImgOut;
      
      lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
      nTaille = nH * nW;
      
      allocation_tableau(ImgIn, OCTET, nTaille*3);
      lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
      allocation_tableau(ImgOut, OCTET, nTaille*3);
      
      

      for(int i = 0; i < nH; i++) {
          for(int j = 0; j < nW*3; j+=3) {
              int iR=i*nW*3+j;
              int iG=i*nW*3+j+1;
              int iB=i*nW*3+j+2;
            //R 
            if(ImgIn[iR]<=R){ // si a la base plus petit que le seuil rouge
              valR=ImgIn[iR]+contraste; // ajout de rouge
              //printf("base = %d et final = %d\n",ImgOut[iR],ImgIn[iR]);
              if(valR>R)valR=R; // si après l'ajout, le seuil est dépassé -> on remet au seuil
            }else{ // si plus grand que le seuil rouge
              valR=ImgIn[iR]-contraste; // on retire du rouge
              //printf("image avant = %d\n",ImgIn[iR]);
              if(valR<R)valR=R; // si on est plus bas que le seuil -> remet au seuil
            }
            if(valR>255)ImgOut[iR]=255; // si rouge depasse 255
            if(valR<0)ImgOut[iR]=0; // si rouge depasse 0

            ImgOut[iR]=valR;


            //G 
            if(ImgIn[iG]<=G){ 
              valG=ImgIn[iG]+contraste; 
              if(valG>G)valG=G; 
            }else{ 
              valG=ImgIn[iG]-contraste; 
              if(valG<G)valG=G; 
            }
            if(valG>255)ImgOut[iG]=255; 
            if(valG<0)ImgOut[iG]=0;

            ImgOut[iG]=valG;


            //B
            if(ImgIn[iB]<=B){
              valB=ImgIn[iB]+contraste; 
              if(valB>B)valB=B; 
            }else{ 
              valB=ImgIn[iB]-contraste; 
            
              if(valB<B)valB=B; 
            }
            if(valB>255)ImgOut[iB]=255; 
            if(valB<0)ImgOut[iB]=0; 

            ImgOut[iB]=valB;

            
          

          }
      }

    printf("contrastee = %d et R = %d\n",contraste,R);


      


      ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
      free(ImgIn);
      return 1;
    }


};
