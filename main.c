#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
  // aktualny stan
  volatile uint8_t stan = 0;
  volatile uint8_t miga = 0;

  // wyjscia swiatel
  DDRB =  0b00111111;
  DDRC =  0b00111111;

  // bez swiecenia
  PORTB = 0b00000000;
  PORTC = 0b00000000;

  // wejscie przycisku
  DDRD =  0b11111011;


  // glowna petla
  while (1) {

    // jezeli przycisk wcisniety
    if (~PIND & (1<<PD2)) {
      _delay_ms(80);
      // i caly czas jest wcisniety
      if (~PIND & (1<<PD2)) {
        // kolejny stan
        stan++;
        miga = 1;

        if (stan == 3)
          stan = 1;
      }
    }


    // obsluga stanow
    switch (stan) {
      // skrzyzowanie nieczynne
      case 0:
        if (miga) {
          PORTB = 0b00100100;
          PORTC = 0b00100100;
        } else {
          PORTB = 0b00000000;
          PORTC = 0b00000000;
        }

        miga = !miga;


        _delay_ms(1000);


        break;

      // zolty na NS -> czerwony na NS, zolto-czerwony na EW, zielony na EW
      case 1:
        if (miga) {
          PORTB = 0b00100100;
          PORTC = 0b00101101;

          _delay_ms(1000);

          PORTB = 0b00001001;
          PORTC = 0b00010010;

          miga = 0;
        }


        break;

      // zolty na EW -> czerowny na EW, zolto-czerwony na NS, zielony na NS
      case 2:
        if (miga) {
          PORTC = 0b00100100;
          PORTB = 0b00101101;

          _delay_ms(1000);

          PORTC = 0b00001001;
          PORTB = 0b00010010;

          miga = 0;
        }
        break;
    }
  }

  return 0;
}
