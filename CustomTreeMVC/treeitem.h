#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>



class TreeItem
{
public:
    TreeItem(const QVariant &data, TreeItem *parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);
    void removeChild(TreeItem *child);
    void setParent(TreeItem *newParent);

    TreeItem *getChild(int n);
    int row() const;
    int getChildCount() const;
    int columnCount() const;
    QVariant getData() const;
    TreeItem *getParent();

private:
    QList<TreeItem*> childItems;
    QVariant itemData;
    TreeItem *parentItem;
};

#endif // TREEITEM_H
