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

#ifndef SIMON_DICT_H_3242C8BA5338485898083584C232BC90
#define SIMON_DICT_H_3242C8BA5338485898083584C232BC90

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>

/**
  \class Dict

  \brief Provides some basic functions and members that make up a Dictionary

  Provides functions to convert between IPA and XSP and holds some members like
  the words, pronunciations and categories.
  This are simple QStringLists because this is still _very_ low-level

  The matrix from ipa to x-sampa was built with the matrix from theiling for reference.
  Thanks!

\author Peter Grasch
\date 6.5.2007
*/
class Dict : public QObject
{
  Q_OBJECT

    signals:
  void loaded();
  void progress(int prog);
  protected:
    QHash<int, QString> translationLookup, modifiers;
    QStringList allowedPhonemes;

    QStringList words;
    QStringList pronunciations;
    QStringList categories;

    void buildAllowedPhonemes();
    void buildTranslationTables();

    QString segmentSampa(const QString& sampa);
    QString adaptToSimonPhonemeSet(QString sampa);
  public:

    enum DictType
    {
      HadifixBOMP=1,
      HTKLexicon=2,
      PLS=4,
      SPHINX=8,
      JuliusVocabulary=16
    };

    Dict(QObject *parent=0);
    QString ipaToXSampa(QString ipa);
    virtual void load(QString path, QString encodingName) = 0;
    QStringList getWords() const { return words; }
    QStringList getPronuncations() const { return pronunciations; }
    QStringList getCategories() const { return categories; }
    virtual ~Dict();

};
#endif
