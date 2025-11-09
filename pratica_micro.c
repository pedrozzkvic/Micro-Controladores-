#include <Utility.h>
#include <LCD_Blio.h>
#include <stdio.h>

// A questão 1 era só pra acender os leds da placa, deixar em HIGH PA6  e PA7

void questao2(){ //Fazer um buzzer dar um beep curto, espera, mais 2 beeps curtos
	  while (1){
		  Delay_us(1000000);

		  GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		  Delay_us(500000);
		  GPIO_Write_Pin(GPIOA, PIN_6, LOW);

		  Delay_us(1000000);

		  GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		  Delay_us(500000);
		  GPIO_Write_Pin(GPIOA, PIN_6, LOW);

		  Delay_us(500000);

		  GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		  Delay_us(500000);
		  GPIO_Write_Pin(GPIOA, PIN_6, LOW);
	  }
}

void questao3(){ //Acender dois leds diferentes, um acende aos poucos e outro ao contrário
  int atraso;
	while(1){
		for(atraso = 0; atraso <= 10000; atraso += 50){
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);

			Delay_us(atraso);

			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
			Delay_us(10000 - atraso);
		}

		for(atraso = 0; atraso <= 10000; atraso += 50){
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);

	     	Delay_us(atraso);

			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
			Delay_us(10000 - atraso);

		}
	}
}

void questao4(){ //Usar os botões K0, K1 e KUP pra acender leds externos
    int botao1 = GPIO_Read_Pin(GPIOA, PIN_0);
    int botao2 = GPIO_Read_Pin(GPIOE, PIN_3);
    int botao3 = GPIO_Read_Pin(GPIOE, PIN_4);

    if (botao1 == HIGH){
                GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
                GPIO_Write_Pin(GPIOA, PIN_3, LOW);
                GPIO_Write_Pin(GPIOA, PIN_4, LOW);
                Delay_ms(200);
    }

    if (botao2 == LOW){
                GPIO_Write_Pin(GPIOA, PIN_2, LOW);
                GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
                GPIO_Write_Pin(GPIOA, PIN_4, LOW);
                Delay_ms(200);
    }
    if (botao3 == LOW){
              GPIO_Write_Pin(GPIOA, PIN_2, LOW);
        	  GPIO_Write_Pin(GPIOA, PIN_3, LOW);
              GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
              Delay_ms(200);
    }
}

void questao5(){ //K0 e K1 acendem seus respectivos leds, quando um ta acesso o outro travaado, kup reseta
	while (1)
	{
	    int k1 = !GPIO_Read_Pin(GPIOE, PIN_4); // botão K1
	    int k2 = !GPIO_Read_Pin(GPIOE, PIN_3); // botão K2
	    int k3 = GPIO_Read_Pin(GPIOE, PIN_2);  // botão K3 (pull-down)

	    if (k3) { // botão de reset
	        GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	        GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	    }
	    else if (k1 && !k2) { // só K1 pressionado
	        GPIO_Write_Pin(GPIOA, PIN_6, LOW);
	        GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	    }
	    else if (k2 && !k1) { // só K2 pressionado
	        GPIO_Write_Pin(GPIOA, PIN_7, LOW);
	        GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	    }
	    else { // nenhum ou ambos pressionados
	        GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	        GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	    }
	}

}

void questao6(){ //Fazer uma contagem binária usando 8 leds
	int aux = 0;
	while(1){
	GPIO_Write_Port(GPIOE, aux);
	aux++;
	if(aux == 255){
		aux = 0;
	}
	Delay_ms(250);
	}
}

void questao7(){ //Um led andante indo e voltando
	for(int i = 0; i < 8; i++){
		if(i-1 < 0){
            GPIO_Write_Pin(GPIOE, i, HIGH);
		}
        GPIO_Write_Pin(GPIOE, i, HIGH);
        Delay_ms(100);
  	    GPIO_Write_Pin(GPIOE, i-1 , LOW);
	}

	for(int i = 8; i > 0; i--){
		if(i-1 < 0){
            GPIO_Write_Pin(GPIOE, i, LOW);
		}
        GPIO_Write_Pin(GPIOE, i-1, HIGH);
        Delay_ms(100);
  	    GPIO_Write_Pin(GPIOE, i , LOW);
	}
}

