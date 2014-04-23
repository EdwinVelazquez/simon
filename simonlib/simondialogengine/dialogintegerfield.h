/*
 *   Copyright (C) 2014 Benjamin Bowley-Bryant <benbb@utexas.edu>
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

#ifndef SIMON_DIALOGINTEGERFIELD_H_numbers
#define SIMON_DIALOGINTEGERFIELD_H_numbers

#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QSharedPointer>
#include <KDebug>
#include "dialogfield.h"

class DialogIntegerField : public DialogField<int>
{
  protected:
    virtual const QString& getType() const { return DialogIntegerField::typeInfo.id; }
    virtual QSharedPointer<VariableType> parseValue(const QString& value);

    virtual QSharedPointer<VariableType> deSerializeValue(const QDomElement& elem);
    virtual QDomElement seriaizeValue(QDomDocument * doc);

    DialogIntegerField() : DialogField< int >() { }
    DialogIntegerField(const QString& n) : DialogField< int >(n) { }
  public:
    static const DialogFieldTypeInfo typeInfo;
    static DialogFieldBase* deSerializeDialogIntegerField(const QDomElement& elem);
    static DialogFieldBase* createDialogIntegerField(const QString& name, const QString& value);

    DialogIntegerField(const QString& name, const VariableType& val) : DialogField<int>(name,val) { }

    virtual QString toString() { return QString::number(*getVal().data()); }
};
#endif /* SIMON_DIALOGINTEGERFIELD_H_numbers */
