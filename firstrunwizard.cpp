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
#include <QWizardPage>

FirstRunWizard::FirstRunWizard(QWidget* parent): SimonWizard(parent)
{
	setWindowTitle(tr("simon Erstkonfiguration"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/firstrun.png"));
	addPage(createIntroPage());
	addPage(createFinishedPage());
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