void questao8(){ //simulando um cruzamento, os leds correspondem aos semáforos
	GPIO_Write_Pin(GPIOE, PIN_0, HIGH); // liga vermelho 1
	GPIO_Write_Pin(GPIOE, PIN_5, HIGH); // liga verde 2

	Delay_ms(2000);

	GPIO_Write_Pin(GPIOE, PIN_5, LOW); // desliga verde 2
	GPIO_Write_Pin(GPIOE, PIN_4, HIGH); // liga amarelo 2

	Delay_ms(2000);

	GPIO_Write_Pin(GPIOE, PIN_4, LOW); // desliga amarelo 2
	GPIO_Write_Pin(GPIOE, PIN_3, HIGH); // liga vermelho 2
	GPIO_Write_Pin(GPIOE, PIN_0, LOW); // desliga vermelho 1
	GPIO_Write_Pin(GPIOE, PIN_2, HIGH); // liga verde 1

	Delay_ms(2000);

	GPIO_Write_Pin(GPIOE, PIN_2, LOW); // desliga verde 1
	GPIO_Write_Pin(GPIOE, PIN_1, HIGH); // liga amarelo 1

	Delay_ms(2000);

	GPIO_Write_Pin(GPIOE, PIN_1, LOW); // desliga amarelo 1
	GPIO_Write_Pin(GPIOE, PIN_3, LOW); // desliga vermelho 2
}

void questao9(){ //contagem hexadecimal indo e voltando num display de 7 segmentos
	 const uint8_t mask[16]={
	 0b00111111, //0
	 0b00000110, //1
	 0b01011011, //2
	 0b01001111, //3
	 0b01100110, //4
	 0b01101101, //5
	 0b01111101, //6
	 0b00000111, //7
	 0b01111111, //8
	 0b01101111, //9
	 0b01110111, //A
	 0b01111100, //B
	 0b00111001, //C
	 0b01011110, //D
	 0b01111001, //E
	 0b01110001  //F
	 };

	while(1){
		for(int i = 0; i < 16; i++){
			GPIO_Write_Port(GPIOA, mask[i]);
			Delay_ms(500);
		}
		for(int i = 15; i >= 0; i--){
			GPIO_Write_Port(GPIOA, mask[i]);
			Delay_ms(500);
		}
	}
}

void questao10(){ //mesma coisa da anterior, mas quando um chega em 16 o outro vai pra 1. Seria um o(n^2)
	 const uint8_t mask[16]={
	 0b00111111, //0
	 0b00000110, //1
	 0b01011011, //2
	 0b01001111, //3
	 0b01100110, //4
	 0b01101101, //5
	 0b01111101, //6
	 0b00000111, //7
	 0b01111111, //8
	 0b01101111, //9
	 0b01110111, //A
	 0b01111100, //B
	 0b00111001, //C
	 0b01011110, //D
	 0b01111001, //E
	 0b01110001  //F
	 };

	void printarDisplay(int display, int valor){
	    GPIO_Write_Pin(GPIOE, 7, LOW);
	    GPIO_Write_Pin(GPIOE, 8, LOW);

	    GPIO_Write_Port(GPIOA, mask[valor]);

	    if (display == 0)
	        GPIO_Write_Pin(GPIOE, 7, HIGH); //dezena
	    else if(display == 1){
	        GPIO_Write_Pin(GPIOE, 8, HIGH); //unidade
		    Delay_us(50);
	    }
	}

	 while (1){
	        for (int dezena = 0; dezena < 16; dezena++){
	            for (int unidade = 0; unidade < 16; unidade++){
	                int contador = 0;
	                while (contador < 1000){
	                    printarDisplay(0, dezena);
	                    printarDisplay(1, unidade);
	                    Delay_us(100);
	                    contador++;
	            }
	        }
	    }
	}

	// GND display -> pino 1 (transistor)
	// Pino qualquer -> pino 2 (transistor)
	// GND da placa -> pino 3 (transistor)

}

