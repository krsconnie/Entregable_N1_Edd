#ifndef MOVING_IMG_H
#define MOVING_IMG_H

#include "basics.h"
#include <stack>
#include <queue>
#include <functional>
#include <iostream>
#include <string>


/*

Clase que representa una imagen como una matriz, en base a 3 tonalidades (rgb)
aparte esta clase implementa funciones para modificar dicha imagen (mover hacia arriba/abajo, derecha/izquiera, rotar 90°), 
también cuenta con un historial (stack) que permite implementar las funciones de repetir, deshacer y rehacer.

Cuenta con un "registro de auditoría" que permite visualizar todos los cambios hechos en la imagen mediante la función repetir todo,
esta genera imagenes de todas las funciones llamadas por el usuario.

*/
 

class moving_image {

private:

  unsigned char **red_layer; // Capa de tonalidades rojas
  unsigned char **green_layer; // Capa de tonalidades verdes
  unsigned char **blue_layer; // Capa de tonalidades azules

  std::stack<std::string> histostack; // Stack que funciona como historial editable
  std::stack<std::string> histoaux; // Stack auxiliar para las funciones undo/redo
  std::queue<std::string> histotal; // Queue que funciona como historial total

public:

  // Constructor de la imagen. Se crea una imagen por defecto
  moving_image() {

    // Reserva de memoria para las 3 matrices RGB
    
    red_layer = new unsigned char*[ H_IMG ]; // Filas rojas, cantidad de filas hace referencia a la altura de la imagen
    
    green_layer = new unsigned char*[ H_IMG ]; // Filas verdes
    
    blue_layer = new unsigned char*[ H_IMG ]; // Filas azules
    
    
    for(int i = 0; i < H_IMG; i++) {
    
      red_layer[ i ] = new unsigned char[ W_IMG ]; // Columnas rojas, cantidad de columnas hace referencia al ancho de la imagen
    
      green_layer[ i ] = new unsigned char[ W_IMG ]; // Columnas verdes
    
      blue_layer[ i ] = new unsigned char[ W_IMG ]; // Columnas azules
    
    }

    // Llenamos la imagen con su color de fondo
    
    for(int i = 0; i < H_IMG; i++)
  
      for(int j = 0; j < W_IMG; j++) {
	     
        red_layer[ i ][ j ] = DEFAULT_R;
        green_layer[ i ][ j ] = DEFAULT_G;
        blue_layer[ i ][ j ] = DEFAULT_B;
      
      }

    // Dibujamos el objeto en su posición inicial
    for(int i = 0; i < 322; i++)

      for(int j = 0; j < 256; j++) {

	     if(!s_R[ i ][ j ] && !s_G[ i ][ j ] && !s_B[ i ][ j ]) {
	     
       red_layer[ INIT_Y + i ][ INIT_X + j ] = DEFAULT_R;
	     green_layer[ INIT_Y + i ][ INIT_X + j ] = DEFAULT_G;
	     blue_layer[ INIT_Y + i ][ INIT_X + j ] = DEFAULT_B;
	     
       } else {
	     
       red_layer[ INIT_Y + i ][ INIT_X + j ] = s_R[ i ][ j ];
	     green_layer[ INIT_Y + i ][ INIT_X + j ] = s_G[ i ][ j ];
	     blue_layer[ INIT_Y + i ][ INIT_X + j ] = s_B[ i ][ j ];
	
  }
     
      }   
  
  }

  // Destructor de la clase
  ~moving_image() {
  
    for(int i = 0; i < H_IMG; i++) {
  
      delete red_layer[ i ]; // Borra las columnas rojas
      delete green_layer[ i ]; // Borra las columnas verdes
      delete blue_layer[ i ]; // Borra las clomnas azules
  
    }

    delete red_layer; // Borra las filas rojas
    delete green_layer; // Borra las filas verdes
    delete blue_layer; // Borra las filas azules
  
  }

