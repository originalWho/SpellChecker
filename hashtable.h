#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QMultiHash>
#include <QObject>
/**
 * @brief The HashTable class It is a container for dictionaries
 */
class HashTable:public QObject
{
private:
    Q_OBJECT
    /**
     * @brief dictionaryCount Number of available dictionaries
     */
    static int dictionaryCount;
    /**
     * @brief id Name (id) of a dictionary (hashtable)
     */
    QString id;
    /**
     * @brief words Container of words. Key is words' length, value is a QList of words of a certain length
     */
    QMultiHash<int, QString> words;

public:
    HashTable();
    ~HashTable();

    /**
     * @brief getDictionaryCount
     * @return dictionaryCount Number of imported dictionaries
     */
    static inline int getDictionaryCount() {return dictionaryCount;}

    /**
     * @brief setDictionaryCount Set exact number of imported dictionaries
     * @param value Number of dictionaries
     */
    static inline void setDictionaryCount(int value) {dictionaryCount = value;}

    /**
     * @brief incDictionaryCount Increase number of imported dictionaries by one
     */
    static inline void incDictionaryCount() {dictionaryCount++;}

    /**
     * @brief decDictionaryCount Decrease number of imported dictionaries by one
     */
    static inline void decDictionaryCount() {dictionaryCount--;}

    /**
     * @brief setId Set name (id) of a hashtable
     * @param _id Name of a hashtable
     */
    inline void setId(const QString &_id) {id = _id;}

    /**
     * @brief getId Returns name (id) of a hashtable
     * @return Name of a hashtable
     */
    inline QString getId() const {return id;}

    /**
     * @brief addWord Add a custom word to a dictionary
     * @param word A custom word
     */
    inline void addWord(const QString &word) {words.insert(word.length(), word);}

    /**
     * @brief getSize Returns hashtable size (count of words)
     * @return Size
     */
    inline int getSize() const {return words.size();}

    /**
     * @brief contains Check if certain word is in a dictionary (hashtable)
     * @param word A word
     * @return True, if a word is in a dictionary (hashtable)
     */
    inline bool contains(const QString &word) const {return words.contains(word.length(), word);}

    /**
     * @brief isEmpty Checks if dictionary(hashtable) is empty
     * @return True, if a dictionary (hashtable) is empty
     */
    inline bool isEmpty() const {return words.isEmpty();}

    /**
     * @brief getWords Returns all the values (words) associated with a key (word's length)
     * @param key Word's length
     * @return Words of a certain length
     */
    QList<QString> getWords(int key) const;

};

#endif // HASHTABLE_H
