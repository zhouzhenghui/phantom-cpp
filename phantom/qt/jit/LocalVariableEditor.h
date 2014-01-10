#ifndef phantom_qt_LocalVariableEditor_h__
#define phantom_qt_LocalVariableEditor_h__


/* ****************** Includes ******************* */
#include "phantom/qt/jit/qt_jit.h"
#include "phantom/qt/VariableEditor.h"
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { 
    
namespace qt {

namespace jit {

class LocalVariableManager;
class o_qt_jit_export LocalVariableEditor : public VariableEditor
{
    Q_OBJECT

public:
	LocalVariableEditor(void);
	~LocalVariableEditor(void) {}

    LocalVariableManager* getLocalVariableManager() const;

protected:
    virtual void updateItemLook(QtBrowserItem *item);

protected slots:
    void setCallStackIndex(int index);

};

} // jit
} // qt 
} // phantom 


o_classNS((phantom, qt, jit), LocalVariableEditor, (VariableEditor), o_no_copy)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, qt, jit), LocalVariableEditor);


#endif // phantom_qt_LocalVariableEditor_h__