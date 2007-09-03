//
// C++ Implementation: chooseplacepage
//
// Description:
//
//
// Author: Susanne Tschernegg
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "chooseplacepage.h"
#include "settings.h"
#include "command.h"
#include <QMessageBox>

/**
*   \brief constructor
*   @autor Susanne Tschernegg
*/
ChoosePlacePage::ChoosePlacePage(QWidget* parent): QWizardPage(parent)
{
    vboxLayout = new QVBoxLayout(this);
    
    label = new QLabel(this);
    label->setText(tr("Ort wird den Komandos hinzugef�gt"));
    
    //wenn da eine fehlermeldung kommt, dass falls abbrechen gedr�ckt wird, der wizard zur configurepage zur�ck geht
    vboxLayout->addWidget(label);
}

/**
*   \brief destructor
*   @autor Susanne Tschernegg
*/
ChoosePlacePage::~ChoosePlacePage()
{}
