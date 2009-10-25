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


#ifndef TEXTMACROCOMMANDMANAGER_H
#define TEXTMACROCOMMANDMANAGER_H

#include <simonscenarios/commandmanager.h>

class CreateCommandWidget;
/**
 *	@class PlaceCommandManager
 *	@brief Manager for the place-commands
 *
 *	@version 0.1
 *	@date 20.05.2008
 *	@author Peter Grasch
 */
class TextMacroCommandManager : public CommandManager{
Q_OBJECT
public:
	const QString name() const;
	const KIcon icon() const;
	bool addCommand(Command *command);
	CreateCommandWidget* getCreateCommandWidget(QWidget *parent);

	bool deSerializeCommands(const QDomElement& elem, Scenario *scenario);

    /**
    * @brief Constructor
    * 
    *	@author Peter Grasch
    */
    TextMacroCommandManager(QObject* parent, const QVariantList& args);

    
    ~TextMacroCommandManager();

};

#endif
