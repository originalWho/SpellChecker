#include "filehelper.h"
#include <QFileDialog>
#include <QTextStream>

FileHelper * FileHelper::instance = 0;
FileHelperDestroyer FileHelper::destroyer;

FileHelperDestroyer::~FileHelperDestroyer()
{
    delete instance;
}

void FileHelperDestroyer::initializeFileHelper(FileHelper *_instance)
{
    instance = _instance;
}

FileHelper &FileHelper::getInstance()
{
    if (!instance)
    {
        instance = new FileHelper();
        destroyer.initializeFileHelper(instance);
    }
    return *instance;
}

void FileHelper::openDictionary()
{

}

void FileHelper::importDictionary(bool &imported)
{

    QString fileName = QFileDialog::getOpenFileName(0, "Import a Dictionary", "", "Text documents (*.txt)");
    if (fileName != "")
    {
        QFile file(fileName);
        HashTable *dictionary = new HashTable;
        QString id = "English";
        dictionary->setId(id);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString value = in.readLine();
            dictionary->addWord(value);
        }

        dictionaries.insert(id, dictionary);
        HashTable::incDictionaryCount();
        emit addDictionary(id);

        imported = true;
    }
}

void FileHelper::saveDictionary(bool &saved)
{
    saved = true;
}

void FileHelper::openTextFile()
{
    QString file_name = QFileDialog::getOpenFileName(0, "Open a Text File", "", "Text documents (*.txt)");
    if (file_name != "")
    {
        QFile file (file_name);
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        QString str = stream.readAll();
        returnTextFile(str);
    }

}

void FileHelper::saveTextFile(QString &)
{

}

void FileHelper::saveAsTextFile(QString &)
{

}

HashTable *FileHelper::getDictionary(QString &id) const
{
    if (dictionaries.size() != 0)
        return dictionaries.value(id);
    return NULL;
}

