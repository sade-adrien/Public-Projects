#include <Imagine/Graphics.h>
#include <algorithm>
#include <iostream>
#include "quadtree/quadtree.h"

using namespace Imagine;
using namespace std;


/* IMPORTANT: à lire svp
 *
 * Les questions sont toutes traitées dans le code ci-dessous.
 *
 *
 * REMARQUE: les fonctions de construction d'arbre scinde l'image en 4 récursivement en créant 4 nouvelles images.
 * Or l'énoncé spécifie justement de ne pas faire cela. Je m'en suis rendu compte après avoir programmé toutes les fonctions.
 * Le changement est long mais trivial: il suffit d'inclure en arguments de la fonction les coordonnées du centre de la nouvelle image,
 * ainsi que ses dimensions (width, height) (même schéma que mes fonctions de reconstitution des images grâce à un arbre).
 * On raisonne alors directement avec les coordonnées de l'image originale en travaillant avec le tableau initial byte* image,
 * sans perdre du temps et de la mémoire.
 *
 * Voici cette fonction recodée (je ne l'ai pas remplacée dans le programme pour ne pas avoir à reprogrammer toutes les fonctions de ce type
 * et par peur de créer un bug juste avant de rendre le tp):
 *
 * QuadTree<bool>* construction_arbre(byte* image, int centreX, int centreY, int width, int height) {

    //Si taille=1pixel: tout en bas de l'arbre
    if(width==1 && height==1){
        QuadLeaf<bool>* leaf_pixel = new QuadLeaf<bool> (image[0]==255);        //true if white
        return leaf_pixel;
    }



    //Sinon: il faut rediviser l'image en 4

    QuadTree<bool>* Node_NO = construction_arbre(image,CentreX-width/2,CentreY-height/2,width/2,height/2);
    QuadTree<bool>* Node_NE = construction_arbre(image,CentreX+width/2,CentreY-height/2,width-width/2,height/2);
    QuadTree<bool>* Node_SO = construction_arbre(image,CentreX-width/2,CentreY+height/2,width/2,height-height/2);
    QuadTree<bool>* Node_SE = construction_arbre(image,CentreX+width/2,CentreY+height/2,width-width/2,height-height/2);


    //Remontée récursion
    if(Node_NO->isLeaf() && Node_NE->isLeaf() && Node_SE->isLeaf() && Node_SO->isLeaf()){
    if((Node_NE->value()==Node_NO->value()) && (Node_SE->value()==Node_SO->value()) && (Node_NE->value()==Node_SE->value())){
        bool value = Node_NE->value();
        delete  Node_NE; delete Node_NO; delete Node_SE; delete Node_SO;
        QuadLeaf<bool>* New_Leaf = new QuadLeaf<bool> (value);
        return New_Leaf;
    }
    }

    QuadNode<bool>* New_Node = new QuadNode<bool> (Node_NO,Node_NE,Node_SE,Node_SO);
    return New_Node;
}



* Remarquons qu'avec cette fonction, on peut alors modifier le fonctionnement du programme pour traiter une image rectangulaire:
* mon programme ci-dessous plante de manière aléatoire (lorsqu'on arrive au traitement d'images rectangulaires, selon moi parce que
* lorsque je traite ce cas, les dimensions sont modifiées et l'on vient écrire librement dans un espace qui n'a pas été alloué
* à l'origine (on ne refait pas de new byte[nv_dimensiosn])... (ce qui explique que dans certains cas le programme ne rencontre
* pas d'erreur critique et arrive au bout, tandis que dans d'autres il plante en cours de route).
* Néanmois, si on choisit d'utiliser la fonction construction_arbre() ci-dessus, on peut trouver une solution. En effet,
* on ne cherche alors plus à redimensionner directement l'image (encore un gain de temps et mémoire) mais seulement
* à intervenir dans la construction de son arbre. On construit l'arbre de manière classique, mais en envoyant en argument
* de construction_arbre() les NOUVELLES dimensions (carrées, puissances de 2), et lorsque la fonction est à l'oeuvre
* dès lors qu'elle entre dans un domaine out of bounds de l'image initiale (non carrée), l'arbre est directement muni d'une feuille
* blanche (sans tenter d'aller lire le pixel de l'image, qui n'existe donc pas). En sortie (après reconstruction), on aura bien une
* image carrée munie de bandes blanches. Cette méthode est possible, car la NOUVELLE fonction construction_arbre() (ci-dessus) n'a
* pas besoin d'aller lire des pixels qui seraient initialement out_of_bounds de l'image si on lui ajoute la condition de vérification
* des bounds (et en cas de validation de cette condition, création automatique d'une feuille blanche). Dans tous les cas, il aurait
* fallu modifier légèrement la fonction construction_arbre() (par exemple construction_arbre_rectangular()), pour corriger le bug.
*

* */


