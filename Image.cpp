/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.cpp
 * Author: Joy_Admin
 *
 * Created on 17 octobre 2016, 12:35
 */

#include "Image.h"
#include <fstream> // ifstream
#include <sstream> //sstream
#include <vector> //vector
#include <cstdlib>
#include <cmath>
using namespace std;
Image::Image(){

}

bool Image::test(string file)
{
    int  heig = 0, wid = 0;
    ifstream infile(file.c_str());
    stringstream ss;
    string inputLine = "";

    // First line : version
    getline(infile,inputLine);
    if(inputLine.compare("P2") != 0) 
    {
        cerr << "Erreur!!!!!!, Impossible de travailler sur le fichier." << endl;
        SetValide(false) ;
    }
    cout << "\n" << endl;
    // Second line : comment
    getline(infile,inputLine);

    // Continue with a stringstream
    ss << infile.rdbuf();
    // Third line : size
    ss >> wid >> heig;
  
    infile.close();
  
    return wid != 0 && heig!= 0;
}

Image::Image(bool val)
{
    valide = val;
}


Image::Image(string file)
{
    reload(file);
}
//*/

/**
 * on charge une image 
 * @param output
 * @return 
 */
bool Image::reload(string output) {
    string file = output;
  valide = test(file);
   if(valide)
   {
  int row = 0, col = 0, height = 0, width = 0;
  ifstream infile(file.c_str());
  stringstream ss;
  string inputLine = "";

  // First line : version
  getline(infile,inputLine);
  cout << "\t*****Analyse de votre fichier.*****\n" << endl;
  if(inputLine.compare("P2") != 0) cerr << "Erreur!!!!!!!, Impossible de travailler sur le fichier.\n" << endl;
  else 
  {
      version = inputLine;
      cout << "NomFichier : " << file << endl;
      file = file.substr(0,file.size()-4);
      SetfileName(file);
      cout << "Version : " << inputLine << endl;
  }

  // Second line : comment
  getline(infile,inputLine);
  cout << "Comment : " << inputLine << endl;

  // Continue with a stringstream
  ss << infile.rdbuf();
  // Third line : size
  ss >> width >> height;
  Setwidth(width);
  Setheight(height);
  cout << width << " columns and " << height << " rows" << endl;
  
  // Fourth line : size
  ss >> niveau;
  SetNiveau(niveau);
  cout << "Niveau " << niveau  << endl;
  array = new int* [height];
  minval = niveau;
  maxval = 0;
  // Following lines : data
  for(row = 0; row < height; ++row)
  {
       array[row] = new int[width];
    for (col = 0; col < width; ++col) 
    {
        ss >> array[row][col];
        
        if ( array[row][col] > maxval )
        {
            maxval =  array[row][col];
        }
        if ( array[row][col] < minval )
        {
            minval =  array[row][col];
        }
    }
  }
  Setmaxval(maxval);
  Setminval(minval);
 
 /*/ Now print the array to see the result
  for(row = 0; row < height; ++row) {
    for(col = 0; col < width; ++col) {
      cout << array[row][col] << " ";
    }
    cout << endl;
  }//*/
  infile.close();
  cout << "\t*****Fin de l'analyse.*****\n" << endl;
      SetLuminance(CalLuminance());
   }
}


//on ecrit l'image de sortie
bool Image::writeImage(string output){
    ofstream Flux(output.c_str());
    if(Flux)
    {
        Flux<<version<<endl;
        Flux<<"#Creator : Joy Jedidja Ndjama Version 1.1"<<endl;
        Flux<<width<<" "<<height<<endl;
        Flux<<niveau<<endl;
        for(int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col) Flux << array[row][col]<< endl;
           
        return true;
    }
    else
    {
        cout<<"Erreur lors de l'ouverture du fichier"<<endl;
        return false;
    }
}

/**
 * 
 * on calcule la luminance
 * @return 
 */
double Image::CalLuminance()
{
    return CalLuminance(array);
}

/**
 * 
 * on calcule la luminance
 * @return 
 */
double Image::CalLuminance(int** arr)
{
    double luminance = 0;
    
    for(int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col) luminance += arr[row][col];
    
    luminance /= (height * width);
    
    return luminance;
}

