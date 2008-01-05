//
// C++ Implementation: selectlanguagemodelsourcepage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "selectlanguagemodelsourcepage.h"
#include "firstrunwizard.h"

SelectLanguageModelSourcePage::SelectLanguageModelSourcePage(QWidget* parent): QWizardPage(parent)
{
	setTitle("Sprachmodell: Quelle");
	ui.setupUi(this);
	connect(ui.rbNewModel, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));
	connect(ui.rbOpenModel, SIGNAL(toggled(bool)), this, SLOT(updateInfo()));
	updateInfo();
}

void SelectLanguageModelSourcePage::updateInfo()
{
	if (ui.rbNewModel->isChecked())
	{
		ui.lbInfo->setText(tr("<html><head /><body><p>Wenn Sie ein neues Sprachmodell generieren werden Sie aufgefordert werden:</p><ul><li>Pfade zu den ben�tigten Dateien zu setzen.<li>Ein W�rterbuch zu importieren (meist aus dem Internet)<li>Grammatikdefinitionen zu erstellen (auch diese k�nnen aus pers�nlichen Texten importiert werden</ul><p>Das schlie�t das erste erstellen des Sprachmodelles einmal ab. Damit das Modell einsatzf�hig ist, m�ssen noch W�rter zum aktiven Sprachschatz hinzugef�gt werden und das Modell trainiert werden.</p></body></html>"));
	} else 
	{
		ui.lbInfo->setText(tr("Wenn Sie ein vorhandenes Sprachmodell mit simon verwenden wollen, ist die Prozedur denkbar einfach. Sie werden mit der Konfigurationsseite des Modells konfrontiert, wo nur mehr die n�tigen Pfade zu den Dateien konfiguriert werden m�ssen."));
	}
}

int SelectLanguageModelSourcePage::nextId() const
{
	if (ui.rbNewModel->isChecked())
	{
		return FirstRunWizard::ModelSettingsPage;
	} else
		return FirstRunWizard::NewModelDescription;
}


SelectLanguageModelSourcePage::~SelectLanguageModelSourcePage()
{
}


