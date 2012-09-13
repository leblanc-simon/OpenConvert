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

#include "about.h"
#include "ui_about.h"
#include "version.h"
#include "QString"

/**
 * Constructeur
 */
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->init();
}

/**
 * Destructeur
 */
About::~About()
{
    delete ui;
}

/**
 * Initialisation des SIGNAL et remplacement du numéro de version
 * Si l'application est compilée avec l'option -DPORTAILPRO
 * on remplace le nom de l'auteur et le site web
 *
 * @return void
 * @since  1.0.0
 */
void About::init()
{
    QObject::connect(this->ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    QObject::connect(this->ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    // On applique le numero de version
    this->ui->label->setText(this->ui->label->text().replace(QString("%%VERSION%%"), QString(VER_PRODUCTVERSION_STR)));
}