void questao11(){ //exibir os nicks meus de vinicius e vinicius num led, e fazer uma contagem regressiva
	LCD_Init(4, 20);
	LCD_Display_ON();
	LCD_Clear();
	LCD_Cursor_OFF();
	LCD_Blink_OFF();

	char string[20];

	LCD_Write_String(1, 1, "zzkvic");
	LCD_Write_String(2, 1, "xt");
	LCD_Write_String(3, 1, "Ruitso");


	for(int i = 10; i != 0; i--){
		sprintf(string, "%d", i);
		LCD_Write_String(4, 1, string);
		Delay_ms(500);
		LCD_Write_String(4, 1, "          ");
	}
}

void questao12(){ //usar um motor dc e uma ponte H para um motor acelerar, parar,  e acelerar no sentido oposto
	while(1){
		for(int i = 0; i < 2000; i++){
			GPIO_Write_Pin(GPIOA, 1, HIGH);
			GPIO_Write_Pin(GPIOA, 0, LOW);
			GPIO_Write_Pin(GPIOA, 6, HIGH);
			Delay_us(i);
			GPIO_Write_Pin(GPIOA, 6, LOW);
			Delay_us(2000-i);
		}
		for(int i = 0; i < 2000; i++){
			GPIO_Write_Pin(GPIOA, 1, HIGH);
			GPIO_Write_Pin(GPIOA, 0, LOW);
			GPIO_Write_Pin(GPIOA, 6, HIGH);
			Delay_us(2000-i);
			GPIO_Write_Pin(GPIOA, 6, LOW);
			Delay_us(i);
		}
		for(int i = 0; i < 2000; i++){
			GPIO_Write_Pin(GPIOA, 1, LOW);
			GPIO_Write_Pin(GPIOA, 0, HIGH);
			GPIO_Write_Pin(GPIOA, 6, HIGH);
			Delay_us(i);
			GPIO_Write_Pin(GPIOA, 6, LOW);
			Delay_us(2000-i);
		}
		for(int i = 0; i < 2000; i++){
			GPIO_Write_Pin(GPIOA, 1, LOW);
			GPIO_Write_Pin(GPIOA, 0, HIGH);
			GPIO_Write_Pin(GPIOA, 6, HIGH);
			Delay_us(2000-i);
			GPIO_Write_Pin(GPIOA, 6, LOW);
			Delay_us(i);
		}
	}
}

void questao13(){ //semelhante a anterior
	void acionar_passo(int passo){
	    switch(passo){
	        case 1: GPIO_Write_Port(GPIOA, 0b0001); break;
	        case 2: GPIO_Write_Port(GPIOA, 0b1000); break;
	        case 3: GPIO_Write_Port(GPIOA, 0b0010); break;
	        case 4: GPIO_Write_Port(GPIOA, 0b0100); break;
	    }
	}

	int passos = 1;

    	for(int passos = 0; passos < 200; passos++){
	        acionar_passo(passos);
	        passos++;

	        if(passos > 4){
	        	passos = 1;
	        }

	        Delay_us(3000);


	    for(int passos = 0; passos < 200; passos++){
	        acionar_passo(passos);
	        passos++;

	        if(passos > 4){
	        	passos = 1;
	        }

	        Delay_us(3000);
	    }

	    Delay_ms(1000);
	    passos = 4;

	    for(int passos = 0; passos < 200; passos++){
	        acionar_passo(passos);
	        passos--;

	        if(passos < 1){
	        	passos = 4;
	        }

	        Delay_us(3000);
	    }
    }
}

