/*
 *   Copyright (C) 2010 Peter Grasch <grasch@simon-listens.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "soundserver.h"
#include "soundconfig.h"
#include "soundinputclient.h"
#include "soundoutputclient.h"
#include "simonsoundinput.h"
#include "simonsoundoutput.h"

#include <QObject>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>

#include <KDebug>
#include <KLocalizedString>

SoundServer* SoundServer::instance=NULL;

/**
 * \brief Constructor
 */
SoundServer::SoundServer(QObject* parent) : QIODevice(parent)
{
	open(QIODevice::ReadWrite);
}


qint64 SoundServer::readData(char *toRead, qint64 maxLen)
{
	Q_UNUSED(toRead);
	Q_UNUSED(maxLen);
	//TODO
	/*
	if (!currentOutputClient)
	{
		kDebug() << "No current output client";
		return -1;
	}

	qint64 read = currentOutputClient->getDataProvider()->read(toRead, maxLen);

	if (read <= 0)
		deRegisterOutputClient(currentOutputClient);

	return read;
	*/
	return 0;
}


qint64 SoundServer::writeData(const char *toWrite, qint64 len)
{
	Q_UNUSED(toWrite);
	Q_UNUSED(len);
	//FIXME: split this
	/*QByteArray data;
	data.append(toWrite, len);

	//length is in ms
	qint64 length = byteSizeToLength(data.count());

	//pass data on to all registered, active clients
	
	QList<SoundInputClient*> active = inputs.activeInputClients.keys();
	foreach (SoundInputClient *c, active)
	{
		qint64 streamTime = activeInputClients.value(c)+length;
		c->process(data, streamTime);
		//update time stamp
		activeInputClients.insert(c, streamTime);
	}
	return len;*/
	return 0;
}

QString SoundServer::defaultInputDevice()
{
	QString systemDefault = QAudioDeviceInfo::defaultInputDevice().deviceName();

	foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
	{
		if (deviceInfo.deviceName() == "pulse")
		{
			systemDefault = "pulse";
			break;
		}
	}

	return systemDefault;
}

QString SoundServer::defaultOutputDevice()
{
	QString systemDefault = QAudioDeviceInfo::defaultOutputDevice().deviceName();

	foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
	{
		if (deviceInfo.deviceName() == "pulse")
		{
			systemDefault = "pulse";
			break;
		}
	}

	return systemDefault;
}



bool SoundServer::registerInputClient(SoundInputClient* client)
{
	kDebug() << "Register input client";
	if (client->isExclusive())
	{
		QHashIterator<SimonSound::DeviceConfiguration, SimonSoundInput*> i(inputs);
		while (i.hasNext())
		{
			i.next();
			SimonSoundInput *soundInput = i.value();

			//suspend all other inputs
			QHashIterator<SoundInputClient*, qint64> j(soundInput->activeInputClients());
			while (j.hasNext())
			{
				j.next();
				soundInput->suspend(j.key());
			}


		}
	}


	bool succ = true;

	SimonSound::DeviceConfiguration clientRequestedSoundConfiguration = client->deviceConfiguration();
	if (!inputs.contains(client->deviceConfiguration())) //recording not currently running
	{
		kDebug() << "No input for this particular configuration...";

		//then start recording
		succ = startRecording(clientRequestedSoundConfiguration);
		if (! (client->deviceConfiguration() == clientRequestedSoundConfiguration) )
			client->setDeviceConfiguration(clientRequestedSoundConfiguration); // found something supported that is very close
	}

	if (succ)
	{
		SimonSoundInput *input = inputs.value(clientRequestedSoundConfiguration);
		input->addActive(client);
	}

	return succ;
}

bool SoundServer::deRegisterInputClient(SoundInputClient* client)
{
	kDebug() << "Deregistering input client";

	bool success = true;

	QHashIterator<SimonSound::DeviceConfiguration, SimonSoundInput*> i(inputs);
	while (i.hasNext())
	{
		i.next();
		success = i.value()->deRegisterInputClient(client) && success;
	}

	return success;
}



