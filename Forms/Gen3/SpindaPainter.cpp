/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2019 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "SpindaPainter.hpp"
#include "ui_SpindaPainter.h"

SpindaPainter::SpindaPainter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpindaPainter)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    setupModels();
}

SpindaPainter::~SpindaPainter()
{
    delete ui;
}

void SpindaPainter::setupModels()
{
    ui->textBoxPID->setValues(InputType::Seed32Bit);

    scene = new QGraphicsScene(ui->graphicsView);
    connect(scene, &QGraphicsScene::changed, this, &SpindaPainter::updatePID);
    ui->graphicsView->setScene(scene);

    spinda = new QGraphicsPixmapItem(QPixmap(":/images/spinda.png"));
    spot1 = new GraphicsPixmapItem(QPixmap(":/images/spinda_spot1"));
    spot2 = new GraphicsPixmapItem(QPixmap(":/images/spinda_spot2"));
    spot3 = new GraphicsPixmapItem(QPixmap(":/images/spinda_spot3"));
    spot4 = new GraphicsPixmapItem(QPixmap(":/images/spinda_spot4"));

    spot1->setFlag(QGraphicsItem::ItemIsMovable);
    spot1->setMin(64, 48);
    spot1->setMax(184, 168);

    spot2->setFlag(QGraphicsItem::ItemIsMovable);
    spot2->setMin(256, 56);
    spot2->setMax(376, 176);

    spot3->setFlag(QGraphicsItem::ItemIsMovable);
    spot3->setMin(112, 192);
    spot3->setMax(232, 312);

    spot4->setFlag(QGraphicsItem::ItemIsMovable);
    spot4->setMin(208, 200);
    spot4->setMax(328, 320);

    scene->addItem(spinda);
    scene->addItem(spot1);
    scene->addItem(spot2);
    scene->addItem(spot3);
    scene->addItem(spot4);
}

void SpindaPainter::moveSpot(GraphicsPixmapItem *item, int index)
{
    int x = (pid >> (index * 8)) & 0xf;
    int y = (pid >> (index * 8 + 4)) & 0xf;

    x += coords[2 * index] + origin[0];
    y += coords[2 * index + 1] + origin[1];

    item->setPos(x * 8, y * 8);
}

void SpindaPainter::updateInfo()
{
    QString info = Nature::getNature(pid % 25) + ", ";
    info += QString((pid & 0xff) > 126 ? "♂" : "♀") + ", ";
    info += QString((pid & 1) == 0 ? tr("Ability 0") : tr("Ability 1"));
    ui->labelInfo->setText(info);
}

void SpindaPainter::on_textBoxPID_textEdited(const QString &arg1)
{
    u32 newPID = arg1.toUInt(nullptr, 16);

    if (pid != newPID)
    {
        pid = newPID;
        updateInfo();

        text = true;
        moveSpot(spot1, 0);
        moveSpot(spot2, 1);
        moveSpot(spot3, 2);
        moveSpot(spot4, 3);
    }
}

void SpindaPainter::updatePID(const QList<QRectF> & /*region*/)
{
    if (!text)
    {
        QVector<qreal> pos;
        pos.append(spot1->x());
        pos.append(spot1->y());
        pos.append(spot2->x());
        pos.append(spot2->y());
        pos.append(spot3->x());
        pos.append(spot3->y());
        pos.append(spot4->x());
        pos.append(spot4->y());

        pid = 0;
        for (u8 i = 0; i < 4; i++)
        {
            u32 left = static_cast<u32>(pos[i * 2] / 8) - coords[2 * i] - origin[0];
            u32 right = static_cast<u32>(pos[i * 2 + 1] / 8) - coords[2 * i + 1] - origin[1];

            pid |= (left << (28 - i * 8));
            pid |= (right << (24 - i * 8));
        }

        ui->textBoxPID->setText(QString::number(pid, 16));
        updateInfo();
    }
    else
    {
        text = false;
    }
}