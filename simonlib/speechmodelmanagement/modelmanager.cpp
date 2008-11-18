/*
 *   Copyright (C) 2008 Peter Grasch <grasch@simon-listens.org>
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

#include "modelmanager.h"
#include "grammarmanager.h"
#include "wordlistmanager.h"
#include "trainingmanager.h"
#include "speechmodelmanagementconfiguration.h"

#include <speechmodelbase/model.h>
#include <speechmodelbase/wordlistcontainer.h>
#include <speechmodelbase/grammarcontainer.h>
#include <speechmodelbase/languagedescriptioncontainer.h>
#include <speechmodelbase/trainingcontainer.h>

#include <KStandardDirs>
#include <QFile>
#include <QFileInfo>
#include <QBuffer>
#include <QDir>


ModelManager::ModelManager()
{
	connect (WordListManager::getInstance(), SIGNAL(wordlistChanged()), 
		  this, SIGNAL(modelChanged()));

	connect (WordListManager::getInstance(), SIGNAL(shadowListChanged()), 
		  this, SIGNAL(modelChanged()));
	
	connect (TrainingManager::getInstance(), SIGNAL(trainingDataChanged()),
		  this, SIGNAL(modelChanged()));
	
	connect (TrainingManager::getInstance(), SIGNAL(trainingSettingsChanged()),
		  this, SIGNAL(modelChanged()));
	
	connect (GrammarManager::getInstance(), SIGNAL(structuresChanged()), 
		  this, SIGNAL(modelChanged()));
}

Model* ModelManager::createActiveContainer()
{
	int modelSampleRate=SpeechModelManagementConfiguration::modelSampleRate();
	
	QFile hmmDefs(KStandardDirs::locate("appdata", "model/hmmdefs"));
	QFile tiedList(KStandardDirs::locate("appdata", "model/tiedlist"));
	
	QFile dict(KStandardDirs::locate("appdata", "model/model.dict"));
	QFile dfa(KStandardDirs::locate("appdata", "model/model.dfa"));
	
	if ((!hmmDefs.open(QIODevice::ReadOnly)) || (!tiedList.open(QIODevice::ReadOnly))
		|| (!dict.open(QIODevice::ReadOnly))
		|| (!dfa.open(QIODevice::ReadOnly)))
		return 0;
	
	return new Model(modelSampleRate, hmmDefs.readAll(), tiedList.readAll(), dict.readAll(), dfa.readAll());
}

int ModelManager::getActiveModelSampleRate()
{
	return SpeechModelManagementConfiguration::modelSampleRate();
}

QDateTime ModelManager::getActiveContainerModifiedTime()
{
	if (!hasActiveContainer()) return QDateTime();

	KConfig config( KStandardDirs::locateLocal("appdata", "model/activemodelrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	return cGroup.readEntry("Date", QDateTime());
}


bool ModelManager::storeActiveModel(const QDateTime& changedTime, int sampleRate, const QByteArray& hmmDefs,
			const QByteArray& tiedList, const QByteArray& dict, const QByteArray& dfa)
{
	KConfig config( KStandardDirs::locateLocal("appdata", "model/activemodelrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	cGroup.writeEntry("Date", changedTime);
	config.sync();
	
	SpeechModelManagementConfiguration::setModelSampleRate(sampleRate);
	
	QFile hmmDefsFile(KStandardDirs::locateLocal("appdata", "model/hmmdefs"));
	QFile tiedlistFile(KStandardDirs::locateLocal("appdata", "model/tiedlist"));
	QFile dictFile(KStandardDirs::locateLocal("appdata", "model/model.dict"));
	QFile dfaFile(KStandardDirs::locateLocal("appdata", "model/model.dfa"));
	
	if (!hmmDefsFile.open(QIODevice::WriteOnly)
		|| !tiedlistFile.open(QIODevice::WriteOnly)
		|| !dictFile.open(QIODevice::WriteOnly)
		|| !dfaFile.open(QIODevice::WriteOnly))
		return false;
	
	hmmDefsFile.write(hmmDefs);
	tiedlistFile.write(tiedList);
	dictFile.write(dict);
	dfaFile.write(dfa);
	
	hmmDefsFile.close();
	tiedlistFile.close();
	dictFile.close();
	dfaFile.close();
	
	return true;
}

QByteArray ModelManager::getSample(const QString& sampleName)
{
	QFile f(SpeechModelManagementConfiguration::modelTrainingsDataPath().path()+"/"+sampleName.toUtf8());
	if (!f.open(QIODevice::ReadOnly)) return QByteArray();
	return f.readAll();
}


WordListContainer* ModelManager::getWordListContainer()
{
	WordList *simpleVocabList = WordListManager::getInstance()->getSimpleVocab();
	WordListManager::getInstance()->saveWordList(simpleVocabList, 
						      KStandardDirs::locateLocal("tmp", "simplevocab"));
	delete simpleVocabList;

	QFile simpleVocab(KStandardDirs::locateLocal("tmp", "simplevocab"));
	
	QFile activeVocab(KStandardDirs::locate("appdata", "model/model.voca"));
	QFile activeLexicon(KStandardDirs::locate("appdata", "model/lexicon"));
	
	if ((!simpleVocab.open(QIODevice::ReadOnly))
		|| (!activeVocab.open(QIODevice::ReadOnly))
		|| (!activeLexicon.open(QIODevice::ReadOnly)))
		return 0;

	return new WordListContainer(simpleVocab.readAll(), activeVocab.readAll(), activeLexicon.readAll());
}

QDateTime ModelManager::getWordListModifiedTime()
{
	if (!hasWordList()) return QDateTime();
	
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	/* grammar might effect the simpleVocab */
	return qMax(cGroup.readEntry("WordListDate", QDateTime()), cGroup.readEntry("GrammarDate", QDateTime()));
}


