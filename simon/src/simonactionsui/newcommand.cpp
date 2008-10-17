/*
 *   Copyright (C) 2008 Peter Grasch <grasch@simon-listens.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "newcommand.h"

#include <commandpluginbase/command.h>
#include <commandpluginbase/createcommandwidget.h>
#include <simonactions/actionmanager.h>

#include <KUrl>
#include <KMessageBox>
#include <KKeySequenceWidget>
#include <KDialogButtonBox>

NewCommand::NewCommand(QWidget *parent) : KDialog(parent)
{
	QWidget *widget = new QWidget( this );
	ui.setupUi(widget);
	
	ui.swCommandCreaters->removeWidget(ui.swCommandCreaters->currentWidget());
	
	setMainWidget( widget );
	setCaption( i18n("Kommando") );
	
	connect(ui.leTrigger, SIGNAL(textChanged(QString)), this, SLOT(setWindowTitleToCommandName(QString)));
	connect(ui.leTrigger, SIGNAL(textChanged(QString)), this, SLOT(checkIfComplete()));
	
	commandCreaters=0;
	checkIfComplete();
}

bool NewCommand::registerCreators(QList<CreateCommandWidget*>* commandCreaters)
{
	if (this->commandCreaters)
		delete this->commandCreaters;
	
	foreach (CreateCommandWidget *widget, *commandCreaters)
	{
		ui.cbType->addItem(widget->windowIcon(), widget->windowTitle());
		ui.swCommandCreaters->addWidget(widget);
		connect(widget, SIGNAL(completeChanged()), this, SLOT(checkIfComplete()));
	}
	
	this->commandCreaters = commandCreaters;
	return true;
}


void NewCommand::init(Command *command)
{
	if (!command) return;
	
	ui.leTrigger->setText(command->getTrigger());
	ui.ibIcon->setIcon(command->getIconSrc());

	bool found=false;
	int i=0;
	foreach (CreateCommandWidget *widget, *commandCreaters)
	{
		if (widget->init(command))
		{
			found=true;
			ui.cbType->setCurrentIndex(i);
			ui.swCommandCreaters->setCurrentIndex(i);
		}
		i++;
	}
	if (!found)
		KMessageBox::error(this, i18n("Konnte Kommandotyp nicht bestimmen."));
	
	checkIfComplete();
}

void NewCommand::checkIfComplete()
{
	CreateCommandWidget *creater = dynamic_cast<CreateCommandWidget*>(ui.swCommandCreaters->currentWidget());
// 	Q_ASSERT(creater);
	
	bool complete;
	if (!creater) 
		complete = false;
	else
		complete = (!ui.leTrigger->text().isEmpty()) && creater->isComplete();
	
	enableButtonOk(complete);
}

void NewCommand::setWindowTitleToCommandName(QString name)
{
	if (!name.isEmpty())
		setCaption(i18n("Kommando: %1", name));
	else setCaption(i18n("Kommando"));
}

Command* NewCommand::newCommand()
{
	if (KDialog::exec())
	{
		//creating
		CreateCommandWidget *creater = dynamic_cast<CreateCommandWidget*>(ui.swCommandCreaters->currentWidget());
		Q_ASSERT(creater);
		
		if (!creater) return 0;
		
		return creater->createCommand(ui.leTrigger->text(), ui.ibIcon->icon());
		
// 		int type = ui.cbType->currentIndex();
// 		switch (type)
// 		{
// 			case 0: //Program
// 				command = new ExecutableCommand(ui.leTrigger->text(), ui.ibIcon->icon(),
// 							ui.urExecutable->url().path(), ui.urWorkingDirectory->url());
// 				break;
// 				
// 			case 1: //place
// 				command = new PlaceCommand(ui.leTrigger->text(), ui.ibIcon->icon(),
// 							ui.urUrl->url());
// 				break;
// 				
// 			case 2: //shortcut
// 				command = new ShortcutCommand(ui.leTrigger->text(), ui.ibIcon->icon(),
// 							ui.ksShortcut->keySequence());
// 				break;
// 				
// 			case 3: //textmacro
// 				command = new TextMacroCommand(ui.leTrigger->text(), ui.ibIcon->icon(),
// 							ui.teMacroText->toPlainText());
// 				break;
// 		}
// 		ui.ksShortcut->clearKeySequence();
// 		return command;
	}
// 	ui.ksShortcut->clearKeySequence();
	return 0;
}

NewCommand::~NewCommand()
{
	delete commandCreaters;
}