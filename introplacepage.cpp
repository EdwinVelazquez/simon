//
// C++ Implementation: introplacepage
//
// Description:
//
//
// Author: Susanne Tschernegg
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "introplacepage.h"
#include "settings.h"
#include "command.h"
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>

/**
*   \brief constructor
*   @author Susanne Tschernegg
*   @param QWidget* parent
*/
IntroPlacePage::IntroPlacePage(QWidget* parent): QWizardPage(parent)
{
    vboxLayout = new QVBoxLayout(this);
	setTitle(tr("Hinzuf�gen eines Ortes"));
	QLabel *label = new QLabel(this);
	label->setText(tr("Hier k�nnen Sie einen Ort ihren Kommandos hinzuf�gen, um ihn sp�ter �ber das Schl�sselwort Simon anzusprechen. \n\nEs wird zwischen lokalen und entfernten Orten unterschieden. Unter entfernten Orten versteht man Orte, die �ber das Internet erreichbar sind.\n\n"));
	label->setWordWrap(true);
    
    rbLocalPlace = new QRadioButton(this);
    rbLocalPlace->setText(tr("Lokaler Ort"));
    rbLocalPlace->setChecked(true);
    rbRemotePlace = new QRadioButton(this);
    rbRemotePlace->setText(tr("Entfernter Ort"));
    
    vboxLayout->addWidget(label);
    vboxLayout->addWidget(rbLocalPlace);
    vboxLayout->addWidget(rbRemotePlace);
    
    connect(rbLocalPlace, SIGNAL(clicked()), this, SIGNAL(placeChanged()));
    connect(rbRemotePlace, SIGNAL(clicked()), this, SIGNAL(placeChanged()));
}

/**
*   \brief destructor
*   @author Susanne Tschernegg
*/
IntroPlacePage::~IntroPlacePage()
{
    vboxLayout->deleteLater();
    rbRemotePlace->deleteLater();
}

