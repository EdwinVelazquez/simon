//
// C++ Implementation: firstrunwizard
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QWizardPage>
#include "firstrunwizard.h"
#include "externalprogrammanager.h"
#include "systemwidgetpage.h"
#include "selectlanguagemodelsourcepage.h"

#include "firstrunmodelsettings.h"
#include "firstruncreatedictionarypage.h"

#include "firstrunimportdictselectsourcepage.h"
#include "firstrunimportbomppage.h"
#include "importdictwiktionarypage.h"
#include "importdictworkingpage.h"


#include "importgrammarselectfilespage.h"
#include "firstrunimportgrammarworkingpage.h"

#include "grammarmanager.h"
#include "grammarsettings.h"

#include "wordlistmanager.h"
#include "trainingmanager.h"

#include "soundsettings.h"
#include "networksettings.h"
#include "passwordsettings.h"


FirstRunWizard::FirstRunWizard(AddWordView *addWordView, QWidget* parent): SimonWizard(parent)
{
	this->wordListManager=0;
	this->trainingManager=0;

	setWindowTitle(tr("simon Erstkonfiguration"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/banners/firstrun.png"));
	addPage(createIntroPage());
	addPage(createCheckList());
	addPage(createExternalProgramsPage());
	addPage(createLanguageModelDescription());
	addPage(createLanguageModelSelectSource());
	addPage(createNewModelDescription());
	addPage(createModelSettings());

	addPage(createCreateDictionaryPage());

	addPage(createImportDictSelectTypePage());
	addPage(createImportDictBOMPPage());
	addPage(createImportDictWiktionaryPage());
	addPage(createImportDictWorkingPage());

	addPage(createGrammarDescriptionPage());
	addPage(createSelectFilesPage());
	addPage(createGrammarWorkingPage());
	addPage(createGrammarSettings());

	addPage(createSoundSettingsPage());

	addPage(createPasswordDescriptionPage());
	addPage(createPasswordSettingsPage());

	addPage(createJuliusdDescriptionPage());
	addPage(createJuliusdSettingsPage());

	addPage(createFinishedPage());
    
    this->addWordView = addWordView;
}

void FirstRunWizard::setWordListManager(WordListManager *wordListManager)
{
	if (this->wordListManager) delete this->wordListManager;

	this->wordListManager = wordListManager;
	this->firstRunImportGrammarWorkingPage->setWordListManager(wordListManager);
	connect(importDictWorkingPage, SIGNAL(wordListImported(WordList*)), this, SLOT(importDict(WordList*)));

	this->grammarManager = new GrammarManager(wordListManager);
	GrammarSettings *grammarSettings = new GrammarSettings(grammarSettingsPage, grammarManager);
	connect(firstRunImportGrammarWorkingPage, SIGNAL(grammarCreated(QStringList)), 
		grammarSettings, SLOT(mergeGrammar(QStringList)));

	grammarSettingsPage->setChild(grammarSettings);
}

void FirstRunWizard::mergeGrammarStructure(QStringList structures)
{
// 	QStringList newStructs = grammarManager->getAllStructures();
// 	for (int i=0; i < newStructs.count(); i++)
// 		if (!structures.contains(newStructs[i]))
// 			structures << newStructs[i];
// 	grammarSettingsPage->mergeGrammar(structures);
}

void FirstRunWizard::importDict(WordList *words)
{
	if (this->wordListManager)
	{
		this->wordListManager->addWords(words, true, true);
	}
}

void FirstRunWizard::setTrainingManager(TrainingManager *trainingManager)
{
	if (this->trainingManager) delete this->trainingManager;

	this->trainingManager = trainingManager;
}

QWizardPage* FirstRunWizard::createCreateDictionaryPage()
{
	FirstRunCreateDictionaryPage *page = new FirstRunCreateDictionaryPage(addWordView, this);
	connect(page, SIGNAL(wordListManagerCreated(WordListManager*)), this, SLOT(setWordListManager(WordListManager*)));
	connect(page, SIGNAL(trainingManagerCreated(TrainingManager*)), this, SLOT(setTrainingManager(TrainingManager*)));
	connect(page, SIGNAL(done()), this, SLOT(next()));
	return page;
}


QWizardPage* FirstRunWizard::createImportDictSelectTypePage()
{
	return (QWizardPage*) new FirstRunImportDictSelectSourcePage(this);
}

QWizardPage* FirstRunWizard::createImportDictBOMPPage()
{
	return (QWizardPage*) new FirstRunImportBOMPPage(this);
}

QWizardPage* FirstRunWizard::createImportDictWiktionaryPage()
{
	return (QWizardPage*) new ImportDictWiktionaryPage(this);
}

QWizardPage* FirstRunWizard::createImportDictWorkingPage()
{
	this->importDictWorkingPage = new ImportDictWorkingPage(this);
	return (QWizardPage*) importDictWorkingPage;
}


QWizardPage* FirstRunWizard::createGrammarDescriptionPage()
{
	QWizardPage *description = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(description);
	QLabel *desc = new QLabel(description);
	lay->addWidget(desc);
	description->setLayout(lay);

	desc->setWordWrap(true);
	description->setTitle(tr("Die Grammatik"));
	desc->setText(tr("<html><head /><body><p>Sie haben nun ein (Schatten-) W�rterbuch und ein (Schatten-) Vokabular (wenn das importierte W�rterbuch diese Informationen zur Verf�gung gestellt hat) importiert (Sie k�nnen jetzt zur�ckgehen und noch ein W�rterbuch importieren, wenn Sie m�chten - Sie k�nnen aber dies aber auch nach Abschluss' dieses Assistenten jederzeit in der \"Wortliste\" nachholen).</p><p>Es fehlt nun f�r ihr pers�nliches Sprachmodell noch die Grammatik und die Trainingsdaten.</p><p>Im n�chsten Schritt werden wir anhand von von Ihnen geschriebenen Textdateien Ihren Grammatikalischen Stil ermitteln.</p></body></html>"));

	return description;
}



QWizardPage* FirstRunWizard::createSoundSettingsPage()
{
	SystemWidgetPage *sound = new SystemWidgetPage(this);
	sound->setChild(new SoundSettings(sound));
	return sound;
}

QWizardPage* FirstRunWizard::createPasswordDescriptionPage()
{
	QWizardPage *description = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(description);
	QLabel *desc = new QLabel(description);
	lay->addWidget(desc);
	description->setLayout(lay);

	desc->setWordWrap(true);
	description->setTitle(tr("�ber den Passwortschutz"));
	desc->setText(tr("<html><head /><body><p>simon unterscheidet generell zwischen normaler Benutzung (dies umfasst das Trainieren, Hinzuf�gen von W�rtern, durchsuchen der Wortliste, etc.) und einem \"Systemverwaltungsmodus\". Dieser umfasst zum Beispiel die Systemeinstellungen.</p><p>Der Systemverwaltungsmodus kann mit einem Passwort gegen unlauteren Zugriff gesperrt werden. </p></body></html>"));

	return description;
}

QWizardPage* FirstRunWizard::createPasswordSettingsPage()
{
	SystemWidgetPage *passpg = new SystemWidgetPage(this);
	passpg->setChild(new PasswordSettings(this));
	return passpg;
}

QWizardPage* FirstRunWizard::createJuliusdDescriptionPage()
{
	QWizardPage *description = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(description);
	QLabel *desc = new QLabel(description);
	lay->addWidget(desc);
	description->setLayout(lay);

	desc->setWordWrap(true);
	description->setTitle(tr("�ber Juliusd"));
	desc->setText(tr("<html><head /><body><p>Das simon-System besteht eigentlich aus zwei Teilen:</p><ul><li>simon (client; Dieses Programm)<li>juliusd (server, verwaltet julius)</ul><p>Der juliusd kann beliebig viele simon-clients gleichzeitig bedienen.</p><p>Meist wird der Juliusd auf einem zentralen Server ausgef�hrt werden, zu dem alle Clients verbinden. Es ist jedoch eine Einzelinstallation m�glich. Starten Sie daf�r Juliusd lokal und geben auf der n�chsten Seite als Adresse ihre Loopbackadresse (meist 127.0.0.1 / localhost) und den konfigurierten Port (standardm�sig 4444) an.</p><p>N�here Informationen zu Juliusd finden Sie im Handbuch</p></body></html>"));

	return description;
}

QWizardPage* FirstRunWizard::createJuliusdSettingsPage()
{
	SystemWidgetPage *julius = new SystemWidgetPage(this);
	julius->setChild(new NetworkSettings(julius));
	return julius;
}

QWizardPage* FirstRunWizard::createSelectFilesPage()
{
	return new ImportGrammarSelectFilesPage(this);
}

QWizardPage* FirstRunWizard::createGrammarWorkingPage()
{
	this->firstRunImportGrammarWorkingPage = new FirstRunImportGrammarWorkingPage(this);

	connect(firstRunImportGrammarWorkingPage, SIGNAL(grammarCreated(QStringList)), 
		this, SLOT(mergeGrammarStructure(QStringList)));
	
	return (QWizardPage*) firstRunImportGrammarWorkingPage;
}

QWizardPage* FirstRunWizard::createGrammarSettings()
{
	grammarSettingsPage = new SystemWidgetPage(this);
	return (QWizardPage*) grammarSettingsPage;
	
}

QWizardPage* FirstRunWizard::createLanguageModelDescription()
{
	QWizardPage *description = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(description);
	QLabel *desc = new QLabel(description);
	lay->addWidget(desc);
	description->setLayout(lay);

	desc->setWordWrap(true);
	description->setTitle(tr("Das Sprachmodell"));
	desc->setText(tr("<html><head /><body><p>Sie ben�tigen die folgenden Einzelteile:</p><ul><li>(Schatten-) W�rterbuch, (Schatten-) Vokabeln, Grammatik und Trainingsdaten (pfad, prompts, wav_config)<br />Personenbezogen<li>Sprachskripte (tree1.hed)<br />Sprachbezogen<li>Modellskripte (sil.hed, config, proto, mkphones0.led und -1.led, global.ded, mktri.led)<br />Generell</ul><p>Aus diesen Eingabedaten werden dann folgende Dateien erstellt:<ul><li>hmmdefs<br />Beinhaltet eine technische Repr�sentation der Stimme<li>tiedlist<br />Eine Liste der verwendeten Lautkombinationen<li>dict / dfa<br />Eine von julian lesbare Form der Grammatik</body></html>"));

	return description;
}

QWizardPage* FirstRunWizard::createIntroPage()
{
	QWizardPage *intro = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(intro);
	QLabel *desc = new QLabel(intro);
	lay->addWidget(desc);
	intro->setLayout(lay);

	desc->setWordWrap(true);
	intro->setTitle(tr("Willkommen bei simon"));
	desc->setText(tr("Dieser Assistent wird Ihnen helfen, simon zu konfigurieren.\n\nAlle Einstellungen die Sie in diesem Assistenten treffen k�nnen sp�ter �ber das Systemmen� wieder ge�ndert werden. Bitte beachten Sie, das die Einstellungen hier essientiell f�r die Funktionst�chtigkeit von simon sind.\n\nSollten Sie sich bei einigen Punkten nicht sicher sein, sehen Sie bitte im Handbuch nach oder fragen Sie gegebenenfalls ihren Systemadministrator."));

	return intro;
}

QWizardPage* FirstRunWizard::createCheckList()
{
	QWizardPage *checklist = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(checklist);
	QLabel *desc = new QLabel(checklist);
	desc->setOpenExternalLinks(true);
	lay->addWidget(desc);
	checklist->setLayout(lay);

	desc->setWordWrap(true);
	checklist->setTitle(tr("Checkliste"));
	desc->setText(tr("<html><head/><body><p>Um simon erfolgreich zu benutzen werden einige externe Programme und Dateien ben�tigt.</p><ul><li>HTK Toolkit<br />(Erh�ltlich von der <a href=\"http://htk.eng.cam.ac.uk/\">Universit�t Cambridge</a>)<li>Julius<br />(Erh�ltlich von der offiziellen <a href=\"http://julius.sourceforge.jp/en/\">Julius Homepage</a>)<li>BZip2<br />(Erh�ltlich von der <a href=\"http://www.bzip.org/\">Homepage</a>)<li>Diverse Sprachmodell Skripte und Konfigurationsdateien<br />Halten Sie diese f�r die anschliesende Konfiguration bereit. F�r die Englische Sprache erhalten Sie die Dateien zum Beispiel vom GPL Sprachmodell voxforge (<a href=\"http://www.voxforge.org\">Voxforge Homepage</a>). Im Zweifelsfall wenden Sie sich bitte an den simon support (<a href=\"mailto:support@simon-listens.org\">support@simon-listens.org</a>) oder besuchen Sie das <a href=\"http://www.simon-listens.org/wiki/\">Wiki</a> (im Aufbau)</ul><p>Bitte installieren Sie diese, bevor Sie hier fortfahren.</p></body></html>"));

	return checklist;
}



QWizardPage* FirstRunWizard::createNewModelDescription()
{
	QWizardPage *newModel = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(newModel);
	QLabel *desc = new QLabel(newModel);
	desc->setOpenExternalLinks(true);
	lay->addWidget(desc);
	newModel->setLayout(lay);

	desc->setWordWrap(true);
	newModel->setTitle(tr("Neues Sprachmodell"));
	desc->setText(tr("<html><head /><body><p>Sie haben ausgew�hlt ein neues Sprachmodell zu erstellen.</p><p>Bitte bedenken Sie, dass sie daf�r trozdem noch einige Skripte ben�tigen die von simon m�glicherweise nicht mitgeliefert werden.</p><p>F�r den n�chsten Schritt brauchen Sie g�ltige, teilweise Ihrer Sprache entsprechenden, Exemplare der Dateien:<br />wav_config (wenn Sie simon zum Training verwenden k�nnen Sie bedenkenlos die voxforge-Version der Datei verwenden), tree1.hed (diese Datei muss auf Ihre Sprache, in diesem Fall Deutsch, angepasst sein), config, proto, mkphones0.led, mkphones1.led, global.ded, mktri.led<br /><b>Sie k�nnen die meisten dieser Dateien aus einem aktuellen Voxforge-Snapshot entnehmen. (<a href=\"http://www.voxforge.org\">Voxforge Homepage</a>)</b></p><p>Au�erdem ben�tigen Sie <i>leere</i> prompts, lexicon, shadow-lexicon, vocab, shadow-vocab und grammar Dateien, die Sie im n�chsten Schritt angeben m�ssen.</p><p>Eine ausf�hrliche Anleitung finden Sie im <a href=\"http://www.cyber-byte.at/wiki/index.php?title=Initial_Configuration\">Wiki</a></body></html>"));

	return newModel;
}

QWizardPage* FirstRunWizard::createModelSettings()
{
	return (QWizardPage*) new FirstRunModelSettings(this);
}


QWizardPage* FirstRunWizard::createExternalProgramsPage()
{
	SystemWidgetPage *page = new SystemWidgetPage(this);
	page->setChild(new ExternalProgramManager(page));
	return (QWizardPage*) page;
}

QWizardPage* FirstRunWizard::createLanguageModelSelectSource()
{
	return (QWizardPage*) new SelectLanguageModelSourcePage(this);
}

QWizardPage* FirstRunWizard::createFinishedPage()
{
	QWizardPage *finished = new QWizardPage(this);
	QHBoxLayout *lay = new QHBoxLayout(finished);
	QLabel *desc = new QLabel(finished);
	lay->addWidget(desc);
	finished->setLayout(lay);

	desc->setWordWrap(true);
	finished->setTitle(tr("Konfiguration abgeschlossen"));
	desc->setText(tr("Die Konfiguration von simon ist hiermit abgeschlossen.\n\nSie k�nnen alle Einstellungen im System-Men� bearbeiten.\n\nSollten Sie soeben ein neues Sprachmodell erstellt haben, m�ssen Sie diese vor der ersten Verwendung trainieren. Selektieren Sie hierzu den Men�punkt \"Training\".\n\nViel Spa� mit simon!"));

	return finished;
}


FirstRunWizard::~FirstRunWizard()
{
}


