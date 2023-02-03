#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "initialization.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define dx 20
#define dy 40
#define mainDELAY_LOOP_COUNT		( 0xfffff )
int i , j , Field[dx][dy] ,x ,y , Gy , head , tail , power , a , b , var ,Game , dir , score , speedOffset;
int highScore =0;
//FILE *f;
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3( void *pvParameters );
xTaskHandle xTask1Handle;
xTaskHandle xTask2Handle;
xTaskHandle xTask3Handle;
//xSemaphoreHandle xMutex;
//unsigned portBASE_TYPE uxPriority;
char received_char;
/*
Unused code
void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
} */
void snakeInit(){
   //f = fopen("highscore.txt" , "r");
  // fscanf(f , "%d" , &highScore);
   //fclose(f);
    for(i=0 ; i<dx ; i++){
        for(j=0 ; j<dy ; j++){
            Field[i][j] = 0; //Populating dimensions array initally with zeroes
        }

}
		//Snake variables
    x =dx/2;
    y =dy/2;
    Gy = y;
    head = 5;
    tail = 1;
    power = 0;
    dir = 'd';
    score = 0;
		Game = 1;
	speedOffset = 0;
        for (i =0; i < head ; i++)
        {
            Gy++;
            Field[x][Gy-head] = i+1;

        }
			//print("\033[?25l");
}
// Unused code
/*void gameOver(){
    //printf("\a");
    if(score > highScore){
        //print("NEW HIGHSCORE %d !!!! \n\n" + score);
        system("pause");
        f = fopen("highscore.txt", "w");
        fprintf(f, "%d", score);
        fclose(f);
    }
    
   
    
    
}*/

void printField(){
    for(int i = 0; i <= dy + 1; i++){  //top row
        print("+");
    }
print("             Current score: ");  
printInt(score);	// Printing current score 	
print("\n");


for(int i = 0; i < dx; i++){     // middle of the play field
    print("+");
    for(int j = 0; j < dy; j++){
        if(Field[i][j] == 0){
            print(" ");
        }
        if(Field[i][j] >0 && Field[i][j] != head){
            print("#"); // Snake body

        }
        if(Field[i][j] == head){
            print("@"); // Snake head

        }
         if(Field[i][j] == -1){
            print("~"); //Power-up

        }
        if(j == dy-1){
            print("+");
					print("\n");
					
        }
     
    }
}

for(int i = 0; i <= dy + 1; i++){    // bottom row
    print("+");
}
print("\n");
}


void randomPower(){
    //srand(time(0));
    a= 1 + rand()%(dx-2);
    b= 1 + rand()%(dy-2);
	//Randomizing power ups
    if( power == 0 && Field[a][b] == 0){
        Field[a][b] = -1; 
        power =1;

    }

}

void movement(char var){
	//using only lower-case letters
	var = tolower(var);
	  //UART0_CTL_R &= ~(1 << 0);
    if( (var == 'w' || var == 's' || var == 'd' || var =='a' ) && 
    (abs(dir-var) > 5)) dir = var; // Passing through walls
    //Left direction
    if (dir == 'a'){
        y--;
			if(x == -1) x = dx-1;
       if(Field[x][y] !=0 &&   Field[x][y] != -1) {			//xSemaphoreGive( xMutex);
					xTaskCreate(	vTask3,		/* Pointer to the function that implements the task. */
					"Game_Over",	/* Text name for the task.  This is to facilitate debugging only. */
					200,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					2,			/* This task will run at priority 1. */
					&xTask3Handle );	}	/* We are not using the task handle. */
	
        if(y == 0) y = dy-1;
        if(Field[x][y] == -1){
            power =0;
					speedOffset++; // Increase speed on power-up
            score+= 5; // Incremeent score by 5
            tail -= 1;
        }
        head++;
        Field[x][y] = head;
    }
    if (dir == 'w'){
        x--;
			      if(x == -1) x = dx-1;
       if(Field[x][y] !=0 &&   Field[x][y] != -1) {			//xSemaphoreGive( xMutex);
					xTaskCreate(	vTask3,		/* Pointer to the function that implements the task. */
					"Game_Over",	/* Text name for the task.  This is to facilitate debugging only. */
					200,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					2,			/* This task will run at priority 1. */
					&xTask3Handle );	}	/* We are not using the task handle. */
	
        if(Field[x][y] == -1){
            power =0;
            score+= 5;
						speedOffset++;
            tail -= 1;
            
        }
        head++;
        Field[x][y] = head;
    }
    if (dir == 's'){
        x++;
			   if(x == dx-1) x = 0;
       if(Field[x][y] !=0 &&   Field[x][y] != -1) {			//xSemaphoreGive( xMutex);
					xTaskCreate(	vTask3,		/* Pointer to the function that implements the task. */
					"Game_Over",	/* Text name for the task.  This is to facilitate debugging only. */
					200,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					2,			/* This task will run at priority 1. */
					&xTask3Handle );	}	/* We are not using the task handle. */
	
        if(Field[x][y] == -1){
            power =0;
					speedOffset++;
            score+= 5;
            tail -= 1;
        }
        head++;
        Field[x][y] = head;
    }
    if (dir == 'd'){
        y++;
			  if(y == dy-1) y = 0;
        if(Field[x][y] !=0 &&   Field[x][y] != -1) {			//xSemaphoreGive( xMutex);
					xTaskCreate(	vTask3,		/* Pointer to the function that implements the task. */
					"Game_Over",	/* Text name for the task.  This is to facilitate debugging only. */
					200,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					2,			/* This task will run at priority 1. */
					&xTask3Handle );	}	/* We are not using the task handle. */
	
         if(Field[x][y] == -1){
            power =0;
            score+= 5;
					 speedOffset++;
            tail -= 1;
        }
        head++;
        Field[x][y] = head;
    }


}