void questao14(){ //apagar e acender leds usando interrupção
	void exibirHexPortA(uint8_t valor) { GPIO_Write_Port(GPIOA, valor);}
	void exibirHexPortD(uint8_t valor){ GPIO_Write_Port(GPIOD, valor);}

	uint32_t tempo_led1 = 0;
	uint32_t tempo_led2 = 0;
  while(1){
	if (GPIO_Read_Pin(GPIOE, PIN_4) == 0){
	tempo_led1 += 2000; // adiciona 3 segundos

	while (GPIO_Read_Pin(GPIOE, PIN_4) == 0); // espera soltar
	}

	// Verifica botão K1 (LED2)
	if (GPIO_Read_Pin(GPIOE, PIN_3) == 0){
	tempo_led2 += 4000;

	while (GPIO_Read_Pin(GPIOE, PIN_3) == 0);
	}

	// Atualiza LED1
	if (tempo_led1 > 0){
	GPIO_Write_Pin(GPIOA, PIN_6, LOW); // acende LED (ativo em LOW)
	Delay_ms(100); // passo de tempo
	tempo_led1 -= 100;
	} else {
	GPIO_Write_Pin(GPIOA, PIN_6, HIGH); // apaga LED
	}

	// Atualiza LED2
	if (tempo_led2 > 0){
	GPIO_Write_Pin(GPIOA, PIN_7, LOW);
	Delay_ms(100);
	tempo_led2 -= 100;
	} else {
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	}
  }
}

void questao15(){ //acender um led externo somente se os dois botões forem pressionados juntos
	while(1){
		if(!GPIO_Read_Pin(GPIOE, 4) && GPIO_Read_Pin(GPIOE, 3)){
			while(!GPIO_Read_Pin(GPIOE, 4)){
				if(!GPIO_Read_Pin(GPIOE, 4) && !GPIO_Read_Pin(GPIOE, 3)){
					GPIO_Write_Pin(GPIOA, 6, LOW);
					Delay_ms(500);

					if(GPIO_Read_Pin(GPIOE, 3) || GPIO_Read_Pin(GPIOE, 4)){
						break;
					}
				}
			}
		}
		GPIO_Write_Pin(GPIOA, 6, HIGH);
		Delay_ms(500);
	}
}

void questao16() {
	while(1){
		int cont = 0;
		if(!GPIO_Read_Pin(GPIOE, 4) && GPIO_Read_Pin(GPIOE, 3)){
			while(!GPIO_Read_Pin(GPIOE, 4)){
				cont += 1;
				Delay_ms(1);
				if(!GPIO_Read_Pin(GPIOE, 4) && !GPIO_Read_Pin(GPIOE, 3) && cont <= 1000){
					GPIO_Write_Pin(GPIOA, 6, LOW);
					Delay_ms(500);

					if(GPIO_Read_Pin(GPIOE, 3) || GPIO_Read_Pin(GPIOE, 4)){
						break;
					}
				}
			}
		}
		GPIO_Write_Pin(GPIOA, 6, HIGH);
		Delay_ms(500);
	}
}

void questao17(){
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_0, OUTPUT);

	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	int atraso = 500;

	while(1){
		GPIO_Write_Pin(GPIOE, PIN_0, HIGH);
		Delay_us(atraso);
		GPIO_Write_Pin(GPIOE, PIN_0, LOW);
		Delay_us(20000 - atraso);

		if(!GPIO_Read_Pin(GPIOE, PIN_3) && atraso != 2500){
			atraso += 50;
		}
		if(!GPIO_Read_Pin(GPIOE, PIN_4) && atraso != 500){
			atraso -= 50;
		}
	}
}

