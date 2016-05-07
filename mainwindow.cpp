#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    autoCorrectionLabel = ui->autoCorrectLabel;
    autoCorrectionLabel->setStyleSheet("color:grey");
    actionButton = ui->actionButton;
    textEdit = ui->textEdit;
    textEdit->setContextMenuPolicy(Qt::CustomContextMenu);

    textChecked = false;
    textCorrected = false;

    if (HashTable::getDictionaryCount() == 0)
    {
        actionButton->setText("Upload a Dictionary");
    }

    createActions();
    createMenu();

    connect(textEdit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(autoCorrectAct, SIGNAL(toggled(bool)), this, SLOT(enableAutoCorrection(bool)));
    connect(this, SIGNAL(checkText(QTextDocument&)), &TextHelper::getInstance(), SLOT(checkText(QTextDocument&)));
    connect(this, SIGNAL(correctText(QTextDocument&)), &TextHelper::getInstance(), SLOT(correctText(QTextDocument&)));
    connect(this, SIGNAL(importDictionary(bool&)), &FileHelper::getInstance(), SLOT(importDictionary(bool&)));
    connect(this, SIGNAL(openTextFile()), &FileHelper::getInstance(), SLOT(openTextFile()));
    connect(this, SIGNAL(saveTextFile(QString&)), &FileHelper::getInstance(), SLOT(saveTextFile(QString&)));
    connect(this, SIGNAL(saveAsTextFile(QString&)), &FileHelper::getInstance(), SLOT(saveAsTextFile(QString&)));
    connect(&FileHelper::getInstance(), SIGNAL(returnTextFile(QString&)), this, SLOT(setTextFile(QString&)));
    connect(&FileHelper::getInstance(), SIGNAL(addDictionary(QString&)), this, SLOT(addDictionary(QString&)));
    connect(this, SIGNAL(getSelectedDict(QString&)), &TextHelper::getInstance(), SLOT(setSelectedDict(QString&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(_openTextFile()));

    saveAct = new QAction(tr("Save"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(_saveTextFile()));

    saveAsAct = new QAction(tr("Save As..."), this);
    saveAsAct->setShortcut(tr("Shift+Ctrl+S"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(_saveAsTextFile()));

    autoCorrectAct = new QAction(tr("Autocorrection"), this);
    autoCorrectAct->setShortcut(tr("Shift+Ctrl+C"));
    autoCorrectAct->setCheckable(true);

    importDictAct = new QAction(tr("Import a Dictionary..."), this);
    importDictAct->setShortcut(tr("Shift+Ctrl+D"));
    connect(importDictAct, SIGNAL(triggered()), this, SLOT(_importDictionary()));

    dictGroup = new QActionGroup(this);
    dictGroup->setExclusive(true);
    //connect(dictGroup, SIGNAL(triggered(QAction*)), this, SLOT(_getSelectedDict(QAction*)));

    removeDictAct = new QAction(tr("Remove a Dictionary..."), this);
    removeDictAct->setShortcut(tr("Shift+Ctrl+R"));

    helpAct = new QAction(tr("Application Help"), this);
    helpAct->setShortcut(tr("F1"));

    statAct = new QAction(tr("Statistics"), this);
    statAct->setShortcut(tr("F2"));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(autoCorrectAct);

    dictMenu = menuBar()->addMenu(tr("&Dictionary"));
    dictMenu->addAction(importDictAct);
    dictMenu->addAction(removeDictAct);
    dictMenu->addSeparator()->setText(tr("Dictionaries"));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addSeparator();
    helpMenu->addAction(statAct);
}

void MainWindow::showContextMenu(const QPoint &point)
{
    QMenu *menu = textEdit->createStandardContextMenu();

    if (textChecked)
    {
        QTextCursor cursor = textEdit->textCursor();
        cursor.select(QTextCursor::WordUnderCursor);
        QString word = cursor.selectedText();
        cursor.clearSelection();
        QList<QString> *list = TextHelper::getInstance().getSuggestions(word);
        if (list != NULL && list->size() > 0)
        {
            menu->addSeparator();
            foreach(QString str, *list)
            {
                QAction *action = menu->addAction(str);
                connect(action, SIGNAL(triggered()), this, SLOT(replaceWord()));
            }
        } else {
            QAction *action = new QAction(tr("No suggestions available"), this);
            action->setEnabled(false);
            menu->addAction(action);
        }
    }

    menu->exec(textEdit->mapToGlobal(point));
    delete menu;
}

void MainWindow::replaceWord()
{
    QAction *action = (QAction *) sender();
    QTextCursor textCursor = textEdit->textCursor();
    textCursor.select(QTextCursor::WordUnderCursor);
    textCursor.removeSelectedText();
    textCursor.insertText(action->text());
    textChecked = true;
}

void MainWindow::enableAutoCorrection(bool enabled)
{
    if (enabled)
        autoCorrectionLabel->setText("Autocorrection enabled");
    else
        autoCorrectionLabel->setText("");
}

void MainWindow::on_textEdit_textChanged()
{
    if (HashTable::getDictionaryCount() != 0)
    {
        bool isEmpty = textEdit->toPlainText().isEmpty();
        if (isEmpty)
        {
            actionButton->setEnabled(false);
        }
        else{
            actionButton->setEnabled(true);
            actionButton->setText("Check");
        }
    }
    textChecked = false;
}

void MainWindow::on_actionButton_clicked()
{

    if (HashTable::getDictionaryCount() == 0)
    {
        bool imported = false;
        emit importDictionary(imported);
        if (imported)
        {
            HashTable::incDictionaryCount();
            actionButton->setText("Check");
            if (textEdit->toPlainText().isEmpty())
                actionButton->setEnabled(false);
        }
    }
    else
    {
        QTextDocument *textDocument = textEdit->document();
        if (textChecked)
        {
            if (textCorrected)
            {
                QClipboard *clipBoard = QApplication::clipboard();
                clipBoard->setText(textEdit->toPlainText());
            }
            else
            {
                emit correctText(*textDocument);
                actionButton->setText("Copy");
            }
        }
        else
        {
            emit checkText(*textDocument);
            textChecked = true;

            /* Autocorrection
            if (autoCorrectAct->isChecked())
            {
                emit correctText(*textDocument);
                actionButton->setText("Copy");
            }
            else
            {
                actionButton->setText("Correct All");
            }
            */
        }
    }
}

void MainWindow::setTextFile(QString &text)
{
    textEdit->clear();
    textEdit->setText(text);
}

void MainWindow::_openTextFile()
{
    emit openTextFile();
}

void MainWindow::_saveTextFile()
{
    QString text = textEdit->toPlainText();
    emit saveTextFile(text);
}

void MainWindow::_saveAsTextFile()
{
    QString text = textEdit->toPlainText();
    emit saveAsTextFile(text);
}

void MainWindow::_importDictionary()
{
    bool imported = false;
    emit importDictionary(imported);
}

void MainWindow::_saveDictionary()
{
    bool saved = false;
    emit saveDictionary(saved);
}

void MainWindow::_getSelectedDict(QAction *action)
{
    QString id = action->text();
    emit getSelectedDict(id);
}

void MainWindow::addDictionary(QString &id)
{
    QAction *action = new QAction(id, this);
    action->setCheckable(true);
    action->setChecked(true);
    emit getSelectedDict(id);
    dicts.push_back(action);
    dictMenu->addAction(dicts[dicts.size() - 1]);
}