void updateTail(){
		//xSemaphoreTake( xMutex , portMAX_DELAY);


    for( i =0 ; i < dx ; i++ ){
     for( j = 0 ; j < dy ; j++){
        if( Field[i][j] == tail ){
            Field[i][j] = 0;
     }
    }
}
    tail++;	
		//xSemaphoreGive( xMutex);
 // UART0_CTL_R |= (1 << 0) | (1 << 8) | (1<<9);


}



int main(void){
	uart0_init(CLK_SPEED , BAUD_RATE);
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Start game",	/* Text name for the task.  This is to facilitate debugging only. */
					200,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					2,			/* This task will run at priority 2. */
					&xTask1Handle );		/* We are not using the task handle. */

	
	
		vTaskStartScheduler();
   for( ;; );

}


void vTask1( void *pvParameters )
{
	//Start game Task
		clear();
		print(" \n\n          WELCOME TO SNAKE GAME !!!!!!!!!!!!!!!!!!     ");
		print(" \n\n          USE W/A/S/D TO MOVE YOUR SNAKE     " );
		print(" \n\n          EAT POWERUPS TO GAIN LENGTH AND INCREASE YOUR SCORE    " );
		print(" \n\n          TO START GAME PRESS E    " );
		print("\033[?25l");

	for(;;){
		if(received_char == 'e'){
			//If game starts switch to Task 2
			xTaskCreate( vTask2 , "Snake" , 200 , NULL , 1 ,&xTask2Handle);
			snakeInit();
			vTaskDelete(xTask1Handle);
		}
	}

	


}
void vTask2( void *pvParameters )
{
	for(;;){
		printField();
			randomPower();
			movement(dir);
			updateTail();
			vTaskDelay( (100 - speedOffset) / portTICK_RATE_MS);
			clear();
			print("\033[?25l"); // Hide green courser
		
	}


}
void vTask3( void *pvParameters )
{
		clear();
		Game = 0;
		print(" \n\n          WELCOME TO SNAKE GAME !!!!!!!!!!!!!!!!!!     ");
		print(" \n\n          USE w/a/s/d TO MOVE YOUR SNAKE     " );
		print(" \n\n          EAT POWERUPS TO GAIN LENGTH AND INCREASE YOUR SCORE    " );
		print(" \n\n          TO START GAME PRESS E     " );
		print(" \n\n          Score:    " );
		printInt(score);
	if (score > highScore){
		//Checking if you beat the highscore
	highScore = score;
			print(" \n\n       NEW HIGHSCORE !!!!!!!!!!   " );
	}
	print(" \n\n          High-Score:    " );
	printInt(highScore);
	
		print("\033[?25l");
	for(;;){
		//Start game once again
		if(received_char == 'e'){
			speedOffset+=10;
			snakeInit();
			vTaskDelete(xTask3Handle);
		}
	}
}





void UART0_Handler(void){
	
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	received_char = UART0_DR_R;
	UART0_ICR_R &= ~(1 << 4);
	//char c = readChar();
	//printChar(c);
	//printChar(received_char);
	if ( Game == 1){
	//print ("HIT");
	movement(received_char);
	updateTail();
	}
	//Delay(1000);
  portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
	
}


