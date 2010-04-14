#include "CREReportDefinition.h"

CREReportDefinition::CREReportDefinition()
{
}

CREReportDefinition::CREReportDefinition(const CREReportDefinition& other) : QObject()
{
    setName(other.name());
    setHeader(other.header());
    setItemSort(other.itemSort());
    setItemDisplay(other.itemDisplay());
}

CREReportDefinition::~CREReportDefinition()
{
}

const QString& CREReportDefinition::name() const
{
    return myName;
}

void CREReportDefinition::setName(const QString& name)
{
    myName = name;
}

const QString& CREReportDefinition::header() const
{
    return myHeader;
}

void CREReportDefinition::setHeader(const QString& header)
{
    myHeader = header;
}

const QString& CREReportDefinition::itemSort() const
{
    return myItemSort;
}

void CREReportDefinition::setItemSort(const QString& sort)
{
    myItemSort = sort;
}

const QString& CREReportDefinition::itemDisplay() const
{
    return myItemDisplay;
}

void CREReportDefinition::setItemDisplay(const QString& display)
{
    myItemDisplay = display;
}

const QString& CREReportDefinition::footer() const
{
    return myFooter;
}

void CREReportDefinition::setFooter(const QString& footer)
{
    myFooter = footer;
}
