#ifndef CONVERTISSEUR_H
#define CONVERTISSEUR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <cmath>

typedef unsigned char OCTET;
typedef unsigned char OCTET;

std::vector<float> RGBtoHSV(int ntaille,OCTET* ImgIn){
    std::vector<float> HSV;
    for (int i=0; i < ntaille*3; i+=3)
    {
        double R,G,B;
        R = (double)ImgIn[i]/255;
        G = (double)ImgIn[i+1]/255;
        B = (double)ImgIn[i+2]/255;

        double cmax = fmax(R,fmax(G,B));
        double cmin = fmin(R,fmin(G,B));
        double delta = cmax - cmin;
        double H = 0;
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
        H = std::round(H);
        HSV.push_back(H);
        HSV.push_back(S);
        HSV.push_back(cmax);
        // std::cout << "H = " <<  H <<  "S = " <<  S <<  "V = " <<  cmax << std::endl;

    }
    return HSV;
}

std::vector<int> getHistoHSV(std::vector<float> ImgIn, int nTaille3){

    std::vector<int> histogramme(nTaille3, 0);

    for(int i = 0; i < nTaille3; i+=3){
        int valeur = ImgIn[i];
        histogramme[valeur]++;
    }

    return histogramme;

}

int sommeVoisinHSV(const std::vector<int>& histoHSV, int teinte) {
    int somme = 0;
    int voisins = 5; // Nombre de voisins à inclure de chaque côté de la teinte

    if (teinte >= 0 && teinte < histoHSV.size()) {
        // Parcours des voisins dans la plage spécifiée
        for (int i = std::max(0, teinte - voisins); i <= std::min((int)histoHSV.size() - 1, teinte + voisins); ++i) {
            somme += histoHSV[i];
        }
    }

    return somme;
}

int teinte(const std::vector<int>& histoHSV){
    int result = 0;
    int value = 0;

    for(int i = 0; i < histoHSV.size(); i++){
        if (histoHSV[i] > value){
            value = histoHSV[i];
            result = i;
        }
    }
    return result;
}


void HSVtoRGB(float H, float S, float V, int *r, int *g, int *b) {
    float C = S * V;
    float X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    float m = V - C;
    float Rs, Gs, Bs;

    if(H >= 0 && H < 60) {
        Rs = C; Gs = X; Bs = 0;
    } else if(H < 120) {
        Rs = X; Gs = C; Bs = 0;
    } else if(H < 180) {
        Rs = 0; Gs = C; Bs = X;
    } else if(H < 240) {
        Rs = 0; Gs = X; Bs = C;
    } else if(H < 300) {
        Rs = X; Gs = 0; Bs = C;
    } else {
        Rs = C; Gs = 0; Bs = X;
    }

    *r = (Rs + m) * 255;
    *g = (Gs + m) * 255;
    *b = (Bs + m) * 255;
}



std::vector<float>findBestHarmonieMono(const std::vector<int>& histoHSV, std::vector<float> ImgIn, int nTaille3) {
    std::vector<float> ImgOut;
    ImgOut.resize(nTaille3);
    int t = teinte(histoHSV); // On pourra choisir la teinte à la main plus tard

    // On harmonise les couleurs de l'image
    for(int i = 0; i < nTaille3; i+=3){
        ImgOut[i] = t;
        ImgOut[i+1] = ImgIn[i+1];
        ImgOut[i+2] = ImgIn[i+2];
    }

    return ImgOut;
}

std::vector<float> findBestHarmonieCompl(const std::vector<int>& histoHSV, std::vector<float> ImgIn, int nTaille3) {
    std::vector<float> ImgOut;
    ImgOut.resize(nTaille3);
    int t = teinte(histoHSV);
    int complementaire =(t + 180) % 360;

    // On harmonise les couleurs de l'image
    for(int i = 0; i < nTaille3; i+=3){
        if (std::abs(t - ImgIn[i]) < std::abs( complementaire - ImgIn[i])) {
            ImgOut[i] = t;
        } else {
            ImgOut[i] = complementaire;
        }
        ImgOut[i+1] = ImgIn[i+1];
        ImgOut[i+2] = ImgIn[i+2];
    }

    return ImgOut;
}


#endif // CONVERTISSEUR_H
