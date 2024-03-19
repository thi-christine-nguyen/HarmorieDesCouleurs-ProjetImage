// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
#include "math.h"
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
      void RGBtoHSV(std::vector<int,float,float>* HSV,OCTET R,OCTET G,OCTET B){
      double cmax = fmax(R,fmax(G,B));
        double cmin = fmin(R,fmin(G,B));
        double delta = cmax - cmin;
        double H;
        if (delta == 0) {
        H = 0;
        } else if (cmax == R) {
        H = 60 * ((G - B) / delta);
        } else if (cmax == G) {
        H = 60 * (((B - R) / delta) + 2);
        } else if (cmax == B) {
        H = 60 * (((R - G) / delta) + 4);
        }
        if (H<0)
        H += 360;
        float S;
        if ( cmax ==0){
            S = 0;
        } else 
        S = delta/cmax;
        //HSV.push_back(H,S,cmax);
        HSV[i][0]= H;
        HSV[i][1]= S;
        HSV[i][2]= cmax;

    }






  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
   std::vector<int,float,float> HSV;
   for (int i=0; i < nTaille3; i+=3)
     {
        double R,G,B;
        R = (double)ImgIn[i]/255;
        G = (double)ImgIn[i+1]/255;
        B = (double)ImgIn[i+2]/255;
        RGBtoHSV(&HSV,R,G,B);
     }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