  // Función utilizada para guardar la imagen en formato .png
  void draw(const char* nb) {
  
    _draw(nb);
  
  }

  // Función que similar desplazar la imagen, de manera circular, d pixeles a la izquierda
  void move_left(int d) {
    
    std::string funcion = "L" + std::to_string(d);
    
    histostack.push( funcion ); //Agrega la llamada a la función al historial
    histotal.push( funcion ); //Agrega la llamada a la funciión al historial total

    unsigned char **tmp_layer = new unsigned char*[ H_IMG ];
    
    for(int i = 0; i < H_IMG; i++) 
      tmp_layer[ i ] = new unsigned char[ W_IMG ];
    
    // Mover la capa roja
    
    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG-d; j++)

    	 tmp_layer[ i ][ j ] = red_layer[ i ][ j + d ];      
    


    for(int i = 0; i < H_IMG; i++)
      for(int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
    	 
       tmp_layer[ i ][ j ] = red_layer[ i ][ k ];      



    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG; j++)
    	
      red_layer[ i ][ j ] = tmp_layer[ i ][ j ];


    // Mover la capa verde
    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG-d; j++)
    	
      tmp_layer[ i ][ j ] = green_layer[ i ][ j + d ];      


    
    for(int i = 0; i < H_IMG; i++)
      for(int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
    	
      tmp_layer[ i ][ j ] = green_layer[ i ][ k ];      



    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG; j++)
    	
      green_layer[ i ][ j ] = tmp_layer[ i ][ j ];



    // Mover la capa azul
    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG - d; j++)
    	
      tmp_layer[ i ][ j ] = blue_layer[ i ][ j + d ];      


    
    for(int i = 0; i < H_IMG; i++)
      for(int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
    	
      tmp_layer[ i ][ j ] = blue_layer[ i ][ k ];      



    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG; j++)
    	blue_layer[ i ][ j ] = tmp_layer[ i ][ j ];

  }


   // Función que similar desplazar la imagen d pixeles a la derecha
  void move_right(int d) {
    
   std::string funcion = "R" + std::to_string(d);
    
    histostack.push( funcion ); //Agrega la llamada a la función al historial
    histotal.push( funcion ); //Agrega la llamada a la funciión al historial total

    unsigned char **tmp_layer2 = new unsigned char*[ H_IMG ];
    for(int i = 0; i < H_IMG; i++)

      tmp_layer2[ i ] = new unsigned char[ W_IMG ];
    
    // Mover la capa roja
    for(int i = 0; i < H_IMG; i++)
      for(int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
    
      tmp_layer2[ i ][ k ] = red_layer[ i ][ j ];      
    
 

    for(int i = 0; i < H_IMG; i++)
      for(int j = d, k = 0; j < W_IMG; j++, k++)
    
      tmp_layer2[ i ][ j ] = red_layer[ i ][ k ];      



    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG; j++)
    
      red_layer[ i ][ j ] = tmp_layer2[ i ][ j ];


    // Mover la capa verde
    for(int i = 0; i < H_IMG; i++)
      for(int j = W_IMG - d, k = 0; j < W_IMG ; j++, k++)
    
      tmp_layer2[ i ][ k ] = green_layer[ i ][ j ];   



    for(int i = 0; i < H_IMG; i++)
      for(int j = d, k = 0; j < W_IMG; j++, k++)
      
      tmp_layer2[ i ][ j ] = green_layer[ i ][ k ];      



    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG; j++)
      
      green_layer[ i ][ j ] = tmp_layer2[ i ][ j ];



    // Mover la capa azul
    for(int i = 0; i < H_IMG; i++)
      for(int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
      
      tmp_layer2[ i ][ k ] = blue_layer[ i ][ j ];


    
    for(int i = 0; i < H_IMG; i++)
      for(int j = d, k = 0; j < W_IMG; j++, k++)
     
      tmp_layer2[ i ][ j ] = blue_layer[ i ][ k ];      



    for(int i = 0; i < H_IMG; i++)
      for(int j = 0; j < W_IMG; j++)
      blue_layer[ i ][ j ] = tmp_layer2[ i ][ j ];

  }


  // Función que similar desplazar la imagen d pixeles hacía arriba
  void move_up(int d){
    
    std::string funcion = "U" + std::to_string(d);
    
    histostack.push( funcion ); //Agrega la llamada a la función al historial
    histotal.push( funcion ); //Agrega la llamada a la funciión al historial total
    
    unsigned char **tmp_layer3 = new unsigned char*[ H_IMG ];
    for(int i = 0; i < H_IMG; i++) 
      tmp_layer3[ i ] = new unsigned char[ W_IMG ];
    

    // Mover la capa roja
    for(int j = 0; j < W_IMG; j++)
      for(int i = H_IMG - d, k = 0; i < H_IMG; i++, k++)
      
      tmp_layer3[ i ][ j ] = red_layer[ k ][ j ];      
    


    for(int j = 0; j < W_IMG; j++)
      for(int i = d; i < H_IMG; i++)
      
      tmp_layer3[ i - d ][ j ] = red_layer[ i ][ j ];      



    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG; i++)
      
      red_layer[ i ][ j ] = tmp_layer3[ i ][ j ];



    // Mover la capa verde
    for(int j = 0; j < W_IMG; j++)
      for(int i = H_IMG - d, k = 0; i < H_IMG; i++, k++)
      
      tmp_layer3[ i ][ j ] = green_layer[ k ][ j ];      
    


    for(int j = 0; j < W_IMG; j++)
      for(int i = d; i < H_IMG; i++)
      
      tmp_layer3[ i - d ][ j ] = green_layer[ i ][ j ];      



    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG; i++)
      
      green_layer[ i ][ j ] = tmp_layer3[ i ][ j ];



    // Mover la capa azul
    for(int j = 0; j < W_IMG; j++)
      for(int i = H_IMG - d, k = 0; i < H_IMG; i++, k++)
      
      tmp_layer3[ i ][ j ] = blue_layer[ k ][ j ];      
    


    for(int j = 0; j < W_IMG; j++)
      for(int i = d; i < H_IMG; i++)
      
      tmp_layer3[ i - d ][ j ] = blue_layer[ i ][ j ];      



    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG; i++)
      
      blue_layer[ i ][ j ] = tmp_layer3[ i ][ j ];

   
   }

