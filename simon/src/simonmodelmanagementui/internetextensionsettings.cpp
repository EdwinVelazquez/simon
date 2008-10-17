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

#include "internetextensionsettings.h"
#include <kgenericfactory.h>
#include <KGlobal>

K_PLUGIN_FACTORY( InternetExtensionSettingsFactory, 
			registerPlugin< InternetExtensionSettings >(); 
		)
        
K_EXPORT_PLUGIN( InternetExtensionSettingsFactory("InternetExtensionSettings") )

InternetExtensionSettings::InternetExtensionSettings(QWidget* parent, const QVariantList &args): KCModule(KGlobal::mainComponent(), parent, args)
{
	Q_UNUSED(args);

	ui.setupUi(this);

	connect(ui.kcfg_WikiDumpPrefix, SIGNAL(textChanged(QString)), this, SLOT(makeExample()));
	connect(ui.kcfg_WikiDumpPostfix, SIGNAL(textChanged(QString)), this, SLOT(makeExample()));

	makeExample();
}


InternetExtensionSettings::~InternetExtensionSettings()
{
}

void InternetExtensionSettings::makeExample()
{
	QString example;
	example += ui.kcfg_WikiDumpPrefix->text();
	example += "xxwiktionary/xxxxxxxx";
	example += ui.kcfg_WikiDumpPostfix->text();
	ui.lbExample->setText(example);
}