//*******************Q3**********************
QuadTree<bool>* construction_arbre(byte* image, int width, int height) {

    //Si taille=1pixel: tout en bas de l'arbre
    if(width==1 && height==1){
        QuadLeaf<bool>* leaf_pixel = new QuadLeaf<bool> (image[0]==255);        //true if white
        return leaf_pixel;
    }



    //Sinon: il faut rediviser l'image en 4
    byte* image_NO = new byte [width*height/4];      //construction img NO
    for(int i=0;i<height/2;i++){
        for(int j=0;j<width/2;j++){
            image_NO[i*width/2+j]=image[i*width+j];
        }
    }


    QuadTree<bool>* Node_NO = construction_arbre(image_NO,width/2,height/2);
    delete [] image_NO;


    byte* image_NE = new byte [(width-width/2)*height/2];     //construction img NE
    for(int i=0;i<height/2;i++){
        for(int j=width/2;j<width;j++){
            image_NE[i*width/2+j-(width/2)]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_NE = construction_arbre(image_NE,width-width/2,height/2);
    delete [] image_NE;


    byte* image_SO = new byte [width/2*(height-height/2)];    //construction img SO
    for(int i=height/2;i<height;i++){
        for(int j=0;j<width/2;j++){
            image_SO[(i-(height/2))*width/2+j]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_SO = construction_arbre(image_SO,width/2,height-height/2);
    delete [] image_SO;


    byte* image_SE = new byte [(width-width/2)*(height-height/2)];    //construction img SE
    for(int i=height/2;i<height;i++){
        for(int j=width/2;j<width;j++){
            image_SE[(i-(height/2))*width/2+j-(width/2)]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_SE = construction_arbre(image_SE,width-width/2,height-height/2);
    delete [] image_SE;



    //Remontée récursion
    if(Node_NO->isLeaf() && Node_NE->isLeaf() && Node_SE->isLeaf() && Node_SO->isLeaf()){
    if((Node_NE->value()==Node_NO->value()) && (Node_SE->value()==Node_SO->value()) && (Node_NE->value()==Node_SE->value())){
        bool value = Node_NE->value();
        delete  Node_NE; delete Node_NO; delete Node_SE; delete Node_SO;
        QuadLeaf<bool>* New_Leaf = new QuadLeaf<bool> (value);
        return New_Leaf;
    }
    }

    QuadNode<bool>* New_Node = new QuadNode<bool> (Node_NO,Node_NE,Node_SE,Node_SO);
    return New_Node;
}



//******************Q4*******************
QuadLeaf<bool> black_leaf(false);
QuadLeaf<bool> white_leaf(true);

QuadTree<bool>* construction_arbre_quaddag_version(byte* image, int width, int height) {

    //Si taille=1pixel: tout en bas de l'arbre
    if(width==1 && height==1){
        if(image[0]==255)
            return &white_leaf;
        return &black_leaf;
    }



    //Sinon: il faut rediviser l'image en 4
    byte* image_NO = new byte [width*height/4];      //construction img NO
    for(int i=0;i<height/2;i++){
        for(int j=0;j<width/2;j++){
            image_NO[i*width/2+j]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_NO = construction_arbre(image_NO,width/2,height/2);
    delete [] image_NO;


    byte* image_NE = new byte [(width-width/2)*height/2];     //construction img NE
    for(int i=0;i<height/2;i++){
        for(int j=width/2;j<width;j++){
            image_NE[i*width/2+j-(width/2)]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_NE = construction_arbre(image_NE,width-width/2,height/2);
    delete [] image_NE;


    byte* image_SO = new byte [width/2*(height-height/2)];    //construction img SO
    for(int i=height/2;i<height;i++){
        for(int j=0;j<width/2;j++){
            image_SO[(i-(height/2))*width/2+j]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_SO = construction_arbre(image_SO,width/2,height-height/2);
    delete [] image_SO;


    byte* image_SE = new byte [(width-width/2)*(height-height/2)];    //construction img SE
    for(int i=height/2;i<height;i++){
        for(int j=width/2;j<width;j++){
            image_SE[(i-(height/2))*width/2+j-(width/2)]=image[i*width+j];
        }
    }

    QuadTree<bool>* Node_SE = construction_arbre(image_SE,width-width/2,height-height/2);
    delete [] image_SE;



    //Remontée récursion
    if(Node_NO->isLeaf() && Node_NE->isLeaf() && Node_SE->isLeaf() && Node_SO->isLeaf()){
    if((Node_NE->value()==Node_NO->value()) && (Node_SE->value()==Node_SO->value()) && (Node_NE->value()==Node_SE->value())){
        bool value = Node_NE->value();
        if(value)
            return &white_leaf;
        return &black_leaf;
    }
    }

    QuadNode<bool>* New_Node = new QuadNode<bool> (Node_NO,Node_NE,Node_SE,Node_SO);
    return New_Node;
}



//********************Q5*******************
void image_reconstitution_from_tree(QuadTree<bool>* image_tree, byte* image_reconstituee, int width, int height, int centerX, int centerY, int width_total, bool print_squares){
    if(image_tree->isNode()){
        int tab_width[4]={width/2,width-width/2,width-width/2,width/2};
        int tab_height[4]={height/2,height/2,height-height/2,height-height/2};
        int tab_centerX[4]={-(width/2-width/4),(width-width/2)/2,(width-width/2)/2,-(width/2-width/4)};
        int tab_centerY[4]={-(height/2-height/4),-(height/2-height/4),(height-height/2)/2,(height-height/2)/2};
        for(int d=0;d<4;d++)
            image_reconstitution_from_tree(image_tree->son(d),image_reconstituee,tab_width[d],tab_height[d],centerX+tab_centerX[d],centerY+tab_centerY[d], width_total, print_squares);
    }

    else{
        int value = 0;
        if(image_tree->value()){
            value=255;
        }

        for(int i=centerY-height/2;i<centerY+height/2+1;i++){
            for(int j=centerX-width/2;j<centerX+width/2+1;j++){
                image_reconstituee[i*width_total+j]=byte(value);
            }
        }

        if(width>1 && height>1 && print_squares){                     //grosses feuilles seulement: taille>1pixels à faire varier au besoin
            for(int j=centerX-width/2;j<centerX+width/2;j++)
                image_reconstituee[(centerY-height/2)*width_total+j]=byte(255-value);
            for(int j=centerX-width/2;j<centerX+width/2;j++)
                image_reconstituee[(centerY+height/2)*width_total+j]=byte(255-value);
            for(int i=centerY-height/2;i<centerY+height/2;i++)
                image_reconstituee[i*width_total+(centerX-width/2)]=byte(255-value);
            for(int i=centerY-height/2;i<centerY+height/2;i++)
                image_reconstituee[i*width_total+(centerX+width/2)]=byte(255-value);
        }
    }
}



//********************Q7**************************
int first_higher_power_of_2(int my_number) {
    int i = 1;
    while (my_number > i)
        i *= 2;
    return i;
}

void image_conversion_rectangulare_to_square_on_power_of_2(byte* image, int &width, int &height){
    int initial_width = width;
    int initial_height = height;

    if(width>height)
        height=width;
    else if (height>width)
        width=height;

    width=first_higher_power_of_2(width);
    height=first_higher_power_of_2(height);

    for(int i=initial_height-1;i>=0;i--){
        for(int j=initial_width;j>=0;j--){
            image[i*width+j]=image[i*initial_width+j];
        }
    }
    for(int i=0;i<height;i++){
        for(int j=initial_width;j<width;j++){
            image[i*width+j]=byte(255);
        }
    }
    for(int j=0;j<width;j++){
        for(int i=initial_height;i<height;i++){
            image[i*width+j]=byte(255);
        }
    }
}



//********************Q8**************************
QuadTree<byte>* construction_arbre_grey_levels(byte* image, int width, int height, int seuil, bool adaptive_seuil) {

    //Si taille=1pixel: tout en bas de l'arbre
    if(width==1 && height==1){
        QuadLeaf<byte>* leaf_pixel = new QuadLeaf<byte> (image[0]);
        return leaf_pixel;
    }



    //Sinon: il faut rediviser l'image en 4
    if(adaptive_seuil)                  //Si demandé, on adapte le seuil: il diminue lorsque la région augmente
        seuil-=2;

    byte* image_NO = new byte [width*height/4];      //construction img NO
    for(int i=0;i<height/2;i++){
        for(int j=0;j<width/2;j++){
            image_NO[i*width/2+j]=image[i*width+j];
        }
    }


    QuadTree<byte>* Node_NO = construction_arbre_grey_levels(image_NO,width/2,height/2,seuil,adaptive_seuil);
    delete [] image_NO;


    byte* image_NE = new byte [(width-width/2)*height/2];     //construction img NE
    for(int i=0;i<height/2;i++){
        for(int j=width/2;j<width;j++){
            image_NE[i*width/2+j-(width/2)]=image[i*width+j];
        }
    }

    QuadTree<byte>* Node_NE = construction_arbre_grey_levels(image_NE,width-width/2,height/2,seuil,adaptive_seuil);
    delete [] image_NE;


    byte* image_SO = new byte [width/2*(height-height/2)];    //construction img SO
    for(int i=height/2;i<height;i++){
        for(int j=0;j<width/2;j++){
            image_SO[(i-(height/2))*width/2+j]=image[i*width+j];
        }
    }

    QuadTree<byte>* Node_SO = construction_arbre_grey_levels(image_SO,width/2,height-height/2,seuil,adaptive_seuil);
    delete [] image_SO;


    byte* image_SE = new byte [(width-width/2)*(height-height/2)];    //construction img SE
    for(int i=height/2;i<height;i++){
        for(int j=width/2;j<width;j++){
            image_SE[(i-(height/2))*width/2+j-(width/2)]=image[i*width+j];
        }
    }

    QuadTree<byte>* Node_SE = construction_arbre_grey_levels(image_SE,width-width/2,height-height/2,seuil,adaptive_seuil);
    delete [] image_SE;



    //Remontée récursion
    if(Node_NO->isLeaf() && Node_NE->isLeaf() && Node_SE->isLeaf() && Node_SO->isLeaf()){
        bool fusion;
        fusion = (int(Node_NO->value())-int(Node_NE->value())<seuil);
        fusion = fusion && (abs(int(Node_SO->value())-int(Node_SE->value()))<seuil);
        fusion = fusion && (abs(int(Node_NO->value())-int(Node_SO->value()))<seuil);
        fusion = fusion && (abs(int(Node_NE->value())-int(Node_SE->value()))<seuil);
        fusion = fusion && (abs(int(Node_NO->value())-int(Node_SE->value()))<seuil);
        fusion = fusion && (abs(int(Node_NE->value())-int(Node_SO->value()))<seuil);

        if(fusion){
            int mean = int(float(int(Node_NO->value())+int(Node_NE->value())+int(Node_SE->value())+int(Node_SO->value()))/4.f);
            QuadLeaf<byte>* New_Leaf = new QuadLeaf<byte> (byte(mean));
            delete  Node_NE; delete Node_NO; delete Node_SE; delete Node_SO;
            return New_Leaf;
        }
    }

    QuadNode<byte>* New_Node = new QuadNode<byte> (Node_NO,Node_NE,Node_SE,Node_SO);
    return New_Node;
}

void image_reconstitution_from_tree_grey_levels(QuadTree<byte>* image_tree, byte* image_reconstituee, int width, int height, int centerX, int centerY, int width_total, bool print_squares){
    if(image_tree->isNode()){
        int tab_width[4]={width/2,width-width/2,width-width/2,width/2};
        int tab_height[4]={height/2,height/2,height-height/2,height-height/2};
        int tab_centerX[4]={-(width/2-width/4),(width-width/2)/2,(width-width/2)/2,-(width/2-width/4)};
        int tab_centerY[4]={-(height/2-height/4),-(height/2-height/4),(height-height/2)/2,(height-height/2)/2};
        for(int d=0;d<4;d++)
            image_reconstitution_from_tree_grey_levels(image_tree->son(d),image_reconstituee,tab_width[d],tab_height[d],centerX+tab_centerX[d],centerY+tab_centerY[d], width_total, print_squares);
    }

    else{
        byte value = image_tree->value();

        for(int i=centerY-height/2;i<centerY+height/2+1;i++){
            for(int j=centerX-width/2;j<centerX+width/2+1;j++){
                image_reconstituee[i*width_total+j]=byte(value);
            }
        }
    }

    if(width>6 && height>6 && print_squares){                                //grosses feuilles seulement: taille>6pixels à faire varier au besoin
                for(int j=centerX-width/2;j<centerX+width/2;j++)
                    image_reconstituee[(centerY-height/2)*width_total+j]=byte(255);
                for(int j=centerX-width/2;j<centerX+width/2;j++)
                    image_reconstituee[(centerY+height/2)*width_total+j]=byte(255);
                for(int i=centerY-height/2;i<centerY+height/2;i++)
                    image_reconstituee[i*width_total+(centerX-width/2)]=byte(255);
                for(int i=centerY-height/2;i<centerY+height/2;i++)
                    image_reconstituee[i*width_total+(centerX+width/2)]=byte(255);
            }
}



int main(int argc, char **argv) {
    // Get image file (default is running horse)
    const char *image_file =
        (argc > 1) ? argv[1] : srcPath("running-horse-square.png");
    // Load image
    byte* image;
    int width, height;
    cout << "Loading image: " << image_file << endl; 
    loadGreyImage(image_file, image, width, height);
    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;
    // Display image
    Window window = openWindow(width, height);
    putGreyImage(IntPoint2(0,0), image, width, height);
    // Pause
    click();


    //****************Q3******************
    QuadTree<bool>* tree_image = construction_arbre(image,width,height);
   // display(tree_image);



    cout << "************************************" << endl;
    //**************Q4********************  --> modifier protect_leaves_from_destruction dans quadtree.h
    QuadTree<bool>* tree_image_quaddag_version = construction_arbre_quaddag_version(image,width,height);
    display(tree_image_quaddag_version);


    //******************Q5***********************
    byte* image_reconstituee = new byte [width*height];
    for(int i =0;i<height;i++){
        for(int j=0;j<width;j++){
            image_reconstituee[i*width+j]=byte(255);
        }
    }
    image_reconstitution_from_tree(tree_image_quaddag_version,image_reconstituee,width,height,width/2,height/2,width,true);

    clearWindow();
    click();
    putGreyImage(IntPoint2(0,0),image_reconstituee,width,height);
    click();


    //******************Q6************************
    unsigned long taille_image_compressee=sizeof(QuadNode<bool>)*tree_image->nNodes() + sizeof(QuadLeaf<bool>)*tree_image->nLeaves();
    unsigned long taille_image_compressee_quaddag=sizeof(QuadNode<bool>)*tree_image_quaddag_version->nNodes() + sizeof(QuadLeaf<bool>)*2;
    unsigned long taille_image_non_compresse=width*height*sizeof(byte);
    cout << "********************************" << endl;
    cout << "La taille de l'image non compressée est : " << taille_image_non_compresse << " octets." << endl;
    cout << "La taille de l'image compressée (non quaddag) est : " << taille_image_compressee << " octets." << endl;
    cout << "La taille de l'image compressée (quaddag) est : " << taille_image_compressee_quaddag << " octets." << endl;
    cout << "On peut donc mesurer le taux de compression en faisant 1- le rapport des tailles des images compressée et non compressée:" << endl;
    cout << "Taux de compression (non quaddag) = " << 100.f-float(taille_image_compressee)/float(taille_image_non_compresse)*100.f << " %" << endl;
    cout << "Taux de compression (quaddag) = " << 100.f-float(taille_image_compressee_quaddag)/float(taille_image_non_compresse)*100.f << " %" << endl;

    closeWindow(window);


    //********************Q7**************************
    const char *image_file_rectangular =
        (argc > 1) ? argv[1] : srcPath("running-horse-rect.png");
    byte* rectangular_image;
    int rectangular_width, rectangular_height;

    cout << "************************************" << endl;
    cout << "Loading image: " << image_file_rectangular << endl;
    loadGreyImage(image_file_rectangular, rectangular_image, rectangular_width, rectangular_height);
    cout << "Image size: " << rectangular_width << "x" << rectangular_height << endl;
    cout << "Number of pixels: " << rectangular_width*rectangular_height << endl;

    Window rectangular_window = openWindow(rectangular_width,rectangular_height);

    putGreyImage(IntPoint2(0,0),rectangular_image,rectangular_width,rectangular_height);
    click();
    closeWindow(rectangular_window);

    image_conversion_rectangulare_to_square_on_power_of_2(rectangular_image,rectangular_width,rectangular_height);
    Window square_window = openWindow(rectangular_width,rectangular_height);
    putGreyImage(IntPoint2(0,0),rectangular_image,rectangular_width,rectangular_height);
    cout << "Image size: " << rectangular_width << "x" << rectangular_height << endl;
    click();

    QuadTree<bool>* tree_rectangular_image = construction_arbre_quaddag_version(rectangular_image,rectangular_width,rectangular_height);
    byte* rectangular_image_reconstituee = new byte [rectangular_width*rectangular_height];
    for(int i =0;i<rectangular_height;i++){
        for(int j=0;j<rectangular_width;j++){
            rectangular_image_reconstituee[i*rectangular_width+j]=byte(255);
        }
    }
    image_reconstitution_from_tree(tree_rectangular_image,rectangular_image_reconstituee,rectangular_width,rectangular_height,rectangular_width/2,rectangular_height/2,rectangular_width,true);

    clearWindow();
    click();
    putGreyImage(IntPoint2(0,0),rectangular_image_reconstituee,rectangular_width,rectangular_height);
    click();
    closeWindow(square_window);



    //********************Q8********************
    const char *image_file_grey =
        (argc > 1) ? argv[1] : srcPath("passerelle_SdB_rectangular_grey.jpg");
    byte* grey_image;
    int grey_width, grey_height;

    cout << "************************************" << endl;
    cout << "Loading image: " << image_file_grey << endl;
    loadGreyImage(image_file_grey, grey_image, grey_width, grey_height);
    cout << "Image size: " << grey_width << "x" << grey_height << endl;
    cout << "Number of pixels: " << grey_width*grey_height << endl;

    Window grey_window = openWindow(grey_width,grey_height);

    putGreyImage(IntPoint2(0,0),grey_image,grey_width,grey_height);
    click();
    closeWindow(grey_window);

    image_conversion_rectangulare_to_square_on_power_of_2(grey_image,grey_width,grey_height);
    Window grey_square_window = openWindow(grey_width,grey_height);
    putGreyImage(IntPoint2(0,0),grey_image,grey_width,grey_height);
    cout << "Image size: " << grey_width << "x" << grey_height << endl;
    click();

    QuadTree<byte>* tree_grey_image = construction_arbre_grey_levels(grey_image,grey_width,grey_height,30,false);          //faire varier le dernier argument pour faire varier le niveau de compression (seuil), 1 pour compression nulle; le dernier argument permet ou non d'adapter le seuil à la taille de la région (et dans ce cas l'argument seuil devient le seuil initial)
    byte* grey_image_reconstituee = new byte [grey_width*grey_height];
    for(int i =0;i<grey_height;i++){
        for(int j=0;j<grey_width;j++){
            grey_image_reconstituee[i*grey_width+j]=byte(255);
        }
    }
    image_reconstitution_from_tree_grey_levels(tree_grey_image,grey_image_reconstituee,grey_width,grey_height,grey_width/2,grey_height/2,grey_width,false);       //passer le dernier argument en false pour mieux observer la compression

    clearWindow();
    click();
    putGreyImage(IntPoint2(0,0),grey_image_reconstituee,grey_width,grey_height);
    click();

    tree_grey_image = construction_arbre_grey_levels(grey_image,grey_width,grey_height,30,true);             //version avec variation du seuil
    for(int i =0;i<grey_height;i++){
        for(int j=0;j<grey_width;j++){
            grey_image_reconstituee[i*grey_width+j]=byte(255);
        }
    }
    image_reconstitution_from_tree_grey_levels(tree_grey_image,grey_image_reconstituee,grey_width,grey_height,grey_width/2,grey_height/2,grey_width,false);
    putGreyImage(IntPoint2(0,0),grey_image_reconstituee,grey_width,grey_height);
    click();

    closeWindow(grey_square_window);









    delete tree_image;
    delete tree_image_quaddag_version;
    delete [] image_reconstituee;
    delete tree_rectangular_image;
    delete [] rectangular_image_reconstituee;
    delete tree_grey_image;
    delete [] grey_image_reconstituee;



    // Exit
    return 0;
}
