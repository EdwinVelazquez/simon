//
// C++ Implementation: addwordintropage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "addwordintropage.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <KLineEdit>

/**
 * \brief Constructor - also creates the GUI Elements
 * \author Peter Grasch
 * @param parent
 * The parent of the widget
 */
AddWordIntroPage::AddWordIntroPage(QWidget* parent): QWizardPage(parent)
{
	setTitle(tr("Hinzuf�gen eines neuen Wortes"));
	QLabel *label = new QLabel(this);
	label->setWordWrap(true);
	label->setText(tr("Mit Hilfe dieses Assistenten k�nnen Sie neue W�rter zum Sprachmodell hinzuf�gen.\n\nGeben Sie hierzu bitte den Namen des Wortes an und best�tigen Sie mit \"Weiter\":\n\n"));
	QLabel *lbName = new QLabel(this);
	lbName->setText(tr("Neues Wort:"));
	KLineEdit *leName = new KLineEdit(this);
	QVBoxLayout *layout = new QVBoxLayout(this);
	QHBoxLayout *loName = new QHBoxLayout();
	loName->addWidget(lbName);
	loName->addWidget(leName);

	layout->addWidget(label);
	registerField("wordNameIntro*", leName);
	layout->addLayout(loName);
	
	setLayout(layout);
}

