#include "myAudio.h"

MyAudio::MyAudio(uint32_t samplesReservation)
{
   	valid = true;
   	if(!al_init())
        	valid = false;
    	else if(!al_install_audio())
    	    	valid = false;
    	else if(!al_init_acodec_addon())
    	{
        	al_uninstall_audio();
        	valid = false;
    	}
    	else if( !al_reserve_samples(samplesReservation))
    	{
            	al_uninstall_audio();
            	valid = false;
    	}
    	samplesStored = 0;
}
sampleID MyAudio::loadSample(char* fileName)
{
    	sampleID newSample= al_load_sample(fileName);   //cargar el archivo del sample en memoria
    	if(newSample)
        	loadedSamples[samplesStored++] = newSample;//si se cargo exitosamente, guardar el ID en la primer 
                                                    //posicion libre del arreglo y "apuntar" al siguiente 
                                                    //lugar libre del arreglo aumentando samplesStored
    	return newSample;   //si hubo error, devuelve NULL, sino devuelve su ID
}
void MyAudio::playSampleOnce(sampleID sample)
{
    	al_play_sample(sample, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}
void MyAudio::playSampleLooped(ALLEGRO_SAMPLE* sample)
{
    	al_play_sample(sample, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_LOOP, nullptr);
}
void MyAudio::stopSample(ALLEGRO_SAMPLE* sample)
{
    	al_stop_sample((ALLEGRO_SAMPLE_ID*)sample);
}
void MyAudio::stopSamples()
{
    	al_stop_samples();
}
bool MyAudio::isValid()
{
    	return valid;
}
void MyAudio::destructor()
{
    	for(uint32_t i = 0; i < samplesStored; ++i)
    	{
        	al_destroy_sample(loadedSamples[i]);
    	}
   	al_uninstall_audio();
}
