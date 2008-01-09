/***************************************************************************
 *   Copyright (C) 2006 by Peter Grasch   *
 *   bedahr@gmx.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#include "addwordview.h"
#include <QWizardPage>
#include <QMessageBox>
#include <QLineEdit>
#include "logger.h"
#include "addwordintropage.h"
#include "addwordrecordpage.h"
#include "addwordresolvepage.h"
#include "wordlistmanager.h"

/**
 * @brief Constructor
 *
 * Constructs a new AddWordView Object.
 * Initializes the UI and sets it to the first page
 *
 *	@author Peter Grasch
 * @param QWidget *parent
 * Parent of the Dialog; Default: 0
 * @param Qt::Wflags f
 * Qt Windowflags - default 0
*/

AddWordView::AddWordView(QWidget *parent, WordListManager *wordlistMgr, GrammarManager *grammarManager)
	: QWizard (parent)
{
	prevId=0;
	this->wordlistMgr = wordlistMgr;
	this->welcomePage = createWelcomePage();
	resolvePage = createResolvePage(grammarManager);
	this->addPage((QWizardPage*) welcomePage);
	this->addPage(resolvePage);

	this->addPage(createRecordPage());
	this->addPage(createFinishedPage());
	
	connect(this, SIGNAL(finished( int )), this, SLOT(finish( int )));
	connect(this, SIGNAL(currentIdChanged( int )), this, SLOT(idChanged(int)));

	setWindowTitle(tr("Wort hinzuf�gen"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(tr(":/images/banners/addword.png")));
}

void AddWordView::idChanged(int newId)
{
	if ((newId == 1))
	{
		resolvePage->init(welcomePage->getName());
	}
	prevId = newId;
}

/**
 * \brief Creates the welcomepage
 * \author Peter Grasch
 * @return the QWizardPage
 */
AddWordIntroPage* AddWordView::createWelcomePage()
{
	return new AddWordIntroPage(this);
}

/**
 * \brief Creates the recordpage
 * \author Peter Grasch
 * @return the QWizardPage
 */
QWizardPage* AddWordView::createRecordPage()
{
	return new AddWordRecordPage(this);
}

/**
 * \brief Creates the recordpage
 * \author Peter Grasch
 * @return the QWizardPage
 */
AddWordResolvePage* AddWordView::createResolvePage(GrammarManager *grammarManager)
{
	return new AddWordResolvePage(wordlistMgr, grammarManager, this);
}


/**
 * \brief Creates the finishedpage
 * \author Peter Grasch
 * @return the QWizardPage
 */
QWizardPage* AddWordView::createFinishedPage()
{
	QWizardPage *finished = new QWizardPage(this);
	finished->setTitle(tr("Hinzuf�gen des Wortes"));
	QLabel *label = new QLabel(finished);
	label->setText(tr("Es wurden alle ben�tigten Daten gesammelt.\n\nSimon kann das neue Wort jetzt lernen.\nBitte ueberpr�fen Sie, bevor Sie hier\nbest�tigen, ob die Aufnahmen nicht von\nHintergrundger�uschen beeintr�chtigt werden.\n\nKlicken Sie auf \"Fertigstellen\" um den Wizard \nabzuschlie�en."));
	QVBoxLayout *layout = new QVBoxLayout(finished);
	layout->addWidget(label);
	finished->setLayout(layout);
	
	return finished;
}




/**
 * \brief Writes the word into the files and cleans up the wizard
 * 
 * \author Peter Grasch
 */
void AddWordView::finish(int done)
{
	((AddWordRecordPage*) this->page(2))->cleanUp();
	if (!done) return;
	
	QString word = ((AddWordIntroPage*) this->page(0))->getName();
	
	Logger::log(tr("[INF] F�ge neues Wort zum Modell hinzu..."));
	Logger::log(tr("[INF] Neues Wort lautet: ")+word);
	//finishs up
	
	WordList *list = new WordList();

	list->append(Word(resolvePage->getName(), resolvePage->getPronunciation(), resolvePage->getTerminal(), 2 /* 2 recordings */));

	wordlistMgr->addWords(list, true /*sorted*/, false /*shadowed*/);

	//TODO: Process recordings

	//cleaning up
	Logger::log(tr("[INF] Wort hinzugef�gt: ")+word);
	emit addedWord();
	
	restart();
}
