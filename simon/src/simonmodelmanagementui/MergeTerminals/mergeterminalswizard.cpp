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

#include "mergeterminalswizard.h"
#include "mergeterminalsselectterminalspage.h"
#include "mergeterminalsworkingpage.h"
#include <QWizardPage>
#include <QLabel>
#include <QHBoxLayout>
#include <KStandardDirs>

MergeTerminalsWizard::MergeTerminalsWizard(QWidget* parent): SimonWizard(parent)
{
  setWindowTitle(i18n("Merge Categories"));
  addPage(createSelectTerminalsPage());
  addPage(createWorkingPage());
  addPage(createFinishedPage());
  setBanner("merge");
}


QWizardPage* MergeTerminalsWizard::createSelectTerminalsPage()
{
  return new MergeTerminalsSelectTerminalsPage(this);
}


QWizardPage* MergeTerminalsWizard::createWorkingPage()
{
  MergeTerminalsWorkingPage *working = new MergeTerminalsWorkingPage(this);
  connect(working, SIGNAL(done()), this, SLOT(next()));
  return working;
}


QWizardPage* MergeTerminalsWizard::createFinishedPage()
{
  QWizardPage *finished = new QWizardPage(this);
  QHBoxLayout *lay = new QHBoxLayout(finished);
  QLabel *desc = new QLabel(finished);
  lay->addWidget(desc);
  finished->setLayout(lay);

  desc->setWordWrap(true);
  finished->setTitle(i18n("Import completed"));
  desc->setText(i18n("The categories have been merged.\n\nThank you for improving Simon."));

  return finished;
}