void questao18(){ //fazer um teclado de membrana 4x4 ter seus caracteres mostrados num display de 7 segmentos quando pressionados
	// Set dos binários
	const uint8_t mask[16] = {
			0b00111111, //0
			0b00000110, //1
			0b01011011, //2
			0b01001111, //3
			0b01100110, //4
			0b01101101, //5
			0b01111101, //6
			0b00000111, //7
			0b01111111, //8
			0b01101111, //9
			0b01110111, //A
			0b01111100, //B
			0b00111001, //C
			0b01011110, //D
			0b01111001, //E
			0b01110001  //F
	};

	while(1){ //um sensor de proximidade que apita mais quanto mais próximo
			GPIO_Write_Pin(GPIOD, PIN_0, LOW);

				Delay_ms(5);

				if (!GPIO_Read_Pin(GPIOD, PIN_4)){
				GPIO_Write_Port(GPIOA, mask[1]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_5)){
				GPIO_Write_Port(GPIOA, mask[2]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_6)){
				GPIO_Write_Port(GPIOA, mask[3]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_7)){
				GPIO_Write_Port(GPIOA, mask[10]);
				}
				GPIO_Write_Pin(GPIOD, PIN_0, HIGH);


				GPIO_Write_Pin(GPIOD, PIN_1, LOW);
				Delay_ms(5);
				if (!GPIO_Read_Pin(GPIOD, PIN_4)){
				GPIO_Write_Port(GPIOA, mask[4]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_5)){
				GPIO_Write_Port(GPIOA, mask[5]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_6)){
				GPIO_Write_Port(GPIOA, mask[6]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_7)){
				GPIO_Write_Port(GPIOA, mask[11]);
				}
				GPIO_Write_Pin(GPIOD, PIN_1, HIGH);

				GPIO_Write_Pin(GPIOD, PIN_2, LOW);
				Delay_ms(5);
				if (!GPIO_Read_Pin(GPIOD, PIN_4)){
				GPIO_Write_Port(GPIOA, mask[7]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_5)){
				GPIO_Write_Port(GPIOA, mask[8]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_6)){
				GPIO_Write_Port(GPIOA, mask[9]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_7)){
				GPIO_Write_Port(GPIOA, mask[12]);
				}
				GPIO_Write_Pin(GPIOD, PIN_2, HIGH);

				GPIO_Write_Pin(GPIOD, PIN_3, LOW);
				Delay_ms(15);
				if (!GPIO_Read_Pin(GPIOD, PIN_4)){
				GPIO_Write_Port(GPIOA, mask[14]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_5)){
				GPIO_Write_Port(GPIOA, mask[0]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_6)){
				GPIO_Write_Port(GPIOA, mask[15]);
				} else if (!GPIO_Read_Pin(GPIOD, PIN_7)){
				GPIO_Write_Port(GPIOA, mask[13]);
				}

				GPIO_Write_Pin(GPIOD, PIN_3, HIGH);
	}

}

void questao19(){
	uint32_t tempoPulso = 0;
	float distancia = 0.0f;

	GPIO_Write_Pin(GPIOA, 0, HIGH);
	Delay_us(10);
	GPIO_Write_Pin(GPIOA, 0, LOW);

	while(GPIO_Read_Pin(GPIOA, 1) == LOW);

	while(GPIO_Read_Pin(GPIOA, 1) == HIGH){
		Delay_us(1);
		tempoPulso++;
	}

	distancia = tempoPulso / 58.0f;
	if(tempoPulso > 25000){
		distancia = -1.0f;
	} else {
		distancia = tempoPulso / 58.0f;
	}

	if(distancia < 0){
		GPIO_Write_Pin(GPIOA, 2, LOW);
	}
	else if(distancia > 50.0f){
		GPIO_Write_Pin(GPIOA, 2, LOW);
	}
	else if(distancia >= 30.0f){
		GPIO_Write_Pin(GPIOA, 2, HIGH);
		Delay_ms(300);
		GPIO_Write_Pin(GPIOA, 2, LOW);
		Delay_ms(300);
	}
	else if(distancia > 10.0f){
		GPIO_Write_Pin(GPIOA, 2, HIGH);
		Delay_ms(200);
		GPIO_Write_Pin(GPIOA, 2, LOW);
		Delay_ms(300);
	} else {
		GPIO_Write_Pin(GPIOA, 2, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, 2, LOW);
		Delay_ms(300);
	}
	Delay_ms(500);
}



int main{
    while(1){
        questao19
    }
    return 0;
}
