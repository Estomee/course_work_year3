#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Имя для общей памяти
    const QString sharedMemoryKey = "course_work_year_3";

    // Создаем объект общей памяти
    QSharedMemory sharedMemory(sharedMemoryKey);

    // Пытаемся присоединиться к общей памяти
    if (!sharedMemory.create(1))
    {
        // Если не удалось создать общую память, значит, приложение уже запущено
        QMessageBox::critical(&w, "Ошибка", "Приложение уже запущено!");
        return 1;
    }


    w.show();

    return a.exec();
}
