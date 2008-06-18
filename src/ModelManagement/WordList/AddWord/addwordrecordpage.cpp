//
// C++ Implementation: addwordrecordpage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "addwordrecordpage.h"
#include <QDate>
#include <QTime>
#include <QDir>
#include <QMessageBox>
#include "../../../SimonLib/FileSystem/filesystemencoder.h"
#include "../../../SimonLib/Settings/settings.h"

/**
 * \brief Constructor - also creates the GUI Elements
 * \author Peter Grasch
 * @param parent
 * The parent of the widget
 */
AddWordRecordPage::AddWordRecordPage(QWidget *parent)
 : QWizardPage(parent)
{
	setTitle(tr("Aufnehmen des Wortes"));
	lay = new QVBoxLayout(this);
	QLabel *desc = new QLabel(this);
	desc->setWordWrap(true);
	desc->setText(tr("Bitte nehmen Sie nun das hinzuzuf�gende Wort zweimal auf.\n\nBitte achten Sie darauf, das Wort deutlich, aber nat�rlich auszusprechen und vermeiden Sie Hintergrundger�usche.\n"));
	lay->addWidget(desc);


	rec1 = 0;
	rec2 = 0;
}

QString AddWordRecordPage::getSamplesDir()
{
	QString sampleDir = Settings::getS("Model/PathToSamples");
	QDir dir(sampleDir);
	if (!dir.exists())
		if (dir.mkpath(sampleDir))
			return sampleDir;
		else return "";

	return sampleDir;
}

/**
 * \brief Sets the recwidgets-titles to the examples of the previous page (pulled out of the fields wordExamples1,2)
 * \author Peter Grasch
 */
void AddWordRecordPage::initializePage()
{
	if (rec1)
	{
		lay->removeWidget(rec1);
		rec1->deleteLater();
	}
	if (rec2)
	{
		lay->removeWidget(rec2);
		rec2->deleteLater();
	}
	QString example1=field("wordExample1").toString();
	QString example2=field("wordExample2").toString();
	QString dateTime = QDate::currentDate().toString ( "yyyy-MM-dd" ) +"_"+QTime::currentTime().toString("hh-mm-ss");
	QString filename1=example1.replace(" ", "_")+ "_1_"+dateTime;
	QString filename2=example2.replace(" ", "_")+ "_2_"+dateTime;

	filename1 = FileSystemEncoder::encodeFilename(filename1);
	filename2 = FileSystemEncoder::encodeFilename(filename2);



	emit recordingNamesGenerated(filename1, filename2);

	QString sampleDir = getSamplesDir();
	if (sampleDir.isEmpty()) {
		QMessageBox::critical(this, tr("Konnte Pfad nicht anlegen"), tr("Konnte Pfad nicht erstellen.\n\nBitte �berpr�fen Sie Ihre Schreibrechte im konfigurierten Sample-Pfad"));
		return;
	}

	rec1 = new RecWidget(tr("1: %1").arg(example1), Settings::getS("Model/PathToSamples")+"/"+filename1+".wav", this);
	rec2 = new RecWidget(tr("2: %1").arg(example2), Settings::getS("Model/PathToSamples")+"/"+filename2+".wav", this);

	
	connect(rec1, SIGNAL(recordingFinished()), this, SIGNAL(completeChanged()));
	connect(rec2, SIGNAL(recordingFinished()), this, SIGNAL(completeChanged()));
	connect(rec1, SIGNAL(sampleDeleted()), this, SIGNAL(completeChanged()));
	connect(rec2, SIGNAL(sampleDeleted()), this, SIGNAL(completeChanged()));

	lay->addWidget(rec1);
	lay->addWidget(rec2);
}


/**
 * \brief Destructor; Calls cleanUp()
 * \author Peter Grasch
 * \see cleanUp()
 */
AddWordRecordPage::~AddWordRecordPage()
{
	if (rec1) rec1->deleteLater();
	if (rec2) rec2->deleteLater();
	if (lay) delete lay;
}


