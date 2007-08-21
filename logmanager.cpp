//
// C++ Implementation: logmanager
//
// Description: 
//
//
// Author: Phillip Goriup <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "logmanager.h"
#include <QRegExp>
#include <QFile>
#include <QCoreApplication>
#include <logger.h>


/**
 * \brief Constructor
 * creating a new Instanz of LogManager
 *
 * \author Phillip Goriup
 */
LogManager::LogManager()
{
	this->finishedLoading = false;
	entries = new LogEntryList();
	killMe=false;
	connect(this, SIGNAL(finished()), this, SLOT(resetKillFlag()));
	connect(this, SIGNAL(terminated()), this, SLOT(resetKillFlag()));
}



bool LogManager::readLog()
{	
	return true;
}

/**
 * \brief reads the logfile, and saves the content into a vector of LogEntry
 * get the information of the loggfile by reading line by line. chops every line into
 * the tags;
 * researches every line if a extra information is given 
 * 	[ERR] for Error
 * 	[INF] for Info
 * 	[UPD] for Update
 * saves the read informations into a Vector of LogEntry
 * 
 * \author Phillip Goriup, Peter Grasch
 */
void LogManager::run ()
{
	finishedLoading = false;
	if(!this->entries)
	{
		this->entries = new LogEntryList;
	}
	else
	{
		delete(this->entries);
		this->entries = new LogEntryList;
	}
	QFile *LogF = new QFile("log/simon.log");
	if (!LogF->open(QIODevice::ReadOnly))
	{
		emit logReadFinished(0);
	}
	QString str;
	int type;
	
	int i = 0;
	
	QCoreApplication::processEvents();
	while (!LogF->atEnd () && !killMe)
	{
		type = 0;
		
		str = LogF->readLine();
		if(str.contains("[ERR]", Qt::CaseInsensitive))
			type = type|ERR;
		if(str.contains("[INF]", Qt::CaseInsensitive))
			type = type|INF;
		if(str.contains("[UPD]", Qt::CaseInsensitive))
			type = type|UPD;
		if(str.contains("[SET]", Qt::CaseInsensitive))
			type = type|SET;

		//MMMMMMMMMMMMUUUUUUUUUUUUUUUUUUHHHHHHHAAAAAAHHHHHHAAAAAAAA
		QTime funzi_der_erste = QTime::fromString(str.mid(12 ,8),"hh:mm:ss");
		QDate funzus_der_grosse = QDate::fromString(str.mid(1,10),"yyyy/MM/dd");
		//_______________________________________________________________________
		
		this->entries->append(LogEntry(funzus_der_grosse , 
		funzi_der_erste, 
		str.remove(QRegExp("\\[.*\\]")).trimmed().toLatin1(), type));
		
		i++;
	}	
	delete(LogF);
	if (!killMe)
	{
		finishedLoading = true;
		emit this->logReadFinished(1);
	}
	else
	{
		emit this->logReadFinished(0);
	}
}




/**
 * \brief returns entries per one day
 *
 * \param 
 * 
 * \author Phillip Goriup
 */
LogEntryList* LogManager::getDay(QDate day)
{
	LogEntryList *entriesperday = new LogEntryList;
	int i = 0;
	int size = entries->count();
	while((i<size) && (this->entries->at(i++).getDate() < day));
	i--;
		
	
	while((i<size) && (this->entries->at(i).getDate() == day))
	{
		
		entriesperday->append(this->entries->at(i));
		i++;
		
	}
	
	return entriesperday;
}


/**
 * \brief clears the memory after a abort, or a leave
 *
 * \author Phillip Goriup
 */
void LogManager::stop(bool free)
{
	killMe=true;
	if(free)
		this->entries->clear();
	
	if((!free) && (this->isRunning ()))
	{
		this->wait(5000);
		this->entries->clear();
	}
	this->wait(5000);
	this->terminate();
	killMe=false;

}

/**
 * \brief returns all entries
 *
 * \author Phillip Goriup
 */
LogEntryList* LogManager::getAll()
{
	return this->entries;
}


/**
 * \brief Destructor
 * 
 * \author Phillip Goriup
 */
LogManager::~LogManager()
{
	this->entries->clear();
}



