//
// C++ Implementation: importlexiconpage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importlexiconpage.h"
#include <QFileDialog>

ImportLexiconPage::ImportLexiconPage(QWidget* parent): QWizardPage(parent)
{
	ui.setupUi(this);
	setTitle(tr("Lexikon ausw�hlen"));
	registerField("lexiconFilename", ui.lePath);
	connect(ui.tbOpenFile, SIGNAL(clicked()), this, SLOT(selectFile()));
}


void ImportLexiconPage::selectFile()
{
	ui.lePath->setText(QFileDialog::getOpenFileName(this, tr("Lexikon �ffnen")));
}

ImportLexiconPage::~ImportLexiconPage()
{
}


