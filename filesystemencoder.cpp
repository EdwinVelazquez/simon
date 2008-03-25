//
// C++ Implementation: filesystemencoder
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "filesystemencoder.h"
#include <QString>
/**
 * \brief Encode the given filename
 * \author Peter Grasch
 * @param  in filename
 * @return safe filename
 */
QString FileSystemEncoder::encodeFilename(QString in)
{
	in.replace("�", "%ue");
	in.replace("�", "%ue");
	in.replace("�", "%oe");
	in.replace("�", "%Ue");
	in.replace("�", "%Ae");
	in.replace("�", "%Oe");
	return in;
}

/**
 * \brief Decode the given filename
 * \author Peter Grasch
 * @param  in Safe filename
 * @return Original filename
 */
QString FileSystemEncoder::decodeFilename(QString  in)
{
	in.replace("u@e", "%ue");
	in.replace("a@e", "%ae");
	in.replace("o@e", "%oe");
	in.replace("A@e", "%Ae");
	in.replace("O@e", "%Oe");
	in.replace("U@e", "%Ue");
	return in;
}
