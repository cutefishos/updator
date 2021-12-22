/*
 * Copyright (C) 2021 CutefishOS Team.
 *
 * Author:     Kate Leet <kate@cutefishos.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "upgradeablemodel.h"

UpgradeableModel *UpgradeableModel::self()
{
    static UpgradeableModel s;
    return &s;
}

UpgradeableModel::UpgradeableModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> UpgradeableModel::roleNames() const
{
    static QHash<int, QByteArray> s_roles;

    if (s_roles.isEmpty()) {
        s_roles.insert(UpgradeableModel::NameRole, QByteArrayLiteral("name"));
        s_roles.insert(UpgradeableModel::VersionRole, QByteArrayLiteral("version"));
    }

    return s_roles;
}

int UpgradeableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_packages.count();
}

QVariant UpgradeableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    PackageInfo info = m_packages.at(index.row());

    switch (role) {
    case UpgradeableModel::NameRole:
        return info.name;
    case UpgradeableModel::VersionRole:
        return info.version;
    default:
        break;
    }

    // FIXME: Implement me!
    return QVariant();
}

void UpgradeableModel::addPackage(const QString &name, const QString &version)
{
    beginInsertRows(QModelIndex(), 0, 0);
    PackageInfo info;
    info.name = name;
    info.version = version;
    m_packages.prepend(info);
    endInsertRows();
}
