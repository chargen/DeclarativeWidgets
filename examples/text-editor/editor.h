/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef EDITOR_H
#define EDITOR_H

#include <QIcon>
#include <QObject>

class QTextDocument;

class Editor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QTextDocument* document READ document CONSTANT)
  Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

  public:
    explicit Editor(QObject *parent = 0);
    ~Editor();
    
    QTextDocument *document() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

    Q_INVOKABLE QIcon iconFromFile(const QString &fileName) const;
    Q_INVOKABLE QIcon iconFromTheme(const QString &iconName) const;

  Q_SIGNALS:
    void fileNameChanged(const QString &fileName);
    void requestSaveFileName();

    void information(const QString &message);
    void critical(const QString &message);

  public Q_SLOTS:
    void newDocument();
    void open(const QString &fileName);
    void save();

  private:
    QTextDocument *m_document;
    QString m_fileName;
};

#endif // EDITOR_H