bool ModelManager::storeWordList(const QDateTime& changedTime, const QByteArray& simpleVocab,
			const QByteArray& activeVocab, const QByteArray& activeLexicon)
{
	if (!WordListManager::getInstance()->refreshWordListFiles(simpleVocab, activeVocab, activeLexicon))
		return false;
	
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	cGroup.writeEntry("WordListDate", changedTime);
	config.sync();
	return true;
}

GrammarContainer* ModelManager::getGrammarContainer()
{
	QFile grammar(KStandardDirs::locate("appdata", "model/model.grammar"));
	if (!grammar.open(QIODevice::ReadOnly))
		return 0;

	return new GrammarContainer(grammar.readAll());
}

QDateTime ModelManager::getGrammarModifiedTime()
{
	if (!hasGrammar()) return QDateTime();
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	return cGroup.readEntry("GrammarDate", QDateTime());
}


bool ModelManager::storeGrammar(const QDateTime& changedTime, const QByteArray& grammarStructures)
{
	if (!GrammarManager::getInstance()->refreshFiles(grammarStructures)) return false;
	
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	cGroup.writeEntry("GrammarDate", changedTime);
	config.sync();
	return true;
}


LanguageDescriptionContainer* ModelManager::getLanguageDescriptionContainer()
{
	QFile treeHed(KStandardDirs::locate("appdata", "model/tree1.hed"));
	QFile shadowVocab(KStandardDirs::locate("appdata", "model/shadow.voca"));

	if ((!treeHed.open(QIODevice::ReadOnly))
		|| (!shadowVocab.open(QIODevice::ReadOnly)))
		return 0;

	return new LanguageDescriptionContainer(shadowVocab.readAll(), treeHed.readAll());
}

QDateTime ModelManager::getLanguageDescriptionModifiedTime()
{
	if (!hasLanguageDescription()) return QDateTime();
	
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	return cGroup.readEntry("LanguageDescriptionDate", QDateTime());
}



bool ModelManager::storeLanguageDescription(const QDateTime& changedTime, const QByteArray& shadowVocab, 
				        const QByteArray& treeHed)
{
	if (!WordListManager::getInstance()->refreshShadowListFiles(shadowVocab)) return false;
	
	QFile treeHedF(KStandardDirs::locateLocal("appdata", "model/tree1.hed"));
	if (!treeHedF.open(QIODevice::WriteOnly))
		return false;
	
	treeHedF.write(treeHed);
	treeHedF.close();
	
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	cGroup.writeEntry("LanguageDescriptionDate", changedTime);
	config.sync();
	return true;
}


