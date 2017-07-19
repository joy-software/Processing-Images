/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Joy_Admin
 *
 * Created on 17 octobre 2016, 10:45
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cmath>

#include "Image.h"

using namespace std;

/*
 * 
 */

void message(string operation){
    cout<<"-------------------"<<operation<<"------------------------"<<endl;
}

void erreur(string operation){
    cout<<"/*-/*-/*-/*-/*-/*-/*-"<<operation<<"*-/*-/*-/*-/*-/*-/*-/"<<endl;
}

void message(string operation, double val){
    cout<<"-------------------"<<operation<< val<<"------------------------"<<endl;
}

int main(int argc, char** argv) {
    
   string nomImage="",response;
   //Image imageTraite;
   bool valid = false, result = false;
   int choix = 0;
   int smin = -1;
   int smax = 256, zoom1 = 0, zoom2 = 0,count = 0,res = 0;
   double fac = 0.0;
   Image imageTraite(false);
   
   cout << "\tJoy vous salut: Bienvenue a vous!!!." << endl;
   
    cout<< "\n\tNous allons effectuer quelques traitements sur une image de votre choix\n"<<endl;
    cout<<"\n\t ****ATTENTION!!!!!!! Votre image doit etre au format .pgm****\n"<< endl;
 
    do
    {
       cout<<"\tSaisir le nom de votre image(ex test.pgm)"<< endl;
    
        //on recupère le nom de l'image
        cin>>nomImage; 
        cout <<"\n\n" << endl; 
        result = imageTraite.test(nomImage);
    }
    while(!result);

       cout<<"\tImage valide....."<< endl;
       cout <<"\n\n" << endl; 
       message("Debut des traitements");
       cout <<"\n\n" << endl;  
      imageTraite.reload(nomImage);
    do
    {
       choix = 0; 
      while(choix<1||choix>21){
        cout <<"\n\n" << endl; 
        cout <<"Que souhaitez vous faire?" << endl;
        cout <<"\t1->  Calcul de la valeur de la Luminance" << endl;
        cout <<"\t2->  Calcul de la valeur du Contraste" << endl;
        cout <<"\t3->  Augmenter/Diminuer la Luminosite" << endl;
        cout <<"\t4->  Augmenter/Diminuer le Contraste" << endl;
        cout <<"\t5->  Effectuer la transformation Lineaire" << endl;
        cout <<"\t6->  Effectuer la transformation par Saturation" << endl;
        cout <<"\t7->  Effectuer l'Egalisation des Histogrammes" << endl;
        cout <<"\t8->  Additionner a une autre image de meme dimension" << endl;
        cout <<"\t9->  Soustraire a une autre image de meme dimension" << endl;
        cout <<"\t10-> Multiplication d'une Image" << endl;
        cout <<"\t11-> Inverser l'Image" << endl;
        cout <<"\t12-> Renverser l'Image" << endl;
        cout <<"\t13-> Faire un Zoom plus sur l'Image" << endl;
        cout <<"\t14-> Effectuer la convolution par filtre moyenneur" << endl;
        cout <<"\t15-> Effectuer la convolution par filtre gaussien" << endl;
        cout <<"\t16-> Effectuer la convolution par filtre median" << endl;
        cout <<"\t17-> Contour Filtre Roberts" << endl;
        cout <<"\t18-> Contour Filtre Prewitt" << endl;
        cout <<"\t19-> Contour Filtre Sobel" << endl;
        cout <<"\t20-> Changer d'image" << endl;
        cout <<"\t21-> Quitter" << endl;
        message("Copyright, 2016 - Joy Jedidja NDJAMA");
        cout <<"\n\n" << endl;
        cin>>response;
        choix = atoi(response.c_str());
    }
    cout <<"\n\n" << endl; 
    switch(choix){
    case 1:
        message("Calcul de la valeur de la Luminance");
        if(imageTraite.CalLuminance()){
            message(" Le Traitement s'est bien effectue");
            message("Luminance: ",imageTraite.GetLuminance());
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 2:
        message("Calcul de la valeur du Contraste");
       
            message(" Le Traitement s'est bien effectue");
            message("Contraste: ",imageTraite.CalContraste());
        break;
    case 5:
        message("Effectuer la transformation Lineaire");
        cout<<"  "<<endl;
        if(imageTraite.transformationLineaire()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 6:
        
        message("Effectuer la transformation par Saturation");
        cout<<"  "<<endl;
        while(smin< 0 || smin>255)
        {
            cout<<"Quelle est la saturation minimale? "<<endl;
            cout<<"Entrez un nombre entre 0 et 255"<<endl;

            cin>>response;
            smin = atoi(response.c_str());
        }
         cout<<"\n"<<endl;
        while(smax< 0 || smax>255 || smax < smin)
        {
             cout<<"Quelle est la saturation maximale?\n";
            cout<<"Entrez un nombre entre 0 et 255"<<endl;
            cout<<"Un nombre plus grand que smin"<<endl;
           
            cin>>response;
            smax = atoi(response.c_str());;
        }
        
        if(imageTraite.transformationLineaireSaturation(smin,smax)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        smin = -1;
        smax = 256;
        break;//
    case 7:
        message("Effectuer l'Egalisation des Histogrammes");
        cout<<"  "<<endl;
        if(imageTraite.egalisationHistogramme()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;//
    case 8:
        message("Additionner a une autre image de meme dimension");
        valid = false;
        count = 0;
        while(!valid && count < 2)
        {
            cout<<"  "<< endl;
            cout<<"\tSaisir le nom la deuxieme image(ex test.pgm)"<< endl;
            count++;
            //on recupère le nom de l'image
            cin>>nomImage; 
            Image imageTraite2(nomImage);
            if(imageTraite2.Getwidth() == imageTraite.Getwidth() || imageTraite2.Getheight() == imageTraite.Getheight())
            {
              if(imageTraite.additionImage(imageTraite2)){
                message(" Le Traitement s'est bien effectue");
                }
                else{
                erreur("Erreur lors du traitement.");
                 }  
              valid = true;
            }
            else
            {
                 erreur("Choississez des images de meme dimension.");
                 cout<<"\n"<< endl;
                 cout<<"\til ne vous reste qu'un essai, apres quoi vous irez au menu principal"<< endl;
                 valid = false;
            }
        }
        break;
    case 9:
        message("Soustraire a une autre image de meme dimension");
         valid = false;
         count = 0;
        while(!valid && count < 2)
        {
            cout<<"  "<< endl;
            cout<<"\tSaisir le nom la deuxieme image(ex test.pgm)"<< endl;
            count++;
            //on recupère le nom de l'image
            cin>>nomImage; 
            Image imageTraite2(nomImage);
            if(imageTraite2.Getwidth() == imageTraite.Getwidth() || imageTraite2.Getheight() == imageTraite.Getheight())
            {
              if(imageTraite.soustractionImage(imageTraite2)){
                message(" Le Traitement s'est bien effectue");
                }
                else{
                erreur("Erreur lors du traitement.");
                 }  
              valid = true;
            }
            else
            {
                 erreur("Choississez des images de meme taille.");
                 cout<<"\n"<< endl;
                 cout<<"\til ne vous reste qu'un essai, apres quoi vous irez au menu principal"<< endl;
                 valid = false;
            }
        }
        break;
    case 10: 
        message("Multiplication d'une Image");
        cout<<"  "<<endl;
         fac = 0; 
        do
        {
            cout<<"Entrez un nombre representant le facteur (different de zero)"<<endl;
            cin>>response;
            fac = atof(response.c_str());
        }
        while(fac==0);
        if(imageTraite.multiplicationImage(fac)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 3: 
        message("Augmenter/Diminuer la Luminosite");
        cout<<"  "<<endl;
         fac = 0; 
        do
        {
            cout<<"De combien souhaitez vous augmenter/Diminuer la luminosite?"<<endl;
            cout<<"Entrer ce nombre"<<endl;
            cin>>response;
            fac = atof(response.c_str());
        }
        while(fac==0);
        if(imageTraite.luminositeImage(fac)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 4: 
        message("Augmenter/Diminuer le Contraste");
        cout<<"  "<<endl;
        fac = 0;
        do
        {
        cout<<"De combien souhaitez vous augmenter/diminuer le Contraste?"<<endl;
        cout<<"Entrer ce nombre"<<endl;
        cin>>response;
        fac = atof(response.c_str());
        }
        while(fac==0);
        if(imageTraite.contrasteImage(fac)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 11: 
        message("Inverser une Image");
        cout<<"  "<<endl;
        if(imageTraite.inversionImage()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 12: 
        message("Renverser une Image");
        cout<<"  "<<endl;
        if(imageTraite.renverseImage()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 13: 
        message("Faire un Zoom plus sur l'Image");
        cout<<"  "<<endl;
        cout<<"De combien souhaitez vous zoomer?"<<endl;
        cout<<"Choississez des zoom au moins egal a 1"<<endl;
        valid = false;
        count = 0;
        zoom1 = 0; zoom2 = 0;
        while(!valid && count < 2)
        {
            while(zoom1 < 1 && count < 3)
            {
                cout<<"Entrer la valeur du zoom vertical"<< endl;
                cin>>response;
                zoom1 = atoi(response.c_str());
                count++;
                if(zoom1 > 0)valid = true;
            }
            count--;
           
             while(zoom2 < 1 && count < 3)
            {
                cout<<"Entrer la valeur du zoom horizontal"<< endl;
                cin>>response;
                zoom2 = atoi(response.c_str());
                count++;
                if(zoom2 > 0)valid = true;
            }
            
           
            
            if(valid)
            {
               if(imageTraite.zoomImage(zoom1,zoom2)){
                   message(" Le Traitement s'est bien effectue");
                }
                else{
                    erreur("Erreur lors du traitement");
                }
                valid = true;
            }
            else
            {
                 erreur("Erreur!!!!!Choississez des images de même taille.");
                 valid = false;
            }
        }
        
       
        break;   
   
    case 14: 
        message("Effectuer la convolution par filtre moyenneur");
        cout<<"  "<<endl;
        cout<<"Entrer la dimension du filtre (un nombre impair plus grand que 1, 3 est choisi par defaut): "<< endl;
        
        cin>>response;
        zoom1 = atoi(response.c_str());
        if(zoom1%2 == 0 || zoom1 == 1) zoom1 = 3;
        if(imageTraite.convolutionFiltreMoyenneur(zoom1)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;  
    case 15: 
        message("Effectuer la convolution par filtre gaussien");
        cout<<"  "<<endl;
        cout<<"Entrer la dimension du filtre (un nombre impair: 3 ou , 5 ): "<< endl;
        cin>>response;
        zoom1 = atoi(response.c_str());
        if(zoom1 != 3 && zoom1 != 5) zoom1 = 3;
        if(imageTraite.convolutionFiltreGaussien(zoom1)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 16: 
        message("Effectuer la convolution par filtre median");
        cout<<"  "<<endl;
        cout<<"Entrer la dimension du filtre (un nombre impair plus grand que 1, 3 est choisi par defaut): "<< endl;
        cin>>response;
        zoom1 = atoi(response.c_str());
        if(zoom1%2 == 0 || zoom1 == 1) zoom1 = 3;
        if(imageTraite.convolutionFiltreMedian(zoom1)){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 17: 
        message("Contour Filtre Roberts");
        cout<<"  "<<endl;
        if(imageTraite.contourRoberts()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 18: 
        message("Contour Filtre Prewitt");
        cout<<"  "<<endl;
        if(imageTraite.contourPrewitt()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 19: 
        message("Contour Filtre Sobel");
        cout<<"  "<<endl;
        if(imageTraite.contourSobel()){
            message(" Le Traitement s'est bien effectue");
        }
        else{
            erreur("Erreur lors du traitement");
        }
        break;
    case 20: 
        do
        {
           message("\tSaisir le nom de votre image(ex test.pgm)");
            //on recupère le nom de l'image
            cin>>nomImage; 
            cout <<"\n\n" << endl; 
            result = imageTraite.test(nomImage);
        }
        while(!result);

        cout<<"\tImage valide....."<< endl;
        cout <<"\n\n" << endl; 
        imageTraite.reload(nomImage);
        message(imageTraite.GetfileName()+" a ete bien chargee. Continuez vos traitements");
        break;
    case 21:
        message("Quitter le programme");
        
        message("Aurevoir et a la prochaine");
        
        message("Copyright, 2016 - Joy Jedidja NDJAMA");
        break;
    }
    
    }
    while(choix != 21);
      
  return 0;
}

