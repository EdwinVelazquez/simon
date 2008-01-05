//
// C++ Interface: soundsettings
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SOUNDSETTINGS_H
#define SOUNDSETTINGS_H

#include "systemwidget.h"
#include "ui_soundsettingsdlg.h"

class SoundControl;

/**
 * \class SoundSettinsg
 * \author Peter Grasch
 * \date 12.8.2007
 * \brief SystemWidget to manager the soundsettings
 */
class SoundSettings : public SystemWidget
{
Q_OBJECT

private:
	Ui::SoundSettingsDlg ui; //!< UI definition - made by uic from the QTDesigner .ui
	SoundControl *sc;

private slots:
	void refreshDeviceCapabilities();
	
public slots:
	bool init();
	bool apply();
	bool reset();
public:
    SoundSettings(QWidget* parent);
	bool isComplete();
    ~SoundSettings();

};

#endif
