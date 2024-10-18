// #ifndef KB_RULE_H
// #define KB_RULE_H
// #include <string>
// #include <vector>
// #include "kb_entity.h"
// #include "kb_value.h"
// #include "kb_operation.h"

// class KBRule : public KBEntity
// {
// public:
//     KBRule(const string id, const string tag, const char* desc){

//     }
//     virtual ~KBRule();
//     void init(); //string id, condition: Evaluatable, instructions: List[KBInstruction], else_instructions: List[KBInstruction] | None = None, meta='simple', desc=None
//     void attrs();
//     void innerXml();
//     void fromXml(); // xml: Element
//     void dict();
// private:
//     string id;
//     char* desc;
//     Evaluatable * condition = nullptr;
//     //vector<KBInstruc>
//     string meta;
//     KBValue * evaluated_condition = nullptr;
// };

// #endif // KB_RULE_H
