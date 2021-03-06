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

#ifndef SIMON_CLIENTSOCKET_H_3FD79B24B9DD413D89FDD2D63112BE40
#define SIMON_CLIENTSOCKET_H_3FD79B24B9DD413D89FDD2D63112BE40

#include <QSslSocket>
#include <QList>
#include <QMutex>
#include <sscprotocol/sscprotocol.h>

const qint8 protocolVersion=1;

class DatabaseAccess;
class SSCObject;
class User;
class Sample;

class ClientSocket : public QSslSocket
{
  Q_OBJECT

  private:
    bool lockedDown;
    QMutex messageLocker;

    DatabaseAccess *databaseAccess;

    QString samplePath(qint32 userId);

    void waitForMessage(qint64 length, QDataStream& stream, QByteArray& message);
    void sendCode(qint32 code);
    bool sendResponse(qint32 code, qint32 response);
    void sendObject(qint32 code, SSCObject* object);
    void sendObjects(qint32 code, QList<SSCObject*> objects);

    void sendUser(qint32 id);
    void sendUsers(User *filterUser, qint32 institutionId, const QString& referenceId);
    void removeUser(qint32 id);
    void sendLanguages();
    void sendMicrophones();
    void sendSoundCards();
    void sendInstitutions();
    void removeInstitution(qint32 id);
    void removeUserInInstitution(qint32 userId, qint32 institutionId);
    void sendUserInstitutionAssociations(qint32 userId);

    void storeSample(Sample *s);

  private slots:
    void slotSocketError();
    void processRequest();
  public:
    ClientSocket(int socketDescriptor, DatabaseAccess *databaseAccess, QObject *parent=0);

    virtual ~ClientSocket();

};
#endif
