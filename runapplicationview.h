//
// C++ Interface: runapplicationview
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef RUNAPPLICATIONVIEW_H
#define RUNAPPLICATIONVIEW_H

#include <QDialog>
#include <QWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSize>
#include "simoninfo.h"
#include "ui_rundialog.h"
#include "runcommand.h"

/**
 *	@class RunApplicationView
 *	@brief Provides a graphical frontend to run commands and perform 
 * 	system actions
 *
 *	@version 0.1
 *	@date 23.01.2006
 *	@author Peter Grasch
 *	@todo Implementing filtering functions
 */
class RunApplicationView : public QDialog {
	Q_OBJECT

signals:
	void hidden();
	
private:
	Ui::RunDialog ui;
	RunCommand *run;
	void hideEvent(QHideEvent *event) { emit hidden(); }
public slots:
	void insertCommands(CommandList list);
	void runCommand(QTableWidgetItem* command);
	void runSelectedCommand();
	void clearSearchText();
	void filterByPattern();
	void filterByPattern(QString filter, CommandList *commlist=NULL);
	CommandList filterByCategory(int commandtype, CommandList *commlist=NULL);
	CommandList filterByStrCategory(QString commandtype, CommandList *commlist=NULL);
	int getCategory(QString commandtype);
public:
    RunApplicationView(QWidget *parent);

    ~RunApplicationView();

};

#endif
