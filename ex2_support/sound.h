#ifndef SOUND_H
#define SOUND_H

void play_sound();
void set_sound_type(sound_type);
void change_volume(int delta_volume);
void change_frequency(int delta_freq);

#endif