//
// C++ Interface: wordlistview
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef WORDLISTVIEW_H
#define WORDLISTVIEW_H

#define sImportDict 	32


#include "word.h"
#include "ui_wordlist.h"
#include "inlinewidget.h"


class TrainingView;
class QPoint;
class ImportDictView;
class WordListManager;

/**
 *	@class WordListView
 *	@brief Frontend to the Wordlist
 *
 *	@version 0.1
 *	@date 23.01.2006
 *	@author Peter Grasch
 */


class WordListView : public InlineWidget {
	Q_OBJECT
private:
	int shownDialogs;
	QPoint importDictPos;
	
	bool abortVocabInsertion;
	Ui::WordList ui;	//!< UI definition - made by uic from the QTDesigner .ui
	WordList trainingwordlist;  //!< Holds all the words that are scheduled for training
	WordListManager *wordListManager; //!< Concept class
	ImportDictView *importDictView; //!< Provides the Interface to import a dictionary
	
	void setDirty ( bool dirty );

signals:
	void wordlistLoaded();


public slots:
	void abortInsertion() { abortVocabInsertion = true; }
	void reloadList();
	void reloadShadowList();
	void askForRebuild();
	void suggestTraining();
	void markWordToTrain( Word word );
	void copyWordToTrain();
	void deleteTrainingWord();
	void deleteSelectedWord();
	void trainList();
	void importDict(WordList* list);
	void clearList();
	void filterListbyPattern(QString filter="");
	void insertVocab(WordList *vocab);
	void show();
	void hide();
	void showImportDictDialog();

	void setSettingsVisible();
	void setSettingsHidden();

	WordListManager* getManager(){return wordListManager;}

public:
	WordListView(QWidget *parent);
	
	~WordListView();

};

#endif
