//
// C++ Implementation: importprogramwizard
//
// Description:
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importprogramwizard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

/**
*   \brief constructor which creats the wizardpages
*   @autor Susanne Tschernegg
*/
ImportProgramWizard::ImportProgramWizard(QWidget* parent): QWizard(parent)
{
    oldId=0;
    this->addPage(createIntroPage());
	this->addPage(createSelectProgramPage());
	this->addPage(createConfigureProgramPage());
    ImportProgramPage *ipp = createImportProgramPage();
    this->addPage(ipp);
    this->addPage(createFinishedPage());
    
    //(connect(this, SIGNAL(finished( int )), this, SLOT(finish( int )));
    
	setWindowTitle("Programm hinzuf�gen");
    setPixmap(QWizard::WatermarkPixmap, QPixmap(tr(":/images/importdict.png")));
    
    connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(idChanged(int)));
    connect(ipp, SIGNAL(commandCreated(Command*)), this, SIGNAL(commandCreated(Command*)));
    connect(ipp, SIGNAL(commandCreated(Command*)), this, SLOT(next()));
    connect(this, SIGNAL(finished(int)), this, SLOT(restart()));
    
   // QMessageBox::information(0, "importProgramwizard","konstruktor");
}

/**
*   \brief destructor
*   @autor Susanne Tschernegg
*/
ImportProgramWizard::~ImportProgramWizard()
{}

/**
*   \brief Creates the intro page
*   @autor Susanne Tschernegg
*/
QWizardPage* ImportProgramWizard::createIntroPage()
{
    QWizardPage *intro = new QWizardPage(this);
	intro->setTitle("Hinzuf�gen des Programmes");
	QLabel *label = new QLabel(intro);
	label->setText("Hier kann ein Programm den Kommandos - die Simon kennt - hinzugef�gt werden.");
	QVBoxLayout *layout = new QVBoxLayout(intro);
	layout->addWidget(label);
	intro->setLayout(layout);
	
	return intro;
}

/**
*   \brief creates the selectprogrampage
*   @autor Susanne Tschernegg
*/
SelectProgramPage* ImportProgramWizard::createSelectProgramPage()
{
    return new SelectProgramPage(this);
}

/**
*   \brief creates the configureprogrampage
*   @autor Susanne Tschernegg
*/
ConfigureProgramPage* ImportProgramWizard::createConfigureProgramPage()
{
    return new ConfigureProgramPage(this);
}

/**
*   \brief creates the importprogrampage
*   @autor Susanne Tschernegg
*/
ImportProgramPage* ImportProgramWizard::createImportProgramPage()
{
    return new ImportProgramPage(this);
}

/**
*   \brief creates the last page
*   @autor Susanne Tschernegg
*/
QWizardPage* ImportProgramWizard::createFinishedPage()
{
    QWizardPage *finished = new QWizardPage(this);
	finished->setTitle("Hinzuf�gen des Programmes");
	QLabel *label = new QLabel(finished);
	label->setText("Klicken Sie auf \"Fertigstellen\" um den Wizard \nabzuschlie�en.");
	QVBoxLayout *layout = new QVBoxLayout(finished);
	layout->addWidget(label);
	finished->setLayout(layout);
	
	return finished;
}

void ImportProgramWizard::idChanged(int newId)
{
    if((oldId==1) && (newId==2))
    {
        SelectProgramPage *spp = dynamic_cast<SelectProgramPage*>(page(1));
        if(!spp)
            return;
        ConfigureProgramPage *cpp = dynamic_cast<ConfigureProgramPage*>(page(2));
        cpp->progName = spp->getName();
        cpp->execPath = spp->getExecPath();
        cpp->writeInformation();
    }
    else if((oldId==2) && (newId==3))
    {
        ConfigureProgramPage *cpp = dynamic_cast<ConfigureProgramPage*>(page(2));
        if(!cpp)
            return;
        ImportProgramPage *ipp = dynamic_cast<ImportProgramPage*>(page(3));
        ipp->createCommand(cpp->progName, cpp->execPath);
    }
/*    else if((oldId==3) && (newId==4))
    {

    }*/
    else if((oldId==4) && (newId==3))
    {
        restart();
        next();
    }
    
    oldId = newId;
}
