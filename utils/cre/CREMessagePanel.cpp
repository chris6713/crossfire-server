#include <QtGui>
#include "CREMessagePanel.h"
#include "CREFilterDefinition.h"
#include "MessageFile.h"

CREMessagePanel::CREMessagePanel()
{
    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("Location:"), this), 0, 0);
    myLocation = new QLineEdit(this);
    layout->addWidget(myLocation, 0, 1);

    QGroupBox* box = new QGroupBox(tr("Rules"));
    layout->addWidget(box, 1, 0, 1, 2);

    QGridLayout* rules = new QGridLayout();
    box->setLayout(rules);

    myRules = new QTreeWidget();
    rules->addWidget(myRules, 0, 0, 4, 1);
    QStringList labels;
    labels << tr("match") << tr("pre") << tr("message") << tr("post") << tr("replies") << tr("include");
    myRules->setHeaderLabels(labels);
    connect(myRules, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));

    myMessage = NULL;
}

CREMessagePanel::~CREMessagePanel()
{
}

QString toDisplay(const QList<QStringList>& list)
{
    QStringList data;
    foreach(QStringList item, list)
        data.append(item.join(" "));
    return data.join("\n");
}

void CREMessagePanel::setMessage(MessageFile* message)
{
    myLocation->setText(message->location());

    /* so the change handler won't do anything */
    myMessage = NULL;
    myRules->clear();
    myMessage = message;

    foreach(MessageRule* rule, myMessage->rules())
    {
        QStringList data;
        data << rule->match().join("\n");
        data << toDisplay(rule->preconditions());
        data << rule->messages().join("\n");
        data << toDisplay(rule->postconditions());
        data << toDisplay(rule->replies());
        data << rule->include();
        new QTreeWidgetItem(myRules, data);
    }

    if (myRules->topLevelItemCount() != 0)
        myDefaultBackground = myRules->topLevelItem(0)->background(0);
}

void setBackgroundColor(QTreeWidgetItem* item, QBrush color)
{
    for (int c = 0; c < item->columnCount(); c++)
        item->setBackground(c, color);
}

void CREMessagePanel::currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* /*previous*/)
{
    if (!myMessage || myRules->topLevelItemCount() == 0)
        return;

    for (int r = 0; r < myMessage->rules().size(); r++)
    {
        setBackgroundColor(myRules->topLevelItem(r), myDefaultBackground);
    }

    int index = myRules->indexOfTopLevelItem(current);
    if (index < 0 || index >= myMessage->rules().size())
        return;

    MessageRule* rule = myMessage->rules()[index];

    foreach(QStringList pre, rule->preconditions())
    {
        if (pre.size() < 3)
            continue;

        if (pre[0] != "token")
            continue;

        QStringList acceptable = pre;
        acceptable.removeFirst();
        acceptable.removeFirst();

        for (int c = 0; c < myMessage->rules().size(); c++)
        {
            MessageRule* check = myMessage->rules()[c];

            if (check == rule)
                continue;

            bool match = false;
            foreach(QStringList post, check->postconditions())
            {
                if (post.size() < 3)
                    continue;
                if (post[0] != "settoken" || post[1] != pre[1] || !acceptable.contains(post[2]))
                    continue;
                match = true;
                break;
            }

            if (match)
                setBackgroundColor(myRules->topLevelItem(c), Qt::red);
        }
    }

    foreach(QStringList post, rule->postconditions())
    {
        if (post.size() < 3)
            continue;

        if (post[0] != "settoken")
            continue;

        for (int c = 0; c < myMessage->rules().size(); c++)
        {
            MessageRule* check = myMessage->rules()[c];

            if (check == rule)
                continue;

            bool match = false;
            foreach(QStringList pre, check->preconditions())
            {
                if (pre.size() < 3)
                    continue;
                if (pre[0] != "token" || pre[1] != post[1])
                    continue;

                QStringList acceptable = pre;
                acceptable.removeFirst();
                acceptable.removeFirst();
                if (!acceptable.contains(post[2]))
                    continue;

                match = true;
                break;
            }

            if (match)
                setBackgroundColor(myRules->topLevelItem(c), Qt::blue);
        }
    }
}