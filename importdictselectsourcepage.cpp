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

#include <QLabel>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

ImportDictSelectSourcePage::ImportDictSelectSourcePage(QWidget* parent): QWizardPage(parent)
{
	setTitle("Typ ausw�hlen");
	QVBoxLayout *lay = new QVBoxLayout(this);
	
	QLabel *desc = new QLabel(this);
	desc->setText(tr("Simon kann zwei verschiedene Typen von W�rterb�chern importieren: HADIFIX-BOMP W�rterb�cher und Wiktionary-Dumps. Bitte selektieren Sie welchen Typ von W�rterbuch Sie importieren m�chten:\n\n"));
	desc->setWordWrap(true);
	
	QRadioButton *hadifixBOMP=new QRadioButton("HADIFIX-BOMP", this);
// 	QRadioButton *wiktionary = new QRadioButton(-"
}


ImportDictSelectSourcePage::~ImportDictSelectSourcePage()
{
}


