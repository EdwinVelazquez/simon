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

#ifndef SIMON_SYNCHRONISATIONMANAGER_H_B6B7076C3F184C0DAEBC11F4C2F160E4
#define SIMON_SYNCHRONISATIONMANAGER_H_B6B7076C3F184C0DAEBC11F4C2F160E4

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QMap>

class Model;
class LanguageDescriptionContainer;
class TrainingContainer;

class SynchronisationManager : public QObject
{
  Q_OBJECT

    private:
    QString username;
    QString srcContainerTempPath;
    bool removeAllFiles(const QString& dir);
    bool removeDirectory(const QString& dir);
    bool cleanTemp();

    QString getLatestPath(const QMap<QDateTime, QString>& models);

    QMap<QDateTime, QString> getTrainingDatas();
    QMap<QDateTime, QString> getLanguageDescriptions();
    QMap<QDateTime, QString> getSelectedScenarioLists();

    QString getLatestLanguageDescriptionPath();
    QString getLatestTrainingPath();
    QString getLatestSelectedScenarioListPath();

    QStringList getAllScenarios();
    QString getLatestScenarioPath(const QString& id);

    void touchTempModel();

  public:
    explicit SynchronisationManager(const QString& username, QObject *parent=0);

    QMap<QDateTime, QString> getModels();

    Model* getActiveModel();
    bool hasActiveModel();
    QDateTime getActiveModelDate();
    void setActiveModelSampleRate(int activeModelSampleRate);
    bool storeActiveModel(const QDateTime& changedDate, qint32 sampleRate, const QByteArray& container);

    QDateTime getBaseModelDate();
    Model* getBaseModel();
    QString getBaseModelPath();
    int getBaseModelType();
    bool storeBaseModel(const QDateTime& changedDate, int baseModelType, const QByteArray& container);

    QDateTime getModelSrcDate();
    QDateTime getCompileModelSrcDate();
    bool hasModelSrc();

    QDateTime getLanguageDescriptionDate(QString path=QString());
    bool hasLanguageDescription(const QString& modelPath=QString());
    LanguageDescriptionContainer* getLanguageDescription();
    bool storeLanguageDescription(const QDateTime& changedDate, const QByteArray& shadowVocab,
      const QByteArray& languageProfile=QByteArray());

    QDateTime getTrainingDate(QString path=QString());
    bool hasTraining(const QString& modelPath=QString());
    TrainingContainer* getTraining();
    bool storeTraining(const QDateTime& changedDate, qint32 sampleRate, const QByteArray& prompts);

    QByteArray getScenario(const QString& scenarioId);
    bool storeScenario(const QString& id, const QByteArray& scenario);
    QDateTime localScenarioDate(const QString& scenarioId);
    QDateTime scenarioDate(const QString& path);

    void deletedScenarios(const QStringList& ids, const QList<QDateTime>& scenarioTimes);

    bool hasScenarioRc(const QString& modelPath=QString());
    QDateTime selectedScenariosDate();
    QDateTime getSelectedScenarioListModifiedDateFromPath(const QString& path);
    bool storeSelectedScenarioList(const QDateTime& modifiedDate, const QStringList& scenarioIds);

    QStringList getAvailableSamples();
    QByteArray getSample(const QString& sampleName);
    bool storeSample(const QString& name, const QByteArray& sample);

    QStringList getScenarioPaths();
    QString getPromptsPath();

    bool startSynchronisation();
    bool abort();
    bool commit();
    bool removeExcessModelBackups();

    void modelCompiled(const QString& path);
    bool createTrainingData(const QString& dest);
    bool copyTrainingData(const QString& source, const QString& dest);
    bool copyLanguageDescription(const QString& source, const QString& dest);
    bool copyScenarioRc(const QString& source, const QString& dest);
    bool copyScenarios(const QString& source, const QString& dest, bool touchAccessTime=false);
    bool switchToModel(const QDateTime& modelDate);

    QStringList getAllScenarioIds();

    QStringList getLatestSelectedScenarioList();
    ~SynchronisationManager();

};
#endif
