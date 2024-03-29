#include <avr/io.h>
#include <util/delay.h>

struct CTC1
{
    static void setup()
    {
        // CTC mode with TOP-OCR1A

        TCCR1A = 0;
        TCCR1B = _BV(WGM12);

        // toggle channel A on compare match

        TCCR1A = (TCCR1A & ~(_BV(COM1A1) | _BV(COM1A0))) | _BV(COM1A0);

        // set channel A bound pin to output mode

        DDRB |= _BV(1); // PB1 on 328p, use _BV(5) for PB5 on 32U4
    }

    static void set_freq(float f)
    {
        static const float f1 = min_freq(1), f8 = min_freq(8), f64 = min_freq(64), f256 = min_freq(256);

        uint16_t n;

        if (f >= f1)        n = 1;
        else if (f >= f8)   n = 8;
        else if (f >= f64)  n = 64;
        else if (f >= f256) n = 256;
        else                n = 1024;

        prescale(n);

        OCR1A = static_cast<uint16_t>(round(F_CPU / (2 * n * f) - 1));
    }

    static void prescale(uint16_t n)
    {
        uint8_t bits = 0;

        switch (n)
        {
            case    1:  bits = _BV(CS10);               break;
            case    8:  bits = _BV(CS11);               break;
            case   64:  bits = _BV(CS11) | _BV(CS10);   break;
            case  256:  bits = _BV(CS12);               break;
            case 1024:  bits = _BV(CS12) | _BV(CS10);   break;
            default:    bits = 0;
        }

        TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11) | _BV(CS10))) | bits;
    }

    static inline float min_freq(uint16_t n)
    {
        return ceil(F_CPU / (2 * n * 65536));
    }
};

void setup()
{
    CTC1::setup();
}

void loop()
{
 

            CTC1::set_freq(78);
            
        
}
