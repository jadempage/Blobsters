#include "audio.h"



AudioGeneratorWAV* wav;
AudioFileSourcePROGMEM* file;
AudioOutputI2S* out;

void audio::playSound(soundContext sc) {

	switch (sc) {
		case scButtonA: file = new AudioFileSourcePROGMEM(se_BtnA, sizeof(se_BtnA)); break;
		case scButtonB: file = new AudioFileSourcePROGMEM(se_BtnB, sizeof(se_BtnB)); break;
		case scButtonC: file = new AudioFileSourcePROGMEM(se_BtnC, sizeof(se_BtnC)); break;
		case scWinGame: file = new AudioFileSourcePROGMEM(se_GameWin, sizeof(se_GameWin)); break;
		case scLoseGame: file = new AudioFileSourcePROGMEM(se_GameLose, sizeof(se_GameLose)); break;
		case scDrawCard: file = new AudioFileSourcePROGMEM(se_CardPlace, sizeof(se_CardPlace)); break;
		case scBallHit: file = new AudioFileSourcePROGMEM(se_BallHit, sizeof(se_BallHit)); break;
		case scBallScore: file = new AudioFileSourcePROGMEM(se_BallScore, sizeof(se_BallScore)); break;
		case scBombExplode: file = new AudioFileSourcePROGMEM(se_BombExplode, sizeof(se_BombExplode)); break;
		case scAppleCatch: file = new AudioFileSourcePROGMEM(se_AppleCatch,  sizeof(se_AppleCatch)); break;
	}
	/*file = new AudioFileSourcePROGMEM(af_btnPress, sizeof(af_btnPress));*/
	out = new AudioOutputI2S(0, 1); // Output to builtInDAC
	out->SetOutputModeMono(true);
	wav = new AudioGeneratorWAV();
	wav->begin(file, out);
	wavloop(); 
	}

void audio::wavloop()
{
		if (!wav) {
			return;
		}
		//Serial.write(audioRunning);
		if (wav->isRunning()) {
			if (!wav->loop()) {
				wav->stop();
				delete wav;
				delete file;
				delete out;
				wav = NULL;
			}
		}
		//else {
		//	delay(1000);
}

void audio::forceStop() {
	//Serial.write(audioRunning);
	if (!wav) {
		return;
	}
	if (wav->isRunning()) {
		wav->stop();
		if (wav) { delete wav; }
		if (file) { delete file; }
		if (out) { delete out; }
		wav = NULL; 
	}
}
	
void audio::waitForFinish() {
	if (wav->isRunning()) {
		if (wav->loop()) {
			waitForFinish(); 
		}
	}
}