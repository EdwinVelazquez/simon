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

#include "listcommand.h"
#include "commandlistwidget.h"
#include <simonactions/actionmanager.h>
#include <unistd.h>
#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QObject>
#include <QTableWidgetSelectionRange>
#include <QHeaderView>
#include <QApplication>
#include <QVariant>
#include <KIcon>
#include <KLocalizedString>


QStringList ListCommand::numberIdentifiers;

ListCommand::ListCommand(const QString& name, const QString& iconSrc, const QStringList& commands, 
		const QStringList& iconSrcs, const QStringList& commandTypes) : Command(name, iconSrc)
{
	this->iconsrcs = iconSrcs;
	this->commands = commands;
	this->commandTypes = commandTypes;
	
	clw = new CommandListWidget();
	connect(clw, SIGNAL(canceled()), this, SLOT(cancel()));
	connect(clw, SIGNAL(runRequest(int)), this, SLOT(processRequest(int)));
	

	if (numberIdentifiers.isEmpty())
		numberIdentifiers << i18n("Zero") << i18n("One") << i18n("Two") 
			<< i18n("Three") << i18n("Four") << i18n("Five") <<
			i18n("Six") << i18n("Seven") << i18n("Eight") << i18n("Nine");
	
	startIndex=0;
}


bool ListCommand::processRequest(int index)
{
	Q_ASSERT(commands.count() == commandTypes.count());

	if (index > commands.count())
		return false;

	if (index == 0)
	{
		//go back
		if (startIndex > 0)
			startIndex -= 8;
		listCurrentCommandSection();
		return true;
	} else if (index == 9)
	{
		//go forward
		if (startIndex+8 < commands.count())
			startIndex += 8;
		listCurrentCommandSection();
		return true;
	} else {
		//execute list entry
		// if index==1, we want it to represent the _first_ entry in the list (index==0)
		index--;
		index += startIndex;

		Q_ASSERT(commands.count() == commandTypes.count());
		if (index >= commands.count())
			return false;

		clw->close();
		usleep(300000);
		ActionManager::getInstance()->triggerCommand(commandTypes[index], commands[index]);
		ActionManager::getInstance()->deRegisterGreedyReceiver(this);
	}
	return false;
}

void ListCommand::cancel()
{
	clw->close();
	ActionManager::getInstance()->deRegisterGreedyReceiver(this);
}

bool ListCommand::greedyTrigger(const QString& inputText)
{
	if (inputText.toUpper() == i18n("Cancel").toUpper())
	{
		clw->close();
		return true;
	}

	bool ok=false;
	int index = inputText.toInt(&ok);
	if (!ok)
	{
		while ((index < numberIdentifiers.count()) && (numberIdentifiers.at(index).toUpper() != inputText.toUpper()))
			index++;

		if (index == numberIdentifiers.count()) return false;
	}

	return processRequest(index);
}

const QString ListCommand::staticCategoryText()
{
	return i18n("List");
}

const QString ListCommand::getCategoryText() const
{
	return ListCommand::staticCategoryText();
}

const KIcon ListCommand::staticCategoryIcon()
{
	return KIcon("view-choose");
}

const KIcon ListCommand::getCategoryIcon() const
{
	return ListCommand::staticCategoryIcon();
}

const QMap<QString,QVariant> ListCommand::getValueMapPrivate() const
{
	QMap<QString,QVariant> out;
	out.insert(i18n("Commands"), commands.join("\n"));
	return out;
}

void ListCommand::listCurrentCommandSection()
{
	QStringList nowIconSrcs, nowCommands;
	for (int i=startIndex; (i < commands.count()) && (i-startIndex < 8); i++)
	{
		nowIconSrcs << iconsrcs[i];
		nowCommands << commands[i];
	}
	CommandListWidget::Flags flags;
	if (startIndex > 0)
	{
		if (startIndex+8 < commands.count())
			flags = CommandListWidget::HasNext|CommandListWidget::HasBack;
		else 
			flags = CommandListWidget::HasBack;
	} else 
		if (startIndex+8 < commands.count())
			flags = CommandListWidget::HasNext;

	clw->init(nowIconSrcs, nowCommands, flags);
}

bool ListCommand::triggerPrivate()
{
	if (commands.count() == 0) return false;

	Q_ASSERT(commands.count() == commandTypes.count());
	//showing list

	clw->setWindowIcon(KIcon(getIconSrc()));
	clw->setWindowTitle(getTrigger());

	listCurrentCommandSection();

	ActionManager::getInstance()->registerGreedyReceiver(this);

	clw->show();

	return true;
}

ListCommand::~ListCommand()
{
	ActionManager::getInstance()->deRegisterGreedyReceiver(this);
	clw->deleteLater();
}

