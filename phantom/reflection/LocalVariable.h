

#ifndef o_reflection_LocalVariable_h__
#define o_reflection_LocalVariable_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class Block;
class o_export LocalVariable : public LanguageElement
{
	friend class Block;

public:
    enum 
    {
        e_InvalidFrameOffset = 0x7FFFFFFF
    };

public:
    LocalVariable(Block* a_pBlock, reflection::Type* a_pType, const string& a_strName, const CodeLocation& a_Location, bitfield modifiers = 0);
	~LocalVariable(void) 	{}

    reflection::Type*   getValueType() const { return m_pType; }
    Block*              getBlock() const;

    bool isAccessibleAtCodePosition(const CodePosition& position) const;

    void setFrameOffset(int a_iOffset)
    {
        o_assert(m_iFrameOffset == e_InvalidFrameOffset);
        m_iFrameOffset = a_iOffset;
    }

    int getFrameOffset() const { return m_iFrameOffset; }

    virtual LanguageElement* getElement( const char* a_strQualifiedName , template_specialization const* , function_signature const* , bitfield a_bfModifiers /*= bitfield()*/ ) const;

protected:
    Type*   m_pType;
    int     m_iFrameOffset;	
};

o_namespace_end(phantom, reflection)

o_classNS((phantom, reflection), LocalVariable, (LanguageElement))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection), LocalVariable);


#endif