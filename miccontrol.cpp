//
// C++ Implementation: miccontrol
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "miccontrol.h"


/**
 *	@brief Constructor
 *	
 *	Creates a new Soundbackend depending on the arch.
 *	
 *	@author Peter Grasch
 */
MicControl::MicControl()
{
#ifdef linux
	soundbackend = new ALSABackend();
#endif
}


/**
 *	@brief Prepares the mic for recording
 *	
 *	Calls - depending on the arch. all the needed calls to get
 *	the sound card ready for recording
 *	It also catches all possible errors and tells the user about it
 *	
 *	@author Peter Grasch
 *	@param short channels
 *	Number of channels (1=mono, 2=stereo,...)
 *	@param int samplerate
 *	Samplerate in Hz (usually 44100)
 *	@return bool
 *	Returns wether the mic was successfully prepared
 */
bool MicControl::initializeMic(short channels, int samplerate)
{
#ifdef linux
	ALSABackend *abackend = dynamic_cast<ALSABackend*>(soundbackend);
	if (!(abackend)) return false;
	
	if (!(abackend->openDevice("default")))
	{
			SimonInfo::showMessage("Konnte Soundkarte nicht �ffnen", 6000);
			return false;
	}
	if (!(abackend->setInterleaved(true)))
	{
		SimonInfo::showMessage("Konnte Soundkarte nicht auf interleaved setzen", 6000);
		return false;
	}
	if (!(abackend->setSampleRate(samplerate)))
	{
		SimonInfo::showMessage("Konnte Samplerate nicht setzen", 6000);
		return false;
	}
	
	if (!(abackend->setChannels(channels)))
	{
		SimonInfo::showMessage("Setzen der Kan�le fehlgeschlagen", 6000);
		return false;
	}
	
	if (!(abackend->prepareDevice()))
	{
		SimonInfo::showMessage("Konnte das Ger�t nicht vorbereiten", 6000);
		return false;
	}
	
#endif //linux
}


/**
 *	@brief Captures data from the device
 *	
 *	Records data from a prepared the device
 *	
 *	@author Peter Grasch
 *	@param int count
 *	Number of frames
 *	@param short buffersize
 *	Buffersize per frame
 *	@return short**
 *	Twodimensional array of the frequencies
 *	@see initializeMic()
 */
short** MicControl::capture (int count, short buffersize)
{
	
#ifdef linux
	ALSABackend *abackend = dynamic_cast<ALSABackend*>(soundbackend);
	if (!(abackend)) return false;
	
	short **buffer;
	
	buffer = abackend->readData(count,buffersize);
	if (!(buffer))
	{
		SimonInfo::showMessage("Aufnehmen fehlgeschlagen", 6000);
	}
	return buffer;
#endif //linux
}


/**
 *	@brief Closes the mic
 *	
 *	Closes the handles and opens the lock
 *	
 *	@author Peter Grasch
 *	@return bool
 *	Returns wether the mic was successfully closed
 */
bool MicControl::closeMic()
{
#ifdef linux
	ALSABackend *abackend = dynamic_cast<ALSABackend*>(soundbackend);
	if (!(abackend)) return false;
	
	if (!(abackend->closeDevice()))
	{
		SimonInfo::showMessage("Konnte Soundkarte nicht schlie�en", 6000);
		return false;
	}
#endif //linux
}


/**
 *	@brief Returns the current volume in percent
 *	
 *	@author Peter Grasch
 *	@return int
 *	volume in percent
*/
int MicControl::getVolume()
{
	
}

/**
 *	@brief Sets the volume in percent
 *	
 *	@author Peter Grasch
 *	@param int percent
 *	volume in percent
*/
void MicControl::setVolume(int percent)
{
	
}


/**
 *	@brief Destructor
 *	
 *	@author Peter Grasch
*/
MicControl::~MicControl()
{
}
