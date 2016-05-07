#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QTextDocument>
#include <QActionGroup>
#include "filehelper.h"
#include "texthelper.h"
#include "hashtable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /**
     * @brief autoCorrectionLabel Text label which indicates if autocorrection is enabled
     */
    QLabel *autoCorrectionLabel;
    /**
     * @brief fileMenu, dictMenu, helpMenu are drop-down menus in menuBar
     */
    QMenu *fileMenu;
    QMenu *dictMenu;
    QMenu *helpMenu;
    /**
     * @brief openAct, saveAct, saveAsAct are actions in fileMenu to operate with text files
     */
    QAction *openAct; //Ctrl + O
    QAction *saveAct; //Ctrl + S
    QAction *saveAsAct; //Ctrl + Shift + S
    /**
     * @brief autoCorrectAct Checkable option in fileMenu which enables autocorrection
     */
    QAction *autoCorrectAct; //Ctrl + Shift + C
    /**
     * @brief importDictAct, removeDictAct are actions in dictMenu to operate with dictionaries
     */
    QAction *importDictAct; //Ctrl + Shift + D
    QAction *removeDictAct; //Ctrl + Shift + R
    /**
     * @brief statAct Opens a new window with text's statistics
     */
    QAction *statAct; //F2
    /**
     * @brief helpAct Help
     */
    QAction *helpAct; //F1
    /**
     * @brief dictGroup Separated list of available dictionaries in dictMenu
     */
    QActionGroup *dictGroup;
    /**
     * @brief actionButton The action button of universal purposes in MainWindow
     */
    QPushButton *actionButton;
    /**
     * @brief textEdit TextEdit widget
     */
    QTextEdit *textEdit;
    /**
     * @brief dicts List of available dictionaries to display in dictGroup
     */
    QVector<QAction *> dicts;

    /**
     * @brief createActions Creates actions, assignes shortcuts and connects to slots
     */
    void createActions();
    /**
     * @brief createMenu Creates menu in menuBar, asssignes actions to menus
     */
    void createMenu();

    /**
     * @brief textChecked True, if text is checked
     */
    bool textChecked;

    /**
     * @brief textCorrected True, if text if corrected
     */
    bool textCorrected;

signals:
    /**
     * @brief importDictionary Import a dictionary was clicked
     * Connected to importDicitonary (FileHelper)
     */
    void importDictionary(bool &);
    /**
     * @brief saveDictionary Save a dictionary was clicked
     * Connected to saveDictionary (FileHelper)
     */
    void saveDictionary(bool &);
    /**
     * @brief checkText Check was clicked
     * Passes text from textEdit widget
     * Connected to checkText (TextHelper)
     */
    void checkText(QTextDocument &);
    /**
     * @brief correctText Correct All was clicked
     * Passes text from textEdit widget
     */
    void correctText(QTextDocument &);
    /**
     * @brief openTextFile Open... was clicked
     * Connected to openTextFile (FileHelper)
     */
    void openTextFile();
    /**
     * @brief saveTextFile Save was clicked
     * Passes text from textEdit widget
     * Connected to saveTextFile (FileHelper)
     */
    void saveTextFile(QString &);
    /**
     * @brief saveAsTextFile Save As... was clicked
     * Passes text from textEdit widget
     * Connected to saveAsTextFile (FileHelper)
     */
    void saveAsTextFile(QString &);
    /**
     * @brief getSelectedDict Set selected dictionary
     * Passes name (id) of a dictionary
     * Connected to setSelectedDict (TextHelper)
     */
    void getSelectedDict(QString &);

private slots:
    /**
     * @brief showContextMenu Shows context menu on a right-button click
     * Passes QPoint (position of mouse)
     */
    void showContextMenu(const QPoint &);
    /**
     * @brief replaceWord Replaces an incorrect word with a word from a suggestions list
     */
    void replaceWord();
    /**
     * @brief enableAutoCorrection Enable or disable autocorrection
     * Passes autoCorrectAct->isChecked()
     */
    void enableAutoCorrection(bool);
    /**
     * @brief on_textEdit_textChanged
     * Set actionButton disabled, if textEdit is empty
     * Set textChecked, textCorrected false, if text is changed
     */
    void on_textEdit_textChanged();
    /**
     * @brief on_actionButton_clicked
     * Uploads a dictionary, if none is available
     * Checks text, if textEdit widget is not empty
     * Corrects text, if text is checked for mistakes and autocorrection is not enabled
     * Copies text to clipboard, if text is checked and corrected
     */
    void on_actionButton_clicked();
    /**
     * @brief setTextFile Set text in textEdit widget from an opened text file
     * Gets text (QString)
     * Connected to returnTextFile (FileHelper)
     */
    void setTextFile(QString &);
    /**
     * @brief _openTextFile
     * Emits openTextFile()
     */
    void _openTextFile();
    /**
     * @brief _saveTextFile
     * Emits saveTextFile()
     */
    void _saveTextFile();
    /**
     * @brief _saveAsTextFile
     * Emits saveAsTextFile()
     */
    void _saveAsTextFile();
    /**
     * @brief _importDictionary
     * Emits importDictionary()
     */
    void _importDictionary();
    /**
     * @brief _saveDictionary
     * Emits saveDictionary()
     */
    void _saveDictionary();
    /**
     * @brief _getSelectedDict
     * Emits getSelectedDict()
     */
    void _getSelectedDict(QAction *);

public slots:
    /**
     * @brief addDictionary
     * Adds a new dictionary to dictGroup
     * Gets name (id) of a dictionary
     * Connected to addDictionary (FileHelper)
     */
    void addDictionary(QString &);
};

#endif // MAINWINDOW_H
