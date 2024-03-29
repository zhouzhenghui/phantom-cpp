/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UndoStack.h"
#include "UndoStack.hxx"
#include "UndoCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), UndoStack);

o_namespace_begin(phantom, qt)

UndoStack::UndoStack() 
: m_iStackIndex(-1)
{

}

UndoStack::~UndoStack()
{
    for(auto it = m_UndoCommands.rbegin(); it != m_UndoCommands.rend(); ++it)
    {
        o_dynamic_delete *it;
    }
}

void UndoStack::pushCommand( UndoCommand* a_pUndoCommand )
{
    o_connect(a_pUndoCommand, undone(), this, slotCommandUndone());
    o_connect(a_pUndoCommand, redone(), this, slotCommandRedone());
    o_assert(a_pUndoCommand->m_uiIndex == ~size_t(0));
    o_assert(a_pUndoCommand->m_pUndoStack == nullptr);
    o_assert(std::find(m_UndoCommands.begin(), m_UndoCommands.end(), a_pUndoCommand) == m_UndoCommands.end());
    a_pUndoCommand->m_uiIndex = m_iStackIndex+1;
    a_pUndoCommand->setUndoStack(this);
    auto where = m_UndoCommands.begin()+(m_iStackIndex+1);
    m_UndoCommands.insert(where, a_pUndoCommand);
    if(a_pUndoCommand->internalRedo())
    {
        m_iStackIndex++;
        // Delete command after the current stack index
        while(m_UndoCommands.size() > (size_t)(m_iStackIndex+1))
        {
            o_emit commandAboutToBeRemoved(m_UndoCommands.back());
            o_dynamic_delete m_UndoCommands.back();
            m_UndoCommands.pop_back();
        }
        o_emit commandAdded(a_pUndoCommand);
        o_emit stackIndexChanged(m_iStackIndex);
    }
    else 
    {
        m_UndoCommands.erase(m_UndoCommands.begin()+(m_iStackIndex+1));
        o_dynamic_delete a_pUndoCommand;
    }
}


void UndoStack::popCommand( UndoCommand* a_pUndoCommand )
{
    o_disconnect(a_pUndoCommand, undone(), this, slotCommandUndone());
    o_disconnect(a_pUndoCommand, redone(), this, slotCommandRedone());
    o_assert(m_UndoCommands[a_pUndoCommand->m_uiIndex] == a_pUndoCommand);
    o_assert(a_pUndoCommand->m_pUndoStack == this);
    size_t foundIndex = 0xffffffff;
    o_emit commandAboutToBeRemoved(a_pUndoCommand);
    for(size_t i = 0; i<m_UndoCommands.size()-1; ++i)
    {
        if(m_UndoCommands[i] == a_pUndoCommand)
        {
            foundIndex = i;
            a_pUndoCommand->m_uiIndex = ~size_t(0);
            a_pUndoCommand->setUndoStack(nullptr);
        }
        if(foundIndex != ~size_t(0))
        {
            m_UndoCommands[i] = m_UndoCommands[i+1];
        }
    }
    o_assert(foundIndex != ~size_t(0) OR m_UndoCommands.back() == a_pUndoCommand);
    if(foundIndex == ~size_t(0)) foundIndex = m_UndoCommands.size()-1;
    if(m_iStackIndex >= foundIndex)
        m_iStackIndex--;
    a_pUndoCommand->internalUndo();
    m_UndoCommands.pop_back();
}

void UndoStack::setStackIndex( int index )
{
    if(m_iStackIndex == index) return;
    o_assert(index < (int)m_UndoCommands.size());
    while(m_iStackIndex < index)
    {
        m_iStackIndex++;
        m_UndoCommands[m_iStackIndex]->internalRedo();
        /*for(int i = m_iStackIndex+1; i<(int)m_UndoCommands.size(); ++i)
        {
            m_UndoCommands[i]->previousCommandRedone(m_UndoCommands[m_iStackIndex]);
        }*/
    }
    while(m_iStackIndex > index )
    {
        m_UndoCommands[m_iStackIndex--]->internalUndo();
    }
    o_emit stackIndexChanged(m_iStackIndex);
}

bool UndoStack::isUndoable() const
{
    return m_iStackIndex > -1;
}

bool UndoStack::isRedoable() const
{
    return m_iStackIndex < ((int)m_UndoCommands.size())-1;
}

void UndoStack::abortInProgressCommand()
{

}

void UndoStack::slotCommandUndone()
{
    o_emit commandUndone(as<UndoCommand*>(connection::sender()));
}

void UndoStack::slotCommandRedone()
{
    o_emit commandRedone(as<UndoCommand*>(connection::sender()));
}

o_namespace_end(phantom, qt)