// Función que similar desplazar la imagen d pixeles hacía abajo
 void move_down(int d){

  std::string funcion = "D" + std::to_string(d);
    
  histostack.push( funcion ); //Agrega la llamada a la función al historial
  histotal.push( funcion ); //Agrega la llamada a la funciión al historial total

   unsigned char **tmp_layer4 = new unsigned char*[ H_IMG ];
    for(int i = 0; i < H_IMG; i++) 
      tmp_layer4[ i ] = new unsigned char[ W_IMG ];
    


    // Mover la capa roja
    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG - d ; i++)
      
      tmp_layer4[ i + d ][ j ] = red_layer[ i ][ j ];      
    


    for(int j = 0; j < W_IMG; j++)
      for(int i = H_IMG - d, k = 0; i < H_IMG; i++, k++)
      
      tmp_layer4[ k ][ j ] = red_layer[ i ][ j ];      



    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG; i++)
      
      red_layer[ i ][ j ] = tmp_layer4[ i ][ j ];



    // Mover la capa verde
    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG - d ; i++)
      
      tmp_layer4[ i + d ][ j ] = green_layer[ i ][ j ];      
    


    for(int j = 0; j < W_IMG; j++)
      for(int i = H_IMG - d, k = 0; i < H_IMG; i++, k++)
      
      tmp_layer4[ k ][ j ] = green_layer[ i ][ j ];      



    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG; i++)
      
      green_layer[ i ][ j ] = tmp_layer4[ i ][ j ];



    // Mover la capa azul
    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG - d ; i++)
      
      tmp_layer4[ i + d ][ j ] = blue_layer[ i ][ j ];      
    


    for(int j = 0; j < W_IMG; j++)
      for(int i = H_IMG - d, k = 0; i < H_IMG; i++, k++)
      
      tmp_layer4[ k ][ j ] = blue_layer[ i ][ j ];    



    for(int j = 0; j < W_IMG; j++)
      for(int i = 0; i < H_IMG; i++)
      
      blue_layer[ i ][ j ] = tmp_layer4[ i ][ j ];

    }

  void rotate() {
    
    std::string funcion = "A90";
    
    histostack.push( funcion ); //Agrega la llamada a la función al historial
    histotal.push( funcion ); //Agrega la llamada a la funciión al historial total


    unsigned char **tmp_layer = new unsigned char*[ W_IMG ];
    for(int i = 0; i < W_IMG; i++) 
      
        tmp_layer[ i ] = new unsigned char[ H_IMG ];

    //Intercambiar coordenadas capa roja
    for(int i = 0; i < H_IMG; i++) {
        for(int j = 0; j < W_IMG; j++) {
      
            tmp_layer[ W_IMG - 1 - j ][ i ] = red_layer[ i ][ j ];
      
        }
    }

    //Actualizar capa roja
    for(int i = 0; i < W_IMG; i++) {
        for(int j = 0; j < H_IMG; j++) {
      
            red_layer[ i ][ j ] = tmp_layer[ i ][ j ];
      
        }
    }

    //Intercambiar coordenadas capa verde
    for(int i = 0; i < H_IMG; i++) {
        for(int j = 0; j < W_IMG; j++) {
            
            tmp_layer[ W_IMG - 1 - j ][ i ] = green_layer[ i ][ j ];
      
        }
    }

    //Actualizar capa verde
    for(int i = 0; i < W_IMG; i++) {
        for(int j = 0; j < H_IMG; j++) {
            
            green_layer[ i ][ j ] = tmp_layer[ i ][ j ];
        }
    }

    //Intercambiar coordenadas capa azul
    for(int i = 0; i < H_IMG; i++) {
        for(int j = 0; j < W_IMG; j++) {
            
            tmp_layer[ W_IMG - 1 - j ][ i ] = blue_layer[ i ][ j ];
        }
    }

    //Actualizar capa azul
    for(int i = 0; i < W_IMG; i++) {
        for(int j = 0; j < H_IMG; j++) {
          
            blue_layer[ i ][ j ] = tmp_layer[ i ][ j ];
        }
    }
    }

    void rotate_horario() {


   std::string funcion = "H90";
    
    histostack.push( funcion ); //Agrega la llamada a la función al historial
    histotal.push( funcion ); //Agrega la llamada a la funciión al historial total


    unsigned char **tmp_layer = new unsigned char*[ W_IMG ];

    for(int i = 0; i < W_IMG; i++) 
        tmp_layer[ i ] = new unsigned char[ H_IMG ];


    for(int i = 0; i < H_IMG; i++) {
        for(int j = 0; j < W_IMG; j++) {

            tmp_layer[ j ][ H_IMG - 1 - i ] = red_layer[ i ][ j ];

        }
    }

    for(int i = 0; i < W_IMG; i++) {
        for(int j = 0; j < H_IMG; j++) {

            red_layer[ i ][ j ] = tmp_layer[ i ][ j ];

        }
    }

    for(int i = 0; i < H_IMG; i++) {
        for(int j = 0; j < W_IMG; j++) {
            
            tmp_layer[ j ][ H_IMG - 1 - i ] = green_layer[ i ][ j ];
        
        }
    }

    for(int i = 0; i < W_IMG; i++) {
        for(int j = 0; j < H_IMG; j++) {
        
            green_layer[ i ][ j ] = tmp_layer[ i ][ j ];
        
        }
    }

    for(int i = 0; i < H_IMG; i++) {
        for(int j = 0; j < W_IMG; j++) {
        
            tmp_layer[ j ][ H_IMG - 1 - i ] = blue_layer[ i ][ j ];
        
        }
    }

    for (int i = 0; i < W_IMG; i++){
      for (int j = 0; j < H_IMG; j++){

        blue_layer[ i ][ j ] = tmp_layer[ i ][ j ];
      
      }
    }

    for (int i = 0; i < W_IMG; i++){
      delete[] tmp_layer[i];
      delete[] tmp_layer;
  }
  }

    void undo(){

      if(!histostack.empty()){

        std::string lastf = histostack.top();
        char function = lastf[0];
        int d = std::stoi(lastf.substr(1));
        
        histoaux.push(lastf);
        histostack.pop();
      
        switch(function){
        
          case 'L':

            move_right(d);
            histostack.pop();
            break;
        
          case 'R':
        
            move_left(d);
            histostack.pop();
            break;
        
          case 'U':
          
            move_down(d);
            histostack.pop();

            break;
        
          case 'D':
        
            move_up(d);
            histostack.pop();

            break;
          case 'A':
            rotate_horario();
            histostack.pop();
            break;

          case 'H':
            rotate();
            histostack.pop();
            break;
          }

        } else {

          std::cout<<"No se puede realizar esta acción, el historial esta vacío"<<std::endl;

    }
}
    void redo(){
      
      if(!histoaux.empty()){
        
        std::string lastf = histoaux.top();
        char function = lastf[0];
        int d = std::stoi(lastf.substr(1));

        switch(function){
          case 'L':

            move_left(d);
            histostack.pop();
            break;

          case 'R':

            move_right(d);
            histostack.pop();
            break;

          case 'U':

            move_up(d);
            histostack.pop();
            break;

          case 'D':

            move_down(d);
            histostack.pop();
            break;

          case 'A':

            rotate();
            histostack.pop();
            break;

          case 'H':
            
            rotate_horario();
            histostack.pop();
            break;
          }

      } else {

        std::cout<<"No se puede realizar esta acción, el historial de borrado esta vacio"<<std::endl;
    
    }
  }

    void repeat(){

      if(!histostack.empty()){

        std::string lastf = histostack.top();
        char function = lastf[0];
        int d = std::stoi(lastf.substr(1));

        switch(function){
          case 'L':

            move_left(d);
            break;

          case 'R':

            move_right(d);
            break;

          case 'U':

            move_up(d);
            break;

          case 'D':

            move_down(d);
            break;

          case 'A':

            rotate();
            break;

          case 'H':
            
            rotate_horario();
            break;

      }
    } else {

        std::cout<<"No se puede realizar esta acción, el historial esta vacío"<<std::endl;

    }
  }

    void repeat_all(){

    }

private:
  // Función privada que guarda la imagen en formato .png
  void _draw(const char* nb) {
    //    unsigned char rgb[H_IMG * W_IMG * 3], *p = rgb;
    unsigned char *rgb = new unsigned char[ H_IMG * W_IMG * 3 ];
    unsigned char *p = rgb;
    unsigned x, y;

    // La imagen resultante tendrá el nombre dado por la variable 'nb'
    FILE *fp = fopen(nb, "wb");

    // Transformamos las 3 matrices en una arreglo unidimensional
    for (y = 0; y < H_IMG; y++)
        for (x = 0; x < W_IMG; x++) {
            *p++ = red_layer[ y ][ x ];    /* R */
            *p++ = green_layer[ y ][ x ];    /* G */
            *p++ = blue_layer[ y ][ x ];    /* B */
        }
    // La función svpng() transforma las 3 matrices RGB en una imagen PNG 
    svpng(fp, W_IMG, H_IMG, rgb, 0);
    fclose(fp);
}

  
};

#endif
