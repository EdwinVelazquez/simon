//
// C++ Implementation: importbomppage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importbomppage.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>

ImportBOMPPage::ImportBOMPPage(QWidget* parent): QWizardPage(parent)
{
	QVBoxLayout *lay = new QVBoxLayout(this);
	QLabel *lbDesc = new QLabel (this);
	lbDesc->setText(tr("<html><head></head><body><p>Das BOMP Wörterbuch ist ein von der Universität Bonn entwickeltes, frei erhätliches, Wörterbuch. Der Download ist gratis, muss aber per e-Mail angefragt werden.</p><p>Näheres finden Sie hier:<br/><a href=http://www.ikp.uni-bonn.de/dt/forsch/phonetik/bomp/LIESMICH.html>http://www.ikp.uni-bonn.de/dt/forsch/phonetik/bomp/LIESMICH.html</a></p><p>Simon kann die <b>HADIFIX</b> Version des Wörterbuchs importieren. Bitte wählen Sie die (extrahierte) aus und bestätigen Sie mit weiter:<br /><br /></p></body></html>"));
	lbDesc->setWordWrap(true);
	
	QHBoxLayout *fileLay = new QHBoxLayout();
	QLabel *lbFile = new QLabel(this);
	lbFile->setText(tr("HADIFIX-BOMP:"));
	
	QPushButton *pbOpenFile = new QPushButton(this);
	pbOpenFile->setIcon(QIcon(":/images/icons/document-open.svg"));
	QLineEdit *leFile = new QLineEdit(this);
	registerField("fileName*", leFile);
	fileLay->addWidget(lbFile);
	fileLay->addWidget(leFile);
	fileLay->addWidget(pbOpenFile);
	
	connect(pbOpenFile, SIGNAL(clicked()), this, SLOT(setFile()));

	lay->addWidget(lbDesc);
	lay->addLayout(fileLay);
	this->setLayout(lay);

	setTitle("Importiere BOMP Wörterbuch");
}

void ImportBOMPPage::setFile()
{

}

ImportBOMPPage::~ImportBOMPPage()
{
}