/**
 * on calcule le contraste
 * @return 
 */
double Image::CalContraste()
{
    return CalContraste(array);
}

/**
 * on calcule le contraste
 * @return 
 */
double Image::CalContraste(int** arr)
{
    double contraste = 0.0;
    
    
    for(int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col) contraste += pow(arr[row][col] - luminance,2) ;
    
    contraste = sqrt(contraste * 1/(width * height));
    return contraste;
}

/**
 * On construit une image connaissant tous ses pixels
 * @param arr
 * @return 
 */
bool Image::writeImage(int** arr,int zoom1,int zoom2){
    writeImage(arr,zoom1,zoom2,false);
}

bool Image::writeImage(int** arr, int i, int j, bool val) {
    int wid = j * width;
    int hei = i * height;

    ofstream Flux(output.c_str());
    if(Flux)
    {
        Flux<<version<<endl;
        Flux<<"#Creator : Joy Jedidja Ndjama Version 1.1"<<endl;
        Flux<<wid<<" "<<hei<<endl;
        Flux<<niveau<<endl;
        if(val)cout<<"\tEcriture du fichier resultat en cours ";

        for(int row = 0; row < hei; ++row)
        {  if(val) cout<<" ... ";
            for (int col = 0; col < wid; ++col) 
            {
                Flux <<arr[row][col]<<endl; 
            }
        }  
         if(val) cout<<"\n Terminee "<<endl;
        //Flux.close();
        return true;
    }
    else
    {
        cout<<"Erreur lors de l'ouverture du fichier"<<endl;
        //Flux.close();
        return false;
    }
}


/**
 * On construit une image connaissant tous ses pixels
 * @param arr
 * @return 
 */
bool Image::writeImage(int** arr){
    writeImage(arr,1,1);
}

/**
 * transformation linéaire
 * @return 
 */
bool Image::transformationLineaire()
{
    SetOutput(GetfileName()+"Transformation_Lineaire.pgm");
    transformationLineaireSaturation(minval,maxval);
}

/**
 * transformation lineaire par saturation
 * @param sMin
 * @param sMax
 * @return 
 */
bool Image::transformationLineaireSaturation(int sMin, int sMax)
{
    int pas = sMax - sMin;
    if(pas == 255)
    {
        cout<<"\t Pas besoin d'effectuer de transformation lineaire puisse que le "
                "pas optimal de cet image est de 255\n"<<endl;
        cout<<"\t Vous obtiendrez la meme image en sortie\n"<<endl;
        return false;
    }
    else
    {
        int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
              arr[row][col] = (255 * (array[row][col] - minval)) / (pas);
              
              if ( arr[row][col] <= 0) 
              {
                  arr[row][col] = 0;
              }
              if (arr[row][col] >= 255)
              {
                  arr[row][col] = 255;
              }
          }
        }
        
         if(sMin != minval)SetOutput(GetfileName()+"Transformation_Lineaire_Sat.pgm");
         writeImage(arr);
         cout<<"\tTransformation lineaire terminee\n"<<endl;
         cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
    }
}

/**
 * egalisation des histogrammes
 * @return 
 */
bool Image::egalisationHistogramme() {

    //etape une: calcul de l'histogramme
    int* histogramme = constructionHistogramme(array);
    
    //etape deux: normalisation de l'histogramme
    double* histogramme1 = normalistationHistogramme(histogramme); 
    
    //etape trois: densité de probalité normalisé
    histogramme1 = densiteHistogramme(histogramme1);
    
    //etape quatre: transformation des niveaux de gris de l'image
     int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = histogramme1[array[row][col]] * 255 ;  
          }
        }
     
     SetOutput(GetfileName()+"Egalisation.pgm");
     writeImage(arr);
     cout<<"\tEgalisation des histogrammes terminee\n"<<endl;
        cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
    return true;
}

/**
 * on construit l'histogramme de base
 * @param arr
 * @return 
 */
int* Image::constructionHistogramme(int** arr) {
    int* histogramme = new int[256];
    for (int col = 0; col < 255; col++)
        {
            
             histogramme[col] = 0;
            
        }
    
     for(int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col)
        {
            {
                for(int i = 0; i < 255; i++)
                {
                    if (array[row][col] == i)
                    {
                        ++histogramme[i];
                    }
                }
            }
        }
    return histogramme;
}

