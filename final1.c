#include <DIO.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


int counter = 0;
int temp = 0 ;
bool current_state1=false, previous_state1=false, current_state2=false, previous_state2=false ;
long long millis1, millis2 ;
long  overflow_counts = 0 ;


void setup() {
  lcd.begin(16,2);
  DIO_InitPortDirection(PB, INPUT, 0x01);     // pir1         arduino pin 8
  DIO_InitPortDirection(PB, INPUT, 0x02 );    // pir2         arduino pin 9
  DIO_InitPortDirection(PB,OUTPUT, 0x04 );    // fan          arduino pin 10
  DIO_InitPortDirection(PB,OUTPUT, 0x08 );    // LED          arduino pin 11

  timer1_init();  
  ADC_init();
}

void loop() {
  
    if(temp >= 35)
      DIO_WritePort(PB, HIGH, 0x04);
    else if(temp< 35)
      DIO_WritePort(PB, LOW , 0x04);

    count_people();
    
    if(counter >= 1){
      DIO_WritePort(PB, HIGH, 0x08);}
   else if(counter <= 0){
      counter = 0 ;
      DIO_WritePort(PB, LOW , 0x08);
   }
}




void count_people(){
  pir();
  if(current_state1==true && previous_state2==true)
    counter -=1 ;
  if(current_state2==true && previous_state1==true)
    counter +=1 ;
  else
    counter = counter;
  }



void pir(){
  int pir_reading1 = DIO_ReadPort(PB, 0x01);
  int pir_reading2 = DIO_ReadPort(PB, 0x02);

  if(pir_reading1){
    millis1 = millis();
    current_state1 = 1;
    }

  if(pir_reading2){
    millis2 = millis();
    current_state2 = 1;
    }

  if(millis() - millis1 >= 3000 ){
    previous_state1 =  current_state1;
    current_state1  = DIO_ReadPort(PB, 0x01);
    }

  if(millis() - millis2 >= 3000 ){
    previous_state2 =  current_state2;
    current_state2  =  DIO_ReadPort(PB, 0x02);
    }
    
  }



void timer1_init()
{
    TCNT1H = 0x0B ;
    TCNT1L = 0xDB ;
    TCCR1A = 0x00 ;
    TCCR1B = 0x04 ;     // prescaler 1:256

    // enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);

    // enable global interrupts
    sei();  
}


ISR(TIMER1_OVF_vect){
    overflow_counts += 1 ;
    if(overflow_counts % 10 == 0)
      ADMUX  = 0x40 ;
    else 
      ADMUX  = 0x45 ; 

    TCNT1H = 0x0B ;
    TCNT1L = 0xDB ;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("count: ");
    lcd.print(counter);    
    lcd.setCursor(0,1);
    lcd.print("temp: ");
    lcd.print(temp);   
 
  } 

void ADC_init(){
    ADCSRA = 0x8F ;
    ADMUX  = 0x45 ; 
    ADCSRA |= (1<<ADSC);
  }
  

ISR(ADC_vect){
    if(overflow_counts % 10 == 0){
      temp = (ADCW/4) ;
    }
    else{
      if(ADCW >= 200){
        lcd.setCursor(0,0);
        lcd.print("WARNING !!");
        lcd.setCursor(0,1);
        lcd.print("WARNING !!");
      }}
    ADCSRA |= (1<<ADSC);
   }
