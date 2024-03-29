#include <stdint.h>
#include "sound.h"
#include "efm32gg.h"
#include "math.h"
#include <stdbool.h>
#include "timer.h"
#include "gpio.h"


static int amplitude = 200;
static uint8_t sound_type = 0;
static double time = 0.0;
static int sawtooth_val = 0;
static int frequency = 500;
static bool square_high = false;
static int square_count = 0;
static uint16_t triangle_val = 0;
static bool triangle_rise = true;



void play_sound()
{
    time += 0.00002264285;
    switch(sound_type)
    {
        case 0:
            *DAC0_CH0DATA = 0;
            *DAC0_CH1DATA = 0;
            time = 0.0;
            break;
        case 1:
            play_triangle();
            break;
        case 2:
            play_sawtooth();
            break;
        case 3:
            play_square();
            break;
    }
}

void play_triangle()
{
    if(time > 1)
    {
        time = 0;
        sound_type = 0;
    }
    if(triangle_val > amplitude)
    {
        triangle_rise = false;
    }
    if (triangle_rise)
    {
        triangle_val += (int)round(amplitude * 0.00002264285 * ((double)frequency*2));
    }
    else
    {
        if (triangle_val < (int)round(amplitude * 0.00002264285 * ((double)frequency*2)))
        {
            triangle_rise = true;
        }
        else
        {
            triangle_val -= (int)round(amplitude * 0.00002264285 * ((double)frequency*2));
        }
        
    }
    *DAC0_CH0DATA = triangle_val;
    *DAC0_CH1DATA = triangle_val;
}

void play_sawtooth()
{
    if (time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    if (sawtooth_val > amplitude)
    {
        sawtooth_val = 0;
    }
    sawtooth_val += (int)(round((double)amplitude * 0.00002264285 * (double)frequency));
    *DAC0_CH0DATA = sawtooth_val;
    *DAC0_CH1DATA = sawtooth_val;
}

void change_volume(int delta_volume)
{
    if((abs(delta_volume) > amplitude) && (delta_volume < 0))
    {
        amplitude = 0;
    }
    else
    {
        amplitude += delta_volume;
    }
    
}

void change_frequency(int delta_freq)
{
    if ((abs(delta_freq) > frequency) && delta_freq < 0)
    {
        frequency = 1;
    }
    else
    {
        frequency += delta_freq;
    }
    
} 

void play_square()
{
    if(time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    double period = round((41000/(double)frequency));
    square_count += 1;
    if (square_count > period)
    {
        square_count = 0;
        if(square_high)
        {
            square_high = false;
            *DAC0_CH0DATA = 0;
            *DAC0_CH1DATA = 0;
        }
        else
        {
            square_high = true;
            *DAC0_CH0DATA = amplitude;
            *DAC0_CH1DATA = amplitude;
        }
        
    }

}

void set_sound_type(uint8_t sound)
{
    time = 0.0;
    sound_type = sound;
}

void startup_tune()
{
    GPIO_illuminate_LED(4);
    set_sound_type(1);
    frequency = 522;//C
    for (int i = 0; i < 15000; ++i)
    {
        busy_wait();
        play_sound();
    }
    GPIO_illuminate_LED(5);
    set_sound_type(1);
    frequency = 660;//E
    for (int i = 0; i < 15000; ++i)
    {
        busy_wait();
        play_sound();
    }
    set_sound_type(1);
    frequency = 784;//G
    GPIO_illuminate_LED(6);
    for (int i = 0; i < 15000; ++i)
    {
        busy_wait();
        play_sound();
    }
    set_sound_type(0);
    frequency = 500;
}