/**
 * on normalise l'histogramme
 * @param histogramme
 * @return 
 */
double* Image::normalistationHistogramme(int* histogramme) {
    double* histogramme1 = new double[256];
    double pixel = width * height;
    for (int col = 0; col < 255; col++)
        { 
             histogramme1[col] = ( histogramme[col] / pixel);  
        }
    
    return histogramme1;
}

/**
 * on calcule la densité de probalité normalisé
 * @param histogramme
 * @return 
 */
double* Image::densiteHistogramme(double* histogramme) {
    double* histogramme1 = new double[256];
    
    for (int col = 0; col < 255; col++)
    { 
         for (int c = 0; c <= col; c++)
        { 
             histogramme1[col] += histogramme[c];  
        }
    }
    
    return histogramme1;
}

/**
 * on additionne deux images
 * @param image
 * @return 
 */
bool Image::additionImage(Image& image) {
int** arr = new int* [width];
int** arr1 = image.GetArray();

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = arr1[row][col] + array[row][col] ; 
            if (arr[row][col] >= 255)
            {
                  arr[row][col] = 255;
            }
          }
        }
     SetOutput(GetfileName()+"Addition.pgm");
     bool result = writeImage(arr);
     cout<<"\tAddition des deux images terminee\n"<<endl;
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
}

/**
 * on additionne deux images
 * @param image
 * @return 
 */
int** Image::additionImage(int** arr1,int** arr2) {
int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = arr1[row][col] + arr2[row][col] ; 
            if (arr[row][col] >= 255)
            {
                  arr[row][col] = 255;
            }
          }
        }

    return (arr);
    
}

/**
 * on soustrait deux images
 * @param image
 * @return 
 */
bool Image::soustractionImage(Image& image) {
int** arr = new int* [width];
int** arr1 = image.GetArray();

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = array[row][col] - arr1[row][col] ; 
            if (arr[row][col] <= 0)
              {
                  arr[row][col] = 0;
              }
          }
        }
      SetOutput(GetfileName()+"Soustraction.pgm");
     bool result = writeImage(arr);
     cout<<"\tSoustraction des deux images terminee\n"<<endl;
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
}

/**
 * on multiplie une image par un facteur
 * @param fac
 * @return 
 */
bool Image::multiplicationImage(double fac) {
    int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = array[row][col] * fac ; 
            if (arr[row][col] <= 0)
              {
                  arr[row][col] = 0;
              }
            if (arr[row][col] >= 255)
              {
                  arr[row][col] = 255;
              }
          }
        }
     
      SetOutput(GetfileName()+"Multiplication.pgm");
     bool result = writeImage(arr);
     cout<<"\tMultiplication de l'image terminee\n"<<endl;
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
    
}

/**
 * on augmente la luminosite de l'image
 * @param fac
 * @return 
 */
bool Image::luminositeImage(double fac) {
int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = array[row][col] + fac ; 
            if (arr[row][col] <= 0)
              {
                  arr[row][col] = 0;
              }
            if (arr[row][col] >= 255)
              {
                  arr[row][col] = 255;
              }
          }
        }
     
      SetOutput(GetfileName()+"Luminosite.pgm");
     bool result = writeImage(arr);
     cout<<"\tAncienne luminance: "<<GetLuminance() <<" \n"<<endl;
     cout<<"\tNouvelle luminance: "<<CalLuminance(arr) <<" \n"<<endl;
     if(fac > 0 )cout<<"\tAugmentation de la luminosite terminee\n"<<endl;
     if(fac < 0 )cout<<"\tDimunition de la luminosite terminee\n"<<endl;
     
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
}

/**
 * on augmente la luminosite de l'image
 * @param fac
 * @return 
 */
