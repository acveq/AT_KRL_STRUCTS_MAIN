#include "../include/kb_rule.h"
#include "kb_entity.h"
#include <string>
#include <vector>
#include <optional>
#include <map>
#include <memory>
#include <algorithm>
#include <memory>
#include <cstring>

// Реализация класса KBInstruction
unique_ptr<KBInstruction> KBInstruction::from_xml(xmlNodePtr element) {
    return make_unique<KBInstruction>();
}
string KBInstruction::krl() const {
    return "";
}
void KBInstruction::validate(KBEntity* kb) {

}

KBRule::KBRule(const string& id, unique_ptr<Evaluatable> condition,
            vector<unique_ptr<KBInstruction>> instructions,
            optional<vector<unique_ptr<KBInstruction>>> else_instructions,
            const string& meta, const string& desc)
    : KBEntity(id), id(id), condition(move(condition)), instructions(move(instructions)),
    else_instructions(move(else_instructions)), meta(meta), desc(desc.empty() ? id : desc) {

    this->condition->owner = this;
    for (auto& instr : this->instructions) {
        instr->owner = this;
    }

    if (this->else_instructions) {
        for (auto& else_instr : *this->else_instructions) {
            else_instr->owner = this;
        }
    }
}
map<string, string> KBRule::attrs() const {
    auto parent_attrs = attrs();
    parent_attrs["id"] = id;
    parent_attrs["meta"] = meta;
    parent_attrs["desc"] = desc;
    return parent_attrs;
}
vector<xmlNodePtr> KBRule::inner_xml() const {
    vector<xmlNodePtr> res;

    xmlNodePtr condition_node = xmlNewNode(NULL, BAD_CAST "condition");
    xmlAddChild(condition_node, condition->toXML());
    res.push_back(condition_node);

    xmlNodePtr action_node = xmlNewNode(NULL, BAD_CAST "action");
    for (const auto& instruction : instructions) {
        xmlAddChild(action_node, instruction->xml);
    }
    res.push_back(action_node);

    if (else_instructions && !else_instructions->empty()) {
        xmlNodePtr else_action_node = xmlNewNode(NULL, BAD_CAST "else-action");
        for (const auto& instruction : *else_instructions) {
            xmlAddChild(else_action_node, instruction->xml);
        }
        res.push_back(else_action_node);
    }

    return res;
}
unique_ptr<KBRule> KBRule::from_xml(xmlNodePtr xml) {
    xmlNodePtr condition_xml = xmlFirstElementChild(xml->children);
    auto condition = from_xml(condition_xml);

    xmlNodePtr action_xml = xmlFirstElementChild(xml->children);
    vector<unique_ptr<KBInstruction>> instructions;
    for (xmlNodePtr instruction_xml = xmlFirstElementChild(action_xml->children); instruction_xml; instruction_xml = xmlNextElementSibling(instruction_xml)) {
        instructions.push_back(KBInstruction::from_xml(instruction_xml));
    }

    optional<vector<unique_ptr<KBInstruction>>> else_instructions;
    xmlNodePtr else_action_xml = xmlFirstElementChild(xml->children);
    if (else_action_xml) {
        vector<unique_ptr<KBInstruction>> else_instrs;
        for (xmlNodePtr else_instruction_xml = xmlFirstElementChild(else_action_xml->children); else_instruction_xml; else_instruction_xml = xmlNextElementSibling(else_instruction_xml)) {
            else_instrs.push_back(KBInstruction::from_xml(else_instruction_xml));
        }
        else_instructions = move(else_instrs);
    }
    return NULL;
    //return make_unique<KBRule>(xmlGetProp(xml, BAD_CAST "id"), move(condition), move(instructions), move(else_instructions));
}
map<string, string> KBRule::to_dict() const {
    map<string, string> res = attrs();
    return res;
}
unique_ptr<KBRule> KBRule::from_dict(const map<string, string>& d) {
    return nullptr;
}
string KBRule::krl() const {
    string action_krl = "ТО\n    ";
    for (const auto& instruction : instructions) {
        action_krl += instruction->krl() + "\n    ";
    }

    string else_action_krl;
    if (else_instructions && !else_instructions->empty()) {
        else_action_krl = "ИНАЧЕ\n    ";
        for (const auto& instruction : *else_instructions) {
            else_action_krl += instruction->krl() + "\n    ";
        }
    }

    return "ПРАВИЛО " + id + "\nЕСЛИ\n    " + condition->getTag()+ "\n" + action_krl + else_action_krl + "КОММЕНТАРИЙ " + desc + "\n";
}
void KBRule::validate(KBEntity* kb) {
    if (!evaluated_condition) {
        //condition->validate(kb);

        for (const auto& instruct : instructions) {
            instruct->validate(kb);
        }

        evaluated_condition = "validated";
    }
}
string KBRule::xml_owner_path() const {
    return owner->getXMLOwnerPath() + "/rules/rule[" + id + "]";
}
