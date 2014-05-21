/*
 *   Copyright (C) 2014 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_VRPNCOMMANDMANAGER_H_7A7B9100FF5245329569C1B540119C37
#define SIMON_VRPNCOMMANDMANAGER_H_7A7B9100FF5245329569C1B540119C37

#include <simonscenarios/commandmanager.h>
#include <simonactions/greedyreceiver.h>
#include <QVariantList>

class QWidget;
class VRPNConfiguration;
class VRPNSet;
class VRPNSetContainer;

class VRPNCommandManager : public CommandManager
{
  Q_OBJECT

  private:
    VRPNConfiguration* getVRPNConfiguration();

  protected:
    bool shouldAcceptCommand(Command *command);

  public:
    const QString preferredTrigger() const { return QString(); }
    const QString iconSrc() const;
    const QString name() const;
    bool deSerializeConfig(const QDomElement& elem);

    CreateCommandWidget* getCreateCommandWidget(QWidget *parent);

    VRPNCommandManager(QObject* parent, const QVariantList& args);

    ~VRPNCommandManager();

};
#endif
