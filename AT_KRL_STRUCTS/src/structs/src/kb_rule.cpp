// #include "kb_rule.h"
// #include "kb_entity.h"
// #include <string>
// #include <vector>
// #include <optional>
// #include <map>
// #include <memory>
// #include <algorithm>
// #include <memory>
// #include <cstring>


// // Реализация класса KBInstruction
// std::unique_ptr<KBInstruction> KBInstruction::from_xml(xmlNodePtr element) {
//     return std::make_unique<KBInstruction>();
// }

// std::string KBInstruction::krl() const {
//     return "";
// }

// void KBInstruction::validate(KBEntity* kb) {
//     // Реализация валидации
// }


// KBRule::KBRule(const std::string& id, std::unique_ptr<Evaluatable> condition,
//                std::vector<std::unique_ptr<KBInstruction>> instructions,
//                std::optional<std::vector<std::unique_ptr<KBInstruction>>> else_instructions,
//                const std::string& meta, const std::string& desc)
//     : id(id), condition(std::move(condition)), instructions(std::move(instructions)),
//     else_instructions(std::move(else_instructions)), meta(meta), desc(desc.empty() ? id : desc) {

//     this->condition->owner = this;
//     for (auto& instr : this->instructions) {
//         instr->owner = this;
//     }

//     if (this->else_instructions) {
//         for (auto& else_instr : *this->else_instructions) {
//             else_instr->owner = this;
//         }
//     }
// }

// std::map<std::string, std::string> KBRule::attrs() const {
//     auto parent_attrs = attrs();
//     parent_attrs["id"] = id;
//     parent_attrs["meta"] = meta;
//     parent_attrs["desc"] = desc;
//     return parent_attrs;
// }

// std::vector<xmlNodePtr> KBRule::inner_xml() const {
//     std::vector<xmlNodePtr> res;

//     xmlNodePtr condition_node = xmlNewNode(NULL, BAD_CAST "condition");
//     xmlAddChild(condition_node, condition->toXML());
//     res.push_back(condition_node);

//     xmlNodePtr action_node = xmlNewNode(NULL, BAD_CAST "action");
//     for (const auto& instruction : instructions) {
//         xmlAddChild(action_node, instruction->xml);
//     }
//     res.push_back(action_node);

//     if (else_instructions && !else_instructions->empty()) {
//         xmlNodePtr else_action_node = xmlNewNode(NULL, BAD_CAST "else-action");
//         for (const auto& instruction : *else_instructions) {
//             xmlAddChild(else_action_node, instruction->xml);
//         }
//         res.push_back(else_action_node);
//     }

//     return res;
// }

// std::unique_ptr<KBRule> KBRule::from_xml(xmlNodePtr xml) {
//     xmlNodePtr condition_xml = xmlFirstElementChild(xml->children);
//     auto condition = from_xml(condition_xml);

//     xmlNodePtr action_xml = xmlFirstElementChild(xml->children);
//     std::vector<std::unique_ptr<KBInstruction>> instructions;
//     for (xmlNodePtr instruction_xml = xmlFirstElementChild(action_xml->children); instruction_xml; instruction_xml = xmlNextElementSibling(instruction_xml)) {
//         instructions.push_back(KBInstruction::from_xml(instruction_xml));
//     }

//     std::optional<std::vector<std::unique_ptr<KBInstruction>>> else_instructions;
//     xmlNodePtr else_action_xml = xmlFirstElementChild(xml->children);
//     if (else_action_xml) {
//         std::vector<std::unique_ptr<KBInstruction>> else_instrs;
//         for (xmlNodePtr else_instruction_xml = xmlFirstElementChild(else_action_xml->children); else_instruction_xml; else_instruction_xml = xmlNextElementSibling(else_instruction_xml)) {
//             else_instrs.push_back(KBInstruction::from_xml(else_instruction_xml));
//         }
//         else_instructions = std::move(else_instrs);
//     }
//     return NULL;
//     //return std::make_unique<KBRule>(xmlGetProp(xml, BAD_CAST "id"), std::move(condition), std::move(instructions), std::move(else_instructions));
// }

// std::map<std::string, std::string> KBRule::to_dict() const {
//     std::map<std::string, std::string> res = attrs();
//     return res;
// }

// std::unique_ptr<KBRule> KBRule::from_dict(const std::map<std::string, std::string>& d) {
//     return nullptr;
// }

// std::string KBRule::krl() const {
//     std::string action_krl = "ТО\n    ";
//     for (const auto& instruction : instructions) {
//         action_krl += instruction->krl() + "\n    ";
//     }

//     std::string else_action_krl;
//     if (else_instructions && !else_instructions->empty()) {
//         else_action_krl = "ИНАЧЕ\n    ";
//         for (const auto& instruction : *else_instructions) {
//             else_action_krl += instruction->krl() + "\n    ";
//         }
//     }

//     return "ПРАВИЛО " + id + "\nЕСЛИ\n    " + condition->getTag()+ "\n" + action_krl + else_action_krl + "КОММЕНТАРИЙ " + desc + "\n";
// }

// void KBRule::validate(KBEntity* kb) {
//     if (!evaluated_condition) {
//         //condition->validate(kb);

//         for (const auto& instruct : instructions) {
//             instruct->validate(kb);
//         }

//         evaluated_condition = "validated";
//     }
// }

// std::string KBRule::xml_owner_path() const {
//     return owner->getXMLOwnerPath() + "/rules/rule[" + id + "]";
// }
