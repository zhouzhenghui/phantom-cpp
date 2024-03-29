/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SaveDataCommand.h"
#include "SaveDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/serialization/DataStateBase.h>
/* *********************************************** */
o_registerN((phantom, qt), SaveDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

SaveDataCommand::SaveDataCommand(phantom::serialization::Node* a_pNode, const phantom::data& a_Data)
: UndoCommand()
, m_pDataBase(a_pNode->getDataBase())
, m_uiParentGuid(a_pNode->getGuid())
, m_uiGuid(a_pNode->getDataBase()->getGuid(a_Data))
{
    o_assert(m_pDataBase);
    setName("Save '"+m_pDataBase->getDataAttributeValue(a_Data, "name")+"' ("+boost::lexical_cast<string>((void*)m_uiGuid)+")");
}

SaveDataCommand::~SaveDataCommand()
{

}


//================================================
// Operations
//================================================


void SaveDataCommand::redo()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    if(!d.isNull())
    {
        pParentNode->saveData(d);
        if(m_pDataBase->getDataStateBase())
        {
            pParentNode->saveDataState(d, m_pDataBase->getDataStateBase()->getCurrentStateId());
        }
        pParentNode->saveDataAttributes(d);
        pParentNode->saveIndex();
    }
}

void SaveDataCommand::undo()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    if(!d.isNull())
    {
        pParentNode->saveData(d);
        if(m_pDataBase->getDataStateBase())
        {
            pParentNode->saveDataState(d, m_pDataBase->getDataStateBase()->getCurrentStateId());
        }
        pParentNode->saveDataAttributes(d);
        pParentNode->saveIndex();
    }
}

}}
