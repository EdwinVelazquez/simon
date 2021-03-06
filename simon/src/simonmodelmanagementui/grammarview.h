/*
 *   Copyright (C) 2008 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_GRAMMARVIEW_H_9DC3821C61394228AED5ECE6953DF69A
#define SIMON_GRAMMARVIEW_H_9DC3821C61394228AED5ECE6953DF69A

#include "simonmodelmanagementui_export.h"
#include <simonuicomponents/inlinewidget.h>

#include <simonscenarios/scenariodisplay.h>

/**
  @author Peter Grasch <bedahr@gmx.net>
*/
class GrammarViewPrivate;

class SIMONMODELMANAGEMENTUI_EXPORT GrammarView : public InlineWidget, public ScenarioDisplay
{
  Q_OBJECT
    private:
    GrammarViewPrivate *d;

  protected:
    void displayScenarioPrivate(Scenario *scenario);

  public:
    GrammarView(QWidget* parent=0);
    ~GrammarView();

};
#endif
