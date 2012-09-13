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

#include "convertwindow.h"
#include "ui_convertwindow.h"

#include <QWebElement>
#include <QWebFrame>
#include <QWebSettings>
#include <QString>
#include <QDir>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QCloseEvent>

#include "about.h"


/**
 * Constructeur
 */
ConvertWindow::ConvertWindow(QWidget *parent) :
    QMainWindow(parent),
    convert_window(new Ui::ConvertWindow)
{
    convert_window->setupUi(this);
    this->setWindowModality(Qt::NonModal);

    setup();
    initIcon();
}


/**
 * Destructeur
 */
ConvertWindow::~ConvertWindow()
{
    delete convert_window;
}


/**
 * Méthode initialisant du programme
 *
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::setup()
{
}


/**
 * Méthode initialisant l'icône de la zone de notification
 *
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::initIcon()
{
    tray_icon = new QSystemTrayIcon(this);

    QMenu* menu = new QMenu(this);

    QAction* action_show = new QAction(QString::fromUtf8("Afficher"), this);
    QAction* action_hide = new QAction(QString::fromUtf8("Réduire"), this);
    QAction* action_about = new QAction(QString::fromUtf8("A propos de QOpenConvert"), this);
    QAction* action_close = new QAction(QString::fromUtf8("Fermer QOpenConvert"), this);

    connect(action_show, SIGNAL(triggered()), this, SLOT(showWindow()));
    connect(action_hide, SIGNAL(triggered()), this, SLOT(hideWindow()));
    connect(action_close, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(action_about, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


    menu->addAction(action_show);
    menu->addAction(action_hide);
    menu->addAction(action_about);
    menu->addAction(action_close);

    tray_icon->setContextMenu(menu);

    QIcon image = QIcon(":/images/icon.png");
    tray_icon->setIcon(image);

    tray_icon->show();
}


/**
 * Méthode interceptant l'événement de fermeture de la fenêtre
 *
 * @param  QCloseEvent*     event   l'événement intercepté
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::closeEvent(QCloseEvent *event)
{
    if (tray_icon->isVisible()) {
        hideWindow();
        event->ignore();
    }
}


/**
 * SLOT pour afficher la fenêtre principale
 *
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::showWindow()
{
    this->show();
    this->setWindowState(Qt::WindowActive);
}


/**
 * SLOT pour cacher la fenêtre principale
 *
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::hideWindow()
{
    this->hide();
    this->setWindowState(Qt::WindowMinimized);
}

/**
 * SLOT pour l'affichage du About
 *
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::showAbout()
{
    showWindow();
    About* w = new About(this);
    w->show();
}


/**
 * SLOT de gestion du clic sur l'icône de la zone de notification
 * double-clic : on affiche ou on cache selon l'état actuel
 * simple-clic gauche : on affiche au premier place si l'état n'est pas hidden
 *
 * @param  QSystemTrayIcon::ActivationReason   reason     l'objet ActivationReason intercepté par le SIGNAL
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::DoubleClick:
            if (this->isHidden()) {
                showWindow();
            } else {
                hideWindow();
            }
            break;
        default:
            ;
    }
}
