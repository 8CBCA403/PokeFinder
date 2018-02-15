#include "Profile3Model.hpp"

Profile3Model::Profile3Model(QObject *parent) : QAbstractTableModel(parent)
{
}

void Profile3Model::setModel(vector<Profile3> profiles)
{
    model = profiles;
}

void Profile3Model::addItem(Profile3 profile)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i);
    model.push_back(profile);
    emit endInsertRows();
}

void Profile3Model::updateProfile(Profile3 profile, int row)
{
    model[row] = profile;
}

int Profile3Model::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return (int)model.size();
}

int Profile3Model::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 6;
}

QVariant Profile3Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();
        Profile3 profile = model[row];
        switch (column)
        {
            case 0:
                return profile.profileName;
            case 1:
                return profile.getVersion();
            case 2:
                return profile.getLanguage();
            case 3:
                return profile.tid;
            case 4:
                return profile.sid;
            case 5:
                if (profile.version == 0 || profile.version == 1)
                {
                    return profile.deadBattery ? tr("Yes") : tr("No");
                }
                else
                {
                    return "N/A";
                }
        }
    }
    return QVariant();
}

QVariant Profile3Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return tr("Profile Name");
                case 1:
                    return tr("Version");
                case 2:
                    return tr("Language");
                case 3:
                    return tr("TID");
                case 4:
                    return tr("SID");
                case 5:
                    return tr("Dead Battery");
            }
        }
    }
    return QVariant();
}

Profile3 Profile3Model::getProfile(int index)
{
    return model[index];
}

void Profile3Model::removeProfile(int index)
{
    model.erase(model.begin() + index);
}
