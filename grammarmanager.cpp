//
// C++ Implementation: grammarmanager
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "grammarmanager.h"
#include "logger.h"
#include "settings.h"
#include "wordlistmanager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>



GrammarManager* GrammarManager::instance;

/**
 * \brief Constructor
 * \author Peter Grasch
 * @param wordlistManager Initializes the member
 */
GrammarManager::GrammarManager(WordListManager *wordlistManager)
{
	this->wordlistManager = wordlistManager;
}

GrammarManager * GrammarManager::getInstance()
{
	if (!instance)
		instance = new GrammarManager(WordListManager::getInstance());
	return instance;
}

/**
 * \brief Loads the structures from the file
 * \author Peter Grasch
 * @return Successs
 */
bool GrammarManager::load()
{
	structures.clear();
	
	QString path =Settings::getS("Model/PathToGrammar");
	Logger::log(QCoreApplication::tr("[INF] Lade Grammatik von %1").arg(path));
	
	QFile grammar(Settings::getS("Model/PathToGrammar"));
	if (!grammar.open(QIODevice::ReadOnly)) return false;
	
	QString structure;
	while (!grammar.atEnd()) 
	{
		structure = grammar.readLine(1500);
		structure.remove(0,7);		//remove the leading "S:NS_B "
		structure = structure.left(structure.count()-6);  //remove the trailing " NS_E"
		structures << structure;
	}
	
	grammar.close();
	
	return true;
}

/**
 * \brief Renames the terminal to the given, new name
 * @param terminal The terminal to renmae
 * @param newName The new name
 */
void GrammarManager::renameTerminal(QString terminal, QString newName)
{
	terminal.replace(".", "\\.");
	terminal.replace("-", "\\-");
	terminal.replace("!", "\\!");
	terminal.replace("?", "\\?");
	terminal.replace("*", "\\*");
	terminal.replace("\\", "\\\\");
	terminal.replace("^", "\\^");
	terminal.replace("$", "\\$");

	structures.replaceInStrings(QRegExp("^"+terminal+"$"), newName);
	structures.replaceInStrings(QRegExp(" "+terminal+"$"), " "+newName);
	structures.replaceInStrings(QRegExp("^"+terminal+" "), newName+" ");
	structures.replaceInStrings(QRegExp(" "+terminal+" "), " "+newName+" ");
}

/**
 * \brief Get Examples for the word of the specified terminal
 * \author Peter Grasch
 * @param word The word to look for examples for
 * @param terminal The terminal of the word
 * @param count How many examples do we want?
 * @return Examples
 */
QStringList GrammarManager::getExamples(QString word, QString terminal, int count)
{
	QStringList grammarStructures = getStructures(terminal);

	if (grammarStructures.count()==0)
	{
		//couldn't resolve terminal - not in grammar definition
		return QStringList();
	}
	
	QStringList chosen;
	QString curTerminal;
	bool alreadyUsed=false;
	for (int i=0; i < count; i++)
	{
		QString sentence = grammarStructures.at(qrand()%grammarStructures.count());
	
		QStringList terminals = sentence.split(" ");
		
		
		//find random words for this terminals:
		//replace the first occurance of the words terminal with the actual word we are trying to
		//"demonstrate in action"
		//this is ensured by the alreadyUsed variable which holds if the word was already replaced
		//if it is set the occurance of the terminal is used just like any other
		for (int j=0; j < terminals.count(); j++)
		{
			
			curTerminal = terminals[j];
			if ((curTerminal == terminal) && (!alreadyUsed))
			{
				terminals.replace(j, word);
				alreadyUsed = true;
			} else
			{
				
				terminals.replace(j, wordlistManager->getRandomWord(terminals[j]));
			}
		}
		
		chosen << terminals.join(" ").trimmed();
		alreadyUsed=false;
	}
	return chosen;
}

/**
 * \brief Returns all terminals contained in the grammar
 * \author Peter Grasch
 * @return The terminals
 */
QStringList GrammarManager::getTerminals()
{
	QStringList out;
	QStringList terminalsInStruct;
	for (int i=0; i < structures.count(); i++)
	{
		terminalsInStruct.clear();
		terminalsInStruct = structures[i].split(" ");
		for (int j=0; j < terminalsInStruct.count(); j++)
			if (!out.contains(terminalsInStruct[j]))
				out << terminalsInStruct[j];
	}
	return out;
}

/**
 * \brief Returns structures using the specified terminal
 * \author Peter Grasch
 * @param terminal The terminal to lok for
 * @return The structures
 */
QStringList GrammarManager::getStructures(QString terminal)
{
	QStringList matching;
	int i=0;
	while (i < this->structures.count())
	{
		if(structures[i].contains(terminal)) matching << structures[i];
		i++;
	}
	return matching;
}

/**
 * \brief Saves the structures
 * \author Peter Grasch
 * @return success
 */
bool GrammarManager::save()
{
	QString path =Settings::getS("Model/PathToGrammar");
	Logger::log(QCoreApplication::tr("[INF] Speichere Grammatik nach %1").arg(path));
	
	QFile grammar(Settings::getS("Model/PathToGrammar"));
	if (!grammar.open(QIODevice::WriteOnly)) return false;
	
	for (int i=0; i < structures.count(); i++)
		grammar.write("S:NS_B "+structures[i].toLatin1()+" NS_E\n");
	
	grammar.close();
	
	return true;
}

/**
 * \brief Sets the structures to the given structures
 * @param structures The structures to set to
 */
void GrammarManager::setStructures(QStringList structures)
{
	this->structures = structures;
}

