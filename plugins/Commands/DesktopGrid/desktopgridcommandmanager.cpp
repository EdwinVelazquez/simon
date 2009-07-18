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

#include "desktopgridcommandmanager.h"
#include <simonlogging/logger.h>
#include "screengrid.h"
#include <KLocalizedString>
#include <KGenericFactory>
#include <KAction>
#include <KActionCollection>
#include "desktopgridconfiguration.h"

K_PLUGIN_FACTORY( DesktopGridPluginFactory, 
			registerPlugin< DesktopGridCommandManager >(); 
			registerPlugin< DesktopGridConfiguration >(); 
		)
        
K_EXPORT_PLUGIN( DesktopGridPluginFactory("simondesktopgridcommand") )



DesktopGridCommandManager::DesktopGridCommandManager(QObject *parent, const QVariantList& args) : CommandManager(parent, args)
{
	setXMLFile("simondesktopgridpluginui.rc");
	activateAction = new KAction(this);
	activateAction->setText(i18n("Activate Desktopgrid"));
	activateAction->setIcon(KIcon("games-config-board"));
	connect(activateAction, SIGNAL(triggered(bool)),
		this, SLOT(activate()));
	actionCollection()->addAction("simondesktopgridplugin", activateAction);
}

const QString DesktopGridCommandManager::name() const
{
	return i18n("Desktopgrid");
}

CommandConfiguration* DesktopGridCommandManager::getConfigurationPage()
{
	return DesktopGridConfiguration::getInstance();
}

bool DesktopGridCommandManager::trigger(const QString& triggerName)
{
	kDebug() << triggerName << DesktopGridConfiguration::getInstance()->trigger();
	if (triggerName != DesktopGridConfiguration::getInstance()->trigger()) return false;

	activate();
	return true;
}

void DesktopGridCommandManager::activate()
{
	Logger::log(i18n("[INF] Activating desktopgrid"));
	ScreenGrid *screenGrid = new ScreenGrid();
	screenGrid->show();
}
 
bool DesktopGridCommandManager::load()
{
	DesktopGridConfiguration::getInstance(dynamic_cast<QWidget*>(parent()), QVariantList())->load();
	return true;
}

bool DesktopGridCommandManager::save()
{
	return true;
}

DesktopGridCommandManager::~DesktopGridCommandManager()
{
	activateAction->deleteLater();
// 	DesktopGridConfiguration::getInstance()->destroy();
}
