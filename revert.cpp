//
// C++ Implementation: revert
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "revert.h"

Revert::Revert(QWidget *parent) : SystemWidget(tr("Zur�cksetzen"), QIcon(":/images/icons/gtk-undo-ltr.svg"), tr("Stellen Sie einen vorherigen Zeitpunkt des Systems wieder her"), parent)
{
	ui.setupUi(this);
	hide();

	//set help
	help = tr("Dieser Men�punkt erlaubt es Ihnen, die Einstellungen simpel und einfach zu einem fr�heren Stadium zur�ckzusetzen.\n\nUm zum Beispiel zum Stand vom 1.1. zur�ckzusetzen, w�hlen Sie einfach im Kalender den 1. J�nner, selektieren alle �nderungen und klicken auf \"Die ausgew�hlten �nderungen R�ckg�ngig machen\".\n\nDie Suche dient als Einschr�nkung der �nderung.\n\nBitte beachten sie das die immer nur die selektierten �nderungen zur�ckgenommen werden!");
}


bool Revert::init()
{
	
	return true;
}


bool Revert::apply()
{
	
	return true;
}

bool Revert::reset()
{
	
	return true;
}

Revert::~Revert()
{
}


