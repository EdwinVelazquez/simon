//
// C++ Implementation: importdictselectsourcepage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importdictselectsourcepage.h"
#include "importdictview.h"
#include <QLabel>
#include <QRadioButton>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>

/**
 * \brief Constructor - Inits the gui
 * \author Peter Grasch
 * @param parent Parent of the WizardPage
 */
ImportDictSelectSourcePage::ImportDictSelectSourcePage(QWidget* parent): QWizardPage(parent)
{
	setTitle(tr("Wörterbuch Typ auswählen"));
	QVBoxLayout *lay = new QVBoxLayout(this);
	
	QLabel *desc = new QLabel(this);
	desc->setText(tr("Simon kann zwei verschiedene Typen von Wörterbüchern importieren: HADIFIX-BOMP Wörterbücher und Wiktionary-Dumps.\n\nBitte selektieren Sie welchen Typ von Wörterbuch Sie importieren möchten:\n"));
	desc->setWordWrap(true);
	
	QRadioButton *hadifixBOMP=new QRadioButton(tr("HADIFIX-BOMP"), this);
	QRadioButton *wiktionary = new QRadioButton(tr("Wiktionary Wörterbuch"), this);
	
	registerField("hadifix", hadifixBOMP, "checked", SIGNAL(toggled(bool)));
	registerField("wiktionary", wiktionary, "checked", SIGNAL(toggled(bool)));

	lay->addWidget(desc);
	lay->addWidget(hadifixBOMP);
	lay->addWidget(wiktionary);
	setLayout(lay);

	hadifixBOMP->setChecked(true);
}
/**
 * \brief Returns the next id for the wizard (2 if we selected hadifix, else 3)
 * \author Peter Grasch
 * @return the id
 */
int ImportDictSelectSourcePage::nextId() const
{
	if (field("hadifix").toBool())
	{
		return ImportDictView::BompPage;
	} else return ImportDictView::WiktionaryPage;
}

/**
 * \brief destructor
 * \author Peter Grasch
 */
ImportDictSelectSourcePage::~ImportDictSelectSourcePage()
{
}


