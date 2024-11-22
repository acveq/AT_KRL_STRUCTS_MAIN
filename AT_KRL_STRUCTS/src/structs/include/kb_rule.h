#ifndef KB_RULE_H
#define KB_RULE_H
#include <string>
#include <vector>
#include "kb_entity.h"
#include "kb_value.h"
#include "kb_operation.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>


class KBInstruction {
public:
    KBEntity* owner;
    xmlNodePtr xml;
    static unique_ptr<KBInstruction> from_xml(xmlNodePtr element);
    string krl() const;
    void validate(KBEntity* kb);
};

class KBRule : public KBEntity {
public:
    string id;
    unique_ptr<Evaluatable> condition;
    vector<unique_ptr<KBInstruction>> instructions;
    optional<vector<unique_ptr<KBInstruction>>> else_instructions;
    string meta;
    string desc;
    optional<string> evaluated_condition;

    explicit KBRule(const string& id, unique_ptr<Evaluatable> condition,
           vector<unique_ptr<KBInstruction>> instructions,
           optional<vector<unique_ptr<KBInstruction>>> else_instructions = nullopt,
           const string& meta = "simple", const string& desc = "");

    map<string, string> attrs() const;
    vector<xmlNodePtr> inner_xml() const;
    static unique_ptr<KBRule> from_xml(xmlNodePtr xml);
    map<string, string> to_dict() const;
    static unique_ptr<KBRule> from_dict(const map<string, string>& d);
    string krl() const;
    void validate(KBEntity* kb);
    string xml_owner_path() const;
};

#endif // KBRULE_H
