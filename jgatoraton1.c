/*
 * File:   JuegoGatoRaton.c
 * Author: Sebastián López, Danny Martinez
 *
 * Created on 21 de septiembre de 2017, 03:32 PM
 */


#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <time.h> //***********librerias para       //Para tratamiento y conversión entre formatos de fecha y hora.
#include <stdint.h>//******* poder 
#include <stdlib.h> //************ usar     //generación de números pseudo-aleatorios
#include <math.h> //********* random        //Contiene las funciones matemáticas comunes.


unsigned int RATON = 4; //luz encendida que representa al raton
unsigned int GATO = 1;  //Luz encendidad durante un segundo que representa al gato

void interrupt isr(){  //funcion de interrupcion;
/*    
       if(INTCONbits.RBIF == 1)
        { 
           do{}while(PORTBbits.RB7!=0); 
         if(GATO!=128) //verifica que no haya desborade, es decir si llega al led MSB no pase y no genere error
            GATO = GATO*2;
        INTCONbits.RBIF = 0; //interrupcion
        } 
             */
     if(INTCONbits.INTF == 1) //habilita la interrupcion 
    {
         __delay_ms(50);
        if(GATO!=1) //verifica que no haya desborade, es decir si llega al led LSB no pase y no genere error
           GATO = GATO/2;    //para la izquierda
        
        INTCONbits.INTF = 0; //pone en 0 interrupcion, para despues volver a usar otra
    }      
        
  }

void validar(){ //funcion validar
    if(RATON==GATO){ //en el momento en que los 2 leds esten en la misma posicion
            PORTC = RATON; //el puerto c toma el valor de "GATO"
            PORTDbits.RD0 = 1;  //enciende otro led que esta en el pin 0 del puerto D
            __delay_ms(3000);   //enciende el led por 3 segundos
            PORTDbits.RD0 = 0;  //pasados los 3 segundos apague el led
        }
        else if(PORTBbits.RB7 == 1)//QUIRAR DESDE AQUI
            
        {__delay_ms(50);
         do{}while(PORTBbits.RB7!=0); //verifica si fue presionado el pin 7 del puerto B         
         if(GATO!=128) //verifica que no haya desborade, es decir si llega al led MSB no pase y no genere error
            GATO = GATO*2;
         
       // INTCONbits.RBIF = 0; //interrupcion
        } //HASTA AQUI
        else 
            PORTC = RATON + GATO;   //de no atraparlo siga con el juego //suma que no lleva acarreo
            //PORTC = RATON + GATO;
        
}
void main(void) {
    TRISC = 0;  //puerto c como salidas
    PORTC = 1; //empieza en la primera posicion
    TRISB = 0xFF;   //puerto B como entrada
    ANSEL = 0;      //desactiva entradas analogicas
    ANSELH = 0;
    TRISD = 0;      //puerto D como salidas    
    PORTD = 0;    
    //INTCON = 10001000; //interrupciones de RB4 y RB7
    INTCONbits.GIE = 1;     //habilita las todas las interrupciones
  //  INTCONbits.RBIE = 1; 
    INTCONbits.INTE = 1;     
    
    int aux;    //variables auxiliar
    int aux2=0; //variables auxiliar2
    while (1){
        
        do
        {RATON = rand()%7; //hace que RATON sea aleatorio 
        RATON = pow(2, RATON); //PORTC como 2 a la potencia(random)
        }while(RATON == GATO); //para que el raton nunca caiga en la posicion del gato
        aux = 0;
        while(aux<5){   // hace que el led que representa al raton este con una luz intermitente, menor que 5 paraque halla 10 ocilaciones
            validar(); 
            __delay_ms(50);
            aux2 = RATON;
            RATON = 0; //raton en 0 para que el led titile
            validar();
            __delay_ms(50);
            RATON = aux2;
            aux++; //aux para que el raton titile, el aux2 guarda la variable 
        }   
    }   
}



       