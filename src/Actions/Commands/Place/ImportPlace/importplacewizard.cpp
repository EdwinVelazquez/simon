//
// C++ Implementation: importplacewizard
//
// Description:
//
//
// Author: Susanne Tschernegg
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importplacewizard.h"
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>
#include <QPixmap>
#include <QRadioButton>
#include "../placecommand.h"
#include "selectplacepage.h"

/**
*   \brief constructor which creats the wizardpages
*   @author Susanne Tschernegg
*   @param QWidget *parent
*/
ImportPlaceWizard::ImportPlaceWizard(QWidget* parent): QWizard(parent)
{
	this->addPage(createIntroPlacePage());
	selectPlacePage = createSelectPlacePage();
	addPage(selectPlacePage);
	this->addPage(createFinishedPage());

	setWindowTitle(tr("Ort hinzuf�gen"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/banners/importplace.png"));

	connect(this, SIGNAL(finished(int)), this, SLOT(createCommand(int)));
}

void ImportPlaceWizard::createCommand(int status)
{
	if (status)
		emit commandCreated(new PlaceCommand(selectPlacePage->getName(), "", selectPlacePage->getUrl()));
	
	restart();
}

/**
*   \brief destructor
*   @author Susanne Tschernegg
*/
ImportPlaceWizard::~ImportPlaceWizard()
{}

/**
*   \brief Creates the select-page
*   @author Peter Grasch
*   @return The page
*/
SelectPlacePage* ImportPlaceWizard::createSelectPlacePage()
{
	return new SelectPlacePage(this);
}

/**
*   \brief Creates the intro page
*   @author Susanne Tschernegg
*   @return IntroPlacePage*
*       returns the new initialized IntroPlacePage
*/
QWizardPage* ImportPlaceWizard::createIntroPlacePage()
{
	QWizardPage *intro = new QWizardPage(this);
	intro->setTitle(tr("Hinzuf�gen eines Ortes"));

	QLabel *label = new QLabel(intro);
	label->setWordWrap(true);
	label->setText(tr("Hier k�nnen Sie einen Ort den Kommandos hinzuf�gen.\n\nsimon unterscheidet grunds�tzlich zwischen lokalen (Ordner) und entfernten Orten (HTTP / FTP).\n\n"));
	QVBoxLayout *layout = new QVBoxLayout(intro);
	layout->addWidget(label);
	intro->setLayout(layout);

	return intro;
}



/**
*   \brief creates the last page
*   @author Susanne Tschernegg
*   @return QWizardPage*
*       returns a new WizardPage 
*/
QWizardPage* ImportPlaceWizard::createFinishedPage()
{
	QWizardPage *finished = new QWizardPage(this);
	finished->setTitle(tr("Hinzuf�gen eines Ortes"));
	QLabel *label = new QLabel(finished);
	label->setWordWrap(true);
	label->setText(tr("\n\nKlicken Sie auf \"Fertigstellen\" um den Wizard abzuschlie�en."));
	QVBoxLayout *layout = new QVBoxLayout(finished);
	layout->addWidget(label);
	finished->setLayout(layout);
	
	return finished;
}