bool SoundServer::startRecording(SimonSound::DeviceConfiguration& device)
{
	kDebug() << "Starting recording";

	QAudioFormat format;
	format.setFrequency(device.sampleRate());
	format.setChannels(device.channels());
	format.setSampleSize(16); // 16 bit
	format.setSampleType(QAudioFormat::SignedInt); // SignedInt currently
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setCodec("audio/pcm");

	QAudioDeviceInfo selectedInfo = QAudioDeviceInfo::defaultInputDevice();
	foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
		if (deviceInfo.deviceName() == device.name())
			selectedInfo = deviceInfo;

	if (!selectedInfo.isFormatSupported(format))
	{
		kDebug() << "Format not supported";
		emit error(i18n("Recording format not supported."));
		emit inputStateChanged(QAudio::StoppedState);
		return false;
	}

	QAudioInput *input = new QAudioInput(selectedInfo, format, this);
	connect(input, SIGNAL(stateChanged(QAudio::State)), this, SLOT(slotInputStateChanged(QAudio::State)));
	connect(input, SIGNAL(stateChanged(QAudio::State)), this, SIGNAL(inputStateChanged(QAudio::State)));

	inputs.insert(device, new SimonSoundInput(input));

	input->start(this);

	suspendPlayback();

	kDebug() << "Started audio input";
	return true;
}

void SoundServer::suspendRecording()
{
	foreach (SimonSoundInput *in, inputs.values())
		in->suspendInput();
}

void SoundServer::resumeRecording()
{
	foreach (SimonSoundInput *in, inputs.values())
		in->resumeInput();
}

void SoundServer::suspendPlayback()
{
	foreach (SimonSoundOutput *out, outputs.values())
		out->suspendOutput();
}

void SoundServer::resumePlayback()
{
	foreach (SimonSoundOutput *out, outputs.values())
		out->resumeOutput();
}




bool SoundServer::registerOutputClient(SoundOutputClient* client)
{
	kDebug() << "Register output client";
	//FIXME
	Q_UNUSED(client);
	/*
	if (currentOutputClient != NULL)
		suspendedOutputClients.append(currentOutputClient);

	currentOutputClient = client;

	bool succ = true;


	if (!outputs.contains(client->deviceConfiguration())) //playback not currently running
	{
		//then start playback
		SimonSound::DeviceConfiguration dev = client->deviceConfiguration();
		succ = startPlayback(dev);
		if (! (client->deviceConfiguration() == dev) )
			client->setDeviceConfiguration(dev); // found something supported that is very close
	}
	return succ;
	*/

	return true;
}

bool SoundServer::deRegisterOutputClient(SoundOutputClient* client)
{
	//FIXME
	Q_UNUSED(client);
	/*
	kDebug() << "Deregister output client";
	client->finish();
	if (client != currentOutputClient)
	{
		//wasn't active anyways
		suspendedOutputClients.removeAll(client);
		return true;
	}

	

	if (suspendedOutputClients.isEmpty())
	{
		currentOutputClient = NULL;
		kDebug() << "No active clients available... Stopping playback";
		return stopPlayback();
	}

	currentOutputClient = suspendedOutputClients.takeAt(0);
	return true;
	*/

	return true;
}

