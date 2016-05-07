#ifndef TEXTHELPER_H
#define TEXTHELPER_H

#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include "filehelper.h"
/**
 * Singleton TextHelper class is responsible for processing text from textEdit widget
 */
class TextHelper;

class TextHelperDestroyer
{
private:
    TextHelper *instance;
public:
    ~TextHelperDestroyer();
    void initialize(TextHelper *);
};

class TextHelper: public QObject
{
private:
    Q_OBJECT
    static TextHelper *instance;
    static TextHelperDestroyer destroyer;
    /**
     * @brief checkWord Checks if word is correct
     * @param QTextCursor position
     */
    void checkWord(QTextCursor *);
    /**
     * @brief isCorrect Returns correctness of a word
     * @return True, if a word is correct
     */
    bool isCorrect(QString &);
    /**
     * @brief selectedDict Name (id) of a selected in MainWindow dictionary
     */
    QString selectedDict;
    /**
     * @brief hashTable Selected dictionary
     */
    HashTable *hashTable;
    /**
     * @brief hammingDistance Hamming Distance of a word from text and a word from dictionary
     * @return
     */
    int hammingDistance(QString &, QString &) const;
protected:
    TextHelper() {}
    ~TextHelper() {}
    TextHelper(const TextHelper &);
    TextHelper& operator=(TextHelper &);
    friend class TextHelperDestroyer;

public:
    static TextHelper& getInstance();
    /**
     * @brief getSuggestions for a word from text
     * @param a word
     * @return Suggestions for a word
     */
    QList<QString> * getSuggestions(QString &);

public slots:
    /**
     * @brief checkText Checks if every word from text is correct
     * @param QTextDocument from textEdit widget
     * Connected to checkText (MainWindow)
     */
    void checkText(QTextDocument &);
    /**
     * @brief correctText Corrects every word in text by replacing one with a closest word from suggestions
     * @param QTextDocument from textEdit widget
     * Connected to correctText (MainWindow)
     */
    void correctText(QTextDocument &);
    /**
     * @brief setSelectedDict set selected in MainWindow dictionary
     * @param Name (id) of a dictionary
     * Connected to getSelectedDict (MainWindow)
     */
    void setSelectedDict(QString &);
};

#endif // TEXTHELPER_H
