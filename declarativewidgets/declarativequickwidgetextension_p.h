/*
  declarativequickwidgetextension_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nathan Collins <nathan.collins@kdab.com>

  Licensees holding valid commercial KDAB DeclarativeWidgets licenses may use this file in
  accordance with DeclarativeWidgets Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DECLARATIVEQUICKWIDGETEXTENSION_P_H
#define DECLARATIVEQUICKWIDGETEXTENSION_P_H

#include "declarativewidgets_export.h"
#include "declarativewidgetextension.h"

#include <QPointer>

class DeclarativeContext;

QT_BEGIN_NAMESPACE
class QQuickWidget;
QT_END_NAMESPACE

class DECLARATIVEWIDGETS_EXPORT DeclarativeQuickWidgetExtension : public DeclarativeWidgetExtension
{
  Q_OBJECT

  Q_PROPERTY(QObject* rootContext READ declarativeRootContext WRITE setDeclarativeRootContext
             NOTIFY declarativeRootContextChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeQuickWidgetExtension(QObject *parent = 0);
    ~DeclarativeQuickWidgetExtension();

    QQuickWidget *extendedQuickWidget() const;

    void setDeclarativeRootContext(QObject *context);
    QObject *declarativeRootContext() const;

  Q_SIGNALS:
    void declarativeRootContextChanged();

  private:
    QPointer<DeclarativeContext> m_rootContext;
};

#endif