bool SoundServer::startPlayback(SimonSound::DeviceConfiguration& device)
{
	kDebug() << "Starting playback...";

	kDebug() << "Suspending recording during playback";
	suspendRecording();

	QAudioFormat format;
	format.setFrequency(device.sampleRate());
	format.setChannels(device.channels());
	format.setSampleSize(16); // 16 bit
	format.setSampleType(QAudioFormat::SignedInt); // SignedInt currently
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setCodec("audio/pcm");

	QAudioDeviceInfo selectedInfo = QAudioDeviceInfo::defaultOutputDevice();
	foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
		if (deviceInfo.deviceName() == device.name())
			selectedInfo = deviceInfo;

	if (!selectedInfo.isFormatSupported(format))
	{
		kDebug() << "Format not supported; Trying something similar";
		format = selectedInfo.nearestFormat(format);
	}

	if(format.sampleSize() != 16) {
		kDebug() << "Sample size is not 16 bit. Aborting.";
		emit error(i18n("Sample size not equal to 16 bit."));
		emit outputStateChanged(QAudio::StoppedState);
		return false;
	}
	
	device.setChannels(format.channels());
	device.setSampleRate(format.frequency());

	kDebug() << "Using device: " << selectedInfo.deviceName();

	QAudioOutput *output = new QAudioOutput(selectedInfo, format, this);
	connect(output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(slotOutputStateChanged(QAudio::State)));
	connect(output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(outputStateChanged(QAudio::State)));
	output->start(this);

	outputs.insert(device, new SimonSoundOutput(output));

	kDebug() << "Started audio output";
	return true;
}


qint64 SoundServer::byteSizeToLength(qint64 bytes, SimonSound::DeviceConfiguration device)
{
	return bytes / (device.channels() * 2 /* 16 bit */ * ((float)device.sampleRate() / 1000.0f));
}

qint64 SoundServer::lengthToByteSize(qint64 length, SimonSound::DeviceConfiguration device)
{
	return length * (device.channels() * 2 /* 16 bit */ * ((float)device.sampleRate() / 1000.0f));
}


void SoundServer::slotInputStateChanged(QAudio::State state)
{
	kDebug() << "Input state changed: " << state;
	//FIXME

	/*
	if (!input) return;

	if (state == QAudio::StoppedState)
	{
		switch (input->error())
		{
			case QAudio::NoError:
				kDebug() << "Input stopped without error";
				break;
			case QAudio::OpenError:
				emit error(i18n("Failed to open the input audio device.\n\nPlease check your sound configuration."));
				break;

			case QAudio::IOError:
				emit error(i18n("An error occured while reading data from the audio device."));
				break;

			case QAudio::UnderrunError:
				emit error(i18n("Buffer underrun when processing the sound data."));
				break;

			case QAudio::FatalError:
				emit error(i18n("A fatal error occured during recording."));
				break;
		}
	}
	*/
}

void SoundServer::slotOutputStateChanged(QAudio::State state)
{
	kDebug() << "Output state changed: " << state;

	//FIXME
	/*
	if (state == QAudio::StoppedState)
	{
		switch (output->error())
		{
			case QAudio::NoError:
				kDebug() << "Output stopped without error";
				break;
			case QAudio::OpenError:
				emit error(i18n("Failed to open the audio device.\n\nPlease check your sound configuration."));
				break;

			case QAudio::IOError:
				emit error(i18n("An error occured while writing data to the audio device."));
				break;

			case QAudio::UnderrunError:
				kWarning() << i18n("Buffer underrun when processing the sound data.");
				break;

			case QAudio::FatalError:
				emit error(i18n("A fatal error occured during playback."));
				break;
		}
	}
	*/
}

bool SoundServer::reinitializeDevices()
{
	kDebug() << "Reinitialize devices...";
	bool succ = true;

	//TODO
	
	//succ = stopPlayback() && succ;
	//succ = startPlayback() && succ;

	//succ = stopRecording() && succ;
	//succ = startRecording() && succ;

	return succ;
}

int SoundServer::getInputDeviceCount()
{
	return SoundConfiguration::soundInputDevices().count();
}

int SoundServer::getOutputDeviceCount()
{
	return SoundConfiguration::soundOutputDevices().count();
}

bool SoundServer::getDefaultToPowerTraining()
{
	return SoundConfiguration::defaultToPowerTraining();
}

int SoundServer::getLevelThreshold()
{
	return SoundConfiguration::level();
}

int SoundServer::getHeadMargin()
{
	return SoundConfiguration::headMargin();
}

int SoundServer::getTailMargin()
{
	return SoundConfiguration::tailMargin();
}

int SoundServer::getShortSampleCutoff()
{
	return SoundConfiguration::skipSamples();
}


/**
 * \brief Destructor
 */
SoundServer::~SoundServer()
{
}



