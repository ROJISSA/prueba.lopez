#include "mkl25z4.h"

#define pine 5
uint4_t array_bcd [9]={0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001}; 
int vector[4][10]{
    {0,0,0,0},
    {0,0,0,1},
    {0,0,1,0},
    {0,0,1,1},
    {0,1,0,0},
    {0,1,0,1},
    {0,1,1,0},
    {0,1,1,1},
    {1,0,0,0},
    {1,0,0,1}
};



void multi_init(){
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
    PORTC -> PCR(1) |= PORTC_PCR_MUX(0);
    PORTC -> PCR(2) |= PORTC_PCR_MUX(0);
    PORTC -> PCR(3) |= PORTC_PCR_MUX(0);
    PORTC -> PCR(4) |= PORTC_PCR_MUX(1);
}

void multi_func(){
    int funcion = puls_retu(pine);
    if(funcion==1){
        PTC -> PSOR |= (1u<<(pine));
        return 1;
    }
    if (funcion==0){
        PTC -> PSOR |= (0u<<(pine));
        return 0;
    }
    
}

int puls_retu(int pinelegido){
    PORTC -> PCR(pinelegido) |= PORTC_PCR_MUX(0);
    int estadopuls = PTC -> PDIR & (1u<<(pinelegido));
    if(estadopuls == 0)
    {
        return 0;
    }
    if(estadopuls == 1)
    {
        return 1;
    }
}

void cont_asce(){
    int cont1 = 0;
    int cont2 = 0;
    for (cont1 = 0; cont1 <= 9 ; cont1 ++)
    {
        if (cont1 == 9 & cont2 < 9)
        {
            cont1 == 0;
            cont2 ++;
        }
    } 
    for (int i = 0; i <= 4; i++)
    {
        PTC -> PSOR |= (vector[i][cont1]<<(5));
        PTC -> PSOR |= (vector[i][cont1]<<(6));
        PTC -> PSOR |= (vector[i][cont1]<<(7));
        PTC -> PSOR |= (vector[i][cont1]<<(8));
    }
}

void cont_desc(){
    int cont1 = 9;
    int cont2 = 9;
    for (cont1 = 9; cont1 = 0 ; cont1 --)
    {
        if (cont1 == 0 & cont2 > 0)
        {
            cont1 == 9;
            cont2 --;
        }
    }
    for (int i = 0; i <= 4; i++)
    {
        PTC -> PSOR |= (vector[i][cont1]<<(9));
        PTC -> PSOR |= (vector[i][cont1]<<(10));
        PTC -> PSOR |= (vector[i][cont1]<<(11));
        PTC -> PSOR |= (vector[i][cont1]<<(12));
    }
}

void control_leds(int pospin, int estado){
    PTC -> PSOR |= (estado<<(pospin));
}