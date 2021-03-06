/*
 *   Copyright (C) 2009 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_SSC_USER_H_586F99940E1A4366937DCB1984C37B25
#define SIMON_SSC_USER_H_586F99940E1A4366937DCB1984C37B25

#include <QString>
#include <QDebug>
#include "sscobject.h"
#include "sscobjects_export.h"

class SSCOBJECTS_EXPORT User : public SSCObject
{

  private:
    qint32 m_userId;
    QString m_surname;
    QString m_givenName;
    QChar m_sex;
    qint16 m_birthYear;
    QString m_zipCode;
    QString m_education;
    QString m_currentOccupation;
    QString m_motherTongueId;
    QString m_motherTongue;
    QString m_diagnosis;
    qint8 m_orientation;
    qint8 m_motorFunction;
    qint8 m_communication;
    QString m_mouthMotoric;
    qint8 m_interviewPossible;
    qint8 m_repeatingPossible;

  public:
    User(qint32 userId,QString surname,
      QString givenName,QChar sex,
      qint16 birthYear,QString zipCode,
      QString education,QString currentOccupation,
      QString motherTongueId,QString motherTongue,
      QString diagnosis,qint8 orientation,
      qint8 motorFunction,qint8 communication,QString mouthMotoric,
      qint8 interviewPossible,qint8 repeatingPossible);

    User() : m_userId(0), m_birthYear(0), m_orientation(0), m_motorFunction(0), 
    m_communication(0), m_interviewPossible(2), m_repeatingPossible(2) {}

    void deserialize(QByteArray data);
    QByteArray serialize();

    qint32 userId() { return m_userId; }
    QString surname() { return m_surname; }
    QString givenName() { return m_givenName; }
    QChar sex() { return m_sex; }
    qint16 birthYear() { return m_birthYear; }
    QString zipCode() { return m_zipCode; }
    QString education() { return m_education; }
    QString currentOccupation() { return m_currentOccupation; }
    QString motherTongueId() { return m_motherTongueId; }
    QString motherTongue() { return m_motherTongue; }
    QString diagnosis() { return m_diagnosis; }
    qint8 orientation() { return m_orientation; }
    qint8 communication() { return m_communication; }
    qint8 motorFunction() { return m_motorFunction; }
    QString mouthMotoric() { return m_mouthMotoric; }
    qint8 interviewPossible() { return m_interviewPossible; }
    qint8 repeatingPossible() { return m_repeatingPossible; }

    void setBirthYear(qint16 birthYear) { m_birthYear = birthYear; }
    void setInterviewPossible(qint8 interviewPossible) { m_interviewPossible = interviewPossible; }
    void setRepeatingPossible(qint8 repeatingPossible) { m_repeatingPossible = repeatingPossible; }
    
    void setOrientation(qint8 orientation) { m_orientation = orientation; }
    void setMotorFunction(qint8 motorFunction) { m_motorFunction = motorFunction; }
    void setCommunication(qint8 communication) { m_communication = communication; }
    
    ~User() {}
};
#endif
