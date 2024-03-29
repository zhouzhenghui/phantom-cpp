#ifndef o_reflection_eval_CxxDriver_h__
#define o_reflection_eval_CxxDriver_h__

namespace phantom 
{
    class CxxParser;
    class CxxLexer;
    struct CxxToken;
    struct CxxTokenizer;
    class CxxSearchContext;
    namespace reflection 
    {
        class CxxPrecompiler;
    }
    struct CxxStatements;
    typedef CxxStatements CxxDeclarations;
    struct CxxExpression;

    class CxxDriver
    {        
        friend struct CxxTokenizer;

    public:
        enum EParseType
        {
            e_ParseType_TranslationUnit,
            e_ParseType_Expression,
        };

    public:
        static CxxDriver*   Instance() { return sm_pInstance; }

    public:
        CxxDriver(const string& a_strExpressionToParse);
        CxxDriver(reflection::Source* a_pSource);
        ~CxxDriver();
        CxxLexer* getLexer() const { return m_pLexer; }
        CxxParser* getParser() const { return m_pParser; }
        std::string* getFileName() const { return m_pFileName; }
        void registerToken(CxxToken* a_pToken)
        {
            o_assert(m_tokens);
            m_tokens->push_back(a_pToken);
        }

        bool isShaman() const { return true; }

        void incrementErrorCount();

        bool waitForExpressionParsingStart() const { return m_eParseType == e_ParseType_Expression AND !m_bExpressionParsingStarted; }

        void setExpressionParsingStarted();

        int parse(vector<CxxToken*>& tokenproduction);

        EParseType getParseType() const { return m_eParseType; }

        CxxDeclarations*    declarations() const { if(m_eParseType == e_ParseType_TranslationUnit) return m_Result.d; return nullptr; }

        CxxExpression*      expression() const { if(m_eParseType == e_ParseType_Expression) return m_Result.e; return nullptr; }

        void setParserDebugLevel(int level);

        reflection::Source* getSource() const { return m_pSource; }

        int     handleEndOfFile();

    protected:
        CxxParser* m_pParser;
        CxxLexer* m_pLexer;
        std::string* m_pFileName;
        static CxxDriver* sm_pInstance;
        EParseType m_eParseType;
        bool m_bExpressionParsingStarted;
        vector<CxxToken*>* m_tokens;
        reflection::Source* m_pSource;
        istream* m_pInputStream;
        size_t m_uiInputStreamIndex;
        union 
        {
            CxxDeclarations* d;
            CxxExpression* e;
        } m_Result;
    };
}

#endif // o_reflection_eval_CxxDriver_h__
