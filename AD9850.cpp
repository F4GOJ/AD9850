/******************************************************************************************************************
 * Arduino library for AD9850
 * Created 23/08/2014
 * Christophe Caiveau f4goj@free.fr 
 *
 * Use this library freely
 *
 * Hardware connections : 
 * W_CLK   -> any pin
 * FQ_UD   -> any pin
 * DATA/D7 -> any pin
 * RESET   -> any pin
 *
 * Functions :
 * dds.begin(W_CLK pin, FQ_UD pin, DATA pin, RESET pin); Initialize the output pins and master reset the AD9850 
 * dds.calibrate(frequency); Compensation of crystal oscillator frequency
 * dds.setfreq(frequency,phase); frequency in Hz, phase coded on 5 bits
 * dds.down(); power down mode reducing the dissipated power from 380mW to 30mW @5V
 * dds.up(); wake-up the AD9850
 *
 * AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf
 *
 *****************************************************************************************************************/

#include <AD9850.h>

AD9850 DDS;

AD9850::AD9850() {

}

void AD9850::begin(int w_clk, int fq_ud, int data, int reset) {
	W_CLK = w_clk;
	FQ_UD = fq_ud;
	DATA = data;
	RESET = reset;
	deltaphase = 0;
	phase = 0;
	calibFreq = 125000000;
	begin_priv();
}

void AD9850::begin_priv() {
	pinMode(W_CLK, OUTPUT);
	pinMode(FQ_UD, OUTPUT);
	pinMode(DATA, OUTPUT);
	pinMode(RESET, OUTPUT);
	
	pulse(RESET);
	pulse(W_CLK);
	pulse(FQ_UD);
}

void AD9850::update() {

    for (int i=0; i<4; i++, deltaphase>>=8) {
     shiftOut(DATA, W_CLK, LSBFIRST, deltaphase & 0xFF);
    }
    shiftOut(DATA, W_CLK, LSBFIRST, phase & 0xFF);
    pulse(FQ_UD);
}


void AD9850::setfreq(double f, uint8_t p) {
	deltaphase = f * 4294967296.0 / calibFreq;
	phase = p << 3;
	update();
}


void AD9850::down() {
	pulse(FQ_UD);
	shiftOut(DATA, W_CLK, LSBFIRST, 0x04);
	pulse(FQ_UD);
}
    

void AD9850::up() {
	update();
}


void AD9850::calibrate(double TrimFreq)
{
	calibFreq = TrimFreq;
}


void AD9850::pulse(int pin) {
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}
