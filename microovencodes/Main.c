/*
 * File:   Main.c
 * Author: icon
 *
 * Created on December 8, 2021, 12:36 AM
 */


#include <xc.h>
#include "clcd.h"
#include "Main.h"
#include "matrix_keypad.h"
#include "timers.h"

#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)

char sec, min;
unsigned char operation_mode, reset_flag;// set the operation

static void init_config(void) {
    // intialization of clcd
     init_clcd();
     // intialization of MKP Module
     init_matrix_keypad();
     // intialization of Timer2  Module
     init_timer2();
     PEIE =1;
     GIE =1;
     
     FAN_DDR =0; //FAN pin setting as output
     FAN =0; //FAN is kept OFF
}

void main(void) {
    unsigned char key;
    
    init_config();
    power_on_screen();
    clear_clcd();
    operation_mode = COOKING_MODE_DISPLAY;
     while (1) {
         key = read_matrix_keypad(STATE);//0 1 2....9 * #
         if(operation_mode == MICRO_MODE)
         {
             ;
         }
         else if(key ==1)//MKP key1 is pressed
         {
            operation_mode =MICRO_MODE;
            reset_flag = MICRO_MODE_RESET;
            clear_clcd();
            clcd_print(" Power = 900W ",LINE2(0));
            __delay_ms(3000);
            clear_clcd();
            
            
         }
         switch(operation_mode)
         {
             case COOKING_MODE_DISPLAY:
                 cooking_mode_display();
                 break;
             case MICRO_MODE:
                 set_time(key);
                 
                 break;
                
                 
         }
         reset_flag = RESET_NOTHING;
        
    }
}
void clear_clcd(void)
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(100);
}

void power_on_screen(void)
{
    for(int i =0;i<16;i++)
    {
         clcd_putch(BLOCK,LINE1(i));
    }
    clcd_print("  Powering ON   ",LINE2(0));
    clcd_print(" Microwave Oven ",LINE3(0));
     for(int i =0;i<16;i++)
     {
         clcd_putch(BLOCK,LINE4(i));
     }
    // 3sec Delay
    __delay_ms(3000);
}

void cooking_mode_display(void)
{
    clcd_print("1.Micro",LINE1(0));
    clcd_print("2.Grill",LINE2(0));
    clcd_print("3.Convection",LINE3(0));
    clcd_print("4.Start",LINE4(0));
}

void set_time(unsigned char key)
{
    static int wait, blink, key_count;
    if(reset_flag == MICRO_MODE_RESET)
    {
        wait =10;
        blink =0;
        key_count =0;
        sec =0;
        min =0;
        key = ALL_RELEASED; 
        clcd_print("SET TIME (MM:SS)",LINE1(0));
        clcd_print("TIME- ",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    
        
        
    }
    
    //BAsed On MKP key press read sec and min:
    //Key : 0,1,2,4...9
    //Except keys: '*','#',ALL_RELEASED
    if(key != '*' && key !='#' &&key != ALL_RELEASED)
    {
        //Accept sec field :
        key_count++;
        if(key_count <= 2)
        {    
            sec =sec * 10 + key;
        }
        else if(key_count >2 && key_count <=4)
        {
            min= min* 10 +key;
        }
        
    }
    if(key == '*')
    {
        //To clear sec:
        if(key_count <= 2)
        {
            sec = 0;
            key_count = 0;
        }
        else if(key_count >2 && key_count <=4)
        {
            min =0;
            key_count = 2;
        }
        
    }
    if(key == '#')//Enter key
    {
        clear_clcd();
        operation_mode = TIME_DISPLAY;
        FAN = 1; //Turn ON FAN
        //Switch ON The Timer2
        TMR2ON = 1;
    }
        
      
      
    //Display Number of mins and secs
    //sec=0 1 2.....59 
    //sec=12
   /* if(wait++ ==10)
    {
        wait = 0; 
        blink = !blink;
        
    }
    if(blink)
    {
       clcd_putch("  ",LINE2(9)); 
    }
 */ 
    clcd_putch(sec/10 + '0',LINE2(9));//"1"
    clcd_putch(sec%10 + '0',LINE2(10));//"2"
    clcd_putch(min/10 + '0',LINE2(6));//"1"
    clcd_putch(min%10 + '0',LINE2(7));//"2"
    clcd_putch(':',LINE2(8));
    
    
    
    
    
    
}

