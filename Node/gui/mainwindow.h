#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include "node.h"
#include <blockscene.h>
#include <QToolBox>
#include <QButtonGroup>
#include <blockitem.h>
#include <QTextEdit>
#include <QSpinBox>
#include "mygraphicsview.h"


class BlockScene;
class Node;
class MyGraphicsView;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    void createToolBox();
    void createFileMenu();
    void createActions();
    void createToolbars();
    void ioBox(BlockItem::BlockType type, int in, int out);

    QWidget *createCellWidget(const QString &text,
                              BlockItem::BlockType type);

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;

    QGraphicsView *view;
    MyGraphicsView *mView;
    Node *node;
    BlockScene *blockScene;
    QVBoxLayout *vbLayOutProp;

    QMenu *fileMenu;
    QMenu *itemMenu;


    QAction *runAction;
    QAction *stopAction;
    QAction *deleteAction;
    QAction *saveAction;
    QAction *openAction;
    QAction *defaultAction;

    QToolBar *editToolBar;
    QToolBar *runToolBar;
    QToolBar *stopToolBar;

    QTextEdit *teOuts;

    QLabel *lblIns, *lblOuts;

    QSpinBox *sbIns, *sbOuts;

    QHBoxLayout *hbIO;
    QGroupBox *gbIO;

    int vScrolInitVal, hScrolInitVal;

     QTableWidget * tableWidget;



public slots:
    void buttonGroupClicked(int id);
    void itemInserted(BlockItem *item);
    void run();
    void stop();
    void deleteItem();
    void updateTEOuts(QString strOut);
    void save();
    void open();
    void setDefault();
};

#endif // MAINWINDOW_H
