// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2023 The Dinartether Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DINARTETHER_QT_ASSETCONTROLTREEWIDGET_H
#define DINARTETHER_QT_ASSETCONTROLTREEWIDGET_H

#include <QKeyEvent>
#include <QTreeWidget>

class AssetControlTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit AssetControlTreeWidget(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // DINARTETHER_QT_ASSETCONTROLTREEWIDGET_H
