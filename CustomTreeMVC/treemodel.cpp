#include "treemodel.h"

TreeModel::TreeModel(QList<QVariant> &items, QList<QPair<QVariant, QVariant>> &hierarchy, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVariant rootData;
    QHash<QString, TreeItem*> data;
    // Create root point
    rootData = "Tree View";
    rootItem = new TreeItem(rootData);
    // Initializing data
    for (auto item : items)
    {
        data.insert(item.toString(), new TreeItem(item, rootItem));
    }
    // Applying hierarchy
    for (auto pair : hierarchy)
    {
        data.value(pair.second.toString())->setParent(data.value((pair.first.toString())));
    }
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->getData();

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    // Row defines child position in childItems
    TreeItem *childItem = parentItem->getChild(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    // Default parent is root
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->getParent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    // Same as child count
    TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->getChildCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->getData();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    // Items are not editable
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
