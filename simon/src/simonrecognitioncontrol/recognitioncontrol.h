/*
 *   Copyright (C) 2008 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_RECOGNITIONCONTROL_H_405E2F7D85464072A6740F08D0459935
#define SIMON_RECOGNITIONCONTROL_H_405E2F7D85464072A6740F08D0459935

#include "recognitioncontrol_export.h"
#include <simonrecognitionresult/recognitionresult.h>
#include <simondstreamer/simonsender.h>
#include <QStringList>
#include <QMutex>

class ThreadedSSLSocket;
class QTimer;
class QProcess;
class Operation;

const qint8 protocolVersion=5;

class QDateTime;
class SimondStreamer;

/**
 *	@class RecognitionControl
 *	@brief Provides the methods and emits the needed signals to work with simond
 *
 *	@version 0.1
 *	@date 23.01.2006
 *	@author Peter Grasch
 */
class RECOGNITIONCONTROL_EXPORT RecognitionControl : public SimonSender
{
  Q_OBJECT

  public:
    RecognitionControl();

    ~RecognitionControl();

    static RecognitionControl* getInstance();

    enum RecognitionStatus
    {
      Ready=0,
      Started=1,
      Paused=2,
      Resumed=3,
      Stopped=4
    };

    bool getAvailableModels();
    bool switchToModel(const QDateTime& model);
    bool isConnected();

    bool pauseRecognition();
    bool resumeRecognition();

  private:
    static RecognitionControl *instance;
    QProcess *localSimond;
    bool blockAutoStart;

    SimondStreamer* simondStreamer;

    QByteArray stillToProcess;
    QStringList missingScenarios;
    bool m_loggedIn;
    bool recognitionReady;
    ThreadedSSLSocket *socket;

    Operation *synchronisationOperation;
    Operation *modelCompilationOperation;
    Operation* createModelCompilationOperation();

    QTimer *timeoutWatcher;

    QMutex sendMutex;
    QMutex receiveMutex;
    bool currentlyReading;

    QStringList serverConnectionsToTry;
    QStringList serverConnectionErrors;

    void sampleNotAvailable(const QString&);
    void wordUndefined(const QString&);
    void classUndefined(const QString&);
    void phonemeUndefined(const QString&);
    void displayCompilationProtocol(const QString& protocol);

    bool startSimondStreamer();
    bool stopSimondStreamer();
    
    void send(qint32 requestId, const QByteArray& data, bool includeLength=true);

    bool storeBaseModel(const QDateTime& changedTime, int baseModelType,
      const QByteArray& container);
    bool storeLanguageDescription(const QDateTime& changedTime, QByteArray& shadowVocab,
      const QByteArray& languageProfile=QByteArray());
    bool storeTraining(const QDateTime& changedTime, qint32 sampleRate,
      const QByteArray& prompts);
    bool storeActiveModel(const QDateTime& changedTime, qint32 sampleRate, const QByteArray& container);
    bool storeSample(const QString& name, const QByteArray& sample);

  signals:
    void connected();
    void disconnected();

    void connectionError(const QString& errStr);
    void simondSystemError(const QString& errStr);
    void synchronisationError(const QString &err);
    void synchroniationCompleted();
    void recognitionError(const QString &err, const QString& protocol);
    void compilationError(const QString &err, const QString& protocol);

    void simondSystemWarning(const QString&);
    void synchronisationWarning(const QString&);
    void recognitionWarning(const QString&);
    void compilationWarning(const QString&);

    void status(const QString&, int progNow=-1, int progMax=0);
    void progress(int now, int max=-1);

    void loggedIn();

    void recognitionStatusChanged(RecognitionControl::RecognitionStatus);
    void recognised(RecognitionResultList recognitionResults);

    void modelsAvailable(const QList<QDateTime>& models);

  public slots:
    void startup();

    void disconnectFromServer();
    void startConnecting();

    bool startRecognition();
    bool stopRecognition();

    void fetchCompilationProtocol();
    void askStartSynchronisation();
    void startSynchronisation();
    
  public:
    void setBlockAutoStart(bool block);

  private slots:
    void actOnAutoConnect();
    void slotDisconnected();
    void sendRequest (qint32 request);
    void login();
    void connectedTo();
    void errorOccured();
    void connectTo( QString server="127.0.0.1", quint16 port=4444 );
    void connectToNext();
    void timeoutReached();
    void messageReceived();
    bool sendActiveModel();
    void sendActiveModelSampleRate();

    void sendScenariosToDelete();

    bool sendBaseModel();

    void sendSelectedScenarioList();

    void sendScenario(QString scenarioId);

    void sendDeactivatedScenarioList();
    void sendDeactivatedSampleGroups();
    void sendDeactivatedSampleGroups(const QStringList& sampleGroups);

    void sendLanguageDescription();

    void sendTraining();

    void sendSample(QString sampleName);

    void startSampleToRecognizePrivate(qint8 id, qint8 channels, qint32 sampleRate);
    void sendSampleToRecognizePrivate(qint8 id, const QByteArray& data);
    void recognizeSamplePrivate(qint8 id);

    void synchronisationComplete();
    void synchronisationDone();

    void abortModelCompilation();

    void streamStarted();
    void streamStopped();

    void startPrivateSimond();

};
#endif
