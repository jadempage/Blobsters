#include "audio.h"



AudioGeneratorWAV* wav;
AudioFileSourcePROGMEM* file;
AudioOutputI2S* out;

void audio::playSound(soundContext sc) {

	switch (sc) {
		case scButtonA: file = new AudioFileSourcePROGMEM(se_BtnA, sizeof(se_BtnA)); break;
		case scButtonB: file = new AudioFileSourcePROGMEM(se_BtnB, sizeof(se_BtnB)); break;
		case scButtonC: file = new AudioFileSourcePROGMEM(se_BtnC, sizeof(se_BtnC)); break;
	}
	/*file = new AudioFileSourcePROGMEM(af_btnPress, sizeof(af_btnPress));*/
	out = new AudioOutputI2S(0, 1); // Output to builtInDAC
	out->SetOutputModeMono(true);
	wav = new AudioGeneratorWAV();
	wav->begin(file, out);
	audioRunning = true; 
	wavloop(); 
	}

void audio::wavloop()
{
	if (audioRunning) {
		Serial.write(audioRunning);
		if (wav->isRunning()) {
			if (!wav->loop()) {
				wav->stop();
				audioRunning = false; 
				delete wav;
				delete file;
				delete out;
			}
		}
		//else {
		//	delay(1000);
		//}
	}

}

void audio::forceStop() {
	Serial.write(audioRunning);
	if (wav->isRunning()) {
		wav->stop();
		if (wav) { delete wav; }
		if (wav) { delete file; }
		if (wav) { delete out; }
	}
}
	
