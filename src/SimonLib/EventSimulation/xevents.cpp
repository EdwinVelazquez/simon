//
// C++ Implementation: xevents
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QHash>
#include <QCoreApplication>
#include <KMessageBox>
#include <KLocalizedString>
#include <QDebug>
#include "xevents.h"
#include "../Logging/logger.h"
// #include "key.h"


#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/extensions/XTest.h>

#ifdef None
#undef None
#endif

#ifdef KeyPress
#undef KeyPress
#endif

/**
 * @brief Constructor
 * 
 * Opens the display (member)
 *
 * @param char* displayName
 * The name of the display to open
 * 
 * @author Peter Grasch
 */
XEvents::XEvents(char* displayName) : CoreEvents()
{
	display = openDisplay(displayName);
}


/**
 * @brief Opens the Display and returns the handle
 *
 * @param int keycombination
 * The keycombination
 * 
 * @author Peter Grasch
 */
Display* XEvents::openDisplay(char* displayName)
{
	int Event, Error;
	int Major, Minor;
	
	Logger::log(QCoreApplication::tr("[INF] �ffne display \"%1\"").arg(QString(displayName)));

	Display * display = XOpenDisplay(displayName);

	if (!display) {
		Logger::log(QCoreApplication::tr("[ERR] Fehler beim �ffnen des display \"%1\"").arg(QString(displayName)));
		KMessageBox::error(0,i18n("Konnte Display nicht �ffnen. Bitte �berpr�fen Sie ihre Konfiguration und / oder setzen Sie sich mit den simon-Entwickler in Verbindung. (Display: \"%1\")").arg(QString(XDisplayName ( displayName ))));
		return NULL;
	}

	//check wether the XTest extension is installed
	if ( !XTestQueryExtension(display, &Event, &Error, &Major, &Minor) ) {
		Logger::log("[ERR] Display "+QString(displayName)+" unterst�tzt XTest nicht");
		KMessageBox::error(0,i18n("Der X-Server unterst�tzt die \"XTest\" nicht - bitte installieren Sie diese. (Display: \"%1\")").arg(QString(DisplayString(display))));

		XCloseDisplay(display);
		return NULL;
	}


	//The following should be logged somewhere... Interresting for debugging purposes...
	//We'll do that once we have the logging classes...
	Logger::log(i18n("[INF] XTest f�r Server \"%1\" ist Version %2.%3").arg(QString(DisplayString(display))).arg(Major).arg(Minor));

	Logger::log(i18n("[INF] Aufnahme der Display-Kontrolle"));
	XTestGrabControl( display, True ); 
	Logger::log(i18n("[INF] Synchronisiere Display"));
	XSync( display,True ); 
	return display;
}

/**
 * \brief Clicks the coordinates with a simple LMB-Click and release
 * \author Peter Grasch
 * @param x The x coordinate
 * @param y The y coordinate
 */
void XEvents::click(int x, int y)
{
	if (!display) return;
	XTestFakeMotionEvent(display, 0, x, y, 10);
	XTestFakeButtonEvent(display, 1, true, 10);
	XTestFakeButtonEvent(display, 1, false, 10);
	XFlush(display);
}

/**
 * \brief Resolves the string to an appropriate keysym and sends it using pressKey(...)
 * \author Peter Grasch
 * @param keysymString The string to convert/send
 * @see sendKey()
 */
void XEvents::sendKeySymString(QString keysymString)
{
	pressKey(XStringToKeysym(keysymString.toAscii().data()));
}

/**
 * \brief Overloaded function; Calls sendKey(unsigned int)
 * @param key The key will be casted to unsigned short and passed to sendKey
 */
void XEvents::sendChar(char key)
{
	sendKey((unsigned int) key);
}

/**
 * \brief Sends the raw unicode character given by key
 * \author Peter Grasch
 * @param key The key to send
 */