bool Image::contrasteImage(double fac) {
    
    double contraste = CalContraste();
    double luminance = GetLuminance();
    double coef = 0;
 
    coef = ( contraste + fac ) / contraste;
    
int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = coef*array[row][col] ; 
            if (arr[row][col] <= 0)
              {
                  arr[row][col] = 0;
              }
            if (arr[row][col] >= 255)
              {
                  arr[row][col] = 255;
              }
          }
        }
     
     SetOutput(GetfileName()+"Contraste.pgm");
     bool result = writeImage(arr);
     cout<<"\tAncienne contraste: "<<contraste <<" \n"<<endl;
     double cont = CalContraste(arr),diff;
     cout<<"\tNouveau contraste: "<< cont <<" \n"<<endl;
     string res = "";
     if(fac > 0 )res =" L'augmentation" ;
     if(fac < 0 )res = "La dimunition" ;
     diff = abs(contraste - cont);
     if(diff < abs(fac - 2)) 
     {
         cout<<"\tDesole, nous n'avons pas atteint "<<res<<" de "<<fac<<" que vous souhaitiez\n"<<endl;
          if(fac > 0 )cout<<"\tRessayez avec une valeur plus petite.\n"<<endl;
          if(fac < 0 )cout<<"\tRessayez avec une valeur plus grande.\n"<<endl;
     }
     cout<<"\t"<<res<<" de "<< diff<<" du contraste est terminee\n"<<endl;
     
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
}

/**
 * on inverse l'image
 * @return 
 */
bool Image::inversionImage() {
int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          {
            arr[row][col] = 255 - array[row][col]  ; 
            if (arr[row][col] <= 0)
              {
                  arr[row][col] = 0;
              }
          }
        }
      SetOutput(GetfileName()+"Inversion.pgm");
     bool result = writeImage(arr);
     cout<<"\tInversion terminee\n"<<endl;
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
}

/**
 * on renverse l'image
 * @return 
 */
bool Image::renverseImage() {
int** arr = new int* [width];

        for(int row = 0; row < height; ++row)
        {
             arr[row] = new int[width];
          for (int col = 0; col < width; ++col) 
          { 
            arr[row][col] = array[height - row - 1][width - col -1]  ; 
          }
        }
     
      SetOutput(GetfileName()+"Renverse.pgm");
     bool result = writeImage(arr);
     cout<<"\tL'image a ete renverse\n"<<endl;
     cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
     
     return result;
}

/**
 * on fait le zoom sur l'image
 * @return 
 */
bool Image::zoomImage(int zoom1,int zoom2) {

    int hei = zoom1* height;
    int wid = zoom2 * width;
  int** arr1 = new int* [hei];
  
 
  int col1 = 0, row1 = 0;

  // Following lines : data
  for(int row = 0; row < height; ++row)
  {
      for(int j = 0; j < zoom1; ++j)
      {
        arr1[row1+j] = new int[wid];

      }
       
    for (int col = 0; col < width; ++col) 
    { 
        for(int i = 0; i < zoom1; ++i)
        {   for(int j = 0; j < zoom2; ++j)
            {
                arr1[row1+i][col1+j] = array[row][col];
                
            }
        }
        col1 += zoom2;
    }//*/
       col1 = 0;
       row1 += zoom1;
       
  }
       
       
  SetOutput(GetfileName()+"zoom.pgm");//GetfileName()
  writeImage(arr1,zoom1,zoom2,true);
  cout<<"\tL'image a ete zoome\n"<<endl;
  cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
}

/**
 * convulution avec filtre moyenneur
 * @param dim
 * @return 
 */
bool Image::convolutionFiltreMoyenneur(int dim) {

    int** R;
    

    R = new int* [height];
    
        for(int i=0; i < height; i++){
            R[i] = new int[width];
            for(int j=0; j < width; j++){
                R[i][j] = 0;
            }
        }

        int m(dim/2);

        for(int i=m; i < height - m; i++){
            for(int j=m; j < width - m; j++){
                for(int k=0; k < dim; k++){
                    for(int l=0; l < dim; l++){
                        R[i][j] += array[i-k+m][j-l+m];
                    }
                }
                R[i][j] /= pow(dim,2);
            }
        }
        SetOutput(GetfileName()+"FiltreMoyenneur.pgm");
        bool result =  writeImage(R);
        cout<<"\tLe filtre moyenneur a ete applique a l'image\n"<<endl;
        cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
        return result;
}

/**
 * la convolution avec filtre gaussien
 * @param dim
 * @param sigma
 * @return 
 */
