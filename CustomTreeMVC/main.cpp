#include "treemodel.h"
#include "treemodel.h"
#include <QApplication>
#include <QFileSystemModel>
#include <QSplitter>
#include <QTreeView>

int main(int argc, char *argv[])
{
    // App set-up
    QApplication app(argc, argv);

    // Prepare data
    QList<QVariant> fullList({1, 2, 3, 4, 10, 11, 111, 20, 31, 32});
    QList<QPair<QVariant, QVariant>> dependList({{1, 11}, {2, 20}, {3, 31}, {3, 32}, {11, 111}});

    // Model
    TreeModel *model = new TreeModel(fullList, dependList);

    // QTreeView
    QTreeView view;
    view.setModel(model);
    view.setWindowTitle("Custom Tree Model");
    view.show();

    return app.exec();
}
