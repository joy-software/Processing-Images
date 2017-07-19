/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.h
 * Author: Joy_Admin
 *
 * Created on 17 octobre 2016, 12:21
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Image

{
       // construction de la matrix avex le vecteur recuppérer
    protected:
        void printMatrix(vector< vector<int> > I);

        // les attributs pour chaque images
    private:
        int height;
        int width;
        string version;
        int niveau;
        int maxval;
        int minval;
        double luminance ;
        int** array;
        string fileName;
        string output;
        bool valide;

    // les différentes méthodes de traitement
    public:
        Image();
        Image(string file);
        Image(bool val);
        virtual ~Image();
        
    // les getteurs et setteurs
        int Getheight() { return height; }
        void Setheight(int val) { height = val; }
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        string Getversion() { return version; }
        void Setversion(string val) { version = val; }
        int Getmaxval() { return maxval; }
        void Setmaxval(int val) { maxval = val; }
        string GetfileName() { return fileName; }
        void SetfileName(string val) { fileName = val; }
        string GetOutput() { return output; }
        void SetOutput(string val) { output = val; }
        int Getminval() { return minval; }
        void Setminval(int val) { minval = val; }
        int GetNiveau() { return niveau; }
        void SetNiveau(int val) { niveau = val; }
        int** GetArray() { return array; }
        void setArray(int** arr) { array = arr; }
        void SetLuminance(double val) { luminance = val; }
        double GetLuminance() { return luminance; }
        bool GetValide(){return valide;}
        bool SetValide(bool val){valide = val;}
        
        bool test(string name);
        bool reload(string output);
        bool writeImage(string output);
        bool writeImage(int** arr);
        bool writeImage(int** arr, int i,int j);
        bool writeImage(int** arr, int i,int j,bool val);

     //différentes opérations sur les images
        double CalLuminance();
        double CalLuminance(int** arr);
        double CalContraste();
        double CalContraste(int** arr);
        bool transformationLineaire();
        bool transformationLineaireSaturation(int sMin,int sMax);
        bool egalisationHistogramme();
        int* constructionHistogramme(int** arr);
        double* normalistationHistogramme(int* histogramme);
        double* densiteHistogramme(double* histogramme);
        bool additionImage(Image &image);
        int** additionImage(int** R,int** R1);
        bool soustractionImage(Image &image);
        bool multiplicationImage(double fac);
        bool luminositeImage(double fac);
        bool contrasteImage(double fac);
        bool inversionImage();
        bool renverseImage();
        bool zoomImage(int zoom1,int zoom2);
        bool convolutionFiltreMoyenneur(int dim);
        bool convolutionFiltreGaussien(int dim);
        bool convolutionFiltreMedian(int dim);
        int mediane(int** K,int dim);
        bool contourRoberts();
        bool contourPrewitt();
        bool contourSobel();
        int** convolution(int** arr,double** K,int dim);


       


};

#endif // IMAGE_H