bool Image::convolutionFiltreGaussien(int dim) {
int** R;
double K[dim][dim];

//construction de la matrice gaussienne
double  facteurGaussien = 0.0;

if(dim == 3)
{
    K[0][0] = 1;
    K[0][1] = 2;
    K[0][2] = 1;
    K[1][0] = 2;
    K[1][1] = 4;
    K[1][2] = 2;
    K[2][0] = 1;
    K[2][1] = 2;
    K[2][2] = 1;
}
else
{
    K[0][0] =  K[4][4] = K[4][0] = K[0][4] =  1;
    K[0][1] = K[1][0] = K[4][1] = K[4][3] =  K[3][0] = K[3][4] = K[0][3] = K[1][4] =  2;
    K[1][2] =  K[1][3] =  K[3][2] = K[3][3] =  6;
    K[2][0] = K[2][4] = K[0][2] = K[4][2] = 3;
    K[2][1] = K[2][3] = K[1][1] =  K[3][1] = 8;
    K[2][2] = 10; 
}
    
   
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
           facteurGaussien += K[i ][j ]  ;
        }
    }
    

    R = new int* [height];
    
        for(int i=0; i < height; i++){
            R[i] = new int[width];
            for(int j=0; j < width; j++){
                R[i][j] = 0;
            }
        }

        int m(dim/2);

        for(int i=m; i < height - m; i++){
            for(int j=m; j < width - m; j++){
                for(int k=0; k < dim; k++){
                    for(int l=0; l < dim; l++){
                        R[i][j] += array[i-k+m][j-l+m]*K[dim-1-k][dim-1-l];
                      
                    }
                }
                R[i][j] /=  facteurGaussien ;
            }
        }
        
         SetOutput(GetfileName()+"FiltreGaussien.pgm");
        bool result =  writeImage(R);
        cout<<"\tLe filtre gaussien a ete applique a l'image\n"<<endl;
        cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
        return result;
}
//*/

/**
 * convolution filtre median
 * @param dim
 * @return 
 */
bool Image::convolutionFiltreMedian(int dim) {

    int** R;
    int** K;

//construction de la matrice gaussienne

    R = new int* [height];
    
        for(int i=0; i < height; i++){
            R[i] = new int[width];
            for(int j=0; j < width; j++){
                R[i][j] = 0;
            }
        }

    K = new int* [dim];
    
        for(int i=0; i < dim; i++){
            K[i] = new int[dim]; 
        }
    
        int m(dim/2);

        for(int i=m; i < height - m; i++){
            for(int j=m; j < width - m; j++){
                for(int k=0; k < dim; k++){
                    for(int l=0; l < dim; l++){
                        K[dim-1-k][dim-1-l] = array[i-k+m][j-l+m] ;
                    }
                }
                R[i][j] =  mediane (K,dim);
            }
        }
        
         SetOutput(GetfileName()+"FiltreMedian.pgm");
        bool result =  writeImage(R);
        cout<<"\tLe filtre median a ete applique a l'image\n"<<endl;
        cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
        return result;
}

/**
 * renvoit la valeur mediane pour un pixel donné
 * @param K
 * @param dim
 * @return 
 */
int Image::mediane(int** K,int dim) {
    
    int dim1 = dim*dim;
    int temp[dim1],temp1[dim1];
    int k = 0, echange = 0 , aux = 0;
    for(int i=0; i < dim; i++){
          for(int j=0; j < dim; j++){
              temp[k] = K[i][j];
              temp1 [k] = 255;
              k++;
          }
    }
    for(int i=0; i < dim1; i++){
          for(int j = i; j < dim1; j++){
              if(temp[j] < temp1[i])
              {
                  temp1[i] = temp[j];
                  echange = j;
              }
          }
          aux = temp[i];
          temp[i] = temp[echange];
          temp[echange] = aux;
    }
//    for(int j = 0; j < dim1; j++){
//               cout<<temp[j]<< "     "<<temp1[j]<<endl;
//          }
//    
    return temp1[dim];
}

/**
 * On applique le filtre de Roberts
 * @return 
 */
