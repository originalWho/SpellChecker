#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QMap>
#include <QObject>
#include "hashtable.h"

/**
 * @brief Singleton class FileHelper is responsible for processing text files
 */
class FileHelper;

class FileHelperDestroyer
{
private:
    FileHelper *instance;
public:
    ~FileHelperDestroyer();
    void initializeFileHelper(FileHelper *);
};

class FileHelper: public QObject
{
private:
    Q_OBJECT
    static FileHelper *instance;
    static FileHelperDestroyer destroyer;
    /**
     * @brief dictionaries Contains information about available dictionaries.
     * Key - is name (id) of a dictionary, value - is a dictionary
     */
    QMap<QString, HashTable *> dictionaries;
protected:
    FileHelper() {}
    FileHelper(const FileHelper &);
    FileHelper& operator=(FileHelper &);
    ~FileHelper() {}
    friend class FileHelperDestroyer;

public:
    static FileHelper& getInstance();

public slots:
    /**
     * @brief openDictionary Opens every dictionary imported to operating folder of program at its start
     * Connected to openDictionary (MainWindow)
     */
    void openDictionary();

    /**
     * @brief importDictionary Imports a custom dictionary (text file), creates a hashtable, fills it with imported words.
     * @param bool flag. True, if import was successful
     * Key of hashtable is a word's length, value is imported words.
     * Saves it to operating folder.
     * Connected to importDictionary (MainWindow)
     */
    void importDictionary(bool &);

    /**
     * @brief saveDictionary Saves a dictionary into operating folder
     * @param bool flag. True, if save was successful
     * Connected to saveDictionary (MainWindow)
     */
    void saveDictionary(bool &);

    /**
     * @brief openTextFile Opens a text file, loads text in textEdit widget
     * Connected to openTextFile (MainWindow)
     */
    void openTextFile();

    /**
     * @brief saveTextFile Saves text from textEdit widget to the same text file, which was opened earlier
     * @param Text (QString) from textEdit widget
     * Connected to saveTextFile (MainWindow)
     */
    void saveTextFile(QString &);

    /**
     * @brief saveAsTextFile Saves text from textEdit widget to a separate text file
     * @param Text (QString) from textEdit widget
     * Connected to saveAsTextFile (MainWindow)
     */
    void saveAsTextFile(QString &);

    /**
     * @brief getDictionary Returns a certain dictionray
     * @param id Name (id) of a dictionary
     * @return Dictionary (hashtable)
     * Connected to getDictionary (MainWindow)
     */
    HashTable *getDictionary(QString &id) const;
signals:
    /**
     * @brief returnTextFile Passes text (QString) from a text file to MainWindow
     * @param Text (QString) from a text file
     * Connected to setTextFile (MainWindow)
     */
    void returnTextFile(QString &);
    /**
     * @brief addDictionary Passes name (id) of an imported dictionary to MainWindow
     * @param Name (id) of an imported dictionary
     * Connected to addDictionary (MainWindow)
     */
    void addDictionary(QString &);
};


#endif // FILEHELPER_H
