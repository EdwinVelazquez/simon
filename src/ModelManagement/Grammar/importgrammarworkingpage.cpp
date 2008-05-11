//
// C++ Implementation: importgrammarworkingpage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importgrammarworkingpage.h"
#include "importgrammar.h"
#include <QFile>

ImportGrammarWorkingPage::ImportGrammarWorkingPage(QWidget* parent): QWizardPage(parent)
{
	grammarImporter=0;
	completed=false;
	setTitle(tr("Analyse l�uft..."));
	ui.setupUi(this);
}

void ImportGrammarWorkingPage::printStatus(QString status)
{
	ui.lbCurrentAction->setText(status);
	QCoreApplication::processEvents();
}

void ImportGrammarWorkingPage::displayFileProgress(int progress, int max)
{
	ui.pbProgress->setMaximum(max);
	ui.pbProgress->setValue(progress);
	QCoreApplication::processEvents();
}

void ImportGrammarWorkingPage::displayWholeProgress(int progress, int max)
{
	ui.pbTotal->setMaximum(max);
	ui.pbTotal->setValue(progress);
	QCoreApplication::processEvents();
}

void ImportGrammarWorkingPage::initializePage()
{
	completed=false;
	emit completeChanged();

	if (grammarImporter) grammarImporter->deleteLater();

	grammarImporter = new ImportGrammar(this);
	connect(grammarImporter, SIGNAL(status(QString)), this, SLOT(printStatus(QString)));
	connect(grammarImporter, SIGNAL(fileProgress(int, int)), this, SLOT(displayFileProgress(int, int)));
	connect(grammarImporter, SIGNAL(allProgress(int, int)), this, SLOT(displayWholeProgress(int, int)));
	connect(grammarImporter, SIGNAL(grammarCreated(QStringList)), this, SIGNAL(grammarCreated(QStringList)));
	connect(grammarImporter, SIGNAL(grammarCreated(QStringList)), this, SLOT(setComplete()));


	QStringList files = field("files").toString().split("||");
	
	grammarImporter->setFiles(files);
	grammarImporter->setIncludeUnknown(field("includeUnknown").toBool());
	grammarImporter->start();
}

void ImportGrammarWorkingPage::cancel()
{
	if (!grammarImporter) return;
	if (grammarImporter->isRunning())
		grammarImporter->terminate();
}


ImportGrammarWorkingPage::~ImportGrammarWorkingPage()
{
	if (grammarImporter) grammarImporter->deleteLater();
}


