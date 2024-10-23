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

    static std::unique_ptr<KBInstruction> from_xml(xmlNodePtr element);
    std::string krl() const;
    void validate(KBEntity* kb);
};

class KBRule : public KBEntity {
public:
    std::string id;
    std::unique_ptr<Evaluatable> condition;
    std::vector<std::unique_ptr<KBInstruction>> instructions;
    std::optional<std::vector<std::unique_ptr<KBInstruction>>> else_instructions;
    std::string meta;
    std::string desc;
    std::optional<std::string> evaluated_condition;

    explicit KBRule(const std::string& id, std::unique_ptr<Evaluatable> condition,
           std::vector<std::unique_ptr<KBInstruction>> instructions,
           std::optional<std::vector<std::unique_ptr<KBInstruction>>> else_instructions = std::nullopt,
           const std::string& meta = "simple", const std::string& desc = "");

    std::map<std::string, std::string> attrs() const;
    std::vector<xmlNodePtr> inner_xml() const;
    static std::unique_ptr<KBRule> from_xml(xmlNodePtr xml);
    std::map<std::string, std::string> to_dict() const;
    static std::unique_ptr<KBRule> from_dict(const std::map<std::string, std::string>& d);
    std::string krl() const;
    void validate(KBEntity* kb);
    std::string xml_owner_path() const;
};

#endif // KBRULE_H
