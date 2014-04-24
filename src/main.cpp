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

#include <QApplication>
#include "QFileInfo"

#include "convertwindow.h"

/**
 * lancement du programme principal
 * @param   int     argc    nombre d'argument
 * @param   char*   argv    ensemble des arguments
 * @return  int             valeur de sortie du programme
 * @since   1.0.0
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConvertWindow w;
    
    w.show();

    return a.exec();
}
