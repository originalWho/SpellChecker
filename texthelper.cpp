#include "texthelper.h"

#include <QMessageBox>

TextHelper * TextHelper::instance = 0;
TextHelperDestroyer TextHelper::destroyer;

TextHelperDestroyer::~TextHelperDestroyer()
{
    delete instance;
}

void TextHelperDestroyer::initialize(TextHelper *_instance)
{
    instance = _instance;
}

void TextHelper::setSelectedDict(QString &dict)
{
    selectedDict = dict;
    hashTable = FileHelper::getInstance().getDictionary(selectedDict);
}

bool TextHelper::isCorrect(QString &word)
{
    if (hashTable)
        return hashTable->contains(word);
    return true;
}

int TextHelper::hammingDistance(QString &word1, QString &word2) const
{
    if (word1.length() != word2.length())
        return -1;
    else {
        int distance = 0;
        for (int i = 0; i < word1.length() && distance < 2; i++)
            if (word1.at(i) != word2.at(i))
                distance++;
        return distance;
    }
}

void TextHelper::checkWord(QTextCursor *cursor)
{
    cursor->select(QTextCursor::WordUnderCursor);
    QString word = cursor->selectedText();
    if (!isCorrect(word) && word.length() > 2)
    {
        QTextCharFormat charFormat = cursor->charFormat();
        charFormat.setUnderlineColor(QColor(Qt::red));
        charFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        cursor->setCharFormat(charFormat);
    }
    cursor->clearSelection();
    QTextCharFormat charFormat = cursor->charFormat();
    charFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
    cursor->setCharFormat(charFormat);
}

TextHelper &TextHelper::getInstance()
{
    if (!instance)
    {
        instance = new TextHelper();
        destroyer.initialize(instance);
    }
    return *instance;
}

QList<QString> *TextHelper::getSuggestions(QString &word)
{
    QList<QString> *suggestions = new QList<QString>;
    if (hashTable)
    {
        QList<QString> dictionary = hashTable->getWords(word.length());
        if (dictionary.count() != 0){
            for (int i = 0; i < dictionary.count() && suggestions->count() < 5; i++){
                QString wordDict = dictionary.at(i);
                int distance = hammingDistance(word, wordDict);
                if (distance > -1 && distance < 2)
                    suggestions->append(wordDict);
            }
        }
    }
    return suggestions;
}

void TextHelper::checkText(QTextDocument &text)
{
    QTextCursor textCursor(&text);
    while (!textCursor.atEnd())
    {
        checkWord(&textCursor);
        textCursor.movePosition(QTextCursor::NextWord);
    }
}

void TextHelper::correctText(QTextDocument &text)
{
    QTextCursor textCursor(&text);
}


