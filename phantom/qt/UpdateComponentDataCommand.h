#pragma once
#ifndef phantom_qt_UpdateComponentDataCommand_h__
#define phantom_qt_UpdateComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UpdateComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class UpdateComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export UpdateComponentDataCommand : public UndoCommand
{
public:
    typedef fastdelegate::FastDelegate<string(serialization::DataBase*, phantom::data)> namer_delegate;
	//================================================
	// Constructors / Destructor
	//================================================

    UpdateComponentDataCommand(serialization::DataBase* a_pDataBase);
    UpdateComponentDataCommand(serialization::DataBase* a_pDataBase, const phantom::data& a_Data);
    UpdateComponentDataCommand(serialization::DataBase* a_pDataBase, uint guid);
    UpdateComponentDataCommand(serialization::DataBase* a_pDataBase, const vector<uint>& a_Guids);
	~UpdateComponentDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();

    void setNamerDelegate(namer_delegate a_Delegate)
    {
        m_Delegate = a_Delegate;
    }

    virtual UpdateComponentDataCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
    serialization::DataBase*        m_pDataBase;
    vector<uint>                    m_RemovedGuids;
    vector<uint>                    m_AddedGuids;
    vector<uint>                    m_SavedDataGuids;
    vector<uint>                    m_SavedNodeIndexGuids;
    vector<uint>                    m_Guids;
    namer_delegate                  m_Delegate;
    bool                            m_bInitialized;

private:
    static bool ClassTypeHasComponent(reflection::ClassType* a_pType);
    static bool ClassHasComponent(reflection::Class* a_pType);

};

} // qt 
} // phantom

#endif // phantom_qt_UpdateComponentDataCommand_h__
