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

#include "declarativefontdialog_p.h"

class DeclarativeFontDialogAttached::Private
{
  public:
    Private() : dialogAccepted(false), options(0) {}

  public:
    QFont initial;
    QString title;
    bool dialogAccepted;
    QFontDialog::FontDialogOptions options;
};


DeclarativeFontDialogAttached::DeclarativeFontDialogAttached(QObject *parent)
  : StaticDialogMethodAttached(parent), d(new Private)
{
}

DeclarativeFontDialogAttached::~DeclarativeFontDialogAttached()
{
  delete d;
}

void DeclarativeFontDialogAttached::setTitle(const QString &title)
{
  if (title == d->title)
    return;

  d->title = title;
  emit titleChanged(title);
}

QString DeclarativeFontDialogAttached::title() const
{
  return d->title;
}

bool DeclarativeFontDialogAttached::dialogAccepted() const
{
  return d->dialogAccepted;
}

void DeclarativeFontDialogAttached::setOptions(int options)
{
  if (options == d->options)
    return;

  d->options = static_cast<QFontDialog::FontDialogOptions>(options);
  emit optionsChanged(options);
}

int DeclarativeFontDialogAttached::options() const
{
  return d->options;
}

QFont DeclarativeFontDialogAttached::getFont()
{
  QWidget *parent = bestParentWindow();
  bool ok = false;

  QFont retVal;
  if (d->title.isEmpty() && d->options == 0) {
    retVal = QFontDialog::getFont(&ok, d->initial, parent);
  } else if (d->options != 0) {
    retVal = QFontDialog::getFont(&ok, d->initial, parent, d->title, d->options);
  } else {
    retVal = QFontDialog::getFont(&ok, d->initial, parent, d->title);
  }

  setDialogAccepted(ok);
  return retVal;
}

QFont DeclarativeFontDialogAttached::getFont(const QString &fontFamily)
{
  d->initial = QFont(fontFamily);
  return getFont();
}

void DeclarativeFontDialogAttached::setDialogAccepted(bool accepted)
{
  if (accepted == d->dialogAccepted)
    return;

  d->dialogAccepted = accepted;
  emit dialogAcceptedChanged(accepted);
}

DeclarativeFontDialog::DeclarativeFontDialog(QObject *parent)
  : DeclarativeWidgetProxy<QFontDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeFontDialogAttached *DeclarativeFontDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFontDialogAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeFontDialog, QFontDialog)
