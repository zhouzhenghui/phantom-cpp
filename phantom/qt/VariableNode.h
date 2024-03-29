#ifndef phantom_qt_VariableNode_h__
#define phantom_qt_VariableNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
#include <QIcon>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableNode);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableModel;
class VariableAction;
class UndoStack;
class UndoCommand;
class VariableNodeDelegate;
class Menu;
class VariableWidgetEditor;

enum EVariableNodeProperty
{
    e_VariableNodeProperty_ReloadOnChildChange = 0x1,
};

o_declare_flags(VariableNodeProperties, EVariableNodeProperty);

class o_qt_export VariableNode 
{
    friend class VariableModel;

public:
    static VariableNode* FromData(serialization::DataBase* a_pDataBase, const vector<phantom::data>& a_Data);

    enum EClassDisplayPolicy
    {
        e_ClassDisplayPolicy_Tree,
        e_ClassDisplayPolicy_List,
    };

    VariableNode(const string& a_strName);
    VariableNode(const string& a_strName, const vector<reflection::Expression*>& a_Expressions, reflection::Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    VariableNode(reflection::Type* a_pValueType, const string& a_strName, const vector<reflection::Expression*>& a_Expressions, reflection::Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    ~VariableNode();

    o_initialize();
    o_terminate();

    // void eval(EEvalPolicies a_eEvalPolicy);
    void setDelegate(VariableNodeDelegate* a_pDelegate);

    VariableWidgetEditor* createEditor() const;
    QWidget* createActionWidget() const;
    QWidget* createValueWidget() const;
    Menu* createMenu() const;

    string valueText() const;
    QIcon valueIcon() const;

    VariableModel* getVariableModel() const { return m_pVariableModel; }

    virtual UndoCommand* createValueSetUndoCommand(const void* a_pValue) const;

    bool hasModifier(modifiers_t a_Modifier) const { return (m_Modifiers & a_Modifier) == a_Modifier; }

    void setModifiers(modifiers_t a_Modifiers) { m_Modifiers = a_Modifiers; }

    modifiers_t getModifiers() const { return m_Modifiers; }

    bool hasMultipleValues() const;

    bool hasExpressions() const { return !m_Expressions.empty(); }

    reflection::Type*  getValueType() const;

    void setChangingStructure(bool a_bValue)
    {
        m_bChangeStructure = a_bValue;
    }

    bool isChangingStructure() const { return m_bChangeStructure; }

    void flush() const;

    void update() const;

    const QIcon& getIcon() const { return m_Icon; }

    void setIcon(const QIcon& a_Icon) { m_Icon = a_Icon; }

    void getValue(void* a_pDest) const;

    void setValue(void const* a_pSrc) const;

    void getValues(void** a_pMultipleDest) const;

    void setValues(void const ** a_pMultipleSrc) const;

    VariableNode* getParentNode() const { return m_pParentNode; }

    VariableNode* getPrev() const { return m_pParentNode ? m_pParentNode->getPrevChild((VariableNode*)this) : nullptr; }

    VariableNode* getNext() const { return m_pParentNode ? m_pParentNode->getNextChild((VariableNode*)this) : nullptr; }

    VariableNode* getNextChild(VariableNode* a_pCurrent) const;

    VariableNode* getPrevChild(VariableNode* a_pCurrent) const;

    // reflection::Expression* evalExpression(size_t i) const;

    vector<reflection::Expression*>::const_iterator beginExpressions() const { return m_Expressions.begin(); }
    vector<reflection::Expression*>::const_iterator endExpressions() const { return m_Expressions.end(); }

    reflection::Expression* getExpression(size_t i) const { return m_Expressions[i]; }
    size_t getExpressionCount() const { return m_Expressions.size(); }

    reflection::Range* getRange() const { return m_pRange; } 

    void setRange(reflection::Range* a_pRange) { m_pRange = a_pRange; }

    void setName(const string& a_strName);

    const string& getName() const { return m_strName; }

    string getQualifiedName(const string& a_strSeparator = ".") const 
    {
        if(m_pParentNode)
        {
            string qualifiedName = m_pParentNode->getQualifiedName();
            if(NOT(qualifiedName.empty()))
            {
                return qualifiedName + a_strSeparator + m_strName;
            }
        }
        return m_strName;
    }

    vector<VariableNode*>::const_iterator beginChildNodes() const { return m_ChildNodes.begin(); }
    vector<VariableNode*>::const_iterator endChildNodes() const { return m_ChildNodes.end(); }

    size_t  getChildNodeCount() const { return m_ChildNodes.size(); }

    void addChildNode(VariableNode* a_pVariableNode);

    void removeChildNode(VariableNode* a_pVariableNode);

    void setExpressionUndoStack(size_t i, UndoStack* a_pUndoStack)
    {
        m_ExpressionUndoStacks[i] = a_pUndoStack;
    }

    UndoStack* getExpressionUndoStack(size_t i) const
    {
        return m_ExpressionUndoStacks[i];
    }

    void clear();

    void addAction(VariableAction* a_pAction, const string& a_strCategory = "")
    {
        m_Actions[a_strCategory].push_back(a_pAction);
    }

    void invalidate();

protected:
    o_signal_data(nameChanged, const string&);
    o_signal_data(valueChanged);
    o_signal_data(childNodeAdded, VariableNode*);
    o_signal_data(childNodeAboutToBeRemoved, VariableNode*);

protected:
    void setVariableModel(VariableModel* a_pVariableModel);

protected:
    void updateType();
    void destroyExpressions();

protected:
    string                          m_strName;
    string                          m_strValueText;
    QIcon                           m_Icon;
    vector<reflection::Expression*> m_Expressions;
    vector<UndoStack*>              m_ExpressionUndoStacks;
    map<string, vector<VariableAction*>> m_Actions;
    reflection::Type*               m_pValueType;
    reflection::Range*              m_pRange;
    VariableNode*                   m_pParentNode;
    VariableNodeDelegate*           m_pDelegate;
    VariableModel*                  m_pVariableModel;
    vector<VariableNode*>           m_ChildNodes;
    vector<VariableAction*>         m_VariableActions;
    EClassDisplayPolicy             m_eClassDisplayPolicy;
    modifiers_t                        m_Modifiers;
    bool                            m_bChangeStructure;
};

}}


#endif // phantom_qt_VariableNode_h__
