#include "treeitem.h"

TreeItem::TreeItem(const QVariant &data, TreeItem *parent)
{
    this->parentItem = parent;
    if (parent)
        parent->appendChild(this);
    this->itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(this->childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
    this->childItems.append(child);
}

void TreeItem::removeChild(TreeItem *child)
{
    if (this->childItems.contains(child))
        this->childItems.removeOne(child);
}

void TreeItem::setParent(TreeItem *newParent)
{
    // The function used to manipulate child-parent relations
    if (this->parentItem)
        this->parentItem->removeChild(this);
    this->parentItem = newParent;
    if (newParent)
        newParent->appendChild(this);
}

int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

TreeItem *TreeItem::getChild(int n)
{
    return this->childItems.value(n);
}

int TreeItem::getChildCount() const
{
    return this->childItems.count();
}

int TreeItem::columnCount() const
{
    // Single-item tree
    return 1;
}

QVariant TreeItem::getData() const
{
    return this->itemData;
}

TreeItem *TreeItem::getParent()
{
    return this->parentItem;
}