bool Image::contourRoberts() {
    
    int dim = 2;
    double** K = new double* [dim];
    
        for(int i=0; i < dim; i++){
            K[i] = new double[dim]; 
        }
    K[0][0] = 1;
    K[1][1] = -1;
    K[0][1] = K[1][0] = 0;
    
    int** R = convolution(array,K,2);
    
    K[0][0] = K[1][1] = 0;
    K[0][1] = 1;
    K[1][0] = -1;
    
    int** R1 = convolution(R,K,2);
    
    R = additionImage(R,R1);
    
    SetOutput(GetfileName()+"ContourRoberts.pgm");
    bool result =  writeImage(R);
    cout<<"\tLes contours de l'image ont pu etre ressorti.\n"<<endl;
    cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
    return result;
}

/**
 * filtre de Prewitt
 * @return 
 */
bool Image::contourPrewitt() {
int dim = 3;
    double** K = new double* [dim];
    
        for(int i=0; i < dim; i++){
            K[i] = new double[dim]; 
            for(int j=0; j < dim; j++){
                if(i == 0)
                {
                    K[i][j] = -1;
                }
                if(i == 1)
                {
                   K[i][j] = 0;
                }
                if(i == 2)
                {
                   K[i][j] = 1; 
                }
            }
        }
        
    
    int** R = convolution(array,K,2);
    
   for(int i=0; i < dim; i++){
        for(int j=0; j < dim; j++){
            if(j == 0)
            {
                K[i][j] = -1;
            }
            if(j == 1)
            {
               K[i][j] = 0;
            }
            if(j == 2)
            {
               K[i][j] = 1; 
            }
        }
    }
   
    
    
    int** R1 = convolution(R,K,2);
    
    R = additionImage(R,R1);
    
    SetOutput(GetfileName()+"ContourPrewitt.pgm");
    bool result =  writeImage(R);
    cout<<"\tLes contours de l'image ont pu etre ressorti.\n"<<endl;
    cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
    return result;
}

bool Image::contourSobel() {
int dim = 3;
    double** K = new double* [dim];
    
        for(int i=0; i < dim; i++){
            K[i] = new double[dim]; 
            for(int j=0; j < dim; j++){
                if((j == 0 || j == 2) && (i != 1))
                {
                    K[i][j] = -1;
                    if(i == 2) K[i][j] *= -1;   
                }
                if(j == 1 && i != 1)
                {
                    K[i][j] = -2;
                    if(i == 2) K[i][j] *= -1;  
                }
                if(i == 1)
                {
                   K[i][j] = 0;
                }
            }
        }

   
    int** R = convolution(array,K,2);
    
   for(int i=0; i < dim; i++){
        for(int j=0; j < dim; j++){
            if((i == 0 || i == 2) && (j != 1))
            {
                K[i][j] = -1;
                if(j == 2) K[i][j] *= -1;   
            }
            if(i == 1 && j != 1)
            {
                K[i][j] = -2;
                if(j == 2) K[i][j] *= -1;  
            }
            if(j == 1)
            {
               K[i][j] = 0;
            }
        }
    }
    
    
    
    int** R1 = convolution(R,K,2);
    
    R = additionImage(R,R1);
    
    SetOutput(GetfileName()+"ContourSobell.pgm");
    bool result =  writeImage(R);
    cout<<"\tLes contours de l'image ont pu etre ressorti.\n"<<endl;
    cout<<"\tConsultez l'image "<<output <<" pour voir le resultat\n"<<endl;
    return result;
}


/**
 * ON applique l'algorithme de convulution
 * @param arr
 * @param K
 * @param dim
 * @return 
 */
int** Image::convolution(int** arr,double** K,int dim) {

int** R;
    

    R = new int* [height];
    
        for(int i=0; i < height; i++){
            R[i] = new int[width];
            for(int j=0; j < width; j++){
                R[i][j] = 0;
            }
        }

        int m(dim/2);

        for(int i=m; i < height - m; i++){
            for(int j=m; j < width - m; j++){
                for(int k=0; k < dim; k++){
                    for(int l=0; l < dim; l++){
                        R[i][j] += arr[i-k+m][j-l+m]*K[dim-1-k][dim-1-l];
                      
                    }
                }
            }
        }
        

      return (R);
        
}


Image::~Image()
{
    //dtor
}
