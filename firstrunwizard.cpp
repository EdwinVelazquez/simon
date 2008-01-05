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
#include "firstrunwizard.h"
#include "externalprogrammanager.h"
#include "systemwidgetpage.h"
#include "selectlanguagemodelsourcepage.h"
#include <QWizardPage>

FirstRunWizard::FirstRunWizard(QWidget* parent): SimonWizard(parent)
{
	setWindowTitle(tr("simon Erstkonfiguration"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/firstrun.png"));
	addPage(createIntroPage());
	addPage(createCheckList());
	addPage(createExternalProgramsPage());
	addPage(createLanguageModelSelectSource());
	addPage(createFinishedPage());
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
	desc->setText(tr("Das von simon verwendete Sprachmodell besteht aus vielen Einzelteilen. Einige davon sind individuell f�r den Sprecher, andere sind abh�ngig von der gesprochenen Sprache"));

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
	lay->addWidget(desc);
	checklist->setLayout(lay);

	desc->setWordWrap(true);
	checklist->setTitle(tr("Checkliste"));
	desc->setText(tr("<html><head/><body><p>Um simon erfolgreich zu benutzen werden einige externe Programme ben�tigt.</p><ul><li>HTK Toolkit<br />(Erh�ltlich von http://htk.eng.cam.ac.uk/)<li>Julius<br />(Erh�ltlich von http://julius.sourceforge.jp/en/)<li>BZip2<br />(Erh�ltlich von http://www.bzip.org/)</ul><p>Bitte installieren Sie diese, bevor Sie hier fortfahren</p><p>Au�erdem werden wir im Laufe des Assistenten folgende Datens�tze erstellt:</p><ul><li>Lexikon<li>Vokabular / Grammatik</ul><p>F�r die Einsatzf�higkeit von simon muss dieses Modell dann noch mit Trainingssamples fundiert werden.</p></body></html>"));

	return checklist;
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
	desc->setText(tr("Die Konfiguration von simon ist hiermit abgeschlossen.\n\nSie k�nnen alle Einstellungen im System-Men� bearbeiten."));

	return finished;
}


FirstRunWizard::~FirstRunWizard()
{
}