#include <QDebug>
void XEvents::sendKey(unsigned int key /*unicode*/)
{
	qDebug() << key;
	sleep(1);
	if (!display) return;
// 	char keyChr[256];
// 	sprintf(keyChr,"U%x",key);
// 	KeySym keyToSend=XStringToKeysym(keyChr);
	KeyCode keyCode = XKeysymToKeycode(display, key);
	
	KeySym shiftSym = XKeycodeToKeysym(display, keyCode, 1);
	KeySym altGrSym = XKeycodeToKeysym(display, keyCode, 2);
	
	if (shiftSym == key)
		setModifierKey(Qt::SHIFT, true);
	else if (altGrSym == key)
		setModifierKey(Qt::Key_AltGr, true);
	
	qDebug() << keyCode;
	
	pressKeyCode(keyCode);
	unsetUnneededModifiers();
	
	
// 	qDebug() << "Keysym: " << keyToSend;
// 	qDebug() << "KeyCode: " << keyCode;
// 	qDebug() << "Keysym reverse: " << XKeycodeToKeysym(display, XKeysymToKeycode(display, key), 0); //nomods
// 	qDebug() << "Keysym reverse: " << XKeycodeToKeysym(display, XKeysymToKeycode(display, key), 1); //shift
// 	qDebug() << "Keysym reverse: " << XKeycodeToKeysym(display, XKeysymToKeycode(display, key), 2); //altgr
// 	qDebug() << "Keysym reverse: " << XKeycodeToKeysym(display, XKeysymToKeycode(display, key), 3);
// 	qDebug() << "Keysym reverse: " << XKeycodeToKeysym(display, XKeysymToKeycode(display, key), 4);
// 	qDebug() << "-------------";
	
// 	if (key > 32)
// 	{
// 		int syms;
// 		KeyCode keyToSendcode = XKeysymToKeycode(display, keyToSend);hier kommt der test. qorjq
// 		KeySym *keyToSendShifted=XGetKeyboardMapping(display, keyToSendcode, 1, &syms);
// 		if (!keyToSendShifted) return;	//get the keyToSendboard mapping and go back
// 		for (; syms && (!keyToSendShifted[syms-1]); syms--) ; //to the first in the list
// 		if (!syms) return;	//return on error
// 		
// 		if (keyToSend==keyToSendShifted[2])
// 			setModifierKey(Qt::Key_AltGr, true);
// 		
// 		char keyChr = (char) keyToSend;
// 		KeySym generatedKeySym = XStringToKeysym(&keyChr);
// 		qDebug() << generatedKeySym;
// 		
// 		if (generatedKeySym)
// 			pressKey(generatedKeySym);
// 		else pressKey((KeySym) keyToSend);
// 		unsetUnneededModifiers();
// 	} else {
		
// 		pressKey(keyToSend);
// 	}
	
}

void XEvents::pressKey(KeySym key)
{
	pressKeyCode(XKeysymToKeycode(display, key));
}

void XEvents::pressKeyCode(KeyCode code)
{
	XTestFakeKeyEvent(display, code, True, 15);
	XTestFakeKeyEvent(display, code, False, 15);
	XFlush ( display );
}


/**
 * @brief Sets the modifier key
 *
 * @param int virtualKey
 * The keycode
 * @param bool once
 * Wether the modifier should be unset after one "normal" key
 * 
 * @author Peter Grasch
 */
void XEvents::setModifierKey(int virtualKey, bool once)
{
	if ((!shiftSet) && (virtualKey & Qt::SHIFT))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), True, 5);
		shiftSet=true;
		shiftOnce=once;
	}
	if ((!altgrSet) && (virtualKey & Qt::Key_AltGr))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_ISO_Level3_Shift), True, 5);
		altgrSet=true;
		altgrOnce=once;
	}
	if ((!strgSet) && (virtualKey & Qt::CTRL))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Control_L), True, 5);
		strgSet=true;
		strgOnce=once;
	}
	if ((!altSet) && (virtualKey & Qt::ALT))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Alt_L), True, 5);
		altSet=true;
		altOnce=once;
	}
	if ((!superSet) && (virtualKey & Qt::META))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Super_L), True, 5);
		superSet=true;
		superOnce=once;
	}
	
	XFlush ( display );
}

/**
 * @brief Un-Set the modifier
 *
 * @param int virtualKey
 * The keycode
 * 
 * @author Peter Grasch
 */
void XEvents::unsetModifier(int virtualKey)
{
	if ((virtualKey & Qt::SHIFT))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), False, 5);
		shiftSet=false;
	}
	if ((virtualKey & Qt::Key_AltGr))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_ISO_Level3_Shift), False, 5);
		altgrSet=false;
	}
	if ((virtualKey & Qt::CTRL))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Control_L), False, 5);
		strgSet=false;
	}
	if ((virtualKey & Qt::ALT))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Alt_L), False, 5);
		altSet=false;
	}
	if ((virtualKey & Qt::META))
	{
		XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Super_L), False, 5);
		superSet=false;
	}
	XFlush ( display );
}

/**
 * @brief Destructor
 *
 * 
 *
 * @author Peter Grasch
 */
XEvents::~XEvents()
{
	XCloseDisplay(display);
	delete display;
}


