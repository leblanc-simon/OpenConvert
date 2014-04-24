/*
QOpenTodoList is a program to manage  your todo list
Copyright (C) 2011  Simon Leblanc <contact@leblanc-simon.eu>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef ConvertWindow_H
#define ConvertWindow_H

#include <QMainWindow>
#include <QWidget>
#include <QWebElement>
#include <QSystemTrayIcon>

namespace Ui {
    class ConvertWindow;
}

class ConvertWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConvertWindow(QWidget *parent = 0);
    ~ConvertWindow();

protected:
    void            closeEvent(QCloseEvent *event);

private:
    Ui::ConvertWindow *convert_window;
    void            setup();

    QSystemTrayIcon *tray_icon;
    void            initIcon();

private slots:
    void            showWindow();
    void            hideWindow();
    void            showAbout();
    void            iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // ConvertWindow_H