TrainingContainer* ModelManager::getTrainingContainer()
{
	int modelSampleRate=SpeechModelManagementConfiguration::modelSampleRate();
	
//	TrainingManager::getInstance()->writePromptsFile(
//			TrainingManager::getInstance()->getPrompts(), 
//			KStandardDirs::locateLocal("tmp", "transferprompts"));

	QFile wavConfig(KStandardDirs::locate("appdata", "model/wav_config"));
	QFile prompts(KStandardDirs::locate("appdata", "model/prompts"));
	

	if ((!wavConfig.open(QIODevice::ReadOnly)) || (!prompts.open(QIODevice::ReadOnly)))
		return 0;

	return new TrainingContainer(modelSampleRate, wavConfig.readAll(),
				  prompts.readAll());
}

QDateTime ModelManager::getTrainingModifiedTime()
{
	if (!hasTraining()) return QDateTime();

	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	return cGroup.readEntry("TrainingDate", QDateTime());
}

bool ModelManager::storeTraining(const QDateTime& changedTime, int sampleRate, const QByteArray& wavConfig,
					const QByteArray& prompts)
{
	if (!TrainingManager::getInstance()->refreshTraining(sampleRate, prompts))
		return false;
	
	QFile wavConfigF(KStandardDirs::locateLocal("appdata", "model/wav_config"));
	if (!wavConfigF.open(QIODevice::WriteOnly))
		return false;
	
	wavConfigF.write(wavConfig);
	wavConfigF.close();
	
	
	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	cGroup.writeEntry("TrainingDate", changedTime);
	config.sync();
	return true;
}

void ModelManager::buildMissingSamplesList()
{
	QStringList newList = TrainingManager::getInstance()->getPrompts()->keys();
	QDir samplesDir(SpeechModelManagementConfiguration::modelTrainingsDataPath().path());
	QStringList oldList = samplesDir.entryList(QStringList() << "*.wav");
	
	foreach (QString fileName, newList)
	{
		if ((!oldList.contains(fileName)) && (!this->missingFiles.contains(fileName)))
			missingFiles << fileName;
	}
}


bool ModelManager::storeSample(const QByteArray& sample)
{
	if (missingFiles.isEmpty()) return false;

	QString dirPath = SpeechModelManagementConfiguration::modelTrainingsDataPath().path()+'/';

	QFile f(dirPath+missingFiles.at(0)+".wav");
	if (!f.open(QIODevice::WriteOnly)) return false;

	f.write(sample);
	f.close();

	missingFiles.removeAt(0);
	return true;
}

QString ModelManager::missingSample()
{
	if (missingFiles.isEmpty()) return QString();

	return missingFiles.at(0);
}

bool ModelManager::hasWordList()
{
	return (QFile::exists(KStandardDirs::locate("appdata", "model/model.voca")) && 
		  QFile::exists(KStandardDirs::locate("appdata", "model/lexicon")));
}

bool ModelManager::hasTraining()
{
	return (QFile::exists(KStandardDirs::locate("appdata", "model/wav_config")) && 
		  QFile::exists(KStandardDirs::locate("appdata", "model/prompts")));
}

bool ModelManager::hasGrammar()
{
	return QFile::exists(KStandardDirs::locate("appdata", "model/model.grammar"));
}

bool ModelManager::hasLanguageDescription()
{
	return (QFile::exists(KStandardDirs::locate("appdata", "model/tree1.hed")) && 
		  QFile::exists(KStandardDirs::locate("appdata", "model/shadow.voca")));
}

bool ModelManager::hasActiveContainer()
{
	return (QFile::exists(KStandardDirs::locate("appdata", "model/hmmdefs")) && 
		  QFile::exists(KStandardDirs::locate("appdata", "model/tiedlist")) &&
		  QFile::exists(KStandardDirs::locate("appdata", "model/model.dict")) && 
		  QFile::exists(KStandardDirs::locate("appdata", "model/model.dfa")));
}


QDateTime ModelManager::getSrcContainerModifiedTime()
{
	if (!hasWordList() || !hasTraining() || !hasGrammar() || !hasLanguageDescription())
		return QDateTime();

	KConfig config( KStandardDirs::locateLocal("appdata", "model/modelsrcrc"), KConfig::SimpleConfig );
	KConfigGroup cGroup(&config, "");
	QDateTime maxModifiedDate = qMax(cGroup.readEntry("WordListDate", QDateTime()),
					 cGroup.readEntry("GrammarDate", QDateTime()));
	maxModifiedDate = qMax(maxModifiedDate, cGroup.readEntry("LanguageDescriptionDate", QDateTime()));
	return qMax(maxModifiedDate, cGroup.readEntry("TrainingDate", QDateTime()));
}