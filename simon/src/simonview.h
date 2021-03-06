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

#ifndef SIMON_SIMONVIEW_H_FAA1A01DFF1E4DA098606C3E951E43AD
#define SIMON_SIMONVIEW_H_FAA1A01DFF1E4DA098606C3E951E43AD

/**
 *	@class SimonView
 *	@brief The Main UI Class
 *
 *	This class is not only the "main" UI-Class but also the interface to the
 *	underlying main concept class.
 *
 *	@version 0.1
 *	@date 07.01.2006
 *	@author Peter Grasch
 */

#include "ui_simonview.h"
#include <KDE/KXmlGuiWindow>
#include <simonappcore/simoncontrol.h>
#include <simonscenarios/scenariodisplay.h>
#include <simonscenarios/scenarioofferui.h>

#include <QMutex>

#include <KDE/KHTMLPart>

class TrayIconManager;
class KCMultiDialog;
class KAction;
class KComboBox;
class WelcomePage;
class TrainingView;
class VocabularyView;
class GrammarView;
class RunCommandView;
class ContextView;
class QTimeLine;
class Author;

class SimonView : public KXmlGuiWindow, public ScenarioDisplay, public ScenarioOfferUi
{
    Q_OBJECT
  public:
    explicit SimonView(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~SimonView();

    void closeEvent ( QCloseEvent * event );
    bool askToAcceptScenario(const QString& requester, const QString& name, const QList<Author*> authors) const;

  public slots:
    void displayConnectionStatus(const QString &status);

    void closeSimon();

    void toggleConnection();
    void displayError(const QString& error);

    void toggleActivation();
    void setActivation(bool active);
    void representState(SimonControl::SystemStatus status);
    
    void showSystemDialog();
    void showSampleShare();
    
   private slots:
    void updateActionList();
    void editScenario();
    void backToOverview();
    void backButtonAnimationStep(int step);
   
  private:
    void setupSignalSlots();
    void setupActions();

    void displayScenarioPrivate(Scenario *scenario);
    
    QMutex guiUpdateMutex;

    KAction *disconnectAction;
    KAction *activateAction;
    KAction *connectAction;

    Ui::MainWindow ui;                            //!< Mainwindow UI definition - made by uic from the QTDesigner .ui
    SimonControl *control;                        //!< Pointer to the main concept class
    TrayIconManager *trayManager;                 //!< Handles the TrayIcon
    
    WelcomePage *welcomePage;
    TrainingView *trainDialog;
    VocabularyView *vocabularyView;
    GrammarView *grammarView;
    ContextView *contextDialog;
    RunCommandView *runDialog;
    
    QTimeLine* backButtonAnimation;
};


#endif
