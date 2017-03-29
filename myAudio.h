#ifndef MYAUDIO_H
#define MYAUDIO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

#define SONGFILE1 "DiscoMusic.wav"  //archivo del audio que se reproduce durante la simulacion del modo uno
#define MAX_SAMPLES	3

typedef unsigned int uint;
typedef ALLEGRO_SAMPLE* sampleID;   //sirve para tener un mayor nivel de abstraccion de allegro

class MyAudio{
private:
	sampleID loadedSamples[MAX_SAMPLES];       //Se agrega por escalabilidad y para destruir los samples al finalizar el programa
	uint samplesStored;
	bool valid;
public:
	MyAudio(uint sampleOverlap);                //sampleOverlap: hasta cuantas samples se pueden escuchar al mismo tiempo
	sampleID loadSample(char* fileName);        //carga en memoria el sample deseado 
	void playSampleOnce(sampleID sample);       //Reproduce una vez el sample recibido
	void playSampleLooped(sampleID sample);     //Reproduce loopeado el sample recibido
	void stopSample(sampleID sample);           //detiene la reproduccion del sample recibido
	void stopSamples();                         //detiene la reproduccion de todas las samples. No es necesario en este programa pero se agrega por escalabilidad 
	bool isValid();
	void destructor();
};

#endif /* MYAUDIO_H */
